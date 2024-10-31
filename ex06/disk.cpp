// disk.cpp

#include "disk.h"
#include <cmath>

Disk::Disk(Point center, float radius) : center_(center), radius_(radius) {}

std::string Disk::get_name() const {
    return "Disk";
}

float Disk::compute_area() const {
    return M_PI * radius_ * radius_; // Area = π * r²
}

Disk* Disk::create() const {
    float radius = std::sqrt(1 / M_PI); // Radius calculated to give area of 1
    return new Disk(Point(0, 0), radius); // Creates a new Disk with calculated radius
}

Disk* Disk::clone() const {
    return new Disk(*this); // Uses the copy constructor to create a new Disk
}
