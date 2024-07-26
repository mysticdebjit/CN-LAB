#include <stdio.h>

int isLittleEndian() {
    unsigned int x = 1;
    char *c = (char*)&x;
    return (int)*c;
}

unsigned int convertEndianness(unsigned int num) {
    return ((num >> 24) & 0x000000FF) |
           ((num >>  8) & 0x0000FF00) |
           ((num <<  8) & 0x00FF0000) |
           ((num << 24) & 0xFF000000);
}

int main() {
    unsigned int num;
    printf("Enter a number: ");
    scanf("%u", &num);

    if (isLittleEndian()) {
        printf("Host machine is Little Endian\n");
    } else {
        printf("Host machine is Big Endian\n");
    }

    unsigned char *bytePointer = (unsigned char*)&num;
    printf("Byte content in memory:\n");
    for (int i = 0; i < sizeof(num); i++) {
        printf("Byte %d: %02x\n", i, bytePointer[i]);
    }

    unsigned int convertedNum = convertEndianness(num);
    printf("Number after converting endianness: %u\n", convertedNum);

    bytePointer = (unsigned char*)&convertedNum;
    printf("Byte content in memory after conversion:\n");
    for (int i = 0; i < sizeof(convertedNum); i++) {
        printf("Byte %d: %02x\n", i, bytePointer[i]);
    }

    return 0;
}

