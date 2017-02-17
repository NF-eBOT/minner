#include <iostream>

#include "libs/colormod.h"
#include "libs/rapidxml/rapidxml.hpp"

#include "libs/geturl.h"
#include "libs/helpers.h"

//#include "restclient-cpp/restclient.h"

//#include "libs/geturl.h"

#define NAME "NF-e / Avisos"
#define PAGE_URL "http://www.nfe.fazenda.gov.br/portal/informe.aspx?ehCTG=false";
#define BASE_URL "http://www.nfe.fazenda.gov.br";
#define INTERVAL = 30;

Color::Modifier red(Color::FG_RED);
Color::Modifier def(Color::FG_DEFAULT);
Color::Modifier green(Color::FG_GREEN);

int main(){

    auto start = std::chrono::system_clock::now();
    std::cout << green << "---- Starting -> " << NAME << def << std::endl;

    scraper::getUrl web("http://www.nfe.fazenda.gov.br/portal/informe.aspx?ehCTG=false");
    std::string res = web.getData();

    if(res.empty())
    {
        std::cout << red << "Cannot access this url !" << std::endl;
    }
    else
    {

        rapidxml::xml_document<> doc;

        char* cstr = new char[res.size() + 1];
        strcpy(cstr, res.c_str());

        doc.parse<0>(cstr);

        rapidxml::xml_node<> *node = doc.first_node("html")
                ->first_node("body")
                ->first_node("div")
                ->next_sibling("div")
                ->first_node()
                ->first_node("div")
                ->last_node()
                ->last_node();

        std::cout << node->name() << " - " << node->first_attribute()->value() << std::endl;

        for (rapidxml::xml_node<> * content = node->first_node("div"); content; content = content->next_sibling())
        {

            std::string _class(content->first_attribute()->value());

            std::cout << " " << content->name() << " - " << _class << std::endl;

            if(_class == "divInforme") {

                std::string description = content->first_node("p")->value();
                std::string description_decoded = scraper::Helpers::iso_8859_1_to_utf8(description);

                std::cout << description_decoded << std::endl;

            }

        }

    }

    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << green << "---- Execution time -> " << elapsed.count() << "ms" << def << std::endl;

}



/*




 -    //sleep
-
- #include <chrono>
-#include <thread>
-    std::chrono::seconds dura( 5);
-    std::this_thread::sleep_for( dura );



 * */