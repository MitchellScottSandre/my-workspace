#ifndef STRING_TRIMMER_H
#define STRING_TRIMMER_H
#include <vector>
#include <string>

//TODO: refactor this into one StringUitl class
class StringTrimmer {
public:
    static void trim(std::string & x) {
        // Trim start of word
        char c = x.at(0);
        while (c == ' ') {
            x.erase(0, 1);
            c = x.at(0);
        }

        // Trim end of word
        c = x.at(x.length() - 1);
        while (c == ' ') {
            x.erase(x.length() - 1, 1);
            c = x.at(x.length() - 1);        
        }
    }
};

#endif