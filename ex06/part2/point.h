#ifndef POINT_H
#define POINT_H

struct Point {
    float x, y;
    Point(float x_val = 0.0f, float y_val = 0.0f) : x(x_val), y(y_val) {}
};

#endif // POINT_H
