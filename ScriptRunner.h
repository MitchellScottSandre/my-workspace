#ifndef SCRIPT_RUNNER_H
#define SCRIPT_RUNNER_H
#include <string>
#include <vector>

class ScriptRunner {
public:
    static std::string executeCommand(std::string cmd);

    static std::vector<std::string> getApplicationNamesList();
};
#endif