#ifndef COMPUTERGRAPHICSPRACTICE_CONVEX_H
#define COMPUTERGRAPHICSPRACTICE_CONVEX_H

#include <vector>

namespace Convex {
    struct Point {
        int x, y;

        Point(int x, int y) : x(x), y(y) {
        }
    };

    std::vector<std::vector<Point>> vectorMethod(std::vector<Point> points);

    bool checkIntersection(Point p1, Point p2, Point p3, Point p4);

    Point findIntersection(Point p1, Point p2, Point p3, Point p4);

    void main(int argc, char **argv);
}

#endif //COMPUTERGRAPHICSPRACTICE_CONVEX_H
