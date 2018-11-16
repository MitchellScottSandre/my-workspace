#ifndef DISPLAY_DIMENSIONS_H
#define DISPLAY_DIMENSIONS_H

class DisplayDimensions {
private:
    int width;
    int height;

public:
    DisplayDimensions(int w, int h);
    ~DisplayDimensions();
    int getWidth();
    int getHeight();
};

#endif