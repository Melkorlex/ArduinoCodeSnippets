// https://github.com/NorthernWidget/DS3231
#include <DS3231.h>   // https://github.com/NorthernWidget/DS3231
#include <Wire.h>
RTClib rtc;           // RTC Instance
DateTime dtNow;      // DateTime instance

bool xRtcAvailable;
String rtcGetTimeString();  

void rtcInit(){
  // https://forum.arduino.cc/t/checking-to-see-if-an-rtc-ds3231-is-present-and-running/550216/6 
  Serial.begin(9600);
  Wire.begin();
  delay(500);
  Wire.beginTransmission(0x68);
  Wire.write(0x0F);     // Statusregister, welches OSF Flag an 7. bit stelle enthält
  Wire.endTransmission();
  Wire.requestFrom(0x68,1);   // Request, um Inhalt des Statusregisters zu erhalten

  byte by = Wire.read();
  if((by & 0x80) != 0x80){
    xRtcAvailable = true; 
    sdActionLogger("RTC is at running condition", "OSF=0");
    nextionSplashScreen(true,"RTC Modul gestartet");
  }
  else{
    xRtcAvailable = false; 
    sdActionLogger("RTC is not running", "OSF=1");
    nextionSplashScreen(true, "RTC konnte nicht gestartet werden");
  }
}   


uint8_t rtcGetTimeInt(){
  if(xRtcAvailable){
    // Uhrzeit in String Speichern
    String strRtcTime;
    dtNow = rtc.now();
    strRtcTime = (dtNow.day(), DEC) + String(".") + (dtNow.month(), DEC) + String(".") + (dtNow.year(), DEC) + String("  ") + (dtNow.hour(), DEC) + String(":") + (dtNow.minute(), DEC);
  }
}
