#include "../includes/JSON.hpp"
#include "../includes/DiscordBot.hpp"
#include "../includes/Queue.hpp"
#include "../includes/Signal.hpp"
#include "../includes/Thread.hpp"

#include <cstddef>
#include <memory>

int main(int argc, char** argv) {

	std::unique_ptr<IJson> iJson = nullptr;

	std::shared_ptr<Json::discordData> discordDStruct = std::make_shared<Json::discordData>();

	std::unique_ptr<Json> json = std::make_unique<Json>();

	json->dData = discordDStruct;

	iJson = std::move(json);

	iJson->readDataToStruct();

	printf("NOTICE: Token is: %s\n", discordDStruct->botToken);
	printf("NOTICE: Channel ID is: %llu\n", discordDStruct->channelID);

 	bool qRun = 1;

	std::unique_ptr<IDiscordBot> iDiscordBot = std::make_unique<DiscordBot>(
			discordDStruct->botToken,
			discordDStruct->channelID
	);

	std::unique_ptr<IQueue> iQueue = std::make_unique<Queue>();

	std::shared_ptr<SigInt> Signal = std::make_shared<SigInt>(&qRun);
	Signal->instance = Signal;

	std::shared_ptr<ISignal> iSignal = std::move(Signal);

	std::unique_ptr<IThread> iThread = std::make_unique<Thread>();

	iSignal->regSig();

	iThread->setThreadFunc([](void* arg) -> void* {
		IDiscordBot* bot = static_cast<IDiscordBot*>(arg);
		return bot->run(nullptr);

	});

	iThread->run(iDiscordBot.get());

	const char* buffer;
	while(qRun) {
		buffer = iQueue->receiveQueue();
		if(buffer) {
			iDiscordBot->log(buffer);

		}

	}

	iDiscordBot->stop();
	iThread->stop();

	return 0;
}
