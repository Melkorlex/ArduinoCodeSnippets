// With this scetch snipped you are able to document any actions of your arduino (failures, important code actions and so on)



#include <SD.h>      // https://www.arduino.cc/reference/en/libraries/sd/
#include <SPI.h>     // https://www.arduino.cc/reference/en/language/functions/communication/spi/
const int iSpi_SS = 53;  // SPI SS Pin (Chip Select)

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
