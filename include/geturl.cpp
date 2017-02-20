#include "geturl.h"

std::string scraper::getUrl::getData() {
    return curlBuffer;
}

scraper::getUrl::~getUrl() {
}

scraper::getUrl::getUrl(std::string url) {

    curl_global_init(CURL_GLOBAL_DEFAULT);
    this->curl = curl_easy_init();

    if (!this->curl)
        throw std::string("Curl did not initialize!");

    curl_easy_setopt(curl, CURLOPT_HTTP_CONTENT_DECODING, 1);
    curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "iso-8859-15");
    curl_easy_setopt(curl, CURLOPT_TRANSFER_ENCODING, 1);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

    curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, &this->curlWriter);
    curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &this->curlBuffer);
    curl_easy_setopt(this->curl, CURLOPT_URL, url.c_str());

    curl_easy_perform(this->curl);

    curl_easy_cleanup(this->curl);
    curl_global_cleanup();

}

int scraper::getUrl::curlWriter(char *data, size_t size, size_t nmemb, std::string *buffer) {

    int result = 0;

    if (buffer != NULL) {
        buffer->append(data, size * nmemb);
        result = size * nmemb;
    }

    return result;

}