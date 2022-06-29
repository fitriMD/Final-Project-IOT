#include <Arduino.h>
#include "DHT.h"  //Memasukan Library DHT ke Program 
#define DHTPIN 2  //menggunakan pin 2 untuk pemasangan sensornya
#define DHTTYPE DHT11 //memilih tipe DHT11, bisa diubah menjadi DHT22, DHT21

DHT dht(DHTPIN, DHTTYPE);  //setting pin yang dipilih dan tipe DHT
int sensorPin = A0;  // pin sensor
int powerPin = D6;    // untuk pengganti VCC
int LEDM = D1;
int LEDK = D2;
int LEDH = D3;

String temp;
String hum;
String tanah;

void setup() {
  // jadikan pin power sebagai output
  pinMode(powerPin, OUTPUT);
  // default bernilai LOW
  digitalWrite(powerPin, LOW);
  // mulai komunikasi serial
  Serial.begin(115200);
  dht.begin();
  pinMode(LEDM, OUTPUT);
  pinMode(LEDK, OUTPUT);
  pinMode(LEDH, OUTPUT);
}

void loop() {
  float kelembaban = dht.readHumidity();
  float suhu = dht.readTemperature();

  temp = String(suhu);
  hum = String(kelembaban);
  tanah = String(bacaSensor());
  Serial.print(hum);
  Serial.print(",");
  Serial.print(temp);
  Serial.print(",");
  Serial.println(tanah);
//  Serial.print("Nilai kelembaban Tanah: ");
//  Serial.println(bacaSensor());
//  Serial.print("Suhu : ");
//  Serial.println(suhu);
//  Serial.print("Kelembapan : ");
//  Serial.println(kelembaban);
  // baca setiap 3 detik

  if (suhu > 25 && suhu < 30)
  {
    if(bacaSensor() > 300){
      digitalWrite(LEDM, LOW); // LED nyala
      digitalWrite(LEDK, HIGH); // LED mati
      digitalWrite(LEDH, LOW); 
    }
    else {
      digitalWrite(LEDM, HIGH); // LED nyala
      digitalWrite(LEDK, LOW); // LED mati
      digitalWrite(LEDH, LOW);
    }
  }
  else if (suhu <= 25)
  {
    digitalWrite(LEDM, LOW); // LED nyala
    digitalWrite(LEDK, LOW); // LED mati
    digitalWrite(LEDH, HIGH);
  }
  else if (suhu > 30 || bacaSensor() < 300)
  {
    digitalWrite(LEDM, HIGH); // LED nyala
    digitalWrite(LEDK, LOW); // LED mati
    digitalWrite(LEDH, LOW);
  }
  delay(100);
}

int bacaSensor() {
  // hidupkan power
  digitalWrite(powerPin, HIGH);
  delay(3000);
  // baca nilai analog dari sensor
  int nilaiSensor = analogRead(sensorPin);
  digitalWrite(powerPin, LOW);
  // makin lembab maka makin tinggi nilai outputnya
  return 1023 - nilaiSensor;
}
