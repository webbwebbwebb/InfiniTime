
#pragma once
#include <cstdint>
#include <lvgl/src/lv_core/lv_obj.h>
#include "components/settings/Settings.h"

namespace Pinetime {
  namespace Applications {
    namespace Screens {
      namespace DinnerTime {
        class MenuOverlay {
        public:
          void Create(lv_obj_t* parent, void* pt2Object, void(*ptr2Function)(void* ptr2Object, Pinetime::Controllers::Settings::Colors newForegroundColor));
          lv_obj_t* GetObject();
          void HandleEvent(lv_obj_t* object, lv_event_t event);
          bool Inactive();
          void Show();
          void Hide();
          bool Visible();

        private:
          lv_obj_t* CreateColourButton(lv_obj_t* parent, Pinetime::Controllers::Settings::Colors color);
          uint32_t lastMenuActionTime = 0;
          lv_obj_t* root;
          lv_obj_t* paletteButton;
          lv_obj_t* paletteIcon;
          lv_obj_t* blueButton;
          lv_obj_t* greenButton;
          lv_obj_t* orangeButton;
          lv_obj_t* pinkButton;

          void* _ptr2Object;
          void(*_ptr2Function)(void* ptr2Object, Pinetime::Controllers::Settings::Colors newForegroundColor);
        };
      }
    }
  }
}
