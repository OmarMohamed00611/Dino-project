/*
 * DINO_PROGRAM.c
 *
 *  Created on: Aug 26, 2026
 *      Author: alata
 */

/*
 * main.c
 * Chrome Dino Game using Custom LCD & DIO Drivers (4-Bit Mode)
 */
#define F_CPU 8000000UL
#include "../INCLUDE/LIB/STD_TYPES.h"
#include "../INCLUDE/LIB/BIT_MATH.h"
#include "../INCLUDE/MCAL/DIO/DIO_INTERFACE.h"
#include "../INCLUDE/HAL/LCD/LCD_INTERFACE.h"
#include <util/delay.h>
#include <stdlib.h>

/* ================= Hardware Connections ================= */
#define BUTTON_PORT  PORTA
#define BUTTON_PIN   PIN0
#define BUZZER_PORT  PORTA
#define BUZZER_PIN   PIN1

#define BUTTON_PRESSED DIO_HIGH
#define MIN_OBSTACLE_PERIOD 8   // أقصى سرعة ممكنة للمناقشة (مرحلة الوحش)

/* ================= Custom Characters ================= */
u8 DINO_STAND_PART_1[8]   = {0b00000, 0b00000, 0b00010, 0b00010, 0b00011, 0b00011, 0b00001, 0b00001};
u8 DINO_STAND_PART_2[8]   = {0b00111, 0b00111, 0b00111, 0b00100, 0b11100, 0b11100, 0b11000, 0b01000};
u8 DINO_RIGHT_LEG_PART_1[8] = {0b00000, 0b00000, 0b00010, 0b00010, 0b00011, 0b00011, 0b00001, 0b00001};
u8 DINO_RIGHT_LEG_PART_2[8] = {0b00111, 0b00111, 0b00111, 0b00100, 0b11100, 0b11100, 0b11000, 0b00000};
u8 DINO_LEFT_LEG_PART_1[8]  = {0b00000, 0b00000, 0b00010, 0b00010, 0b00011, 0b00011, 0b00001, 0b00000};
u8 DINO_LEFT_LEG_PART_2[8]  = {0b00111, 0b00111, 0b00111, 0b00100, 0b11100, 0b11100, 0b11000, 0b01000};
u8 CACTUS_PART_1[8]       = {0b00000, 0b00100, 0b00100, 0b10100, 0b10100, 0b11100, 0b00100, 0b00100};
u8 CACTUS_PART_2[8]       = {0b00100, 0b00101, 0b00101, 0b10101, 0b11111, 0b00100, 0b00100, 0b00100};
u8 BIRD_WINGS_PART_1[8]   = {0b00001, 0b00001, 0b00001, 0b00001, 0b01001, 0b11111, 0b00000, 0b00000};
u8 BIRD_WINGS_PART_2[8]   = {0b00000, 0b10000, 0b11000, 0b11100, 0b11110, 0b11111, 0b00000, 0b00000};

/* ================= Simplified Buzzer for Proteus ================= */
void BUZZER_voidPlayTone(u16 duration_ms) {
    MDIO_voidSetPinValue(BUZZER_PORT, BUZZER_PIN, DIO_HIGH);
    for(u16 i = 0; i < duration_ms; i++) {
        _delay_ms(1);
    }
    MDIO_voidSetPinValue(BUZZER_PORT, BUZZER_PIN, DIO_LOW);
}

