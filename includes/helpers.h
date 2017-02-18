#include <string>

#ifndef NF_EBOT_SCRAPERS_HELPERS_H
#define NF_EBOT_SCRAPERS_HELPERS_H

namespace scraper
{

    class Helpers
    {

    public:
        static std::string iso_8859_1_to_utf8(std::string &str);

    };

}

#endif //NF_EBOT_SCRAPERS_HELPERS_H
