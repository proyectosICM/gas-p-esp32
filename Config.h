#ifndef CONFIG_H
#define CONFIG_H

// Configuración de WiFi
#define WIFI_SSID "www.icm.com"
#define WIFI_PASSWORD "Dakar*2024"

// Configuración de IP estática
#define LOCAL_IP   IPAddress(192, 168, 1, 186)
#define GATEWAY     IPAddress(192, 168, 1, 1)
#define SUBNET      IPAddress(255, 255, 255, 0)

// Puerto del servidor
#define SERVER_PORT 82

// Nombre del dispositivo
#define NAME_DEVICE "Puerta 1"

#endif
