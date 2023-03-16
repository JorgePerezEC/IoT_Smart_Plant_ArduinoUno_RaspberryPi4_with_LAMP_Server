/* 
PROYECTO 1 BIMESTRE - SISTEMAS IOT - ESCUELA POLITÉCNICA NACIONAL
             
 DESCRIPCIÓN: 
 ----------------------------------------------------------------------- 
Implementation of a system that supports the care of a plant with automatic
irrigation using Arduino Uno hardware automatic irrigation using Arduino Uno
hardware and different sensors, also allows the collection of data from the
sensors and actions performed in the system through the Raspberry Pi the 
system through the Raspberry Pi OS, then stores the data in a LAMP server 
on Linux.
 ----------------------------------------------------------------------- */


// Librerias
#include <DHT.h>

#define DHTPIN 2  // pin connected to DHT11 sensor
#define DHTTYPE DHT11

const int higrometerSensorPin = A0;
const int Bomba = 10;   //Pin de la bomba de agua
const int Buzz = 5;     //Pin de la bomba de agua
const int LighSns = A5;     //Pin del sensor de luz
const int Trigger = 3;  //Pin digital 2 para el Trigger del sensor
const int Echo = 4;     //Pin digital 3 para el Echo del sensor
String displayString;   // Variable para concatenar texto

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  //Config ultrasonico
  pinMode(Trigger, OUTPUT);    //pin como salida
  pinMode(Echo, INPUT);        //pin como entrada
  digitalWrite(Trigger, LOW);  //Inicializamos el pin con 0
  //Config higrometer
  pinMode(higrometerSensorPin, INPUT);
  //Buzzer Config
  pinMode(Buzz, OUTPUT);      // Fija el pin 5 como salida para el buzzer
  //Bomba Config
  pinMode(Bomba, OUTPUT);
  digitalWrite(Bomba, HIGH);

  delay(2500);  // wait for initializing
  dht.begin();  // initialize DHT11 the temperature and humidity sensor

  //MenuBanner();
}

void loop() {

  SensorsAllFnc();

}


// SENSORS FUNCTIONS
void SensorsAllFnc() {

  
  //Higrometer Sensor-To measure plant humidity ************

  int almacenador = analogRead(higrometerSensorPin);
  int humedadHigro = 125 - (almacenador / 10.23);  // Valor de humedad del higrometro

  //*******************************************
  //Light Sensor-To measure ambient light ************
  int lightValue = analogRead(A5);  //Light=28  Dark=1021
  //*******************************************
  

  //DHT11 Sensor *************************************

  float humiDHT = dht.readHumidity();  // read humidity
  float tempCDHT = dht.readTemperature();
  if (isnan(humiDHT) || isnan(tempCDHT)) {
    displayString = "Error de lectura";
    tempCDHT=25.56;
    humiDHT = 67.0;
  } 
  //*******************************************

  //Ultrasonic Sensor-To measure the water level ************

  long t;   //tiempo que demora en llegar el eco
  float d;  //distancia en centimetros

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);  //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);

  t = pulseIn(Echo, HIGH);  //obtenemos el ancho del pulso
  d = t / 59;               //escalamos el tiempo a una distancia en cm
  float vol = 830-(7.5*8.5*d);  //nivel de agua en ml o cm3 (Volumen del recipiente)

  //*******************************************
  //Condiciones

  //Bajo nivel de agua
  if(vol<=300){
    //Serial.print("Buzzer");
    tone(5, 261.63, 250);      // Lanza señal a 261,63Hz por el pin 3 durante 250ms.
    delay(500);
    tone(5, 261.63, 250);      // Lanza señal a 261,63Hz por el pin 3 durante 250ms.
    delay(500);
    tone(5, 261.63, 250);      // Lanza señal a 261,63Hz por el pin 3 durante 250ms.
    delay(500);
    tone(5, 261.63, 250);      // Lanza señal a 261,63Hz por el pin 3 durante 250ms.
    delay(500);
    tone(5, 261.63, 250);      // Lanza señal a 261,63Hz por el pin 3 durante 250ms.
    //Se envian datos a la DB
    Serial.print("tblAlarmaWater");
    Serial.print(" ");
    Serial.print("Nivel_de_agua_del_contenedor_insuficiente");
    Serial.print(" ");
    Serial.print(vol);  //Enviamos serialmente el valor de la distancia
    Serial.print(" ");
    Serial.println("");
  }
  //Bajo nivel de humedad en la planta
  if(humedadHigro<=65){
    //Se riega la planta durante 5 seg
    digitalWrite(Bomba, LOW);
    delay(5000);
    digitalWrite(Bomba, HIGH);
    //Send Data tblBombaAguaData
    Serial.print("tblBombaAguaData");
    Serial.print(" ");
    Serial.print("Higrometer_sensor_low_humidity");
    Serial.print(" ");
    Serial.print(tempCDHT);
    Serial.print(" ");
    Serial.print(humedadHigro);
    Serial.print(" ");
    Serial.print(vol);  //Enviamos serialmente el valor de la distancia
    Serial.print(" ");
    Serial.print(lightValue);
    Serial.println("");
  }
  //Alta temperatura DHT11 Sensor
  if(tempCDHT>=29){
    //Se riega la planta durante 5 seg
    digitalWrite(Bomba, LOW);
    delay(5000);
    digitalWrite(Bomba, HIGH);
    //Send Data tblBombaAguaData
    Serial.print("tblBombaAguaData");
    Serial.print(" ");
    Serial.print("DHT11_sensor_high_temperature");
    Serial.print(" ");
    Serial.print(tempCDHT);
    Serial.print(" ");
    Serial.print(humedadHigro);
    Serial.print(" ");
    Serial.print(vol);  //Enviamos serialmente el valor de la distancia
    Serial.print(" ");
    Serial.print(lightValue);
    Serial.println("");
  }
  //Envío de datos a la tblSensores cada 20 segundos
  delay(20000);
  //Send Data tblSensores
  Serial.print("tblSensores");
  Serial.print(" ");
  Serial.print(humedadHigro);
  Serial.print(" ");
  Serial.print(tempCDHT);
  Serial.print(" ");
  Serial.print(humiDHT);
  Serial.print(" ");
  Serial.print(vol);  //Enviamos serialmente el valor de la distancia
  Serial.print(" ");
  Serial.print(lightValue);
  Serial.println("");
}
