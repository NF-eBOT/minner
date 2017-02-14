#include <iostream>
#include <string>

#include "restclient-cpp/restclient.h"

#include "libs/rapidxml/rapidxml.hpp"
#include "libs/colormod.h"
#include "libs/geturl.h"

using namespace std;
using namespace rapidxml;

std::string NAME = "NF-e / Avisos";
std::string PAGE_URL = "http://www.nfe.fazenda.gov.br/portal/informe.aspx?ehCTG=false";
std::string BASE_URL = "http://www.nfe.fazenda.gov.br";
int INTERVAL = 30;

int main ()
{

    auto start = std::chrono::system_clock::now();

    Color::Modifier red(Color::FG_RED);
    Color::Modifier def(Color::FG_DEFAULT);
    Color::Modifier green(Color::FG_GREEN);

    //try {

        //RestClient::Response r = RestClient::get("https://api.nfebot.com.br:8443/news");
        //cout << r.body << endl;

        xml_document<> doc;

        cout << green << "---- NF-eBOT Scraper Started" << def << endl;

        GetURL::getUrl web(PAGE_URL);

        string res = web.getData();

        if(res.empty())
        {
            cout << red << "Cannot access this url !" << endl;
        }
        else
        {

            char* cstr = new char[res.size() + 1];
            strcpy(cstr, res.c_str());

            doc.parse<0>(cstr);

            xml_node<> *node = doc.first_node("html")
                    ->first_node("body")
                    ->first_node("div")
                    ->next_sibling("div")
                    ->first_node()
                    ->first_node("div")
                    ->last_node()
                    ->last_node();

            cout << node->name() << " - " << node->first_attribute()->value() << endl;

            for (xml_node<> * content = node->first_node("div"); content; content = content->next_sibling())
            {

                string _class(content->first_attribute()->value());

                cout << " " << content->name() << " - " << _class << endl;

                if(_class == "divInforme")
                {

                    cout << "  " << content->first_node("p")->value() << endl;

                }

            }

        }

    //} catch (...) {
      //  cout << red << "Some error ocurred !" << endl;
    //}

    // Log
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << green << "---- END - execution time - " << elapsed.count() << "ms" << def << endl;

}


/*

 -    //sleep
-
- #include <chrono>
-#include <thread>
-    std::chrono::seconds dura( 5);
-    std::this_thread::sleep_for( dura );



 * */