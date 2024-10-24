#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <cstdlib> // for exit()

// Define a struct for representing three-dimensional points with integral coordinates 
struct Point {
    int x, y, z;

    Point(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}
};

// Class for representing a queue 
class Queue {
public:
    Queue(int max_size=100) : _num_items(0), _max_size(max_size), 
        _first(0), _last(0), _items(new Point[max_size]) {}

    ~Queue() { delete[] _items; }

    // Check whether the queue is empty 
    bool empty() const;

    // Check whether the queue is full
    bool full() const;

    // Return the number of elements in the queue 
    int size() const;

    // Insert an element in the queue 
    void enqueue(const Point);

    // Remove an element from the queue 
    void dequeue();

    // Access the least recently added element
    Point peek() const;

private:
    int _num_items; // number of elements in the queue
    const int _max_size; // capacity of the fixed-size queue
    int _first; // index to the first element of the queue
    int _last; // index of the next available slot 
    Point* _items; // data container 
};

#endif 
