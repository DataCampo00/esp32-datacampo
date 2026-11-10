//Descripción: este programa combina el Deep Sleep por temporizador con la lectura del sensor
//ambiental BME680. Cada 30 segundos el ESP32 despierta, inicializa el sensor, toma una lectura
//de temperatura, presion, humedad, resistencia de gas y altitud aproximada, la imprime por
//serial y vuelve a dormir. El contador de arranques vive en memoria RTC.
//Basado en los ejemplos TimerWakeUp de Espressif y BME680test de Adafruit.
//Montaje I2C: VCC->3V3, GND->GND, SDA->GPIO21, SCL->GPIO22

// 1. DECLARAR LIBRERIAS
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

// 2. DEFINICIÓN O ETIQUETADO DE PINES DE ENTRADA Y SALIDA
#define BME_SDA 21  // Pin de datos I2C (por defecto en el ESP32)
#define BME_SCL 22  // Pin de reloj I2C (por defecto en el ESP32)

// 3. DECLARACION DE CONSTANTES
#define uS_TO_S_FACTOR 1000000ULL  // Factor de conversion de microsegundos a segundos
#define TIME_TO_SLEEP  5          // Tiempo que el ESP32 estara dormido (en segundos)
#define SEALEVELPRESSURE_HPA (1013.25)  // Presion al nivel del mar, para calcular la altitud

// 4. DECLARACION DE VARIABLES
RTC_DATA_ATTR int bootCount = 0;  // Vive en memoria RTC: sobrevive al Deep Sleep
Adafruit_BME680 bme(&Wire);       // Objeto del sensor, comunicacion por I2C

// 5. DECLARACION DE SUBRUTINAS Y/O FUNCIONES
void print_wakeup_reason() {
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch (wakeup_reason) {
    case ESP_SLEEP_WAKEUP_EXT0:     Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1:     Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER:    Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD: Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP:      Serial.println("Wakeup caused by ULP program"); break;
    default:                        Serial.printf("Wakeup was not caused by deep sleep: %d\n", wakeup_reason); break;
  }
}

bool iniciarSensor() {
  if (!bme.begin()) {
    return false;
  }

  // Configuracion de sobremuestreo y filtro, valores recomendados por Bosch
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150);  // Calentador a 320 grados C durante 150 ms

  return true;
}

void leerSensor() {
  if (!bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }

  Serial.print("Temperature = ");
  Serial.print(bme.temperature);
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(bme.pressure / 100.0);
  Serial.println(" hPa");

  Serial.print("Humidity = ");
  Serial.print(bme.humidity);
  Serial.println(" %");

  Serial.print("Gas = ");
  Serial.print(bme.gas_resistance / 1000.0);
  Serial.println(" KOhms");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");
}

void dormir() {
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) + " Seconds");

  Serial.println("Going to sleep now");
  Serial.flush();
  esp_deep_sleep_start();
}

// 6. CONFIGURACION INICIAL
void setup() {
  // CONFIGURACION DE PINES DE ENTRADA Y SALIDA
  // Los pines I2C no usan pinMode; los configura la libreria Wire

  // LIMPIEZA DE SALIDAS
  // No aplica: este programa no maneja salidas

  // COMUNICACIONES
  Serial.begin(115200);
  delay(1000);  //Take some time to open up the Serial Monitor
  Wire.begin(BME_SDA, BME_SCL);

  // CUERPO DEL PROGRAMA
  // En Deep Sleep todo el trabajo va aqui, porque el chip se reinicia en cada despertar
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  print_wakeup_reason();

  if (iniciarSensor()) {
    leerSensor();
  } else {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
  }

  dormir();

  Serial.println("This will never be printed");
}

// 7. FUNCION INFINITA PRINCIPAL
void loop() {
  //This is not going to be called
}