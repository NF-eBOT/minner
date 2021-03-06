#include "slack.h"

size_t noop_cb(void *buffer, size_t size, size_t nmemb, void *userp) {
    return size * nmemb;
}

void scraper::Slack::send(const std::string message) {

    scraper::Config config;

    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {

        std::string slack_url = "https://hooks.slack.com/services/" + config.slack_token;
        curl_easy_setopt(curl, CURLOPT_URL, slack_url.c_str());

        nlohmann::json news;

        news = {
                {"channel",  config.slack_channel},
                {"username", config.slack_username},
                {"text",     message}
        };

        std::string payload = news.dump();

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, noop_cb);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            fprintf(stderr, "Slack send failed: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);

    }

    curl_global_cleanup();

}

