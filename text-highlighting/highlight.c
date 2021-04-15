#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *fp = {NULL};
    char *buffer = {NULL};
    const size_t BUFFER_SIZE = {1024};

    if (argc != 2) {
        fprintf(stderr, "Anzahl der Parameter falsch (%d)\n", argc - 1);
        return EXIT_FAILURE;
    }

    if ((fp = fopen(argv[1], "r"))) {
        if ((buffer = malloc(BUFFER_SIZE))) {
            *buffer = '\0';
        } else {
            fputs("Out of Memory\n", stderr);
            fclose(fp);
            return EXIT_FAILURE;
        }

        while (!feof(fp)) {
            if (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
                char *ptr = strtok(buffer, " ");
                while (ptr != NULL) {
                    if (strcmp(ptr, "Canusa") == 0) {
                        printf("\x1b[32m%s \x1b[0m", ptr);
                    } else if (strcmp(ptr, "Canada") == 0) {
                        printf("\x1b[31m%s \x1b[0m", ptr);
                    } else if (strcmp(ptr, "US") == 0) {
                        printf("\x1b[34m%s \x1b[0m", ptr);
                    } else {
                        printf("%s ", ptr);
                    }
                    ptr = strtok(NULL, " ");
                }
            }
        }

        fclose(fp);
        free(buffer);
    } else {
        perror(argv[1]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}