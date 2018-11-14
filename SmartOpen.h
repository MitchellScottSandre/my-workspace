#include <string>

class SmartOpen {
private:
    std::string name;
    int position;

    std::string 

public:
    static const int POSITION_LEFT;
    static const int POSITION_MIDDLE;
    static const int POSITION_RIGHT;
    static const int FULL_SCREEN;

    SmartOpen();
    ~SmartOpen();
};