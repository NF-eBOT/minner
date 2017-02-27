#include "nfe_fazenda_tecnicos.h"

parsers::nfeFazendaTecnicos::nfeFazendaTecnicos() {

    this->NAME = "NF-e / Notas Técnicas";
    this->PAGE_URL = "http://www.nfe.fazenda.gov.br/portal/listaConteudo.aspx?tipoConteudo=tW+YMyk/50s=";
    this->BASE_URL = "http://www.nfe.fazenda.gov.br";
    this->ARGV_KEY = "nfe-notas-tecnicas";

}

void parsers::nfeFazendaTecnicos::parse(rapidxml::xml_document<> &doc) {

    /// Logs
    int count_news = 0;

    /// Select important node in XML
    rapidxml::xml_node<> *node = doc.first_node("html")
            ->first_node("body")
            ->last_node("div")
            ->first_node("form")
            ->first_node("div")
            ->last_node("div")
            ->last_node("div")
            ->first_node()
            ->first_node("body")
            ->last_node();
            //->document()
            //->first_node()
            //->first_node("body")
            //->last_node();
            //->first_node();
            //->next_sibling();
            //->last_node();
            //->next_sibling("div");

            /*
            ->first_node("div")
            ->next_sibling("div")
            ->first_node()
            ->first_node("div")
            ->last_node()
            ->last_node();
             */

    for (rapidxml::xml_node<> *content = node->first_node("div"); content; content = content->next_sibling()) {

        std::string _class = content->first_attribute()->value();

        std::cout << _class << std::endl;

        if(_class == "indentacaoNormal"){
            
            std::cout << "\t" << "found" << std::endl;
            

            for (rapidxml::xml_node<> *content_2 = content->first_node(); content_2; content_2 = content_2->next_sibling()) {

                std::string _class = content->name();

                std::cout << "\t\t" << _class << std::endl;


            }

        }

    }



    /*

     for (rapidxml::xml_node<> *content = node->first_node("div"); content; content = content->next_sibling()) {

        /// Get node class attribute
        std::string _class = content->first_attribute()->value();

        /// Check if node is news node
        if (_class == "divInforme") {

            /// Logs
            count_news++;
            std::cout << blue << "Found news " + std::to_string(count_news) << def << std::endl;

            /// Get node value
            std::string content_news = content->first_node("p")->value();
            /// Remove strange things in text
            std::string news_sanitized = scraper::Helpers::sanitize_news(content_news);

            const std::string &_news_sanitized = news_sanitized;

            /// Extract date
            std::regex r_date("^\\d{2}\\/\\d{2}\\/\\d{4}");
            std::smatch m_date;
            std::regex_search(_news_sanitized.begin(), _news_sanitized.end(), m_date, r_date);
            std::string date = m_date[0];

            /// Extract title/description
            std::regex r_desc(" - (.*)");
            std::smatch m_desc;
            std::regex_search(_news_sanitized.begin(), _news_sanitized.end(), m_desc, r_desc);
            std::string description = m_desc[1];

            /// Create json to post in API
            nlohmann::json _new;
            _new["date"] = date;
            _new["title"] = description;

            _new["scraper"] = {
                    {"name",     this->NAME},
                    {"base_url", this->BASE_URL},
                    {"page_url", this->PAGE_URL},
                    {"interval", "0"}
            };

            this->news.push_back(_new);

        }
    }

     */

}