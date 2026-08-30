// 1. DECLARAR LIBRERIAS
// #include <WiFi.h>

// 2. DEFINICIÓN O ETIQUETADO DE PINES DE ENTRADA Y SALIDA
#define LM35 34  // Sensor LM35 conectado al GPIO 34 (ADC1)

// 3. DECLARACION DE CONSTANTES
const float V_REF    = 3.3;    // Voltaje de referencia del ADC (3.3V)
const float ADC_RES  = 4095.0; // Resolución del ADC (12 bits = 4095 niveles)
const float mV_GRADO = 0.01;   // El LM35 genera 10mV por grado (0.01V/°C)

// 4. DECLARACION DE VARIABLES
int   valorADC   = 0;   // Lectura cruda del ADC (0 - 4095)
float voltaje    = 0.0; // Voltaje calculado en el pin (0 - 3.3V)
float temperatura = 0.0; // Temperatura calculada en grados Celsius

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
  valorADC    = analogRead(LM35);                  // Leo el ADC (0 - 4095)
  voltaje     = (valorADC * V_REF) / ADC_RES;      // Convierto ADC a voltaje
  temperatura = voltaje / mV_GRADO;                 // Convierto voltaje a °C

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  delay(500);   // Lectura cada 0.5 segundo
}