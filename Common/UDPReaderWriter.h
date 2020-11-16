/*
 *   Copyright (C) 2009-2011,2013,2018,2020 by Jonathan Naylor G4KLX
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

#ifndef UDPReaderWriter_H
#define UDPReaderWriter_H

#include <wx/wx.h>

#if !defined(__WINDOWS__)
#include <netdb.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#endif

#if !defined(UDP_SOCKET_MAX)
#define UDP_SOCKET_MAX	1
#endif

enum IPMATCHTYPE {
	IMT_ADDRESS_AND_PORT,
	IMT_ADDRESS_ONLY
};

class CUDPReaderWriter {
public:
	CUDPReaderWriter(const wxString& address, unsigned int port);
	CUDPReaderWriter(unsigned int port);
	CUDPReaderWriter();
	~CUDPReaderWriter();

	static int lookup(const wxString& hostName, unsigned int port, sockaddr_storage& address, unsigned int& address_length);
	static int lookup(const wxString& hostName, unsigned int port, sockaddr_storage& address, unsigned int& address_length, struct addrinfo& hints);

	static bool match(const sockaddr_storage& addr1, const sockaddr_storage& addr2, IPMATCHTYPE type = IMT_ADDRESS_AND_PORT);

	bool open(const sockaddr_storage& addr);
	bool open(int family);
	bool open();

	int  read(unsigned char* buffer, unsigned int length, sockaddr_storage& addr, unsigned int& addrLen);
	bool write(const unsigned char* buffer, unsigned int length, const sockaddr_storage& addr, unsigned int addrLen);

	void close();

	unsigned int getPort() const;

private:
	wxString         m_address;
	unsigned short   m_port;
	sockaddr_storage m_addr;
	unsigned int     m_addrLen;
	int              m_fd;
};

#endif
