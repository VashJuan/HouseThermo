// Tiny RTC (DS1307)
//
// from http://blog.simtronyx.de/en/tiny-rtc-ds1307-real-time-clock-with-an-additional-temperature-sensor-ds18b20/

#include <Wire.h>    // I2C-Bibliothek einbinden
#include "RTClib.h"  // RTC-Bibliothek einbinden

RTC_DS1307 RTC;      // RTC Modul

#include <OneWire.h>            // OneWire-Bibliothek einbinden
#include <DallasTemperature.h>  // DS18B20-Bibliothek einbinden

#define DS18B20_PIN 2   // Pin für DS18B20 definieren Arduino D2

OneWire oneWire(DS18B20_PIN);          // OneWire Referenz setzen
DallasTemperature sensors(&oneWire);   // DS18B20 initialisieren

void setup(void) {

  // Initialisiere I2C  
  Wire.begin();
  
  // Initialisiere RTC
  RTC.begin();

  // Serielle Ausgabe starten 
  Serial.begin(9600);

  // Begrüßungstext auf seriellem Monitor ausgeben
  Serial.println("Start Date & Temperature - from blog.simtronyx.de");

  // Prüfen ob RTC läuft  
  if (! RTC.isrunning()) {
    
    // Aktuelles Datum und Zeit setzen, falls die Uhr noch nicht läuft
    RTC.adjust(DateTime(__DATE__, __TIME__));
    
    Serial.println("Adjusted Time & Date.");
  }
  else Serial.println("Maintained date & time.");

  sensors.begin();  // DS18B20 starten
}

void loop(){
  
  DateTime now=RTC.now();
  show_time_and_date(now);
  
  sensors.requestTemperatures();
  show_temperature(sensors.getTempCByIndex(0));
  
  delay(3000);
}

// 
String get_day_of_week(uint8_t dow){ 
  
  String dows="  ";
  switch(dow){
   case 0: dows="Su"; break;
   case 1: dows="Mo"; break;
   case 2: dows="Tu"; break;
   case 3: dows="We"; break;
   case 4: dows="Th"; break;
   case 5: dows="Fr"; break;
   case 6: dows="Sa"; break;
  }
  
  return dows;
}

void show_time_and_date(DateTime datetime){
  
//  Serial.print(get_day_of_week(datetime.dayOfWeek()));
  Serial.print(", ");
  
  if(datetime.month()<10)Serial.print(0);
  Serial.print(datetime.month(),DEC);
  Serial.print("//");  
  if(datetime.day()<10)Serial.print(0);
  Serial.print(datetime.day(),DEC);
  Serial.print("//");
  Serial.println(datetime.year(),DEC);
  

  if(datetime.hour()<10)Serial.print(0);
  Serial.print(datetime.hour(),DEC);
  Serial.print(":");
  if(datetime.minute()<10)Serial.print(0);
  Serial.print(datetime.minute(),DEC);
  Serial.print(":");
  if(datetime.second()<10)Serial.print(0);
  Serial.println(datetime.second(),DEC);
}

// Temperatur ausgeben
void show_temperature(float temp){
  
  Serial.print("Temperatur: ");
  Serial.print(temp);
  Serial.print(" o");
  //Serial.write(176);  // display the ° symbol
  Serial.println("C");
}
