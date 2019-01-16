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
#ifndef NatTraversalHandler_H
#define NatTraversalHandler_H

#define G2_TRAVERSAL_TIMEOUT 29 //seconds

#include "G2ProtocolHandler.h"

#include <wx/wx.h>
#include <ctime>

enum NAT_TRAVERSAL_TYPE {
    NTT_G2,
    //NTT_DEXTRA
    //NTT_DCS
    //NTT_DPLUS
};

class CNatTraversalRecord {
public:
    CNatTraversalRecord(const wxString& address) :
    m_address(address),
    m_timestamp(0)
    {
    }

    std::time_t getTimestamp() const
    {
        return m_timestamp;
    }

    void setTimestamp(std::time_t timestamp)
    {
        m_timestamp = timestamp;
    }

private:
    wxString m_address;
    std::time_t m_timestamp;
};

WX_DECLARE_STRING_HASH_MAP(CNatTraversalRecord*, CNatTraversalCache_t);

/*
* This keeps track of when we UDP punched to one destination so to avoid unnecessary traffic on each ircddb reporting
*/
class CNatTraversalHandler {
public:
    CNatTraversalHandler();
    ~CNatTraversalHandler();

    void setG2Handler(CG2ProtocolHandler* handler);
    void traverseNatG2(const wxString& address);

private:
    CNatTraversalCache_t m_g2cache;    
    CG2ProtocolHandler* m_g2Handler;
};

#endif

#endif