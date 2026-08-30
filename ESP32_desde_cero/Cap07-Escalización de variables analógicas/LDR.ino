// 1. DECLARAR LIBRERIAS
// #include <WiFi.h>

// 2. DEFINICIÓN O ETIQUETADO DE PINES DE ENTRADA Y SALIDA
#define LDR_PIN 34   // LDR conectado al GPIO 34 (ADC1)

// 3. DECLARACION DE CONSTANTES
const int OSCURO = 4095;   // Valor ADC en oscuridad total
const int LUZ    = 749;    // Valor ADC bajo luz directa

// 4. DECLARACION DE VARIABLES
int lecturaADC = 0;   // Lectura cruda del ADC
int luz        = 0;   // Nivel de luz escalizado (0 - 100%)

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
  lecturaADC = analogRead(LDR_PIN);                    // Leo el ADC crudo
  luz        = map(lecturaADC, OSCURO, LUZ, 0, 100);  // Escalo a porcentaje
  luz        = constrain(luz, 0, 100);                 // Limito entre 0 y 100

  Serial.print("ADC crudo: ");
  Serial.print(lecturaADC);
  Serial.print("  |  Luz: ");
  Serial.print(luz);
  Serial.println(" %");

  delay(500);   // Lectura cada 500ms
}