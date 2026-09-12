#include "Mode.h"
#include "Utility.h"

void StandbyMode::init() {
  USB_Printf("Standby Mode Initialized");
}

void StandbyMode::loop() {
  // Standby mode loop logic
}

void StandbyMode::exit() {
  USB_Printf("Exiting Standby Mode");
}
