#include <iostream>
#include <string>
using namespace std;

class Animal {
public:
  string name;
  int weight, height;

  Animal(string name, int weight = 0, int height = 0)
      : name(name), weight(weight), height(height) {}

  void print() {
    cout << "Name: " << name << endl
         << "Weight: " << weight << endl
         << "Height: " << height << endl;
  }
};

class A {
public:
  // Konstruktor: Beim Initialisieren der Instanz aufgerufen
  A(int value = 0) : v(0) {
    cout << "Konstruktor aufgerufen" << endl;
    if (value < -10)
      v = -10;
    else if (value > 1000)
      v = 1000;
    else
      v = value;
    ++count_instances;
  }

  // Copy Konstruktor
  A(A &other) : v(other.v) {
    cout << "Copy-Konstruktor aufgerufen" << endl;
    ++count_instances;
  }

  // Destruktor: Beim aufloesen der Instanz aufgerufen
  ~A() {
    cout << "Destruktor aufgerufen" << endl;
    --count_instances;
  }

  int getValue() { return v; }

  static int getCountInstances() { return count_instances; }

protected:
private:
  int v;
  static int count_instances;
};

int A::count_instances = 0;

class CColor {
public:
  const static CColor BLACK;
  const static CColor RED;
  const static CColor GREEN;
  const static CColor BLUE;
  const static CColor WHITE;

  int getRed() const { return r; }
  int getGreen() const { return g; }
  int getBlue() const { return b; }

private:
  CColor(int red, int green, int blue) : r(red), g(green), b(blue) {}
  int r, g, b;
};

const CColor CColor::BLACK(0, 0, 0);
const CColor CColor::RED(255, 0, 0);
const CColor CColor::GREEN(0, 255, 0);
const CColor CColor::BLUE(0, 0, 255);
const CColor CColor::WHITE(255, 255, 255);

int main() {

  cout << "Programmstart" << endl;

  const char *test = "Affe";
  const short height = 123;

  Animal monkey(test, height, 456);

  monkey.print();

  A *copy = nullptr;

  {
    A a(12345678);
    copy = new A(a);
    cout << "Wert von Value = " << a.getValue() << endl;
    cout << "Instanzen die aktiv sind " << A::getCountInstances() << endl;
  }

  cout << "Wert von Value (copy) = " << copy->getValue() << endl;
  delete copy, copy = nullptr;
  cout << "Instanzen die aktiv sind " << A::getCountInstances() << endl;

  cout << "Rot hate einen Rotanteil von " << CColor::RED.getRed() << endl;

  cout << "Programmende" << endl;

  return 0;
}
