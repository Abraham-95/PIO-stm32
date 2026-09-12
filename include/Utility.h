#pragma once
#include "stm32f4xx_hal.h"
#include <cstdint>
#include <cstdarg>

void USB_Print(const char* str);
void USB_Printf(const char* fmt, ...);

#ifdef __cplusplus
extern "C" {
#endif
// millis() and micros()
void DWT_Init(void);
uint32_t micros(void);
uint32_t millis(void);
// main.cpp
void setup(void);
void loop(void);
void uartByteReceived(void);

#ifdef __cplusplus
}
#endif
// Serial3
class UART {
public:
  UART(UART_HandleTypeDef* handle);
  void begin();
  void onByteReceived(uint8_t byte);
  bool available();
  uint8_t read();
  uint8_t* getRxBufferPtr() { return &rxByte; }
private:
  UART_HandleTypeDef* huart;
  static const uint16_t BUFFER_SIZE = 256;
  volatile uint8_t buffer[BUFFER_SIZE];
  volatile uint16_t head = 0;
  volatile uint16_t tail = 0;
  uint8_t rxByte;
};
