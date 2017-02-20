#include <iostream>
#include <thread>
#include <memory>

/// Vendor libs
#include "../includes/json.hpp"
#include "../includes/colormod.h"
#include "../includes/rapidxml/rapidxml.hpp"

/// Instructions with libcurl to get HTML from URL
#include "../includes/geturl.h"

/// General helpers
#include "../includes/helpers.h"

/// Send slack messages for monitoring and log
#include "../includes/slack.h"

/// nf-ebot API interface
#include "../includes/nf_ebot_api.h"

/// Configuration variables
#include "config.h"

/// Parsers
#include "../includes/parsers/general.h"
#include "../includes/parsers/nfe_fazenda_avisos.h"

/// Temrinal colors for logs
const Color::Modifier red(Color::FG_RED);
const Color::Modifier green(Color::FG_GREEN);
const Color::Modifier blue(Color::FG_BLUE);
const Color::Modifier yellow(Color::FG_YELLOW);
const Color::Modifier def(Color::FG_DEFAULT);

int main() {

    /// Initialize parser
    std::unique_ptr<parsers::GeneralParser> parser;
    parser = std::make_unique<parsers::nfeFazendaAvisos>();

    /// Config
    scraper::Config *config = new scraper::Config();

    /// Log
    std::string start_message = "Scraper started -> " + parser->NAME + " at " + scraper::Helpers::date_time_now();
    scraper::Slack::send(start_message);
    std::cout << blue << start_message << def << std::endl;

    /// Infinite loop, have pause set by const int UPDATE_INTERVAL
    for (;;) {

        try {

            /// Log
            auto start = std::chrono::system_clock::now();
            std::string start_message = "Scrap starting -> " + parser->NAME + " " + scraper::Helpers::date_time_now();
            std::cout << green << start_message << def << std::endl;

            /// Get HTML/XML from PAGE_URL
            scraper::getUrl web(parser->PAGE_URL);
            std::string res = web.getData();

            if (res.empty()) {
                std::cerr << red << "Scraper " + parser->NAME + " base url is offline!" << def << std::endl;
                scraper::Slack::send("Scraper " + parser->NAME + " base url is offline!");
            } else {

                /// Create XML object from HTML
                rapidxml::xml_document<> doc;
                char *cstr = new char[res.size() + 1];
                strcpy(cstr, res.c_str());
                doc.parse<0>(cstr);

                /// Extract news from XML and generate JSON
                std::vector<nlohmann::json> news = parser->extract(doc);

                /// Save news with nf-eBOT API
                for (int i = 0; i < news.size(); ++i) {

                    std::string response = scraper::nfebotAPI::post_news(news[i]);

                    if (response == "ok") {
                        std::cout << green << " - New " << std::to_string(i) << " saved" << def << std::endl;
                    } else {
                        std::string err = "Error in save new " + std::to_string(i) + ": " + response;
                        std::cerr << red << err << def << std::endl;
                        scraper::Slack::send(parser->NAME + ": " + err);
                    }

                }

                delete[] cstr;

            }

            /// Logs
            auto end = std::chrono::system_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            std::cout << green << "Scrap end, total execution time -> " << elapsed.count() << "ms" << def << std::endl;

            std::cout << yellow << "Wating " << std::to_string(config->loop_interval) << " seconds" << def
                      << std::endl;

            std::chrono::seconds interval(config->loop_interval);
            std::this_thread::sleep_for(interval);

        }
        catch (...) {

            // TODO: refactor error log
            scraper::Slack::send("Any error");
            std::cout << red << "Any motherfucker error!!!!" << std::endl;

        }


    }

}