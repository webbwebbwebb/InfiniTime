#include "displayapp/screens/dinnertime/WatchFaceDinnerTime.h"
#include <lvgl/lvgl.h>
#include <cstdio>
#include <displayapp/Colors.h>
#include "displayapp/screens/Symbols.h"
#include "components/battery/BatteryController.h"
#include "components/ble/BleController.h"
#include "components/ble/NotificationManager.h"
#include "components/heartrate/HeartRateController.h"
#include "components/motion/MotionController.h"
#include "components/settings/Settings.h"

using namespace Pinetime::Applications::Screens::DinnerTime;

WatchFaceDinnerTime::WatchFaceDinnerTime(
                                   const Controllers::Battery& batteryController,
                                   const Controllers::Ble& bleController,
                                   Controllers::DateTime& dateTimeController,
                                   Controllers::HeartRateController& heartRateController,
                                   Controllers::MotionController& motionController,
                                   Controllers::NotificationManager& notificationManager,
                                   Controllers::Settings& settingsController)
                                   /*,Controllers::FS& filesystem)*/
  : currentDateTime {{}},
    batteryController {batteryController},
    bleController {bleController},
    dateTimeController {dateTimeController},
    heartRateController {heartRateController},
    motionController {motionController},
    notificationManager {notificationManager},
    settingsController {settingsController}
  {

  lv_color_t backgroundColor = Convert(settingsController.GetDinnerTimeBackgroundColor());
  lv_color_t foregroundColor = Convert(settingsController.GetDinnerTimeForegroundColor());
  lv_color_t highlightColor = Convert(settingsController.GetDinnerTimeHighlightColor());

/*
  lfs_file f = {};
  if (filesystem.FileOpen(&f, "/fonts/din_1451_std_engschrift_158.bin", LFS_O_RDONLY) >= 0) {
    filesystem.FileClose(&f);
    din_1451_std_engschrift_158 = lv_font_load("F:/fonts/din_1451_std_engschrift_158.bin");
  }

  if (filesystem.FileOpen(&f, "/fonts/din_1451_std_engschrift_28.bin", LFS_O_RDONLY) >= 0) {
    filesystem.FileClose(&f);
    din_1451_std_engschrift_28 = lv_font_load("F:/fonts/din_1451_std_engschrift_28.bin");
  }
*/
  clockPanel.Create(lv_scr_act(), backgroundColor, foregroundColor, &din_1451_engschrift_158);
  lv_obj_align(clockPanel.GetObject(), nullptr, LV_ALIGN_IN_TOP_LEFT, 0, 0);

  dataPanel.Create(lv_scr_act(), backgroundColor, foregroundColor, highlightColor, &din_1451_engschrift_28);
  lv_obj_align(dataPanel.GetObject(), nullptr, LV_ALIGN_IN_TOP_RIGHT, 0, 7);

  menuOverlay.Create(lv_scr_act(), this, OnForegroundColourChangedWrapper);
  lv_obj_align(menuOverlay.GetObject(), nullptr, LV_ALIGN_CENTER, 0, 0);

  taskRefresh = lv_task_create(RefreshTaskCallback, LV_DISP_DEF_REFR_PERIOD, LV_TASK_PRIO_MID, this);
  Refresh();
}

WatchFaceDinnerTime::~WatchFaceDinnerTime() {
  lv_task_del(taskRefresh);
  lv_obj_clean(lv_scr_act());
}

