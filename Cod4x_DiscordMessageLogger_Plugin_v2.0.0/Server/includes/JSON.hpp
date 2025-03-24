#pragma once

#ifndef JSON_HPP
#define JSON_HPP

#include <stdio.h>
#include <memory>
#include <cjson/cJSON.h>

class IJson {
public:
	virtual void readDataToStruct() = 0;

	virtual ~IJson() = default;

};

class Json : public IJson {
public:
	Json();

	struct discordData {
			const char* botToken = nullptr;
			const uint64_t* channelID = nullptr;
	};


	void readDataToStruct() override;

	static struct std::shared_ptr<Json::discordData> dData;

private:
	FILE*          jsonCfgFile = nullptr;
	char*          rawJson = nullptr;
	size_t         configLen = 0;
	size_t         readLen = 0;
	const char*    ptrErr = nullptr;
	ptrdiff_t      errOffset = 0;
	size_t         startOffset = 0;
	size_t         offsetLen = 0;

	cJSON*      jsonCfg = nullptr;
	cJSON*      discordInfo = nullptr;
	cJSON*      botToken = nullptr;
	cJSON*      channelId = nullptr;

};

#endif
