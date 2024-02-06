#ifndef MAIN_h
#define MAIN_h

#define RXD2                16
#define TXD2                17
#define SERIAL2_BAUD        9600
#define SERIAL2_PROTOCOL    SERIAL_8N1
#define SERIAL2_TIMEOUT     500UL          //Timeout in ms if waiting for chars the dont come

#define LED_STABLE      26          //
#define LED_NOISE       27          //
#define LED_LOADED      18          //
#define LED_PRINT       19          //
#define LED_SPEED       23

#define SW_CONFIG       32          //
#define SW_STABLE       15          //
#define SW_NOISE         2          //
#define SW_LOADED        0          //
#define SW_PRINT         4          //
#define SW_SPEED         5          //

#define MONITOR_SPEED    115200
#define SDA              21
#define SCL              22


#define LED_ON           HIGH
#define LED_OFF          LOW


#endif