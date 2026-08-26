#ifndef TIMER0_CONFIG_H
#define TIMER0_CONFIG_H

#define     TIMER0_MODE                  NORMAL_MODE

#define     DISCONNECTED                 0
#define     TOGGLE_ON_COMPARE            1
#define     CLEAR_ON_COMPARE             2
#define     SET_ON_COMPARE               3

#define     TIMER0_OC0_MODE              TOGGLE_ON_COMPARE

#define     TIMER0_PWM_MODE              NON_INVERTING_PWM

#define     NO_CLK_SOURCE_TIMER_STOPED       0x00
#define     NOT_USE_PRESCALER                0x01
#define     PRESCALER_DIVISION_BY_8          0x02
#define     PRESCALER_DIVISION_BY_64         0x03
#define     PRESCALER_DIVISION_BY_256        0x04
#define     PRESCALER_DIVISION_BY_1024       0x05
#define     EXTERNAL_CLK_SOURCE_FALLING_EDGE 0x06
#define     EXTERNAL_CLK_SOURCE_RAISING_EDGE 0x07

#define     TIMER0_CLK_CFG             PRESCALER_DIVISION_BY_8

#define     CPU_CLK                    8

#endif

