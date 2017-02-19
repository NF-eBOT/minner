#include <iostream>
#include <regex>
#include <thread>

//// Vendor libs
#include "../includes/json.hpp"
#include "../includes/colormod.h"
#include "../includes/rapidxml/rapidxml.hpp"

//// Instructions with libcurl to get HTML from URL
#include "../includes/geturl.h"
//// General helpers
#include "../includes/helpers.h"
//// Send slack messages for monitoring and log
#include "../includes/slack.h"

//// Configurations
const std::string NAME("NF-e / Avisos");
const std::string PAGE_URL("http://www.nfe.fazenda.gov.br/portal/informe.aspx?ehCTG=false");
const std::string BASE_URL("http://www.nfe.fazenda.gov.br");
const int UPDATE_INTERVAL = 1;

//// Temrinal colors for logs
Color::Modifier red(Color::FG_RED);
Color::Modifier green(Color::FG_GREEN);
Color::Modifier blue(Color::FG_BLUE);
Color::Modifier yellow(Color::FG_YELLOW);
Color::Modifier def(Color::FG_DEFAULT);

int main() {

    //// Log
    std::string start_message = "Scraper started -> " + NAME + " at " + scraper::Helpers::date_time_now();
    scraper::Slack::send(start_message);
    std::cout << blue << start_message << def << std::endl;

    //// Infinite loop to run forever, have pause set by const int UPDATE_INTERVAL
    int n = 0;
    while (n == 0) {

        try {

            //// Log
            auto start = std::chrono::system_clock::now();
            std::cout << green << "Scrap starting -> " << NAME << " " << scraper::Helpers::date_time_now() << def
                      << std::endl;

            //// Get HTML/XML from PAGE_URL
            scraper::getUrl web(PAGE_URL);
            std::string res = web.getData();

            int count_news = 0;

            if (res.empty()) {
                std::cerr << red << "Scraper " + NAME + " base url is offline!" << std::endl;
                scraper::Slack::send("Scraper " + NAME + " base url is offline!");
            } else {

                //// Create XML object from HTML
                rapidxml::xml_document<> doc;
                char *cstr = new char[res.size() + 1];
                strcpy(cstr, res.c_str());
                doc.parse<0>(cstr);

                //// Select important node in XML
                rapidxml::xml_node<> *node = doc.first_node("html")
                        ->first_node("body")
                        ->first_node("div")
                        ->next_sibling("div")
                        ->first_node()
                        ->first_node("div")
                        ->last_node()
                        ->last_node();

                for (rapidxml::xml_node<> *content = node->first_node("div"); content; content = content->next_sibling()) {

                    //// Get node class attribute
                    std::string _class = content->first_attribute()->value();

                    //// Check if node is news node
                    if (_class == "divInforme") {

                        //// Logs
                        count_news++;
                        std::cout << blue << "\tFound news " + std::to_string(count_news) << def << std::endl;

                        //// Get node value
                        std::string content_news = content->first_node("p")->value();
                        //// Remove strange things in text
                        std::string news_sanitized = scraper::Helpers::sanitize_news(content_news);

                        const std::string &_news_sanitized = news_sanitized;

                        //// Extract date
                        std::regex r_date("^\\d{2}\\/\\d{2}\\/\\d{4}");
                        std::smatch m_date;
                        std::regex_search(_news_sanitized.begin(), _news_sanitized.end(), m_date, r_date);
                        std::string date = m_date[0];

                        //// Extract title/description
                        std::regex r_desc(" - (.*)");
                        std::smatch m_desc;
                        std::regex_search(_news_sanitized.begin(), _news_sanitized.end(), m_desc, r_desc);
                        std::string description = m_desc[1];

                        //// Create json to post in API
                        nlohmann::json news;
                        news["date"] = date;
                        news["title"] = description;

                        news["scraper"] = {
                                {"name",     NAME},
                                {"base_url", BASE_URL},
                                {"page_url", PAGE_URL}
                        };

                    }

                }

                delete[] cstr;

            }

            //// Logs
            auto end = std::chrono::system_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            std::cout << green << "Scrap end, total execution time -> " << elapsed.count() << "ms" << def << std::endl;

            std::cout << yellow << "Wating " << std::to_string(UPDATE_INTERVAL) << " seconds" << def << std::endl;

            std::chrono::seconds interval(UPDATE_INTERVAL);
            std::this_thread::sleep_for(interval);

        }
        catch (...) {

            // TODO: refactor error log
            scraper::Slack::send("Any error");
            std::cout << red << "Any motherfucker error!!!!" << std::endl;

        }


    }

}