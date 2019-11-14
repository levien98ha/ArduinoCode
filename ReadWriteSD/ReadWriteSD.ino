#include <SD.h>


#include <SdFat.h>

//ho tro truy xuat the SD
Sd2Card card;
//ho tro phan vung FAT16 va FAT32
SdVolume volume;
SdFile root;
//cho phep truy xuat tam tin 
SdFile file;

//hien thi loi trong qua trinh truy xuat du lieu
#define error(s) error_P(PSTR(s))

void error_P(const char* str){
  PgmPrint("error:");
  SerialPrintln_P(str);
  if(card.errorCode()) {
    PgmPrint("SD error: ");
    Serial.print(card.errorCode(),HEX);
    Serial.print(',');
    Serial.print(card.errorData(),HEX);
  }
  while(1);
}

//ghi 2 byte
void writeCRLF(SdFile& f){
f.write((uint8_t*)"\r\n",2);}

//ghi 4 byte
void writeNumber(SdFile& f, uint32_t n){
  uint8_t buf[10];
  uint8_t i = 0;
  do{
    i++;
    buf[sizeof(buf) - i] = n%10 + '0';
    n /= 10;
  }
  while(n);
  f.write(&buf[sizeof(buf) - 1], i);
}

void writeString(SdFile& f, char *str){
  uint8_t n;
  for(n = 0; str[n]; n++){
    f.write((uint8_t *)str, n);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Type any character to start");
  while(!Serial.available());


//thong bao loi khi lam viec voi the
  if(!card.init(SPI_HALF_SPEED)) error("card.init failed");

  if(!volume.init(&card)) error("volume.init failed");

  if(!root.openRoot(&volume)) error("openRoot failed");
//  

//mo mot tap tin
  char name[] = "TESTFILE.TXT";
  file.open(&root, name, O_CREAT | O_EXCL | O_WRITE);


  file.timestamp(2,2019,12,25,12,34,56);

  for(uint8_t i = 0; i <10; i++){
    writeString(file, "Line: ");
    writeNumber(file,i);
    writeString(file, " Write test.");
    writeCRLF(file);
  }

  Serial.println("File Created");

  if(file.open(&root, name, O_READ)){
    Serial.println(name);
  }
  else{
    error("file.open failed");
  }
  Serial.println();
  int16_t character;
  while ((character = file.read()) > 0) Serial.print("\nDone");
}

void loop() {
  // put your main code here, to run repeatedly:

}
