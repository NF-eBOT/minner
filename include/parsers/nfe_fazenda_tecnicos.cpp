#include "nfe_fazenda_tecnicos.h"

parsers::nfeFazendaTecnicos::nfeFazendaTecnicos() {

    NAME = "NF-e / Notas Técnicas";
    PAGE_URL = "http://www.nfe.fazenda.gov.br/portal/listaConteudo.aspx?tipoConteudo=tW+YMyk/50s=";
    BASE_URL = "http://www.nfe.fazenda.gov.br";
    ARGV_KEY = "nfe-notas-tecnicas";

}

void parsers::nfeFazendaTecnicos::parse(const rapidxml::xml_document<> &doc) {

    /// Logs
    scraper::Logger logger;
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

    for (rapidxml::xml_node<> *content = node->first_node("div"); content; content = content->next_sibling()) {

        std::string _class = content->first_attribute()->value();

        if (_class == "indentacaoNormal") {

            for (rapidxml::xml_node<> *content_p = content->first_node(
                    "p"); content_p; content_p = content_p->next_sibling()) {

                /// Logs
                logger.debug("Found news " + std::to_string(count_news), NAME, false);
                count_news++;

                std::string title = content_p->first_node("a")->first_node("span")->value();
                std::string title_utf8 = scraper::Helpers::iso_8859_1_to_utf8(title);

                /// Create json to post in API
                nlohmann::json _new;
                _new["title"] = title_utf8;

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
}