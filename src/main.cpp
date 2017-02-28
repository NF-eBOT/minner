#include <iostream>
#include <thread>
#include <memory>
#include <string>

/// Vendor libs
#include "json.hpp"
#include "rapidxml/rapidxml.hpp"

/// Configuration variables
#include "config.h"

/// Logger
#include "logger.cpp"

/// Instructions with libcurl to get HTML from URL
#include "geturl.cpp"

/// General helpers
#include "helpers.cpp"

/// nf-ebot API interface
#include "nf_ebot_api.cpp"

/// Parsers
#include "parsers/general.h"
#include "parsers/nfe_fazenda_avisos.cpp"
#include "parsers/nfe_fazenda_tecnicos.cpp"
#include "parsers/sped.cpp"

int main(int argc, char *argv[]) {

    scraper::Logger logger;
    scraper::Config config;

    /// Log
    logger.info("Scraper main process started at " + scraper::Helpers::date_time_now(), "General", true);

    if (argc == 1) {
        logger.error("Scraper not defined, see README.md for more informations!", "General", false);
        return -1;
    }

    std::string arg_parser = argv[1];

    /// Initialize parsers
    std::unique_ptr <parsers::GeneralParser> parser;

    parsers::nfeFazendaAvisos nfeFazendaAvisos;
    parsers::nfeFazendaTecnicos nfeFazendaTecnicos;
    parsers::Sped Sped;

    /// Define parse by command line argument
    if (arg_parser == nfeFazendaAvisos.ARGV_KEY)
        parser = std::make_unique<parsers::nfeFazendaAvisos>();
    else if (arg_parser == nfeFazendaTecnicos.ARGV_KEY)
        parser = std::make_unique<parsers::nfeFazendaTecnicos>();
    else if (arg_parser == Sped.ARGV_KEY)
        parser = std::make_unique<parsers::Sped>();

    if (!parser) {
        logger.error("Invalid scrap, see README.md for more informations!", "General", false);
        return -1;
    }

    logger.debug("Scraper with parser started.", parser->NAME, false);

    /// Infinite loop, have pause set by const int UPDATE_INTERVAL
    for (;;) {

        try {

            /// Log
            auto start = std::chrono::system_clock::now();
            std::string start_message = "Scrap starting -> " + parser->NAME + " " + scraper::Helpers::date_time_now();
            logger.info(start_message, parser->NAME, false);

            /// Get HTML/XML from PAGE_URL
            scraper::getUrl web(parser->PAGE_URL);
            std::string res = web.getData();

            if (res.empty()) {
                logger.error("Scraper base url is offline!", parser->NAME, true);
            } else {

                /// Normalize HTML/XML, if necessary (some parsers not have normalize_html method)
                parser->normalize_html(res);

                /// Create XML object from HTML
                // TODO: Refactor this bad practice
                rapidxml::xml_document<> doc;
                char *cstr = new char[res.size() + 1];
                strcpy(cstr, res.c_str());
                doc.parse<0>(cstr);

                /// Execute parse, extract news and fill news vector
                parser->parse(doc);

                /// Save news with nf-eBOT API
                for (std::string::size_type i = 0; i < parser->news.size(); ++i) {

                    /// Post new in NF-eBOT API
                    std::string response = scraper::nfebotAPI::post_news(parser->news[i]);

                    if (response == "ok") {
                        logger.info("New " + std::to_string(i) + " saved", parser->NAME, false);
                    } else {
                        std::string err = "Error in save new " + std::to_string(i) + ": " + response;
                        logger.error(err, parser->NAME, true);
                    }

                }

                /// Clear news vector in parser
                parser->news.clear();

                delete[] cstr;

            }

            /// Logs
            auto end = std::chrono::system_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

            logger.info("Scrap end, total execution time -> " + std::to_string(elapsed.count()) + "ms", parser->NAME, false);
            logger.warning("Wating " + std::to_string(config.loop_interval) + " seconds", parser->NAME, false);

            std::chrono::seconds interval(config.loop_interval);
            std::this_thread::sleep_for(interval);

        }
        catch (...) {

            /// TODO: refactor error log
            logger.error("Any mother fucker catch error!", "Default", true);

        }
    }
}