#include <string>
#include <memory>
#include "Application.cc"
using namespace std;

class Desktop {
private:
    unique_ptr<Application> app1;
    unique_ptr<Application> app2;
public:
    const static bool DIRECTION_LEFT = false;
    const static bool DIRECTION_RIGHT = true;

    Desktop(string leftAppName, string rightAppName) : 
        app1{make_unique<Application>(leftAppName, 1)}, 
        app2{make_unique<Application>(rightAppName, 3)} {}

    Desktop(string centreAppName) :  app1{make_unique<Application>(centreAppName, 2)}, app2{nullptr} {}

    void setupApplications(DisplayDimensions displayDimensions) {
        if (app1 != nullptr) {
            app1->setup(displayDimensions);
        }
        
        if (app2 != nullptr) {
            app2->setup(displayDimensions);
        }
    }

    static vector<Desktop> getDesktopsFromInput(string input) {
        vector<Desktop> desktops;
        const string desktopDelimiter = "||";
        const string applicationDelimiter = "|";
        size_t desktopDelimeterIndex = 0;
        string desktopToken;

        while ((desktopDelimeterIndex = input.find(desktopDelimiter)) != string::npos) {
            // Parse desktop token
            desktopToken = input.substr(0, desktopDelimeterIndex);
            int applicationDelimeterIndex = desktopToken.find(applicationDelimiter);
            string leftAppName = Utils::trim(desktopToken.substr(0, applicationDelimeterIndex));
            string rightAppName = Utils::trim(desktopToken.substr(applicationDelimeterIndex + 1));


            // Create Desktop
            // desktops.emplace_back(new Desktop(leftApp, rightApp));
            desktops.emplace_back(Desktop(leftAppName, rightAppName));

            // Remove token from input 
            input.erase(0, desktopDelimeterIndex + desktopDelimiter.length());
        }

        return desktops;
    }
    
    static void switchDesktop(bool direction) {
        string directionKeyCode;
        if (direction == DIRECTION_LEFT) {
            directionKeyCode = "123";
        } else {
            directionKeyCode = "124";
        }

        string command = "osascript -e 'tell application \"System Events\" to key code " + directionKeyCode + " using control down'";
        Utils::getStdoutFromCommand(command);
    }
};