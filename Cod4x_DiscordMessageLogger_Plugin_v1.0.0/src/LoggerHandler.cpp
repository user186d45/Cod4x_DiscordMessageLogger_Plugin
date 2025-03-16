#include "../includes/LoggerHandler.hpp"
#include "../includes/MessageLogger.hpp"
#include "../includes/DiscordLogger.hpp"
#include "../libs/pinc.h"

#include <string>
#include <memory>
#include <thread>


std::shared_ptr<IMessageLogger> LoggerHandler::handler(std::string token, const uint64_t cId) {
	discordLogger = std::make_shared<DiscordLogger>(token, cId);
	if(discordLogger == nullptr) {
		Plugin_PrintError("Discord Logger Plugin: Error occurred on allocating DiscordLogger object on heap.\n");
		return nullptr;
	}

	Plugin_Printf("Discord Logger Plugin: NOTICE: handler created DiscordLogger on heap.\n");

	discordThread = std::thread([this]() mutable {
		discordLogger->botMainThread();

	});
	discordThread.detach();

	return discordLogger;

}


LoggerHandler::~LoggerHandler() {
	if(!discordThread.joinable()) {
		Plugin_PrintError("Discord Logger Plugin: discordThread is not joinable ( the process is not running ).");
		return;
	}

	Plugin_Printf("Discord Logger Plugin: NOTICE: Handler object's destructor has been called, bot thread has been canceled.\n");

}
