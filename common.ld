ENTRY(Reset_Handler)

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
