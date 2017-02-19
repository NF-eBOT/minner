#pragma once

#include "../includes/json.hpp"

namespace scraper {

    class nfebotAPI {

    public:
        static void post_news(nlohmann::json news);

    };

}
