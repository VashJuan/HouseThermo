/**************************************************************************/
/*!
Adafruit MCP9808 breakout: http://www.adafruit.com/products/1782
https://learn.adafruit.com/adafruit-mcp9808-precision-i2c-temperature-sensor-guide?view=all
/**************************************************************************/

#define USETIME true
#define DEBUG true

#include <Wire.h>
#include <Adafruit_MCP9808.h>

//#include <DS1307.h>
// From https://www.dfrobot.com/wiki/index.php/Real_Time_Clock_Module_(DS1307)_V1.1_(SKU:DFR0151)

#include <MicroView.h>
//#include <Time.h>  // http://www.pjrc.com/teensy/td_libs_DS1307RTC.html
//#include <TimeLib.h>
//#include <DS1307RTC.h>  //https://github.com/PaulStoffregen/DS1307RTC

// Create the MCP9808 temperature sensor object
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

boolean StoveOn = false;
int RTCTempInputPin = 5; // NOTE this is UNO pin, NOT the MicroView Pin Number 13!
int StoveOnPin = 3; // NOTE this is UNO pin, NOT the MicroView Pin Number 12!
int StoveOffPin = 0; // NOTE this is UNO pin, NOT the MicroView Pin Number 9!

int button3Pin = A3; // MicroView pin 4!
int button4Pin = A2; // MicroView pin 5!
int button1Pin = A1; // MicroView pin 6!
int button2Pin = A0; // MicroView pin 7!

String outputString;

float setTemp = 78.0; // degrees Farenheight
// Avoid switching stove on and off too often. Set a temp range considered as ideal.
float minusOffset = 2.0; //Degrees farenheit below setTemp when stove goes on
float plusOffset = 2.0; //Degrees farenheit above setTemp when stove goes on

String curTime;


void setup() {
  Serial.begin(9600);
  //while (!Serial) ; // wait for serial
  //delay(200);
  Serial.println("A Sparkfun Microview & MCP9808 & DS1307RTC based thermostat");
  Serial.println("-----------------------------------------------------------");

  uView.begin();
  uView.clear(PAGE);
  uView.setFontType(0);     // set font type 0, please see declaration in MicroView.cpp
  uView.setCursor(0,0);
  uView.println("Seeking sensors");
  uView.display();        // display current page buffer

/*
 *   Actual I2C address = 0x18 (default address) + A2 + A1 + A0
 *   Add A0/A1/A2 to the base (i.e., default) of 0x18
 *   A0 sets lowest bit (i.e., +1) 
 *   A1 sets middle bit (i.e., +2) 
 *   A2 sets high bit (i.e., +4) 
 *   So for example if A2 is tied to VDD and A0 is tied to VDD, the address is 0x18 + 4 + 1 = 0x1D.
 *   If only A1 is tied to VDD, the address is 0x18 + 2 = 0x1A
 */

  if (!tempsensor.begin()) 
  {
    Serial.println("Couldn't find MCP9808!");
    uView.println("MCP9808 NOT found!!!");
  
  }else{
  Serial.println("MCP9808 found");
  uView.println("MCP9808 found");
  }
  
  }
  uView.display();        // display current page buffer 
delay(1000);

  pinMode(StoveOnPin, OUTPUT);      // sets the digital pin as output
  pinMode(StoveOffPin, OUTPUT);      // sets the digital pin as output

  pinMode(button1Pin,INPUT);
  pinMode(button2Pin,INPUT);
  pinMode(button3Pin,INPUT);
  pinMode(button4Pin,INPUT);
}


void getTime() {
  tmElements_t tm;

  if (RTC.read(tm)) {
    curTime="";
    if (DEBUG)
      Serial.print("Time = ");
    
    print2digits(tm.Hour);
    if (DEBUG)
      Serial.write(':');
    curTime+=":";
    
    print2digits(tm.Minute);
    if (DEBUG)
      Serial.write(':');
    curTime+=":";

    
    print2digits(tm.Second);
    curTime+="  ";
    //curTime+=" on ";

    if (DEBUG) {
      Serial.print(", Date (M/D/Y) = ");
      Serial.print(tm.Month);
      Serial.write('/');
    }
    curTime+=String(tm.Month)+"/";
    
    if (DEBUG)
    {
      Serial.print(tm.Day);
      Serial.write('/');
    }
    curTime+=String(tm.Day)+"/";
    
    if (DEBUG)
      Serial.println(tmYearToCalendar(tm.Year));
    int yr=tmYearToCalendar(tm.Year)-2000;
    curTime+=String(yr);
    
  } else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(1000);
  }
  //delay(500);
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    if (DEBUG)
      Serial.write('0');
    curTime+="0";
  }
  if (DEBUG)
      Serial.print(number);
  curTime+=String(number);
}


