// 2. DEFINICIÓN O ETIQUETADO DE PINES DE ENTRADA Y SALIDA
#define RELE   5   // Señal de control al módulo de relé — GPIO 5
#define BOTON  0   // Botón BOOT del ESP32 (GPIO 0)

// 3. DECLARACION DE CONSTANTES

// 4. DECLARACION DE VARIABLES

// 5. DECLARACION DE SUBRUTINAS Y/O FUNCIONES

// 6. CONFIGURACION INICIAL
void setup()
{
  // CONFIGURACION DE PINES DE ENTRADA Y SALIDA
  pinMode(RELE, OUTPUT);
  pinMode(BOTON, INPUT_PULLUP);   // BOOT activa con pull-up interno

  // LIMPIEZA DE SALIDAS
  digitalWrite(RELE, LOW);        // Relé desactivado — foco apagado

  // COMUNICACIONES
  Serial.begin(115200);
}

// 7. FUNCION INFINITA PRINCIPAL
void loop()
{
  if (digitalRead(BOTON) == LOW)   // Botón presionado — LOW por pull-up
  {
    digitalWrite(RELE, HIGH);      // Activa el relé — foco encendido
    Serial.println("Foco: ENCENDIDO");
  }
  else
  {
    digitalWrite(RELE, LOW);       // Desactiva el relé — foco apagado
    Serial.println("Foco: APAGADO");
  }
  delay(100);
}
