#include <SPI.h>
#include <SD.h>

#define CS_PIN 10
File myFile;

bool settingsSD()
{
  if (SD.begin())
  {
    myFile = SD.open("data.txt", FILE_WRITE);
    if(myFile)
    {
      myFile.println("Altitude(m), AltitudeFK, Velocidade(m/s), VelocidadeFK, Paraquedas");
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
    myFile.println(message);
    myFile.close();
  }
}
