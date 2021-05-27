#ifndef _QUEUE_H_
#define _QUEUE_H_
#include "stack.h"

template <typename T>
class CQueue {
public:
    CQueue(const int maxsize);
    ~CQueue();
    int getCount() const;
    bool isEmpty() const;
    //False falls keine Stackelemente zur Verfuegung stehen
    bool enqueue(const T& value);
    //<0 falls kein Wert in der Queue eingespeichert ist
    T dequeue();
private:
    int count;
    CStack<T> *stack;
    Element<T> *front;
    Element<T> *back;
};


template <typename T>
CQueue<T>::CQueue(const int maxsize) : count(0), stack(nullptr), front(nullptr), back(nullptr) {
    stack = new CStack<T>(maxsize);
}

template <typename T>
CQueue<T>::~CQueue() {
    delete stack;
}

template <typename T>
bool CQueue<T>::enqueue(const T& value) {
    if(stack->isEmpty()) return false;
    else
    {
        Element<T> *newelement = {stack->pop()};

        //Element befuellen
        newelement->value = value;

        //Einbauen
        if(count == 0)
        {
            newelement->next = nullptr;
            back = front = newelement;
        }
        else if(count == 1)
        {
            back = newelement;
            back->next = nullptr;
            front->next = back;
        }
        else
        {
            back->next = newelement;
            back = newelement;
            back->next = nullptr;
        }

        ++count;

        return true;
    }
}

template <typename T>
T CQueue<T>::dequeue() {
    if(count > 1)
    {
        T ret = {front->value};
        Element<T> *giveback = {front};
        front = front->next;
        stack->push(giveback);
        --count;

        return ret;
    }
    else if(count == 1)
    {
        //Ausbau komplett
        T ret = {front->value};
        stack->push(back);
        front = back = nullptr;
        count = 0;

        return ret;
    }
    else
        return T();
}

template <typename T>
bool CQueue<T>::isEmpty() const {
    return !count;
}

template <typename T>
int CQueue<T>::getCount() const {
    return count;
}

#endif



