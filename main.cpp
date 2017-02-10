#include <iostream>
#include <string>

#include "restclient-cpp/restclient.h"
#include "libs/rapidxml/rapidxml.hpp"
#include "libs/colormod.h"
#include "libs/geturl.h"

using namespace std;
using namespace rapidxml;

#define url "http://www.nfe.fazenda.gov.br/portal/informe.aspx?ehCTG=false"

int main ()
{

    auto start = std::chrono::system_clock::now();

    RestClient::Response r = RestClient::get("https://api.nfebot.com.br:8443/news");
    cout << r.body << endl;

    Color::Modifier red(Color::FG_RED);
    Color::Modifier def(Color::FG_DEFAULT);
    Color::Modifier green(Color::FG_GREEN);

    xml_document<> doc;

    cout << green << "---- NF-eBOT Scraper Started" << def << endl;

    GetURL::getUrl web(url);

    string res = web.getData();

    if(res.empty())
    {
        cerr << red << "Page not found" << def << endl;
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

    // Log
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << green << "---- END - execution time - " << elapsed.count() << "ms" << def << endl;

}


/*

 // Variables
    int integer;
    bool boolean = true; //8-bits
    char character;
    float decimal;
    double decimal_double;
    wchar_t long_text;
    //

    //sleep

 #include <chrono>
#include <thread>
    std::chrono::seconds dura( 5);
    std::this_thread::sleep_for( dura );


    CURL *curl;
    CURLcode res;
    xml_document<> doc;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

    if(curl) {

        curl_easy_setopt(curl, CURLOPT_URL, "http://www.nfe.fazenda.gov.br/portal/informe.aspx?ehCTG=false");

        res = curl_easy_perform(curl);

        cout << res << endl;

        // Create string from response
        //string str = curl_easy_strerror(res);
        //char* cstr = new char[str.size() + 1];
        //strcpy(cstr, str.c_str());

        //doc.parse<0>(cstr);

        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);

    }

    curl_global_cleanup();

    return 0;

 */