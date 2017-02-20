#pragma once

#include <string>
#include <iostream>

#include <curl/curl.h>

namespace scraper {

    class getUrl {

        CURL *curl;
        std::string curlBuffer;
        CURLcode res;

    public:

        getUrl(std::string url);

        ~getUrl();

        static int curlWriter(char *data, size_t size, size_t nmemb, std::string *buffer);

        std::string getData();

    };

}