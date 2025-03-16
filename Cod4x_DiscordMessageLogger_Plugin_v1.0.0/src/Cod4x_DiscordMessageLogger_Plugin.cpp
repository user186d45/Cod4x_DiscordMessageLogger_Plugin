#include "../includes/MessageLogger.hpp"
#include "../includes/DiscordLogger.hpp"
#include "../includes/LoggerHandler.hpp"
#include "../libs/pinc.h"
#include "version.h"

#include <memory>
#include <string>
#include <string.h>
#include <pthread.h>
#include <stddef.h>

pthread_mutex_t mutex;

std::shared_ptr<IMessageLogger> iMessageLogger = nullptr;
std::shared_ptr<LoggerHandler> handler = nullptr;

PCL int OnInit() {
	const std::string token = "TOKEN";
	const uint64_t channelId = 00000;

	handler = std::make_shared<LoggerHandler>();
	if(handler == nullptr) {
		Plugin_PrintError("Discord Logger Plugin: Error occurred on allocating LoggerHandler object on heap.\n");
		return 1;
	}

	Plugin_Printf("Discord Message Logger Plugin: NOTICE: handler is pointing to %p\n", (void*)handler.get());

	std::string modifyToken = token;
	iMessageLogger = handler->handler(
			modifyToken,
			channelId
	);

	if(iMessageLogger != nullptr) {
		Plugin_Printf("Discord Message Logger Plugin: NOTICE: iMessageLogger is pointing to address: %p\n", (void*)iMessageLogger.get());

	} else {
		Plugin_Printf("Discord Message Logger Plugin: NOTICE: iMessageLogger is not pointing to anything.\n");

	}

	return 0;

}

PCL void OnMessageSent(char* message, int slot, qboolean* show, int mode) {
	pthread_mutex_lock(&mutex);

	char* playerName = Plugin_GetPlayerName(slot);
	size_t len = (strlen(message) + strlen(playerName) + 5) * sizeof(char);

	char* result = (char*)malloc(len);
	snprintf(result, len, "%s: %s\n\n", playerName, message);

	iMessageLogger->log(result);

	free(result);

	pthread_mutex_unlock(&mutex);

}

PCL void OnInfoRequest(pluginInfo_t *info){

    info->handlerVersion.major = PLUGIN_HANDLER_VERSION_MAJOR;
    info->handlerVersion.minor = PLUGIN_HANDLER_VERSION_MINOR;

    info->pluginVersion.major = Cod4x_DiscordMessageLogger_Plugin_VERSION_MAJOR;
    info->pluginVersion.minor = Cod4x_DiscordMessageLogger_Plugin_VERSION_MINOR;
    strncpy(info->fullName,"Cod4x Discord Logger Plugin",sizeof(info->fullName));
    strncpy(info->shortDescription,"Discord Message Logger Plugin for Cod4x.",sizeof(info->shortDescription));
    strncpy(info->longDescription,"This plugin is used to send server chat messages to a discord channel. Coded my LM40 ( DevilHunter )",sizeof(info->longDescription));
}

PCL void OnExitLevel() {
	handler.reset();
	iMessageLogger.reset();

}

PCL void OnTerminate() {
	handler.reset();
	iMessageLogger.reset();

}


