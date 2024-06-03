#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include "../src/obfuspace.h"

void test_encode_speed() {
    char *test_input = "Let's go for 100 chars of text that we want to encode. Some more text. And a bit longer. There, 100";
    int loops = 10000000;

    for (int i = 0; i < loops; ++i) {
        char *pos = test_input;
        while (*pos != 0) {
            BYTE_TO_WHITESPACE(*pos);
            pos++;
        }
    }
}

void test_decode_speed() {
    char *test_input = "Let's go for 100 chars of text that we want to encode. Some more text. And a bit longer. There, 100";
    int32_t encoded_buffer[1024];
    uint8_t decoded_buffer[1024];
    size_t len = strlen(test_input);

    // Manually encode the input string
    for (size_t i = 0; i < len; ++i) {
        encoded_buffer[i] = BYTE_TO_WHITESPACE(test_input[i]);
    }

    int loops = 10000000;

    for (int i = 0; i < loops; ++i) {
        for (size_t j = 0; j < len; ++j) {
            WHITESPACE_TO_BYTE(encoded_buffer[j]);
        }
    }
}

int main() {
    clock_t start, end;
    double cpu_time_used;

    // Test encoding speed
    start = clock(); // Start the clock
    test_encode_speed();
    end = clock(); // End the clock
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC; // Calculate the elapsed time
    double encode_speed = (100 * 10000000 / 1024.0 / 1024.0) / cpu_time_used; // MB per second
    printf("Encoding took %f seconds, speed: %f MB/s\n", cpu_time_used, encode_speed);

    // Test decoding speed
    start = clock(); // Start the clock
    test_decode_speed();
    end = clock(); // End the clock
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC; // Calculate the elapsed time
    double decode_speed = (100 * 10000000 / 1024.0 / 1024.0) / cpu_time_used; // MB per second
    printf("Decoding took %f seconds, speed: %f MB/s\n", cpu_time_used, decode_speed);

    return 0;
}
