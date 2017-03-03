#include "sped.h"

parsers::Sped::Sped() {

    NAME = "Sped / Destaques";
    PAGE_URL = "http://sped.rfb.gov.br";
    BASE_URL = "http://sped.rfb.gov.br";
    KEY = "--sped";

}

void parsers::Sped::parse(const rapidxml::xml_document<> &doc) {

    /// Logs
    scraper::Logger logger;
    int count_news = 0;

    /// Select important node in XML
    rapidxml::xml_node<> *node = doc.first_node("article");

    for (rapidxml::xml_node<> *content = node->first_node(); content; content = content->next_sibling()) {

        std::string node_name = content->name();

        if(node_name == "section")
        {

            /// Logs
            logger.debug("Found news " + std::to_string(count_news), NAME, false);
            count_news++;

            std::string title = content->first_node()->first_node()->value();
            std::string date = content->first_node("p")->value();

            /// Create json to post in API
            nlohmann::json _new;
            _new["title"] = title;
            _new["date"] = date;

            _new["scraper"] = {
                    {"name",     NAME},
                    {"base_url", BASE_URL},
                    {"page_url", PAGE_URL},
                    {"interval", "0"}
            };

            this->news.push_back(_new);

        }
    }
}

void parsers::Sped::normalize_html(std::string &res){
    res.erase(0, res.find("<article class=\"container-conteudo-item grid-3\">"));
    res.erase(res.find("<!-- FIM: conteúdo -->"), res.find("</html>"));
};