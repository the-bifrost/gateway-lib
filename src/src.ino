#include "Bifrost.h"
#include "Envelope.h"

#define TX D2 
#define RX D3

//EspNowHandler espnow = EspNowHandler(RX, TX, 9600);

void setup() {
  Serial.begin(115200);
  delay(500);

  //espnow.begin();
}

void loop() {
  String mensagem = makeEnvelope("", "central", 80, "status", 1);
  Serial.println(mensagem);
  Serial.println(isValidEnvelope(mensagem));

  mensagem = makeEnvelope("", "central", "xuxu", "status", 1);
  Serial.println(mensagem);
  Serial.println(isValidEnvelope(mensagem));

  StaticJsonDocument<128> payloadDoc;
  JsonObject payload = payloadDoc.to<JsonObject>();
  payload["temperature"] = 25.3;
  payload["humidity"] = 60;
  payload["unit"] = "C";

  mensagem = makeEnvelope("sensor01", "bifrost", payload, "state", 1);
  Serial.println(mensagem);
  Serial.println(isValidEnvelope(mensagem));

  delay(2000);
}
