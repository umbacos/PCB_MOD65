# Mod65 Keyboard

![Mod65](https://raw.githubusercontent.com/pioz/aryess_keyboard/refs/heads/main/images/cover.jpg)

* **Keyboard Maintainer**: [umbacos](https://github.com/umbacos)
* **Firmware**: [QMK](https://qmk.fm/)
* **Source**: https://github.com/umbacos/MOD65

MOD65 is a custom mechanical keyboard designed and built from the ground up
by [umbacos](https://github.com/umbacos). It features a custom PCB based on
the [Aryess](https://github.com/pioz/aryess_keyboard) design but with some
improvements and differences.

## Features

* **RP2040 Pro Micro**
* **68% ANSI layout**
* **Rotary encoder (knob)**
* **[Unified Daughterboard](https://unified-daughterboard.github.io)** support
* **RGB Matrix LEDs** (per-key RGB lighting)
* **Underglow LED strip**
* **Configurable physical toggle switch**
* **OLED display**
* **O-ring gasket mount** (Friction fit)
* **PCB compatible with most 68% cases **
* **Built-in [Pomodoro Timer](https://en.wikipedia.org/wiki/Pomodoro_Technique)**
* **Fully open source**
  * **PCB and plate designed with [KiCad 9](https://www.kicad.org/)**
  * **Case designed with [Autodesk Fusion 360](https://www.autodesk.com/products/fusion-360/overview/)**

## Built it yourself

You can build your own **MOD65** keyboard by following these steps.

### Order the PCB and Plate

The PCB and plate production files are ready for you. You only need to upload them to JLCPCB:

* **PCB Production File:** `pcb/production/mod65_2.zip`
* **Plate Production File:** `plate/production/mod65_plate_2.zip`

Go to [https://jlcpcb.com/](https://jlcpcb.com/), and upload both files.

When ordering the PCB:

* Select the **PCB Assembly** option.
* JLCPCB will take care of soldering the components for you.
* Minimum order quantity is 5 units.

You will receive fully assembled PCBs at home.

### Order the Case

For the case, upload the file `case/MOD65 Case.step` to a 3D printing service.
You can use any 3D printing service if you prefer.

### Purchase the Extra Components

You will need some additional components. Here is the full list with purchase links:

| Component                 | Description                           | Purchase Link                                                                                                  |
| ------------------------- | ------------------------------------- | -------------------------------------------------------------------------------------------------------------- |
| **OLED Display**          | SSD1306 OLED 128 x 32                 | [Buy on Amazon](https://www.amazon.it/dp/B079H2C7WH)                                                           |
| **JST Cables**            | 3x JST 4-pin 1mm pitch cables         |                                                                                                                |
|                           | 1x JST 3-pin 1mm pitch cable          |                                                                                                                |
| **Rubber Feet**           | Round 20mm diameter rubber feet       | [Buy on Amazon](https://www.amazon.it/dp/B089SH84C4)                                                           |
| **Rotary Encoder**        | Rotary encorder (EC11 compatible)     | [Buy on Amazon](https://www.amazon.it/dp/B0B63YN466)                                                           |
| **Knob**                  | Metal knob for rotary encoder         | [Buy on Amazon](https://www.amazon.it/dp/B0CRRDYKQK)                                                           |
| **LED Strip**             | APA102-compatible LED strip, \~27.5cm | [Buy on Amazon](https://www.amazon.it/dp/B0B3HDNFVM)                                                           |
| **Stabilizers**           | MX compatible keyboard stabilizers    | [Buy on Amazon](https://www.amazon.it/dp/B01LW5B69T)                                                           |
| **Toggle Switch**         | On/Off switch                         | [Buy on Amazon](https://www.amazon.it/dp/B07J4KB38W)                                                           |
| **Unified Daughterboard** | USB-C daughterboard                   | [Buy on 42keebs](https://42keebs.eu/shop/parts/unified-daughterboard-udb-c3-c4-c5/?attribute_version=C5%20JSH) |
| **O-Ring Gasket**         | VMQ-50 (Silicone 50 duro), AS568-264  | [Buy on Amazon](https://www.amazon.it/dp/B07CVKV6DV)                                                           |
| **Foam Sheet**            | Foam for case/PCB dampening           | [Buy on Amazon](https://www.amazon.it/dp/B0CNVRGXWB)                                                           |

Some items can be found from different sellers depending on your country.

### Assembly

Once you have received the PCB, plate, case, and all components, you can start assembling your MOD65 keyboard.

## Compile the Firmware

```sh
qmk compile -kb umbacos/mod65 -km default
```

This command compiles the firmware for the MOD65 keyboard using the `default` keymap.

---

## Flash the Firmware

To flash the firmware, you must enter **boot mode** on the PCB.

### Entering Boot Mode

* If no firmware is present, connecting the board via USB will automatically
  enter boot mode.
* If firmware is already flashed:

  * Hold the **BOOT** button located on the PCB, then plug in the USB
    cable. Release the button once connected.
  * Alternatively, if this firmware is already running, press the key
    combination: `FN2 + ENTER`.

### Flashing

Once in boot mode, your computer should detect a new USB mass storage device
named something like `RPI-RP2`.

Copy the compiled `.uf2` file (e.g., `umbacos/mod65_default.uf2`) directly into the
root of that device. The board will automatically flash and reboot with the
new firmware.
