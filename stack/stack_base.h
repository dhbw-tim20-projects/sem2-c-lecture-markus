#ifndef _STACK_BASE_H_
#define _STACK_BASE_H_

#include <cstdint>
using namespace std;

typedef uint8_t uint4_t;
typedef uint16_t uint12_t;

/**
 * Adressangabe
 */
union UBankedAddress {
  /**
   * Initalisierungs-Konstruktor
   * @param value Linearer Speicherwert ohne Bankangabe
   */
  UBankedAddress(const uint12_t value = 0) : raw{value} {}

  /**
   * Initalisierungs-Konstruktor
   * @param bank Bankangabe
   * @param address Address segmentiert
   */
  UBankedAddress(const uint4_t bank, const uint8_t address)
      : banked{.address = address, .bank = bank} {}

  uint12_t raw; //!< Rohwert

  struct {
    uint8_t address;  //!< Adresse im Segment
    uint8_t bank : 4; //!< Bankangabe
    uint8_t : 4;
  } banked; //!< Segmente in Bank und Segmentadresse

  /**
   * Erhöht die Adresse (Wert) um 1
   * @return Adresse (Wert) um 1 erhöht
   */
  uint12_t inc() { return raw = 0x0FFF & (raw + 1); }
};

/**
 * Stackverwaltung für den Intel4004 Prozessor.
 * Angelegt als Zirkularspeicher (d.h. es wird überschrieben)
 * wenn mehr wie drei Werte eingeschrieben worden sind und nicht
 * wieder ausgelesen.
 */
class Intel4004StackBase {
public:
  enum {
    STACKSIZE = 3 //!< Maximale Größe des Intel 4004 Stacks
  };

  /**
   * Wirkrichtung
   */
  typedef enum {
    PUSH, //!< Hineinspeichern
    POP   //!< Herausholen
  } EDirection;

  /**
   * Schreibt eine Adresse (Wert) in den Stack ein
   * @param address Adresse
   */
  virtual void push(const UBankedAddress address) = 0;

  /**
   * Liest eine Adresse (Wert) aus dem Stack aus
   * @return Adresse
   */
  virtual UBankedAddress pop() = 0;

  /** Setzt den Stack zurück */
  virtual void reset() = 0;

  /**
   * Gibt die Aktulle Position im Stack aus
   * @return Position
   */
  virtual int getCurrentStackPosition() const = 0;

  /**
   * Zahlt die Anzahl der eingeschriebenen Adressen (Werte)
   * @return Anzahl
   */
  virtual int getCount() const = 0;

  /**
   * Gibt zurück ob der Stack übergelaufen ist (mehr Werte reingeschrieben wie reinpassen)
   * @return <c>true</c> wenn Überlauf, sonst <c>false</c>
   */
  virtual bool isOverflow() const = 0;

  /**
   * Gibt zurück ob der Stack unterlauf ist (mehr Werte ausgelsen wie reingeschrieben)
   * @return <c>true</c> wenn Unterlauf, sonst <c>false</c>
   */
  virtual bool isUnderflow() const = 0;

  /**
   * Kopie der Stackinhalte
   * @param ptr Zeiger auf Kopie (Array der Größe STACKSIZE)
   * @return Pointer auf Kopie
   */
  virtual UBankedAddress *getCopyOfStack(UBankedAddress *const ptr) const = 0;

protected:
  /** Wird aufgerufen wenn ein Fehler passiert */
  virtual void WarningCondition(const EDirection direction) = 0;
};
#endif
