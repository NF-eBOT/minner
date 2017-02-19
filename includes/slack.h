#pragma once

#include <string>
#include <curl/curl.h>

namespace scraper {

    class Slack {

    public:
        static void send(std::string message);

    };

}
