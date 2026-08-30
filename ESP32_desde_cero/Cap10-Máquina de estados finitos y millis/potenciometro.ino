// 1. DECLARAR LIBRERIAS
// #include <WiFi.h>

// 2. DEFINICIÓN O ETIQUETADO DE PINES DE ENTRADA Y SALIDA
#define POT 34   // Potenciómetro al GPIO 34 (ADC1)

// 3. DECLARACION DE CONSTANTES
const unsigned long INTERVALO = 200;   // Intervalo de impresión: 200 segundo

// 4. DECLARACION DE VARIABLES
int lecturaADC  = 0;   // Lectura cruda del ADC
int porcentaje  = 0;   // Valor escalado (0 - 100%)
unsigned long tini = 0;   // Tiempo de inicio de la temporización

// 5. DECLARACION DE SUBRUTINAS Y/O FUNCIONES

// 6. CONFIGURACION INICIAL
void setup()
{
  // CONFIGURACION DE PINES DE ENTRADA Y SALIDA
  // Los pines analógicos no requieren pinMode()

  // LIMPIEZA DE SALIDAS

  // COMUNICACIONES
  Serial.begin(115200);

  tini = millis();   // Inicializo el temporizador
}

// 7. FUNCION INFINITA PRINCIPAL
void loop()
{
  unsigned long tstate = millis() - tini;   // Tiempo transcurrido

  if (tstate >= INTERVALO)   // ¿Pasó 200 milisegundo?
  {
    lecturaADC = analogRead(POT);
    porcentaje = map(lecturaADC, 0, 4095, 0, 100);

    Serial.print("Potenciómetro: ");
    Serial.print(porcentaje);
    Serial.println(" %");

    tini = millis();   // Reinicio el temporizador
  }
}