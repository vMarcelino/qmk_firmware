#include "vMarcelino.h"
#include <stdbool.h>
#include "action.h"
#include "k8_pro.h"
#include "keycodes.h"

bool      ctrl_pressed = false;
const int CTRL_KEY     = KC_LCTL;
int       ctrl_key     = CTRL_KEY;

bool      opt_pressed = false;
const int OPT_KEY     = KC_LOPT;
int       opt_key     = OPT_KEY;

bool vMarcelino_process_record_kb_bt(uint16_t keycode, keyrecord_t *record) {
    // Map CTRL to CMD
    switch (keycode) {
        case KC_LCTL: {
            if (record->event.pressed) {
                register_code(ctrl_key);
                ctrl_pressed = true;
            } else {
                unregister_code(ctrl_key);
                ctrl_pressed = false;
                ctrl_key     = CTRL_KEY;
            }
            return false;
        }
        case KC_LOPTN: {
            if (record->event.pressed) {
                register_code(opt_key);
                opt_pressed = true;
            } else {
                unregister_code(opt_key);
                opt_pressed = false;
                opt_key     = OPT_KEY;
            }
            return false;
        }

        case KC_B:
        case KC_T:
        case KC_N:
        case KC_P:
        case KC_D:
        case KC_S:
        case KC_Y:
        case KC_Z:
        case KC_A:
        case KC_F:
        case KC_X:
        case KC_V:
        case KC_W:
        case KC_C: {
            if (ctrl_pressed && !opt_pressed) {
                const int REPLACEMENT = KC_LCMD;
                if (record->event.pressed) {
                    if (ctrl_key == CTRL_KEY) {
                        unregister_code(CTRL_KEY);
                        register_code(REPLACEMENT);
                        ctrl_key = REPLACEMENT;
                    }
                    register_code(keycode);
                    return false;
                } else {
                    unregister_code(keycode);
                    if (ctrl_key == REPLACEMENT) {
                        unregister_code(REPLACEMENT);
                        register_code(CTRL_KEY);
                        ctrl_key = CTRL_KEY;
                    }
                    return false;
                }
            }

            if (!ctrl_pressed && opt_pressed) {
                const int REPLACEMENT = KC_LCTL;
                if (record->event.pressed) {
                    if (opt_key == OPT_KEY) {
                        unregister_code(OPT_KEY);
                        register_code(REPLACEMENT);
                        opt_key = REPLACEMENT;
                    }
                    register_code(keycode);
                    return false;
                } else {
                    unregister_code(keycode);
                    if (opt_key == REPLACEMENT) {
                        unregister_code(REPLACEMENT);
                        register_code(OPT_KEY);
                        opt_key = OPT_KEY;
                    }
                    return false;
                }
            }
        }

        case KC_LEFT:
        case KC_RIGHT: {
            if (ctrl_pressed && !opt_pressed) {
                if (record->event.pressed) {
                    if (ctrl_key == CTRL_KEY) {
                        unregister_code(CTRL_KEY);
                        register_code(KC_LOPT);
                        ctrl_key = KC_LOPT;
                    }
                    register_code(keycode);
                    return false;
                } else {
                    unregister_code(keycode);
                    if (ctrl_key == KC_LOPT) {
                        unregister_code(KC_LOPT);
                        register_code(CTRL_KEY);
                        ctrl_key = CTRL_KEY;
                    }
                    return false;
                }
            }
        }
    }

    return true;
}
