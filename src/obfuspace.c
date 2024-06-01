#include <stdio.h>
#include <stdint.h>
#include "obfuspace.h"

#define BUFFER_SIZE 10240

int main(int argc, char *argv[]) {
    uint8_t input_buffer[BUFFER_SIZE];
    int32_t output_buffer[BUFFER_SIZE];
    size_t bytes_read, i;

    while ((bytes_read = fread(input_buffer, 1, BUFFER_SIZE, stdin)) > 0) {
        for (i = 0; i < bytes_read; ++i) {
            output_buffer[i] = BYTE_TO_WHITESPACE(input_buffer[i]);
        }
        fwrite(output_buffer, sizeof(int32_t), bytes_read, stdout);
    }

    return 0;
}