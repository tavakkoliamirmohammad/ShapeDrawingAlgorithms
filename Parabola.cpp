#include <GL/glut.h>
#include <cmath>
#include "Parabola.h"

void Parabola::setPixel(int x, int y) {
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}


void Parabola::Bresenham(float a, int xEnd) {
    float d = 2 * a - 1;
    float x = 0, y = 0;
    while (x <= xEnd && x <= 1 / (2 * a)) {
        Parabola::setPixel(round(x), round(y));
        Parabola::setPixel(-round(x), round(y));
        if (d < 0) {
            d += 4 * a * x + 6 * a;
        } else {
            d += 4 * a * x + 6 * a - 2;
            ++y;
        }
        ++x;
    }
    while (x <= xEnd) {
        Parabola::setPixel(round(x), round(y));
        Parabola::setPixel(-round(x), round(y));
        if (d < 0) {
            d += 4 * a * x + 4 * a - 2;
            ++x;
        } else {
            d += -2;

        }
        ++y;
    }
}

void Parabola::MidPoint(float a, int xEnd) {
    float d = a - 1.0 / 2;
    float x = 0, y = 0;
    while (x <= xEnd && x <= 1 / (2 * a)) {
        Parabola::setPixel(round(x), round(y));
        Parabola::setPixel(-round(x), round(y));
        if (d < 0) {
            d += a * (2 * x + 3);
        } else {
            d += a * (2 * x + 3) - 1;
            ++y;
        }
        ++x;
    }
    while (x <= xEnd) {
        Parabola::setPixel(round(x), round(y));
        Parabola::setPixel(-round(x), round(y));
        if (d < 0) {
            d += a * (2 * x + 2) - 1;
            ++x;
        } else {
            d += -1;
        }
        ++y;
    }
}

void Parabola::reshape(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspectRatio = (float) width / height;
    if (width > height)
        gluOrtho2D(-1000, 1000.0 * aspectRatio, -1000, 1000);
    else
        gluOrtho2D(-1000, 1000.0, -1000, 1000.0 / aspectRatio);
    glViewport(0, 0, width, height);
}

void Parabola::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    Parabola::MidPoint(0.001, 900);
    glFlush();
}

void Parabola::main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Ellipses");

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1000, 1000, -1000, 1000);

    glutDisplayFunc(Parabola::render);
    glutReshapeFunc(Parabola::reshape);
    glutMainLoop();
}
