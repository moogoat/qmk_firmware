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
    KC_2ZER = SAFE_RANGE, // 00
    KC_TWPM, // toggle WPM module
};

// Tap Dance defintions
enum tap_dance_keycodes {
    TD_DEV, // twice for dev.
    TDAR, // ->, =>
    TDNL, // twice for numpad lock
};

// Custom keycode definitions
#define KC_SHEN MT(MOD_RSFT, KC_ENT)
#define KC_LS LT(_LS, KC_SPACE)
#define KC_FLAY LT(_FL, KC_F)
#define KC_JLAY LT(_JL, KC_J)
#define KC_CAD C(A(KC_DEL))
#define KC_MIPL LT(_LS, KC_MINS)

// Custom colours
#define HSV_DEFAULT_V 168
#define HSV_QW 128, 255, HSV_DEFAULT_V
#define HSV_FN 28, 255, 255
#define HSV_NP 85, 255, HSV_DEFAULT_V

// Sleep module
static uint32_t sleep_timer;
static bool asleep;

void reset_sleep_status(void) {
    if(asleep) {
        rgblight_enable();
        asleep = false;
    }
    sleep_timer = timer_read32();
}

// Wpm module
#define SLEEP_TIMEOUT 60000
#define WPM_CHECK_INTERVAL 1000
#define WPM_MIN 60
#define WPM_MAX 120
#define WPM_EFFECT RGBLIGHT_MODE_KNIGHT
static uint32_t wpm_check_timer;
static bool wpm_active;

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
 * | LCTRL  | LGUI   | HYPER  | LALT   | LSPACE          | LEFT   | DOWN   | RIGHT  | SPACE           | -/MIPL | FN             | NUMPAD  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_QW] = LAYOUT_ortho_5x15(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_VOLU, KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LCBR, KC_VOLD, KC_RCBR, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_FLAY, KC_G,    KC_LPRN, KC_MUTE, KC_RPRN, KC_H,    KC_JLAY, KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC, KC_UP,   KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_SHEN,
    KC_LCTL, KC_LGUI, KC_HYPR, KC_LALT, KC_LS,   XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_SPC,  XXXXXXX, KC_MIPL, TT(_FN), XXXXXXX, TD(TDNL)
  ),

/* LSPACE
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        | =      | +      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        | Del    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |        | <      | {      | (      | [      |        |        |        | ]      | )      | }      | >      |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        | Arrow  |        |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |                 |        |        |        |                 |        |                 |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_LS] = LAYOUT_ortho_5x15(
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, KC_EQL,  KC_PLUS,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, KC_DEL,
    _______, _______, KC_LABK, KC_LCBR, KC_LPRN, KC_LBRC, _______, _______, _______,  KC_RBRC, KC_RPRN, KC_RCBR, KC_RABK, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, TD(TDAR), _______, _______,
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
 * |        |        | WPMTog |        |        |        | F7     | F8     | F9     | -      |        |        |        |        | C+A+D  |
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
    XXXXXXX, XXXXXXX, KC_TWPM, XXXXXXX, XXXXXXX, XXXXXXX, KC_F6,   KC_F7,   KC_F8,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_CAD,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F4,   KC_F5,   KC_F6,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F1,   KC_F2,   KC_F3,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TT(_FN), XXXXXXX, XXXXXXX, XXXXXXX
  )
};

// Tap dance functions
void td_reset(qk_tap_dance_state_t  *state, void *user_data) {
    if (state->count >= 2)
        reset_keyboard();
}

void td_arrow(qk_tap_dance_state_t  *state, void *user_data) {
    if (state->count == 1)
        SEND_STRING("->");
    else if (state->count == 2)
        SEND_STRING("=>");
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_DEV] = ACTION_TAP_DANCE_FN(td_reset),
    [TDAR] = ACTION_TAP_DANCE_FN(td_arrow),
    [TDNL] = ACTION_TAP_DANCE_LAYER_TOGGLE(XXXXXXX, _NP)
};

// Keyboard overrides
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_TWPM:
        if (record->event.pressed) {
            if(wpm_active) {
                wpm_active = false;
                rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            } else {
                wpm_active = true;
            }
        }
        break;
    case KC_2ZER:
        if (record->event.pressed) {
            SEND_STRING("00");
        }
        break;
    default:
        reset_sleep_status();
        break;
  }
  return true;
}

void matrix_init_user(void) {
    sleep_timer = timer_read32();
    wpm_check_timer = sleep_timer;
    asleep = false;
    wpm_active = true;
}

void matrix_scan_user(void) {
    if(!asleep) {
        if(timer_elapsed32(sleep_timer) > SLEEP_TIMEOUT) {
            rgblight_disable();
            asleep = true;
        }
        if(wpm_active && timer_elapsed32(wpm_check_timer) > WPM_CHECK_INTERVAL) {
            uint8_t wpm = get_current_wpm();
            if(wpm > WPM_MIN) {
                if(wpm < WPM_MAX) {
                    if(rgblight_get_mode() != RGBLIGHT_MODE_STATIC_LIGHT)
                        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
                    uint8_t brightness = HSV_DEFAULT_V+(((255-HSV_DEFAULT_V)*(wpm-WPM_MIN))/(WPM_MAX-WPM_MIN));
                    rgblight_sethsv_noeeprom(rgblight_get_hue(), rgblight_get_sat(), brightness);
                } else {
                    if(rgblight_get_mode() != WPM_EFFECT) {
                        rgblight_mode_noeeprom(WPM_EFFECT);
                        rgblight_sethsv_noeeprom(rgblight_get_hue(), rgblight_get_sat(), 255);
                    }
                }
            }
            wpm_check_timer = timer_read32();
        }
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _QW:
            rgblight_sethsv(HSV_QW);
            break;
        case _FN:
            rgblight_sethsv(HSV_FN);
            break;
        case _NP:
            rgblight_sethsv(HSV_NP);
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
        case KC_MIPL:
            return 125;
        default:
            return TAPPING_TERM;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LS:
        case KC_SHEN:
            return true;
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
