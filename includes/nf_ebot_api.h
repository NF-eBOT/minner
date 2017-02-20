#pragma once

#include <iostream>

#include <curl/curl.h>
#include "json.hpp"

#include "../src/config.h"

namespace scraper {

    class nfebotAPI {

        nfebotAPI();
        ~nfebotAPI();

    public:
        static std::string post_news(nlohmann::json news);

    };

}
