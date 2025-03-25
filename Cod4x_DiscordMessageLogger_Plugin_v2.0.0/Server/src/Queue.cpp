#include "../includes/Queue.hpp"
#include "../includes/Signal.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <errno.h>
#include <string.h>
#include <memory>

Queue::Queue() {
	memset(&dMessageQueueAttr, 0, sizeof(dMessageQueueAttr));
	dMessageQueueAttr.mq_flags = 0;
	dMessageQueueAttr.mq_maxmsg = 10;
	dMessageQueueAttr.mq_msgsize = MAX_SIZE;
	dMessageQueueAttr.mq_curmsgs = 0;

	mq_unlink(COD4X_QUEUE_NAME);
	discordMessageQueue = mq_open(COD4X_QUEUE_NAME, O_CREAT | O_RDONLY | O_NONBLOCK, 0666, &dMessageQueueAttr);
	if(discordMessageQueue == (mqd_t)-1) {
		fprintf(stderr, "Error occurred on opening query: %s\n", strerror(errno));
		exit(EXIT_FAILURE);

	}

	struct mq_attr attr;
	memset(&attr, 0, sizeof(attr));
	mq_getattr(discordMessageQueue, &attr);
	printf("mq_msgsize after open: %ld\n", attr.mq_msgsize);

	bufferSize = MAX_SIZE * sizeof(char);
	buffer = (char*)malloc(bufferSize);
	memset(buffer, 0, bufferSize);

	dur500000000 = {0, 500000000};

}

const char* Queue::receiveQueue() {
	printf("NOTICE: Queue poll started, receiving messages...\n");

	msgLen = mq_receive(discordMessageQueue, buffer, bufferSize, 0);
	if(msgLen < 0) {
		if(errno == EAGAIN) {
			printf("NOTICE: No messages available...\n");
			nanosleep(&dur500000000, NULL);
			return nullptr;

		} else {
			fprintf(stderr, "Error occurred on receiving message: %s\n", strerror(errno));
			exit(EXIT_FAILURE);

		}

	}

	buffer[msgLen] = '\0';

	printf("NOTICE: Returning message: %s\n", buffer);

	return buffer;
}

Queue::~Queue() {
	free(buffer);
	mq_close(discordMessageQueue);

}
