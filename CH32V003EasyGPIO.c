#include "debug.h"
#include "CH32V003EasyGPIO.h"
#include "ch32v00x_gpio.h"

// Stores the mode settings of various pins, such as INPUT, OUTPUT
uint8_t _gpioPinMode[19] = {0xFF, 0xFF, 0xFF, 0xFF,
                            0xFF, 0xFF, 0xFF, 0xFF,
                            0xFF, 0xFF, 0xFF, 0xFF,
                            0xFF, 0xFF, 0xFF, 0xFF,
                            0xFF, 0xFF, 0xFF
                           };

static gpioPinPortMap pinNumToPinPort(uint8_t pin){
    gpioPinPortMap gpio_details;

    // Remap pin selected to GPIO Port
         if(pin == 1 || pin == 2){gpio_details.port = GPIOA;}
    else if(pin >= 3 && pin <= 10){gpio_details.port = GPIOC;}
    else if(pin >= 11 && pin <= 18){gpio_details.port = GPIOD;}

    //Remap pin selected to GPIO_Pin_?
         if(pin == 3 || pin == 11){gpio_details.pin = GPIO_Pin_0;}
    else if(pin == 1 || pin == 4 || pin == 12){gpio_details.pin = GPIO_Pin_1;}
    else if(pin == 2 || pin == 5 || pin == 13){gpio_details.pin = GPIO_Pin_2;}
    else if(pin == 6 || pin == 14){gpio_details.pin = GPIO_Pin_3;}
    else if(pin == 7 || pin == 15){gpio_details.pin = GPIO_Pin_4;}
    else if(pin == 8 || pin == 16){gpio_details.pin = GPIO_Pin_5;}
    else if(pin == 9 || pin == 17){gpio_details.pin = GPIO_Pin_6;}
    else if(pin == 10 || pin == 18){gpio_details.pin = GPIO_Pin_7;}

    return gpio_details;
}

void pinModeRaw(GPIO_TypeDef* port, uint16_t rawPinVal, GPIOMode_TypeDef mode){
    if(port == GPIOA){
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    }else if(port == GPIOC){
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    }else if(port == GPIOD){
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    }

    GPIO_InitTypeDef GPIO_InitStructure = {0};
    GPIO_InitStructure.GPIO_Pin = rawPinVal;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_InitStructure.GPIO_Mode = mode;
    GPIO_Init(port, &GPIO_InitStructure);
}

uint8_t getPinMode(uint8_t pin){
    return _gpioPinMode[pin];
}

void pinModeSetSpeed(uint8_t pin, uint8_t mode, uint8_t speed){
    gpioPinPortMap gpio_pp = pinNumToPinPort(pin);
    uint16_t gpiomode = 0, gpioSpeed = 0;

    if(gpio_pp.port == GPIOA){
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    }else if(gpio_pp.port == GPIOC){
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    }else if(gpio_pp.port == GPIOD){
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    }

    if(mode == INPUT){gpiomode = GPIO_Mode_IN_FLOATING;}
    else if(mode == INPUT_PULLUP){gpiomode = GPIO_Mode_IPU;}
    else if(mode == INPUT_PULLDOWN){gpiomode = GPIO_Mode_IPD;}
    else if(mode == INPUT_ANALOG){gpiomode = GPIO_Mode_AIN;}
    else if(mode == OUTPUT_OPENDRAIN){gpiomode = GPIO_Mode_Out_OD;}
    else if(mode == OUTPUT){gpiomode = GPIO_Mode_Out_PP;}

    if(speed == GPIO_SPEED_2MHz){gpioSpeed = GPIO_Speed_2MHz;}
    else if(speed == GPIO_SPEED_10MHz){gpioSpeed = GPIO_Speed_10MHz;}
    else if(speed == GPIO_SPEED_30MHz){gpioSpeed = GPIO_Speed_30MHz;}

    GPIO_InitTypeDef GPIO_InitStructure = {0};
    GPIO_InitStructure.GPIO_Pin = gpio_pp.pin;
    GPIO_InitStructure.GPIO_Speed = gpioSpeed;
    GPIO_InitStructure.GPIO_Mode = gpiomode;
    GPIO_Init(gpio_pp.port, &GPIO_InitStructure);

    _gpioPinMode[pin] = mode;
}

void pinMode(uint8_t pin, uint8_t mode){
    pinModeSetSpeed(pin, mode, GPIO_SPEED_30MHz);
}

void pinModeAll(uint8_t mode){
    for(uint8_t pin = 0; pin < 19; pin++){
        pinModeSetSpeed(pin, mode, GPIO_SPEED_30MHz);
    }
}

void digitalWrite(uint8_t pin, uint8_t level){
    gpioPinPortMap gpio_pp = pinNumToPinPort(pin);
    GPIO_WriteBit(gpio_pp.port, gpio_pp.pin, level);
}

void digitalWriteRaw(GPIO_TypeDef* port, uint16_t rawPinVal, uint8_t level){
    GPIO_WriteBit(port, rawPinVal, level);
}

uint8_t digitalRead(uint8_t pin){
    gpioPinPortMap gpio_pp = pinNumToPinPort(pin);
    return GPIO_ReadInputDataBit(gpio_pp.port, gpio_pp.pin);
}

uint8_t digitalReadRaw(GPIO_TypeDef* port, uint16_t rawPinVal){
    return GPIO_ReadInputDataBit(port, rawPinVal);
}
