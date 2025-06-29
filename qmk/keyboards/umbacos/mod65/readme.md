# MOD65 Keyboard

![MOD65](https://raw.githubusercontent.com/umbacos/MOD65_keyboard/refs/heads/main/images/cover.jpg)

* **Keyboard Maintainer**: [umbacos](https://github.com/umbacos)
* **Firmware**: [QMK](https://qmk.fm/)
* **Source**: https://github.com/umbacos/MOD65_keyboard

MOD65 is a custom mechanical keyboard designed and built from the ground up
by [umbacos](https://github.com/umbacos). It features a completely custom PCB and a
wide range of modern features for both productivity and aesthetics.

## Features

* **RP2040 Pro Micro**
* **65% ANSI layout**
* **Rotary encoder (knob)**
* **[Unified Daughterboard](https://unified-daughterboard.github.io)** support
* **RGB Matrix LEDs** (per-key RGB lighting)
* **Underglow LED strip**
* **Configurable physical toggle switch**
* **OLED display**
* **O-ring gasket mount** (Friction fit)
* **PCB compatible with [Bakeneko](https://github.com/kkatano/bakeneko-65) case**
* **Built-in [Pomodoro Timer](https://en.wikipedia.org/wiki/Pomodoro_Technique)**
* **Fully open source**
  * **PCB and plate designed with [KiCad 9](https://www.kicad.org/)**
  * **Case designed with [Autodesk Fusion 360](https://www.autodesk.com/products/fusion-360/overview/)**

---

## Compile the Firmware

```sh
qmk compile -kb MOD65 -km default
```

This command compiles the firmware for the MOD65 keyboard using the `default` keymap.

---

## Flash the Firmware

To flash the firmware, you must enter **boot mode** on the PCB.

### Entering Boot Mode

* If no firmware is present, connecting the board via USB will automatically
  enter boot mode.
* If firmware is already flashed:

  * Hold the **BOOT** button located underneath the PCB, then plug in the USB
    cable. Release the button once connected.
  * Alternatively, if this firmware is already running, press the key
    combination: `FN2 + ENTER`.

### Flashing

Once in boot mode, your computer should detect a new USB mass storage device
named something like `RPI-RP2`.

Copy the compiled `.uf2` file (e.g., `MOD65_default.uf2`) directly into the
root of that device. The board will automatically flash and reboot with the
new firmware.
