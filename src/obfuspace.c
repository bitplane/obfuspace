#include <stdio.h>
#include <stdint.h>
#include "obfuspace.h"

int main(int argc, char *argv[]) {

       int c;
       while ((c = getchar()) != EOF) {
              int32_t output = BYTE_TO_WHITESPACE(c);

              fwrite(&output, sizeof(int32_t), 1, stdout);
       }
       return 0;
}
