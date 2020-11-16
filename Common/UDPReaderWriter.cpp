/*
 *   Copyright (C) 2006-2014,2018,2020 by Jonathan Naylor G4KLX
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

#include "UDPReaderWriter.h"

#if !defined(__WINDOWS__)
#include <cerrno>
#endif


CUDPReaderWriter::CUDPReaderWriter(const wxString& address, unsigned int port) :
m_address(address),
m_port(port),
m_addr(),
m_addrLen(0U),
m_fd(-1)
{
#if defined(__WINDOWS__)
	WSAData data;
	int wsaRet = ::WSAStartup(MAKEWORD(2, 2), &data);
	if (wsaRet != 0)
		wxLogError(wxT("Error from WSAStartup"));
#endif
}

CUDPReaderWriter::CUDPReaderWriter(unsigned int port) :
m_address(),
m_port(port),
m_addr(),
m_addrLen(0U),
m_fd(-1)
{
#if defined(__WINDOWS__)
	WSAData data;
	int wsaRet = ::WSAStartup(MAKEWORD(2, 2), &data);
	if (wsaRet != 0)
		wxLogError(wxT("Error from WSAStartup"));
#endif
}

CUDPReaderWriter::CUDPReaderWriter() :
m_address(),
m_port(0U),
m_addr(),
m_addrLen(0U),
m_fd(-1)
{
#if defined(__WINDOWS__)
	WSAData data;
	int wsaRet = ::WSAStartup(MAKEWORD(2, 2), &data);
	if (wsaRet != 0)
		wxLogError(wxT("Error from WSAStartup"));
#endif
}

CUDPReaderWriter::~CUDPReaderWriter()
{
#if defined(__WINDOWS__)
	::WSACleanup();
#endif
}

int CUDPReaderWriter::lookup(const wxString& hostname, unsigned int port, sockaddr_storage& addr, unsigned int& address_length)
{
	struct addrinfo hints;
	::memset(&hints, 0, sizeof(hints));

	return lookup(hostname, port, addr, address_length, hints);
}

int CUDPReaderWriter::lookup(const wxString& hostname, unsigned int port, sockaddr_storage& addr, unsigned int& address_length, struct addrinfo& hints)
{
	std::string portstr = std::to_string(port);
	struct addrinfo *res;

	/* port is always digits, no needs to lookup service */
	hints.ai_flags |= AI_NUMERICSERV;

	int err = ::getaddrinfo(hostname.IsEmpty() ? NULL : (const char*)hostname, portstr.c_str(), &hints, &res);
	if (err != 0) {
		sockaddr_in* paddr = (sockaddr_in*)&addr;
		::memset(paddr, 0x00U, address_length = sizeof(sockaddr_in));
		paddr->sin_family = AF_INET;
		paddr->sin_port = htons(port);
		paddr->sin_addr.s_addr = htonl(INADDR_NONE);
		wxLogError(wxT("Cannot find address for host %s"), hostname.c_str());
		return err;
	}

	::memcpy(&addr, res->ai_addr, address_length = res->ai_addrlen);

	::freeaddrinfo(res);

	return 0;
}

bool CUDPReaderWriter::match(const sockaddr_storage& addr1, const sockaddr_storage& addr2, IPMATCHTYPE type)
{
	if (addr1.ss_family != addr2.ss_family)
		return false;

	if (type == IMT_ADDRESS_AND_PORT) {
		switch (addr1.ss_family) {
		case AF_INET:
			struct sockaddr_in *in_1, *in_2;
			in_1 = (struct sockaddr_in*)&addr1;
			in_2 = (struct sockaddr_in*)&addr2;
			return (in_1->sin_addr.s_addr == in_2->sin_addr.s_addr) && (in_1->sin_port == in_2->sin_port);
		case AF_INET6:
			struct sockaddr_in6 *in6_1, *in6_2;
			in6_1 = (struct sockaddr_in6*)&addr1;
			in6_2 = (struct sockaddr_in6*)&addr2;
			return IN6_ARE_ADDR_EQUAL(&in6_1->sin6_addr, &in6_2->sin6_addr) && (in6_1->sin6_port == in6_2->sin6_port);
		default:
			return false;
		}
	} else if (type == IMT_ADDRESS_ONLY) {
		switch (addr1.ss_family) {
		case AF_INET:
			struct sockaddr_in *in_1, *in_2;
			in_1 = (struct sockaddr_in*)&addr1;
			in_2 = (struct sockaddr_in*)&addr2;
			return in_1->sin_addr.s_addr == in_2->sin_addr.s_addr;
		case AF_INET6:
			struct sockaddr_in6 *in6_1, *in6_2;
			in6_1 = (struct sockaddr_in6*)&addr1;
			in6_2 = (struct sockaddr_in6*)&addr2;
			return IN6_ARE_ADDR_EQUAL(&in6_1->sin6_addr, &in6_2->sin6_addr);
		default:
			return false;
		}
	} else {
		return false;
	}
}

