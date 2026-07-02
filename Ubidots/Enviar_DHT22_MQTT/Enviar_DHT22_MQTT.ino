// 1. DECLARAR LIBRERIAS
#include "UbidotsEsp32Mqtt.h" 
#include "DHT.h"               

// 2. DEFINICIÓN O ETIQUETADO DE PINES DE ENTRADA Y SALIDA
#define DHTPIN 4    // Pin DATA del DHT22 conectado al GPIO4

// 3. DECLARACION DE CONSTANTES
#define DHTTYPE DHT22  // Tipo de sensor DHT

const char* UBIDOTS_TOKEN        = "token default";
const char* UBIDOTS_DEVICE_LABEL = "esp32";
const char* UBIDOTS_VAR_TEMP     = "temperatura";
const char* UBIDOTS_VAR_HUM      = "humedad";
const char* WIFI_SSID            = "wifi";
const char* WIFI_PASS            = "contraseña";

const unsigned long T_SEND = 5000;  // Tiempo entre envíos (5 segundos)

// 4. DECLARACION DE VARIABLES
float temp = 0;
float hum  = 0;

unsigned long tact = 0;
unsigned long tini = 0;
unsigned long trel = 0;

// 5. DECLARACION DE SUBRUTINAS Y/O FUNCIONES
DHT dht(DHTPIN, DHTTYPE);       // Objeto DHT22
Ubidots ubidots(UBIDOTS_TOKEN, "things.ubidots.com"); // Objeto Ubidots

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensaje recibido [");
  Serial.print(topic);
  Serial.print("]: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

// 6. CONFIGURACION INICIAL
void setup() {
  // CONFIGURACION DE PINES DE ENTRADA Y SALIDA
  
  // LIMPIEZA DE SALIDAS

  // COMUNICACIONES
  Serial.begin(115200);

  dht.begin();  // Inicializar sensor DHT22

  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  ubidots.setCallback(callback);
  ubidots.setup();
  ubidots.reconnect();

  tini = millis();
}

// 7. FUNCION INFINITA PRINCIPAL
void loop() {
  tact = millis();  // Tiempo actual

  if (!ubidots.connected()) {  // Si se cayó la conexión, reconectar
    ubidots.reconnect();
  }

  trel = tact - tini;  // Tiempo relativo desde el último envío

  if (trel >= T_SEND) {  // Si pasaron 5 segundos, leer y enviar

    temp = dht.readTemperature();  // Leer temperatura en °C
    hum  = dht.readHumidity();     // Leer humedad en %

    if (isnan(temp) || isnan(hum)) {  // Verificar lectura válida
      Serial.println("Error leyendo DHT22");
      tini = millis();
      return;
    }

    Serial.println("Temperatura: " + String(temp) + " °C");
    Serial.println("Humedad: "     + String(hum)  + " %");

    ubidots.add(UBIDOTS_VAR_TEMP, temp);     // Empaquetar temperatura
    ubidots.add(UBIDOTS_VAR_HUM,  hum);      // Empaquetar humedad
    ubidots.publish(UBIDOTS_DEVICE_LABEL);   // Enviar paquete a Ubidots

    tini = millis();  // Reiniciar timer
  }

  ubidots.loop();  // Mantener conexión MQTT activa
}