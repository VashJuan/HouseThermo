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
- ✅ Q10 MCP9808 plugged in, reads OK. ✅ Q11 Flash any device: M5Dial flashed 2026-10-30 (UTC-hour + DST fixes). MicroView retired, kept for future use.
- **Q12** Clean up the graphics/M5 folders as listed in ROADMAP.md "Housekeeping" (about 2.9 GB to delete, all downloadable or rebuildable)? I'd move the small sketches and PDFs first and delete only after you OK it.
- ✅ Q12 Cleanup approved and done 2026-10-30 (ROADMAP.md "Housekeeping"). The final delete was blocked for Claude, so the bulk is in `D:\Projects\Arduino\_ToDelete_2026-10-30\`.
- **Q13** Delete `D:\Projects\Arduino\_ToDelete_2026-10-30\` (2.4 GB) yourself, or allow Claude to? `Remove-Item -LiteralPath 'D:\Projects\Arduino\_ToDelete_2026-10-30' -Recurse -Force`
- **Q14** Delete the GitHub fork VashJuan/lv_port_pc_visual_studio (no commits of yours), or keep it?
- ✅ Q13 John deleted `_ToDelete_2026-10-30` 2026-10-30.
- **Q15** GitHub deletes (Q7: M5DialThermo, Q14: lv_port_pc_visual_studio fork) need the `delete_repo` scope. Run `gh auth refresh -h github.com -s delete_repo` (opens a browser), then tell Claude to go, or run `gh repo delete VashJuan/M5DialThermo --yes` and `gh repo delete VashJuan/lv_port_pc_visual_studio --yes` yourself.
- **Q16** Plug in the M5Dial (it wasn't on USB 2026-10-30) so Claude can run the I2C scan and flash the relay-state fix.
- ✅ Q7 John deleted GitHub VashJuan/M5DialThermo 2026-10-30. ✅ Q16 M5Dial plugged in; flashed and bench tested.
- **Q17** OFF bench test: when the Dial shows ON, turn the dial below the room temperature (about 66 °F) and leave it plugged in for 4 minutes. Tell Claude when you've done it.
