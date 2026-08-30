// 1. DECLARAR LIBRERIAS
// #include <WiFi.h>

// 2. DEFINICION DE ESTADOS DE LA MEF
#define ELOFF   0   // Estado LED Apagado
#define ELON    1   // Estado LED Encendido
#define EAEMG   2   // Estado Alerta Emergencia

// 3. DEFINICIÓN O ETIQUETADO DE PINES DE ENTRADA Y SALIDA
#define L1    22   // LED principal — GPIO 22
#define L2    23   // LED alerta rojo — GPIO 23
#define BEMG  0   // Switch de emergencia 

// 4. DECLARACION DE CONSTANTES
const unsigned long T_PARPADEO = 500;   // Tiempo de parpadeo: 500 ms

// 5. DECLARACION DE VARIABLES
unsigned int state = ELOFF;   // Estado actual — arranca en ELOFF
unsigned long tini = 0;   // Tiempo de inicio de la temporización

// 6. DECLARACION DE SUBRUTINAS Y/O FUNCIONES

// 7. CONFIGURACION INICIAL
void setup()
{
  // CONFIGURACION DE PINES DE ENTRADA Y SALIDA
  pinMode(L1,   OUTPUT);
  pinMode(L2,   OUTPUT);
  pinMode(BEMG, INPUT_PULLDOWN);   // Switch activa en HIGH

  // LIMPIEZA DE SALIDAS
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);

  // COMUNICACIONES
  Serial.begin(115200);

  // INICIALIZACION DEL TEMPORIZADOR
  tini = millis();
}

// 8. FUNCION INFINITA PRINCIPAL
void loop()
{
  unsigned long tstate = millis() - tini;   // Tiempo en el estado actual

  switch (state)
  {
    // ESTADO ELOFF: LED apagado
    case ELOFF:
      digitalWrite(L1, LOW);
      digitalWrite(L2, LOW);

      if (tstate >= T_PARPADEO)           // Pasó 0.5 seg → encender
      {
        state = ELON;
        tini  = millis();
      }
      else if (digitalRead(BEMG) == HIGH) // Emergencia → alerta
      {
        state = EAEMG;
        tini  = millis();
      }
      break;

    // ESTADO ELON: LED encendido 
    case ELON:
      digitalWrite(L1, HIGH);
      digitalWrite(L2, LOW);

      if (tstate >= T_PARPADEO)           // Pasó 0.5 seg → apagar
      {
        state = ELOFF;
        tini  = millis();
      }
      else if (digitalRead(BEMG) == HIGH) // Emergencia → alerta
      {
        state = EAEMG;
        tini  = millis();
      }
      break;

    //  ESTADO EAEMG: Alerta emergencia 
    case EAEMG:
      digitalWrite(L1, LOW);
      digitalWrite(L2, HIGH);

      if (digitalRead(BEMG) == LOW)       // Emergencia liberada → volver
      {
        state = ELOFF;
        tini  = millis();
      }
      break;
  }
}