void loop() 
{
  outputString="";

//Using Adafruit MCP9808 tenp sensor?
if (true) {

  //Serial.println("wake up MCP9808.... "); // wake up MSP9808 - power consumption ~200 mikro Ampere
  //tempsensor.wake();   // wake up, ready to read!

  // Read and print out the temperature, then convert to *F
  float c = tempsensor.readTempC();
  float f = c * 9.0 / 5.0 + 32;
  Serial.print("Temp: "); Serial.print(c); Serial.print("*C\t"); 
  Serial.print(f); Serial.println("*F");
  
  //Serial.println("Shutdown MCP9808.... ");
  //tempsensor.shutdown(); // shutdown MSP9808 - power consumption ~0.1 mikro Ampere

}
else
{
   
  if (USETIME) {
    getTime();
    Serial.print("Time: "); Serial.println(curTime);
    outputString = curTime;
    outputString+="\n";
 }
  
  // Read and print out the temperature, then convert to *F
  float c = tempsensor.readTempC();
  float f = c * 9.0 / 5.0 + 32;

if (DEBUG) {
  Serial.print("Temp: "); 
  Serial.print(c); Serial.print("*C  \t"); 
  Serial.print(f); Serial.println("*F");
}

  if (f<setTemp-minusOffset)
  {
    //Serial.println("ON");
    StoveOn=true;
    analogWrite(StoveOnPin, 25);   // Turn on Stove!
    digitalWrite(StoveOffPin, LOW);
    outputString+="     Temp\nCur: ";
    outputString+=String(f);
    outputString+="Set: ";
    outputString+=String(setTemp);
    outputString+="Stove On";
    //outputString+="     Temp\nCur: " + String(f) + "Set: " + String(setTemp) + "Stove On";
  }
  else
  {
    if (f>setTemp+plusOffset)
    {
      //Serial.println("OFF");
      StoveOn=false;
      digitalWrite(StoveOnPin, LOW);   // Turn off Stove!
      analogWrite(StoveOffPin, 10);
      outputString += "     Temp\nCur: " + String(f) + "Set: " + String(setTemp) + "Stove Off";
    }
    else
    {
      // temperature is just right!
      //Serial.println("MAINTAIN");
      outputString += "     Temp\nCur: " + String(f) + "Set: " + String(setTemp) + "No Action";
      analogWrite(StoveOnPin, 2);   // Turn on Stove!
      digitalWrite(StoveOffPin, LOW);
    }
  }
}
}
  
  uView.clear(PAGE);
  
  Serial.println(outputString);
  uView.setCursor(0,0);
  uView.println(outputString);
  uView.display();        // display current page buffer


   while (digitalRead(button1Pin)==HIGH)
  {
    //Quickly lower Set Temp
    outputString="Set NIGHT Temp = " +  String(setTemp-=2.0);
    Serial.println(outputString);
    uView.setCursor(0,0);
    uView.println(outputString);
    uView.display();
    delay (1000);
  }  
  
  while (digitalRead(button2Pin)==HIGH)
  {
    outputString="Set Temp = " +  String(setTemp-=0.1);
    Serial.println(outputString);
    uView.setCursor(0,0);
    uView.println(outputString);
    uView.display();
    delay (250);
  }

  while (digitalRead(button3Pin)==HIGH)
  {
    outputString="Set Temp = " +  String(setTemp+=0.1);
    Serial.println(outputString);
    uView.setCursor(0,0);
    uView.println(outputString);
    uView.display();
    delay (250);
  }
  
   while (digitalRead(button4Pin)==HIGH)
  {
    outputString="Set NIGHT Temp = " +  String(setTemp+=2.0);
    Serial.println(outputString);
    uView.setCursor(0,0);
    uView.println(outputString);
    uView.display();
    delay (2000);
  }

  //Serial.println("Shutdown MCP9808.... ");
  //tempsensor.shutdown(); // shutdown MSP9808 - power consumption ~0.1 mikro Ampere

  //TODO: Check Battery Voltage!
  delay(250); 
}
