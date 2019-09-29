# bse-fsw-template
A template project for BSE flight software projects. Built to work with Atmel START generated ASF4 projects, on the Atmel SAMD21J18A processor.

## Building
Run `make`. The produced binaries will end up in `build/`

## Deploying to microcontroller
1. Make sure you've built the code with `make`
2. Make sure you're connected to the board or debugger
3. From within this project directory, start `openocd`
4. In a new terminal within this project directory, run `make connect`
5. At the `(gdb)` prompt run `load` to upload the binary to the microcontroller
6. Run `monitor reset halt` to reset the microcontroller and start debugging
7. Type `c` to run (continue) the program
   1. If you want to step through your code, set any breakpoints you need before this (ex. via `break main`)

Tips: 
- To halt the code and get back to the debugger, do `Ctrl-C`
- To rebuild the code without closing gdb, run `make` at the `(gdb)` prompt and repeat steps 5-7

## Installing the Toolchain
### Windows
1. Install [Chocolatey](https://chocolatey.org/install#installing-chocolatey)
2. Run `choco install make` from a shell with administrator priveledges (right click -> Run as administrator)
3. Download and extract the [Atmel ARM GNU toolchain](https://www.microchip.com/mplab/avr-support/avr-and-arm-toolchains-c-compilers) and add it to your path (e.g. Control Panel -> System -> Advanced system settings -> Environment variables -> Path -> Edit -> New -> `C:\Users\<username>\<path>\arm-none-eabi\bin`).
4. Download and extract the newest Windows version of OpenOCD from [here](https://github.com/gnu-mcu-eclipse/openocd/releases) and add the bin folder to your path (e.g. `C:\Users\<username>\<path>\openocd-0.10.0\bin`). If you have trouble with that version you can also use [this site](http://www.freddiechopin.info/en/download/category/4-openocd) (you'll need something like [7-Zip](https://www.7-zip.org/)).

### Mac OSX
1. Install homebrew [here](https://brew.sh/)
2. Install ARM developer tools: 
```
brew tap PX4/homebrew-px4
brew update
brew search px4
brew install gcc-arm-none-eabi-80
```
3. Install openocd: `brew install openocd`

### Linux (Ubuntu)
1. Install openocd: `sudo apt install openocd`. Unfortunately this doesn't seem to add required udev rules, so you'll need to:
    1. Download the udev rules: `wget https://repo.or.cz/openocd.git/blob_plain/HEAD:/contrib/60-openocd.rules`
    2. Set the rules' owner to root: `sudo chown root:root 60-openocd.rules`
    3. Set the rules' permissions: `sudo chmod 644 60-openocd.rules`
    4. Move the rules: `sudo mv 60-openocd.rules /etc/udev/rules.d/`
    5. Add yourself to the plugdev group: `sudo usermod -a -G plugdev $USERNAME`
    6. Probably log out or reboot. Just running `sudo udevadm control --reload` might also work.
2. Install the ARM GNU Toolchain: `sudo apt install gcc-arm-none-eabi`

### Linux (other distributions)
1. openocd is probably in your package manager, but if not there are instructions [here](http://openocd.org/getting-openocd/). Make sure to put (or symlink) the bin folder in your path.
2. You may need to follow the instructions above to add the udev rules.
3. Install the ARM GNU toolchain from [here](https://www.microchip.com/mplab/avr-support/avr-and-arm-toolchains-c-compilers), and put (or symlink) the bin folder in your path (it may also be in your package manager).

## Changing ASF library configuration
Follow this procedure if you'd like to add Atmel Start ASF libraries, change chip configuration or pinout, etc.
1. Go to [start.atmel.com](start.atmel.com)
2. Click on "Load project from file" and upload `./asf-samd21/atmel_start_config.atstart`
4. As desired, add software components, configure pinmux, package, or clocks
5. Click "Export project", make sure "Makefile (standalone)" is selected, and click "Download pack"
8. Change the `.atzip` file extension on the file you downloaded to `.zip` and extract it
10. Delete the `main.c` file in the downloaded directory
11. Delete the contents of `./asf-samd21/` and copy all files in the downloaded directory there
12. Modify `ATMEL_SRC_DIRS` and `ATMEL_INCLUDE_DIRS` in `./Makefile` according to the instructions there. You may need to make further modifications in `./Makefile` based on changes made by Atmel Start to `./asf-samd21/gcc/Makefile` (to see what changed, do `git diff ./asf-samd21/gcc/Makefile`).