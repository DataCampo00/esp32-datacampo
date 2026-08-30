// 1. DECLARAR LIBRERIAS
// #include <WiFi.h>

// 2. DEFINICIÓN O ETIQUETADO DE PINES DE ENTRADA Y SALIDA
#define VALVULA  5    // Señal de control al módulo MOSFET / transistor
#define BOTON    0    // Botón BOOT del ESP32 (GPIO 0)

// 3. DECLARACION DE CONSTANTES

// 4. DECLARACION DE VARIABLES

// 5. DECLARACION DE SUBRUTINAS Y/O FUNCIONES

// 6. CONFIGURACION INICIAL
void setup()
{
  // CONFIGURACION DE PINES DE ENTRADA Y SALIDA
  pinMode(VALVULA, OUTPUT);
  pinMode(BOTON, INPUT_PULLUP);  // El botón BOOT usa pull-up interno

  // LIMPIEZA DE SALIDAS
  digitalWrite(VALVULA, LOW);    // Válvula cerrada al inicio

  // COMUNICACIONES
  Serial.begin(115200);
}

// 7. FUNCION INFINITA PRINCIPAL
void loop()
{
  if (digitalRead(BOTON) == LOW)   // BOOT activa en LOW por pull-up
  {
    digitalWrite(VALVULA, HIGH);   // Abre la válvula
    Serial.println("Válvula: ABIERTA");
  }
  else
  {
    digitalWrite(VALVULA, LOW);    // Cierra la válvula
    Serial.println("Válvula: CERRADA");
  }
  delay(100);
}