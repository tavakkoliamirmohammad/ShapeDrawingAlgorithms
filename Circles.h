
#ifndef COMPUTERGRAPHICSPRACTICE_CIRCLES_H
#define COMPUTERGRAPHICSPRACTICE_CIRCLES_H

namespace Circles {
    void render();

    void reshape(int width, int height);

    void setPixel(int x, int y);

    void DirectEquation(int cx, int cy, int r);

    void ParametricEquation(int cx, int cy, int r);

    void Bresenham(int cx, int cy, int r);
    void BresenhamFill(int cx, int cy, int r);
    void fillhorizontalLine(int xStart, int xEnd, int y);
    void MidPoint(int cx, int cy, int r);

    void main(int argc, char **argv);
}


#endif //COMPUTERGRAPHICSPRACTICE_CIRCLES_H
