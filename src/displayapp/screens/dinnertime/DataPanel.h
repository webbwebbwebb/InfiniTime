
#pragma once
#include <cstdint>
#include <lvgl/src/lv_core/lv_obj.h>
#include "displayapp/screens/BatteryIcon.h"

namespace Pinetime {
  namespace Applications {
    namespace Screens {
      namespace DinnerTime {
        class DataPanel {
        public:
          DataPanel();
          void Create(lv_obj_t* parent, lv_color_t backgroundColor, lv_color_t foregroundColor, lv_color_t highlightColor, lv_font_t* dataFont);
          void SetBatteryPercentage(uint8_t percentage);
          void SetDate(const char* shortDayName, uint8_t dayNumber);
          void SetHeartrate(uint8_t bpm);
          void SetSeconds(uint8_t seconds);
          void SetSteps(uint32_t dayNumber);
          void SetForegroundColor(lv_color_t color);
          void ShowBluetoothIcon(bool show);
          void ShowNotificationIcon(bool show);
          void ShowPowerIcon(bool show);
          lv_obj_t* GetObject();

        private:
          BatteryIcon batteryIcon;
          lv_obj_t* root;

          lv_obj_t* batteryRow;
          lv_obj_t* batteryIconContainer;
          lv_obj_t* powerIcon;
          lv_obj_t* batteryPercentageValue;

          lv_obj_t* heartbeatRow;
          lv_obj_t* heartbeatIconContainer;
          lv_obj_t* heartbeatIcon;
          lv_obj_t* heartbeatValue;

          lv_obj_t* stepRow;
          lv_obj_t* stepIconContainer;
          lv_obj_t* stepIcon;
          lv_obj_t* stepValue;

          lv_obj_t* dateRow;
          lv_obj_t* dateIconContainer;
          lv_obj_t* dateIcon;
          lv_obj_t* dateValue;

          lv_obj_t* secondsRow;
          lv_obj_t* secondsIconContainer;
          lv_obj_t* secondsIcon;
          lv_obj_t* secondsValue;

          lv_obj_t* iconsRow;
          lv_obj_t* bluetoothIconContainer;
          lv_obj_t* bluetoothIcon;
          lv_obj_t* notificationIcon;
        };
      }
    }
  }
}
