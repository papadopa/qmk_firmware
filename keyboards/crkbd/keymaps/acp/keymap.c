#include QMK_KEYBOARD_H

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  TRIPLE_TAP = 5,
  TRIPLE_HOLD = 6
};

// Tap dance enums.
enum {
  LT1_LGUI = 0
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_split_3x6_3(KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_LCTL, OSL(1), LALT_T(KC_SPC), KC_ENT, OSL(2), RALT_T(KC_BSPC)),
	[1] = LAYOUT_split_3x6_3(KC_TRNS, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_TRNS, KC_TRNS, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(3), KC_TRNS),
	[2] = LAYOUT_split_3x6_3(KC_TRNS, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_PLUS, KC_PIPE, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LPRN, KC_RPRN, KC_MINS, KC_LCBR, KC_RCBR, KC_GRV, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LBRC, KC_RBRC, KC_EQL, KC_NO, KC_BSLS, KC_TRNS, KC_TRNS, MO(3), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[3] = LAYOUT_split_3x6_3(QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, KC_NO, KC_NO, KC_TRNS, KC_TRNS, RGB_HUI, RGB_SAI, RGB_VAI, RGB_TOG, KC_VOLD, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_NO, KC_TRNS, KC_TRNS, RGB_HUD, RGB_SAD, RGB_VAD, RGB_MOD, KC_MUTE, LSFT(LCTL(LGUI(KC_F5))), LGUI(KC_F5), LGUI(KC_L), KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LCA(KC_DOT))
};





bool process_record_user(uint16_t keycode, keyrecord_t *record) {
   switch (keycode) {
      case LALT_T(OSM(MOD_RALT)):
	 if (record->tap.count && record->event.pressed) {
	    set_oneshot_mods(MOD_BIT(KC_RALT));
	    return false;        // Return false to ignore further processing of key
	 }
	 break;
      case KC_A:
      case KC_U:
      case KC_I:
      case KC_O:
      case KC_QUOT:
	 /*
	  * Replace default AltGr + A -> Á -> À
	  *                         U -> Ú -> Ù
	  *                         I -> Í -> È
	  *                         O -> Ó -> Ô 
	  * For AltGr + ' => `
	  */
	 if (record->event.pressed) {
	    if (get_mods() & MOD_BIT(KC_RALT)) {
	       uint8_t _kc_new = (keycode == KC_I) ? KC_E : keycode;
	       uint8_t _kc_accent = (keycode == KC_O) ? KC_CIRC : KC_GRV;
	       uint8_t _mods_tmp = get_mods();
	       if (_mods_tmp & MOD_MASK_SHIFT) {
		  set_mods(_mods_tmp & MOD_BIT(KC_RALT));  // only AltGr
		  tap_code(_kc_accent);
		  clear_mods(); // AltGr + Shift
		  set_mods(_mods_tmp & MOD_MASK_SHIFT); // only LSFT|RSFT
	       } else {
		  tap_code(_kc_accent);
		  clear_mods(); // AltGr
	       }
	       if (keycode != KC_QUOT) {
		  tap_code(_kc_new); // -> à/ù/è
	       }
	       set_mods(_mods_tmp); // restore mods for next keypress
	       return false;
	    }
	    // if no RALT -> process normally (-> return true)
	 }
	 break;
   }
   return true;
}

// qk_tap_dance_action_t tap_dance_actions[] = {
//   [LT1_LGUI]     = ACTION_TAP_DANCE_DOUBLE(OSM(MOD_LGUI), MO(1))
// };

