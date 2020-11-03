#include <GL/glut.h>
#include "Cycloid.h"

float view_width = 0;
float view_height = 0;
float parent_circle_angle = 0;
float child_circle_angle = 0;
int parent_radius = 150;
int child_radius = 75;

void Cycloid::setPixel() {
    glPointSize(9);
    glBegin(GL_POINTS);
    glVertex2i(child_radius, 0);
    glEnd();
}

void Cycloid::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glAccum(GL_RETURN, 0.99);

    glPushMatrix();
    glTranslatef(500, 500, 0);
    glTranslatef(parent_radius, 0, 0);
    glRotatef(parent_circle_angle, 0, 0, 1);
    glColor3f(1, 0, 0);

    glPushMatrix();
    glTranslatef(child_radius, 0, 0);
    glRotatef(child_circle_angle, 0, 0, 1);
    glColor3f(1, 0, 0);
    Cycloid::setPixel();

    glPopMatrix();
    glPopMatrix();
    glAccum(GL_LOAD, 1);
    glutSwapBuffers();
}

void Cycloid::timer(int) {
    parent_circle_angle += 0.5;
    child_circle_angle += 5;
    glutPostRedisplay();
    glutTimerFunc(1, Cycloid::timer, 0);
}

void Cycloid::reshape(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect_ratio = (float) width / height;
    if (width > height) {
        view_width = 1000 * aspect_ratio;
        view_height = 1000;
    } else {
        view_width = 1000;
        view_height = 1000 / aspect_ratio;
    }

    gluOrtho2D(0, view_width, 0, view_height);
    glViewport(0, 0, width, height);
}

void Cycloid::init() {

}

void Cycloid::main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1920, 1080);
    glutCreateWindow("Cycloid");
    Cycloid::init();
    glClearColor(1, 1, 1, 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 1000, 0, 1000);
    glClear(GL_COLOR_BUFFER_BIT);
    glAccum(GL_LOAD, 1);
    glutDisplayFunc(Cycloid::render);
    glutReshapeFunc(Cycloid::reshape);
    glutTimerFunc(5, Cycloid::timer, 0);
    glutMainLoop();
}