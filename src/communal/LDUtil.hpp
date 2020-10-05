#ifndef LDUTIL_HPP
#define LDUTIL_HPP

#include "../entity/Point.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif //M_PI

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

struct World_Data {
    Point top_left;
    float width;
    float height;
    float top;
    float bottom;
    float left;
    float right;

    Point active_top_left;
    float active_width;
    float active_height;
    float active_top;
    float active_bottom;
    float active_left;
    float active_right;

    void init(Point _top_left, Point _dim)
    {
        top_left = _top_left;
        width = _dim.get_x();
        height = _dim.get_y();
        top = 0;
        bottom = height;
        left = 0;
        right = width;

        active_top_left = Point(width * 0.25f, 5.f);
        active_width = width * 0.5f;
        active_height = height - 5.f;
        active_top = 5.f;
        active_bottom = active_height;
        active_left = active_top_left.get_x();;
        active_right = active_left + active_width;
    }
};

// Returns 1 if the lines intersect, otherwise 0. In addition, if the lines 
// intersect the intersection point may be stored in the floats i_x and i_y.
char get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y,
    float p2_x, float p2_y, float p3_x, float p3_y, float *i_x, float *i_y);



#endif // !LDUTIL_HPP