/* ================= Main Function ================= */
int main(void) {
    MDIO_voidInit();
    MDIO_voidSetPinDirection(BUTTON_PORT, BUTTON_PIN, DIO_INPUT);
    MDIO_voidSetPinDirection(BUZZER_PORT, BUZZER_PIN, DIO_OUTPUT);

    MDIO_voidSetPinDirection(PORTD, PIN4, DIO_OUTPUT);
    MDIO_voidSetPinDirection(PORTD, PIN5, DIO_OUTPUT);
    MDIO_voidSetPinDirection(PORTD, PIN6, DIO_OUTPUT);
    MDIO_voidSetPinDirection(PORTD, PIN7, DIO_OUTPUT);

    MDIO_voidSetPinDirection(PORTC, PIN0, DIO_OUTPUT);
    MDIO_voidSetPinDirection(PORTC, PIN1, DIO_OUTPUT);
    MDIO_voidSetPinDirection(PORTC, PIN7, DIO_OUTPUT);

    LCD_voidInit();

    LCD_voidDrawPattern(0, DINO_STAND_PART_1);
    LCD_voidDrawPattern(1, DINO_STAND_PART_2);
    LCD_voidDrawPattern(2, DINO_RIGHT_LEG_PART_1);
    LCD_voidDrawPattern(3, DINO_RIGHT_LEG_PART_2);
    LCD_voidDrawPattern(4, DINO_LEFT_LEG_PART_1);
    LCD_voidDrawPattern(5, DINO_LEFT_LEG_PART_2);
    LCD_voidDrawPattern(6, CACTUS_PART_1);
    LCD_voidDrawPattern(7, CACTUS_PART_2);

    /* --- Game Variables --- */
    u8 dino_col1 = 1, dino_col2 = 2;
    u32 leg_timer = 0; u16 leg_period = 15; u8 leg_flag = 1;

    u8 obstacle_row = LINE_2; s8 obstacle_col = 15;
    u16 obstacle_period = 14;
    u32 obstacle_timer = 0;
    u8 draw_obstacle_flag = 0;
    u8 random_obstacle = 1;
    s8 bird_col = 15;

    u8 hitbox_col1 = 1, hitbox_col2 = 2, jump_flag = 0;
    u32 score_timer = 0; u16 score_period = 40; u32 score_units = 0, score_hundreds = 0;
    u8 acceleration_step = 2;

    PIN_STATUS prev_button_state = DIO_LOW;
    u32 jump_start_time = 0;
    u16 jump_duration = 100;

    u32 jump_sound_timer = 0; u16 jump_sound_period = 600; u32 current_millis = 0;

    while (1) {
        _delay_ms(1);
        current_millis++;

        // --- Dinosaur Legs Animation ---
        if (current_millis > leg_timer + leg_period) {
            leg_timer = current_millis;
            leg_flag = (leg_flag == 1) ? 2 : 1;
        }

        // --- Obstacles Movement ---
        if (current_millis > obstacle_timer + obstacle_period) {
            obstacle_timer = current_millis;
            obstacle_col--;

            if (obstacle_col < 0) {
                obstacle_col = 15;
                if (obstacle_period > MIN_OBSTACLE_PERIOD) {
                    if (obstacle_period > acceleration_step) {
                        obstacle_period -= acceleration_step;
                    }
                    if(obstacle_period < MIN_OBSTACLE_PERIOD) obstacle_period = MIN_OBSTACLE_PERIOD;
                }
                random_obstacle = rand() % 3;
            }

            s8 temp_col = obstacle_col + 1;
            if (temp_col < 16) {
                LCD_voidGoTo_XY(LINE_2, temp_col); LCD_voidWriteChar(' ');
                LCD_voidGoTo_XY(LINE_1, temp_col); LCD_voidWriteChar(' ');
            }
            LCD_voidGoTo_XY(LINE_2, 0); LCD_voidWriteChar(' ');
            LCD_voidGoTo_XY(LINE_1, 0); LCD_voidWriteChar(' ');
            draw_obstacle_flag = 1;
        }

        // --- Draw Dinosaur (Ground) ---
        if (jump_flag == 0) {
            LCD_voidGoTo_XY(LINE_2, dino_col1); LCD_voidWriteChar(leg_flag == 1 ? 2 : 4);
            LCD_voidGoTo_XY(LINE_2, dino_col2); LCD_voidWriteChar(leg_flag == 1 ? 3 : 5);
        }

        // --- Draw Obstacles ---
        if (draw_obstacle_flag == 1) {
            if (random_obstacle == 1 || random_obstacle == 2) {
                obstacle_row = LINE_2;
                LCD_voidGoTo_XY(obstacle_row, obstacle_col);
                LCD_voidWriteChar(random_obstacle == 1 ? 6 : 7);
            } else {
                bird_col = obstacle_col - 1;
                obstacle_row = LINE_1;
                if(bird_col >= 0) { LCD_voidGoTo_XY(obstacle_row, bird_col); LCD_voidWriteChar(6); }
                LCD_voidGoTo_XY(obstacle_row, obstacle_col); LCD_voidWriteChar(7);
            }
            draw_obstacle_flag = 0;
        }

        // --- Read Button ---
        PIN_STATUS button_state = MDIO_PinstatusGetPinValue(BUTTON_PORT, BUTTON_PIN);

        // --- Jump Logic (Balanced Timer) ---
        if (button_state == BUTTON_PRESSED && prev_button_state == DIO_LOW && jump_flag == 0) {
            jump_flag = 1;
            jump_start_time = current_millis;


            jump_duration = obstacle_period * 6;

            LCD_voidGoTo_XY(LINE_2, dino_col1); LCD_voidWriteString((u8*)"  ");
            hitbox_col1 = 50; hitbox_col2 = 50;

            if (current_millis > jump_sound_timer + jump_sound_period) {
                jump_sound_timer = current_millis;
                BUZZER_voidPlayTone(30);
            }
        }
        prev_button_state = button_state;

        if (jump_flag == 1) {
            LCD_voidGoTo_XY(LINE_1, dino_col1); LCD_voidWriteChar(2);
            LCD_voidGoTo_XY(LINE_1, dino_col2); LCD_voidWriteChar(3);

            if (current_millis > jump_start_time + jump_duration) {
                jump_flag = 0;
                LCD_voidGoTo_XY(LINE_1, dino_col1); LCD_voidWriteString((u8*)"  ");
                hitbox_col1 = 1; hitbox_col2 = 2;
            }
        }

        // --- Collision Logic ---
        u8 is_collision = 0;

        if (obstacle_row == LINE_1 && (obstacle_col == 1 || obstacle_col == 2 || bird_col == 1 || bird_col == 2) && jump_flag == 1) {
            is_collision = 1;
        }

        if (obstacle_row == LINE_2 && (obstacle_col == hitbox_col1 || obstacle_col == hitbox_col2)) {
            is_collision = 1;
        }

        // --- GAME OVER & RESET LOGIC ---
        if(is_collision == 1) {
            BUZZER_voidPlayTone(500);

            LCD_voidClearDisplay();
            LCD_voidGoTo_XY(LINE_1, 3); LCD_voidWriteString((u8*)"GAME OVER!");
            _delay_ms(2000);
            LCD_voidClearDisplay();

            obstacle_col = 15; bird_col = 15;
            obstacle_period = 14;
            score_units = 0; score_hundreds = 0;
            jump_flag = 0; hitbox_col1 = 1; hitbox_col2 = 2;
            obstacle_timer = current_millis; leg_timer = current_millis; score_timer = current_millis;
            draw_obstacle_flag = 0;
            random_obstacle = 1;
            prev_button_state = DIO_LOW;

            continue;
        }

        // --- Score Logic ---
        if (current_millis > score_timer + score_period) {
            score_timer = current_millis;
            score_units++;
            if (score_units == 100) {
                BUZZER_voidPlayTone(80); _delay_ms(50); BUZZER_voidPlayTone(80);
                score_units = 0;
                score_hundreds++;
                if (score_hundreds == 100) score_hundreds = 0;
            }
            LCD_voidGoTo_XY(LINE_2, 14); LCD_voidWriteString((u8*)"  ");
            LCD_voidGoTo_XY(LINE_2, 14); LCD_voidWrite_u32Number(score_units);
            LCD_voidGoTo_XY(LINE_1, 14); LCD_voidWriteString((u8*)"  ");
            LCD_voidGoTo_XY(LINE_1, 14); LCD_voidWrite_u32Number(score_hundreds);
        }
    }
    return 0;
}
