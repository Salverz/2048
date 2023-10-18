#include <stdio.h>

int main(void) {
    for (int i = 0; i < 16; i++) {
        printf("%d ", i / 4 + (i % 4) * 4);
    }

    return 0;
}