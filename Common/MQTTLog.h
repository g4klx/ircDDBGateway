/*
 *   Copyright (C) 2015,2016,2020,2022,2023,2025 by Jonathan Naylor G4KLX
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

#if !defined(MQTTLOG_H)
#define	MQTTLOG_H

#include "MQTTConnection.h"

#include <string>

#include <nlohmann/json.hpp>

extern void MQTTLogInitialise();
extern void MQTTLogFinalise();

extern void WriteJSON(const std::string& topLevel, nlohmann::json& json);

extern void WriteJSONStatus(const std::string& status);
extern void WriteJSONLinking(const std::string& repeater, const std::string& reason, const std::string& protocol, const std::string& reflector);
extern void WriteJSONUnlinked(const std::string& repeater, const std::string& reason);
extern void WriteJSONFailed(const std::string& repeater);
extern void WriteJSONRelinking(const std::string& repeater, const std::string& protocol, const std::string& reflector);

#endif
