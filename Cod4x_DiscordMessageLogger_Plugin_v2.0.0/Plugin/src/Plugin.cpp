#include "../libs/pinc.h"
#include "../includes/Queue.hpp"
#include "../../build/default/Plugin/version.h"

#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t mutex;
IQueue* iQueue = nullptr;

PCL int OnInit() {
	pthread_mutex_init(&mutex, NULL);

	iQueue = new Queue();

	return 0;
}

PCL void OnMessageSent(char* message, int slot, qboolean *show, int mode) {
	pthread_mutex_lock(&mutex);

	char* playerName = Plugin_GetPlayerName(slot);
	size_t len = (strlen(message) + strlen(playerName) + 5) * sizeof(char);

	char* result = (char*)malloc(len);
	snprintf(result, len, "%s: %s\n\n", playerName, message);

	iQueue->sendQueue(result);

	free(result);

	pthread_mutex_unlock(&mutex);

}

PCL void OnTerminate() {
	pthread_mutex_destroy(&mutex);

	delete iQueue;

}

PCL void OnInfoRequest(pluginInfo_t *info){

    info->handlerVersion.major = PLUGIN_HANDLER_VERSION_MAJOR;
    info->handlerVersion.minor = PLUGIN_HANDLER_VERSION_MINOR;

    info->pluginVersion.major = Cod4x_DiscordMessageLogger_VERSION_MAJOR;
    info->pluginVersion.minor = Cod4x_DiscordMessageLogger_VERSION_MINOR;
    strncpy(info->fullName,"Cod4x Discord Logger Plugin",sizeof(info->fullName));
    strncpy(info->shortDescription,"Discord Message Logger Plugin for Cod4x.",sizeof(info->shortDescription));
    strncpy(info->longDescription,"This plugin is used to send server chat messages to a discord channel. Coded my LM40 ( DevilHunter )",sizeof(info->longDescription));
}


