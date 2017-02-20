# NF-eBOT - Scrapers
Web scraper responsible to extract relevant news in Brazilian government portals.

## To build
#### First create ```doc/config.h``` with ```doc/config.h.dist``` template and run:
`g++ -std=c++14 src/main.cpp include/*.cpp include/parsers/*.cpp -w -v -lcurl -o build/scrapers_cpp.out`

#### or
`./scripts/gcc_build.sh`

## Folder Structure

* `build`: where builded executable is saved
* `doc`: configuration file
* `include`: local headers
* `include/parsers`: logic of portals/sites scraped
* `lib`: vendor libs
* `scripts`: scripts to help build and install
* `spike`: files to test technologies or ideas
* `src`: main file
