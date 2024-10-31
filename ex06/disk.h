// disk.h

#ifndef DISK_H
#define DISK_H

#include "shape.h"
#include "point.h"
#include <string>

class Disk : public Shape {
public:
    Disk(Point center, float radius);

    std::string get_name() const override;
    float compute_area() const override;
    Disk* create() const override;
    Disk* clone() const override;

    ~Disk() override = default;

private:
    Point center_;
    float radius_;
};

#endif // DISK_H
