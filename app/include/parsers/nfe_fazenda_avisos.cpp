#include "nfe_fazenda_avisos.h"

parsers::nfeFazendaAvisos::nfeFazendaAvisos() {

    NAME = "NF-e / Avisos";
    PAGE_URL = "http://www.nfe.fazenda.gov.br/portal/informe.aspx?ehCTG=false";
    BASE_URL = "http://www.nfe.fazenda.gov.br";
    KEY = "--nfe-avisos";

}

void parsers::nfeFazendaAvisos::parse(const rapidxml::xml_document<> &doc) {

    /// Logs
    scraper::Logger logger;
    int count_news = 0;

    /// Select important node in XML
    rapidxml::xml_node<> *node = doc.first_node("html")
            ->first_node("body")
            ->first_node("div")
            ->next_sibling("div")
            ->first_node()
            ->first_node("div")
            ->last_node()
            ->last_node();

    for (rapidxml::xml_node<> *content = node->first_node("div"); content; content = content->next_sibling()) {

        /// Get node class attribute
        std::string _class = content->first_attribute()->value();

        /// Check if node is news node
        if (_class == "divInforme") {

            /// Logs
            logger.debug("Found news " + std::to_string(count_news), NAME, false);
            count_news++;

            /// Get node value
            std::string content_news = content->first_node("p")->value();
            /// Remove strange things in text
            std::string news_sanitized = scraper::Helpers::remove_new_lines(content_news);

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
            std::string title = m_desc[1];
            std::string title_utf8 = scraper::Helpers::iso_8859_1_to_utf8(title);

            /// Create json to post in API
            nlohmann::json _new;
            _new["date"] = date;
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