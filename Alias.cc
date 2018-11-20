#include "Alias.h"
using namespace std;

struct Alias::AliasImpl {
    bool isValid = true;
    string alias;
    string systemApplicationName;

    AliasImpl(string text) {
        int colonIndex = text.find(":");
        if (colonIndex == string::npos) {
            this->isValid = false;
        } else {
            this->alias = text.substr(1, colonIndex - 2);
            this->systemApplicationName = text.substr(colonIndex + 2, text.length() - colonIndex - 3);
        }
    }
};

Alias::Alias(string text) : aliasPimpl{make_unique<AliasImpl>(text)} {}
Alias::~Alias() {}

bool Alias::isValid() {
    return this->aliasPimpl->isValid;
}

string Alias::getAlias() {
    return this->aliasPimpl->alias;
}

string Alias::getSystemApplicationName() {
    return this->aliasPimpl->systemApplicationName;
}

