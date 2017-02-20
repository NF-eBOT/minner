#pragma once

#include <string>
#include <regex>

#include "../../lib/rapidxml/rapidxml.hpp"
#include "../../lib/json.hpp"
#include "../../lib/colormod.h"

#include "general.h"
#include "../helpers.h"

namespace parsers{

    class nfeFazendaAvisos : public GeneralParser{

    public:
        nfeFazendaAvisos();

    };

}