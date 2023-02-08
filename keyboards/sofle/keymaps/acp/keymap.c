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
	[0] = LAYOUT(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_GRV, KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_MUTE, KC_MPLY, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_LGUI, KC_LALT, KC_LCTL, OSL(1), LALT_T(KC_SPC), KC_ENT, OSL(2), RCTL_T(KC_BSPC), KC_RALT, KC_RGUI),
	[1] = LAYOUT(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_GRV, KC_TRNS, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_TRNS, KC_TRNS, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(3), KC_TRNS, KC_TRNS, KC_TRNS),
	[2] = LAYOUT(KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_TRNS, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_PLUS, KC_PIPE, KC_F12, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LPRN, KC_RPRN, KC_MINS, KC_LCBR, KC_RCBR, KC_GRV, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_EQL, KC_NO, KC_BSLS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(3), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[3] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, KC_NO, KC_NO, KC_TRNS, KC_TRNS, RGB_HUI, RGB_SAI, RGB_VAI, RGB_TOG, KC_VOLD, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_NO, KC_TRNS, KC_TRNS, RGB_HUD, RGB_SAD, RGB_VAD, RGB_MOD, KC_MUTE, KC_TRNS, KC_TRNS, LSFT(LCTL(LGUI(KC_F5))), LGUI(KC_F5), LGUI(KC_L), KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LCA(KC_DOT), KC_TRNS, KC_TRNS)
};

#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
    };

    oled_write_P(qmk_logo, false);
}

static void print_status_narrow(void) {
    // Print current mode
    oled_write_P(PSTR("\n\n"), false);
    oled_write_ln_P(PSTR("MODE"), false);
    oled_write_ln_P(PSTR(""), false);
    if (keymap_config.swap_lctl_lgui) {
        oled_write_ln_P(PSTR("MAC"), false);
    } else {
        oled_write_ln_P(PSTR("WIN"), false);
    }

    oled_write_P(PSTR("\n\n"), false);
    oled_write_P(PSTR("\n\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
    return false;
}

#endif

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_WH_D);
        } else {
            tap_code(KC_WH_U);
        }
    }
    return true;
}

#endif

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
      case KC_QUOT:
	 /*
	  * Replace default AltGr + A -> Á -> À
	  *                         U -> Ú -> Ù
	  *                         I -> Í -> È
	  * For AltGr + ' => `
	  */
	 if (record->event.pressed) {
	    if (get_mods() & MOD_BIT(KC_RALT)) {
	       uint8_t _kc_new = (keycode == KC_I) ? KC_E : keycode;
	       uint8_t _mods_tmp = get_mods();
	       if (_mods_tmp & MOD_MASK_SHIFT) {
		  set_mods(_mods_tmp & MOD_BIT(KC_RALT));  // only AltGr
		  tap_code(KC_GRV);
		  clear_mods(); // AltGr + Shift
		  set_mods(_mods_tmp & MOD_MASK_SHIFT); // only LSFT|RSFT
	       } else {
		  tap_code(KC_GRV);
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

