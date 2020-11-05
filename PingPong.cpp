#include "PingPong.h"
#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;

#include "Circles.h"

#define RACQUET 1000
#define BALL_SHAPE 1001
#define BOX 1002

int range = 80;
int side = 50;


PingPong::GameState game(1000, 500);

void PingPong::GameState::init() {
    this->player.Position = (this->FieldWidth - this->RaquetWidth) / 2;

    this->ball.Position_X = this->FieldWidth / 4;
    this->ball.Position_Y = this->FieldHeight / 4;

    auto theta = ((double) rand() / (RAND_MAX)) * 360;
    this->ball.Velocity_X = cos(theta);
    this->ball.Velocity_Y = abs(sin(theta));
    game.boxes.clear();
    for (int i = 0; i < range; ++i) {
        Box b = Box();
        b.Position_X = (side * i) % game.FieldWidth;
        b.Position_Y = game.FieldHeight - ((side * i) / game.FieldWidth + 1) * side;
        b.Visible =((double) rand() / (RAND_MAX)) > 0.5;
        game.boxes.push_back(b);
    }
}

void PingPong::motion(int x, int y) {
}

void PingPong::timer(int value) {
    game.next_state();
}


bool Collision(int x0, int y0, int w0, int h0, int x1, int y1, int w1, int h1) {
    auto l = fmax(x0, x1);
    auto t = fmin(y0, y1);

    auto r0 = x0 + w0, r1 = x1 + w1;
    auto b0 = y0 - h0, b1 = y1 - h1;

    auto b = fmax(b0, b1);
    auto r = fmin(r0, r1);

    return l <= r && t >= b;
}


void PingPong::keyboard_control(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_RIGHT:
            game.change_state(1);
            break;
        case GLUT_KEY_LEFT:
            game.change_state(-1);
            break;
        default:
            game.change_state(0);
            break;
    }
}

void PingPong::keyboard_up(int key, int x, int y) {
    game.change_state(0);
}

void PingPong::mouse(int button, int state, int x, int y) {
}

void PingPong::GameState::next_state() {
    ball.Position_X += ball.Velocity_X * 10;
    ball.Position_Y += ball.Velocity_Y * 10;

    if (ball.Position_X <= 0) {
        ball.Position_X = 0;
        ball.Velocity_X *= -1;
    } else if (ball.Position_X >= this->FieldWidth) {
        ball.Position_X = this->FieldWidth;
        ball.Velocity_X *= -1;
    }

    if (Collision(player.Position, RaquetMargin, RaquetWidth, RaquetHeight,
                  ball.Position_X - BallSize / 2, ball.Position_Y - BallSize / 2, BallSize, BallSize)) {
        ball.Position_Y = RaquetMargin + RaquetHeight + BallSize;
        ball.Velocity_Y *= -1;
    } else {
        for (int i = 0; i < game.boxes.size(); ++i) {
            Box b = game.boxes[i];
            if (b.Visible && Collision(b.Position_X, b.Position_Y, side, side,
                                       ball.Position_X - BallSize / 2, ball.Position_Y - BallSize / 2, BallSize,
                                       BallSize)) {
                ball.Position_Y = b.Position_Y - side;
                ball.Velocity_Y *= -1;
                game.boxes.erase(boxes.begin() + i);
            }
        }
    }

    if (ball.Position_Y < -BallSize * 2 || ball.Position_Y > FieldWidth + BallSize * 2) {
        init();
    }

    glutPostRedisplay();
    glutTimerFunc(20, PingPong::timer, 0);
}

void PingPong::keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'q':
        case 'Q':
            exit(0);
            break;
        case 'i':
        case 'I':
            game.init();
            break;
    }
}


void PingPong::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    glTranslatef(game.player.Position, game.RaquetMargin, 0);
    glCallList(RACQUET);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(game.ball.Position_X, game.ball.Position_Y, 0);
    glCallList(BALL_SHAPE);
    glPopMatrix();

    for (Box b : game.boxes) {
        if (b.Visible) {
            glPushMatrix();
            glTranslatef(b.Position_X, b.Position_Y, 0);
            glCallList(BOX);
            glPopMatrix();
        }
    }
    glutSwapBuffers();
}

void PingPong::init() {
    game.init();

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1000, 0, 1000);

    glNewList(RACQUET, GL_COMPILE);
    glBegin(GL_QUADS);
    glVertex2i(0, 0);
    glVertex2i(game.RaquetWidth, 0);
    glVertex2i(game.RaquetWidth, game.RaquetHeight);
    glVertex2i(0, game.RaquetHeight);
    glEnd();
    glEndList();

    glNewList(BALL_SHAPE, GL_COMPILE);
    Circles::Bresenham(game.BallSize / 2, game.BallSize / 2, game.BallSize);
    glEndList();

    glNewList(BOX, GL_COMPILE);
    glBegin(GL_LINES);
    glVertex2i(0, 0);
    glVertex2i(side, 0);
    glVertex2i(side, 0);
    glVertex2i(side, side);
    glVertex2i(side, side);
    glVertex2i(0, side);
    glVertex2i(0, side);
    glVertex2i(0, 0);
    glEnd();
    glEndList();


}

void PingPong::GameState::change_state(int state) {
    this->player.Position =
            fmax(fmin(this->player.Position + state * 50, this->FieldWidth - this->RaquetWidth), 0);
    glutPostRedisplay();
}


void PingPong::reshape(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    auto aspectRatio = (float) game.FieldWidth / game.FieldHeight;
    gluOrtho2D(0, game.FieldWidth, -game.FieldWidth / aspectRatio / 2 + game.FieldHeight / 2,
               game.FieldWidth / aspectRatio / 2 + game.FieldHeight / 2);

    glViewport(5, 5, width - 10, height - 10);
}

void PingPong::main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(800, 600);
    glutCreateWindow("Ping Pong");
    //glutFullScreen();

    PingPong::init();

    glutDisplayFunc(PingPong::render);
    glutReshapeFunc(PingPong::reshape);
    glutKeyboardFunc(PingPong::keyboard);
    glutSpecialUpFunc(PingPong::keyboard_up);
    glutSpecialFunc(PingPong::keyboard_control);
    glutMouseFunc(PingPong::mouse);
    glutPassiveMotionFunc(PingPong::motion);
    glutTimerFunc(20, PingPong::timer, 0);

    glutMainLoop();
}
