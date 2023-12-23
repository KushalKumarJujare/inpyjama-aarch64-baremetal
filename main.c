/**
 * Copyright © 2023 inpyjama.com. All Rights Reserved.
 * Author: Mahmad Bharmal <mahmad@inpyjama.com>
 */

#define w32(addr, value) *((volatile unsigned int *) addr) = value
#define r32(addr) *((volatile unsigned int *) addr)

void uart_init (void) {
    w32(0xFE215004, 1);
    w32(0xFE215044, 0);
    w32(0xFE215060, 0);
    w32(0xFE21504c, 3);
    w32(0xFE215050, 0);
    w32(0xFE215044, 0);
    w32(0xFE215048, 0xC6);
    w32(0xFE215068, ((200000000/(115200*8))-1));
    w32(0xFE200004, ((2 << 12) | (2 << 15)));
    w32(0xFE215060, 3);
}

void uart_putc (const char c) {
    while (!(r32(0xFE215054) & 0x20));
    w32(0xFE215040, (unsigned int) c);
}

void uart_puts(const char* s) {
    while (*s != '\0') {
        uart_putc(*s);
        if (*s == '\n') {
            uart_putc('\r');
        }
        s++;
    }
}

void main()
{
    uart_init();
    uart_putc('\n');
    uart_puts("   __  __\n");
    uart_puts("  /  ||  \\\n");
    uart_puts(" /   /\\   \\\n");
    uart_puts("/___/  \\___\\\n");
    uart_putc('\n');
    uart_puts(" Welcome to inpyjama.com!\n");
    uart_puts(" YouTube: https://tinyurl.com/inpyjama-aarch64\n");

    while(1);
}