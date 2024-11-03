// ArrayQueue.h

#include <string>
#include <iostream>
#include <utility> // For std::move and std::swap
#include <exception>
#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H
//negative size check for its size


//custom exception for underflow
class QueueUnderflowException : public std::exception {
    public :
    const char* what() const noexcept override{
        return "queue underflow cannot perform operation in an empty queue,because nothing is there,please add more items";
    }
};

class ArrayQueue {
private:
    int _num_items;       // Number of items in the queue
    int _allocated_size;  // Size of memory allocated
    int _first;           // Index to the first element of the queue
    int _last;            // Index of the next available slot
    std::string* _items;  // Container for queue elements

    void resize(int max_size) noexcept {
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
    ArrayQueue() noexcept
        : _num_items(0), _allocated_size(1), _first(0), _last(0) {
        _items = new std::string[_allocated_size];
    }

    // Parameterized constructor
    explicit ArrayQueue(int allocated_size) {
        if (allocated_size < 0) {
            throw std::invalid_argument("Error: allocated_size cannot be negative.");
        }
        _num_items = 0;
        _allocated_size = allocated_size;
        _first = 0;
        _last = 0;
        _items = new std::string[_allocated_size];
    }

    // Copy constructor
    ArrayQueue(const ArrayQueue& other) noexcept
        : _num_items(other._num_items), 
          _allocated_size(other._allocated_size), 
          _first(0), _last(other._num_items) {
        _items = new std::string[_allocated_size];
        for (int i = 0; i < _num_items; ++i) {
            _items[i] = other._items[(other._first + i) % other._allocated_size];
        }
    }

    // Move constructor
    ArrayQueue(ArrayQueue&& other) noexcept
        : _num_items(other._num_items),
          _allocated_size(other._allocated_size),
          _first(other._first),
          _last(other._last),
          _items(other._items) {
        other._items = nullptr;
        other._num_items = 0;
        other._allocated_size = 0;
        other._first = 0;
        other._last = 0;
    }

    // Assignment operator
    ArrayQueue& operator=(const ArrayQueue& other) noexcept {
        if (this != &other) {
            std::string* new_items = new std::string[other._allocated_size];
            for (int i = 0; i < other._num_items; ++i) {
                new_items[i] = other._items[(other._first + i) % other._allocated_size];
            }
            delete[] _items;
            _items = new_items;
            _num_items = other._num_items;
            _allocated_size = other._allocated_size;
            _first = 0;
            _last = _num_items;
        }
        return *this;
    }

    // Move assignment operator
    ArrayQueue& operator=(ArrayQueue&& other) noexcept {
        if (this != &other) {
            delete[] _items;  // Free existing resources

            _items = other._items;
            _num_items = other._num_items;
            _allocated_size = other._allocated_size;
            _first = other._first;
            _last = other._last;

            other._items = nullptr;
            other._num_items = 0;
            other._allocated_size = 0;
            other._first = 0;
            other._last = 0;
        }
        return *this;
    }

    // Destructor
    ~ArrayQueue() noexcept {
        delete[] _items;
    }

    void enqueue(const std::string& item) noexcept{
        if (_num_items == _allocated_size) resize(2 * _allocated_size);
        _items[_last++] = item;
        if (_last == _allocated_size) _last = 0;
        _num_items++;
    }

    void dequeue() {
        if (empty()) {
            throw QueueUnderflowException();
        }
        _num_items--;
        _first++;
        if (_first == _allocated_size) _first = 0;
        if (_num_items > 0 && _num_items == _allocated_size / 4) resize(_allocated_size / 2);
    }

    std::string peek() {
        if (empty()) {
            throw QueueUnderflowException();
            
        }
        return _items[_first];
    }

    bool empty() const noexcept{
        return _num_items == 0;
    }

    int size() const noexcept{
        return _num_items;
    }
};

#endif // ARRAY_QUEUE_H 
