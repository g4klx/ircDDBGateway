/*
 *   Copyright (C) 2010,2012,2013,2020 by Jonathan Naylor G4KLX
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

#ifndef	PollData_H
#define	PollData_H

#include "Defs.h"

#include <wx/wx.h>

#if defined(__WINDOWS__)
#include "Inaddr.h"
#else
#include <netinet/in.h>
#endif

class CPollData {
public:
	CPollData(const wxString& data1, const wxString& data2, DIRECTION direction, const sockaddr_storage& yourAddr, unsigned int yourAddrLen, unsigned int myPort = 0U);
	CPollData(const wxString& data, const sockaddr_storage& yourAddr, unsigned int yourAddrLen, unsigned int myPort = 0U);
	CPollData(const sockaddr_storage& yourAddr, unsigned int yourAddrLen, unsigned int myPort = 0U);
	CPollData();
	~CPollData();

	bool setDExtraData(const unsigned char* data, unsigned int length, const sockaddr_storage& yourAddr, unsigned int yourAddrLen, unsigned int myPort);
	bool setDPlusData(const unsigned char* data, unsigned int length, const sockaddr_storage& yourAddr, unsigned int yourAddrLen, unsigned int myPort);
	bool setDCSData(const unsigned char* data, unsigned int length, const sockaddr_storage& yourAddr, unsigned int yourAddrLen, unsigned int myPort);
	bool setCCSData(const unsigned char* data, unsigned int length, const sockaddr_storage& yourAddr, unsigned int yourAddrLen, unsigned int myPort);

	unsigned int getDExtraData(unsigned char* data, unsigned int length) const;
	unsigned int getDPlusData(unsigned char* data, unsigned int length) const;
	unsigned int getDCSData(unsigned char* data, unsigned int length) const;
	unsigned int getCCSData(unsigned char* data, unsigned int length) const;

	wxString     getData1() const;
	void         setData1(const wxString& data);

	wxString     getData2() const;
	void         setData2(const wxString& data);

	bool         isDongle() const;

	sockaddr_storage getYourAddr() const;
	unsigned int     getYourAddrLen() const;
	unsigned int     getMyPort() const;

	DIRECTION    getDirection() const;
	unsigned int getLength() const;

private:
	wxString         m_data1;
	wxString         m_data2;
	DIRECTION        m_direction;
	bool             m_dongle;
	unsigned int     m_length;
	sockaddr_storage m_yourAddr;
	unsigned int     m_yourAddrLen;
	unsigned int     m_myPort;
};

#endif
