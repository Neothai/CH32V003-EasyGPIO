# CH32V003-EasyGPIO
Arduino-like GPIO Library For CH32V003 On MounRiver Studio

ไลบรารี่สำหรับใช้งาน I/O บน MCU CH32V003 โดยใช้สไตล์โค้ดแบบ Arduino เช่น `pinMode()`, `digitalWrite()`, `digitalRead()`

# Usage การใช้งาน
- Include Library First `#include "CH32V003EasyGPIO.h"`
- Call `pinMode()` To Set GPIO Pin And Mode
```c
// Set PC4 Pin AS Output Mode
pinMode(PC4, OUTPUT);

// Set PD0 Pin As Input-Pullup Mode
pinMode(PD0, INPUT_PULLUP);
```

- Call `digitalWrite()` To Write GPIO Level
```c
// Set PC4 Pin To High
digitalWrite(PC4, HIGH);

// Set PC4 Pin To Low
digitalWrite(PC4, LOW);
```

- Call `digitalRead()` To read GPIO Level
```c
// Get PD0 Pin Level
uint8_t PD0_level = digitalRead(PD0);
```

# Available Functions ฟังก์ชั่นที่พร้อมใช้งาน
```c
// Functions To Set Pin Mode (ฟังก์ชั่นสำหรับกำหนดโหมดของขา GPIO ต่างๆ)
void pinMode(uint8_t pin, uint8_t mode);
void pinModeAll(uint8_t mode);
void pinModeRaw(GPIO_TypeDef* port, uint16_t rawPinVal, GPIOMode_TypeDef mode);
void pinModeSetSpeed(uint8_t pin, uint8_t mode, uint8_t speed);

// Functions To Get Current Mode Of GPIO Pin (ฟังก์ชั่นสำหรับอ่านโหมดของขา GPIO นั้นๆ)
uint8_t getPinMode(uint8_t pin);

// Functions To Set Pin Level (ฟังก์ชั่นสำหรับตั้งค่า Level ของขา GPIO)
void digitalWrite(uint8_t pin, uint8_t level);
void digitalWriteRaw(GPIO_TypeDef* port, uint16_t rawPinVal, uint8_t level);

// Functions To Get Pin Level (ฟังก์ชั่นสำหรับอ่านค่า Level ของขา GPIO)
uint8_t digitalRead(uint8_t pin);
uint8_t digitalReadRaw(GPIO_TypeDef* port, uint16_t rawPinVal);
```
