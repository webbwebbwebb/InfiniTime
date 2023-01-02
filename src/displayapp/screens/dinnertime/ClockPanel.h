
#pragma once
#include <cstdint>
#include <lvgl/src/lv_core/lv_obj.h>

namespace Pinetime {
  namespace Applications {
    namespace Screens {
      namespace DinnerTime {
        class ClockPanel {
        public:
          void Create(lv_obj_t* parent, lv_color_t backgroundColour, lv_color_t foregroundColour, lv_font_t* timeFont);
          void SetHour(uint8_t hours);
          void SetMinute(uint8_t minutes);
          lv_obj_t* GetObject();

        private:
          lv_obj_t* root;
          lv_obj_t* hourValue;
          lv_obj_t* minuteValue;
        };
      }
    }
  }
}
