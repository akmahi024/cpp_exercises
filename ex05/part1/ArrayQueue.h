#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

#include <string>
#include <iostream>

class ArrayQueue {
private:
    int _num_items; // Number of items in the queue
    int _allocated_size; // Size of memory allocated
    int _first; // Index of the first element of the queue 
    int _last; // Index of the next available slot 
    std::string* _items; // Container for queue elements

    // Resize the array to the specified max size
    void resize(int max_size) {
        if (max_size == 0) max_size = 1;  // Ensure non-zero capacity

        // Create a new array with the new size
        std::string* temp = new std::string[max_size];

        // Copy elements from the old array to the new one
        for (int i = 0; i < _num_items; ++i) {
            temp[i] = _items[(i + _first) % _allocated_size];
        }

        // Clean up the old array and update pointers
        delete[] _items;
        _items = temp;

        _first = 0;
        _last = _num_items;
        _allocated_size = max_size;
    }

public:
    // Default constructor: Create an empty queue with initial size 10
    ArrayQueue() 
        : _num_items(0), _allocated_size(10), _first(0), _last(0) {
        _items = new std::string[_allocated_size];
    }

    // Constructor with a specified initial capacity
    explicit ArrayQueue(int allocated_size) 
        : _num_items(0), _allocated_size(allocated_size), _first(0), _last(0) {
        _items = new std::string[_allocated_size];
    }

    // Destructor: Release the dynamically allocated memory
    ~ArrayQueue() {
        delete[] _items;
    }

    // Add an item to the queue
    void enqueue(const std::string& item) {
        if (_num_items == _allocated_size) {
            resize(2 * _allocated_size);  // Double the size if full
        }
        _items[_last++] = item; 
        if (_last == _allocated_size) _last = 0;  // Wrap around if needed
        _num_items++;
    }

    // Remove the item that was least recently added
    void dequeue() {
        if (empty()) {
            throw std::runtime_error("Queue underflow: Cannot dequeue from an empty queue.");
        }
        _first++;
        if (_first == _allocated_size) _first = 0;  // Wrap around if needed
        _num_items--;
        if (_num_items > 0 && _num_items == _allocated_size / 4) {
            resize(_allocated_size / 2);  // Shrink if needed
        }
    }

    // Access the front item without removing it
    std::string peek() {
        if (empty()) {
            throw std::runtime_error("Queue underflow: Cannot peek from an empty queue.");
        }
        return _items[_first];
    }

    // Check if the queue is empty
    bool empty() const {
        return _num_items == 0;
    }

    // Return the number of elements in the queue
    int size() const {
        return _num_items;
    }
};

#endif // ARRAY_QUEUE_H
