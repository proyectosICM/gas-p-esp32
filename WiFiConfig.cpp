#include "WiFiConfig.h"
#include "MessageHandlers.h"

const char* ssid = "www.icm.com";
const char* password = "Dakar*2024";

IPAddress local_ip(192, 168, 1, 189);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WiFiServer server(82);

void setupWiFi() {
    if (!WiFi.config(local_ip, gateway, subnet)) {
        Serial.println("Fallo en la configuración de la IP estática");
    }

    WiFi.begin(ssid, password);
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
