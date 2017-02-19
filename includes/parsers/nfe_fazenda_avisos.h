#pragma once

#include <string>
#include <regex>

#include "../rapidxml/rapidxml.hpp"
#include "../json.hpp"
#include "../colormod.h"

#include "../helpers.h"

namespace parsers{

    struct nfeFazendaAvisos{

        std::string NAME;
        std::string PAGE_URL;
        std::string BASE_URL;
        int UPDATE_INTERVAL;

        nfeFazendaAvisos();
        std::vector<nlohmann::json> extract(rapidxml::xml_document<>& doc);

    };

}