/**
 * @file bifrost.h
 * @brief  Declaração dos códigos e classes para handlers e sensores Bifrost.
 *
 * A comunicação entre os dispositivos é feita usando um envelope padrão de mensagens.
 * 
 * Para as unidades que recebem dados e enviam para a central bifrost, usamos a Classe
 * BifrostHandler. Ela cria uma conexão com o Dispatcher usando a lib SoftwareSerial e 
 * faz a conversão bidirecional entre serial e JSON.
 */
#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

/**
 * @brief Cria um JSON com as informações recebidas e converte em uma String JSON.
 *
 * Essa função é chamada caso a payload for um objeto da lib ArduinoJson. A String é 
 * montada com base no formato padrão de comunicação (envelope) da Bifrost.
 *
 * @param  src      É o remetente da mensagem (id dos sensores/atuadores, ou então da bifrost)
 * @param  dst      É o destinatário da mensagem (id dos sensores/atuadores, ou então da bifrost)
 * @param  payload  Um objeto JSON da lib ArduinoJSON
 * @param  msgType  Tipo de mensagem (state, register_request, register_response, ...)
 * @param  version  versão do envelope, usamos para permitir retrocompatibilidade no futuro.
 *
 * @return Uma string JSON com todas as informações do envelope.
 */
String makeEnvelope(const String& src, const String& dst, const JsonVariant& payload, const String& msgType = "state", int version = 1);

/**
 * @brief Cria um JSON com as informações recebidas e converte em uma String JSON.
 *
 * Essa função é chamada caso a payload for um valor primitivo (int, string, float, ...). A String é 
 * montada com base no formato padrão de comunicação (envelope) da Bifrost.
 *
 * @param  src      É o remetente da mensagem (id dos sensores/atuadores, ou então da bifrost)
 * @param  dst      É o destinatário da mensagem (id dos sensores/atuadores, ou então da bifrost)
 * @param  payload  Uma variável primitiva
 * @param  msgType  Tipo de mensagem (state, register_request, register_response, ...)
 * @param  version  versão do envelope, usamos para permitir retrocompatibilidade no futuro.
 *
 * @return Uma string JSON com todas as informações do envelope.
 */
template <typename T>
String makeEnvelope(const String& src, const String& dst, T simplePayload, const String& msgType = "state", int version = 1);

/**
 * @brief Recebe uma String e retorna a validação do padrão de mensagens.
 *
 * @param message Uma String que será validada para determinar se está de acordo com o padrão esperado.
 *
 * @return O número inteiro de acordo com o protocolo, caso for inválida, retorna -1.
 */
int isValidEnvelope(const String& message);

/**
 * @class BifrostHandler
 * @brief Classe das Unidades receptoras da bifrost.
 */
class BifrostHandler {
    public:
        /**
         * @brief Inicializa uma nova unidade receptora da bifrost.
         *
         * @param  rxPin  Pino RX da conexão UART
         * @param  txPin  Pino TX da conexão UART
         * @param  baud   baudrate do serial.
        */
        BifrostHandler(uint8_t rxPin, uint8_t txPin, unsigned long baud = 9600);
        void begin();

        /**
         * @brief Envia dados pela conexão softwareSerial já estabelecida.
         * 
         * @param  message  String contendo a mensagem que será enviada.
         *
         * @return Um boolean com o status do envio da mensagem.
         */
        bool send(const String& message);
        
        /**
         * @brief Faz a leitura contínua da conexão serial estabelecida.
         *
         * Sempre que ouverem dados na serial, faz a leitura até a quebra de linha.
         * Caso não houver nada, retorna uma string vazia.
         *
         * @return Uma string com os dados lidos na serial.
         */
        String receive();
    
    private:
        /**
         * Instância interna da conxão serial.
        */
        SoftwareSerial serial;
        unsigned long baudRate;
};

/// Implementação das funções make. A implementação de template só pode ser declarada em bifrost.h
/// por conta do compilador. As outras funções overloading são declaradas aqui para manter tudo em um só lugar.
template <typename T>
String makeEnvelope(const String& src, const String& dst, T simplePayload, const String& msgType, int version) {
  DynamicJsonDocument doc(512);
  doc["v"] = version;
  doc["src"] = src;
  doc["dst"] = dst;
  doc["type"] = msgType;
  doc["ts"] = millis();
  doc["payload"] = simplePayload;

  String output;
  serializeJson(doc, output);
  return output;
}

inline String makeEnvelope(const String& src, const String& dst, const JsonVariant& payload, const String& msgType, int version) {
  DynamicJsonDocument doc(512);
  doc["v"] = version;
  doc["src"] = src;
  doc["dst"] = dst;
  doc["type"] = msgType;
  doc["ts"] = millis();
  doc["payload"] = payload;

  String output;
  serializeJson(doc, output);
  return output;
}