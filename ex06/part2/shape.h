// shape.h

#ifndef SHAPE_H
#define SHAPE_H

#include <string>

class Shape {
public:
    // Returns the name of the shape
    virtual std::string get_name() const = 0;

    // Computes the area of the shape
    virtual float compute_area() const = 0;

    // Creates a new object using the default constructor
    virtual Shape* create() const = 0;

    // Clones the current object using the copy constructor
    virtual Shape* clone() const = 0;

    // Virtual destructor
    virtual ~Shape() = default;
};

#endif // SHAPE_H
