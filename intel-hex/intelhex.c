#include "intelhex.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char charToHexDigit(char c) { return c >= 'A' ? c - 'A' + 10 : c - '0'; }
unsigned char stringToByte(char c[2]) { return charToHexDigit(c[0]) * 16 + charToHexDigit(c[1]); }

int readByteCount(char *line) {
  char byteCountHex[3];
  byteCountHex[0] = line[1];
  byteCountHex[1] = line[2];
  byteCountHex[2] = '\0';
  return strtol(byteCountHex, NULL, 16);
}

int readAddress(char *line) {
  char hexAddress[5];
  hexAddress[0] = line[3];
  hexAddress[1] = line[4];
  hexAddress[2] = line[5];
  hexAddress[3] = line[6];
  hexAddress[4] = '\0';
  return strtol(hexAddress, NULL, 16);
}

char *readRecordType(char *line) {
  char recordType[3];
  recordType[0] = line[7];
  recordType[1] = line[8];
  recordType[2] = '\0';
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
  char checksum[3];
  checksum[0] = line[(byteCount * 2) + 9];
  checksum[1] = line[(byteCount * 2) + 10];
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
  destination = malloc(max_length);

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