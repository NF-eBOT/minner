#include "logger.h"

const Color::Modifier red(Color::FG_RED);
const Color::Modifier green(Color::FG_GREEN);
const Color::Modifier blue(Color::FG_BLUE);
const Color::Modifier yellow(Color::FG_YELLOW);
const Color::Modifier def(Color::FG_DEFAULT);

scraper::Logger::Logger(){}
scraper::Logger::~Logger(){}

void scraper::Logger::info(std::string message, bool slack_send){
	std::cout << green << message << def << std::endl;
	if(slack_send) scraper::Slack::send(message);
}

void scraper::Logger::debug(std::string message, bool slack_send){
	std::cout << blue << message << def << std::endl;
	if(slack_send) scraper::Slack::send(message);
}

void scraper::Logger::warning(std::string message, bool slack_send){
	std::cout << yellow << message << def << std::endl;
	if(slack_send) scraper::Slack::send(message);
}

void scraper::Logger::error(std::string message, bool slack_send){
	std::cout << red << message << def << std::endl;
	if(slack_send) scraper::Slack::send(message);
}