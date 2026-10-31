// M5Dial I2C scanner: lists the devices on the external bus (Port A, 13=SDA, 15=SCL).
// The MCP9808 should answer at 0x18. Results go to the screen and serial; BtnA rescans.
#include <M5Unified.h>

// To scan the internal bus (RTC 0x51, touch 0x38) instead, use m5::In_I2C
#define SCAN_BUS m5::Ex_I2C

static void scan()
{
    M5.Display.fillScreen(TFT_BLACK);
    M5.Display.setCursor(30, 40);
    M5.Display.println("I2C scan");

    int found = 0;
    int y = 75;
    // ESP32-S3 hangs if addresses 0-7 are probed (see M5Unified scanID)
    for (uint8_t addr = 8; addr < 0x78; addr++)
    {
        if (SCAN_BUS.start(addr, false, 400000) && SCAN_BUS.stop())
        {
            Serial.printf("Found 0x%02X\n", addr);
            if (y <= 170)
            {
                M5.Display.setCursor(60, y);
                M5.Display.printf("0x%02X", addr);
                y += 20;
            }
            found++;
        }
        else
        {
            SCAN_BUS.stop();
        }
    }

    Serial.printf("%d device(s) found\n", found);
    M5.Display.setCursor(40, 185);
    M5.Display.printf("%d found", found);
    M5.Display.setCursor(40, 205);
    M5.Display.println("BtnA: rescan");
}

void setup()
{
    M5.begin(M5.config());
    Serial.begin(115200);
    SCAN_BUS.begin();
    M5.Display.setTextSize(2);
    M5.Display.setTextColor(TFT_WHITE, TFT_BLACK);
    scan();
}

void loop()
{
    M5.update();
    if (M5.BtnA.wasPressed())
    {
        scan();
    }
    delay(10);
}
