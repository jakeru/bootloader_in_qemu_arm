ENTRY(Reset_Handler)

MEMORY
{
  FLASH (rx) : ORIGIN = 0x0000000, LENGTH = 128K
  APP (rx) : ORIGIN = 0x00020000, LENGTH = 384K
  RAM   (rwx): ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS
{
  .text : {
    KEEP(*(.isr_vector))
    *(.text*)
    *(.rodata*)
    *(.ARM.exidx*)
    *(.ARM.extab*)
    *(.eh_frame*)
  } > FLASH

  .data : AT(ADDR(.text) + SIZEOF(.text)) {
    _data_start = .;
    *(.data*)
    _data_end = .;
  } > RAM
  _edata = ADDR(.text) + SIZEOF(.text);

  .bss : {
    __bss_start__ = .;
    *(.bss*)
    *(COMMON)
    __bss_end__ = .;
  } > RAM

  __end__ = .;
  end = __end__;
}
