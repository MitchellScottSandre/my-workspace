#include "Application.h"
#include "DisplayDimensions.h"
#include "Desktop.h"
using namespace std;

struct Desktop::DesktopImpl {
    shared_ptr<Application> app1;
    shared_ptr<Application> app2;

    DesktopImpl(std::shared_ptr<Application> leftApp, std::shared_ptr<Application> rightApp) :
        app1{leftApp}, app2{rightApp} {}
};

Desktop::Desktop(std::shared_ptr<Application> leftApp, std::shared_ptr<Application> rightApp) : 
    desktopPimpl{make_unique<DesktopImpl>(leftApp, rightApp)} {}

Desktop::Desktop(std::shared_ptr<Application> centreApp) : 
    desktopPimpl{make_unique<DesktopImpl>(centreApp, nullptr)} {}

Desktop::~Desktop() {}

void Desktop::setupDesktop() {
    if (this->desktopPimpl->app1 != nullptr) {
        this->desktopPimpl->app1->setupApplication();
    }
    
    if (this->desktopPimpl->app2 != nullptr) {
        this->desktopPimpl->app2->setupApplication();
    }
}

    // static vector<Desktop> getDesktopsFromInput(string input) {
    //     vector<Desktop> desktops;
    //     const string desktopDelimiter = "||";
    //     const string applicationDelimiter = "|";
    //     size_t desktopDelimeterIndex = 0;
    //     string desktopToken;

    //     while ((desktopDelimeterIndex = input.find(desktopDelimiter)) != string::npos) {
    //         desktopToken = input.substr(0, desktopDelimeterIndex);
    //         int applicationDelimeterIndex = desktopToken.find(applicationDelimiter);

    //         string leftAppName = "";
    //         string middleAppName = "";
    //         string rightAppName = "";
            
    //         if (applicationDelimeterIndex == string::npos) {
    //             middleAppName = Utils::trim(desktopToken);
    //             cout << desktopToken << endl;
    //             desktops.emplace_back(Desktop(middleAppName));
    //         } else {
    //             leftAppName = Utils::trim(desktopToken.substr(0, applicationDelimeterIndex));
    //             rightAppName = Utils::trim(desktopToken.substr(applicationDelimeterIndex + 1));
    //             desktops.emplace_back(Desktop(leftAppName, rightAppName));
    //         }

    //         // Remove token from input 
    //         input.erase(0, desktopDelimeterIndex + desktopDelimiter.length());
    //     }

    //     return desktops;
    // }
    
    // static void switchDesktop(bool direction) {
    //     string directionKeyCode;
    //     if (direction == DIRECTION_LEFT) {
    //         directionKeyCode = "123";
    //     } else {
    //         directionKeyCode = "124";
    //     }

    //     string command = "osascript -e 'tell application \"System Events\" to key code " + directionKeyCode + " using control down'";
    //     Utils::getStdoutFromCommand(command);
    // }

// bool Desktop::parseDesktopTokensFromInput(vector<string> desktopTokens, string input) {

//     return true;
// }
