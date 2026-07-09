// 1. DECLARAR LIBRERIAS
// #include <WiFi.h>

// 2. DEFINICIÓN O ETIQUETADO DE PINES DE ENTRADA Y SALIDA
#define L1 5   // LED externo conectado al GPIO 5
#define B1 4   // Botón conectado al GPIO 4

// 3. DECLARACION DE CONSTANTES

// 4. DECLARACION DE VARIABLES

// 5. DECLARACION DE SUBRUTINAS Y/O FUNCIONES

// 6. CONFIGURACION INICIAL
void setup()
{
  // CONFIGURACION DE PINES DE ENTRADA Y SALIDA
  pinMode(L1, OUTPUT);          // GPIO 5 como salida
  pinMode(B1, INPUT_PULLDOWN);  // GPIO 4 como entrada con pull-down interno o pinMode(B1, INPUT); si pones resistencia

  // LIMPIEZA DE SALIDAS
  digitalWrite(L1, LOW);

  // COMUNICACIONES
  Serial.begin(115200);
}

// 7. FUNCION INFINITA PRINCIPAL
void loop()
{
  if (digitalRead(B1) == HIGH)   // Si el botón está presionado
  {
    digitalWrite(L1, HIGH);
    Serial.println("Botón PRESIONADO - LED ENCENDIDO");
  }
  else                           // Si el botón no está presionado
  {
    digitalWrite(L1, LOW);
    Serial.println("Botón LIBERADO - LED APAGADO");
  }

  delay(500); // Facilita la lectura en el Monitor Serie
}