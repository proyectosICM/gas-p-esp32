#include "WiFiConfig.h"
#include "MessageHandlers.h"
#include "Config.h"

WiFiServer server(SERVER_PORT);

void setupWiFi() {
    if (!WiFi.config(LOCAL_IP, GATEWAY, SUBNET)) {
        Serial.println("Fallo en la configuración de la IP estática");
    }

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.println("Conectando a la red WiFi...");

    unsigned long startAttemptTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
        delay(100);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("");
        Serial.println("Conectado a la red WiFi");
        Serial.print("Dirección IP: ");
        Serial.println(WiFi.localIP());

        server.begin();
    } else {
        Serial.println("No se pudo conectar a la red WiFi");
    }
}

WiFiServer& getServer() {
    return server;
}
