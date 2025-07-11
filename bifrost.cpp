#include "bifrost.h"

BifrostHandler::BifrostHandler(uint8_t rxPin, uint8_t txPin, unsigned long baud)
  : serial(rxPin, txPin), baudRate(baud) {}

void BifrostHandler::begin() {
  serial.begin(baudRate);
}

bool BifrostHandler::send(const String& message) {
  serial.println(message);
  return true;
}

String BifrostHandler::receive() {
  if (serial.available()) {
    return serial.readStringUntil('\n');
  }
  return "";
}