// CODIGO DE CALIBRACION - Solo para obtener valores extremos
#define SENSOR_PIN 34

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  Serial.println(analogRead(SENSOR_PIN));
  delay(500);
}