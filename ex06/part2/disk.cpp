#include "disk.h"

// Constructor to initialize the disk with center and radius
Disk::Disk(Point center, float radius) : center(center), radius(radius) {}

// Copy constructor
Disk::Disk(const Disk& other) : center(other.center), radius(other.radius) {}

// Return the name of the shape
std::string Disk::get_name() const {
    return "Disk";
}

// Compute the area of the disk (π * r²)
float Disk::compute_area() const {
    return M_PI * radius * radius;
}

// Create a new Disk object (default center at origin with radius 1.0)
Disk* Disk::create() const {
    return new Disk(Point(0.0f, 0.0f), 1.0f);
}

// Clone the current Disk object using the copy constructor
Disk* Disk::clone() const {
    return new Disk(*this);
}
