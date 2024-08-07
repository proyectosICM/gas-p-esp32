#include <Arduino.h>
#include "WiFiConfig.h"
#include "MessageHandlers.h"

void setup() {
  // Inicializa la comunicación serial
  Serial.begin(115200);

  // Configura e inicia el WiFi y el servidor
  setupWiFi();
}

void loop() {
  // Maneja los clientes conectados
  handleClient();
}