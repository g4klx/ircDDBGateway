/*
 *   Copyright (C) 2002,2003,2009,2011,2012,2019 by Jonathan Naylor G4KLX
 *   Copyright (C) 2020 by Adam Kolakowski SQ7LRX
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

#include "ConsoleLogger.h"

const char CConsoleLogger::S_LEVELS[] = "FEWMMIDTPU";

CConsoleLogger::CConsoleLogger() :
wxLog(),
m_stdout(new wxMessageOutputStderr(stdout)),
m_stderr(new wxMessageOutputStderr(stderr))
{
}

CConsoleLogger::~CConsoleLogger()
{
}

void CConsoleLogger::DoLogRecord(wxLogLevel level, const wxString& msg, const wxLogRecordInfo& info)
{
	if (level > 9)
		level = 9;

	if (level <= wxLOG_Error) {
		m_stderr->Printf(wxT("%c: %s\n"), CConsoleLogger::S_LEVELS[level], msg.c_str());
	} else {
		m_stdout->Printf(wxT("%c: %s\n"), CConsoleLogger::S_LEVELS[level], msg.c_str());
	}

	if (level == wxLOG_FatalError)
		::abort();
}
