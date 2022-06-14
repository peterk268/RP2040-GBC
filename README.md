# RP2040-GB for Pico-GB

This is a fork of the [RP2040-GB Game Boy (DMG) emulator from deltabeard](https://github.com/deltabeard/RP2040-GB). 

This fork includes all changes needed for the emulator to run on the [Pico-GB emulation console](https://www.youmaketech.com/pico-gb-raspberry-pi-pico-gameboy-emulation-console/). The Pico-GB is a 3d-printed retro-gaming emulation console that ressembles to the original Nintendo Game Boy released in 1989. 

RP2040-GB is a Game Boy (DMG) emulator [Peanut-GB](https://github.com/deltabeard/Peanut-GB) on the Raspberry Pi RP2040 microcontroller, using an ILI9225 screen.
Runs at more than 70 fps without audio emulation. With frame skip and interlacing, can run at up to 120 fps.

# Raspberry Pi Pico Pins Assignment
UP = GP2
DOWN = GP3
LEFT = GP4
RIGHT = GP5
BUTTON A = GP6
BUTTON B = GP7
SELECT = GP8
START = GP9
BUZZER = GP15
LCD CS = GP17
LCD CLK = GP18
LCD SDI = GP19
LCD RS = GP20
LCD RST = GP21
LCD LED = GP22

# Building

The [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk) is required to build this project. Make sure you are able to compile an [example project](https://github.com/raspberrypi/pico-examples#first--examples) before continuing.

The file `./src/rom.c` is required for this project to compile. This contains the ROM data that will be played by Peanut-GB on the RP2040. To generate this file, the program `xxd` is required. `xxd` is a tool that can convert binary files to a valid C header file, and is packaged with [Vim](https://www.vim.org/) and [NeoVim](https://neovim.io/), prepackaged within the [w64devkit](https://github.com/skeeto/w64devkit) development environment, or can be compiled from source [from the vim repository](https://github.com/vim/vim/tree/master/src/xxd).

Steps:
1. Convert your `*.gb` or `*.gbc`† file to a C header file by executing the following command in a terminal or command prompt:
```sh
xxd -i rom.gb rom.c
```

† *Note that Game Boy Color (GBC) games are not supported with Peanut-GB or RP2040-GB. On load, games that require a GBC hardware will typically display an error message as they will be forced to boot into DMG mode.*

2. Open the `rom.c` file in a text editor, and replace the first line with:
```
#include <pico/platform.h>
const unsigned char __in_flash("rom") rom[] = {
```
Since RP2040-GB is configured to run from internal RAM for performance, the `__in_flash` attribute stops the ROM data from also being copied to the RAM because most ROMs are larger than the available RAM on the RP2040. We also additionally define `const` as this is read-only data.

3. Copy this `rom.c` file to the `src` folder.

The project should now compile with your ROM builtin.

Depending on the license of the ROM that you have built into this project, the output RP2040 binary may not be redistributable under the terms of your local copyright law.

## Future work

Further work is required to improve Peanut-GB for this microcontroller environment. This includes:

- Using an APU that is optimised for space and speed. No, or very few, floating point operations.

## License

MIT
