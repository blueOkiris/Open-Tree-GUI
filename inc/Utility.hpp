#pragma once

#include <string>
#include <vector>

namespace opentree {
    struct Rect {
        unsigned int x, y, w, h;
    };
    
    struct Vector2 {
        unsigned int x, y;
    };
    
    struct Color {
        uint8_t red, green, blue, alpha;
    };

    static inline std::vector<std::string> strsplit(
            const std::string &input, const char delim) {
        std::vector<std::string> substrs;
        
        std::string::size_type beg = 0;
        for(    std::string::size_type end = 0;
                (end = input.find(delim, end)) != std::string::npos;
                ++end) {
            substrs.push_back(input.substr(beg, end - beg));
            beg = end + 1;
        }
        substrs.push_back(input.substr(beg));

        return substrs;
    }
}
