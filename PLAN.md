# HouseThermo: review and upgrade plan

## Current state (2026-10-30)

- One repo, `D:\Projects\Arduino\__HouseThermo` → github.com/VashJuan/HouseThermo, two versions:
  - **Basic 4-key**: root `_HouseThermo.ino`. MicroView (ATmega328, 2 KB RAM), DS1307 RTC +
    DS18B20, four buttons, stove relay on pin 3. Code is 2018–19, last edited Dec 2025.
  - **M5Dial**: `m5dial/` (merged from M5DialThermo with history). ESP32-S3, MCP9808, LoRa to
    the XIAO relay receiver in `m5dial/receiver/`, schedule in `m5dial/data/temps.csv`.
- Legacy code sidelined under `legacy/` (see `LEGACY.md`, ideas in `ROADMAP.md`).
- Decisions (2026-10-30): one repo; PlatformIO for everything; hardware changes OK.
- Nothing is attached to the stove. On USB, 2026-10-30:
  - MicroView = COM12 (FTDI). It runs a **DEBUG build not in the repo** (set 78 °F), backed
    up to `legacy/microview-firmware-backup/`. The DS18B20 on the RTC board reads fine.
    The RTC was halted (dead cell): John replaced the cell, and `tools/rtc_check` set and
    started it. The original firmware was restored, and the time is correct.
  - Receiver = COM11 (XIAO ESP32-S3). It runs the current `m5dial/receiver` code, LoRa
    915 MHz P2P OK.
  - M5Dial = COM13 (after a cable swap). NTP time OK, but the **MCP9808 isn't answering on
    I2C** (reads 999 °F). The timezone was `PST8` (no DST, an hour off in summer): fixed in the
    repo, **not flashed yet**. COM3 (CP210x) is still unknown.
- Builds: `m5dial` and `receiver` both build with espressif32 **pinned to 6.12.0** (8.x
  breaks them). The M5Dial app uses 87% of its 1.3 MB partition.
- The old M5Dial clone (was `D:\Projects\Arduino\M5 Stack\thermo`) is in `D:\Projects\Arduino\_ToDelete_2026-10-30\`.
- Display/M5Dial reference: `D:\Projects\Arduino\_Reference\Displays\Displays.md`. I2C scanner: `tools/i2c_scan`.

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
   (arduino-cli profile), → decided: PlatformIO, as a `microview/` project beside `m5dial/`.
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

### Next session: M5Dial first (MicroView retired 2026-10-30, kept for future projects)

- **Relay-state fix (2026-10-30), code done; the Dial is NOT flashed yet:** the receiver
  answered ON/OFF with `ACK`, which the Dial rejected (`isValidResponse`) and also didn't match
  (`turnOn` expected `STOVE_ON`). So the relay went ON while the Dial stayed at OFF and never
  sent OFF. Status replies (`STOVE_ON_ACK`) were never matched either. Now the receiver answers
  every command with `STOVE_ON_ACK`/`STOVE_OFF_ACK`, and `Stove::applyRemoteState()` adopts
  that state (plain `ACK` is still accepted from old firmware).
- Bench tests 2026-10-30, both units flashed (Dial COM13, receiver COM11): `i2c_scan` found the
  MCP9808 at 0x18. Two more link bugs were found and fixed: (a) a failed LoRaWAN fallback left the
  Wio-E5 out of TEST mode, so P2P died for good (ERROR(-12)); `switchMode()` now restores P2P.
  (b) Both sides waited up to 11 s for an "RX DONE" the Wio-E5 never sends, so about half
  the replies arrived after the Dial stopped listening; a `+TEST: RX "` line now ends the wait.
  After the fixes: 15/15 round trips (~5.5 s each); ON confirmed end to end. The receiver's 10-min
  safety timeout also turned the relay OFF on its own while the link was down.
  **Next:** OFF test. Wait for ON, then turn the dial below the room temperature and confirm the
  receiver logs `Command executed: Stove turned OFF`. Logging tool:
  `tools/lora_log.py` (both COM ports, timestamped; run with the PlatformIO python).
- Fixed + flashed 2026-10-30: the schedule used the UTC hour (7–8 h early) → `RTC::getHour()`
  and `getDayOfWeek()` use local time now; hour 0 → the "24 = Midnight" row; DST timezone default.
- The device's SPIFFS `temps.csv` (base 74 °F) differs from the repo (77 °F). It's in the full
  flash backup `legacy/m5dial-firmware-backup/` (gitignored: contains Wi-Fi secrets).
- The 4-key phases below are parked. The firmware the MicroView ran is in
  `legacy/microview-firmware-backup/`.

### Phase 5: M5Dial review
10. Run the same review on `m5dial/` (it's newer and bigger: ~200 KB of source and docs),
    and check that it doesn't carry over bugs #2, #3 and #6. Known so far: the receiver logs
    "Auto low power mode enabled" even when `AT+LOWPOWER` returns `ERROR(-1)`
    (`m5dial/receiver/src/receiver_main.cpp:108`). Flash is at 87%.
11. Port to espressif32 6.12 → current (Arduino core 3) later: `esp_task_wdt_init` takes a
    config struct now, and `sntp_stop` is gone (`m5dial/src/_thermo.cpp:201`, `m5dial/src/rtc.cpp:175`).

Open decisions are in `Questions for John.md`.
