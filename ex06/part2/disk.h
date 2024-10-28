#ifndef DISK_H
#define DISK_H

#include "shape.h"
#include "point.h"  // Include the Point structure
#include <cmath>  // For M_PI
#include <string>

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

    // Getter for center
    Point get_center() const { return center; }

    // Destructor
    ~Disk() override {}
};

#endif // DISK_H
