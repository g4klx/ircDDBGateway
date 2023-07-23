/*
 *   Copyright (C) 2015,2016,2020,2022,2023 by Jonathan Naylor G4KLX
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "MQTTLog.h"
#include "Utils.h"

#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <ctime>
#include <cassert>
#include <cstring>

CMQTTConnection* m_mqtt = NULL;

void MQTTLogInitialise()
{
}

void MQTTLogFinalise()
{
	if (m_mqtt != NULL) {
		m_mqtt->close();
		delete m_mqtt;
		m_mqtt = NULL;
	}
}

void WriteJSON(const std::string& topLevel, nlohmann::json& json)
{
	if (m_mqtt != NULL) {
		nlohmann::json top;

		top[topLevel] = json;

		m_mqtt->publish("json", top.dump());
	}
}

void WriteJSONLinking(const std::string& protocol, const std::string& direction, const std::string& reason, const wxString& local, const wxString& remote)
{
	nlohmann::json json;

	json["timestamp"] = CUtils::createTimestamp();
	json["action"]    = "linking";
	json["reason"]    = reason;
	json["remote"]    = remote.char_str();
	json["local"]     = local.char_str();
	json["protocol"]  = protocol;
	json["direction"] = direction;

	WriteJSON("link", json);
}

void WriteJSONUnlinked(const std::string& protocol, const std::string& reason, const wxString& local, const wxString& remote)
{
	nlohmann::json json;

	json["timestamp"] = CUtils::createTimestamp();
	json["action"]    = "unlinked";
	json["reason"]    = reason;
	json["remote"]    = remote.char_str();
	json["local"]     = local.char_str();
	json["protocol"]  = protocol;

	WriteJSON("link", json);
}

void WriteJSONRelinking(const std::string& protocol, const wxString& local, const wxString& remote)
{
	nlohmann::json json;

	json["timestamp"] = CUtils::createTimestamp();
	json["action"]    = "relinking";
	json["remote"]    = remote.char_str();
	json["local"]     = local.char_str();
	json["protocol"]  = protocol;

	WriteJSON("link", json);
}

