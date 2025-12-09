#include <stdint.h>

extern int main(void);

extern uint32_t _data_start;
extern uint32_t _data_end;
extern uint32_t _edata;
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;

void Reset_Handler(void);
void Default_Handler(void);

__attribute__((section(".isr_vector")))
const uint32_t vector_table[] = {0x20020000, // Initial stack pointer
				 (uint32_t)Reset_Handler};

void Reset_Handler(void)
{
	// Copy .data section from FLASH to RAM
	uint32_t *data_src = &_edata;
	uint32_t *data_dst = &_data_start;
	while (data_dst < &_data_end) {
		*data_dst++ = *data_src++;
	}

	// Zero out .bss section
	uint32_t *bss_start = &__bss_start__;
	uint32_t *bss_end = &__bss_end__;
	while (bss_start < bss_end) {
		*bss_start++ = 0;
	}

	main();
	while (1)
		;
}

void Default_Handler(void)
{
	while (1)
		;
}
