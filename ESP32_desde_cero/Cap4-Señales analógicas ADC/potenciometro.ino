// 1. DECLARAR LIBRERIAS
// #include <WiFi.h>

// 2. DEFINICIÓN O ETIQUETADO DE PINES DE ENTRADA Y SALIDA
#define POT 34   // Potenciómetro conectado al GPIO 34 (ADC1)

// 3. DECLARACION DE CONSTANTES

// 4. DECLARACION DE VARIABLES
int valorADC = 0;   // Variable para almacenar la lectura del ADC

// 5. DECLARACION DE SUBRUTINAS Y/O FUNCIONES

// 6. CONFIGURACION INICIAL
void setup()
{
  // CONFIGURACION DE PINES DE ENTRADA Y SALIDA
  // Los pines analógicos no requieren pinMode()

  // LIMPIEZA DE SALIDAS

  // COMUNICACIONES
  Serial.begin(115200);   // Inicializo comunicación serial a 115200 baudios
}

// 7. FUNCION INFINITA PRINCIPAL
void loop()
{
  valorADC = analogRead(POT);          // Leo el valor del ADC (0 - 4095)
  Serial.println(valorADC);            // Envío el valor al monitor serial
  delay(200);                          // Espero 200ms entre lecturas
}