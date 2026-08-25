// 1. DECLARAR LIBRERIAS
#include <UbidotsEsp32Mqtt.h>


// 2. DEFINICIÓN O ETIQUETADO DE PINES DE ENTRADA Y SALIDA
#define LEDR 25   // Canal rojo   — GPIO 25
#define LEDG 26   // Canal verde  — GPIO 26
#define LEDB 27   // Canal azul   — GPIO 27


// 3. DECLARACION DE CONSTANTES
const char* UBIDOTS_TOKEN  = "tu token";
const char* WIFI_SSID      = "wifi";
const char* WIFI_PASS      = "contraseña";

const char* DEVICE_LABEL   = "esp32";
const char* VAR_RED        = "led-red";
const char* VAR_GREEN      = "led-green";
const char* VAR_BLUE       = "led-blue";

const int FREQ_PWM = 5000;
const int RES_PWM  = 8;


// 4. DECLARACION DE VARIABLES
Ubidots ubidots(UBIDOTS_TOKEN);


// 5. DECLARACION DE SUBRUTINAS Y/O FUNCIONES
void callback(char* topic, byte* payload, unsigned int length)
{
  String topicStr   = String(topic);
  String payloadStr = "";


  for (unsigned int i = 0; i < length; i++)
  {
    payloadStr += (char)payload[i];
  }


  int pwm = map(constrain(payloadStr.toInt(), 0, 100), 0, 100, 0, 255);


  if      (topicStr.indexOf("/led-red/")   >= 0) { ledcWrite(LEDR, pwm); Serial.print("Rojo: ");  }
  else if (topicStr.indexOf("/led-green/") >= 0) { ledcWrite(LEDG, pwm); Serial.print("Verde: "); }
  else if (topicStr.indexOf("/led-blue/")  >= 0) { ledcWrite(LEDB, pwm); Serial.print("Azul: ");  }


  Serial.println(payloadStr.toInt());
}


// 6. CONFIGURACION INICIAL
void setup()
{
  // CONFIGURACION DE PINES DE ENTRADA Y SALIDA
  ledcAttach(LEDR, FREQ_PWM, RES_PWM);
  ledcAttach(LEDG, FREQ_PWM, RES_PWM);
  ledcAttach(LEDB, FREQ_PWM, RES_PWM);


  // LIMPIEZA DE SALIDAS
  ledcWrite(LEDR, 0);
  ledcWrite(LEDG, 0);
  ledcWrite(LEDB, 0);


  // COMUNICACIONES
  Serial.begin(115200);
  ubidots.setCallback(callback);
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  Serial.println(WiFi.status() == WL_CONNECTED ? "WiFi conectado" : "Error WiFi");
  ubidots.setup();
  ubidots.reconnect();
  Serial.println(ubidots.connected() ? "MQTT conectado" : "Error MQTT");

  ubidots.subscribeLastValue(DEVICE_LABEL, VAR_RED);
  ubidots.subscribeLastValue(DEVICE_LABEL, VAR_GREEN);
  ubidots.subscribeLastValue(DEVICE_LABEL, VAR_BLUE);
}


// 7. FUNCION INFINITA PRINCIPAL
void loop()
{
  if (!ubidots.connected())
  {
    ubidots.reconnect();

    ubidots.subscribeLastValue(DEVICE_LABEL, VAR_RED);
    ubidots.subscribeLastValue(DEVICE_LABEL, VAR_GREEN);
    ubidots.subscribeLastValue(DEVICE_LABEL, VAR_BLUE);
  }

  ubidots.loop();
}