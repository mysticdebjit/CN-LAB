#include <stdio.h>

int main() {
    int number;

    printf("Enter a decimal number: ");
    scanf("%d", &number);

    unsigned char byte1, byte2, byte3, byte4;

    byte1 = (number & 0xFF);
    byte2 = (number >> 8) & 0xFF;
    byte3 = (number >> 16) & 0xFF;
    byte4 = (number >> 24) & 0xFF;

    printf("Byte 1: %x\n", byte1);
    printf("Byte 2: %x\n", byte2);
    printf("Byte 3: %x\n", byte3);
    printf("Byte 4: %x\n", byte4);

    return 0;
}

