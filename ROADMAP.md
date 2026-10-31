# Roadmap ideas

Ideas gathered from the legacy code and notes. The work order is in [PLAN.md](PLAN.md).

## From the legacy experiments

- **Two temperature sensors** (`legacy/Older/Termo/_Works/_MyRTCThermo/*bothThermos*`,
  `*.with.MCP9808`): DS18B20 plus MCP9808, averaged or cross-checked to catch a failed sensor.
- **Set the clock from the PC** (`legacy/Older/SyncArduinoClock`, serial time-set in the
  sketch): replace the hand-edited RTC reset.
- **Hold-off after a change** (`legacy/Archive/*withdelayPostChangeMode*`,
  `*WorksWithHrlyDelay`): minimum on/off time; this is in the current sketch but broken.
- **Backup-battery voltage check** (`readBatVcc()` in the sketch, from the DFRobot sample):
  warn when the RTC coin cell is low.
- **"Hold current temp forever" / reset buttons** (the "alt scheme" comment in the sketch):
  alternative 4-key layout.

## From the 2026 planning (`legacy/2026-experiments/`)

- **Schedule in a CSV file** (CircuitPython CSV links): done in M5Dial as `data/temps.csv`.
  For the 4-key version, keep the schedule in EEPROM instead.
- **Wireless remote sensor or relay** (XIAO ESP32-S3 BLE client/server): M5Dial went with
  LoRa. BLE could still be a cheap second room sensor.

## New

- Override until the next schedule period (the README promises it; not built).
- Fail-safe: stove off on a sensor fault, RTC fault or watchdog reset.
- A shared, unit-tested control core for both front-ends (see PLAN.md Phase 3).

## Housekeeping: graphics and M5 reference folders (surveyed 2026-10-30)

About 3 GB across `D:\Projects\Arduino\LovyanGFX`, `D:\Projects\Arduino\LVGL` and
`D:\Projects\Arduino\M5 Stack`. Almost all of it can be downloaded or rebuilt again.

- **Real content (keep):**
  - `M5 Stack\LovyanGFX_font_display`: John's own repo (github.com/VashJuan/LovyanGFX_font_display),
    clean and pushed. Only its `.pio\` build folder (574 MB) can go.
  - Small sketches that may be John's: `M5 Stack\IC2 Scannner\` (`scan.ino`, `unifiedScan.ino`
    + notes), `M5 Stack\m5Unified\hello\`, and `_Dial\Programming & Examples\Basic\display` and
    `rtc` (edited 2025-12-15). Move the I2C scanner into `tools/i2c_scan` here (it helps with
    MCP9808 checks); the rest into a scratch/sandbox folder.
  - Reference: `_Dial\Programming & Examples\Sch_M5Dial.pdf`, the datasheet PDFs, and the `.url` links.
- **Superseded:** `M5 Stack\thermo` (M5DialThermo clone). Its history is merged into this repo,
  so the whole folder (507 MB, mostly `.pio\`) can go once the GitHub repo is archived (Q7).
- **Upstream only:** `LVGL\lvgl_port_pc_visual_studio` (1.3 GB) is John's GitHub fork with no
  commits of his own; its submodules show deleted files (a broken checkout). Delete and re-clone if needed.
- **Downloads:** `_Dial\Programming & Examples\M5Dial-UserDemo` (292 MB), `M5Dial-Gui-Demo` (185 MB),
  `Factory Demos`, `Volos\M5Dial-main(.zip)`, the esphome zip, `ESP32-S3FN8-Stamp3\`, and the saved
  web pages (`*_files\` + `.html`). Keep their `.url` links instead.
- **Notes:** `LVGL vs LovyanGFX.md` is empty (2 bytes) and appears in two folders. `LVGL\index.md`
  is a copy of the LVGL docs. `M5 Stack\setCursor.md` and `unifiedScan\chat_history.md` are AI chat
  transcripts. Fold anything useful into one `Displays.md` note.
- **Target:** one `D:\Projects\Arduino\_Reference\Displays\` folder (links, PDFs, one note), under 10 MB.
