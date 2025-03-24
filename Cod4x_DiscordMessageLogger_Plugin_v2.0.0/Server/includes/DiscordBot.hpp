#pragma once

#ifndef DISCORD_BOT_HPP
#define DISCORD_BOT_HPP

#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <dpp/dpp.h>

class IDiscordBot {
public:
	virtual void* run(void* arg) = 0;
	virtual void log(const char* msg) = 0;
	virtual void stop() = 0;

	virtual ~IDiscordBot() = default;

};

class DiscordBot : public IDiscordBot {
public:
	DiscordBot(const char* token, uint64_t channelId) : bot(token), cId(channelId) {}

	void* run(void* arg) override;
	void log(const char* msg) override;
	void stop() override;

private:
	dpp::cluster           bot;
	dpp::snowflake         cId;

};

#endif
