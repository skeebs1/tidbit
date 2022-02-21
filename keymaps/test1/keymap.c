/* Copyright 2020 Jay Greco
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
#include "remote_kb.h"

#define _BASE	0
#define _FUNC	1

enum custom_keycodes {
  PROG = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  //Base layer (numpad)
  [_BASE] = LAYOUT(
				  KC_MPLY,	KC_KP_SLASH,	KC_KP_ASTERISK, \
  KC_P7,	KC_P8,    KC_P9,	      KC_PMNS,	 			\
  KC_P4,	KC_P5,    KC_P6,       	KC_PPLS,				\
  KC_P1,	KC_P2,    KC_P3,	      KC_PENT, 	  		\
  KC_0,	  KC_PDOT,  KC_TAB,	      KC_NO      			\
  ),
  // Function layer (numpad)
  [_FUNC] = LAYOUT(
				      KC_NO,  KC_NO,	KC_NO,
	    KC_NO,	KC_NO,  KC_NO,  KC_NO,
	    KC_NO,	KC_NO,  KC_NO,  KC_NO,
	    KC_NO,	KC_NO,  KC_NO,  KC_NO,
	    KC_NO,  KC_NO,  KC_NO,  KC_NO
  )
}; 

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (clockwise) {
    tap_code(KC_VOLU);
  } else {
    tap_code(KC_VOLD);
  } 
  return true;
}

void matrix_init_user(void) {
  matrix_init_remote_kb();
  register_code(KC_NO);
}

void matrix_scan_user(void) {
  matrix_scan_remote_kb();
}

layer_state_t layer_state_set_user(layer_state_t state) {
	 switch (get_highest_layer(state)) {
	 case _FUNC:
		     	unregister_code(KC_NO);
		     	break;
	    default: //  for any other layers, or the default layer
				register_code(KC_NO);
		        break;
	    }
  return state;
}

void led_set_kb(uint8_t usb_led) {
  if (usb_led & (1<<USB_LED_NUM_LOCK))
		set_bitc_LED(LED_DIM);
  else
	  	set_bitc_LED(LED_OFF);
}