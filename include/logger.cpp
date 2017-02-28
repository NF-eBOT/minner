#include "logger.h"

const Color::Modifier red(Color::FG_RED);
const Color::Modifier green(Color::FG_GREEN);
const Color::Modifier blue(Color::FG_BLUE);
const Color::Modifier yellow(Color::FG_YELLOW);
const Color::Modifier def(Color::FG_DEFAULT);

scraper::Logger::Logger(){}
scraper::Logger::~Logger(){}

void scraper::Logger::info(const std::string message, const std::string parser_name, const bool slack_send){
	std::cout << green << parser_name << " - " << message << def << std::endl;
	if(slack_send) scraper::Slack::send(parser_name + " - " + message);
}

void scraper::Logger::debug(const std::string message, const std::string parser_name, const bool slack_send){
	std::cout << blue << parser_name << " - " << message << def << std::endl;
	if(slack_send) scraper::Slack::send(parser_name + " - " + message);
}

void scraper::Logger::warning(const std::string message, const std::string parser_name, const bool slack_send){
	std::cout << yellow << parser_name << " - " << message << def << std::endl;
	if(slack_send) scraper::Slack::send(parser_name + " - " + message);
}

void scraper::Logger::error(const std::string message, const std::string parser_name, const bool slack_send){
	std::cout << red << parser_name << " - " << message << def << std::endl;
	if(slack_send) scraper::Slack::send(parser_name + " - " + message);
}