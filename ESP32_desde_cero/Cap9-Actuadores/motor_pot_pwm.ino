// 1. DECLARAR LIBRERIAS

// 2. DEFINICIÓN O ETIQUETADO DE PINES DE ENTRADA Y SALIDA
#define POT    32   // Potenciómetro conectado al GPIO 32 (ADC1)
#define MOTOR   5   // Señal PWM al módulo MOSFET / transistor — GPIO 5

// 3. DECLARACION DE CONSTANTES
const int  FREQ_PWM = 500;  // Frecuencia PWM en Hz
const int  RES_PWM  = 8;     // Resolución 8 bits (0 - 255)

// 4. DECLARACION DE VARIABLES
int lecturaADC = 0;   // Lectura cruda del potenciómetro (0 - 4095)
int velocidad  = 0;   // Velocidad escalada para PWM (0 - 255)

// 5. DECLARACION DE SUBRUTINAS Y/O FUNCIONES

// 6. CONFIGURACION INICIAL
void setup()
{
  // CONFIGURACION DE PINES DE ENTRADA Y SALIDA
  ledcAttach(MOTOR, FREQ_PWM, RES_PWM);   // Configuro PWM en GPIO 5

  // LIMPIEZA DE SALIDAS
  ledcWrite(MOTOR, 0);   // Motor apagado al inicio

  // COMUNICACIONES
  Serial.begin(115200);
}

// 7. FUNCION INFINITA PRINCIPAL
void loop()
{
  lecturaADC = analogRead(POT);                      // Leo el potenciómetro
  velocidad  = map(lecturaADC, 0, 4095, 0, 255);    // Escalo al rango PWM
  ledcWrite(MOTOR, velocidad);                        // Envío PWM al motor

  Serial.print("ADC: ");
  Serial.print(lecturaADC);
  Serial.print("  |  Velocidad PWM: ");
  Serial.println(velocidad);

  delay(50);
}