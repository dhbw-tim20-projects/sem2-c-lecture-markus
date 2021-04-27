#include "stack.h"
#include <iostream>

using namespace std;

/**
 * Example usage of the stack to see if everything works fine. Unit
 * tests would be better in this case.
 */
int main() {
  Intel4004Stack *stack = new Intel4004Stack();

  cout << "Expect: isUnderflow should return true because no value is present" << endl;
  cout << "Result: " << stack->isUnderflow() << endl << endl;

  cout << "Expect: isOverflow should return false because stack is not filled" << endl;
  cout << "Result: %d \n\n" << stack->isOverflow() << endl << endl;

  cout << "Pushing first entry to stack... " << endl << endl;
  stack->push(UBankedAddress(1000));

  cout << "Expect: getCount should return 1 because one operation was executed" << endl;
  cout << "Result: " << stack->getCount() << endl << endl;

  cout << "Expect: isUnderflow should return false because one value is present" << endl;
  cout << "Result: " << stack->isUnderflow() << endl << endl;

  cout << "Pushing two other entries to stack... " << endl << endl;
  stack->push(UBankedAddress(2000));
  stack->push(UBankedAddress(3000));

  cout << "Expect: getCount should return 3" << endl;
  cout << "Result: " << stack->getCount() << endl << endl;

  cout << "Expect: getCurrentStackPosition should return 2" << endl;
  cout << "Result: " << stack->getCurrentStackPosition() << endl << endl;

  cout << "Expect: isOverflow should return true because next entry will cause overflow" << endl;
  cout << "Result: " << stack->isOverflow() << endl << endl;

  cout << "Pop entry from stack..." << endl << endl;
  UBankedAddress entryFromStack = stack->pop();

  cout << "Expect: result should return last entry (value 3000)" << endl;
  cout << "Result: " << entryFromStack.raw << endl << endl;

  cout << "Expect: getCount should return 4" << endl;
  cout << "Result: " << stack->getCount() << endl << endl;

  cout << "Expect: stack position should equal 1" << endl;
  cout << "Result: " << stack->getCurrentStackPosition() << endl << endl;

  cout << "Reset stack..." << endl << endl;
  stack->reset();

  cout << "Expect: stack position should equal -1 because stack is empty" << endl;
  cout << "Result: " << stack->getCurrentStackPosition() << endl << endl;

  cout << "Expect: stack count should equal 0" << endl;
  cout << "Result: " << stack->getCount() << endl << endl;

  return 0;
}