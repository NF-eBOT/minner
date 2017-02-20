#include <iostream>
#include <thread>
#include <memory>
#include <string>

/// Vendor libs
#include "../lib/json.hpp"
#include "../lib/rapidxml/rapidxml.hpp"

/// Configuration variables
#include "../doc/config.h"

/// Instructions with libcurl to get HTML from URL
#include "../include/geturl.h"

/// General helpers
#include "../include/helpers.h"

/// Send slack messages for monitoring and log
#include "../include/slack.h"

/// nf-ebot API interface
#include "../include/nf_ebot_api.h"

/// Logger
#include "../include/logger.h"

/// Parsers
#include "../include/parsers/general.h"
#include "../include/parsers/nfe_fazenda_avisos.h"

int main(int argc, char *argv[]) {

    scraper::Logger *logger = new scraper::Logger();
    scraper::Config *config = new scraper::Config();

    /// Log
    logger->info("Scraper main process started at " + scraper::Helpers::date_time_now(), true);

    /// Initialize generic parser
    std::unique_ptr<parsers::GeneralParser> parser;

    if(argc == 1)
    {
        logger->error("Scraper do not defined, see README.md for more informations!", false);
        return 0;
    }

    std::string arg = argv[1];

    parsers::nfeFazendaAvisos nfeFazendaAvisos;

    parser = std::make_unique<parsers::nfeFazendaAvisos>();

    /// Infinite loop, have pause set by const int UPDATE_INTERVAL
    for (;;) {

        try {

            /// Log
            auto start = std::chrono::system_clock::now();
            std::string start_message = "Scrap starting -> " + parser->NAME + " " + scraper::Helpers::date_time_now();
            logger->info(start_message, false);

            /// Get HTML/XML from PAGE_URL
            scraper::getUrl web(parser->PAGE_URL);
            std::string res = web.getData();

            if (res.empty()) {
                logger->error("Scraper " + parser->NAME + " base url is offline!", true);
            } else {

                /// Create XML object from HTML
                rapidxml::xml_document<> doc;
                char *cstr = new char[res.size() + 1];
                strcpy(cstr, res.c_str());
                doc.parse<0>(cstr);

                /// Extract news from XML and generate JSON
                std::vector<nlohmann::json> news = parser->extract(doc);

                /// Save news with nf-eBOT API
                for (std::string::size_type i = 0; i < news.size(); ++i) {

                    std::string response = scraper::nfebotAPI::post_news(news[i]);

                    if (response == "ok") {
                        logger->info(" - New " + std::to_string(i) + " saved", false);
                    } else {
                        std::string err = "Error in save new " + std::to_string(i) + ": " + response;
                        logger->error(err, true);
                    }

                }

                delete[] cstr;

            }

            /// Logs
            auto end = std::chrono::system_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

            logger->info("Scrap end, total execution time -> " + std::to_string(elapsed.count()) + "ms", false);
            logger->warning("Wating " + std::to_string(config->loop_interval) + " seconds", false);

            std::chrono::seconds interval(config->loop_interval);
            std::this_thread::sleep_for(interval);

        }
        catch (...) {

            /// TODO: refactor error log
            logger->error("Any mother fucker catch error!", true);

        }
    }
}