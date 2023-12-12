#include <lvgl/lvgl.h>
#include "displayapp/screens/Symbols.h"
#include "displayapp/screens/dinnertime/ClockPanel.h"

using namespace Pinetime::Applications::Screens::DinnerTime;

void ClockPanel::Create(lv_obj_t* parent, lv_color_t backgroundColor, lv_color_t foregroundColor, lv_font_t* timeFont) {

  const lv_coord_t width = 112;
  const lv_coord_t height = 240;

  root = lv_obj_create(parent, nullptr);
  lv_obj_set_size(root, width, height);
  lv_obj_set_style_local_bg_color(root, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, backgroundColor);

  hourValue = lv_label_create(root, nullptr);
  lv_obj_set_style_local_text_color(hourValue, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, foregroundColor);
  lv_obj_set_style_local_text_font(hourValue, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, timeFont);
  lv_obj_set_style_local_text_letter_space(hourValue,LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, -8);
  lv_obj_align(hourValue, nullptr, LV_ALIGN_IN_TOP_LEFT, 1, 5);

  minuteValue = lv_label_create(root, nullptr);
  lv_obj_set_style_local_text_color(minuteValue, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, foregroundColor);
  lv_obj_set_style_local_text_font(minuteValue, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, timeFont);
  lv_obj_set_style_local_text_letter_space(minuteValue, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, -8);
  lv_obj_align(minuteValue, hourValue, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 2);
}

void ClockPanel::SetForegroundColor(lv_color_t color){
  lv_obj_set_style_local_text_color(hourValue, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, color);
  lv_obj_set_style_local_text_color(minuteValue, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, color);
}

void ClockPanel::SetHour(uint8_t hours) {
  lv_label_set_text_fmt(hourValue, "%02d", hours);
  lv_obj_realign(hourValue);
}

void ClockPanel::SetMinute(uint8_t minutes) {
  lv_label_set_text_fmt(minuteValue, "%02d", minutes);
  lv_obj_realign(minuteValue);
}

lv_obj_t* ClockPanel::GetObject() {
  return root;
}