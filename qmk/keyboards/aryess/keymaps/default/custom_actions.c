#include "custom_actions.h"

#define RGBLIGHT_DEFAULT_HSV_COLOR      0,   0,  1 // white low brightness
#define RGB_MATRIX_DEFAULT_HSV_COLOR 124, 255, 255 // cyan high brightness

void rgblight_set_default(void) {
  rgblight_set_speed(128);
  rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
  rgblight_sethsv(RGBLIGHT_DEFAULT_HSV_COLOR);
}

void rgb_matrix_set_default(void) {
  rgb_matrix_set_speed(128);
  rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
  rgb_matrix_sethsv(RGB_MATRIX_DEFAULT_HSV_COLOR);
}
