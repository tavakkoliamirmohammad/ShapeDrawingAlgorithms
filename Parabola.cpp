#include <GL/glut.h>
#include "Parabola.h"

void Parabola::setPixel(int x, int y) {
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}


void Parabola::Bresenham(int cx, int cy, int rx, int ry) {

}

void Parabola::reshape(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspectRatio = (float) width / height;
    if (width > height)
        gluOrtho2D(0, 1000.0 * aspectRatio, 0, 1000);
    else
        gluOrtho2D(0, 1000.0, 0, 1000.0 / aspectRatio);
    glViewport(0, 0, width, height);
}

void Parabola::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    Parabola::Bresenham(500, 500, 200, 300);
    glFlush();
}

void Parabola::main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Ellipses");

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-500, 500, 0, 1000);

    glutDisplayFunc(Parabola::render);
    glutReshapeFunc(Parabola::reshape);
    glutMainLoop();
}
