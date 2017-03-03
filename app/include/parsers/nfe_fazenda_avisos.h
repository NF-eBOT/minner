#pragma once

#include <string>
#include <regex>

#include "rapidxml/rapidxml.hpp"
#include "json.hpp"

#include "general.h"
#include "helpers.h"

namespace parsers{

    class nfeFazendaAvisos : public GeneralParser{

    public:
        nfeFazendaAvisos();
        void parse(const rapidxml::xml_document<> &doc);
    };

}