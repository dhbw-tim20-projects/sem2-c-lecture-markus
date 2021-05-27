#ifndef _STACK_H_
#define _STACK_H_

template <class T>
struct Element {
    Element() : next(nullptr) {}
    Element(const T v): next(nullptr), value(v) {}
    Element<T> *next;
    //Unbelegt ist -1
    T value {};
};

template <typename T>
class CStack {
public:
    CStack(int maxsize = 100) : size(maxsize), count(maxsize), elements(nullptr), top(nullptr) {
        top = elements = new Element<T>[size];

        for(int i = size - 1; i > 0; --i)
            elements[i - 1].next = &elements[i];
    }

    ~CStack() {
        delete [] elements;
    }

    bool push(Element<T> *element) {
        if(element) {
            element->next = top;
            top = element;
            ++count;
            return true;
        }
        else return false;
    }

    Element<T> *pop() {
        if(isEmpty()) return nullptr;
        else {
            Element<T> *ret = top;
            top = top->next;
            --count;
            return ret;
        }
    }
    bool isEmpty() const {
        return !count;
    }
    bool isFull() const {
        return count == size;
    }
    int getCount() const {
        return count;
    }
    int getSize() const {
        return size;
    }
private:
    int size, count;
    Element<T> *elements;
    Element<T> *top;
};
#endif
