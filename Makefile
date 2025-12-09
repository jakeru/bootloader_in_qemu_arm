QEMU_BASE = -M mps2-an385 -display none -monitor none -semihosting-config enable=on,target=native

CC = arm-none-eabi-gcc
CFLAGS = -mcpu=cortex-m3 -mthumb -nostartfiles -g -Og

TARGET_BL = bootloader.elf
LDFLAGS_BL = -T bootloader.ld

TARGET_APP = app.elf
LDFLAGS_APP = -T app.ld

SOURCES = startup.c log.c

SOURCES_APP = $(SOURCES) app.c
OBJECTS_APP = $(SOURCES_APP:.c=.o)

SOURCES_BL = $(SOURCES) bootloader.c
OBJECTS_BL = $(SOURCES_BL:.c=.o)

all: $(TARGET_BL) $(TARGET_APP)

$(TARGET_BL): $(OBJECTS_BL) Makefile
	$(CC) $(CFLAGS) $(LDFLAGS_BL) $(OBJECTS_BL) -o $(TARGET_BL)

$(TARGET_APP): $(OBJECTS_APP) Makefile
	$(CC) $(CFLAGS) $(LDFLAGS_APP) $(OBJECTS_APP) -o $(TARGET_APP)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET_BL) $(TARGET_APP)
	qemu-system-arm $(QEMU_BASE) -kernel $(TARGET_BL) -device loader,file=$(TARGET_APP),addr=0x20000

debug: $(TARGET_BL) $(TARGET_APP)
	@echo "Starting QEMU with GDB server on port 1234"
	@echo "Connect with: "
	@echo "gdb-multiarch $(TARGET_BL) -ex 'target remote localhost:1234' -ex 'add-symbol-file $(TARGET_APP) 0x20000'"
	qemu-system-arm $(QEMU_BASE) -kernel $(TARGET_BL) -device loader,file=$(TARGET_APP),addr=0x20000 -s -S

clean:
	rm -f $(OBJECTS_APP) $(OBJECTS_BL) $(TARGET_APP) $(TARGET_BL)

.PHONY: all clean run debug
