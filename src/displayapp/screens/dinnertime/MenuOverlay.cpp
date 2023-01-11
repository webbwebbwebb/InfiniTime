#include <lvgl/lvgl.h>
#include <cstdio>
#include <displayapp/Colors.h>
#include "displayapp/screens/Symbols.h"
#include "displayapp/screens/dinnertime/MenuOverlay.h"
#include "components/settings/Settings.h"

using namespace Pinetime::Applications::Screens::DinnerTime;

namespace {
  void event_handler(lv_obj_t* obj, lv_event_t event) {
    auto* screen = static_cast<MenuOverlay*>(obj->user_data);
    screen->HandleEvent(obj, event);
  }
}

void MenuOverlay::Create(lv_obj_t* parent, void* ptr2Object, void(*ptr2Function)(void* ptr2Object, Pinetime::Controllers::Settings::Colors newForegroundColor)) {
  _ptr2Object = ptr2Object;
  _ptr2Function = ptr2Function;
  
  root = lv_obj_create(parent, nullptr);
  lv_obj_set_size(root, 240, 240);
  lv_obj_set_style_local_bg_opa(root, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_0);

  paletteButton = lv_btn_create(root, nullptr);
  paletteButton->user_data = this;
  lv_obj_set_size(paletteButton, 150, 60);
  lv_obj_align(paletteButton, root, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_local_radius(paletteButton, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 20);
  lv_obj_set_style_local_bg_opa(paletteButton, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_50);
  lv_obj_set_event_cb(paletteButton, event_handler);

  paletteIcon = lv_label_create(paletteButton, nullptr);
  lv_obj_set_style_local_text_font(paletteIcon, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_sys_48);
  lv_label_set_text_static(paletteIcon, Symbols::paintbrushLg);

  blueButton = CreateColourButton(root, Pinetime::Controllers::Settings::Colors::Blue);
  lv_obj_align(blueButton, root, LV_ALIGN_CENTER, 0, 88);
  lv_obj_set_hidden(blueButton, true);

  greenButton = CreateColourButton(root, Pinetime::Controllers::Settings::Colors::Green);
  lv_obj_align(greenButton, root, LV_ALIGN_CENTER, 0, -88);
  lv_obj_set_hidden(greenButton, true);

  orangeButton = CreateColourButton(root, Pinetime::Controllers::Settings::Colors::Orange);
  lv_obj_align(orangeButton, root, LV_ALIGN_CENTER, 0, 28);
  lv_obj_set_hidden(orangeButton, true);
  
  pinkButton = CreateColourButton(root, Pinetime::Controllers::Settings::Colors::HotPink);
  lv_obj_align(pinkButton, root, LV_ALIGN_CENTER, 0, -28);
  lv_obj_set_hidden(pinkButton, true);

  Hide();
}

lv_obj_t* MenuOverlay::GetObject() {
  return root;
}

bool MenuOverlay::Inactive() {
  return (lastMenuActionTime > 0) && (lv_tick_get() - lastMenuActionTime > 3000);
}

void MenuOverlay::Show() {
   lv_obj_set_hidden(root, false);
   lv_obj_set_hidden(paletteButton, false);
   lastMenuActionTime = lv_tick_get();
}

void MenuOverlay::Hide() {
  lv_obj_set_hidden(root, true);
  lv_obj_set_hidden(paletteButton, true);
  lv_obj_set_hidden(blueButton, true);
  lv_obj_set_hidden(greenButton, true);
  lv_obj_set_hidden(orangeButton, true);
  lv_obj_set_hidden(pinkButton, true);
  lastMenuActionTime = 0;
}

bool MenuOverlay::Visible() {
  return !lv_obj_get_hidden(root);
}

void MenuOverlay::HandleEvent(lv_obj_t* object, lv_event_t event) {
  if (event == LV_EVENT_CLICKED) {
    if (object == paletteButton) {
      lastMenuActionTime = lv_tick_get();
      lv_obj_set_hidden(paletteButton, true);
      lv_obj_set_hidden(blueButton, false);
      lv_obj_set_hidden(greenButton, false);
      lv_obj_set_hidden(orangeButton, false);
      lv_obj_set_hidden(pinkButton, false);
    }
    if (object == blueButton) {
      lastMenuActionTime = lv_tick_get();
      _ptr2Function(_ptr2Object, Pinetime::Controllers::Settings::Colors::Blue);
    }
    if (object == greenButton) {
      lastMenuActionTime = lv_tick_get();
      _ptr2Function(_ptr2Object, Pinetime::Controllers::Settings::Colors::Green);
    }
    if (object == orangeButton) {
      lastMenuActionTime = lv_tick_get();
      _ptr2Function(_ptr2Object, Pinetime::Controllers::Settings::Colors::Orange);
    }
    if (object == pinkButton) {
      lastMenuActionTime = lv_tick_get();
      _ptr2Function(_ptr2Object, Pinetime::Controllers::Settings::Colors::HotPink);
    }
  } 
}

lv_obj_t* MenuOverlay::CreateColourButton(lv_obj_t* parent, Pinetime::Controllers::Settings::Colors color) {
  lv_obj_t* newButton = lv_btn_create(parent, nullptr);
  newButton->user_data = this;
  lv_obj_set_size(newButton, 64, 64);
  lv_obj_set_style_local_bg_color(newButton, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, Convert(color));
  lv_obj_set_style_local_border_color(newButton, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
  lv_obj_set_style_local_border_width(newButton, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 8);
  lv_obj_set_style_local_radius(newButton, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_RADIUS_CIRCLE);
  lv_obj_set_event_cb(newButton, event_handler);
  return newButton;
}