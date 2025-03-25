#pragma once

#ifndef THREAD_HPP
#define THREAD_HPP

#include <pthread.h>

class IThread {
public:
	virtual void setThreadFunc(void* (*threadFunc) (void*)) = 0;
	virtual void run(void* arg) = 0;
	virtual void stop() = 0;

	virtual ~IThread() = default;

protected:
	void* (*tFunc) (void*);

};

class Thread : public IThread {
public:
	void setThreadFunc(void* (*threadFunc) (void*)) override;
	void run(void* arg) override;
	void stop() override;

private:
	pthread_t thread;
	int rValue = 0;

};

#endif
