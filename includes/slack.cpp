#include <curl/curl.h>
#include <iostream>

#include "json.hpp"

#include "slack.h"
#include "helpers.h"

size_t noop_cb(void *ptr, size_t size, size_t nmemb, void *data) {
    return size * nmemb;
}

void scraper::Slack::send(std::string message) {

    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {

        curl_easy_setopt(curl, CURLOPT_URL,
                         "https://hooks.slack.com/services/token");

        nlohmann::json news;

        news = {
                {"channel",  "#logs-stage"},
                {"username", "NF-eBOT System Logs Stage"},
                {"text",     message}
        };

        std::string payload = news.dump();

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, noop_cb);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            fprintf(stderr, "Slack send failed: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);

    }

    curl_global_cleanup();

}

