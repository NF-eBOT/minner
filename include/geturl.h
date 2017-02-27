#pragma once

#include <string>

#include <curl/curl.h>

namespace scraper {

    class getUrl {

        CURL *curl;
        std::string curlBuffer;
        static int curlWriter(char *data, size_t size, size_t nmemb, std::string *buffer);

    public:

        getUrl(std::string url);
        ~getUrl();

        const std::string getData();

    };

}