#include <SD.h>      // https://www.arduino.cc/reference/en/libraries/sd/
#include <SPI.h>     // https://www.arduino.cc/reference/en/language/functions/communication/spi/

const int iSpi_SS = 53;  // SPI SS Pin (Chip Select)

File sdFile;                           // File object

int iAirVal = 50; 
int iWatVal = 100;
bool xSdAvailable = false;

// ##################
// SD Init
// ##################
while(!Serial);
  xSdAvailable = SD.begin(iSpi_SS);
  delay(1000);

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
