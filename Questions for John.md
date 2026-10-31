# Questions for John

## HouseThermo (4-key + M5Dial)

- **Q1** Is the MicroView 4-key unit still running on the stove? If it is, which firmware
  is on it? The repo sketch can't switch the stove (PLAN.md bug #1), so it may be running
  an older build.
- **Q2** Shared core: should it live in the M5DialThermo repo, with the 4-key version as a
  second PlatformIO target there? Or should both repos stay separate and share a copied
  header? (I recommend separate repos, with the core header copied into both for now.)
- **Q3** Build tool for the 4-key version: arduino-cli (what it uses now) or PlatformIO
  (what M5Dial uses)?
- **Q4** Hardware upgrades OK for the 4-key version (DS3231 RTC, moving the stove LED off
  pin 0)? Or should it stay on the current wiring?
- **Q6** Can I permanently delete these? They're on disk only (not in git), but each one can
  be rebuilt or downloaded again: `.build\` (empty), `HouseThermo\` (old 2018 clone, now
  redundant), `legacy\2026-experiments\.venv` and `.idea`, the `.uf2` firmware,
  `legacy\build.13Mar2019\` object files, and the duplicate library folders and zips under
  `legacy\Older\Termo\`. I'd keep the vendor PDFs and saved pages as reference.
- **Q5** Can I push commit `4ff70a6` (legacy capture) to the public GitHub repo?

## Answered 2026-10-30

- ✅ Q1 Nothing on the stove. All 3 boards on USB. ✅ Q2 Collapse into one repo (done: m5dial/). ✅ Q3 PlatformIO. ✅ Q4 Hardware changes OK. ✅ Q5 Pushed. ✅ Q6 Junk deleted.
- **Q7** Archive the old GitHub repo VashJuan/M5DialThermo (read-only), with a README line pointing here?
- **Q8** The MicroView clock reads 1/1/00. Can you check or replace the RTC coin cell (CR2032 / LIR2032)?
- **Q9** What is on COM3 (Silicon Labs CP210x)? Is the M5Dial on a data cable?
- ✅ Q8 Cell replaced 2026-10-30; RTC set and running.
- **Q10** The M5Dial's MCP9808 doesn't answer on I2C (999 °F). Is it plugged in, and is the Grove cable OK?
- **Q11** Can I flash the M5Dial with the repo build (DST fix)? I'd back up its current flash first.
