/**
 * @file  bifrost.h
 * @brief Definição dos códigos para o envelopamento padrão de mensagens da Bifrost.
 *
 * Para que todos os dispositivos "falem a mesma língua", usamos um envelopamento
 * padrão dos dados. A Classe e funções abaixo servem para montar, validar e fazer
 * a leitura desse Envelope padrão. 
 */
#pragma once

#include <Arduino.h>
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
inline String makeEnvelope(const String& src, const String& dst, const JsonVariant& payload, const String& msgType, int version) {
  DynamicJsonDocument doc(512);

  switch (version) {
    case 1:
      doc["v"] = version;
      doc["src"] = src;
      doc["dst"] = dst;
      doc["type"] = msgType;
      doc["ts"] = millis();
      doc["payload"] = payload;

    default:
      // Procolos sem uma versão configurada retornam uma string nula.
      return "";
  }
    
  String output;
  serializeJson(doc, output);
  return output;
}

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
inline String makeEnvelope(const String& src, const String& dst, T simplePayload, const String& msgType, int version) {
  DynamicJsonDocument doc(512);

  switch (version) {
    case 1:
      doc["v"] = version;
      doc["src"] = src;
      doc["dst"] = dst;
      doc["type"] = msgType;
      doc["ts"] = millis();
      doc["payload"] = simplePayload;

    default:
      // Procolos sem uma versão configurada retornam uma string nula.
      return "";
  }

  String output;
  serializeJson(doc, output);
  return output;
}

/**
 * @brief Recebe uma String e retorna a validação do padrão de mensagens.
 * 
 * Atualmente ela válida apenas de acordo com a versão 1 do protocolo, mas é necessário
 * implementar a verificação para diferentes versões.
 *
 * @param message Uma String que será validada para determinar se está de acordo com o padrão esperado.
 *
 * @return Um boolean. True -> É um envelope válido.
 */
inline bool isValidEnvelope(const String& message) {
  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, message);

  if (error) return false;

  return doc.containsKey("v") && 
         doc.containsKey("src") &&
         doc.containsKey("dst") && 
         doc.containsKey("type") && 
         doc.containsKey("ts") && 
         doc.containsKey("payload");
}

/**
 * @brief Recebe uma String, faz o parse parse para JSON e retorna a validação sucesso.
 * 
 * Atualmente ela válida apenas de acordo com a versão 1 do protocolo, mas é necessário
 * implementar a verificação para diferentes versões.
 *
 * @param message A string que será usada para fazer o Parse JSON.
 * @param docOut O documento JSON em que serão salvos os dados.
 *
 * @return Um boolean. True -> É um envelope válido.
 */
inline bool deserializeEnvelope(const String& message, JsonDocument& docOut) {
  DeserializationError error = deserializeJson(docOut, message);
  if (error) return false;

  // Suporte apenas ao protocolo versão 1 por enquanto
  if (!docOut.containsKey("v") || docOut["v"].as<int>() != 1) return false;

  return docOut.containsKey("src") &&
         docOut.containsKey("dst") &&
         docOut.containsKey("type") &&
         docOut.containsKey("ts") &&
         docOut.containsKey("payload");
}



