// 1. DECLARAR LIBRERIAS
#include "UbidotsEsp32Mqtt.h"

// 2. DEFINICIÓN O ETIQUETADO DE PINES DE ENTRADA Y SALIDA
#define VENTILADOR 5   // Señal PWM al módulo MOSFET — GPIO 5

// 3. DECLARACION DE CONSTANTES
const char* UBIDOTS_TOKEN          = "BBUS-gwVrg4NTI8l2b1YCMCaw4vbrECoc62";
const char* UBIDOTS_DEVICE_LABEL   = "esp32";
const char* UBIDOTS_VARIABLE_LABEL = "velocidad-ventilador";
const char* WIFI_SSID              = "POCO_Eli";
const char* WIFI_PASS              = "elisa123456";
const int   FREQ_PWM               = 1000;   // Frecuencia PWM en Hz
const int   RES_PWM                = 8;      // Resolución 8 bits (0 - 255)

// 4. DECLARACION DE VARIABLES
unsigned int velocidad = 0;   // Velocidad del ventilador (0 - 255)
Ubidots ubidots(UBIDOTS_TOKEN);

// 5. DECLARACION DE SUBRUTINAS Y/O FUNCIONES
void callback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Mensaje recibido: ");
  String payloadStr = (char*)payload;
  Serial.println(payloadStr);

  // El slider de Ubidots envía valores de 0 a 100
  // Se convierte a rango PWM de 0 a 255
  velocidad = payloadStr.toFloat() * 255.0 / 100.0;
  velocidad = constrain(velocidad, 0, 255);   // Limito entre 0 y 255

  ledcWrite(VENTILADOR, velocidad);

  Serial.print("Velocidad PWM: ");
  Serial.println(velocidad);
}

// 6. CONFIGURACION INICIAL
void setup()
{
  // CONFIGURACION DE PINES DE ENTRADA Y SALIDA
  ledcAttach(VENTILADOR, FREQ_PWM, RES_PWM);

  // LIMPIEZA DE SALIDAS
  ledcWrite(VENTILADOR, 0);   // Ventilador apagado al inicio

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