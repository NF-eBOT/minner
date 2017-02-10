#include <curl/curl.h>

namespace GetURL{

    class getUrl {

    public: getUrl (std::string url) {

            curl_global_init(CURL_GLOBAL_DEFAULT);
            curl = curl_easy_init();

            if(!curl)
                throw std::string ("Curl did not initialize!");

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &getUrl::curlWriter);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curlBuffer);
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            curl_global_cleanup();

        };

        static int curlWriter(char *data, size_t size, size_t nmemb, std::string *buffer) {

            int result = 0;
            if (buffer != NULL) {
                buffer->append(data, size * nmemb);
                result = size * nmemb;
            }
            return result;

        }

        std::string getData () {
            return curlBuffer;
        }

    protected:
        CURL * curl;
        std::string curlBuffer;

    };

}