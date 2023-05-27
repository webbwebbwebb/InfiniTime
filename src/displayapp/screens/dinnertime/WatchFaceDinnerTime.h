#pragma once

#include <lvgl/src/lv_core/lv_obj.h>
#include <chrono>
#include <cstdint>
#include <memory>
#include "displayapp/screens/Screen.h"
#include "components/datetime/DateTimeController.h"
#include "components/ble/BleController.h"
#include "displayapp/widgets/StatusIcons.h"
#include "displayapp/screens/dinnertime/ClockPanel.h"
#include "displayapp/screens/dinnertime/DataPanel.h"
#include "displayapp/screens/dinnertime/MenuOverlay.h"
#include "utility/DirtyValue.h"

extern lv_font_t din_1451_engschrift_28;
extern lv_font_t din_1451_engschrift_158;

namespace Pinetime {
  namespace Controllers {
    class Settings;
    class Battery;
    class Ble;
    class NotificationManager;
    class HeartRateController;
    class MotionController;
  }

  namespace Applications {
    namespace Screens {
      namespace DinnerTime {
        class WatchFaceDinnerTime : public Screen {
        public:
          WatchFaceDinnerTime(
                          const Controllers::Battery& batteryController,
                          const Controllers::Ble& bleController,
                          Controllers::DateTime& dateTimeController,
                          Controllers::HeartRateController& heartRateController,
                          Controllers::MotionController& motionController,
                          Controllers::NotificationManager& notificationManager,
                          Controllers::Settings& settingsController);
                          
          ~WatchFaceDinnerTime() override;

          bool OnButtonPushed() override;
          bool OnTouchEvent(TouchEvents event) override;
          void Refresh() override;

          void OnForegroundColourChanged(Pinetime::Controllers::Settings::Colors newForegroundColor);
          static void OnForegroundColourChangedWrapper(void* ptr2Object, Pinetime::Controllers::Settings::Colors newForegroundColor);

          static bool IsAvailable(Pinetime::Controllers::FS& filesystem);

        private:
          uint8_t displayedHour = -1;
          uint8_t displayedMinute = -1;
          uint8_t displayedSecond = -1;

          uint16_t currentYear = 1970;
          Controllers::DateTime::Months currentMonth = Pinetime::Controllers::DateTime::Months::Unknown;
          Controllers::DateTime::Days currentDayOfWeek = Pinetime::Controllers::DateTime::Days::Unknown;
          uint8_t currentDay = 0;

          Utility::DirtyValue<uint8_t> batteryPercentRemaining {};
          Utility::DirtyValue<bool> powerPresent {};
          Utility::DirtyValue<bool> bleState {};
          Utility::DirtyValue<bool> bleRadioEnabled {};
          Utility::DirtyValue<std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>> currentDateTime {};
          Utility::DirtyValue<bool> motionSensorOk {};
          Utility::DirtyValue<uint32_t> stepCount {};
          Utility::DirtyValue<uint8_t> heartbeat {};
          Utility::DirtyValue<bool> heartbeatRunning {};
          Utility::DirtyValue<bool> notificationState {};

          lv_obj_t* root;
          
          ClockPanel clockPanel;
          DataPanel dataPanel;
          MenuOverlay menuOverlay;

          const Controllers::Battery& batteryController;
          const Controllers::Ble& bleController;
          Controllers::DateTime& dateTimeController;
          Controllers::HeartRateController& heartRateController;
          Controllers::MotionController& motionController;
          Controllers::NotificationManager& notificationManager;
          Controllers::Settings& settingsController;

          lv_task_t* taskRefresh;

          /*
          lv_font_t* din_1451_std_engschrift_158;
          lv_font_t* din_1451_std_engschrift_28;
          */
        };
      }
    }
  }
}
