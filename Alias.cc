#include "Alias.h"
using namespace std;

struct Alias::AliasImpl {
    string alias;
    string systemApplicationName;

    AliasImpl(string text) {
        int colonIndex = text.find(":");
        this->alias = text.substr(1, colonIndex - 2);
        this->systemApplicationName = text.substr(colonIndex + 2, text.length() - colonIndex - 3);
    }
};

Alias::Alias(string text) : aliasPimpl{make_unique<AliasImpl>(text)} {}
Alias::~Alias() {}

string Alias::getAlias() {
    return this->aliasPimpl->alias;
}

string Alias::getSystemApplicationName() {
    return this->aliasPimpl->systemApplicationName;
}

