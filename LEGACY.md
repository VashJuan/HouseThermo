# Legacy code map

Captured into git on 2026-10-30 for the record. Files are kept where they were on disk.

| Path | What it is | Dates |
| --- | --- | --- |
| `_HouseThermo.ino` | Current 4-key MicroView thermostat sketch | edited Dec 2025 |
| `Archive/` | Earlier versions of the sketch (`.x`, `.ino.N` = snapshots) | Jan 2018 – Nov 2018 |
| `build.13Mar2019/` | Last known flashed firmware (`.hex`) and its build manifest | Mar 2019 |
| `Hack/` | Copies of DallasTemperature, OneWire and MicroView libraries used to build | Dec 2019 |
| `Older/Termo/` | 2017–18 experiments: RTC set/read, DS18B20, MCP9808, MicroView demos, `_MyRTCThermo` (precursor) | Dec 2017 – Mar 2018 |
| `Older/SyncArduinoClock/` | Set the RTC from the PC clock | Dec 2017 |
| `MicroViewDemo/` | MicroView display demo | Jan 2018 |
| `Dallas Temperature Control - TwoPin_DS18B20/` | DS18B20 two-pin test | Jan 2018 |
| `2026/` | Links and XIAO ESP32-S3 BLE samples from the M5Dial planning | Dec 2025 |

## Left out of git (still on disk)

- `HouseThermo/HouseThermo/`: old 2018 clone of this repo. Its one unique file is
  `Archive/_HouseThermo.8Mar2018.ino.x`.
- Build objects, `2026/.venv`, `2026/.idea`, the CircuitPython `.uf2` firmware.
- Vendor zips, datasheet PDFs, saved web pages, and duplicate copies of third-party
  libraries (DallasTemperature 3.7.2 beta, OneWire, RTClib, DFRobot DS1307, DipMicro and
  Hobbyist RTC samples).

## Libraries the sketch needs

`TimeLib`, `MicroView`, `OneWire`, `DallasTemperature`, `Wire`, `DS1307` (DFRobot).
