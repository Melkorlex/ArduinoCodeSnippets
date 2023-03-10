// ###########
// How to wire SD Card module
// ###########
/*
                Arduino UNO     Arduino MEGA      Arduino MKR      
VCC             3.3V or 5V      3.3V or 5V  	    3.3V 
CS (SS)         4               53                7
MOSI(COPI)      11              51                8
CLK(SCK)        13              52                9
MISO(CIPO)      12              50                10  
GND             GND             GND               GND
*/



// ###################
#include <SD.h>      // https://www.arduino.cc/reference/en/libraries/sd/
#include <SPI.h>     // https://www.arduino.cc/reference/en/language/functions/communication/spi/
const int iSpi_SS = 53;  // SPI SS Pin (CS == Chip Select / SS == Slave Select)


File sdFile;                           // File object

int iAirVal = 50; 
int iWatVal = 100;
bool xSdAvailable = false;
String str_persistentVarPath;

void setup() {
  pinMode(iSpi_SS, OUTPUT);
  sdInit();
}

void loop() {

}

// ##################
// SD Init
// ##################
void sdInit(){
  Serial.begin(9600);
  while(!Serial);

  xSdAvailable = SD.begin(iSpi_SS);
  delay(1000);

  if(!SD.exists("dat")){
    SD.mkdir("dat");
    delay(500);

    while(!SD.exists(str_persistentVarPath)){
      sdFile = SD.open(str_persistentVarPath, FILE_WRITE);
      sdFile.close();
    }
  }
}

// ##################
// The Function: Saving Var onto SD Card
// ##################

void sdPersistentVarsWrite(){
  sdFile = SD.open(str_persistentVarPath, O_READ | O_WRITE | O_CREAT); // https://arduino.stackexchange.com/questions/86626/how-can-i-delete-contents-of-an-sd-card-in-arduino 
  delay(100);
  if (sdFile){
    sdFile.print(String("iAirVal =")   + iAirVal + String("\n"));
    sdFile.print(String("iWatVal =")   + iWatVal + String("\n"));
    // Add so much variables as you want
    sdFile.close();
  }
  
  
// ##################
// The Function: Reading Variables from SD into Buffer
// ##################
void sdPersistentVarsRead(){

  nextionSplashScreen(true,"Lade persistente Variablen");
  sdFile = SD.open(str_persistentVarPath);
  if(sdFile){
    char cBuffer[40]; // <-- 40 ist der Speicherumfang der pro Zeile gebuffert werden kann
    byte byIndex = 0; 
    while(sdFile.available()){
      char c = sdFile.read();
      if (c == '\n' || c == '\r') {     // Check, ob <cr> oder <lf> vorhanden
      sdParseSaveBuffer(cBuffer);
      byIndex = 0; 
      cBuffer[byIndex] = '\0';          // Buffer NULL terminated 
      }
      else{
        cBuffer[byIndex++] = c; 
        cBuffer[byIndex]   = '\0';     // Buffer NULL terminated 
      }
    } 
    sdFile.close(); 
 
  }

}
  
// ##################
// The Function: Parsing Var from Buffer and write into the correct variable
// ##################
  void sdParseSaveBuffer(char *cReadBuff){
    char *cName = strtok(cReadBuff, " =");       //Name aus der Zeile lesen und " =" separieren
    if(cName){
      char *cJunk = strtok(NULL, " ");      // Leerzeichen verwerfen
      if (cJunk){
        char *cVal  = strtok(NULL, " ");
        if (cVal){
          // Vergleich der Werte und schreiben in die Variable
          // "atoi" dient der Konvertierung von Char to Int
          int iVal = atoi(cVal);
          if(strcmp(cName, "iAirVal"))
            iAirVal = iVal; 
          if(strcmp(cName, "iWatVal"))
            iWatVal = iVal;
          // .... 
          // .... if you write more variables on SD, you also have to add the variables here
        }
      }
    }
}
