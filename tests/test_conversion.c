#include <stdio.h>
#include <assert.h>
#include "../src/obfuspace.h"

void print_bits(char c) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (c >> i) & 1);
    }
}

void test_whitespace_to_crumb() {
    assert(WHITESPACE_TO_CRUMB(' ') == 0);
    assert(WHITESPACE_TO_CRUMB('\t') == 1);
    assert(WHITESPACE_TO_CRUMB('\n') == 2);
    assert(WHITESPACE_TO_CRUMB('\r') == 3);
    printf("test_whitespace_to_crumb passed\n");
}

void test_crumb_to_whitespace() {
    assert(CRUMB_TO_WHITESPACE(0) == ' ');
    assert(CRUMB_TO_WHITESPACE(1) == '\t');
    assert(CRUMB_TO_WHITESPACE(2) == '\n');
    assert(CRUMB_TO_WHITESPACE(3) == '\r');
    printf("test_crumb_to_whitespace passed\n");
}

void test_get_crumb() {
    assert(GET_CRUMB(0b11000000, 0) == 3);
    assert(GET_CRUMB(0b00110000, 1) == 3);
    assert(GET_CRUMB(0b00001100, 2) == 3);
    assert(GET_CRUMB(0b00000011, 3) == 3);
    printf("test_get_crumb passed\n");
}

void test_set_crumb() {
    assert(SET_CRUMB(3, 0) == 0b11000000);
    assert(SET_CRUMB(3, 1) == 0b00110000);
    assert(SET_CRUMB(3, 2) == 0b00001100);
    assert(SET_CRUMB(3, 3) == 0b00000011);
    printf("test_set_crumb passed\n");
}

void test_get_byte() {
    unsigned int val = 0x12345678;
    assert(GET_BYTE(val, 0) == 0x12);
    assert(GET_BYTE(val, 1) == 0x34);
    assert(GET_BYTE(val, 2) == 0x56);
    assert(GET_BYTE(val, 3) == 0x78);
    printf("test_get_byte passed\n");
}

void test_set_byte() {
    unsigned int val = 0x12;
    assert(SET_BYTE(val, 0) == 0x12000000);
    assert(SET_BYTE(val, 1) == 0x00120000);
    assert(SET_BYTE(val, 2) == 0x00001200);
    assert(SET_BYTE(val, 3) == 0x00000012);
    printf("test_set_byte passed\n");
}

void test_whitespace_to_byte() {
    int value = 0x20090a0d; // " \t\n\r"
    assert(WHITESPACE_TO_BYTE(value) == 0b00011011);
    printf("test_whitespace_to_byte passed\n");
}

void test_byte_to_whitespace() {
    int value = 0b00011011;
    assert(BYTE_TO_WHITESPACE(value) == 0x20090a0d); // " \t\n\r"
    printf("test_byte_to_whitespace passed\n");
}

int main() {
    test_whitespace_to_crumb();
    test_crumb_to_whitespace();
    test_get_crumb();
    test_set_crumb();
    test_get_byte();
    test_set_byte();
    test_whitespace_to_byte();
    test_byte_to_whitespace();

    return 0;
}
