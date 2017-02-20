#include "nf_ebot_api.h"

std::string scraper::nfebotAPI::post_news(nlohmann::json news){

    scraper::Config *config = new Config();

    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {

        curl_easy_setopt(curl, CURLOPT_URL, config->api_url.c_str());

        struct curl_slist *headers = NULL;
        std::string token = "X-TOKEN: " + config->api_token;
        headers = curl_slist_append(headers, token.c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");

        std::string payload = news.dump();

        //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, noop_cb);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            return curl_easy_strerror(res);

        curl_easy_cleanup(curl);
        curl_global_cleanup();
        delete[] headers;
        delete config;

        return "ok";

    }

    curl_global_cleanup();

};