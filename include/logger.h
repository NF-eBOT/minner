#pragma once

#include <string>

#include "colormod.h"

#include "slack.cpp"

namespace scraper{

	class Logger{

	public:

		Logger();
		~Logger();

		void info(const std::string message, const bool slack_send);
		void debug(const std::string message, const bool slack_send);
		void warning(const std::string message, const bool slack_send);
		void error(const std::string message, const bool slack_send);

	};

}