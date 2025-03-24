#pragma once

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "../includes/Signal.hpp"

#include <signal.h>
#include <mqueue.h>
#include <cstddef>
#include <memory>

#define COD4X_QUEUE_NAME "/libCod4xDiscordMessageQ"
#define MAX_SIZE 1024

class IQueue {
public:
	virtual const char* receiveQueue() = 0;

	virtual ~IQueue() = default;

};

class Queue : public IQueue {
public:
	Queue();

	const char* receiveQueue() override;

	~Queue();

private:
	mqd_t                           discordMessageQueue;
	struct mq_attr                  dMessageQueueAttr;
	struct timespec                 dur500000000;
	char*                           buffer = nullptr;
	ssize_t                         msgLen = 0;
	size_t                          bufferSize = 0;

};

#endif
