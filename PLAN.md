# HouseThermo: review and upgrade plan

## Current state (2026-10-30)

- Two versions of the same thermostat:
  - **Basic 4-key**: this repo, `D:\Projects\Arduino\__HouseThermo` →
    github.com/VashJuan/HouseThermo. MicroView (ATmega328, 2 KB RAM), DS1307 RTC + DS18B20,
    four buttons, stove relay on pin 3. Code is 2018–19, last edited Dec 2025.
  - **M5Dial**: `D:\Projects\Arduino\M5 Stack\thermo` → github.com/VashJuan/M5DialThermo.
    ESP32-S3, MCP9808, LoRa to a relay receiver, schedule in `data/temps.csv`. Active Jan 2026.
- Legacy code captured in commit `4ff70a6` and sidelined under `legacy/` (see `LEGACY.md`, ideas in `ROADMAP.md`).
- `arduino-cli` is installed; the 4-key sketch has not been compiled since 2019.

## Review findings so far (4-key `_HouseThermo.ino`)

| # | Sev | Line | Issue |
| --- | --- | --- | --- |
| 1 | High | 223 | `numberOfSeconds()` is TimeLib's *seconds-within-minute* (x % 60), so it is always < 180. `proceed` is never true and the stove never switches. Should be `now() - lastTransition`. |
| 2 | High | 154 | No sensor check: a disconnected DS18B20 reads -127 °C (-196 °F), so the stove would run with no limit. Power-on reads 85 °C. Needs a sanity range and a fail-safe (stove off). |
| 3 | Med | 51 | `timeOffset[25]` is indexed by hour 0–23. Index 0 is `0`, so 12–1 AM gets no setback (comment calls index 24 "Midnight"; index 24 is never used). Check M5Dial `stove.hpp`, which uses the same table. |
| 4 | Med | 3–6 | `#ifdef USE_18B20` / `USE_TIME` are always true (they test *defined*, not the value). `MANUAL_RTC_RESET` is unused. |
| 5 | Med | 29, 243 | Stove LED on pin 0 (serial RX), `analogWrite(…, 300)` is over 255, and pin 0 isn't PWM. It fights `Serial`. |
| 6 | Med | 285–324 | Buttons block the loop with no debounce. The override is permanent, though the README says "until next time period". |
| 7 | Low | 42, 213 | Heavy `String` use on a 2 KB-RAM chip fragments the heap over weeks of uptime. |
| 8 | Low | 90–117 | RTC reset is hand-edited code. The commented "compile time" block doesn't compile (wrong syntax). |
| 9 | Low | .vscode | Board is `arduino:avr:unowifi`; MicroView is an Uno-class board on FTDI. `c_cpp_properties.json` is 804 bytes of blank spaces. |

## Plan

### Phase 1: Reproducible build (4-key)
1. Pin the libraries (the versions in `legacy/build.13Mar2019/includes.cache`) in a `sketch.yaml`
   (arduino-cli profile), or move to PlatformIO to match M5Dial.
2. Compile the sketch as-is to get a baseline. Fix `.vscode` (board, include paths).

### Phase 2: Fix the bugs (4-key)
3. Fix #1–#5 first (they're about safety and correctness), then #6–#8.
4. Bench test with a lamp or LED on the relay pin before it goes back on the stove.

### Phase 3: Shared core for both versions ("where easy")
5. Pull the hardware-free logic (hourly schedule, hysteresis, minimum on/off time, sensor
   sanity check, override-until-next-period) into one small C++ header with no `String`,
   so it fits both the Uno and the ESP32.
6. Add host unit tests for it (PlatformIO `native`). Both front-ends call it: the 4-key
   UI with MicroView, and the M5Dial UI with LoRa.

### Phase 4: Upgrades (4-key)
7. Replace the DFRobot DS1307 library with RTClib. Consider a DS3231 (it drifts less).
   Set the clock from the PC over serial instead of editing code.
8. Store the schedule in EEPROM; let the buttons edit it. Debounce the buttons without blocking.
9. Add the watchdog (`avr/wdt.h`) and make the stove fail off on any fault.

### Phase 5: M5Dial review
10. Run the same review on M5DialThermo (it's newer and bigger: ~200 KB of source and docs),
    and check that it doesn't carry over bugs #2, #3 and #6.

Open decisions are in `Questions for John.md`.
