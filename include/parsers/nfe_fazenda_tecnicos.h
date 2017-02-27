#pragma once

#include <string>
#include <regex>

#include "rapidxml/rapidxml.hpp"
#include "json.hpp"

#include "general.h"
#include "helpers.h"

namespace parsers{

    class nfeFazendaTecnicos : public GeneralParser{

    public:
        nfeFazendaTecnicos();
        void parse(rapidxml::xml_document<> &doc);
    };

}