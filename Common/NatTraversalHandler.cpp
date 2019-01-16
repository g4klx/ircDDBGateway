/*
 *   Copyright (C) 2010,2011,2012,2013,2014,2015,2016,2017,2018 by Jonathan Naylor G4KLX
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

#if defined(ENABLE_NAT_TRAVERSAL)

#include "NatTraversalHandler.h"

const unsigned int CACHE_SIZE = 500U;

CNatTraversalHandler::CNatTraversalHandler() :
m_g2cache(CACHE_SIZE),
m_g2Handler(NULL)
{

}

CNatTraversalHandler::~CNatTraversalHandler()
{
    for (CNatTraversalCache_t::iterator it = m_g2cache.begin(); it != m_g2cache.end(); ++it)
		delete it->second;
}

void CNatTraversalHandler::setG2Handler(CG2ProtocolHandler * handler)
{
    m_g2Handler = handler;
}

void CNatTraversalHandler::traverseNatG2(const wxString& address)
{
    if(m_g2Handler != NULL){
        CNatTraversalRecord* record = m_g2cache[address];
        
        if(record == NULL) {
            record = new CNatTraversalRecord(address);
            m_g2cache[address] = record;
        }

        std::time_t currentTime = std::time(NULL);
        if(currentTime - record->getTimestamp() > G2_TRAVERSAL_TIMEOUT) {
            record->setTimestamp(currentTime);
            m_g2Handler->traverseNat(address);
        }
    }
}

#endif