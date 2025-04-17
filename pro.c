#include <reg51.h>
#include <stdio.h>

// Pins
sbit Trig = P2^0;
sbit Echo = P2^1;

// UART Init
void UART_Init() {
    SCON = 0x50;      // 8-bit UART, REN enabled
    TMOD |= 0x20;     // Timer1, Mode 2, auto-reload
    TH1 = 0xFD;       // Baud rate 9600 for 11.0592MHz
    TL1 = 0xFD;
    TR1 = 1;          // Start Timer1
}

// Send string over UART
void UART_SendString(char* str) {
    while (*str) {
        SBUF = *str;
        while (!TI);
        TI = 0;
        str++;
    }
}

// Delay in microseconds (approximate)
void delay_us(unsigned int us) {
    while(us--);
}

// Delay in milliseconds
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 1275; j++);
}

// Get distance in cm from ultrasonic sensor
unsigned int get_distance() {
    unsigned int time = 0;

    Trig = 0;
    delay_us(2);
    Trig = 1;
    delay_us(10);
    Trig = 0;

    while (!Echo); // Wait until Echo goes HIGH
    while (Echo) { // Measure duration Echo stays HIGH
        time++;
        delay_us(10);
    }

    return time / 58; // Convert time to distance (cm)
}

void main() {
    unsigned int distance;

    UART_Init(); // Initialize UART

    while(1) {
        distance = get_distance();

        if (distance > 0 && distance <= 15) {
            UART_SendString("obstacle detected\n");
        } else {
            UART_SendString("no obstacle\n");
        }

        delay_ms(500);
    }
}
