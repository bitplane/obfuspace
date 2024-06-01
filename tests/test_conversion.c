#include <stdio.h>
#include "../src/obfuspace.h"


void print_bits(char c) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (c >> i) & 1);
    }
}

int test_whitespace_to_crumb() {
    return WHITESPACE_TO_CRUMB(' ') == 0 &&
           WHITESPACE_TO_CRUMB('\t') == 1 &&
           WHITESPACE_TO_CRUMB('\n') == 2 &&
           WHITESPACE_TO_CRUMB('\r') == 3;
}

int test_crumb_to_whitespace() {
    return CRUMB_TO_WHITESPACE(0) == ' ' &&
           CRUMB_TO_WHITESPACE(1) == '\t' &&
           CRUMB_TO_WHITESPACE(2) == '\n' &&
           CRUMB_TO_WHITESPACE(3) == '\r';
}

int test_get_crumb() {
    return GET_CRUMB(0b11000000, 0) == 3 &&
           GET_CRUMB(0b00110000, 1) == 3 &&
           GET_CRUMB(0b00001100, 2) == 3 &&
           GET_CRUMB(0b00000011, 3) == 3;
}

int test_set_crumb() {
    return SET_CRUMB(3, 0) == 0b11000000 &&
           SET_CRUMB(3, 1) == 0b00110000 &&
           SET_CRUMB(3, 2) == 0b00001100 &&
           SET_CRUMB(3, 3) == 0b00000011;
}

int test_get_byte() {
    // get a byte from a 4-byte integer
    unsigned int val = 0x12345678;

    return GET_BYTE(val, 0) == 0x12 &&
           GET_BYTE(val, 1) == 0x34 &&
           GET_BYTE(val, 2) == 0x56 &&
           GET_BYTE(val, 3) == 0x78;
}

int test_set_byte() {
    // set a byte in a 4-byte integer
    unsigned int val = 0x12;
    return SET_BYTE(val, 0) == 0x12000000 &&
           SET_BYTE(val, 1) == 0x00120000 &&
           SET_BYTE(val, 2) == 0x00001200 &&
           SET_BYTE(val, 3) == 0x00000012;
}

int test_whitespace_to_byte() {
    //            " \t\n\r"
    int value = 0x20090a0d;
    return WHITESPACE_TO_BYTE(value) == 0b00011011;
}

int test_byte_to_whitespace() {
    //            " \t\n\r"
    int value = 0b00011011;
    return BYTE_TO_WHITESPACE(value) == 0x20090a0d;
}


int main() {
    printf("test_whitespace_to_crumb: %d\n", test_whitespace_to_crumb());
    printf("test_crumb_to_whitespace: %d\n", test_crumb_to_whitespace());
    printf("test_get_crumb: %d\n", test_get_crumb());
    printf("test_set_crumb: %d\n", test_set_crumb());
    printf("test_get_byte: %d\n", test_get_byte());
    printf("test_set_byte: %d\n", test_set_byte());
    printf("test_whitespace_to_byte: %d\n", test_whitespace_to_byte());
    printf("test_byte_to_whitespace: %d\n", test_byte_to_whitespace());

    return 0;
}