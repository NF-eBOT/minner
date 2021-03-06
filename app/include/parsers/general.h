#pragma once

#include "rapidxml/rapidxml.hpp"
#include "json.hpp"

namespace parsers{

    class GeneralParser{

    public:
        GeneralParser() = default;
        virtual ~GeneralParser() = default;

        std::string NAME;
        std::string PAGE_URL;
        std::string BASE_URL;
        std::string KEY;

        std::vector<nlohmann::json> news;

        virtual void parse(const rapidxml::xml_document<> &doc){};
        virtual void normalize_html(std::string &res){};

    };

}