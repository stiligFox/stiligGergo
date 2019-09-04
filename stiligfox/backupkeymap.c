#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _NUM 1
#define _UTIL 2
#define _PAD 3
#define _GAME 4
#define _GAME2 5

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_gergo(KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_NO, KC_UP, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_ENT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_NO, KC_LCTL, KC_RCTL, KC_DOWN, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, TT(3), KC_LGUI, LT(1,KC_SPC), KC_LALT, KC_RALT, LT(3,KC_SPC), KC_RGUI, TT(2)),
	[1] = LAYOUT_gergo(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_RGHT, KC_MINS, KC_BSLS, KC_LBRC, KC_RBRC, KC_QUOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_LEFT, KC_EQL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[2] = LAYOUT_gergo(KC_NO, KC_NO, KC_UP, KC_NO, KC_NO, KC_NO, KC_INS, KC_HOME, KC_PGUP, KC_MFFD, KC__VOLUP, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO, KC_NO, KC_PWR, KC_DEL, KC_END, KC_PGDN, KC_MPLY, KC__MUTE, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, TG(4), KC_NO, KC_NO, KC_NO, KC_MRWD, KC__VOLDOWN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[3] = LAYOUT_gergo(KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_PSLS, KC_P7, KC_P8, KC_P9, KC_PMNS, KC_TRNS, KC_CAPS, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_NO, KC_NLCK, KC_PAST, KC_P4, KC_P5, KC_P6, KC_PPLS, KC_TRNS, KC_TRNS, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_PEQL, KC_P1, KC_P2, KC_P3, KC_PENT, KC_TAB, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LT(1,KC_P0), LT(2,KC_PDOT)),
	[4] = LAYOUT_gergo(KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_NO, KC_NO, KC_NO, KC_NO, KC_UP, KC_NO, KC_NO, KC_NO, KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_V, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO, KC_LALT, MO(5), KC_SPC, KC_LGUI, KC_TRNS, KC_TRNS, MO(1), MO(2)),
	[5] = LAYOUT_gergo(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_CAPS, KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180;
}

void oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _NUM:
            oled_write_P(PSTR("Numrow\n"), false);
            break;
        case _UTIL:
            oled_write_P(PSTR("Utility\n"), false);
            break;
        case _PAD:
            oled_write_P(PSTR("Numpad\n"), false);
            break;
        case _GAME:
            oled_write_P(PSTR("Game\n"), false);
            break;
        case _GAME2:
            oled_write_P(PSTR("Game 2\n"), false);
            break;
    }
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(led_usb_state & (1<<USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(led_usb_state & (1<<USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(led_usb_state & (1<<USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}
#endif
