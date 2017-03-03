#pragma once

#include <string>
#include <regex>
#include <ctime>

namespace scraper {

    class Helpers {

    public:
        // TODO: Make const parameter
        static std::string iso_8859_1_to_utf8(std::string &str);
        // TODO: Make const parameter
        static std::string remove_new_lines(std::string text);

        static std::string date_time_now();

    };

}
