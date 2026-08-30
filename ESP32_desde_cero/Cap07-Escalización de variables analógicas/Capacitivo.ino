// 1. DECLARAR LIBRERIAS
// #include <WiFi.h>

// 2. DEFINICIÓN O ETIQUETADO DE PINES DE ENTRADA Y SALIDA
#define HUMEDAD_PIN 34   // Sensor de humedad conectado al GPIO 34 (ADC1)

// 3. DECLARACION DE CONSTANTES
const int SECO  = 2840;   // Valor ADC en aire (suelo seco)
const int MOJADO = 749;  // Valor ADC en agua (suelo saturado)

// 4. DECLARACION DE VARIABLES
int   lecturaADC = 0;    // Lectura cruda del ADC (0 - 4095)
int   humedad    = 0;    // Humedad escalizada (0 - 100%)

// 5. DECLARACION DE SUBRUTINAS Y/O FUNCIONES

// 6. CONFIGURACION INICIAL
void setup()
{
  // CONFIGURACION DE PINES DE ENTRADA Y SALIDA
  // Los pines analógicos no requieren pinMode()

  // LIMPIEZA DE SALIDAS

  // COMUNICACIONES
  Serial.begin(115200);
}

// 7. FUNCION INFINITA PRINCIPAL
void loop()
{
  lecturaADC = analogRead(HUMEDAD_PIN);                    // Leo el ADC crudo
  humedad    = map(lecturaADC, SECO, MOJADO, 0, 100);     // Escalo a porcentaje
  humedad    = constrain(humedad, 0, 100);                 // Limito entre 0 y 100

  Serial.print("ADC crudo: ");
  Serial.print(lecturaADC);
  Serial.print("  |  Humedad: ");
  Serial.print(humedad);
  Serial.println(" %");

  delay(1000);   // Lectura cada 1 segundo
}