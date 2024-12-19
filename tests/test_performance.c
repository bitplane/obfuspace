#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include "../src/obfuspace.h"

void test_encode_speed() {
    char *test_input = "Let's go for 100 chars of text that we want to encode. Some more text. And a bit longer. There, 100";
    int loops = 10000000;
    int32_t result; // Declare result variable

    for (int i = 0; i < loops; ++i) {
        char *pos = test_input;
        while (*pos != 0) {
            result = BYTE_TO_WHITESPACE(*pos);  // Use the result
            pos++;
        }
    }

    // Use result in some way to avoid the compiler optimizing it out
    printf("Last encode result: %d\n", result);
}

void test_decode_speed() {
    char *test_input = "Let's go for 100 chars of text that we want to encode. Some more text. And a bit longer. There, 100";
    int32_t encoded_buffer[1024];
    uint8_t decoded_buffer[1024]; // Use this variable in the loop
    size_t len = strlen(test_input);

    // Manually encode the input string
    for (size_t i = 0; i < len; ++i) {
        encoded_buffer[i] = BYTE_TO_WHITESPACE(test_input[i]);
    }

    int loops = 10000000;
    uint8_t result; // Declare result variable

    for (int i = 0; i < loops; ++i) {
        for (size_t j = 0; j < len; ++j) {
            result = WHITESPACE_TO_BYTE(encoded_buffer[j]);  // Use the result
            decoded_buffer[j] = result; // Store in the decoded buffer to use it
        }
    }

    // Use result and decoded_buffer in some way to avoid the compiler optimizing them out
    printf("Last decode result: %d\n", result);
    printf("First decoded character: %c\n", decoded_buffer[0]);
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
