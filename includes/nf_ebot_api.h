#pragma once

#include "../includes/json.hpp"

namespace scraper {

    class nfebotAPI {

    public:
        static std::string post_news(nlohmann::json news);

    };

}
