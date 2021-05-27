#include "stack.h"
#include "queue.h"
#include <iostream>

using namespace std;

int main() {
    {
        CStack<string> source(20), dest(0);

        cout << "Count Source " << source.getCount() << endl;
        cout << "Count Destination " << dest.getCount() << endl;

        while(source.getCount())
            dest.push(source.pop());

        cout << "Count Source " << source.getCount() << endl;
        cout << "Count Destination " << dest.getCount() << endl;
    }

    {
        CQueue<string> queue(20);

        queue.enqueue("asd");
        queue.enqueue("vbn");
        queue.enqueue("5tew");

        cout << queue.dequeue() << endl;

        queue.enqueue("rdfg");
        queue.enqueue("sdgerg");

        cout << queue.dequeue() << endl;
        cout << queue.dequeue() << endl;
        cout << queue.dequeue() << endl;

        // queue.enqueue(18);
        // queue.enqueue(21);
        // queue.enqueue(23);
        // queue.enqueue(28);
        // queue.enqueue(35);

        // while(!queue.isEmpty())
        //     cout << queue.dequeue() << endl;

        // cout << queue.dequeue() << endl;
    }

    return 0;
}
