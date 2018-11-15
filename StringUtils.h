#ifndef STRING_UTILS_H
#define STRING_UTILS_H
#include <sstream>      // std::stringstream
#include <istream>      // std::getLine
#include <vector>
#include <string>

//TODO: refactor this into one StringUitl class
class StringUtils {
public:
    static void split(std::vector<std::string> & data, std::string text, char delimiter) {
        stringstream ss(text);
        string token;
        while (getline(ss, token, delimiter)) {
            data.emplace_back(token);
        }
    }
    
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
    
    static void trim(std::string & s) {
        // Trim start of word
        char c = s.at(0);
        while (c == ' ') {
            s.erase(0, 1);
            c = s.at(0);
        }

        // Trim end of word
        c = s.at(s.length() - 1);
        while (c == ' ') {
            s.erase(s.length() - 1, 1);
            c = s.at(s.length() - 1);        
        }
    }

    static void removeFullScreenDelimiters(std::string & s) {
        s = s.substr(1, s.length() - 1);
        s = s.substr(0, s.length() - 1);
    }

    // Taken from https://en.cppreference.com/w/cpp/string/byte/tolower
    static std::string str_tolower(std::string s) {
        std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return std::tolower(c); });
        return s;
    }

    static bool equalsIgnoreCase(std::string a, std::string b) {
        return StringUtils::str_tolower(a) == StringUtils::str_tolower(b);
    }
};

#endif