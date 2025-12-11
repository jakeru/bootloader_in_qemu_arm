#include "log.h"

static volatile bool svc_handler_called = false;

void SVC_Handler(void)
{
	LOG("SVC handler in app");
	svc_handler_called = true;
}

int main(void)
{
	LOG("This is the application");

	// Enable interrupts
	__asm volatile("cpsie i" ::: "memory");

	LOG("Triggering SVC exception to test interrupts");

	__asm volatile("svc #0");

	if (svc_handler_called) {
		LOG("SVC Handler was called");
	} else {
		LOG("Error: SVC Handler was not called");
	}

	LOG("Done");

	volatile uint32_t i = 0;
	while (1) {
		i++;
	}
}
