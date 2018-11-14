#include "SmartOpen.h"
#include "View.h"
#include "Controller.h"
using namespace std;

int main( int argc, char * argv[] ) {
    std::shared_ptr<SmartOpen> model = std::make_shared<SmartOpen>();
    std::shared_ptr<Controller> controller = std::make_shared<Controller>(model);
    View view(controller, model);
    model->attach(&view);
    model->run();
    return 0;
}