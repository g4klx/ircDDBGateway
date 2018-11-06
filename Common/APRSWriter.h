/*
 *   Copyright (C) 2010,2011,2012,2018 by Jonathan Naylor G4KLX
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

#ifndef	APRSWriter_H
#define	APRSWriter_H

#include "APRSWriterThread.h"
#include "UDPReaderWriter.h"
#include "APRSCollector.h"
#include "DStarDefines.h"
#include "HeaderData.h"
#include "AMBEData.h"
#include "Timer.h"
#include "Defs.h"

#include <wx/wx.h>

class CAPRSEntry {
public:
	CAPRSEntry(const wxString& callsign, const wxString& band, double frequency, double offset, double range, double latitude, double longitude, double agl);
	~CAPRSEntry();

	wxString getCallsign() const;
	wxString getBand() const;
	double   getFrequency() const;
	double   getOffset() const;
	double   getRange() const;
	double   getLatitude() const;
	double   getLongitude() const;
	double   getAGL() const;
	CAPRSCollector* getCollector() const;

	// Transmission timer
	void reset();
	void clock(unsigned int ms);
	bool isOK();

private:
	wxString        m_callsign;
	wxString        m_band;
	double          m_frequency;
	double          m_offset;
	double          m_range;
	double          m_latitude;
	double          m_longitude;
	double          m_agl;
	CTimer          m_timer;
	bool            m_first;
	CAPRSCollector* m_collector;
};

WX_DECLARE_STRING_HASH_MAP(CAPRSEntry*, CEntry_t);

class CAPRSWriter {
public:
	CAPRSWriter(const wxString& hostname, unsigned int port, const wxString& gateway, const wxString& password, const wxString& address);
	~CAPRSWriter();

	bool open();

	void setFixedPort(const wxString& callsign, const wxString& band, double frequency, double offset, double range, double latitude, double longitude, double agl);

	void setMobilePort(const wxString& callsign, const wxString& band, double frequency, double offset, double range, const wxString& address, unsigned int port);

	void writeHeader(const wxString& callsign, const CHeaderData& header);

	void writeData(const wxString& callsign, const CAMBEData& data);

	bool isConnected() const;

	void clock(unsigned int ms);

	void close();

private:
	CAPRSWriterThread* m_thread;
	CTimer             m_idTimer;
	wxString           m_gateway;
	CEntry_t           m_array;
	in_addr            m_address;
	unsigned int       m_port;
	CUDPReaderWriter*  m_socket;

	bool pollGPS();
	void sendIdFramesFixed();
	void sendIdFramesMobile();
};

#endif

