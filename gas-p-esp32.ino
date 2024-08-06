#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <map>
#include <functional>

// Configura tus credenciales WiFi
const char* ssid = "www.icm.com";
const char* password = "Dakar*2024";

String disNombre = "Piso";

// Configura una IP estática
IPAddress local_ip(192, 168, 1, 189);  // Cambia a la IP que desees usar
IPAddress gateway(192, 168, 1, 1);     // Cambia al gateway de tu red
IPAddress subnet(255, 255, 255, 0);    // Cambia a la máscara de subred de tu red

WiFiServer server(82);  // Puerto en el que escuchará

// Definir funciones de manejo de mensajes
void handleIsConnect(WiFiClient& client) {
  //client.println("connect");
  Serial.println("Cliente conectado");
}

void handleGetName(WiFiClient& client) {
  client.println("nombre: " + disNombre);
  Serial.println("Mensaje enviado: nombre: " + disNombre);
}

void handleActivated(WiFiClient& client) {

  Serial.println("Dispositivo Accionado");
  client.stop();
}

void handleDisconnect(WiFiClient& client) {
  client.stop();
  Serial.println("Cliente desconectado");
}

void handleUnknown(WiFiClient& client) {
  Serial.println("Mensaje no reconocido.");
}

// Crear un mapa de funciones
std::map<String, std::function<void(WiFiClient&)>> messageHandlers = {
  { "isConnected", handleIsConnect },
  { "getName", handleGetName },
  { "activate", handleActivated },
  { "disconnect", handleDisconnect }
};

void setup() {
  // Inicializa la comunicación serial
  Serial.begin(115200);

  // Configura la IP estática
  if (!WiFi.config(local_ip, gateway, subnet)) {
    Serial.println("Fallo en la configuración de la IP estática");
  }

  // Conéctate a la red WiFi
  WiFi.begin(ssid, password);

  Serial.println("Conectando a la red WiFi...");

  // Espera hasta que se conecte con un timeout
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
    delay(100);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    // Imprime la dirección IP cuando esté conectado
    Serial.println("");
    Serial.println("Conectado a la red WiFi");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());

    // Inicia el servidor
    server.begin();
  } else {
    Serial.println("No se pudo conectar a la red WiFi");
  }
}

void loop() {
  // Espera por un cliente
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Cliente conectado");

    while (client.connected()) {
      if (client.available()) {
        String message = client.readStringUntil('\n');
        message.trim();

        Serial.print("Mensaje recibido: ");
        Serial.println(message);

        // Responde según el mensaje recibido usando el mapa de funciones
        auto handler = messageHandlers.find(message);
        if (handler != messageHandlers.end()) {
          handler->second(client);  // Llama a la función asociada
        } else {
          handleUnknown(client);
        }
      }
    }
  }
}