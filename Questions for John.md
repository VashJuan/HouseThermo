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
- **Q5** Can I push commit `4ff70a6` (legacy capture) to the public GitHub repo?
