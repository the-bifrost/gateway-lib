/**
 * @file BifrostHandler.h
 * @brief Declaração da Classe base para todos os Handlers da Bifrost.
 * 
 * Todos os Handlers devem implementar as funções descritas aqui, dando override para
 * lidar com suas próprias formas de comunicação (Serial, MQTT, Zigbee, etc).
 */
#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

#include <Envelope.h>

class BifrostHandler {
  public:
    virtual void begin() = 0;
    virtual String read() = 0;
    virtual bool send();
    virtual String getID() = 0;
    virtual bool setID() = 0;
  
  private:
    String id;

  protected:
    SoftwareSerial* serial;
    int _baudrate;
};