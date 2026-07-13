// 1. DECLARAR LIBRERIAS
#include "DHT.h"

// 2. DEFINICIÓN O ETIQUETADO DE PINES DE ENTRADA Y SALIDA
#define DHTPIN 4  //pin data del sensor DHT conectado al pin  2
#define DHTTYPE DHT22

// 3. DECLARACION DE CONSTANTES

// 4. DECLARACION DE VARIABLES
float temperatura = 0;
float humedad = 0;
DHT dht(DHTPIN, DHTTYPE);  //variable (clase) DHT llamada dht iniciada en el pin DHTPIN y con el tipo DHTTYPE. Permite leer ls variables tem o hum

// 5. DECLARACION DE SUBRUTINAS Y/O FUNCIONES

// 6. CONFIGURACION INICIAL
void setup() {
  // CONFIGURACION DE PINES DE ENTRADA Y SALIDA. LAS ENTRADAS ANALOGAS NO SE CONFIGURAN
  // No se hace porque es bidireccional, es decir, con solo un pin entra y sale datos, por la libreria
  // LIMPIEZA DE SALIDAS

  // COMUNICACIONES
  Serial.begin(115200);
  dht.begin();  //inicializar sensor dht
}

// 7. FUNCION INFINITA PRINICIPAL
void loop() {

  delay(1000);  //retardo entre mediciones
  temperatura = dht.readTemperature();
  humedad = dht.readHumidity();
  Serial.print("temperatura: ");
  Serial.print(temperatura);
  Serial.print(" Humedad: ");
  Serial.println(humedad);
}