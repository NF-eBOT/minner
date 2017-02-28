#pragma once

#include <string>

namespace scraper {

    // TODO: Make this Config more simple
    class Config {

    public:

        /// General
        int loop_interval;

        /// API
        std::string api_url;
        std::string api_token;

        /// slack
        std::string slack_token;
        std::string slack_channel;
        std::string slack_username;

        Config() {

            loop_interval = 0;

            /*
            api_url = "https://api.nfebot.com.br:8443/news";
            api_token = "a4b45ebf0220ba7b27541527f3fd24aa2a3d0bf6af696f32859f76870ade317b224d9e7e8ee0e1ac6c23225104565093f390f99f5a1a1815879892a7b72f7c42";

            slack_token = "T331BFP55/B32DBUYCD/2ESRWWVJsrxOIs11ogU4cZbX";
            slack_channel = "#logs";
            slack_username = "NF-eBOT C++ Scraper";
             * */

            api_url = "http://localhost:8080/news";
            api_token = "a4b45ebf0220ba7b27541527f3fd24aa2a3d0bf6af696f32859f76870ade317b224d9e7e8ee0e1ac6c23225104565093f390f99f5a1a1815879892a7b72f7c42";

            slack_token = "T331BFP55/B34CSSX2N/xj9RaAcrVu7VxBLR7mH0rusx";
            slack_channel = "#logs-stage";
            slack_username = "[STAGE] NF-eBOT C++ Scraper";

        }

    };

}