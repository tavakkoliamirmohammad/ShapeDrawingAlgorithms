#include <GL/glut.h>
#include "Ellipse.h"

void Ellipse::setPixel(int x, int y) {
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}


void Ellipse::Bresenham(int cx, int cy, int rx, int ry) {
    int d = 2 * ry * ry + rx * rx - 2 * rx * rx * ry;
    int x = 0, y = ry;
    while (ry * ry * x < rx * rx * y) {
        Ellipse::setPixel(cx + x, cy + y);
        Ellipse::setPixel(cx - x, cy + y);
        Ellipse::setPixel(cx + x, cy - y);
        Ellipse::setPixel(cx - x, cy - y);
        if (d < 0) {
            d += ry * ry * (4 * x + 6);
        } else {
            d += ry * ry * (4 * x + 6) + rx * rx * (4 - 4 * y);
            --y;
        }
        ++x;
    }
}

void Ellipse::reshape(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspectRatio = (float) width / height;
    if (width > height)
        gluOrtho2D(0, 1000.0 * aspectRatio, 0, 1000);
    else
        gluOrtho2D(0, 1000.0, 0, 1000.0 / aspectRatio);
    glViewport(0, 0, width, height);
}

void Ellipse::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    Ellipse::Bresenham(500, 500, 200, 300);
    glFlush();
}

void Ellipse::main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Ellipses");

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 1000.0, 0, 1000);

    glutDisplayFunc(Ellipse::render);
    glutReshapeFunc(Ellipse::reshape);
    glutMainLoop();
}