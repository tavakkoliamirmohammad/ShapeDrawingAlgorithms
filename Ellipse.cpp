#include <GL/glut.h>
#include <cmath>
#include "Ellipse.h"

void Ellipse::setPixel(int x, int y) {
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void Ellipse::arcBresenham(int cx, int cy, int rx, int ry, int start, int end) {
    int d = 2 * ry * ry + rx * rx - 2 * rx * rx * ry;
    int x = 0, y = ry;
    start = start / 180.0 * M_PI;
    end = end / 180.0 * M_PI;
    int angle;
    while (ry * ry * x < rx * rx * y) {
        angle = x != 0 ? atan((float) y / x) : atan(INFINITY);
        if (start <= angle && angle <= end) {
            Ellipse::setPixel(cx + x, cy + y);
        }
        if (start <= M_PI - angle && M_PI - angle <= end) {
            Ellipse::setPixel(cx - x, cy + y);
        }
        if (start <= M_PI + angle && M_PI + angle <= end) {
            Ellipse::setPixel(cx - x, cy - y);
        }
        if (start <= 2 * M_PI - angle && 2 * M_PI - angle <= end) {
            Ellipse::setPixel(cx + x, cy - y);
        }
        if (d < 0) {
            d += ry * ry * (4 * x + 6);
        } else {
            d += ry * ry * (4 * x + 6) + rx * rx * (4 - 4 * y);
            --y;
        }
        ++x;
    }
    while (y > 0) {
        angle = x != 0 ? atan((float) y / x) : atan(INFINITY);
        if (start <= angle && angle <= end) {
            Ellipse::setPixel(cx + x, cy + y);
        }
        if (start <= M_PI - angle && M_PI - angle <= end) {
            Ellipse::setPixel(cx - x, cy + y);
        }
        if (start <= M_PI + angle && M_PI + angle <= end) {
            Ellipse::setPixel(cx - x, cy - y);
        }
        if (start <= 2 * M_PI - angle && 2 * M_PI - angle <= end) {
            Ellipse::setPixel(cx + x, cy - y);
        }
        if (d > 0) {
            d += rx * rx * (-4 * y + 6);
        } else {
            d += ry * ry * (4 * x + 4) + rx * rx * (-4 * y + 6);
            x++;
        }
        --y;
    }
}

void Ellipse::arcMidpoint(int cx, int cy, int rx, int ry, int start, int end) {
    int x = 0;
    int y = ry;
    int angle;
    start = start / 180.0 * M_PI;
    end = end / 180.0 * M_PI;
    int d = ry * ry - rx * rx * ry + rx * rx / 4;
    while (ry * ry * x < rx * rx * y) {
        angle = x != 0 ? atan((float) y / x) : atan(INFINITY);
        if (start <= angle && angle <= end) {
            Ellipse::setPixel(cx + x, cy + y);
        }
        if (start <= M_PI - angle && M_PI - angle <= end) {
            Ellipse::setPixel(cx - x, cy + y);
        }
        if (start <= M_PI + angle && M_PI + angle <= end) {
            Ellipse::setPixel(cx - x, cy - y);
        }
        if (start <= 2 * M_PI - angle && 2 * M_PI - angle <= end) {
            Ellipse::setPixel(cx + x, cy - y);
        }

        if (d < 0) {
            d += 2 * ry * ry * x + ry * ry;
        } else {
            d += 2 * ry * ry * x + ry * ry - 2 * rx * rx * y;
            y--;
        }
        x++;
    }

    while (y > 0) {
        angle = x != 0 ? atan((float) y / x) : atan(INFINITY);
        if (start <= angle && angle <= end) {
            Ellipse::setPixel(cx + x, cy + y);
        }
        if (start <= M_PI - angle && M_PI - angle <= end) {
            Ellipse::setPixel(cx - x, cy + y);
        }
        if (start <= M_PI + angle && M_PI + angle <= end) {
            Ellipse::setPixel(cx - x, cy - y);
        }
        if (start <= 2 * M_PI - angle && 2 * M_PI - angle <= end) {
            Ellipse::setPixel(cx + x, cy - y);
        }

        if (d < 0) {
            d += 2 * rx * rx * y + rx * rx;
        } else {
            d += 2 * rx * rx * y + rx * rx - 2 * ry * ry * x;
            x++;
        }
        y--;
    }
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
    while (y > 0) {
        Ellipse::setPixel(cx + x, cy + y);
        Ellipse::setPixel(cx - x, cy + y);
        Ellipse::setPixel(cx + x, cy - y);
        Ellipse::setPixel(cx - x, cy - y);
        if (d > 0) {
            d += rx * rx * (-4 * y + 6);
        } else {
            d += ry * ry * (4 * x + 4) + rx * rx * (-4 * y + 6);
            x++;
        }
        --y;
    }
}

void Ellipse::MidPoint(int cx, int cy, int rx, int ry) {
    int x = 0;
    int y = ry;

    int d = ry * ry - rx * rx * ry + rx * rx / 4;
    while (ry * ry * x < rx * rx * y) {
        Ellipse::setPixel(cx + x, cy + y);
        Ellipse::setPixel(cx - x, cy + y);
        Ellipse::setPixel(cx + x, cy - y);
        Ellipse::setPixel(cx - x, cy - y);

        if (d < 0) {
            d += 2 * ry * ry * x + ry * ry;
        } else {
            d += 2 * ry * ry * x + ry * ry - 2 * rx * rx * y;
            y--;
        }
        x++;
    }

    while (y > 0) {
        Ellipse::setPixel(cx + x, cy + y);
        Ellipse::setPixel(cx - x, cy + y);
        Ellipse::setPixel(cx + x, cy - y);
        Ellipse::setPixel(cx - x, cy - y);

        if (d < 0) {
            d += 2 * rx * rx * y + rx * rx;
        } else {
            d += 2 * rx * rx * y + rx * rx - 2 * ry * ry * x;
            x++;
        }
        y--;
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
    Ellipse::arcMidpoint(500, 500, 100, 400, 0, 95);
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