#ifndef ALIAS_H
#define ALIAS_H
#include <string>
#include <memory>

class Alias {
private:
    struct AliasImpl;
    std::unique_ptr<AliasImpl> aliasPimpl;

public:
    Alias(std::string text);
    ~Alias();
    std::string getAlias();
    std::string getSystemApplicationName();
};
#endif