#include "intelhex.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  if (argc != 2) {
    fprintf(stderr, "Wrong number of parameters! (%d) \n", argc - 1);
    return EXIT_FAILURE;
  }

  uint8_t *destination = {NULL};

  readHexFile(argv[1], destination, 586);

  return EXIT_SUCCESS;
}