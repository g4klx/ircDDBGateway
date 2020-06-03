/*
 *   Copyright (C) 2010,2011,2012,2018,2020 by Jonathan Naylor G4KLX
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

#include "UDPReaderWriter.h"
#include "APRSCollector.h"
#include "DStarDefines.h"
#include "HeaderData.h"
#include "AMBEData.h"
#include "Timer.h"
#include "Defs.h"

#if !defined(_WIN32) && !defined(_WIN64)
#include <gps.h>
#endif

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
	CAPRSWriter(const wxString& address, unsigned int port, const wxString& gateway);
	~CAPRSWriter();

	bool open();

	void setPortFixed(const wxString& callsign, const wxString& band, double frequency, double offset, double range, double latitude, double longitude, double agl);

	void setPortGPSD(const wxString& callsign, const wxString& band, double frequency, double offset, double range, const wxString& address, const wxString& port);

	void writeHeader(const wxString& callsign, const CHeaderData& header);

	void writeData(const wxString& callsign, const CAMBEData& data);

	void clock(unsigned int ms);

	void close();

private:
	CTimer             m_idTimer;
	wxString           m_gateway;
	CEntry_t           m_array;
	in_addr            m_aprsAddress;
	unsigned int       m_aprsPort;
	CUDPReaderWriter   m_aprsSocket;
#if !defined(_WIN32) && !defined(_WIN64)
	bool               m_gpsdEnabled;
	wxString           m_gpsdAddress;
	wxString           m_gpsdPort;
	struct gps_data_t  m_gpsdData;
#endif

	void sendIdFramesFixed();
	void sendIdFramesMobile();
};

#endif

