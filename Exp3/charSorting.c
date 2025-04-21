#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* frequencySort(char* s) {
    int frequency[256] = {0};
    int len = strlen(s);
    for (int i = 0; i < len; i++){
        frequency[(unsigned char)s[i]] += 1;
    }
    typedef struct{
        int frequency;
        char ascii;
    }Char;
    Char arr[256];
    int arrSize = 0;
    for (int i = 0; i < 256; i++) {
        if (frequency[i] > 0) {
            arr[arrSize].frequency = frequency[i];
            arr[arrSize].ascii = (char) i;
            arrSize += 1;
        }
    }

    for (int i = 0; i < arrSize; i++) {
        for (int j = 0; j < arrSize - 1 - i; j++) {
            if (arr[j].frequency < arr[j + 1].frequency ||
            arr[j].frequency == arr[j + 1].frequency && arr[j].ascii > arr[j + 1].ascii) {
                Char tmp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = tmp;
            }
        }
    }
    
    // print
    char *str = malloc(sizeof(char) * 100);
    int pos = 0;
    for (int i = 0; i < arrSize; i++) {
        for (int j = arr[i].frequency; j > 0; j--) {
            str[pos++] = arr[i].ascii;
        }
    }
    return str;
}

int main() {
    char s[1000];
    scanf("%s", s);
    
    char* result = frequencySort(s);
    printf("%s\n", result);
    
    return 0;
}