### !!! UNDER CONSTRUCTION !!!

# NF-eBOT - Scrapers
Web scraper responsible to extract relevant news in Brazilian government portals.

## To build
#### First create ```src/config.h``` with ```src/config.h.dist``` template and run:
`g++ -std=c++14 -stdlib=libc++ src/main.cpp includes/*.cpp includes/parsers/*.cpp -w -lcurl -o build/scrapers_cpp.out`

## or
`./bin/gcc_run.sh`

## Folder Structure

* `bin`: executables to help any think
* `buld`: where builded executable is saved
* `cmake`: cmake files (under construction)
* `includes`: local and vendor libs
* `includes/parsers`: logic of portals/sites scraped
* `src`: main and configuration file
