#include "convex.h"

using namespace std;

vector<vector<Convex::Point>> Convex::vectorMethod(vector<Point> points) {
    if (points.size() < 4) {
        vector<vector<Point>> ps;
        ps.push_back(points);
        return ps;
    }
    vector<vector<Point>> polygons;
    for (int i = 0; i < points.size() - 1; ++i) {
        Point p1 = points[(i) % points.size()];
        Point p2 = points[(i + 1) % points.size()];
        Point p3 = points[(i + 2) % points.size()];
        Point p4 = points[(i + 3) % points.size()];
        if ((p2.x - p1.x) * (p4.y - p3.y) < (p2.y - p1.y) * (p4.x - p3.x)) {
            for (int j = i + 4; j != i; j = (j + 1) % points.size()) {
                if (checkIntersection(p1, p2, points[j % points.size()], points[(j + 1) % points.size()])) {
                    Point intersection = findIntersection(p1, p2, points[j % points.size()],
                                                          points[(j + 1) % points.size()]);
                    vector<Point> convex_poly1, convex_poly2;
                    convex_poly1.push_back(p1);
                    convex_poly1.push_back(p2);
                    convex_poly1.push_back(intersection);
                    for (int k = j + 1; k != i; k = (k + 1) % points.size()) {
                        convex_poly1.push_back(points[k % points.size()]);
                    }
                    for (int k = i + 1; k != (j + 1); k = (k + 1) % points.size()) {
                        convex_poly2.push_back(points[k % points.size()]);
                    }
                    convex_poly2.push_back(intersection);
                    for (vector<Point> ps : vectorMethod(convex_poly1)) {
                        polygons.push_back(ps);
                    }
                    for (vector<Point> ps : vectorMethod(convex_poly2)) {
                        polygons.push_back(ps);
                    }
                    return polygons;
                }
            }
        }
    }
    polygons.push_back(points);
    return polygons;
}

bool Convex::checkIntersection(Point p1, Point p2, Point p3, Point p4) {
    float denom = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);
    float u = -((p1.x - p2.x) * (p1.y - p3.y) - (p1.y - p2.y) * (p1.x - p3.x)) / denom;
    return ((p1.x - p2.x) * (p3.y - p4.y) != (p1.y - p2.y) * (p3.x - p4.x)) && (u > 0 && u < 1);
}

Convex::Point Convex::findIntersection(Point p1, Point p2, Point p3, Point p4) {
    float denom = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);
    float u = -((p1.x - p2.x) * (p1.y - p3.y) - (p1.y - p2.y) * (p1.x - p3.x)) / denom;
    return Point(p3.x + (p4.x - p3.x) * u, p3.y + (p4.y - p3.x) * u);
}
