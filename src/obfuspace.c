#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "obfuspace.h"

#define BUFFER_SIZE 10240

size_t encode_bytes(const uint8_t *input, int32_t *output, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        output[i] = BYTE_TO_WHITESPACE(input[i]);
    }
    return size;
}

size_t decode_bytes(const int32_t *input, uint8_t *output, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        output[i] = WHITESPACE_TO_BYTE(input[i]);
    }
    return size;
}

void encode_stdio() {
    uint8_t input_buffer[BUFFER_SIZE];
    int32_t output_buffer[BUFFER_SIZE];
    size_t bytes_read;

    while ((bytes_read = fread(input_buffer, 1, BUFFER_SIZE, stdin)) > 0) {
        size_t processed = encode_bytes(input_buffer, output_buffer, bytes_read);
        fwrite(output_buffer, sizeof(int32_t), processed, stdout);
    }
}

void decode_stdio() {
    int32_t input_buffer[BUFFER_SIZE];
    uint8_t output_buffer[BUFFER_SIZE];
    size_t bytes_read;

    while ((bytes_read = fread(input_buffer, sizeof(int32_t), BUFFER_SIZE, stdin)) > 0) {
        size_t processed = decode_bytes(input_buffer, output_buffer, bytes_read);
        fwrite(output_buffer, 1, processed, stdout);
    }
}

void auto_stdio() {
    int32_t first_four_bytes = 0;
    size_t bytes_read = fread(&first_four_bytes, 1, sizeof(first_four_bytes), stdin);

    if (bytes_read < sizeof(first_four_bytes)) {
        // Not enough bytes, encode what we have
        uint8_t input_buffer[BUFFER_SIZE];
        memcpy(&input_buffer, &first_four_bytes, bytes_read);
        int32_t output_buffer[BUFFER_SIZE];
        size_t processed = encode_bytes(input_buffer, output_buffer, bytes_read);
        fwrite(output_buffer, sizeof(int32_t), processed, stdout);
    } else {
        // Determine if the first four bytes are encoded
        if (IS_WHITESPACE_32(first_four_bytes)) {
            // Write the first 4 bytes as decoded
            uint8_t output_buffer[4];
            decode_bytes(&first_four_bytes, output_buffer, 1);
            fwrite(output_buffer, 1, 4, stdout);
            // Continue decoding the rest
            decode_stdio();
        } else {
            // Write the first 4 bytes as encoded
            int32_t output_buffer[1];
            encode_bytes((uint8_t *)&first_four_bytes, output_buffer, 4);
            fwrite(output_buffer, sizeof(int32_t), 4, stdout);
            // Continue encoding the rest
            encode_stdio();
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        // No arguments, default to auto
        auto_stdio();
    } else if (argc == 2) {
        if (strcmp(argv[1], "-e") == 0) {
            encode_stdio();
        } else if (strcmp(argv[1], "-d") == 0) {
            decode_stdio();
        } else if (strcmp(argv[1], "-a") == 0) {
            auto_stdio();
        } else {
            fprintf(stderr, "Invalid option: %s\n", argv[1]);
            fprintf(stderr, "Usage: %s [-e (encode) | -d (decode) | -a (auto)]\n", argv[0]);
            return 1;
        }
    } else {
        fprintf(stderr, "Usage: %s [-e (encode) | -d (decode) | -a (auto)]\n", argv[0]);
        return 1;
    }

    return 0;
}

