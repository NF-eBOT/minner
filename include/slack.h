#pragma once

#include <string>
#include <iostream>
#include <curl/curl.h>

#include "../lib/json.hpp"

#include "../doc/config.h"

#include "helpers.h"

namespace scraper {

    class Slack {

    public:
        static void send(std::string message);

    };

}
