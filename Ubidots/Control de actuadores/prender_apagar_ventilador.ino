// 1. DECLARAR LIBRERIAS
#include "UbidotsEsp32Mqtt.h"

// 2. DEFINICIÓN O ETIQUETADO DE PINES DE ENTRADA Y SALIDA
#define VENTILADOR 5   // Señal de control al módulo MOSFET — GPIO 5

// 3. DECLARACION DE CONSTANTES
const char* UBIDOTS_TOKEN          = "TU_TOKEN";
const char* UBIDOTS_DEVICE_LABEL   = "esp32";
const char* UBIDOTS_VARIABLE_LABEL = "ventilador";
const char* WIFI_SSID              = "TU_RED_WIFI";
const char* WIFI_PASS              = "TU_PASSWORD_WIFI";

// 4. DECLARACION DE VARIABLES
Ubidots ubidots(UBIDOTS_TOKEN);

// 5. DECLARACION DE SUBRUTINAS Y/O FUNCIONES
void callback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Mensaje recibido: ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if ((char)payload[0] == '1')   // Si llega 1 desde Ubidots
  {
    digitalWrite(VENTILADOR, HIGH);   // Enciende el ventilador
    Serial.println("Ventilador: ENCENDIDO");
  }
  else                           // Si llega 0 desde Ubidots
  {
    digitalWrite(VENTILADOR, LOW);    // Apaga el ventilador
    Serial.println("Ventilador: APAGADO");
  }
}

// 6. CONFIGURACION INICIAL
void setup()
{
  // CONFIGURACION DE PINES DE ENTRADA Y SALIDA
  pinMode(VENTILADOR, OUTPUT);

  // LIMPIEZA DE SALIDAS
  digitalWrite(VENTILADOR, LOW);   // Ventilador apagado al inicio

  // COMUNICACIONES
  Serial.begin(115200);
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  ubidots.setCallback(callback);
  ubidots.setup();
  ubidots.reconnect();
  ubidots.subscribeLastValue(UBIDOTS_DEVICE_LABEL, UBIDOTS_VARIABLE_LABEL);
}

// 7. FUNCION INFINITA PRINCIPAL
void loop()
{
  if (!ubidots.connected())
  {
    ubidots.reconnect();
    ubidots.subscribeLastValue(UBIDOTS_DEVICE_LABEL, UBIDOTS_VARIABLE_LABEL);
  }
  ubidots.loop();
}