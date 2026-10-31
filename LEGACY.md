# Legacy code map

Captured into git on 2026-10-30 and moved under `legacy/` (sidelined, not deleted).
The root holds only the current 4-key sketch and project docs.

| Path | What it is | Dates |
| --- | --- | --- |
| `_HouseThermo.ino` (root) | Current 4-key MicroView thermostat sketch | edited Dec 2025 |
| `legacy/Archive/` | Earlier versions of the sketch (`.x`, `.ino.N` = snapshots) | Jan 2018 – Nov 2018 |
| `legacy/build.13Mar2019/` | Last known flashed firmware (`.hex`) and its build manifest | Mar 2019 |
| `legacy/Hack/` | Copies of DallasTemperature, OneWire and MicroView libraries used to build | Dec 2019 |
| `legacy/Older/Termo/` | 2017–18 experiments: RTC set/read, DS18B20, MCP9808, MicroView demos, `_MyRTCThermo` (precursor) | Dec 2017 – Mar 2018 |
| `legacy/Older/SyncArduinoClock/` | Set the RTC from the PC clock | Dec 2017 |
| `legacy/MicroViewDemo/` | MicroView display demo | Jan 2018 |
| `legacy/Dallas Temperature Control - TwoPin_DS18B20/` | DS18B20 two-pin test | Jan 2018 |
| `legacy/2026-experiments/` | CircuitPython / XIAO ESP32-S3 BLE trials and links from the M5Dial planning | Dec 2025 |

Reference material (vendor datasheets, saved pages, `.url` links) stays beside the code it
relates to. PDFs, zips and saved pages are on disk only, not in git.

Ideas worth carrying forward are in [ROADMAP.md](ROADMAP.md).

## On disk only, not in git

- `HouseThermo/HouseThermo/`: old 2018 clone of this repo. Its one unique file is
  `legacy/Archive/_HouseThermo.8Mar2018.ino.x`.
- Build objects, `legacy/2026-experiments/.venv` and `.idea`, the CircuitPython `.uf2`.
- Vendor zips, datasheet PDFs, saved web pages, and duplicate copies of third-party
  libraries (DallasTemperature 3.7.2 beta, OneWire, RTClib, DFRobot DS1307, DipMicro and
  Hobbyist RTC samples).

## Libraries the sketch needs

`TimeLib`, `MicroView`, `OneWire`, `DallasTemperature`, `Wire`, `DS1307` (DFRobot).
