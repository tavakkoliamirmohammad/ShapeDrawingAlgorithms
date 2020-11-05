
#ifndef COMPUTERGRAPHICSPRACTICE_PINGPONG_H
#define COMPUTERGRAPHICSPRACTICE_PINGPONG_H

#include <vector>

namespace PingPong {
    struct Player {
        int Position;
    };

    struct Ball {
        int Position_X;
        int Position_Y;
        float Velocity_X;
        float Velocity_Y;
    };

    struct Box {
        int Position_X;
        int Position_Y;
        bool Visible;

    };

    struct GameState {
        int FieldWidth;
        int FieldHeight;
        int RaquetWidth;
        int RaquetHeight;
        int RaquetMargin;
        int BallSize;

        Player player;
        Ball ball;
        std::vector<Box> boxes;

        GameState(int width, int height) :
                FieldWidth(width), FieldHeight(height) {
            RaquetWidth = height / 4;
            RaquetHeight = height / 24;
            BallSize = height / 24;
            RaquetMargin = width / 24;
        }

        void init();

        void next_state();

        void change_state(int state);
    };

    void init();

    void render();

    void reshape(int width, int height);

    void keyboard(unsigned char key, int x, int y);

    void keyboard_control(int key, int x, int y);

    void keyboard_up(int key, int x, int y);

    void mouse(int button, int state, int x, int y);

    void motion(int x, int y);

    void timer(int value);

    void main(int argc, char **argv);
}
#endif //COMPUTERGRAPHICSPRACTICE_PINGPONG_H
