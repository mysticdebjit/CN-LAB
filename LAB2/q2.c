#include <stdio.h>
#include <string.h>

struct pkt {
    char ch1;
    char ch2[2];
    char ch3;
};

int main() {
    struct pkt data;
    int num;
    
    printf("Enter a number: ");
    scanf("%d", &num);
    
    data.ch1 = (char)((num >> 24) & 0xFF);
    data.ch2[0] = (char)((num >> 16) & 0xFF);
    data.ch2[1] = (char)((num >> 8) & 0xFF);
    data.ch3 = (char)(num & 0xFF);
    
    printf("Content of ch1: %d\n", data.ch1);
    printf("Content of ch2[0]: %d\n", data.ch2[0]);
    printf("Content of ch2[1]: %d\n", data.ch2[1]);
    printf("Content of ch3: %d\n", data.ch3);
    
    int aggregatedNum = ((int)data.ch1 << 24) | ((int)data.ch2[0] << 16) | ((int)data.ch2[1] << 8) | (int)data.ch3;
    
    printf("Aggregated number: %d\n", aggregatedNum);
    
    return 0;
}

