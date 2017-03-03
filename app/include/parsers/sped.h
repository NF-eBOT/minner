#pragma once

#include <string>
#include <regex>

#include "rapidxml/rapidxml.hpp"
#include "json.hpp"

#include "general.h"
#include "helpers.h"

namespace parsers{

    class Sped : public GeneralParser{

    public:
        Sped();
        void parse(const rapidxml::xml_document<> &doc);
        void normalize_html(std::string &res);
    };

}