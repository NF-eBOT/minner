#include <string>
#include <regex>
#include <ctime>

#include "helpers.h"

std::string scraper::Helpers::iso_8859_1_to_utf8(std::string &str) {
    std::string strOut;
    for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
        uint8_t ch = *it;
        if (ch < 0x80) {
            strOut.push_back(ch);
        } else {
            strOut.push_back(0xc0 | ch >> 6);
            strOut.push_back(0x80 | (ch & 0x3f));
        }
    }

    return strOut;
}

std::string scraper::Helpers::sanitize_news(std::string text) {

    std::string description_decoded = scraper::Helpers::iso_8859_1_to_utf8(text);
    std::regex remove_spaces("\\s+");

    return std::regex_replace(description_decoded, remove_spaces, " ");

}

std::string scraper::Helpers::date_time_now() {

    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", timeinfo);
    std::string str(buffer);

    return str;

}