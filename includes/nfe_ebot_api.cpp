#include <curl/curl.h>
#include <iostream>

#include "json.hpp"

#include "nf_ebot_api.h"

std::string scraper::nfebotAPI::post_news(nlohmann::json news){

    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {

        curl_easy_setopt(curl, CURLOPT_URL,
                         "apu_url");

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "X-TOKEN: token");
        headers = curl_slist_append(headers, "Content-Type: application/json");

        std::string payload = news.dump();

        //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, noop_cb);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            return curl_easy_strerror(res);

        return "ok";

    }

    curl_global_cleanup();

};