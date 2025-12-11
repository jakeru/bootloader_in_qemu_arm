#include "common.h"

int main(void);

void Reset_Handler(void);
void Hardfault_Handler(void);
void SVC_Handler(void);

static uint32_t stack[1024];

__attribute__((section(".isr_vector"))) const void *vector_table[] = {
	[0] = &stack[sizeof(stack) / sizeof(stack[0])],
	[1] = Reset_Handler,
	[3] = Hardfault_Handler,
	[11] = SVC_Handler,
};

void Reset_Handler(void)
{
	extern uint32_t _data_start;
	extern uint32_t _data_end;
	extern uint32_t _edata;
	extern uint32_t __bss_start__;
	extern uint32_t __bss_end__;

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

void Hardfault_Handler(void)
{
	while (1)
		;
}
