/*
 *   Copyright (C) 2018 by Jonathan Naylor G4KLX
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

#include "MobileGPSSet.h"

const unsigned int CONTROL_WIDTH1 = 130U;
const unsigned int CONTROL_WIDTH2 = 80U;

const unsigned int ADDRESS_LENGTH = 15U;
const unsigned int PORT_LENGTH    = 5U;

const unsigned int BORDER_SIZE = 5U;

CMobileGPSSet::CMobileGPSSet(wxWindow* parent, int id, const wxString& title, bool enabled, const wxString& address, unsigned int port) :
wxPanel(parent, id),
m_title(title),
m_enabled(NULL),
m_address(NULL),
m_port(NULL)
{
	wxFlexGridSizer* sizer = new wxFlexGridSizer(2);

	wxStaticText* enabledLabel = new wxStaticText(this, -1, _("Mobile GPS"));
	sizer->Add(enabledLabel, 0, wxALL | wxALIGN_RIGHT, BORDER_SIZE);

	m_enabled = new wxChoice(this, -1, wxDefaultPosition, wxSize(CONTROL_WIDTH1, -1));
	m_enabled->Append(_("Disabled"));
	m_enabled->Append(_("Enabled"));
	sizer->Add(m_enabled, 0, wxALL | wxALIGN_LEFT, BORDER_SIZE);
	m_enabled->SetSelection(enabled ? 1 : 0);

	wxStaticText* addressLabel = new wxStaticText(this, -1, _("Address"));
	sizer->Add(addressLabel, 0, wxALL | wxALIGN_RIGHT, BORDER_SIZE);

	m_address = new CAddressTextCtrl(this, -1, address, wxDefaultPosition, wxSize(CONTROL_WIDTH1, -1));
	m_address->SetMaxLength(ADDRESS_LENGTH);
	sizer->Add(m_address, 0, wxALL | wxALIGN_LEFT, BORDER_SIZE);

	wxStaticText* portLabel = new wxStaticText(this, -1, _("Port"));
	sizer->Add(portLabel, 0, wxALL | wxALIGN_RIGHT, BORDER_SIZE);

	wxString buffer;
	buffer.Printf(wxT("%u"), port);

	m_port = new CPortTextCtrl(this, -1, buffer, wxDefaultPosition, wxSize(CONTROL_WIDTH2, -1));
	m_port->SetMaxLength(PORT_LENGTH);
	sizer->Add(m_port, 0, wxALL | wxALIGN_LEFT, BORDER_SIZE);

	SetAutoLayout(true);

	SetSizer(sizer);
}


CMobileGPSSet::~CMobileGPSSet()
{
}

bool CMobileGPSSet::Validate()
{
	if (m_enabled->GetCurrentSelection() == wxNOT_FOUND)
		return false;

	wxString address = getAddress();

	if (address.IsEmpty()) {
		wxMessageDialog dialog(this, _("The Mobile GPS Address is not valid"), m_title + _(" Error"), wxICON_ERROR);
		dialog.ShowModal();
		return false;
	}

	unsigned int port = getPort();

	if (port == 0U || port > 65535U) {
		wxMessageDialog dialog(this, _("The Mobile GPS Port is not valid"), m_title + _(" Error"), wxICON_ERROR);
		dialog.ShowModal();
		return false;
	}

	return true;
}

bool CMobileGPSSet::getEnabled() const
{
	int c = m_enabled->GetCurrentSelection();
	if (c == wxNOT_FOUND)
		return false;

	return c == 1;
}

wxString CMobileGPSSet::getAddress() const
{
	return m_address->GetValue();
}

unsigned int CMobileGPSSet::getPort() const
{
	unsigned long n;
	m_port->GetValue().ToULong(&n);

	return n;
}
