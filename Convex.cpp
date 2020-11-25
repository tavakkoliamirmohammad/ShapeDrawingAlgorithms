#include "Convex.h"
#include <GL/glut.h>

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
        Point p3 = p2;
        Point p4 = points[(i + 2) % points.size()];
        if ((p2.x - p1.x) * (p4.y - p3.y) < (p2.y - p1.y) * (p4.x - p3.x)) {
            for (int j = i + 2; j % points.size() != i; ++j) {
                if (checkIntersection(p1, p2, points[j % points.size()], points[(j + 1) % points.size()])) {
                    Point intersection = findIntersection(p1, p2, points[j % points.size()],
                                                          points[(j + 1) % points.size()]);
                    vector<Point> convex_poly1, convex_poly2;
                    convex_poly1.push_back(p1);
                    convex_poly1.push_back(p2);
                    convex_poly1.push_back(intersection);
                    for (int k = j + 1; k % points.size() != i; ++k) {
                        convex_poly1.push_back(points[k % points.size()]);
                    }
                    for (int k = i + 1; k % points.size() != (j + 1) % points.size(); k += 1) {
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
    if (denom == 0)
        return false;
    float u = -((p1.x - p2.x) * (p1.y - p3.y) - (p1.y - p2.y) * (p1.x - p3.x)) / denom;
    return (u > 0 && u <= 1);
}

Convex::Point Convex::findIntersection(Point p1, Point p2, Point p3, Point p4) {
    float denom = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);
    float u = -((p1.x - p2.x) * (p1.y - p3.y) - (p1.y - p2.y) * (p1.x - p3.x)) / denom;
    return Point(p3.x + (p4.x - p3.x) * u, p3.y + (p4.y - p3.y) * u);
}

void Convex::showSinglePolygon(vector<Point> points) {
    glColor3f(0, 0, 1);
    glBegin(GL_LINE_LOOP);
    for (Point p : points)
        glVertex2i(p.x, p.y);
    glEnd();
}

void Convex::showVectorPolygon(vector<std::vector<Point>> vPoints) {
    for (auto &vPoint : vPoints) {
        showSinglePolygon(vPoint);
    }
}

void Convex::render() {
    glClear(GL_COLOR_BUFFER_BIT);
//    vector<Point> p = {Point(100, 100), Point(200, 100), Point(200, 200), Point(100, 200)};
//    vector<Point> p = {Point(100, 100), Point(200, 100), Point(150, 150), Point(200, 200), Point(100, 200)};
//    vector<Point> p = { Point(100, 100), Point(200, 100), Point(250, 150), Point(300, 100), Point(300, 400), Point(100, 400)};
//    vector<Point> p = { Point(500, 500), Point(550, 550), Point(700, 600), Point(550, 650), Point(500, 700), Point(450, 650), Point(300, 600), Point(450, 550)};
    vector<Point> p = { Point(400, 400) ,Point{10, 400} ,Point{200, 300}, Point{10, 210}, Point{400, 210}, Point{10, 100}, Point{600, 110} , Point{400, 300} };
//    showSinglePolygon(p);

    vector<vector<Point>> res = vectorMethod(p);
    showVectorPolygon(res);

    glFlush();
}

void Convex::reshape(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspectRatio = (float) width / height;
    if (width > height)
        gluOrtho2D(0, 1000.0 * aspectRatio, 0, 1000);
    else
        gluOrtho2D(0, 1000.0, 0, 1000.0 / aspectRatio);
    glViewport(0, 0, width, height);
}

void Convex::main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Convex Finder");

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 1000.0, 0, 1000);

    glutDisplayFunc(Convex::render);
    glutReshapeFunc(Convex::reshape);
    glutMainLoop();
}