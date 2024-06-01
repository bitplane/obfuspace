#include <stdio.h>
#include <time.h>
#include "../src/obfuspace.h"


void test_encode_speed() {

    char* test_input = "Let's go for 100 chars of text that we want to encode. Some more text. And a bit longer. There, 100";
    int loops = 10000000;

    for (int i=0; i < loops; ++i) {
        char *pos=test_input;
        while(*pos != 0) {
            BYTE_TO_WHITESPACE(*pos);
            pos++;
        }
    }
}

int main() {
    clock_t start, end;
    double cpu_time_used;

    start = clock(); // Start the clock
    test_encode_speed();
    end = clock(); // End the clock

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; // Calculate the elapsed time

    printf("Took %f seconds to execute\n", cpu_time_used);

    return 0;
}
