#pragma once

#ifndef DISCORD_LOGGER_HPP
#define DISCORD_LOGGER_HPP

#include "MessageLogger.hpp"

#include <dpp/dpp.h>
#include <string>

class DiscordLogger : public IMessageLogger {
public:
	DiscordLogger(std::string token, const uint64_t cId) : bot(token), channelId(cId) {}
	virtual ~DiscordLogger();

	void botMainThread();

	void log(const char* msg) override;

private:
	dpp::cluster bot;
	const uint64_t channelId;

};

#endif
