/* Copyright 2025 pioz <https://github.com/pioz>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "custom_actions.h"
#include "pomodoro.h"
#include "toggle_switch.h"

#define T_CAPS LCAG_T(KC_CAPS)
#define MO_FN1 MO(FN1)
#define MO_FN2 MO(FN2)

enum custom_keycodes {
  C_RGB = SAFE_RANGE,
  C_PLYP,
  C_RSTP
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
     * │ ~ │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│Ply│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │PgU│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
     * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │Hom│
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
     * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │ Shift│ ↑ │End│
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬───┼───┼───┤
     * │Ctrl│Alt │Cmd │                            │Fn2│Fn1│ ← │ ↓ │ → │
     * └────┴────┴────┴────────────────────────────┴───┴───┴───┴───┴───┘
     */
    [MAC] = LAYOUT_65_ansi(
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_MPLY,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
      T_CAPS,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_HOME,
      KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,
      KC_LCTL, KC_LALT, KC_LCMD,                            KC_SPC,                             MO_FN2,  MO_FN1,  KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
     * │ ~ │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│Ply│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │PgU│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
     * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │Hom│
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
     * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │ Shift│ ↑ │End│
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬───┼───┼───┤
     * │Ctrl│Win │Alt │                            │Fn2│Fn1│ ← │ ↓ │ → │
     * └────┴────┴────┴────────────────────────────┴───┴───┴───┴───┴───┘
     */
    [WIN] = LAYOUT_65_ansi(
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_MPLY,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
      T_CAPS,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_HOME,
      KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,
      KC_LCTL, KC_LALT, KC_LCMD,                            KC_SPC,                             MO_FN2,  MO_FN1,  KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
     * │Esc│F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│  Del  │Mut│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
     * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │   │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
     * │      │   │Slp│   │   │   │   │   │   │   │   │   │        │   │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
     * │        │   │   │   │   │   │   │   │   │   │PRs│      │VoU│   │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬───┼───┼───┤
     * │    │    │    │        POMODORO PLAY       │   │   │Prv│VoD│Nxt│
     * └────┴────┴────┴────────────────────────────┴───┴───┴───┴───┴───┘
     */
    [FN1] = LAYOUT_65_ansi(
      KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_MUTE,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGDN,
      _______, _______, KC_SLEP, _______, _______, _______, _______, _______, _______, _______, _______, _______,          TG(WIN), _______,
      _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, C_RSTP,  _______, KC_VOLU, _______,
      _______, _______, _______,                            C_PLYP,                             _______, _______, KC_MPRV, KC_VOLD, KC_MNXT
    ),

    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
     * │MTg│MPv│MNx│MVD│MVU│MSD│MSU│MHD│MHU│MSD│MSU│   │   │       │MTg│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
     * │ RTg │RPv│RPv│RNx│RVD│RVU│RSD│RSU│RHD│RHU│RSD│RSU│   │ LRst│   │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
     * │      │   │   │   │   │   │   │   │   │   │   │   │  Boot  │   │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
     * │        │   │   │   │   │   │NKR│   │   │   │   │      │   │   │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬───┼───┼───┤
     * │    │    │    │                            │   │   │   │   │   │
     * └────┴────┴────┴────────────────────────────┴───┴───┴───┴───┴───┘
     */
    [FN2] = LAYOUT_65_ansi(
      RM_TOGG, RM_PREV, RM_NEXT, RM_VALD, RM_VALU, RM_SPDD, RM_SPDU, RM_HUED, RM_HUEU, RM_SATD, RM_SATU, _______, _______, _______, UG_TOGG,
      UG_TOGG, UG_PREV, UG_NEXT, UG_VALD, UG_VALU, UG_SPDD, UG_SPDU, UG_HUED, UG_HUEU, UG_SATD, UG_SATU, _______, _______, C_RGB,   _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          QK_BOOT, _______,
      _______,          _______, _______, _______, _______, _______, NK_TOGG, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______
    ),
};

static inline void tap_code_or_hscroll(uint16_t keycode, bool clockwise) {
  uint8_t mods_state = get_mods() | get_weak_mods() | get_oneshot_mods();
  if (mods_state & MOD_BIT(KC_LCTL)) {
    unregister_code(KC_LCTL);
    report_mouse_t report = {};
    report.h = 5;
    if (!clockwise) report.h *= -1;
    host_mouse_send(&report);
    register_code(KC_LCTL);
  } else {
    tap_code(keycode);
  }
}

// QMK life cicle

static bool init = false;

void keyboard_post_init_user(void) {
  #if defined(CONSOLE_ENABLE)
  debug_enable = true;
  debug_matrix = true;
  debug_keyboard = true;
  debug_mouse = true;
  #endif
  #if defined(TOGGLE_SWITCH)
  switch_init();
  #endif
  #if defined(POMODORO)
  pomodoro_init();
  #endif
  init = true;
}

void matrix_scan_user(void) {
  if (init) {
    #if defined(TOGGLE_SWITCH)
    switch_update();
    #endif
    #if defined(POMODORO)
    pomodoro_update();
    #endif
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case C_RGB:
        rgblight_set_default();
        rgb_matrix_set_default();
        return false;

      #if defined(POMODORO)
      case C_PLYP:
        pomodoro_start();
        return false;

      case C_RSTP:
        pomodoro_reset();
        return false;
      #endif
    }
  }
  return true; // default behaviour
}

// Combo

#if defined(COMBO_ENABLE)
const uint16_t PROGMEM esc_combo[] = {KC_GRV, KC_1, COMBO_END};
combo_t key_combos[] = {
  COMBO(esc_combo, KC_ESC)
};
#endif

// Encoder

#if defined(ENCODER_ENABLE)
bool encoder_update_user(uint8_t index, bool clockwise) {
  if (get_mods() & MOD_BIT(KC_LSFT)) { // L-SHIFT is pressed
    // tap_code16(clockwise ? KC_MS_WH_RIGHT : KC_MS_WH_LEFT);
    report_mouse_t report = {};
    report.h = clockwise ? 3 : -3;
    host_mouse_send(&report);
    return false;
  }

  if (IS_LAYER_ON(FN1)) {
    tap_code(clockwise ? KC_MNXT : KC_MPRV);
    return false;
  }

  if (IS_LAYER_ON(FN2)) {
    tap_code(clockwise ? UG_VALU : UG_VALD);
    return false;
  }

  tap_code(clockwise ? KC_VOLU : KC_VOLD);
  return false;
}

#endif
