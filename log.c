#include "log.h"

static void semihost_write0(const char *s)
{
	// Semihosting SYS_WRITE0: write null-terminated string
	__asm volatile("mov r0, #0x04\n" // SYS_WRITE0 operation
		       "mov r1, %0\n"    // String address parameter
		       "bkpt #0xAB\n"    // Semihosting breakpoint
		       :
		       : "r"(s)
		       : "r0", "r1", "memory");
}

void log_msg(const char *s)
{
	semihost_write0(s);
	semihost_write0("\n");
}
