#include "log.h"

// Application start address (from app.ld)
#define APP_START_ADDR 0x00020000

// Location of Vector Table Offset Register (VTOR)
#define SCB_VTOR ((volatile uint32_t *)0xE000ED08)

static volatile bool svc_handler_called = false;

// Sets the Vector Table Offset Register (VTOR)
static void set_vtor(uint32_t offset)
{
	*SCB_VTOR = offset;
}

void SVC_Handler(void)
{
	LOG("SCV Handler in bootloader");
	svc_handler_called = true;
}

// Jumps to application at specified address
static void jump_to_app(uint32_t app_addr)
{
	// Get pointer to application vector table
	// It should be located at the beginning of the application memory
	const void **app_vector_table = (const void **)app_addr;

	// Get reset handler from application vector table
	const void *app_reset_handler = app_vector_table[1];
	typedef void (*reset_handler_t)(void);
	reset_handler_t app_reset = app_reset_handler;

	// Disable interrupts before jumping
	__asm volatile("cpsid i" ::: "memory");

	// Set VTOR to beginning of application memory
	set_vtor(app_addr);

	// Set stack pointer to application's stack pointer
	const void *app_stack_pointer = app_vector_table[0];
	__asm volatile("msr msp, %0\n" : : "r"(app_stack_pointer));

	// Jump to application reset handler
	app_reset();
}

int main(void)
{
	LOG("Booting application at 0x00020000");

	LOG("Triggering SVC exception to test interrupts");

	__asm volatile("svc #0");

	if (svc_handler_called) {
		LOG("SVC Handler was called");
	} else {
		LOG("Error: SVC Handler was not called");
	}

	LOG("Jumping to application");

	// Jump to application
	jump_to_app(APP_START_ADDR);

	// Should never reach here
	while (1)
		;
}
