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
            string loation = "";
            string size = "";
            string halfWidth = to_string(displayDimensions.getWidth() / 2);
            string height = to_string(displayDimensions.getHeight());
            string width = to_string(displayDimensions.getWidth());

            switch (position) {
                case POSITION_LEFT:
                    loation = "{0, 0}";
                    size = "{" + halfWidth + ", " + height + "}";
                    break;
                case POSITION_MIDDLE:
                    loation = "{0, 0}";
                    size = "{" + width + ", " + height + "}";
                    break;
                case POSITION_RIGHT:
                    loation = "{" + halfWidth + ", 0}";
                    size = "{" + halfWidth + ", " + height + "}";
                    break;
            }

            string command1 = "osascript -e 'tell application \"System Events\" to set position of window 1 of application process \"" + this->getName() + "\" to " + loation + "'";
            string command2 = "osascript -e 'tell application \"System Events\" to set size of window 1 of application process \"" + this->getName() + "\" to " + size + "'";

            cout << command1 << endl;
            cout << command2 << endl;
            Utils::getStdoutFromCommand(command1);
            Utils::getStdoutFromCommand(command2);
        }

        void setup(DisplayDimensions displayDimensions) {
            open();
            putInPosition(displayDimensions);
            putInPosition(displayDimensions);
        }
        
        string getName() {
            return this->name;
        }
};