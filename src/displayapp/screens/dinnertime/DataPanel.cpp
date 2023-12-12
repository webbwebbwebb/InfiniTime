#include <lvgl/lvgl.h>
#include "displayapp/screens/Symbols.h"
#include "displayapp/screens/dinnertime/DataPanel.h"

using namespace Pinetime::Applications::Screens::DinnerTime;

DataPanel::DataPanel() : batteryIcon(true) {
  
}

void DataPanel::Create(lv_obj_t* parent, lv_color_t backgroundColor, lv_color_t foregroundColor, lv_color_t highlightColor, lv_font_t* dataFont) {

  const lv_coord_t width = 112;
  const lv_coord_t height = 226;
  const lv_coord_t rowHeight = 32;
  const lv_coord_t rowSpacing = 6;
  const lv_coord_t leftPadding = 6;
  const lv_coord_t rightPadding = 6;

  root = lv_obj_create(parent, nullptr);
  lv_obj_set_size(root, width, height);
  lv_obj_set_style_local_bg_color(root, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, backgroundColor);

  batteryRow = lv_obj_create(root, nullptr);
  lv_obj_set_size(batteryRow, width, rowHeight);
  lv_obj_set_style_local_radius(batteryRow, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 2);
  lv_obj_set_style_local_bg_color(batteryRow, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, foregroundColor);
  lv_obj_align(batteryRow, nullptr, LV_ALIGN_IN_TOP_MID, 0, 0);

  batteryIconContainer = lv_obj_create(batteryRow, nullptr);
  lv_obj_set_size(batteryIconContainer, 32, rowHeight);
  lv_obj_set_style_local_bg_color(batteryIconContainer, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, foregroundColor);
  lv_obj_align(batteryIconContainer, nullptr, LV_ALIGN_IN_LEFT_MID, 0, 0);

  batteryIcon.Create(batteryIconContainer);
  lv_obj_align(batteryIcon.GetObject(), nullptr, LV_ALIGN_CENTER, 0, 0);

  powerIcon = lv_label_create(batteryRow, nullptr);
  lv_obj_set_style_local_text_color(powerIcon, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, highlightColor);
  lv_label_set_text_static(powerIcon, Symbols::plug);
  lv_obj_align(powerIcon, nullptr, LV_ALIGN_IN_LEFT_MID, leftPadding + 24, 0);
  ShowPowerIcon(false);

  batteryPercentageValue = lv_label_create(batteryRow, nullptr);
  lv_obj_set_style_local_text_color(batteryPercentageValue, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, backgroundColor);
  lv_obj_set_style_local_text_font(batteryPercentageValue, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, dataFont);
  lv_label_set_text_static(batteryPercentageValue, 0);
  lv_obj_align(batteryPercentageValue, nullptr, LV_ALIGN_IN_RIGHT_MID, -rightPadding, 0);

  weatherRow = lv_obj_create(root, nullptr);
  lv_obj_set_size(weatherRow, width, rowHeight);
  lv_obj_set_style_local_radius(weatherRow, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 2);
  lv_obj_set_style_local_bg_color(weatherRow, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, foregroundColor);
  lv_obj_align(weatherRow, batteryRow, LV_ALIGN_OUT_BOTTOM_MID, 0, rowSpacing);

  weatherIconContainer = lv_obj_create(weatherRow, nullptr);
  lv_obj_set_size(weatherIconContainer, 32, rowHeight);
  lv_obj_set_style_local_bg_color(weatherIconContainer, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, foregroundColor);
  lv_obj_align(weatherIconContainer, nullptr, LV_ALIGN_IN_LEFT_MID, 0, 0);

  weatherIcon = lv_label_create(weatherIconContainer, nullptr);
  lv_obj_set_style_local_text_color(weatherIcon, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, highlightColor);
  lv_obj_set_style_local_text_font(weatherIcon, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &fontawesome_weathericons);
  lv_label_set_text_static(weatherIcon, Symbols::ban);
  lv_obj_align(weatherIcon, nullptr, LV_ALIGN_CENTER, 0, 0);

  temperatureValue = lv_label_create(weatherRow, nullptr);
  lv_obj_set_style_local_text_color(temperatureValue, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, backgroundColor);
  lv_obj_set_style_local_text_font(temperatureValue, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, dataFont);
  lv_label_set_text_static(temperatureValue, "--");
  lv_obj_align(temperatureValue, nullptr, LV_ALIGN_IN_RIGHT_MID, -rightPadding, 0);

  stepRow = lv_obj_create(root, nullptr);
  lv_obj_set_size(stepRow, width, rowHeight);
  lv_obj_set_style_local_radius(stepRow, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 2);
  lv_obj_set_style_local_bg_color(stepRow, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, foregroundColor);
  lv_obj_align(stepRow, weatherRow, LV_ALIGN_OUT_BOTTOM_MID, 0, rowSpacing);

  stepIconContainer = lv_obj_create(stepRow, nullptr);
  lv_obj_set_size(stepIconContainer, 32, rowHeight);
  lv_obj_set_style_local_bg_color(stepIconContainer, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, foregroundColor);
  lv_obj_align(stepIconContainer, nullptr, LV_ALIGN_IN_LEFT_MID, 0, 0);

  stepIcon = lv_label_create(stepIconContainer, nullptr);
  lv_obj_set_style_local_text_color(stepIcon, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, highlightColor);
  lv_label_set_text_static(stepIcon, Symbols::shoe);
  lv_obj_align(stepIcon, nullptr, LV_ALIGN_CENTER, 0, 0);

  stepValue = lv_label_create(stepRow, nullptr);
  lv_obj_set_style_local_text_color(stepValue, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, backgroundColor);
  lv_obj_set_style_local_text_font(stepValue, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, dataFont);
  lv_label_set_text_static(stepValue, 0);
  lv_obj_align(stepValue, nullptr, LV_ALIGN_IN_RIGHT_MID, -rightPadding, 0);

  dateRow = lv_obj_create(root, nullptr);
  lv_obj_set_size(dateRow, width, rowHeight);
  lv_obj_set_style_local_radius(dateRow, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 2);
  lv_obj_set_style_local_bg_color(dateRow, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, foregroundColor);
  lv_obj_align(dateRow, stepRow, LV_ALIGN_OUT_BOTTOM_MID, 0, rowSpacing);

  dateIconContainer = lv_obj_create(dateRow, nullptr);
  lv_obj_set_size(dateIconContainer, 32, rowHeight);
  lv_obj_set_style_local_bg_color(dateIconContainer, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, foregroundColor);
  lv_obj_align(dateIconContainer, nullptr, LV_ALIGN_IN_LEFT_MID, 0, 0);

  dateIcon = lv_label_create(dateIconContainer, nullptr);
  lv_obj_set_style_local_text_color(dateIcon, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, highlightColor);
  lv_label_set_text_static(dateIcon, Symbols::calendar);
  lv_obj_align(dateIcon, nullptr, LV_ALIGN_CENTER, 0, 0);

  dateValue = lv_label_create(dateRow, nullptr);
  lv_obj_set_style_local_text_color(dateValue, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, backgroundColor);
  lv_obj_set_style_local_text_font(dateValue, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, dataFont);
  lv_label_set_text_static(dateValue, "");
  lv_obj_align(dateValue, nullptr, LV_ALIGN_IN_RIGHT_MID, -rightPadding, 0);

  secondsRow = lv_obj_create(root, nullptr);
  lv_obj_set_size(secondsRow, width, rowHeight);
  lv_obj_set_style_local_radius(secondsRow, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 2);
  lv_obj_set_style_local_bg_color(secondsRow, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, foregroundColor);
  lv_obj_align(secondsRow, dateRow, LV_ALIGN_OUT_BOTTOM_MID, 0, rowSpacing);

  secondsIconContainer = lv_obj_create(secondsRow, nullptr);
  lv_obj_set_size(secondsIconContainer, 32, rowHeight);
  lv_obj_set_style_local_bg_color(secondsIconContainer, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, foregroundColor);
  lv_obj_align(secondsIconContainer, nullptr, LV_ALIGN_IN_LEFT_MID, 0, 0);

  secondsIcon = lv_label_create(secondsIconContainer, nullptr);
  lv_obj_set_style_local_text_color(secondsIcon, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, highlightColor);
  lv_label_set_text_static(secondsIcon, Symbols::stopWatch);
  lv_obj_align(secondsIcon, nullptr, LV_ALIGN_CENTER, 0, 0);

  secondsValue = lv_label_create(secondsRow, nullptr);
  lv_obj_set_style_local_text_color(secondsValue, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, backgroundColor);
  lv_obj_set_style_local_text_font(secondsValue, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, dataFont);
  lv_label_set_text_static(secondsValue, 0);
  lv_obj_align(secondsValue, nullptr, LV_ALIGN_IN_RIGHT_MID, -rightPadding, 0);

  iconsRow = lv_obj_create(root, nullptr);
  lv_obj_set_size(iconsRow, width, rowHeight);
  lv_obj_set_style_local_radius(iconsRow, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 2);
  lv_obj_set_style_local_bg_color(iconsRow, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, foregroundColor);
  lv_obj_align(iconsRow, secondsRow, LV_ALIGN_OUT_BOTTOM_MID, 0, rowSpacing);

  bluetoothIconContainer = lv_obj_create(iconsRow, nullptr);
  lv_obj_set_size(bluetoothIconContainer, 32, rowHeight);
  lv_obj_set_style_local_bg_color(bluetoothIconContainer, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, foregroundColor);
  lv_obj_align(bluetoothIconContainer, nullptr, LV_ALIGN_IN_LEFT_MID, 0, 0);

  bluetoothIcon = lv_label_create(bluetoothIconContainer, nullptr);
  lv_obj_set_style_local_text_color(bluetoothIcon, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, highlightColor);
  lv_label_set_text_static(bluetoothIcon, Symbols::bluetooth);
  lv_obj_align(bluetoothIcon, nullptr, LV_ALIGN_CENTER, 0, 0);
  ShowBluetoothIcon(false);
  
  notificationIcon = lv_label_create(iconsRow, nullptr);
  lv_obj_set_style_local_text_color(notificationIcon, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, highlightColor);
  lv_label_set_text_static(notificationIcon, Symbols::info);
  lv_obj_align(notificationIcon, nullptr, LV_ALIGN_IN_LEFT_MID, leftPadding + 24, 0);
}

