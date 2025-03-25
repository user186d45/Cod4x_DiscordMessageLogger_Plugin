#pragma once

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <signal.h>
#include <mqueue.h>
#include <cstddef>
#include <memory>

#define COD4X_QUEUE_NAME "/libCod4xDiscordMessageQ"
#define MAX_SIZE 1024

class IQueue {
public:
	virtual void sendQueue(const char* msg) = 0;

	virtual ~IQueue() = default;

};

class Queue : public IQueue {
public:
	Queue();

	void sendQueue(const char* msg) override;

	~Queue();

private:
	mqd_t                    discordMessageQueue;
	struct mq_attr           dMessageQueueAttr;
	size_t                   bufferSize = 0;
	int                      rValue = 0;

};

#endif
