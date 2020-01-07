/* Copyright 2015-2017 Jack Humbert
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
#include "muse.h"
#include "typo_funcs.c"

enum preonic_layers {
  _QWERTY = 0,
  _COLEMAK,
  _DVORAK,
  _ARROWS,
  _RAISE,
  _ADJUST,
  _NUMPAD,
  _MACRO1,
  _MACRO2,
  _MACRO3
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  NUMPAD,
  RAISE
};

#define TD_START_KEYCODE 0x5700 // this is from the source code, quantum_keycodes.h
#define MACRO_START 1
enum preonic_tapdance {
    TD_NUMPAD_LOCK = 0
};

#include "macros.c"

// Songs
float numpad_on[][2] = SONG(NUM_LOCK_ON_SOUND);
float numpad_off[][2] = SONG(NUM_LOCK_OFF_SOUND);

// Helpers

// Random
static unsigned int g_seed;
void fast_srand(int seed) {
    if(g_seed == 0) g_seed = seed;
}

int fastrand(void) {
    g_seed = (214013*g_seed+2531011);
    return (g_seed>>16)&0x7FFF;
}

/* Blank
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

/*[_BLANK] = LAYOUT_preonic_grid( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
) */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | \    |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  | J/LOw|   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Sh/Ent|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CTRL | GUI  |Numpad| ALT  |Numpad|    Space    |Raise |   -  |MACRO1|MACRO2|MACRO3|
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,  \
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    LT(_ARROWS, KC_J),    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MT(MOD_RSFT, KC_ENT),  \
  KC_LCTL, KC_LGUI, TD(TD_NUMPAD_LOCK), KC_LALT, NUMPAD,   KC_SPC,  KC_SPC,  RAISE, KC_MINS, MO(_MACRO1), MO(_MACRO2), MO(_MACRO3)  \
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | \    |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |N/LOW |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Sh/Ent|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CTRL | GUI  |Numpad| ALT  |Numpad|    Space    |Raise |   -  |MACRO1|MACRO2|MACRO3|
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_preonic_grid( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSLS,  \
  KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    LT(_ARROWS, KC_N),    KC_E,    KC_I,    KC_O,    KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MT(MOD_RSFT, KC_ENT),  \
  KC_LCTL, KC_LGUI, TD(TD_NUMPAD_LOCK), KC_LALT, NUMPAD,   KC_SPC,  KC_SPC,  RAISE, KC_MINS, MO(_MACRO1), MO(_MACRO2), MO(_MACRO3)  \
),

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | \    |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  | H/Low|   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Sh/Ent|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CTRL | GUI  |Numpad| ALT  |Numpad|    Space    |Raise |   -  |MACRO1|MACRO2|MACRO3|
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = LAYOUT_preonic_grid( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSLS,  \
  KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    LT(_ARROWS, KC_H),    KC_T,    KC_N,    KC_S,    KC_SLSH, \
  KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    MT(MOD_RSFT, KC_ENT),  \
  KC_LCTL, KC_LGUI, TD(TD_NUMPAD_LOCK), KC_LALT, NUMPAD,   KC_SPC,  KC_SPC,  RAISE, KC_MINS, MO(_MACRO1), MO(_MACRO2), MO(_MACRO3)  \
),

