#pragma once

#include <string>
#include <regex>

#include "../rapidxml/rapidxml.hpp"
#include "../json.hpp"
#include "../colormod.h"

#include "general.h"
#include "../helpers.h"

namespace parsers{

    class nfeFazendaAvisos : public GeneralParser{

    public:
        nfeFazendaAvisos();

    };

}