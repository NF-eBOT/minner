### !!! UNDER CONSTRUCTION !!!

# NF-eBOT - Scrapers
Microservice responsible to extract relevant news in Brazilian government portals.

## To build
`g++ -std=c++11 -stdlib=libc++ src/main.cpp includes/*.cpp -w -lcurl -o build/scrapers_cpp.out`

## or
`./bin/gcc_run.sh`

## Folder Structure

* `bin`: executables to help any think
* `buld`: where builded executable is saved
* `cmake`: cmake files (under construction)
* `includes`: local and vendor libs
* `src`: main file
