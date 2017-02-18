#include <iostream>
#include <regex>
#include <sstream>

#include "../includes/json.hpp"
#include "../includes/colormod.h"
#include "../includes/rapidxml/rapidxml.hpp"

#include "../includes/geturl.h"
#include "../includes/helpers.h"

const std::string NAME("NF-e / Avisos");
const std::string PAGE_URL("http://www.nfe.fazenda.gov.br/portal/informe.aspx?ehCTG=false");
const std::string BASE_URL("http://www.nfe.fazenda.gov.br");
const int UPDATE_INTERVAL = 30;

Color::Modifier red(Color::FG_RED);
Color::Modifier green(Color::FG_GREEN);
Color::Modifier blue(Color::FG_BLUE);
Color::Modifier def(Color::FG_DEFAULT);

std::string sanitize(std::string text);

int main(){

    auto start = std::chrono::system_clock::now();
    std::cout << green << "---- Starting -> " << NAME << def << std::endl;

    scraper::getUrl web("http://www.nfe.fazenda.gov.br/portal/informe.aspx?ehCTG=false");
    std::string res = web.getData();

    if(res.empty())
    {
        std::cout << red << "Cannot access this url !" << std::endl;
    }
    else
    {

        rapidxml::xml_document<> doc;

        char* cstr = new char[res.size() + 1];
        strcpy(cstr, res.c_str());

        doc.parse<0>(cstr);

        rapidxml::xml_node<> *node = doc.first_node("html")
                ->first_node("body")
                ->first_node("div")
                ->next_sibling("div")
                ->first_node()
                ->first_node("div")
                ->last_node()
                ->last_node();

        for (rapidxml::xml_node<> * content = node->first_node("div"); content; content = content->next_sibling())
        {

            std::string _class = content->first_attribute()->value();

            if(_class == "divInforme") {

                std::string news_sanitized = sanitize(content->first_node("p")->value());
                const std::string& _news_sanitized = news_sanitized;

                std::regex r_date("^\\d{2}\\/\\d{2}\\/\\d{4}");
                std::smatch m_date;
                std::regex_search(_news_sanitized.begin(), _news_sanitized.end(), m_date, r_date);
                std::string date =  m_date[0];

                std::regex r_desc(" - (.*)");
                std::smatch m_desc;
                std::regex_search(_news_sanitized.begin(), _news_sanitized.end(), m_desc, r_desc);
                std::string description = m_desc[1];

                nlohmann::json news;
                news["date"] = date;
                news["title"] = description;

                news["scraper"] = {
                        {"name", NAME},
                        {"base_url", BASE_URL},
                        {"page_url", PAGE_URL}
                };

                std::cout << news << std::endl;

            }

        }

        delete[] cstr;

    }

    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << green << "---- Execution time -> " << elapsed.count() << "ms" << def << std::endl;

}

std::string sanitize(std::string text){

    std::string description_decoded = scraper::Helpers::iso_8859_1_to_utf8(text);
    std::regex remove_spaces("\\s+");

    return std::regex_replace(description_decoded, remove_spaces, " ");

};

/*




 -    //sleep
-
- #include <chrono>
-#include <thread>
-    std::chrono::seconds dura( 5);
-    std::this_thread::sleep_for( dura );



 * */