#include <MicroView.h>

#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

tmElements_t tm;

void setup() {
  bool parse=false;
  bool config=false;

  // get the date and time the compiler was run
  if (getDate(__DATE__) && getTime(__TIME__)) {
    parse = true;
    // and configure the RTC with this info

uView.begin();              // start MicroView
    uView.clear(PAGE);          // clear page
    uView.print("Writing to RTC");   // display string
    uView.display(); delay (200);



    
      //Serial.println("writing system time");
    if (RTC.write(tm)) {
      config = true;
          uView.print("Wrote to RTC");   // display string
    uView.display(); delay (200);
    }
    else
    {uView.print("FAILED TO Write to RTC");   // display string
    uView.display(); delay (200);
    }
  }

  Serial.begin(9600);
    uView.print("start serial");   // display string
    uView.display(); delay (200);
    
  while (!Serial) ; // wait for Arduino Serial Monitor
    uView.print("serial started");   // display string
    uView.display(); delay (200);
    Serial.println("Ready to go....set system time");
  delay(200);
  uView.print("parsing");   // display string
    uView.display(); delay (200);
    
  if (parse && config) {
    Serial.print("DS1307 configured Time=");
    Serial.print(__TIME__);
    Serial.print(", Date=");
    Serial.println(__DATE__);
  } else if (parse) {
    Serial.println("DS1307 Communication Error :-{");
    Serial.println("Please check your circuitry");
  } else {
    Serial.print("Could not parse info from the compiler, Time=\"");
    Serial.print(__TIME__);
    Serial.print("\", Date=\"");
    Serial.print(__DATE__);
    Serial.println("\"");
  }
}

void loop() {
}

bool getTime(const char *str)
{
  int Hour, Min, Sec;

  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  return true;
}

bool getDate(const char *str)
{
  char Month[12];
  int Day, Year;
  uint8_t monthIndex;

  if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3) return false;
  for (monthIndex = 0; monthIndex < 12; monthIndex++) {
    if (strcmp(Month, monthName[monthIndex]) == 0) break;
  }
  if (monthIndex >= 12) return false;
  tm.Day = Day;
  tm.Month = monthIndex + 1;
  tm.Year = CalendarYrToTm(Year);
  return true;
}

