#ifndef DISK_H
#define DISK_H

#include "shape.h"
#include <cmath>  // For M_PI
#include <string>

// Point structure representing a point in 2D space
struct Point {
    float x, y;
    Point(float x_val = 0.0f, float y_val = 0.0f) : x(x_val), y(y_val) {}
};

// Disk class implementing the Shape interface
class Disk : public Shape {
private:
    Point center;
    float radius;

public:
    // Constructor
    Disk(Point center, float radius);

    // Copy constructor (for clone method)
    Disk(const Disk& other);

    // Overriding Shape interface methods
    std::string get_name() const override;
    float compute_area() const override;
    Disk* create() const override;
    Disk* clone() const override;

    // Destructor
    ~Disk() override {}
};

#endif // DISK_H
