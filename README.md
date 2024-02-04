# \_HouseThermo

Rev 10 Dec 2018

\_HouseThermo is a simple Arduino app for turning on and off a heater based on the current
temperature, time, a target temperature that varies hour by hour.

A simple Arduino app that turning on and off a heater (e.g., gas stove) based on the
current temperature & time, versus a target temperature that varies hour by hour.

Currently setup to anticipate an Adafruit MicroView Ardunio, with attached DS1307 RTC,
with Dallas DS18B20 thermometer soldered in, and a 4 button switch that enables
temporarily (until next time period) altering the current temperature setting

## Visual Studio Code Build Instructions

- Workspace: d:/docs/john/arduino/\_HouseThermo,
- in HouseThermo.ino, modify the year reset (or not) the Real Time Clock (Tiny RTC),
- In Visual Studio CODE:
  - Use Control-Shift_P to show the command palette & options Things to set:
  - Board Type: Uno
  - COM Port: Whatever lists FTDI next to it (setting saved in Arduino.json), since
    Microview typically (?) shows up as FTDI
  - ?? When Ready:
  - Upload, which automatically compiles, and then if successful, uploads the code to the
    Arduino, which should flicker during the upload...

Verify include paths:  
in the c_cpp_Properties.json file, verify the paths listed:

I believe it only needs "C:\\Users\\John\\Documents\\Arduino\\libraries" in both upper &
lower locations for compilation and upload and operation to succeed.

However Intellisense can't locate the libraires and still lists that as a "Problem". To
avoid that maybe requires hardcoding the full location of each library - or a tweak to how
VS Code and/or Arduino extension handles libraries???

## License

Standard MIT license, copyright ©2024, VashonSoftware.com
