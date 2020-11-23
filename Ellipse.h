#ifndef COMPUTERGRAPHICSPRACTICE_ELLIPSE_H
#define COMPUTERGRAPHICSPRACTICE_ELLIPSE_H

namespace Ellipse {
    void render();

    void reshape(int width, int height);

    void setPixel(int x, int y);

    void MidPoint(int cx, int cy, int rx, int ry);

    void Bresenham(int cx, int cy, int rx, int ry);

    void fillHorizontalLine(int xStart, int xEnd, int y);

    void BresenhamFill(int cx, int cy, int rx, int ry);

    void arcBresenham(int cx, int cy, int rx, int ry, int start, int end);

    void arcMidpoint(int cx, int cy, int rx, int ry, int startAngle, int endAngle);

    void main(int argc, char **argv);
};

#endif //COMPUTERGRAPHICSPRACTICE_ELLIPSE_H
