/*
 *   Copyright (C) 2012,2013,2018 by Jonathan Naylor G4KLX
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

#ifndef	DCSSet_H
#define	DCSSet_H

#include <wx/wx.h>

class CDCSSet : public wxPanel {
public:
	CDCSSet(wxWindow* parent, int id, const wxString& title, bool enabled);
	virtual ~CDCSSet();

	virtual bool Validate();

	virtual bool getEnabled() const;

private:
	wxString  m_title;
	wxChoice* m_enabled;
};

#endif
