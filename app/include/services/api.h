#pragma once

#include <curl/curl.h>

#include "json.hpp"

#include "config.h"
#include "logger.h"

namespace scraper {

    class nfebotAPI {

    public:
        nfebotAPI();
        ~nfebotAPI();

        static std::string post_news(const nlohmann::json news);

    };

}
