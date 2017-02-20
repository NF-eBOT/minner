### !!! UNDER CONSTRUCTION !!!

# NF-eBOT - Scrapers
Web scraper responsible to extract relevant news in Brazilian government portals.

## To build
#### First create ```src/config.h``` with ```src/config.h.dist``` template and run:
`g++ -std=c++14 src/main.cpp include/*.cpp include/parsers/*.cpp -w -v -lcurl -o build/scrapers_cpp.out`

## or
`./bin/gcc_run.sh`

## Folder Structure

* `bin`: executables to help any think
* `build`: where builded executable is saved
* `doc`: configuration file
* `include`: local headers
* `include/parsers`: logic of portals/sites scraped
* `lib`: vendor libs
* `spike`: files to test technologies or ideas
* `src`: main file
