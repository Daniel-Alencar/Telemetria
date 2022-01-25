#include <SPI.h>
#include <SD.h>

#define CS_PIN 8
File myFile;

bool settingsSD()
{
  if (SD.begin())
  {
    if (myFile)
    {
      myFile = SD.open("data.txt", FILE_WRITE);
      myFile.println("TEMPO, ALTITUDE, AltitudeFk, AY, Temperatura");
      myFile.close();
      return true;
    }
  }
  return false;
}

void writeOnSD(String message)
{
  myFile = SD.open("data.txt", FILE_WRITE);

  if (myFile)
  {
    myFile.println(str);
    myFile.close();
  }
}
