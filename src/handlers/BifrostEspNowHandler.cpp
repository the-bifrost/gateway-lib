/**
 * @file BifrostEspNowHandler.cpp
 * @brief Implementação da Classe base para Handlers que funcionam com ESPNOW.
 * 
 * Essa classe herda de BifrostHandler e faz o override de suas funções para implementar a comunicação via ESP-Now.
 */
#include "BifrostEspNowHandler.h"
#include <ArduinoJson.h>

EspNowHandler::EspNowHandler(uint8_t rx, uint8_t tx, int baudrate) {
  serial = new SoftwareSerial(rx, tx);
  _baudrate = baudrate;
}

void EspNowHandler::begin() {
  serial->begin(_baudrate);
}

String EspNowHandler::read() {
  if (serial->available()) {
    String msg = serial->readStringUntil('\n');
    return msg;
  }
  return "";
}

bool EspNowHandler::send() {
  // Implemente o envio real aqui, se necessário
  return true;
}