void DataPanel::SetForegroundColor(lv_color_t color){
  lv_obj_set_style_local_bg_color(batteryRow, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, color);
  lv_obj_set_style_local_bg_color(batteryIconContainer, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, color);
  lv_obj_set_style_local_bg_color(weatherRow, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, color);
  lv_obj_set_style_local_bg_color(weatherIconContainer, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, color);
  lv_obj_set_style_local_bg_color(stepRow, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, color);
  lv_obj_set_style_local_bg_color(stepIconContainer, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, color);
  lv_obj_set_style_local_bg_color(dateRow, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, color);
  lv_obj_set_style_local_bg_color(dateIconContainer, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, color);
  lv_obj_set_style_local_bg_color(secondsRow, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, color);
  lv_obj_set_style_local_bg_color(secondsIconContainer, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, color);
  lv_obj_set_style_local_bg_color(iconsRow, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, color);
  lv_obj_set_style_local_bg_color(bluetoothIconContainer, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, color);
}

void DataPanel::SetBatteryPercentage(uint8_t percentage) {
  lv_label_set_text_fmt(batteryPercentageValue, "%d%%", percentage);
  lv_obj_realign(batteryPercentageValue);
  batteryIcon.SetBatteryPercentage(percentage);
}

void DataPanel::SetDate(const char* shortDayName, uint8_t dayNumber) {
  lv_label_set_text_fmt(dateValue, "%s %d", shortDayName, dayNumber);
  lv_obj_realign(dateValue);
}

void DataPanel::SetSeconds(uint8_t seconds) {
  lv_label_set_text_fmt(secondsValue, "%02d", seconds);
  lv_obj_realign(secondsValue);
}

void DataPanel::SetSteps(uint32_t steps) {
  lv_label_set_text_fmt(stepValue, "%lu", steps);
  lv_obj_realign(stepValue);
}

void DataPanel::SetTemperature(int16_t degrees) {
  lv_label_set_text_fmt(temperatureValue, "%d°", degrees);
  lv_obj_realign(temperatureValue);
}

void DataPanel::SetWeatherIcon(const char* symbol) {
  lv_label_set_text(weatherIcon, symbol);
  lv_obj_realign(weatherIcon);
}

void DataPanel::ShowBluetoothIcon(bool show) {
  lv_obj_set_hidden(bluetoothIcon, !show);
}

void DataPanel::ShowNotificationIcon(bool show) {
  lv_obj_set_hidden(notificationIcon, !show);
}

void DataPanel::ShowPowerIcon(bool show) {
  lv_obj_set_hidden(powerIcon, !show);
}

lv_obj_t* DataPanel::GetObject() {
  return root;
}