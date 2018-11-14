#include "DisplayDimensions.h"

DisplayDimensions::DisplayDimensions(int w, int h) : width{w}, height{h} {}

int DisplayDimensions::getWidth() { return this->width; }
int DisplayDimensions::getHeight() { return this->height; }
