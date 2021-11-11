#include <SPI.h>
#include <SD.h>

#define CS_PIN 8
File myFile;

bool settingsSD() {
  if(SD.begin()) {
    if(myFile) {
      myFile = SD.open("data.txt", FILE_WRITE);
      myFile.println("TEMPO, ALTITUDE, AltitudeFk, AY, Temperatura");
      myFile.close();
      return true;
    }
  }
  return false;
}

void writeOnSD(float time, float altitude, float altitudeFk, float AY, float temperatura) {
  String str;
  myFile = SD.open("data.txt", FILE_WRITE);

  if(myFile) {
    str = String(time,2) + "," + String(altitude,2) + "," + String(altitudeFk,2) + "," + String(AY,2) + String(temperatura,2);

    myFile.println(str);
    myFile.close();
  }
}


