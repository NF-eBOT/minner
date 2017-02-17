#include <iostream>
#include <curl/curl.h>
#include "geturl.h"

std::string scraper::getUrl::getData() {
    return curlBuffer;
}

scraper::getUrl::~getUrl() {
}

scraper::getUrl::getUrl(std::string url) {

    struct curl_slist *list = NULL;

    list = curl_slist_append(list, "Content-Type:text/html;charset=iso-8859-15");

    //list = curl_slist_append(list, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
    /*
    list = curl_slist_append(list, "Connection: keep-alive");
    list = curl_slist_append(list, "Accept-Encoding: gzip,deflate,sdch");
    list = curl_slist_append(list, "Accept-Language: pt-BR,pt;q=0.8,en-US;q=0.6,en;q=0.4");
    list = curl_slist_append(list, "User-Agent: Mozilla/5.0 (X11; Linux i686) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/33.0.1750.115 Safari/537.36");
    //list = curl_slist_append(list, "Content: text/html");
    //list = curl_slist_append(list, "charset=latim1");
    //list = curl_slist_append(list, "Content-Encoding: gzip");
    list = curl_slist_append(list, "Accept-Charset: utf-8");
    //list = curl_slist_append(list, "Accept-Language: pt-br");
    //list = curl_slist_append(list, "Content-Language: pt, pt-BR");
    */

    curl_global_init(CURL_GLOBAL_DEFAULT);
    this->curl = curl_easy_init();

    if(!this->curl)
        throw std::string ("Curl did not initialize!");

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
    curl_easy_setopt(curl, CURLOPT_HTTP_CONTENT_DECODING, 1);
    curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "iso-8859-15");
    curl_easy_setopt(curl, CURLOPT_TRANSFER_ENCODING, 1);

    curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, &this->curlWriter);
    curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &this->curlBuffer);
    curl_easy_setopt(this->curl, CURLOPT_URL, url.c_str());

    curl_easy_perform(this->curl);

    curl_easy_cleanup(this->curl);
    curl_slist_free_all(list);
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