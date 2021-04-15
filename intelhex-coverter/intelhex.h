#ifndef _INTELHEX_H_
#define _INTELHEX_H_
#include <stdint.h>

/**
 * Dient zum lesen einer Intel HEX Datei
 * @param path Pfadangabe Hex-Datei
 * @param destination Array von Binärdaten
 * @param max_length Größe des Array von Binärdaten
 * @return Anzahl der gelesenen Binär Bytes (im Fehlerfall -1)
 */
extern int readHexFile(const char *path, uint8_t *destination, int max_length);

/**
 * Dient zum schreiben einer Intel HEX Datei
 * @param path Pfadangabe Hex-Datei
 * @param source Array von Binärdaten
 * @param startaddress Startadresse IN der Hex-Datei
 * @param length Anzahl der zu lesenden Werte
 * @return Anzahl der geschriebenen Binär Bytes (im Fehlerfall -1)
 */
extern int writeHexFile(const char *path, uint8_t *source, int startaddress, int length);

#endif
