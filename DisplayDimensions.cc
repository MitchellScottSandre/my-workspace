using namespace std;

class DisplayDimensions {
private:
    int width;
    int height;

public:
    DisplayDimensions(int w, int h) : width{w}, height{h} {}

    int getWidth() { return this->width; }
    int getHeight() { return this->height; }
};