void WatchFaceDinnerTime::Refresh() {

  powerPresent = batteryController.IsPowerPresent();
  if (powerPresent.IsUpdated()) {
    dataPanel.ShowPowerIcon(powerPresent.Get());
  }

  batteryPercentRemaining = batteryController.PercentRemaining();
  if (batteryPercentRemaining.IsUpdated()) {
    auto batteryPercent = batteryPercentRemaining.Get();
    dataPanel.SetBatteryPercentage(batteryPercent);
  }

  bleState = bleController.IsConnected();
  bleRadioEnabled = bleController.IsRadioEnabled();
  if (bleState.IsUpdated() || bleRadioEnabled.IsUpdated()) {
    dataPanel.ShowBluetoothIcon(bleState.Get());
  }

  notificationState = notificationManager.AreNewNotificationsAvailable();
  if (notificationState.IsUpdated()) {
    dataPanel.ShowNotificationIcon(notificationState.Get());    
  }

  currentDateTime = dateTimeController.CurrentDateTime();

  if (currentDateTime.IsUpdated()) {
    auto hour = dateTimeController.Hours();
    auto minute = dateTimeController.Minutes();
    auto second = dateTimeController.Seconds();
    auto year = dateTimeController.Year();
    auto month = dateTimeController.Month();
    auto dayOfWeek = dateTimeController.DayOfWeek();
    auto day = dateTimeController.Day();

    if (displayedSecond != second) {
      displayedSecond = second;
      dataPanel.SetSeconds(second);
    }

    if (displayedHour != hour || displayedMinute != minute) {
      displayedHour = hour;
      displayedMinute = minute;

      if (settingsController.GetClockType() == Controllers::Settings::ClockType::H12) {
        if (hour == 0) {
          hour = 12;
        } else if (hour > 12) {
          hour = hour - 12;
        }
        
      }
      clockPanel.SetHour(hour);
      clockPanel.SetMinute(minute);
    }

    if ((year != currentYear) || (month != currentMonth) || (dayOfWeek != currentDayOfWeek) || (day != currentDay)) {
      dataPanel.SetDate(dateTimeController.DayOfWeekShortToString(), day);
      currentYear = year;
      currentMonth = month;
      currentDayOfWeek = dayOfWeek;
      currentDay = day;
    }
  }

  heartbeat = heartRateController.HeartRate();
  heartbeatRunning = heartRateController.State() != Controllers::HeartRateController::States::Stopped;
  if (heartbeat.IsUpdated() || heartbeatRunning.IsUpdated()) {
    dataPanel.SetHeartrate(heartbeat.Get());
  }

  stepCount = motionController.NbSteps();
  if (stepCount.IsUpdated()) {
    dataPanel.SetSteps(stepCount.Get());
  }

  if (menuOverlay.Visible() && menuOverlay.Inactive()) {
      menuOverlay.Hide();
  }
}

void WatchFaceDinnerTime::OnForegroundColourChanged(Pinetime::Controllers::Settings::Colors newForegroundColor) {
  clockPanel.SetForegroundColor(Convert(newForegroundColor));
  dataPanel.SetForegroundColor(Convert(newForegroundColor));
  settingsController.SetDinnerTimeForegroundColor(newForegroundColor);
  settingsController.SaveSettings();
}

void WatchFaceDinnerTime::OnForegroundColourChangedWrapper(void* ptr2Object, Pinetime::Controllers::Settings::Colors newForegroundColor) {
  WatchFaceDinnerTime* instance = (WatchFaceDinnerTime*)ptr2Object;
  instance->OnForegroundColourChanged(newForegroundColor);
}

bool WatchFaceDinnerTime::OnButtonPushed() {
  if (menuOverlay.Visible()) {
    menuOverlay.Hide();
    return true;
  }
  return false;
}

bool WatchFaceDinnerTime::OnTouchEvent(Pinetime::Applications::TouchEvents event) {
  if ((event == Pinetime::Applications::TouchEvents::LongTap) && !menuOverlay.Visible()) {
    menuOverlay.Show();
    return true;
  }
  return false;
}

/*
bool WatchFaceDinnerTime::IsAvailable(Pinetime::Controllers::FS& filesystem) {

  lfs_file file = {};

  if (filesystem.FileOpen(&file, "/fonts/din_1451_std_engschrift_158.bin", LFS_O_RDONLY) < 0) {
    return false;
  }
  filesystem.FileClose(&file);

  if (filesystem.FileOpen(&file, "/fonts/din_1451_std_engschrift_28.bin", LFS_O_RDONLY) < 0) {
    return false;
  }
  filesystem.FileClose(&file);

  return true;
}
*/