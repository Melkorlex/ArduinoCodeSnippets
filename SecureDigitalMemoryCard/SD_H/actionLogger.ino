// With this scetch snipped you are able to document any actions of your arduino (failures, important code actions and so on)

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

File sdFile;                            // File object
bool xRtcAvailable = false;        // dummy variable for RTC. If you want to use the rtc timestamp you have to init it --> take a look here: 
bool xCsvActLogInit = true;      

void setup() {
  pinMode(iSpi_SS, OUTPUT);
  sdInit();
}

void loop() {
 sdActionLogger(); 
 delay(1000);
}



// ##################
// SD init
// ##################
void sdInit(){
  Serial.begin(9600);
  while(!Serial);

  xSdAvailable = SD.begin(iSpi_SS);
  delay(1000);

  // Check directory structure, create it if it's not existing
  if(!SD.exists("log")){
    Serial.print("-log- dir not exist... create...");
    SD.mkdir("log");
    delay(500);

    while(!SD.exists(str_ActLogFilePath)){
      Serial.print("-ActLogFile- dir not exist... create...");
      sdFile = SD.open(str_ActLogFilePath, FILE_WRITE);
      sdFile.close();
    }
  }

// ##################
// save Scetch actions and/or error messages in txt file
// ##################

void sdActionLogger(String actMessage, String additionalInfo){
  sdFile = SD.open(str_ActLogFilePath, FILE_WRITE);

  if(sdFile){
    // initial creation of csv header file
    if(xCsvActLogInit){
      sdFile.println("Date or elapsed Time(ms);Message;Additional Information");   // next column, /t or ; is also possible
      xCsvActLogInit = false;
    }
    // if rtc module is detected, then use rtc time, otherwise take the arduino system time
    if(xRtcAvailable){
      /*dtNow = rtc.now();
      delay(100);
      sdFile.print((dtNow.year(), DEC) + String("-") + (dtNow.month(), DEC) + String("-") + (dtNow.day(), DEC) + String("-"));
      sdFile.print((dtNow.hour(), DEC) + String("-") + (dtNow.minute(), DEC) + String("-") + (dtNow.second(), DEC) + String(" "));
      */
    }
    else{
      lTimer = millis();
      sdFile.print(String(lTimer));
    }
    
    sdFile.print(";");
    sdFile.print(String(actMessage));
    sdFile.print(";");
    sdFile.println(String(additionalInfo));    
    sdFile.close();
    delay(200);
  }
}
