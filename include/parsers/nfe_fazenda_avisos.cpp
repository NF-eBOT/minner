#include "nfe_fazenda_avisos.h"

/// Temrinal colors for logs
const Color::Modifier red(Color::FG_RED);
const Color::Modifier green(Color::FG_GREEN);
const Color::Modifier blue(Color::FG_BLUE);
const Color::Modifier yellow(Color::FG_YELLOW);
const Color::Modifier def(Color::FG_DEFAULT);

parsers::nfeFazendaAvisos::nfeFazendaAvisos() {

    this->NAME = "NF-e / Avisos";
    this->PAGE_URL = "http://www.nfe.fazenda.gov.br/portal/informe.aspx?ehCTG=false";
    this->BASE_URL = "http://www.nfe.fazenda.gov.br";
    this->ARGV_KEY = "nfe-avisos";

}

std::vector<nlohmann::json> parsers::GeneralParser::extract(rapidxml::xml_document<> &doc) {

    std::vector<nlohmann::json> news;

    /// Logs
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

            news.push_back(_new);

        }

    }

    return news;

}