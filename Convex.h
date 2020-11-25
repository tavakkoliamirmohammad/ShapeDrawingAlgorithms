#ifndef COMPUTERGRAPHICSPRACTICE_CONVEX_H
#define COMPUTERGRAPHICSPRACTICE_CONVEX_H

#include <vector>

namespace Convex {
    struct Point {
        int x, y;

        Point(int x, int y) : x(x), y(y) {
        }
    };

    void render();

    void reshape(int width, int height);

    std::vector<std::vector<Point>> vectorMethod(std::vector<Point> points);

    bool checkIntersection(Point p1, Point p2, Point p3, Point p4);

    Point findIntersection(Point p1, Point p2, Point p3, Point p4);

    void showSinglePolygon(std::vector<Point> points);

    void showVectorPolygon(std::vector<std::vector<Point>> vPoints);

    void main(int argc, char **argv);
}

#endif //COMPUTERGRAPHICSPRACTICE_CONVEX_H
