/**
 * @file bifrost.h
 * @brief Declaração dos códigos e classes para handlers, sensores e parsers Bifrost.
 */

#pragma once

#if defined(ESP8266)
  #define BIFROST_PLATFORM "esp8266"
#elif defined(ESP32)
  #define BIFROST_PLATFORM "esp32"
#else
  #define BIFROST_PLATFORM "unknown"
#endif

/// Libs padrão para a utilização de todos os tipos de dispositivos.
//#include "Envelope.h"

/// Libs dos Sensores, Handlers e Atuadores
//#include "BifrostHandler.h"
//#include "./handlers/BifrostEspNowHandler.h"


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

// /**
//  * @class BifrostHandler
//  * @brief Classe das Unidades receptoras da bifrost.
//  */
// class BifrostHandler {
//     public:
//         /**
//          * @brief Inicializa uma nova unidade receptora da bifrost.
//          *
//          * @param  rxPin  Pino RX da conexão UART
//          * @param  txPin  Pino TX da conexão UART
//          * @param  baud   baudrate do serial.
//         */
//         BifrostHandler(uint8_t rxPin, uint8_t txPin, unsigned long baud = 9600);
//         void begin();

//         /**
//          * @brief Envia dados pela conexão softwareSerial já estabelecida.
//          * 
//          * @param  message  String contendo a mensagem que será enviada.
//          *
//          * @return Um boolean com o status do envio da mensagem.
//          */
//         bool send(const String& message);
        
//         /**
//          * @brief Faz a leitura contínua da conexão serial estabelecida.
//          *
//          * Sempre que ouverem dados na serial, faz a leitura até a quebra de linha.
//          * Caso não houver nada, retorna uma string vazia.
//          *
//          * @return Uma string com os dados lidos na serial.
//          */
//         String receive();
    
//     private:
//         /**
//          * Instância interna da conxão serial.
//         */
//         SoftwareSerial serial;
//         unsigned long baudRate;
// };


///
/// Implementação das Funções da Classe BifrostHandler
///
// BifrostHandler::BifrostHandler(uint8_t rxPin, uint8_t txPin, unsigned long baud): serial(rxPin, txPin), baudRate(baud) {}

// void BifrostHandler::begin() {
//   serial.begin(baudRate);
// }

// bool BifrostHandler::send(const String& message) {
//   serial.println(message);
//   return true;
// }

// String BifrostHandler::receive() {
//   if (serial.available()) {
//     return serial.readStringUntil('\n');
//   }
//   return "";
// }