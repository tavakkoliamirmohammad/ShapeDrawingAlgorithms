
#ifndef COMPUTERGRAPHICSPRACTICE_PARABOLA_H
#define COMPUTERGRAPHICSPRACTICE_PARABOLA_H

namespace Parabola{
    void render();

    void reshape(int width, int height);

    void setPixel(int x, int y);

    void MidPoint(int cx, int cy, int rx, int ry);

    void Bresenham(int xEnd, int yEnd);

    void main(int argc, char **argv);
}


#endif //COMPUTERGRAPHICSPRACTICE_PARABOLA_H
