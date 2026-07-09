// 1. DECLARAR LIBRERIAS
// #include <WiFi.h>

// 2. DEFINICIÓN O ETIQUETADO DE PINES DE ENTRADA Y SALIDA
#define LED_DAC 25   // LED conectado al GPIO 25 (DAC Canal 1)

// 3. DECLARACION DE CONSTANTES
const int PASO      = 5;    // Incremento por ciclo (0 - 255)
const int RETARDO   = 50;   // Tiempo entre cada paso en milisegundos

// 4. DECLARACION DE VARIABLES
int nivelDAC = 0;   // Nivel actual del DAC (0 - 255)

// 5. DECLARACION DE SUBRUTINAS Y/O FUNCIONES

// 6. CONFIGURACION INICIAL
void setup()
{
  // CONFIGURACION DE PINES DE ENTRADA Y SALIDA
  // El DAC no requiere pinMode()

  // LIMPIEZA DE SALIDAS
  dacWrite(LED_DAC, 0);   // Inicio el LED apagado

  // COMUNICACIONES
  Serial.begin(115200);
}

// 7. FUNCION INFINITA PRINCIPAL
void loop()
{
  // Subida: de 0 a 255
  for (nivelDAC = 0; nivelDAC <= 255; nivelDAC += PASO)
  {
    dacWrite(LED_DAC, nivelDAC);   // Escribo el nivel en el DAC
    Serial.println(nivelDAC);      // Muestro el valor en el monitor serial
    delay(RETARDO);
  }

  // Bajada: de 255 a 0
  for (nivelDAC = 255; nivelDAC >= 0; nivelDAC -= PASO)
  {
    dacWrite(LED_DAC, nivelDAC);
    Serial.println(nivelDAC);
    delay(RETARDO);
  }
}