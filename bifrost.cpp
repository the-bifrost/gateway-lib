/**
 * @file bifrost.cpp
 * @brief  Implementação dos códigos e classes para handlers e sensores Bifrost.
 *
 * A comunicação entre os dispositivos é feita usando um envelope padrão de mensagens.
 * 
 * Para as unidades que recebem dados e enviam para a central bifrost, usamos a Classe
 * BifrostHandler. Ela cria uma conexão com o Dispatcher usando a lib SoftwareSerial e 
 * faz a conversão bidirecional entre serial e JSON.
 */
#include "bifrost.h"

/// Mensagens inválidas retornam sempre -1 
int isValidEnvelope(String message) {
  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, message);

  if (error) return -1;

  if (doc.containsKey("v") &&
      doc.containsKey("src") &&
      doc.containsKey("dst") &&
      doc.containsKey("type") &&
      doc.containsKey("ts") &&
      doc.containsKey("payload")) {
    
    if (doc["v"].is<int>()) {
      return doc["v"];
    }
  }

  return -1;
}

///
/// Implementação das Funções da Classe BifrostHandler
///
BifrostHandler::BifrostHandler(uint8_t rxPin, uint8_t txPin, unsigned long baud): serial(rxPin, txPin), baudRate(baud) {}

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