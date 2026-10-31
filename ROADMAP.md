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
