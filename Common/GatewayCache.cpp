/*
 *   Copyright (C) 2010,2011,2012 by Jonathan Naylor G4KLX
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

#include "GatewayCache.h"

const unsigned int CACHE_SIZE = 500U;

CGatewayCache::CGatewayCache() :
m_cache(CACHE_SIZE)
{
}

CGatewayCache::~CGatewayCache()
{
	for (CGatewayCache_t::iterator it = m_cache.begin(); it != m_cache.end(); ++it)
		delete it->second;
}

CGatewayRecord* CGatewayCache::find(const wxString& gateway)
{
	return m_cache[gateway];
}

void CGatewayCache::update(const wxString& gateway, const wxString& address, DSTAR_PROTOCOL protocol, bool addrLock, bool protoLock)
{
	in_addr addr_in;
	addr_in.s_addr = ::inet_addr(address.mb_str());

	CGatewayRecord* rec = m_cache[gateway];

	if(rec == NULL) {
		rec = findByAddress(addr_in);//did this gateway punch to us and we do not have a gateway set for it ?
		if(rec != NULL && rec->getGateway().empty())
			rec->setGateway(gateway);
	}

	if (rec == NULL)
		// A brand new record is needed
		m_cache[gateway] = new CGatewayRecord(gateway, addr_in, G2_DV_PORT, protocol, addrLock, protoLock);
	else
		// Update an existing record
		rec->setData(addr_in, protocol, addrLock, protoLock);
}

void CGatewayCache::updateG2(const wxString& gateway, in_addr address,  unsigned int g2Port)
{
	//empty gateway means we are coming from udp hole punching, let see if we have an gateway with matching address
	CGatewayRecord* rec = gateway.empty()? findByAddress(address) : m_cache[gateway];

	if (rec == NULL) {
		// A brand new record is needed
		m_cache[gateway] = new CGatewayRecord(gateway, address, g2Port, DP_UNKNOWN, false, false);
	}
	else {
		// Update an existing record
		if(rec->getGateway().empty())//if this is a record created from a punch call, set its gateway
			rec->setGateway(gateway);

		rec->setG2Data(address, g2Port);
	}
}

CGatewayRecord* CGatewayCache::findByAddress(in_addr address)
{
	for (CGatewayCache_t::iterator it = m_cache.begin(); it != m_cache.end(); ++it) {
		if(it-> second != NULL
		   && it->second->getAddress().s_addr == address.s_addr)
			return it->second;
	}

	return NULL;
}

unsigned int CGatewayCache::getCount() const
{
	return m_cache.size();
}
