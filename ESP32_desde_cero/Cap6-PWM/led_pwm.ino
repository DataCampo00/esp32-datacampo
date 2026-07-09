// 1. DECLARAR LIBRERIAS
// #include <WiFi.h>

// 2. DEFINICIÓN O ETIQUETADO DE PINES DE ENTRADA Y SALIDA
#define LED_PWM 5   // LED conectado al GPIO 5

// 3. DECLARACION DE CONSTANTES
const int  FRECUENCIA  = 5000;  // Frecuencia PWM en Hz
const int  RESOLUCION  = 8;     // Resolución en bits (0 - 255)
const int  PASO        = 5;     // Incremento por ciclo
const int  RETARDO     = 20;    // Tiempo entre cada paso en ms

// 4. DECLARACION DE VARIABLES
int nivelPWM = 0;   // Nivel actual del duty cycle (0 - 255)

// 5. DECLARACION DE SUBRUTINAS Y/O FUNCIONES

// 6. CONFIGURACION INICIAL
void setup()
{
  // CONFIGURACION DE PINES DE ENTRADA Y SALIDA
  ledcAttach(LED_PWM, FRECUENCIA, RESOLUCION);
  // Configura el GPIO 5 como salida PWM
  // Frecuencia: 5000 Hz
  // Resolución: 8 bits (valores de 0 a 255)
  // El canal se asigna automáticamente

  // LIMPIEZA DE SALIDAS
  ledcWrite(LED_PWM, 0);   // Inicio el LED apagado

  // COMUNICACIONES
  Serial.begin(115200);
}

// 7. FUNCION INFINITA PRINCIPAL
void loop()
{
  // Subida: de 0 a 255
  for (nivelPWM = 0; nivelPWM <= 255; nivelPWM += PASO)
  {
    ledcWrite(LED_PWM, nivelPWM);   // Escribo el duty cycle
    Serial.print("Duty cycle: ");
    Serial.println(nivelPWM);
    delay(RETARDO);
  }

  // Bajada: de 255 a 0
  for (nivelPWM = 255; nivelPWM >= 0; nivelPWM -= PASO)
  {
    ledcWrite(LED_PWM, nivelPWM);
    Serial.print("Duty cycle: ");
    Serial.println(nivelPWM);
    delay(RETARDO);
  }
}