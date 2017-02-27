#pragma once

#include <string>
#include <curl/curl.h>

#include "json.hpp"

#include "config.h"

#include "helpers.h"

namespace scraper {

    class Slack {

    public:
        static void send(const std::string message);
    };

}