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

extern lv_font_t din_1451_std_engschrift_28;
extern lv_font_t din_1451_std_engschrift_158;

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
          WatchFaceDinnerTime(Applications::DisplayApp* app,
                          Controllers::DateTime& dateTimeController,
                          Controllers::Battery& batteryController,
                          Controllers::Ble& bleController,
                          Controllers::NotificationManager& notificatioManager,
                          Controllers::Settings& settingsController,
                          Controllers::HeartRateController& heartRateController,
                          Controllers::MotionController& motionController,
                          Controllers::FS& filesystem);
          ~WatchFaceDinnerTime() override;

          void Refresh() override;

          static bool IsAvailable(Pinetime::Controllers::FS& filesystem);

        private:
          uint8_t displayedHour = -1;
          uint8_t displayedMinute = -1;
          uint8_t displayedSecond = -1;

          uint16_t currentYear = 1970;
          Controllers::DateTime::Months currentMonth = Pinetime::Controllers::DateTime::Months::Unknown;
          Controllers::DateTime::Days currentDayOfWeek = Pinetime::Controllers::DateTime::Days::Unknown;
          uint8_t currentDay = 0;

          DirtyValue<uint8_t> batteryPercentRemaining {};
          DirtyValue<bool> powerPresent {};
          DirtyValue<bool> bleState {};
          DirtyValue<bool> bleRadioEnabled {};
          DirtyValue<std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>> currentDateTime {};
          DirtyValue<bool> motionSensorOk {};
          DirtyValue<uint32_t> stepCount {};
          DirtyValue<uint8_t> heartbeat {};
          DirtyValue<bool> heartbeatRunning {};
          DirtyValue<bool> notificationState {};

          lv_obj_t* root;
          
          ClockPanel clockPanel;
          DataPanel dataPanel;

          Controllers::Battery& batteryController;
          Controllers::Ble& bleController;
          Controllers::DateTime& dateTimeController;
          Controllers::NotificationManager& notificatioManager;
          Controllers::Settings& settingsController;
          Controllers::HeartRateController& heartRateController;
          Controllers::MotionController& motionController;

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
