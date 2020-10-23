#include <GL/glut.h>
#include <cmath>

void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}


void directScan(int xs, int ys, int xe, int ye) {
    float x, y;
    int dx = xe - xs;
    int dy = ye - ys;
    float m = static_cast<float>(dy) / dx;
    float b;
    if (abs(m) < 1) {
        if (xe < xs) {
            x = xe;
            y = ye;
        } else {
            x = xs;
            y = ys;
        }
        b = y - m * x;
        for (int i = 0; i < abs(xe - xs); ++i) {
            setPixel(x, round(y));
            x += 1;
            y = m * x + b;
        }
    } else {
        if (ye < ys) {
            x = xe;
            y = ye;
        } else {
            x = xs;
            y = ys;
        }
        b = y - m * x;
        for (int i = 0; i < abs(ye - ys); ++i) {
            setPixel(x, round(y));
            y += 1;
            x = (y - b) / m;
        }
    }
}

void lineBresenham(int xs, int ys, int xe, int ye) {
    int dx = abs(xe - xs);
    int dy = abs(ye - ys);
    int p, iteration, lowerIncrement, upperIncrement, x, y;
    if (dy > dx) {
        // m > 1
        p = 2 * dx - dy;
        iteration = dy;
        lowerIncrement = 2 * dx;
        upperIncrement = lowerIncrement - 2 * dy;
        if (ye < ys) {
            x = xe;
            y = ye;
        } else {
            x = xs;
            y = ys;
        }
        for (int i = 0; i < iteration; ++i) {
            setPixel(x, y);
            y++;
            if (p < 0) {
                p += lowerIncrement;
            } else {
                x++;
                p += upperIncrement;
            }
        }

    } else {
        // m <= 1
        p = 2 * dy - dx;
        iteration = dx;
        lowerIncrement = 2 * dy;
        upperIncrement = lowerIncrement - 2 * dx;
        if (xe < xs) {
            x = xe;
            y = ye;
        } else {
            x = xs;
            y = ys;
        }
        for (int i = 0; i < iteration; ++i) {
            setPixel(x, y);
            x++;
            if (p < 0) {
                p += lowerIncrement;
            } else {
                y++;
                p += upperIncrement;
            }
        }
    }
}

void digitalDifferentialAnalyser(int xs, int ys, int xe, int ye) {
    int dx = xe - xs;
    int dy = ye - ys;

    float step;
    if (abs(static_cast<float>(dx)) > abs(static_cast<float>(dy))) {
        // m < 1
        step = abs(static_cast<float>(dx));
    } else {
        // m >= 1
        step = abs(static_cast<float>(dy));
    }

    float xi, yi;
    xi = static_cast<float>(dx) / step;
    yi = static_cast<float>(dy) / step;

    float x = xs, y = ys;
    for (int i = 0; i < step; ++i) {
        setPixel(round(x), round(y));
        x += xi;
        y += yi;
    }
}


void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 1, 0);
    directScan(900, 100, 200, 200);
//    digitalDifferentialAnalyser(900, 100, 200, 200);
    glColor3f(1, 0, 0);
    directScan(100, 100, 200, 900);
//    digitalDifferentialAnalyser(100, 100, 200, 900);
    glFlush();
}

void init() {
    glClearColor(1, 1, 1, 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 1000, 0, 1000)

}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(300, 200);
    glutCreateWindow("Line Generation");
    init();
    glutDisplayFunc(render);
    glutMainLoop();
}