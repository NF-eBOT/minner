#pragma once

#include <string>
#include <iostream>

#include <curl/curl.h>
#include "json.hpp"

#include "../src/config.h"
#include "helpers.h"

namespace scraper {

    class Slack {

    public:
        static void send(std::string message);

    };

}
