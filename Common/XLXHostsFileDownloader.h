/*
 *   Copyright (C) 2010-2013,2015 by Jonathan Naylor G4KLX
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


#ifndef XLXHostsFileDownloader_H
#define XLXHostsFileDownloader_H

#include <wx/wx.h>

#if !defined (__WINDOWS__)
#define XLX_USE_WGET //for some reason libwx is missing the net stuff on some distros, therefore always use wget if we are not compiling under windows
#endif

class CXLXHostsFileDownloader {
public:
	static wxString Download(const wxString & xlxHostsFileURL);
};

#endif
