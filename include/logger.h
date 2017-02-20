#pragma once

#include <string>
#include <iostream>

#include "../lib/colormod.h"

#include "slack.h"

namespace scraper{

	class Logger{

	public:

		Logger();
		~Logger();

		void info(std::string message, bool slack_send);
		void debug(std::string message, bool slack_send);
		void warning(std::string message, bool slack_send);
		void error(std::string message, bool slack_send);

	};

}