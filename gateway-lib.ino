#include "bifrost.h"

BifrostHandler bifrost(D2, D3);

void setup() {
  Serial.begin(115200);
  delay(500);

  bifrost.begin();

  DynamicJsonDocument payload(100);
  payload["status"] = "ok";
  payload["val"] = 42;

  String msg = makeEnvelope("sensor1", "gateway", payload);
  bifrost.send(msg);
  Serial.println("Sent:");
  Serial.println(msg);
  delay(1000);

  msg = makeEnvelope("sensor1", "gateway", 20);
  bifrost.send(msg);
  Serial.println("Sent:");
  Serial.println(msg);
  delay(1000);

  msg = makeEnvelope("sensor1", "gateway", "testando");
  bifrost.send(msg);
  Serial.println("Sent:");
  Serial.println(msg);
  delay(1000);
}

void loop() {
  String received = bifrost.receive();
  
  if (received.length()) {
    Serial.println("Received:");
    Serial.println(received);
  }
}