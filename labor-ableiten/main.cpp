#include <iostream>
using namespace std;

class A {
public:
  A(int count) : count(count) {}
  A() : count(0) {}

protected:
  int count;
};

class B : public A {
public:
  B() : A() {}
  void setCount(int count) { this->count = count; }
  int getCount() { return count; }
};

class C {};

class D {
public:
  int firstNumber;
  int secondNumber;
  int thirdNumber;
  int fourthNumber;

  int getFirstNumber() { return firstNumber; }
  int getSecondNumber() { return secondNumber; }
  int getThirdNumber() { return thirdNumber; }
  int getForuthNumber() { return fourthNumber; }
};

int main() {
  A a;
  B b;
  C c;
  D d;

  b.setCount(100);

  cout << "Count is: " << b.getCount() << endl;
  cout << "Size of A is: " << sizeof(a) << endl;
  cout << "Size of C is: " << sizeof(c) << endl;
  cout << "Size of B is: " << sizeof(b) << endl;
  cout << "Size of D is: " << sizeof(d) << endl;

  return 1;
}