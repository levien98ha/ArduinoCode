#include <SPI.h>
#include <SD.h>

const byte csSD = 10;

File myFile;

void setup()
{
   Serial.begin(115200);
   initSD();

  // delete the file:

  SD.remove("test.txt");

  if (SD.exists("test.txt")) {
  } else {
  }
    /////////////////////////
  createFile("test.txt"); // tao file moi
}


void loop()
{
   if (Serial.available())
   {
      String incoming = Serial.readString();
      myFile = SD.open("test.txt", FILE_WRITE);
      if (myFile)
      {
         Serial.print("Writing to test.txt...");
         myFile.println(incoming);        
         myFile.close();
         Serial.println("done.");
      }
      else
      {
         // if the file didn't open, print an error:
         Serial.println("error opening test.txt");
      }
   }
}
//tao file
int createFile(char filename[])
{
  myFile = SD.open(filename, FILE_WRITE); //tao file name = filename

  if (myFile) //co file hay khong
  {
    Serial.println("File created successfully.");
    return 1;
  } else
  {
    Serial.println("Error while creating file.");
    return 0;
  }
}


void initSD()
{
   Serial.print("Initializing SD card...");
   if (!SD.begin(csSD))
   {
      Serial.println("initialization failed!");
      while (1);
   }
   Serial.println("initialization done.");
}
