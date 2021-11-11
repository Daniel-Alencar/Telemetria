/*
  The model file will be:
  Time, Altitude, Temperature, Acelerometer
  10042.101, 42.1, 42.1, 42.1

*/

#include <SPI.h>
#include <SD.h>

#define CS_PIN 8
File myFile;

void setup() {
  Serial.begin(9600);

  pinMode(CS_PIN, OUTPUT);

  Serial.print("Initializing SD card...");
  while (!SD.begin(CS_PIN)) {
    Serial.println("Initialization failed!");
  }
  Serial.println("Initialization done.");


  myFile = SD.open("data.txt", FILE_WRITE);

  if(myFile) {
    Serial.print("Writing...");

    myFile.println("Time, Altitude, Temperature, Acelerometer");
    myFile.close();

    Serial.println("Done.");
  } else {
    Serial.println("Error opening data.txt");
  }
}

void writeOnSD(float time, float altitude, float temperature, float acelerometer) {
  String str;
  myFile = SD.open("data.txt", FILE_WRITE);

  if(myFile) {
    Serial.print("Writing...");

    str = String(time,3) + "," + String(altitude,3) + "," + String(temperature,3) + "," + String(acelerometer,3) + "\n";

    Serial.println(str);
    myFile.println(str);
    myFile.close();

    Serial.println("Done.");
  } else {
    Serial.println("Error opening data.txt");
  }
}

// 60000000 (valor máximo para millis())

float altitude() {
  return 42.1;
}

float temperature() {
  return 42.1;
}

float acelerometer() {
  return 42.1;
}

void loop() {
  writeOnSD(millis() / 1000.0, altitude(), temperature(), acelerometer());
  delay(1000);
}
