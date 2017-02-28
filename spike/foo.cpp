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

int main(int argc, char *argv[]) {

    scraper::Logger logger;
    logger.info("Started foo main !", false);

    std::unique_ptr<parsers::GeneralParser> parser;
    parser = std::make_unique<parsers::nfeFazendaTecnicos>();

    /// Get HTML/XML from PAGE_URL
    scraper::getUrl web(parser->PAGE_URL);
    std::string res = web.getData();

    parser->normalize_html(res);
    
    std::cout << res << std::endl;
    

    /*
    res.erase(0, res.find("<article class=\"container-conteudo-item grid-3\">"));
    res.erase(res.find("<!-- FIM: conteúdo -->"), res.find("</html>"));
     */
}