#include "Circles.h"
#include <GL/glut.h>
#include <cmath>


void Circles::setPixel(int x, int y) {
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void Circles::DirectEquation(int cx, int cy, int r) {
    double step;
    for (int x = cx - r; x <= cx + r; ++x) {
        step = sqrt(r * r - (x - cx) * (x - cx));
        setPixel(x, round(cy + step));
        setPixel(x, round(cy - step));
    }
}

void Circles::fillHorizontalLine(int xStart, int xEnd, int y){
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2i(xStart, y);
    glVertex2i(xEnd, y);
    glEnd();
}


void Circles::BresenhamFill(int cx, int cy, int r){
    int d = 3 - 2 * r;
    int x = 0, y = r;
    while (x <= y) {
        fillHorizontalLine(cx + x, cx - x, cy + y);
        fillHorizontalLine(cx + x, cx - x, cy - y);
        fillHorizontalLine(cx + y, cx - y, cy + x);
        fillHorizontalLine(cx + y, cx - y, cy - x);
        if (d < 0) {
            d += 4 * x + 6;
        } else {
            d += 4 * (x - y) + 10;
            --y;
        }
        ++x;
    }
}

void Circles::Bresenham(int cx, int cy, int r) {
    int d = 3 - 2 * r;
    int x = 0, y = r;
    while (x <= y) {
        setPixel(cx + x, cy + y);
        setPixel(cx - x, cy + y);
        setPixel(cx + x, cy - y);
        setPixel(cx - x, cy - y);
        setPixel(cx + y, cy + x);
        setPixel(cx - y, cy + x);
        setPixel(cx + y, cy - x);
        setPixel(cx - y, cy - x);
        if (d < 0) {
            d += 4 * x + 6;
        } else {
            d += 4 * (x - y) + 10;
            --y;
        }
        ++x;
    }
}

void Circles::MidPoint(int cx, int cy, int r) {
    int p = 1 - r, x = 0, y = r;
    while (x <= y) {
        setPixel(cx + x, cy + y);
        setPixel(cx - x, cy + y);
        setPixel(cx + x, cy - y);
        setPixel(cx - x, cy - y);
        setPixel(cx + y, cy + x);
        setPixel(cx - y, cy + x);
        setPixel(cx + y, cy - x);
        setPixel(cx - y, cy - x);
        if (p < 0) {
            p += 2 * x + 3;
        } else {
            p += 2 * x + 5 - 2 * y;
            --y;
        }
        ++x;
    }
}

void Circles::ParametricEquation(int cx, int cy, int r) {
    float step = 1.0 / r;
    int x, y;
    for (float theta = 0; theta < 2 * M_PI; theta += step) {
        x = cx + r * cos(theta);
        y = cy + r * sin(theta);
        setPixel(x, y);
    }
}

void Circles::reshape(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspectRatio = (float) width / height;
    if (width > height)
        gluOrtho2D(0, 1000.0 * aspectRatio, 0, 1000);
    else
        gluOrtho2D(0, 1000.0, 0, 1000.0 / aspectRatio);
    glViewport(0, 0, width, height);
}

void Circles::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    Circles::BresenhamFill(500, 500, 200);
    glFlush();
}

void Circles::main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Circles");

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 1000.0, 0, 1000);

    glutDisplayFunc(Circles::render);
    glutReshapeFunc(Circles::reshape);
    glutMainLoop();
}