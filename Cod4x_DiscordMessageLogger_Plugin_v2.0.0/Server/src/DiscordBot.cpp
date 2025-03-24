#include "../includes/DiscordBot.hpp"

#include <stdio.h>
#include <memory>

void* DiscordBot::run(void* arg) {
	printf("NOTICE: Bot initializer called.\n");

	bot.on_ready([this](const dpp::ready_t& event) {
		printf("NOTICE: Bot is ready.\n");
	});

	printf("NOTICE: Starting log poll...\n");
	bot.start(dpp::st_wait);

	printf("NOTICE: Bot stopped.\n");

	return nullptr;

}

void DiscordBot::log(const char* msg) {
	dpp::message message2send(cId, msg);

	bot.message_create(message2send);

}

void DiscordBot::stop() {
	printf("NOTICE: Bot is shutting down...\n");
	bot.shutdown();

}
