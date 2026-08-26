/*
 * LCD_CFG.h
 *
 *  Created on: Aug 20, 2026
 *      Author: alata
 */


#ifndef INCLUDE_HAL_LCD_LCD_CFG_H_
#define INCLUDE_HAL_LCD_LCD_CFG_H_

#define LCD_DATA_PORT 			PORTD
#define LCD_CONTROL_PORT    	PORTC

#define LCD_RS_PIN 	        	PIN0
#define LCD_RW_PIN 				PIN1
#define LCD_E_PIN  				PIN7

#define LCD_NO_OF_LINES 		1
// 0 --> 8 BIT MODE
// 1 --> 4 BIT MODE
#define LCD_DL 1  /* تم التعديل هنا ليعمل بنظام 4-Bit */

#define LCD_CHAR_FONT		 	0
#define DISPLAY_ON 				1
#define CURSOR_DISPLAY 			1
#define CURSOR_BLINK 			1
#define LCD_DATA_DIRECTION 		1
#define LCD_SHIFT 				0

#endif /* INCLUDE_HAL_LCD_LCD_CFG_H_ */
