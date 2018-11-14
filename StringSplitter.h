#ifndef STRING_SPLITTER_H
#define STRING_SPLITTER_H
#include <vector>
#include <string>

class StringSplitter {
public:
    static void split(std::vector<std::string> & data, std::string text, std::string delimiter) {
        int delimiterLength = delimiter.length();
        size_t index = 0;
        std::string token;

        // Ensure it ends with the delimiter
        bool endsWithDelimiter = text.substr(text.length() - delimiterLength, delimiterLength) == delimiter;
    
        if (!endsWithDelimiter) {
            text += delimiter;
        }

        // Split the text
        while((index = text.find(delimiter)) != std::string::npos) {
            token = text.substr(0, index);
            data.emplace_back(token);
            text.erase(0, index + delimiterLength);
        }
    }
};

#endif