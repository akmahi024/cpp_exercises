// ArrayQueue.h

#include <string>
#include <iostream>
#include <utility> // For std::swap

#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

class ArrayQueue {
private:
    int _num_items;       // Number of items in the queue
    int _allocated_size;  // Size of memory allocated
    int _first;           // Index to the first element of the queue
    int _last;            // Index of the next available slot
    std::string* _items;  // Container for queue elements

    // Resize the internal array to the specified size
    void resize(int max_size) {
        if (max_size == 0) max_size = 1;

        std::string* temp = new std::string[max_size];
        for (int i = 0; i < _num_items; ++i) {
            temp[i] = _items[(i + _first) % _allocated_size];
        }
        delete[] _items;
        _items = temp;

        _first = 0;
        _last = _num_items;
        _allocated_size = max_size;
    }

public:
    // Default constructor
    ArrayQueue() 
        : _num_items(0), _allocated_size(1), _first(0), _last(0) {
        _items = new std::string[_allocated_size];
    }

    // Parameterized constructor
    explicit ArrayQueue(int allocated_size) 
        : _num_items(0), _allocated_size(allocated_size), _first(0), _last(0) {
        _items = new std::string[_allocated_size];
    }

    // Copy constructor
    ArrayQueue(const ArrayQueue& other) 
        : _num_items(other._num_items), 
          _allocated_size(other._allocated_size), 
          _first(0), _last(other._num_items) {
        _items = new std::string[_allocated_size];
        for (int i = 0; i < _num_items; ++i) {
            _items[i] = other._items[(other._first + i) % other._allocated_size];
        }
    }

    // Assignment operator
    ArrayQueue& operator=(const ArrayQueue& other) {
        if (this != &other) {  // Check for self-assignment
            std::string* new_items = new std::string[other._allocated_size];
            for (int i = 0; i < other._num_items; ++i) {
                new_items[i] = other._items[(other._first + i) % other._allocated_size];
            }

            delete[] _items;  // Free existing resources

            _items = new_items;
            _num_items = other._num_items;
            _allocated_size = other._allocated_size;
            _first = 0;
            _last = _num_items;
        }
        return *this;
    }

    // Destructor
    ~ArrayQueue() {
        delete[] _items;
    }

    // Enqueue an item
    void enqueue(const std::string& item) {
        if (_num_items == _allocated_size) resize(2 * _allocated_size);
        _items[_last++] = item;
        if (_last == _allocated_size) _last = 0;  // Wrap around
        _num_items++;
    }

    // Dequeue an item
    void dequeue() {
        if (empty()) {
            std::cerr << "Queue underflow: Cannot dequeue from an empty queue.\n";
            return;
        }
        _num_items--;
        _first++;
        if (_first == _allocated_size) _first = 0;  // Wrap around
        if (_num_items > 0 && _num_items == _allocated_size / 4) resize(_allocated_size / 2);
    }

    // Peek at the front item
    std::string peek() {
        if (empty()) {
            std::cerr << "Queue is empty: No element to peek.\n";
            return "";
        }
        return _items[_first];
    }

    // Check if the queue is empty
    bool empty() const {
        return _num_items == 0;
    }

    // Get the size of the queue
    int size() const {
        return _num_items;
    }
};

#endif // ARRAY_QUEUE_H
