#ifndef _STACK_H_
#define _STACK_H_

#include "stack_base.h"

class Intel4004Stack : public Intel4004StackBase {
public:
  Intel4004Stack() : pushCount{0}, popCount(0) {}

  virtual void push(const UBankedAddress address);
  virtual UBankedAddress pop();
  virtual void reset();
  virtual int getCurrentStackPosition() const;
  virtual int getCount() const;
  virtual bool isOverflow() const;
  virtual bool isUnderflow() const;
  virtual UBankedAddress *getCopyOfStack(UBankedAddress *const ptr) const;

protected:
  virtual void WarningCondition(const EDirection direction);

private:
  UBankedAddress stack[STACKSIZE];
  int pushCount, popCount;
};

#endif