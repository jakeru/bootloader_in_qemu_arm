#include <stdint.h>

#include "log.h"

// Application start address (from app.ld)
#define APP_START_ADDR 0x00020000

// Jump to application at specified address
static void jump_to_app(uint32_t app_addr)
{
	// Get pointers to application vector table
	uint32_t *app_vector_table = (uint32_t *)app_addr;
	uint32_t app_stack_pointer = app_vector_table[0];
	uint32_t app_reset_handler = app_vector_table[1];

	// Function pointer type for reset handler
	void (*app_reset)(void) = (void (*)(void))app_reset_handler;

	// Disable interrupts before jumping
	__asm volatile("cpsid i" ::: "memory");

	// Set stack pointer to application's stack pointer
	__asm volatile("msr msp, %0\n" : : "r"(app_stack_pointer));

	// Jump to application reset handler
	app_reset();
}

int main(void)
{
	LOG("=== Bootloader starting ===");
	LOG("Printing boot message...");
	LOG("Booting application at 0x00020000");
	LOG("===========================");

	// Jump to application
	jump_to_app(APP_START_ADDR);

	// Should never reach here
	while (1)
		;
}
