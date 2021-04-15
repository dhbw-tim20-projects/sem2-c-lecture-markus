#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *file = {NULL};
    char buffer;
    int count = 0;
    char *charBuffer = malloc(42);

    if (argc != 2) {
        fprintf(stderr, "Wrong number of parameters! (%d) \n", argc - 1);
        exit(EXIT_FAILURE);
    }

    file = fopen(argv[1], "rb");

    if (!file) {
        fprintf(stderr, "Cannot open file \n");
        exit(EXIT_FAILURE);
    }

    while (!feof(file)) {
        buffer = fgetc(file);

        if (count % 16 == 0) {
            printf("\t %s", charBuffer);
            printf("\n %08X: ", (int)ftell(file) - 1);
            memset(charBuffer, 0, 42 * sizeof charBuffer);
        }

        if (buffer != '\n') {
            strncat(charBuffer, &buffer, 1);
        }

        printf("%02X ", buffer);
        count++;
    }

    fclose(file);
}