bool CUDPReaderWriter::open()
{
	sockaddr_storage addr;
	unsigned int addrLen;
	
	lookup(m_address, m_port, addr, addrLen);

	return open(addr);
}

bool CUDPReaderWriter::open(const sockaddr_storage& addr)
{
	return open(addr.ss_family);
}

bool CUDPReaderWriter::open(int family)
{
	m_fd = ::socket(family, SOCK_DGRAM, 0);
	if (m_fd < 0) {
#if defined(__WINDOWS__)
		wxLogError(wxT("Cannot create the UDP socket, err: %lu"), ::GetLastError());
#else
		wxLogError(wxT("Cannot create the UDP socket, err: %d"), errno);
#endif
		return false;
	}

	if (m_port > 0U) {
		sockaddr_storage addr;
		unsigned int addrLen;

		if (!m_address.IsEmpty()) {
			if (lookup(m_address, m_port, addr, addrLen) != 0) {
				wxLogError(wxT("The local address is invalid - %s"), m_address.c_str());
				return false;
			}
		} else {
			if (lookup("", m_port, addr, addrLen) != 0) {
				wxLogError(wxT("The local address is invalid"));
				return false;
			}
		}

		int reuse = 1;
		if (::setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) == -1) {
#if defined(__WINDOWS__)
			wxLogError(wxT("Cannot set the UDP socket option (port: %u), err: %lu"), m_port, ::GetLastError());
#else
			wxLogError(wxT("Cannot set the UDP socket option (port: %u), err: %d"), m_port, errno);
#endif
			return false;
		}

		if (::bind(m_fd, (sockaddr*)&addr, sizeof(sockaddr_storage)) == -1) {
#if defined(__WINDOWS__)
			wxLogError(wxT("Cannot bind the UDP address (port: %u), err: %lu"), m_port, ::GetLastError());
#else
			wxLogError(wxT("Cannot bind the UDP address (port: %u), err: %d"), m_port, errno);
#endif
			return false;
		}
	}

	return true;
}

int CUDPReaderWriter::read(unsigned char* buffer, unsigned int length, sockaddr_storage& addr, unsigned int& addrLen)
{
	// Check that the readfrom() won't block
	fd_set readFds;
	FD_ZERO(&readFds);
#if defined(__WINDOWS__)
	FD_SET((unsigned int)m_fd, &readFds);
#else
	FD_SET(m_fd, &readFds);
#endif

	// Return immediately
	timeval tv;
	tv.tv_sec  = 0L;
	tv.tv_usec = 0L;

	int ret = ::select(m_fd + 1, &readFds, NULL, NULL, &tv);
	if (ret < 0) {
#if defined(__WINDOWS__)
		wxLogError(wxT("Error returned from UDP select (port: %u), err: %lu"), m_port, ::GetLastError());
#else
		wxLogError(wxT("Error returned from UDP select (port: %u), err: %d"), m_port, errno);
#endif
		return -1;
	}

	if (ret == 0)
		return 0;

#if defined(__WINDOWS__)
	int size = sizeof(sockaddr_storage);
#else
	socklen_t size = sizeof(sockaddr_storage);
#endif

	ssize_t len = ::recvfrom(m_fd, (char*)buffer, length, 0, (sockaddr *)&addr, &size);
	if (len <= 0) {
#if defined(__WINDOWS__)
		wxLogError(wxT("Error returned from recvfrom (port: %u), err: %lu"), m_port, ::GetLastError());
#else
		wxLogError(wxT("Error returned from recvfrom (port: %u), err: %d"), m_port, errno);
#endif
		return -1;
	}

	addrLen = size;

	return len;
}

bool CUDPReaderWriter::write(const unsigned char* buffer, unsigned int length, const sockaddr_storage& addr, unsigned int addrLen)
{
	ssize_t ret = ::sendto(m_fd, (char *)buffer, length, 0, (sockaddr *)&addr, addrLen);
	if (ret < 0) {
#if defined(__WINDOWS__)
		wxLogError(wxT("Error returned from sendto (port: %u), err: %lu"), m_port, ::GetLastError());
#else
		wxLogError(wxT("Error returned from sendto (port: %u), err: %d"), m_port, errno);
#endif
		return false;
	}

	if (ret != ssize_t(length))
		return false;

	return true;
}

void CUDPReaderWriter::close()
{
#if defined(__WINDOWS__)
	::closesocket(m_fd);
#else
	::close(m_fd);
#endif
}

unsigned int CUDPReaderWriter::getPort() const
{
	return m_port;
}
