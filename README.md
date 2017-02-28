# NF-eBOT - Scrapers
Web scraper responsible to extract relevant news in Brazilian government portals.


## To Build
#### Dependencies
[libcurl](https://curl.haxx.se/libcurl) - install via OS package manager (ex: apt install libcurl)

#### First create ```doc/config.h``` with ```doc/config.h.dist``` template and run:
`./scripts/gcc_build.sh`


## To Run
`./build/scrapers_cpp.out scraper_key`

## Scrapers key
`nfe-notas-tecnicas` [nfe.fazenda.gov.br / Notas Técnicas](http://www.nfe.fazenda.gov.br/portal/listaConteudo.aspx?tipoConteudo=tW+YMyk/50s=)

`nfe-avisos` [nfe.fazenda.gov.br / Avisos](http://www.nfe.fazenda.gov.br/portal/informe.aspx?ehCTG=false)

`sped` [sped.rfb.gov.br / Destaques](http://sped.rfb.gov.br)

## Folder Structure
* `build`: where builded executable is saved
* `doc`: configuration file
* `include`: local headers
* `include/parsers`: logic of portals/sites scraped
* `lib`: vendor libs
* `scripts`: scripts to help build and install
* `spike`: files to test technologies or ideas
* `src`: main file


## TODO
* Create makefile based in `spike/gcc_build.sh`
* Make `doc/config.h` more simple
* Change all #include to use .h files
* Make const parameters in `include/helpers.h`
* Refactor this code block in `src/main.cpp`:
```
rapidxml::xml_document<> doc;
char *cstr = new char[res.size() + 1];
strcpy(cstr, res.c_str());
doc.parse<0>(cstr);
```


## Special thanks to:
[@mattgodbolt](https://github.com/mattgodbolt)
[@dascandy](https://github.com/dascandy)
[@famastefano](https://github.com/famastefano)
[@grisumbras](https://github.com/grisumbras)
[@Corristo](https://github.com/Corristo)

and other guys in [C++ Slack Group](http://cpplang.diegostamigni.com/)
