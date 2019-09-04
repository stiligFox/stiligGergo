#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;
extern uint8_t         is_master;

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
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_90; }
uint16_t        oled_timer;

char     keylog_str[5]   = {};
uint8_t  keylogs_str_idx = 0;
uint16_t log_timer       = 0;

const char code_to_name[60] = {' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\', '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void oled_task_user(void) {
    /* Show Lock Status (only work on master side) */
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write("Lock:", false);
    oled_write(" ", false);
    oled_write_ln("NUM", led_usb_state & (1 << USB_LED_NUM_LOCK));
    oled_write(" ", false);
    oled_write("CAPS", led_usb_state & (1 << USB_LED_CAPS_LOCK));
    
    /* Show Mod  */
    uint8_t modifiers = get_mods() | get_oneshot_mods();
    oled_write("Mods:", false);
    oled_write(" ", false);
    oled_write_ln("SFT", (modifiers & MOD_MASK_SHIFT));
    oled_write(" ", false);
    oled_write_ln("CTL", (modifiers & MOD_MASK_CTRL));
    oled_write(" ", false);
    oled_write_ln("ALT", (modifiers & MOD_MASK_ALT));
    oled_write(" ", false);
    oled_write_ln("GUI", (modifiers & MOD_MASK_GUI));
    
    /* Active layer */
    
    oled_write("Layer", false);
    oled_write("NumRw", IS_LAYER_ON(_NUM));
    oled_write("Utlty", IS_LAYER_ON(_UTIL));
    oled_write("NumPd", IS_LAYER_ON(_PAD));
    oled_write("Game1", IS_LAYER_ON(_GAME));
    oled_write("Game2", IS_LAYER_ON(_GAME2));
}

#endif
