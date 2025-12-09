#include "log.h"

#include <stdint.h>

int main(void)
{
	LOG("This is the application");

	volatile uint32_t i = 0;
	while (1) {
		i++;
	}
}
