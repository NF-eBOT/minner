#pragma once

#include "../../lib/rapidxml/rapidxml.hpp"
#include "../../lib/json.hpp"

namespace parsers{

    class GeneralParser{

    public:
        GeneralParser() = default;
        virtual ~GeneralParser() = default;

        std::string NAME;
        std::string PAGE_URL;
        std::string BASE_URL;
        int UPDATE_INTERVAL;

        std::vector<nlohmann::json> extract(rapidxml::xml_document<>& doc);

    };

}