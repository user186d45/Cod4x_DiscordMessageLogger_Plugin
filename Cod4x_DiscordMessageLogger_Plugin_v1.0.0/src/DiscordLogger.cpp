#include "../includes/DiscordLogger.hpp"
#include "../libs/pinc.h"

#include <dpp/dpp.h>

void DiscordLogger::botMainThread() {
	bot.on_ready(
		[this](const dpp::ready_t& event) {
			Plugin_Printf("Discord Logger Plugin: NOTICE: The bot has initiated successfully.\n");

	});

	bot.start(dpp::st_wait);
	return;

}

void DiscordLogger::log(const char* msg) {
	bot.message_create(
			dpp::message()
			.set_channel_id(channelId)
			.set_content(msg)
	);

}

DiscordLogger::~DiscordLogger() {
	bot.~cluster();

}
