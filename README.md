# 🌡️ HouseThermo: Smart Stove Thermostat

An Arduino-family thermostat that turns a heater (a gas stove) on and off. It compares the
room temperature with a target that changes hour by hour through the day.

Two generations live in this one repo: the original 2018 four-button MicroView unit, and
the 2026 M5Dial with a wireless LoRa link to the stove relay.

## 🧭 Two versions, one repo

### 🎛️ [M5Dial version](m5dial/README.md) (current)

**Round touch screen + rotary knob, wireless relay**

- M5Stack Dial (ESP32-S3) with an MCP9808 precision temperature sensor
- LoRa link (915 MHz P2P) to a XIAO ESP32-S3 relay receiver at the stove (`m5dial/receiver/`)
- Hour-by-hour schedule in `m5dial/data/temps.csv`; time from NTP
- Merged in from VashJuan/M5DialThermo with its full history (Oct 2026)

### 🔘 Basic 4-key version (retired, kept for parts)

**SparkFun MicroView with four buttons, wired relay**

- MicroView (ATmega328) + DS1307 real-time clock + Dallas DS18B20 thermometer
- Four buttons to bump the target temperature up or down
- Root `_HouseThermo.ino`. Retired Oct 2026; known bugs are listed in [PLAN.md](PLAN.md)

## 📚 Documentation

- 🏠 [User Guide](m5dial/USER_GUIDE.md): operation, LED codes, troubleshooting
- 🔧 [Hardware Guide](m5dial/doc/HARDWARE_GUIDE.md): wiring, pins, LoRa modules
- 🌐 [Network Guide](m5dial/NETWORK_GUIDE.md): P2P vs LoRaWAN, Wi-Fi time sync
- 👨‍💻 [Developer Guide](m5dial/DEVELOPER_GUIDE.md): build, architecture, protocol
- 🗺️ [PLAN.md](PLAN.md) (work order), [ROADMAP.md](ROADMAP.md) (ideas), [LEGACY.md](LEGACY.md) (old code)

## 🚀 Quick Start (M5Dial)

1. Install VS Code + PlatformIO
2. Copy `m5dial/src/secrets_template.h` to `secrets.h` (and the same in `m5dial/receiver/src/`)
3. Build and flash both units (PlatformIO finds the COM port):

   ```powershell
   cd m5dial;          pio run -t upload; pio run -t uploadfs
   cd receiver;        pio run -t upload
   ```

4. **Rotate the dial** to change the base temperature (0.5 °F per click, 50–90 °F)
5. **Press the button** to reset it to the configured value

## 🧰 Tools

- 🔍 [tools/i2c_scan](tools/i2c_scan): M5Dial I2C scanner (the MCP9808 should show at 0x18)
- 🕰️ [tools/rtc_check](tools/rtc_check): MicroView DS1307 clock check and set

## 🛡️ Safety Features

- 🛡️ The receiver turns the stove OFF after 10 minutes without a command
- 🛡️ Always starts with the heater OFF
- 🛡️ The receiver reports the real relay state with every reply, and the Dial follows it
- 🛡️ Watchdog timers on both units
- 🛡️ Base temperature capped at 50–90 °F

## 🔩 Hardware

| Unit | Parts | About |
| --- | --- | --- |
| 🎛️ Dial | M5Stack Dial, MCP9808, Grove-Wio-E5 LoRa | ~$45 |
| 🔥 Receiver | XIAO ESP32-S3, Grove-Wio-E5 LoRa, relay module | ~$30 |
| 🔘 4-key (retired) | MicroView, DS1307 RTC, DS18B20, 4 buttons | — |

## 📜 License

MIT License, see [m5dial/LICENSE](m5dial/LICENSE). Copyright © 2018–2026 VashonSoftware.com

## ✍️ Author

**John Cornelison**  
<john@vashonSoftware.com>

---

_Safe, efficient home heating control, since 2018_ 🏠🔥
