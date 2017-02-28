#include <iostream>
#include <thread>
#include <memory>
#include <string>

/// Vendor libs
#include "json.hpp"
#include "rapidxml/rapidxml.hpp"

#include "logger.cpp"

/// Configuration variables
#include "config.h"

/// Instructions with libcurl to get HTML from URL
#include "geturl.cpp"

/// General helpers
#include "helpers.cpp"

#include "parsers/nfe_fazenda_tecnicos.cpp"
#include "parsers/nfe_fazenda_avisos.cpp"

int main(int argc, char *argv[]) {

    scraper::Logger logger;
    logger.info("Started foo main !", false);
    
    std::unique_ptr<parsers::GeneralParser> parser;
    parsers::nfeFazendaTecnicos nfeFazendaTecnicos;
    parser = std::make_unique<parsers::nfeFazendaTecnicos>();

    /// Get HTML/XML from PAGE_URL
    scraper::getUrl web(parser->PAGE_URL);
    std::string res = web.getData();

    /// Create XML object from HTML
    rapidxml::xml_document<> doc;
    char *cstr = new char[res.size() + 1];
    strcpy(cstr, res.c_str());
    doc.parse<0>(cstr);

    parser->parse(doc);

    std::cout << parser->news << std::endl;

}