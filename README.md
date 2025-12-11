# Test of QEMU and Bootloader

A simple ARM Cortex-M3 bootloader that runs in QEMU. The bootloader loads and
executes an application from a fixed address.

Semihosting is used for printing output to the console.

Written by Jakob Ruhe with help from modern tools during an evening in December
2025.

## Prerequisites

``` sh
apt install gcc-arm-none-eabi qemu-system-arm
```

## Building

Build both the bootloader and application:

``` sh
make
```

## Running

Run the bootloader with the application in QEMU:

```bash
make run
```

This starts QEMU emulating an MPS2-AN385 board with the bootloader, which then
loads and executes the application.

On the console, something like this should be shown:

```
Booting application at 0x00020000
Triggering SVC exception to test interrupts
SCV Handler in bootloader
SVC Handler was called
Jumping to application
This is the application
Triggering SVC exception to test interrupts
SVC handler in app
SVC Handler was called
Done
```

Stop the emulation with ctrl+c.

## Debugging

In one terminal:

``` sh
make debug
```

And follow the instructions about how to launch `gdb-multiarch` in another
terminal to connect to it.
