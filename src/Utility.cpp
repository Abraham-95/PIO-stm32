#include "Utility.h"
#include <cstdio>
#include <cstring>

UART::UART(UART_HandleTypeDef* handle) : huart(handle) {}
// millis() and micros()
void DWT_Init(void) {
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  DWT->CYCCNT = 0; DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

uint32_t micros(void) {
  return DWT->CYCCNT / (SystemCoreClock / 1000000U);
}

uint32_t millis(void) {
  return HAL_GetTick();
}
// Serial3
void UART::begin() {
  HAL_UART_Receive_IT(huart, &rxByte, 1); // first arm interupt
}

void UART::onByteReceived(uint8_t byte) {
  uint16_t next = (head + 1) % BUFFER_SIZE;
  if (next != tail) { // prevent overwrite when buffer is full
    buffer[head] = byte;
    head = next;
  }
  HAL_UART_Receive_IT(huart, &rxByte, 1); // re-arm for next byte
}

bool UART::available() {
  return head != tail;
}

uint8_t UART::read() {
  uint8_t b = buffer[tail]; tail = (tail + 1) % BUFFER_SIZE; return b;
}

extern "C" {
  #include "usbd_cdc_if.h"
}

void USB_Print(const char* str) {
  uint16_t len = strlen(str); CDC_Transmit_FS((uint8_t*)str, len);
}

void USB_Printf(const char* fmt, ...) {
  char buffer[256]; va_list args; va_start(args, fmt);
  int len = vsnprintf(buffer, sizeof(buffer), fmt, args);
  va_end(args);
  if (len > 0) {
    CDC_Transmit_FS((uint8_t*)buffer, (uint16_t)len);
  }
}

