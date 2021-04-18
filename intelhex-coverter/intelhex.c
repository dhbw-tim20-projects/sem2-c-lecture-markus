#include "intelhex.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char charToHexDigit(char c) { return c >= 'A' ? c - 'A' + 10 : c - '0'; }
unsigned char stringToByte(char c[2]) { return charToHexDigit(c[0]) * 16 + charToHexDigit(c[1]); }

int readByteCount(char *line) {
  char byteCountHex[3] = {line[1], line[2], '\0'};
  return strtol(byteCountHex, NULL, 16);
}

int readAddress(char *line) {
  char hexAddress[5] = {line[3], line[4], line[5], line[6], '\0'};
  return strtol(hexAddress, NULL, 16);
}

char *readRecordType(char *line) {
  char recordType[3] = {line[7], line[8], '\0'};
  char *returnValue = malloc(sizeof(recordType));
  strncpy(returnValue, recordType, sizeof(recordType));
  return returnValue;
}

uint8_t *readData(char *line, int byteCount) {
  uint8_t *result = malloc(byteCount);
  int count = 0;
  for (int i = 9; i < (byteCount * 2) + 9; i += 2) {
    char hex[2] = {line[i], line[i + 1]};
    result[count] = stringToByte(hex);
    count++;
  }
  return result;
}

uint8_t readChecksum(char *line, int byteCount) {
  char checksum[3] = {line[(byteCount * 2) + 9], line[(byteCount * 2) + 10]};
  return stringToByte(checksum);
}

uint8_t calculateCheckSum(char *line, int byteCount) {
  int sum = 0;
  for (int i = 1; i < (byteCount * 2) + 8; i += 2) {
    char hex[2] = {line[i], line[i + 1]};
    sum += stringToByte(hex);
  }
  return -(unsigned int)(0x00FF & sum);
}

int readHexFile(const char *path, uint8_t *destination, int max_length) {
  FILE *inputFile = fopen(path, "r");
  char *buffer = malloc(16);
  int totalBytes = 0;

  while (!feof(inputFile)) {
    if (fgets(buffer, max_length, inputFile) != NULL) {

      if (buffer[0] != ':') {
        return -1;
      }

      int byteCount = readByteCount(buffer);
      int address = readAddress(buffer);
      uint8_t *data = readData(buffer, byteCount);

      if (readChecksum(buffer, byteCount) != calculateCheckSum(buffer, byteCount)) {
        return -1;
      }

      for (int i = 0; i < byteCount; i++) {
        destination[address + i] = data[i];
      }

      totalBytes += byteCount;
    }
  }

  return totalBytes;
}

int writeHexFile(const char *path, uint8_t *source, int startaddress, int length) {
  FILE *hex_file = fopen(path, "wb");
  int length_counter = 0;
  int line_address = startaddress;
  int written_bytes = 0;

  for (int i = 0; length_counter < length; i++) {
    int remaining = length - length_counter;
    int line_length = (remaining < 16) ? remaining : 16;
    int hex_line_length = line_length + 5;
    int line_sum = 0;
    uint8_t *buf = malloc(hex_line_length * sizeof(uint8_t));

    *(buf) = line_length;
    *(buf + 1) = line_address >> 8;
    *(buf + 2) = line_address & 0xFF;
    *(buf + 3) = 0x00;

    for (int j = 0; j < 4; j++)
      line_sum += *(buf + j);

    for (int k = 0; k < line_length; k++) {
      *(buf + (4 + k)) = *(source + (i * 16 + k));
      line_sum += *(buf + (4 + k));
      length_counter++;
    }

    *(buf + hex_line_length - 1) = 0xFF & ((line_sum ^ 0xFF) + 1);

    int written_line_bytes = 0;
    written_line_bytes = fprintf(hex_file, ":");
    if (written_line_bytes < 0)
      return -1;
    written_bytes += written_line_bytes;

    for (int j = 0; j < hex_line_length; j++) {
      written_line_bytes = fprintf(hex_file, "%.2X", *(buf + j));
      if (written_line_bytes < 0)
        return -1;
      written_bytes += written_line_bytes;
    }

    written_line_bytes = fprintf(hex_file, "\n");
    if (written_line_bytes < 0)
      return -1;
    written_bytes += written_line_bytes;

    line_address += line_length;
    free(buf);
  }

  int written_line_bytes = 0;
  written_line_bytes = fprintf(hex_file, ":00000001FF");
  if (written_line_bytes < 0)
    return -1;
  written_bytes += written_line_bytes;

  fseek(hex_file, 0L, SEEK_END);
  long int size = ftell(hex_file);
  if (written_bytes != size)
    return -1;

  fclose(hex_file);
  return written_bytes;
}