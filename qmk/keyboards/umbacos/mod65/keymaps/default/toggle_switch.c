#if defined(TOGGLE_SWITCH)
#include "toggle_switch.h"

#define TOGGLE_SWITCH_PIN GP23
#define SWITCH_MODE_LIGHT
// #define SWITCH_MODE_LAYER

static bool prev_state;

void switch_init(void) {
  setPinInput(TOGGLE_SWITCH_PIN);
  #if defined(SWITCH_MODE_LIGHT)
  prev_state = readPin(TOGGLE_SWITCH_PIN);
  if (prev_state) {
    rgblight_enable();
    rgb_matrix_enable();
  } else {
    rgblight_disable();
    rgb_matrix_disable();
  }
  #endif
}


void switch_update(void) {
  bool pin_state = readPin(TOGGLE_SWITCH_PIN); // true = HIGH, false = LOW

  #if defined(SWITCH_MODE_LIGHT)
  if (pin_state != prev_state) {
    if (pin_state) {
      rgblight_enable();
      rgb_matrix_enable();
    } else {
      rgblight_disable();
      rgb_matrix_disable();
    }
    prev_state = pin_state;
  }
  #endif

  #if defined(SWITCH_MODE_LAYER)
  if (pin_state) {
    set_single_persistent_default_layer(WIN);
  } else {
    set_single_persistent_default_layer(MAC);
  }
  #endif
}

#endif
