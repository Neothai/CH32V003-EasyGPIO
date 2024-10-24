#ifndef CH32V003EASYGPIO_H_
#define CH32V003EASYGPIO_H_

#include "ch32v00x_gpio.h"
#include <stdint.h>

// GPIO Pin Available
#define PA1 1
#define PA2 2
#define PC0 3
#define PC1 4
#define PC2 5
#define PC3 6
#define PC4 7
#define PC5 8
#define PC6 9
#define PC7 10
#define PD0 11
#define PD1 12
#define PD2 13
#define PD3 14
#define PD4 15
#define PD5 16
#define PD6 17
#define PD7 18

// GPIO Pin Mode
#define INPUT               0x00
#define INPUT_PULLUP        0x01
#define INPUT_PULLDOWN      0x02
#define INPUT_ANALOG        0x03
#define OUTPUT_OPENDRAIN    0x04
#define OUTPUT              0x05
#define GPIO_NOT_REGISTERED 0xFF

// GPIO Speed
#define GPIO_SPEED_2MHz  0x00
#define GPIO_SPEED_10MHz 0x01
#define GPIO_SPEED_30MHz 0x02

// GPIO Level
#define LOW  0x00
#define HIGH 0x01

typedef struct gpioPinPortMap {
    uint16_t pin;
    GPIO_TypeDef* port;
} gpioPinPortMap;

void pinMode(uint8_t pin, uint8_t mode);
void pinModeAll(uint8_t mode);
void pinModeRaw(GPIO_TypeDef* port, uint16_t rawPinVal, GPIOMode_TypeDef mode);
uint8_t getPinMode(uint8_t pin);
void pinModeSetSpeed(uint8_t pin, uint8_t mode, uint8_t speed);
void digitalWrite(uint8_t pin, uint8_t level);
void digitalWriteRaw(GPIO_TypeDef* port, uint16_t rawPinVal, uint8_t level);
uint8_t digitalRead(uint8_t pin);
uint8_t digitalReadRaw(GPIO_TypeDef* port, uint16_t rawPinVal);

#endif /* CH32V003EASYGPIO_H_ */
