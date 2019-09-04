#include QMK_KEYBOARD_H
#include "drashna.h"

extern keymap_config_t keymap_config;
extern uint8_t         is_master;


enum crkbd_keycodes { RGBRST = NEW_SAFE_RANGE };

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }
uint16_t        oled_timer;

char     keylog_str[5]   = {};
uint8_t  keylogs_str_idx = 0;
uint16_t log_timer       = 0;

const char code_to_name[60] = {' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\', '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void add_keylog(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        keycode = keycode & 0xFF;
    }

    for (uint8_t i = 4; i > 0; i--) {
        keylog_str[i] = keylog_str[i - 1];
    }
    if (keycode < 60) {
        keylog_str[0] = code_to_name[keycode];
    }
    keylog_str[5] = 0;

    log_timer = timer_read();
}

void update_log(void) {
    if (timer_elapsed(log_timer) > 750) {
        add_keylog(0);
    }
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        add_keylog(keycode);
        oled_timer = timer_read();
    }
    return true;
}

void render_status_main(void) {
    /* Show Keyboard Layout  */
    oled_write("Lyout", false);
    switch (biton32(default_layer_state)) {
        case _QWERTY:
            oled_write(" QRTY", false);
            break;
        case _COLEMAK:
            oled_write(" COLE", false);
            break;

    }

    /* Show Lock Status (only work on master side) */
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write("Lock:", false);
    oled_write(" ", false);
    oled_write_ln("NUM", led_usb_state & (1 << USB_LED_NUM_LOCK));
    oled_write(" ", false);
    oled_write("CAPS", led_usb_state & (1 << USB_LED_CAPS_LOCK));
    oled_write(" ", false);
    oled_write("SCRL", led_usb_state & (1 << USB_LED_SCROLL_LOCK));

    /* Show Alt-Gui Swap options */
    oled_write("BTMGK", false);
    oled_write(" ", false);
    oled_write_ln("Win", !keymap_config.swap_lalt_lgui);
    oled_write(" ", false);
    oled_write_ln("Mac", keymap_config.swap_lalt_lgui);

#    if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    /* Show RGB Options */
    render_rgb_status();
#    endif

    oled_write(keylog_str, false);
}

void render_status_secondary(void) {
    /* Show Activated layer */
    oled_write("Layer", false);
    switch (biton32(layer_state)) {
        case _RAISE:
            oled_write("Raise", false);
            break;
        case _LOWER:
            oled_write("Lower", false);
            break;
        case _ADJUST:
            oled_write("Adjst", false);
            break;
        default:
            oled_write("Dflt ", false);
            break;
    }

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


    /* Show logged Keys */
    oled_write(keylog_str, false);
}

void oled_task_user(void) {
    if (timer_elapsed(oled_timer) > 60000) {
        oled_off();
        return;
    }
    if (is_master) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_status_secondary();
    }
}
