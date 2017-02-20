#pragma once

#include <iostream>

#include <curl/curl.h>

#include "../lib/json.hpp"

#include "../doc/config.h"

namespace scraper {

    class nfebotAPI {

        nfebotAPI();
        ~nfebotAPI();

    public:
        static std::string post_news(nlohmann::json news);

    };

}
