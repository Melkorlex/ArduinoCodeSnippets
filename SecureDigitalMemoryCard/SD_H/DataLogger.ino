  #include <SD.h>      // https://www.arduino.cc/reference/en/libraries/sd/
  #include <SPI.h>     // https://www.arduino.cc/reference/en/language/functions/communication/spi/
  const int iSpi_SS = 53;  // SPI SS Pin (Chip Select)

  File sdFile;                            // File object
  bool xSdAvailable = false; 
  bool xCsvDatLogInit = true;   
  bool xRtcAvailable = false;     // No function in this example
  byte byValue1 = 10; 
  byte byValue2 = 25; 



void sdDataLogger(){
  sdFile = SD.open(str_dataLogFilePath, FILE_WRITE);
  if(sdFile){
    if(xCsvDatLogInit){
      sdFile.println("time;value1;value2");  // take note the --> ; between the values. This will create a new column
      xCsvDatLogInit = false;

    }
    
    // For this i initialising an RTC Module in an other file. 
    // For RTC, take a look here: (COMING SOON)
    
    
    if(xRtcAvailable){
      // dtNow = rtc.now();
      // delay(100);
      // sdFile.print((dtNow.year(),DEC)+ String("-") + (dtNow.month(),DEC) + String("-") + (dtNow.day(),DEC)  );
      // sdFile.print((dtNow.hour(),DEC) + String("-") + (dtNow.minute(),DEC) + String("-") + (dtNow.second(),DEC));
    }
    // If there is no RTC module the operating time will be logged
      else{
        lTimer = millis();
        sdFile.print(String(lTimer));
      }
    sdFile.print(";");
    sdFile.print(String(byValue1));
    sdFile.print(";");
    sdFile.print(String(byValue2));
    sdFile.print(";");

    // TODO: Hier noch weitermachen




  }

  sdFile.close();
}
