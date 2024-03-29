#include "stack.h"
#include <iostream>

using namespace std;

void Intel4004Stack::push(const UBankedAddress address) {
  if (isOverflow()) {
    WarningCondition(PUSH);
    return;
  }
  if (getCurrentStackPosition() != -1) {
    stack[getCurrentStackPosition()] = stack[getCurrentStackPosition()].inc();
  }
  stack[getCurrentStackPosition() + 1] = address;
  pushCount++;
}

UBankedAddress Intel4004Stack::pop() {
  if (isUnderflow()) {
    WarningCondition(POP);
    return UBankedAddress(0);
  }
  UBankedAddress result = stack[getCurrentStackPosition()];
  stack[getCurrentStackPosition()] = UBankedAddress(0);
  popCount++;
  return result;
}

int Intel4004Stack::getCurrentStackPosition() const { return pushCount - popCount - 1; }

int Intel4004Stack::getCount() const { return pushCount + popCount; }

bool Intel4004Stack::isOverflow() const { return getCurrentStackPosition() >= STACKSIZE - 1; }

bool Intel4004Stack::isUnderflow() const { return getCurrentStackPosition() == -1; }

void Intel4004Stack::reset() {
  pushCount = 0;
  popCount = 0;
  for (int i = 0; i < STACKSIZE; i++)
    stack[i] = {};
}

UBankedAddress *Intel4004Stack::getCopyOfStack(UBankedAddress *const ptr) const {
  for (int i = 0; i < STACKSIZE; i++)
    ptr[i] = stack[i];
  return ptr;
}

void Intel4004Stack::WarningCondition(const EDirection direction) {
  // TODO: Implement useful error handling
  switch (direction) {
  case PUSH:
    cout << "Warning: Overflow detected!" << endl;
    break;
  case POP:
    cout << "Warning: Underflow detected!" << endl;
    break;
  default:
    cout << "Warning: Unkown error detected!" << endl;
  }
}
