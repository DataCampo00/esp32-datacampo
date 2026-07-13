// Librerias
#include "Adafruit_SI1145.h"

// Constantes
#define TLECT 1000  // Constante tiempo de lectura 1000 ms

// Variables
unsigned long tini = 0;                            // Var para el tiempo inicial
float vis = 0, uv = 0, ir = 0;                     // Vars para los valores del sensor SI1145
Adafruit_SI1145 SensorSI1145 = Adafruit_SI1145();  // Var para la clase SensorSI1145

// Subrutinas y funciones
void leerSensor() {
  vis = SensorSI1145.readVisible();
  uv = SensorSI1145.readUV();
  ir = SensorSI1145.readIR();
  Serial.println("vis: " + String(vis) + " uv: " + String(uv) + " ir: " + String(ir));
}

// Configuración
void setup() {
  // 3. Comunicaciones
  Serial.begin(115200);
  SensorSI1145.begin();  // Inicio comms i2c con el sensor SI1145
  // (Opcional) Reset de tini
  tini = millis();
}

// Ejecución
void loop() {
  if (millis() - tini >= TLECT) {  // Si el tiempo relativo es mayor que el TLECT
    leerSensor();                  // Leo el sensor
    tini = millis();               // Reseteo el tini para volver a temporizar desde 0
  }
}