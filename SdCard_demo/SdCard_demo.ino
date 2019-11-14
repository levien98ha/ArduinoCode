    /////////////////////////////////////////////////////////////////
   //              Arduino SD Card Tutorial     v1.00             //
  //       Get the latest version of the code here:              //
 //         http://educ8s.tv/arduino-sd-card-tutorial           //
/////////////////////////////////////////////////////////////////
#include <SD.h>
#include <SPI.h>

int CS_PIN = 10;

File file;

void setup()
{

  Serial.begin(9600);

  initializeSD();
  createFile("test.txt");
  writeToFile("This is sample text!");
  closeFile();
  //openFile("prefs.txt");
  Serial.println(readLine());
  Serial.println(readLine());
//  closeFile();
}

void loop()
{
}


//check co SD hay khong
void initializeSD()
{
  Serial.println("Initializing SD card...");
  pinMode(CS_PIN, OUTPUT);

  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
}


//tao file
int createFile(char filename[])
{
  file = SD.open(filename, FILE_WRITE); //tao file name = filename

  if (file) //co file hay khong
  {
    Serial.println("File created successfully.");
    return 1;
  } else
  {
    Serial.println("Error while creating file.");
    return 0;
  }
}


//ghi vao the
int writeToFile(char text[])
{
  if (file) //neu co file
  {
    file.println(text); //ghi vao file
    Serial.println("Writing to file: ");
    Serial.println(text);
    return 1;
  } else
  {
    Serial.println("Couldn't write to file");
    return 0;
  }
}

//dong file
void closeFile()
{
  if (file)
  {
    file.close();
    Serial.println("File closed");
  }
}


//mo file de doc
int openFile(char filename[])
{
  file = SD.open(filename);
  if (file)
  {
    Serial.println("File opened with success!");
    return 1;
  } else
  {
    Serial.println("Error opening file...");
    return 0;
  }
}

//doc chuoi tu file de print ra serial
String readLine()
{
  String received = "";
  char ch;
  while (file.available())
  {
    ch = file.read();
    if (ch == '\n')
    {
      return String(received);
    }
    else
    {
      received += ch;
    }
  }
  return "";
}
