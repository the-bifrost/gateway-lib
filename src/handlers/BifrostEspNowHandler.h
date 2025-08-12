/**
 * @file BifrostEspNowHandler.h
 * @brief Declaração da Classe base para Handlers que funcionam com ESPNOW.
 * 
 * Essa classe herda de BifrostHandler e faz o override de suas funções para implementar a comunicação via ESP-Now.
 */
#pragma once

#include "BifrostHandler.h"

class EspNowHandler : public BifrostHandler {
  public:
    EspNowHandler(uint8_t rx, uint8_t tx, int baudrate);
    void begin() override;
    String read() override;
    bool send() override;
    String getID() override;
    bool setID() override;
};