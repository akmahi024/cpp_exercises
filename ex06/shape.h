#ifndef SHAPE_H
#define SHAPE_H

#include <string>

// Interface definition for Shape
class Shape {
public:
    // Pure virtual function to get the name of the shape
    virtual std::string get_name() const = 0;

    // Pure virtual function to compute the area of the shape
    virtual float compute_area() const = 0;

    // Pure virtual function to create a new object using the default constructor
    virtual Shape* create() const = 0;

    // Pure virtual function to clone the object using the copy constructor
    virtual Shape* clone() const = 0;

    // Virtual destructor to allow proper cleanup for derived classes
    virtual ~Shape() {}
};

#endif // SHAPE_H
