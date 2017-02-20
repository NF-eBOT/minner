#pragma once

#include <string>
#include <regex>
#include <ctime>

namespace scraper {

    class Helpers {

    public:
        static std::string iso_8859_1_to_utf8(std::string &str);

        static std::string sanitize_news(std::string text);

        static std::string date_time_now();

    };

}
