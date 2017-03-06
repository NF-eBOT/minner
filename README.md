# Minner - Web Scraper
Minner is an easy way to make any web scraper for data-mining. 
Builded in C++14, with only one shared library, libcurl. With log messages through slack and terminal.

In original version (some parts are still), this scraper is only a service for NF-eBOT, but now, my objective is to refactor this project to make more people use this.

Make fork and refactor for your situation.

<br>

# Compile and Run

### Production:
#### 1. Dependencies
* gcc >= 3.5.1
* [libcurl](https://curl.haxx.se/libcurl) - install via OS package manager (ex: apt install libcurl)

#### 2. Build configuration file
* Create ```doc/config.h``` with ```doc/config.h.dist``` template.

#### 3. Compile:
* `cmake . && make`

#### 4. Run:
* `./minner --SCRAPER_KEY`

<br>

### With Docker:
`(best choice for dev and good choice for production)`
#### 1. Dependencies
* Install [Docker](https://www.docker.com/community-edition#/download)

#### 2. Build configuration file
* Create ```doc/config.h``` with ```doc/config.h.dist``` template.

#### 3. Build container and compile minner (first time, and every time you change config.h)
* `docker build -t nfebot/minner .`

#### # 4. Run
* `docker run -ti --rm nfebot/minner --SCRAPER_KEY`

<br>

### With Vagrant:
`(best choice for Windows and dev)`
#### 1. Dependencies
* Install [Vagrant](https://www.vagrantup.com/downloads.html)

#### 2. Create vm and enter
* `vagrant up && vagrant ssh`

#### 3. Build configuration file
* Create ```doc/config.h``` with ```doc/config.h.dist``` template.

#### # 4. Compile
* `cd /data && cmake . && make`

#### # 5. Run:
* `./minner --SCRAPER_KEY`

<br>

## Available Scraper keys
`--nfe-notas-tecnicas` [nfe.fazenda.gov.br / Notas Técnicas](http://www.nfe.fazenda.gov.br/portal/listaConteudo.aspx?tipoConteudo=tW+YMyk/50s=)

`--nfe-avisos` [nfe.fazenda.gov.br / Avisos](http://www.nfe.fazenda.gov.br/portal/informe.aspx?ehCTG=false)

`--sped` [sped.rfb.gov.br / Destaques](http://sped.rfb.gov.br)

#### For create a new scraper key/parser, explore `app/include/parsers` source.

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
