/* Copyright 2017 Wunder
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
#define XD75_KEYCAPS_LED 5  // F5

// Layer shorthand
enum custom_layers {
    _QW = 0,
    _LS,
    _JL,
    _FL,
    _NP,
    _FN,
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QMKBEST = SAFE_RANGE,
  QMKURL,
  KC_2ZER,
};

// Tap Dance defintions
enum tap_dance_keycodes {
    TD_DEV,
};

// Custom keycode definitions
#define KC_SHEN MT(MOD_RSFT, KC_ENT)
#define KC_LS LT(_LS, KC_SPACE)
#define KC_FLAY LT(_FL, KC_F)
#define KC_JLAY LT(_JL, KC_J)
#define KC_CAD C(A(KC_DEL))

// Other things
// static uint16_t sleep_timer;
// static uint16_t wpm_timer;

/* BLANK
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |                 |        |        |        |                 |        |                 |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
/*
[_BLANK] = LAYOUT_ortho_5x15(
  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______
),

[_BLANK] = LAYOUT_ortho_5x15(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______
),
*/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | `      | 1      | 2      | 3      | 4      | 5      | 6      | Volup  | 5      | 6      | 7      | 8      | 9      | 0      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      | {      | Voldn  | }      | Y      | U      | I      | O      | P      | \      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | ESC    | A      | S      | D      | F/FL   | G      | (      | Mute   | )      | H      | J      | K      | L      | ;      | '      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | [      | UP     | ]      | N      | M      | ,      | .      | /      | SH/ENT |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | LGUI   | HYPER  | LALT   | LSPACE          | LEFT   | DOWN   | RIGHT  | LSPACE          | -      | FN             | NUMPAD  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_QW] = LAYOUT_ortho_5x15(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_VOLU, KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LCBR, KC_VOLD, KC_RCBR, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_FLAY, KC_G,    KC_LPRN, KC_MUTE, KC_RPRN, KC_H,    KC_JLAY, KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC, KC_UP,   KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_SHEN,
    KC_LCTL, KC_LGUI, KC_HYPR, KC_LALT, KC_LS,   XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_LS,  XXXXXXX, KC_MINS, TT(_FN), XXXXXXX, TG(_NP)
  ),

/* LSPACE
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        | =      | +      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        | Del    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |        | <      | {      | (      | [      |        |        |        | ]      | )      | }      | >      |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |                 |        |        |        |                 |        |                 |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_LS] = LAYOUT_ortho_5x15(
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, KC_EQL,  KC_PLUS,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, KC_DEL,
    _______, _______, KC_LABK, KC_LCBR, KC_LPRN, KC_LBRC, _______, _______, _______,  KC_RBRC, KC_RPRN, KC_RCBR, KC_RABK, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______
  ),

/* JLAYER
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        | Home   | Bksp   | Up     | Del    | End    |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        | C(L)   | Left   | Down   | Right  | C(R)   |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |                 |        |        |        |                 |        |                 |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_JL] = LAYOUT_ortho_5x15(
    XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, KC_HOME,    KC_BSPC, KC_UP,   KC_DEL,  KC_END,     XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, C(KC_LEFT), KC_LEFT, KC_DOWN, KC_RGHT, C(KC_RGHT), XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, _______,    _______, _______, _______, _______,    _______, _______, _______,  _______, _______, _______, _______, _______, _______
  ),

/* FLAYER
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        | Home   |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        |Speed0  | Speed1 | Speed2 |        |        |        |        |        | Pgup   |        | MUp    |        | WheelU |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |        |        |        |        |        |        |        |        | Pgdn   | MLeft  | MDown  | MRight | WheelD |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        |        |        |        |        |        |        | End    |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        | M Right Button  |        |        |        | M Left Button   |        |                 |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_FL] = LAYOUT_ortho_5x15(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_HOME, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, KC_ACL0, KC_ACL1, KC_ACL2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_PGUP, XXXXXXX, KC_MS_U, XXXXXXX, KC_WH_U, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_PGDN, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_END,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, _______, _______, _______, KC_BTN2, XXXXXXX, _______, _______, _______,  KC_BTN1, XXXXXXX, _______, _______, _______, _______
  ),

/* NUMPAD
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        | K-     | NUMLCK | K/     | K*     | K-     |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        |        |        |        |        | K+     | K7     | K8     | K9     | K+     |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |        |        |        |        | PENT   | K4     | K5     | K6     | PENT   |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        |        | PENT   | PENT   | K1     | K2     | K3     | PENT   | PENT   |        |        |        |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        | K0              | K.     | 00     | K.     | K0              |        |                 | NUMPAD |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_NP] = LAYOUT_ortho_5x15(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC, KC_PMNS, KC_NLCK, KC_PSLS, KC_PAST,  KC_PMNS, KC_BSPC, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,  KC_PPLS, KC_P7,   KC_P8,   KC_P9,    KC_PPLS, KC_DEL,  XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_ESC,  KC_PENT, KC_P4,   KC_P5,   KC_P6,    KC_PENT, KC_ESC,  XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_PENT, KC_PENT, KC_P1,   KC_P2,   KC_P3,    KC_PENT, KC_PENT, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, _______, _______, _______, KC_P0,   XXXXXXX, KC_PDOT, KC_2ZER, KC_PDOT,  KC_P0,   XXXXXXX, _______, _______, _______, TG(_NP)
  ),

/* FUNCTION
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        | F10    | F11    | F12    |        |        |        |        |        | TD_DEV |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        | F7     | F8     | F9     | -      |        |        |        |        | C+A+D  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        | F4     | F5     | F6     | +      |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        | F1     | F2     | F3     |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        | FN     |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_FN] = LAYOUT_ortho_5x15(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F10,  KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TD(TD_DEV),
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F6,   KC_F7,   KC_F8,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_CAD,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F4,   KC_F5,   KC_F6,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F1,   KC_F2,   KC_F3,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TT(_FN), XXXXXXX, XXXXXXX, XXXXXXX
  )
};

void td_reset(qk_tap_dance_state_t  *state, void *user_data) {
    if (state->count >= 2) {
        reset_keyboard();
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_DEV] = ACTION_TAP_DANCE_FN(td_reset),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QMKBEST:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("QMK is the best thing ever!");
      } else {
        // when keycode QMKBEST is released
      }
      break;
    case QMKURL:
      if (record->event.pressed) {
        // when keycode QMKURL is pressed
        SEND_STRING("https://qmk.fm/" SS_TAP(X_ENTER));
      } else {
        // when keycode QMKURL is released
      }
      break;
    case KC_2ZER:
      if (record->event.pressed) {
          SEND_STRING("00");
      }
      break;
  }
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _QW:
            rgblight_sethsv(HSV_CYAN);
            rgblight_mode(RGBLIGHT_MODE_RAINBOW_MOOD);
            eeprom_update_byte(EECONFIG_VELOCIKEY, 1);
            break;
        case _FN:
            rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
            eeprom_update_byte(EECONFIG_VELOCIKEY, 0);
            rgblight_sethsv(HSV_RED);
            break;
        case _NP:
            rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
            eeprom_update_byte(EECONFIG_VELOCIKEY, 0);
            rgblight_sethsv(HSV_GREEN);
            break;
    }
    return state;
}

void led_set_user(uint8_t usb_led) {
    //rgblight_set_layer_state(0, led_state.caps_lock);
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LS:
            return 100;
        default:
            return TAPPING_TERM;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default: return false;
    }
}

bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode ) {
        case KC_SHEN:
            return true;
        default: return false;
    }
}
