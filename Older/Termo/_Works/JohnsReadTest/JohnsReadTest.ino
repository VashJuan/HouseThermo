//https://github.com/PaulStoffregen/DS1307RTC/blob/master/examples/ReadTest/ReadTest.ino
// With added Read Battery Voltage AND Read Temp using one wire...
//http://www.hobbyist.co.nz/?q=real_time_clock
//https://www.pjrc.com/teensy/td_libs_OneWire.html


#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

void setup() {
  Serial.begin(9600);
  Serial.println("RTC Test, waitin on serial monitor...");
  while (!Serial) ; // wait for serial
  delay(200);
    Serial.println("Ready to go....get system time");
  Serial.println("DS1307RTC Read Test");
  Serial.println("-------------------");

    //Wire.begin();
    pinMode(2, INPUT); // Temp Sensor
    digitalWrite(2, HIGH); // pullup
    
    pinMode(A1, INPUT); // Battery Level
    digitalWrite(A1, HIGH); // pullup
  
}

void loop() {
  tmElements_t tm;

  if (RTC.read(tm)) {
    Serial.print("Ok, Time = ");
    print2digits(tm.Hour);
    Serial.write(':');
    print2digits(tm.Minute);
    Serial.write(':');
    print2digits(tm.Second);
    Serial.print(", Date (D/M/Y) = ");
    Serial.print(tm.Day);
    Serial.write('/');
    Serial.print(tm.Month);
    Serial.write('/');
    Serial.print(tmYearToCalendar(tm.Year));
    Serial.println();
  } else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(3000);
  }
  readBatVcc();
  delay(1000);
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}

float TT=0.0;
int sensorValue=0;

void readBatVcc(void){

    sensorValue = 0;        // value read from the pot
  
    sensorValue = analogRead(A1);
    TT = sensorValue*0.0047;
    Serial.print("Backup Vcc: ");
    Serial.print(TT);
    Serial.print("V");
}

void displTemp (void)
{
  //DS18B20 temp Sensor uses 1 wire interface
  unsigned int Temper=0;
 sensorValue = digitalRead(2);
    

  
  
  /*
   *   byte i;
  byte present = 0;

  byte Tdata[12];
int rtc[7];
int val;
present = ds.reset();
    ds.write(0xCC,1);    
    ds.write(0xBE);         // Read Scratchpad
    for ( i = 0; i < 9; i++) {           // we need 9 bytes
      Tdata[i] = ds.read();
    }    
    Temper = (Tdata[1]<<8 | Tdata[0]);
    TT =Temper*0.0625;
    
    if(TT>200){
     Serial.println("\t DS18B20 Not installed!");
    }else{
      Serial.print("\t Temperature=");
      Serial.println(TT);
    }
   * */
   */
}
}

