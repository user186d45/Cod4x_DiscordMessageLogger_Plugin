#pragma once

#ifndef LOGGER_HANDLER_HPP
#define LOGGER_HANDLER_HPP

#include "MessageLogger.hpp"
#include "DiscordLogger.hpp"
#include <memory>
#include <string>
#include <thread>

class LoggerHandler {
public:
	std::shared_ptr<IMessageLogger> handler(std::string token, const uint64_t cId);

	virtual ~LoggerHandler();

private:
	std::shared_ptr<DiscordLogger> discordLogger = nullptr;
	std::thread discordThread;

};

#endif
