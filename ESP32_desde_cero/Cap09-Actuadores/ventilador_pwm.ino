// 1. DECLARAR LIBRERIAS
// #include <WiFi.h>

// 2. DEFINICIÓN O ETIQUETADO DE PINES DE ENTRADA Y SALIDA
#define VENTILADOR 5   // Señal PWM al módulo MOSFET — GPIO 5

// 3. DECLARACION DE CONSTANTES
const int FREQ_PWM  = 5000;  // Frecuencia PWM en Hz
const int RES_PWM   = 8;     // Resolución 8 bits (0 - 255)
const int PASO      = 5;     // Incremento de velocidad por ciclo
const int T_BAJO    = 3000;  // Tiempo a baja velocidad (30%) en ms
const int T_MEDIO   = 3000;  // Tiempo a velocidad media (60%) en ms
const int T_ALTO    = 3000;  // Tiempo a máxima velocidad (100%) en ms

// 4. DECLARACION DE VARIABLES

// 5. DECLARACION DE SUBRUTINAS Y/O FUNCIONES

// 6. CONFIGURACION INICIAL
void setup()
{
  ledcAttach(VENTILADOR, FREQ_PWM, RES_PWM);
  ledcWrite(VENTILADOR, 0);   // Ventilador apagado al inicio

  Serial.begin(115200);
}

// 7. FUNCION INFINITA PRINCIPAL
void loop()
{
  // Velocidad baja — 30%
  ledcWrite(VENTILADOR, 76);
  Serial.println("Velocidad: BAJA (30%)");
  delay(T_BAJO);

  // Velocidad media — 60%
  ledcWrite(VENTILADOR, 153);
  Serial.println("Velocidad: MEDIA (60%)");
  delay(T_MEDIO);

  // Velocidad máxima — 100%
  ledcWrite(VENTILADOR, 255);
  Serial.println("Velocidad: MAXIMA (100%)");
  delay(T_ALTO);
}