#include "api.h"

std::string scraper::nfebotAPI::post_news(const nlohmann::json news){

    scraper::Config config;
    scraper::Logger logger;

    if(config.dev_mode)
    {
        logger.warning(news.dump(), "", false);
        return "Dev mode activated.";
    }

    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {

        curl_easy_setopt(curl, CURLOPT_URL, config.api_url.c_str());

        // TODO: check if this is necessary \/
        struct curl_slist *headers = NULL;
        std::string token = "X-TOKEN: " + config.api_token;
        headers = curl_slist_append(headers, token.c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");

        std::string payload = news.dump();

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            return curl_easy_strerror(res);

        curl_easy_cleanup(curl);
        curl_global_cleanup();
        delete[] headers;

        return "ok";

    }

    return 0;

}