/* Arrows
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Home | Bksp |  Up  |  Del |  End |      |      |      |      |      |      |   Del|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | C(L) | Left | Down |Right |  C(R)|      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Shift |      |      |      |      |      |      |      |      |      |      |Sh/Ent|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CTRL |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_ARROWS] = LAYOUT_preonic_grid( \
  _______, _______, _______,   _______, _______,  _______, _______, _______, _______, _______, _______, _______, \
  _______, KC_HOME, KC_BSPC, KC_UP, KC_DEL, KC_END, _______, _______, _______, _______, _______, KC_DEL,  \
  _______, C(KC_LEFT), KC_LEFT, KC_DOWN, KC_RIGHT, C(KC_RIGHT), _______, _______, _______, _______, _______, _______, \
  KC_LSFT, _______, _______,   _______, _______,  _______, _______, _______, _______, _______, _______, MT(MOD_RSFT, KC_ENT), \
  KC_LCTL, _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |  F1  |  f2  |  f3  | f4   | f5   |  f6  | f7   | f8   |  =   |   +  |  BKSP|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  f9  |  f10 |  f11 |  f12 |      |      |      |      |      |      |   Del|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |  <   |   {  |  (   |   [  |   ]  |  )   |   }  |  >   |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Shift |      |      |      |      |      |      |      |      |      | Mute |Sh/Ent|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid( \
  _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, _______, KC_EQL, S(KC_EQL), \
  _______, KC_F9, KC_F10, KC_F11, KC_F12, _______, _______, _______, _______, _______, _______, KC_DEL,  \
  _______, _______, S(KC_COMM), S(KC_LBRC), S(KC_9), KC_LBRC, KC_RBRC, S(KC_0), S(KC_RBRC), S(KC_DOT), _______, _______, \
  KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MUTE, MT(MOD_RSFT, KC_ENT), \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY  \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Qwerty|      |      |      |      |      |      |      |      |      |C+A+D |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | RESET|AU TOG|      |DVORAK|      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |C+S+Es|      |      |COLMAK|      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  _______, QWERTY, _______,   _______, _______, _______, _______, _______, _______,_______, _______, C(A(KC_DEL)),  \
  RESET, AU_TOG, _______,  DVORAK,   _______,  _______, _______, _______,  _______, _______,  _______, _______, \
  C(S(KC_ESC)), _______,  _______,  COLEMAK,   _______,  _______,   _______,  _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),
/* Numpad
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      | CALC | NUM_/| NUM_*|Backsp|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  NUM7|NUM8  | NUM9 | NUM_-|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  NUM4| NUM5 | NUM6 | NUM_+|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | NUM1 | NUM2 | NUM3 |NUMENT|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |NUMPAD|      |      |    Space    |      | NUM0 | NUM_0| NUM_.|NUMENT|
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_preonic_grid( \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_CALC, KC_PSLS, KC_PAST, KC_BSPC, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_P7, KC_P8, KC_P9, KC_PMNS,  \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_P4, KC_P5, KC_P6, KC_PPLS, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_P1, KC_P2, KC_P3, KC_PENT, \
  _______, _______, TD(TD_NUMPAD_LOCK), _______, _______, KC_SPC,  KC_SPC, _______, KC_KP_0, KC_KP_0, KC_PDOT, KC_PENT  \
),

/*  Macro 1 - History Macros
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MACRO1] = LAYOUT_preonic_grid( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  \
),

/* Macro 2 - Physical macros, normal
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |well  |      |      |throat|      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |noLymp|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_MACRO2] = LAYOUT_preonic_grid( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, TD(m_wellNAD), XXXXXXX, XXXXXXX, TD(m_nThroat), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TD(m_noLymph), XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  \
),

/* Macro 3 - Misc macros/Abn physical macros
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |throat|      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |lymph |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_MACRO3] = LAYOUT_preonic_grid( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TD(m_abnThroat), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TD(m_lymph), XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  \
)

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
        case COLEMAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_COLEMAK);
          }
          return false;
          break;
        case DVORAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_DVORAK);
          }
          return false;
          break;
        case NUMPAD:
          if (record->event.pressed) {
            layer_on(_NUMPAD);
            update_tri_layer(_NUMPAD, _RAISE, _ADJUST);
          } else {
            layer_off(_NUMPAD);
            update_tri_layer(_NUMPAD, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_NUMPAD, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_NUMPAD, _RAISE, _ADJUST);
          }
          return false;
          break;
      }
    return true;
};

#ifdef AUDIO_ENABLE
bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;
#endif

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

// void test_td(qk_tap_dance_state_t *state, void *user_data) {
//     char buf[256];
//     sprintf(buf, "count: %d, keycode: %d", state->count, state->keycode);
//     SEND_STRING(buf);
//     reset_tap_dance(state);
// }

void toggle_numlock(qk_tap_dance_state_t *state, void *user_data) {
    if(layer_state_is(_NUMPAD)) {
        PLAY_SONG(numpad_off);
        layer_off(_NUMPAD);
    } else {
        if(state->count >= 2) {
            layer_on(_NUMPAD);
            PLAY_SONG(numpad_on);
        }
    }
}

void process_macro(qk_tap_dance_state_t *state, void *user_data) {
    uint8_t count = state->count;
    const char **group = moogoat_getMacro(state->keycode-TD_START_KEYCODE);
    uint8_t len = moogoat_grouplen(group);
    if(count == 1) {
        fast_srand(timer_read());
        SEND_STRING(group[fastrand()%len]);
    } else {
        SEND_STRING(group[(count-2)%len]);
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_NUMPAD_LOCK] = ACTION_TAP_DANCE_FN(toggle_numlock),
    [m_wellNAD] = ACTION_TAP_DANCE_FN(process_macro),
    [m_lymph] = ACTION_TAP_DANCE_FN(process_macro),
    [m_noLymph] = ACTION_TAP_DANCE_FN(process_macro),
    [m_nThroat] = ACTION_TAP_DANCE_FN(process_macro),
    [m_abnThroat] = ACTION_TAP_DANCE_FN(process_macro)
};

/*
For future macros: this might be useful for tap dance. Note that state->keycode may be something to use

void dance_egg (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 100) {
    SEND_STRING ("Safety dance!");
    reset_tap_dance (state);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
 [CT_EGG] = ACTION_TAP_DANCE_FN (dance_egg)
};
*/
