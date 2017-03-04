# Minner - Web Scraper
Minner is a easy way to make any web scraper for data-mining, builded in C++14, with only one shared library, libcurl. Have log messages with slack and terminal.

<br>

# Compile and Run

## # Production:
#### # 1. Dependencies
* gcc >= 3.5.1
* [libcurl](https://curl.haxx.se/libcurl) - install via OS package manager (ex: apt install libcurl)

#### # 2. Build configuration file
* Create ```doc/config.h``` with ```doc/config.h.dist``` template.

#### # 3. Compile:
* `cmake . && make`

#### # 4. Run:
* `./minner --SCRAPER_KEY`



## # With Vagrant :
`(best choice for Windows and dev)`
#### # 1. Dependencies
* Install [Vagrant](https://www.vagrantup.com/downloads.html)

#### # 1. Create vm and enter
* `vagrant up && vagrant ssh`

#### # 2. Build configuration file
* Create ```doc/config.h``` with ```doc/config.h.dist``` template.

#### # 3. Compile
* `cd /data && cmake . && make`

#### # 4. Run:
* `./minner --SCRAPER_KEY`

<br>

## To Run
`./minner --SCRAPER_KEY`

<br>

## About Scraper key
`--nfe-notas-tecnicas` [nfe.fazenda.gov.br / Notas Técnicas](http://www.nfe.fazenda.gov.br/portal/listaConteudo.aspx?tipoConteudo=tW+YMyk/50s=)

`--nfe-avisos` [nfe.fazenda.gov.br / Avisos](http://www.nfe.fazenda.gov.br/portal/informe.aspx?ehCTG=false)

`--sped` [sped.rfb.gov.br / Destaques](http://sped.rfb.gov.br)

<br>

## Folder Structure
* `app`: application source files
  * `app/include`: application lib/modules source file
    * `app/include/parsers`: web page parse layer
    * `app/include/services`: external web services
* `build`: where builded executable is saved (with you use ./scripts/gcc_build.sh)
* `doc`: configuration file
* `lib`: vendor libs
* `scripts`: scripts to help build and install
* `spike`: files to test technologies or ideas

<br>

## TODO
* Create makefile based in `spike/gcc_build.sh`
* Make `doc/config.h` more simple
* Change all #include to use .h files
* Make const parameters in `include/helpers.h`
* Refactor this code block in `app/main.cpp`:
```
rapidxml::xml_document<> doc;
char *cstr = new char[res.size() + 1];
strcpy(cstr, res.c_str());
doc.parse<0>(cstr);
```
And a lot of more refactors...

<br>

## Special thanks to:
[@mattgodbolt](https://github.com/mattgodbolt)
[@dascandy](https://github.com/dascandy)
[@famastefano](https://github.com/famastefano)
[@grisumbras](https://github.com/grisumbras)
[@Corristo](https://github.com/Corristo)

and other guys in [C++ Slack Group](http://cpplang.diegostamigni.com/)
