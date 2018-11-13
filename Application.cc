#include <string>
#include "DisplayDimensions.cc"
#include "Utils.cc"
using namespace std;

class Application {
    private:
        string name;
        int position;
    public:
        static const int POSITION_LEFT = 1;
        static const int POSITION_MIDDLE = 2;
        static const int POSITION_RIGHT = 3;

        Application(string name, int position) : name{name}, position{position} {}

        void open() {
            string command = "osascript -e 'tell application \"" + this->getName() + "\" \nlaunch \nend tell'";
            Utils::getStdoutFromCommand(command);
        }

        void putInPosition(DisplayDimensions displayDimensions) {
            string bounds = "";
            string halfWidth = to_string(displayDimensions.getWidth() / 2);
            string height = to_string(displayDimensions.getHeight());
            string width = to_string(displayDimensions.getWidth());

            switch (position) {
                case POSITION_LEFT:
                    bounds = "{0, 0, " + halfWidth + ", " + height + " }";
                    break;
                case POSITION_MIDDLE:
                    bounds = "{0, 0, " + width + ", " + height + " }";
                    break;
                case POSITION_RIGHT:
                    bounds = "{" + halfWidth + ", 0, " + width + ", " + height + " }";
                    break;
            }

            string command = "osascript -e 'tell application \"" + this->getName() + "\"\nset bounds of  front window to " + bounds + "\nactivate\nnd tell'";
            cout << command << endl;
            Utils::getStdoutFromCommand(command);
        }

        void setup(DisplayDimensions displayDimensions) {
            open();
            Utils::delay(1);
            putInPosition(displayDimensions);
            Utils::delay(1);
        }
        
        string getName() {
            return this->name;
        }
};