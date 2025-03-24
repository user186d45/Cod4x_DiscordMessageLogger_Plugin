#pragma once

#ifndef SIGNAL_HANDLER_HPP
#define SIGNAL_HANDLER_HPP

#include <memory>
#include <signal.h>
#include <errno.h>
#include <cstddef>

class ISignal {
public:
	virtual void regSig() = 0;

	virtual ~ISignal() = default;

};

class SigInt : public ISignal {
public:
	SigInt() : qRun(nullptr) {}
	SigInt(bool* queueRun) : qRun(queueRun) {}

	void regSig() override;

	static std::shared_ptr<SigInt> instance;

private:
	bool*                        qRun;
	struct sigaction             sigIntStruct;
	static void                  sCallback(int sigNum);
	int                          rValue = 0;

};

#endif
