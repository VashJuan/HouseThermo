// DS1307 check: scan I2C, dump the clock, and if it is halted or invalid,
// set it to this sketch's compile time (PC local time) and start it.
#include <Arduino.h>
#include <Wire.h>

const uint8_t DS1307_ADDR = 0x68;

uint8_t bcd2dec(uint8_t v) { return (v >> 4) * 10 + (v & 0x0F); }
uint8_t dec2bcd(uint8_t v) { return ((v / 10) << 4) | (v % 10); }

bool readRegs(uint8_t *r)
{
  Wire.beginTransmission(DS1307_ADDR);
  Wire.write(0);
  if (Wire.endTransmission() != 0) return false;
  if (Wire.requestFrom(DS1307_ADDR, (uint8_t)7) != 7) return false;
  for (int i = 0; i < 7; i++) r[i] = Wire.read();
  return true;
}

void printTime(const uint8_t *r)
{
  char buf[48];
  snprintf(buf, sizeof buf, "20%02u-%02u-%02u %02u:%02u:%02u dow=%u CH=%u",
           bcd2dec(r[6]), bcd2dec(r[5] & 0x1F), bcd2dec(r[4] & 0x3F),
           bcd2dec(r[2] & 0x3F), bcd2dec(r[1] & 0x7F), bcd2dec(r[0] & 0x7F),
           r[3] & 0x07, r[0] >> 7);
  Serial.println(buf);
}

void setFromCompileTime()
{
  // __DATE__ = "Oct 30 2026", __TIME__ = "17:24:48"
  const char *months = "JanFebMarAprMayJunJulAugSepOctNovDec";
  const char *d = __DATE__, *t = __TIME__;
  char mname[4] = {d[0], d[1], d[2], 0};
  uint8_t mon = (strstr(months, mname) - months) / 3 + 1;
  uint8_t day = atoi(d + 4), yr = atoi(d + 9);
  uint8_t hh = atoi(t), mm = atoi(t + 3), ss = atoi(t + 6);
  // Day of week (1=Sun) by Sakamoto's method
  static const uint8_t k[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
  int y = 2000 + yr - (mon < 3);
  uint8_t dow = (y + y / 4 - y / 100 + y / 400 + k[mon - 1] + day) % 7 + 1;

  Wire.beginTransmission(DS1307_ADDR);
  Wire.write(0);
  Wire.write(dec2bcd(ss) & 0x7F); // CH=0 starts the oscillator
  Wire.write(dec2bcd(mm));
  Wire.write(dec2bcd(hh));        // 24-hour mode
  Wire.write(dow);
  Wire.write(dec2bcd(day));
  Wire.write(dec2bcd(mon));
  Wire.write(dec2bcd(yr));
  Serial.print("Set time, I2C status ");
  Serial.println(Wire.endTransmission());
}

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  delay(200);
  Serial.println("\n== RTC check ==");
  for (uint8_t a = 1; a < 127; a++)
  {
    Wire.beginTransmission(a);
    if (Wire.endTransmission() == 0)
    {
      Serial.print("I2C device at 0x");
      Serial.println(a, HEX);
    }
  }

  uint8_t r[7];
  if (!readRegs(r))
  {
    Serial.println("DS1307 NOT RESPONDING at 0x68");
    return;
  }
  printTime(r);
  bool halted = r[0] & 0x80;
  bool invalid = bcd2dec(r[6]) < 26 || bcd2dec(r[5] & 0x1F) == 0;
  if (halted || invalid)
  {
    setFromCompileTime();
  }
}

void loop()
{
  uint8_t r[7];
  if (readRegs(r)) printTime(r);
  else Serial.println("read failed");
  delay(2000);
}
