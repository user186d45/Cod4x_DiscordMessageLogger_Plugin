#pragma once

#ifndef MESSAGE_LOGGER_HPP
#define MESSAGE_LOGGER_HPP

class IMessageLogger {
public:
	virtual void log(const char* msg) = 0;

	virtual ~IMessageLogger() = default;
};

#endif
