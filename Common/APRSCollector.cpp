/*
 *   Copyright (C) 2010,2012,2013,2014,2018 by Jonathan Naylor G4KLX
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

#include "APRSCollector.h"
#include "DStarDefines.h"
#include "Utils.h"

const unsigned int APRS_CSUM_LENGTH = 4U;
const unsigned int APRS_DATA_LENGTH = 300U;
const unsigned int SLOW_DATA_BLOCK_LENGTH = 6U;

const char APRS_OVERLAY = '\\';
const char APRS_SYMBOL  = 'K';

CAPRSCollector::CAPRSCollector() :
m_state(AS_NONE),
m_ggaData(NULL),
m_ggaLength(0U),
m_ggaValid(false),
m_rmcData(NULL),
m_rmcLength(0U),
m_rmcValid(false),
m_crcData(NULL),
m_crcLength(0U),
m_crcValid(false),
m_buffer(NULL),
m_slowData(SS_FIRST),
m_collector(),
m_callsign()
{
	m_ggaData = new unsigned char[APRS_DATA_LENGTH];
	m_rmcData = new unsigned char[APRS_DATA_LENGTH];
	m_crcData = new unsigned char[APRS_DATA_LENGTH];
	m_buffer  = new unsigned char[SLOW_DATA_BLOCK_LENGTH];
}

CAPRSCollector::~CAPRSCollector()
{
	delete[] m_ggaData;
	delete[] m_rmcData;
	delete[] m_crcData;
	delete[] m_buffer;
}

void CAPRSCollector::writeHeader(const wxString& callsign)
{
	m_callsign = callsign;
}

bool CAPRSCollector::writeData(const unsigned char* data)
{
	wxASSERT(data != NULL);

	switch (m_slowData) {
		case SS_FIRST:
			m_buffer[0U] = data[0U] ^ SCRAMBLER_BYTE1;
			m_buffer[1U] = data[1U] ^ SCRAMBLER_BYTE2;
			m_buffer[2U] = data[2U] ^ SCRAMBLER_BYTE3;
			m_slowData = SS_SECOND;
			return false;

		case SS_SECOND:
			m_buffer[3U] = data[0U] ^ SCRAMBLER_BYTE1;
			m_buffer[4U] = data[1U] ^ SCRAMBLER_BYTE2;
			m_buffer[5U] = data[2U] ^ SCRAMBLER_BYTE3;
			m_slowData = SS_FIRST;
			break;
	}

	// Is it GPS data?
	if ((m_buffer[0U] & SLOW_DATA_TYPE_MASK) == SLOW_DATA_TYPE_GPS)
		return addGPSData(m_buffer + 1U);

	return false;
}

void CAPRSCollector::reset()
{
	m_state     = AS_NONE;
	m_ggaLength = 0U;
	m_ggaValid  = false;
	m_rmcLength = 0U;
	m_rmcValid  = false;
	m_crcLength = 0U;
	m_crcValid  = false;
	m_slowData  = SS_FIRST;
	m_collector.Clear();
	m_callsign.Clear();
}

void CAPRSCollector::sync()
{
	m_slowData = SS_FIRST;
}

bool CAPRSCollector::addGPSData(const unsigned char* data)
{
	wxASSERT(data != NULL);

	m_collector.Append((char*)data, 5U);

	if (m_state == AS_GGA) {
		addGGAData();
		return false;
	} else if (m_state == AS_RMC) {
		return addRMCData();
	} else if (m_state == AS_CRC) {
		return addCRCData();
	}
	
	if (m_state != AS_GGA && m_collector.Find(wxT("$GPGGA")) != wxNOT_FOUND) {
		m_state     = AS_GGA;
		m_ggaLength = 0U;
		m_ggaValid  = false;
		m_rmcLength = 0U;
		m_rmcValid  = false;
		return false;
	} else if (m_state != AS_RMC && m_collector.Find(wxT("$GPRMC")) != wxNOT_FOUND) {
		m_state     = AS_RMC;
		m_rmcLength = 0U;
		m_rmcValid  = false;
		return false;
	} else if (m_state != AS_CRC && m_collector.Find(wxT("$$CRC")) != wxNOT_FOUND) {
		m_state     = AS_CRC;
		m_crcLength = 0U;
		m_crcValid  = false;
	}

	return false;
}

void CAPRSCollector::addGGAData()
{
	int n2 = m_collector.Find(wxT('\x0A'), true);
	if (n2 == wxNOT_FOUND)
		return;

	int n1 = m_collector.Find(wxT("$GPGGA"));
	if (n1 == wxNOT_FOUND)
		return;

	if (n2 < n1)
		return;

	unsigned int len = n2 - n1;

	if (len >= APRS_DATA_LENGTH) {
		m_ggaLength = 0U;
		m_ggaValid  = false;
		m_state     = AS_NONE;
		return;
	}

	m_ggaLength = 0U;
	for (int i = n1; i <= n2; i++) {
		m_ggaData[m_ggaLength]  = m_collector.GetChar(i);
		m_ggaData[m_ggaLength] &= 0x7FU;
		m_ggaLength++;
	}

	bool ret = checkXOR(m_ggaData + 1U, m_ggaLength - 1U);
	if (ret) {
		// CUtils::dump(wxT("$GPGGA Valid"), m_ggaData, m_ggaLength);
		m_ggaValid  = true;
		m_state     = AS_RMC;
	} else {
		// CUtils::dump(wxT("$GPGGA Bad checksum"), m_ggaData, m_ggaLength);
		m_ggaLength = 0U;
		m_ggaValid  = false;
		m_state     = AS_RMC;
	}

	m_collector = m_collector.Mid(n2);
}

bool CAPRSCollector::addRMCData()
{
	int n2 = m_collector.Find(wxT('\x0A'), true);
	if (n2 == wxNOT_FOUND)
		return false;

	int n1 = m_collector.Find(wxT("$GPRMC"));
	if (n1 == wxNOT_FOUND)
		return false;

	if (n2 < n1)
		return false;

	unsigned int len = n2 - n1;

	if (len >= APRS_DATA_LENGTH) {
		m_rmcLength = 0U;
		m_rmcValid  = false;
		m_state     = AS_NONE;
		return false;
	}

	m_rmcLength = 0U;
	for (int i = n1; i <= n2; i++) {
		m_rmcData[m_rmcLength]  = m_collector.GetChar(i);
		m_rmcData[m_rmcLength] &= 0x7FU;
		m_rmcLength++;
	}

	bool ret = checkXOR(m_rmcData + 1U, m_rmcLength - 1U);
	if (ret) {
		// CUtils::dump(wxT("$GPRMC Valid"), m_rmcData, m_rmcLength);
		m_rmcValid = true;
	} else {
		// CUtils::dump(wxT("$GPRMC Bad checksum"), m_rmcData, m_rmcLength);
		m_rmcLength = 0U;
		m_rmcValid  = false;
	}

	m_collector = m_collector.Mid(n2);

	m_state = AS_NONE;

	return true;
}

bool CAPRSCollector::addCRCData()
{
	int n2 = m_collector.Find(wxT('\x0D'), true);
	if (n2 == wxNOT_FOUND)
		return false;

	int n1 = m_collector.Find(wxT("$$CRC"));
	if (n1 == wxNOT_FOUND)
		return false;

	if (n2 < n1)
		return false;

	unsigned int len = n2 - n1;

	if (len >= APRS_DATA_LENGTH) {
		m_crcLength = 0U;
		m_crcValid  = false;
		m_state     = AS_NONE;
		return false;
	}

	m_crcLength = 0U;
	for (int i = n1; i <= n2; i++) {
		m_crcData[m_crcLength] = m_collector.GetChar(i);
		m_crcLength++;
	}

	bool ret = checkCRC(m_crcData, m_crcLength);
	if (ret) {
		// CUtils::dump(wxT("$$CRC Valid"), m_crcData, m_crcLength);
		m_crcValid = true;
		m_state = AS_NONE;
		m_collector = m_collector.Mid(n2);
		return true;
	} else {
		// CUtils::dump(wxT("$$CRC Bad checksum"), m_crcData, m_crcLength);
		m_crcLength = 0U;
		m_crcValid  = false;
		m_state     = AS_NONE;
		m_collector = m_collector.Mid(n2);
		return false;
	}
}

unsigned int CAPRSCollector::getData(unsigned char* data, unsigned int length)
{
	wxASSERT(data != NULL);

	// Have we got GPS-A data?
	if (m_crcValid) {
		unsigned int len = m_crcLength - 10U;
		if (len > length)
			len = length;

		::memcpy(data, m_crcData + 10U, len);

		m_crcLength = 0U;
		m_crcValid  = false;

		return len;
	}

	// Have we got GGA data?
	if (m_ggaValid) {
		unsigned int len = convertNMEA1(data, length);

		m_ggaLength = 0U;
		m_rmcLength = 0U;
		m_ggaValid  = false;
		m_rmcValid  = false;

		return len;
	}

	// Have we got RMC data?
	if (m_rmcValid) {
		unsigned int len = convertNMEA2(data, length);

		m_ggaLength = 0U;
		m_rmcLength = 0U;
		m_ggaValid  = false;
		m_rmcValid  = false;

		return len;
	}

	return 0U;
}

bool CAPRSCollector::checkXOR(const unsigned char* data, unsigned int length) const
{
	unsigned int posStar = 0U;
	for (unsigned int i = length - 1U; i > 0U; i--) {
		if (data[i] == '*') {
			posStar = i;
			break;
		}
	}

	if (posStar == 0U)
		return false;

	unsigned char csum = calcXOR(data, posStar);

	char buffer[10U];
	::sprintf(buffer, "%02X", csum);

	return ::memcmp(buffer, data + posStar + 1U, 2U) == 0;
}

unsigned char CAPRSCollector::calcXOR(const unsigned char* buffer, unsigned int length) const
{ 
	wxASSERT(buffer != NULL);
	wxASSERT(length > 0U);

	unsigned char res = 0U;

	for (unsigned int i = 0U; i < length; i++)
		res ^= buffer[i];

	return res;
}

bool CAPRSCollector::checkCRC(const unsigned char* data, unsigned int length) const
{
	unsigned int csum = calcCRC(data + 10U, length - 10U);

	char buffer[10U];
	::sprintf(buffer, "%04X", csum);

	return ::memcmp(buffer, data + 5U, APRS_CSUM_LENGTH) == 0;
}

unsigned int CAPRSCollector::calcCRC(const unsigned char* buffer, unsigned int length) const
{ 
	wxASSERT(buffer != NULL);
	wxASSERT(length > 0U);

	unsigned int icomcrc = 0xFFFFU;

	for (unsigned int j = 0U; j < length; j++) {
		unsigned char ch = buffer[j];

		for (unsigned int i = 0U; i < 8U; i++) {
			bool xorflag = (((icomcrc ^ ch) & 0x01U) == 0x01U);

			icomcrc >>= 1;

			if (xorflag)
				icomcrc ^= 0x8408U;

			ch >>= 1;
		} 
	}

	return ~icomcrc & 0xFFFFU;
}

unsigned int CAPRSCollector::convertNMEA1(unsigned char* data, unsigned int)
{
	// Parse the $GPGGA string into tokens
	char* pGGA[20U];
	::memset(pGGA, 0x00U, 20U * sizeof(char*));
	unsigned int nGGA = 0U;

	char* str = (char*)m_ggaData;
	for (;;) {
		char* p = mystrsep(&str, ",\r\n");

		pGGA[nGGA++] = p;
		if (p == NULL)
			break;
	}

	// Is there any position data?
	if (pGGA[2U] == NULL || pGGA[3U] == NULL || pGGA[4U] == NULL || pGGA[5U] == NULL || ::strlen(pGGA[2U]) == 0U || ::strlen(pGGA[3U]) == 0U || ::strlen(pGGA[4U]) == 0 || ::strlen(pGGA[5U]) == 0)
		return 0U;

	// Is it a valid GPS fix?
	if (::strcmp(pGGA[6U], "0") == 0)
		return 0U;

	char callsign[10U];
	dstarCallsignToAPRS(m_callsign, callsign);

	::sprintf((char*)data, "%s>APDPRS,DSTAR*:!%.7s%s%c%.8s%s%c", callsign, pGGA[2U], pGGA[3U], APRS_OVERLAY, pGGA[4U], pGGA[5U], APRS_SYMBOL);

	// Get the bearing and speed from the RMC data
	if (m_rmcValid) {
		// Parse the $GPRMC string into tokens
		char* pRMC[20U];
		::memset(pRMC, 0x00U, 20U * sizeof(char*));
		unsigned int nRMC = 0U;

		str = (char*)m_rmcData;
		for (;;) {
			char* p = mystrsep(&str, ",\r\n");

			pRMC[nRMC++] = p;
			if (p == NULL)
				break;
		}

		// Check that we have a bearing and speed
		if (pRMC[7U] != NULL && pRMC[8U] != NULL && ::strlen(pRMC[7U]) > 0U && ::strlen(pRMC[8U]) > 0U) {
			int bearing = ::atoi(pRMC[8U]);
			int speed   = ::atoi(pRMC[7U]);

			::sprintf((char*)data + ::strlen((char*)data), "%03d/%03d", bearing, speed);
		}
	}

	if (pGGA[9U] != NULL && ::strlen(pGGA[9U]) > 0U) {
		// Convert altitude from metres to feet
		int altitude = ::atoi(pGGA[9U]);
		::sprintf((char*)data + ::strlen((char*)data), "/A=%06.0f", float(altitude) * 3.28F);
	}

	return ::strlen((char*)data);
}

unsigned int CAPRSCollector::convertNMEA2(unsigned char* data, unsigned int)
{
	// Parse the $GPRMC string into tokens
	char* pRMC[20U];
	::memset(pRMC, 0x00U, 20U * sizeof(char*));
	unsigned int nRMC = 0U;

	char* str = (char*)m_rmcData;
	for (;;) {
		char* p = mystrsep(&str, ",\r\n");

		pRMC[nRMC++] = p;
		if (p == NULL)
			break;
	}

	// Is there any position data?
	if (pRMC[3U] == NULL || pRMC[4U] == NULL || pRMC[5U] == NULL || pRMC[6U] == NULL || ::strlen(pRMC[3U]) == 0U || ::strlen(pRMC[4U]) == 0U || ::strlen(pRMC[5U]) == 0 || ::strlen(pRMC[6U]) == 0)
		return 0U;

	// Is it a valid GPS fix?
	if (::strcmp(pRMC[2U], "A") != 0)
		return 0U;

	char callsign[10U];
	dstarCallsignToAPRS(m_callsign, callsign);

	::sprintf((char*)data, "%s>APDPRS,DSTAR*:!%.7s%s%c%.8s%s%c", callsign, pRMC[3U], pRMC[4U], APRS_OVERLAY, pRMC[5U], pRMC[6U], APRS_SYMBOL);

	if (pRMC[7U] != NULL && pRMC[8U] != NULL && ::strlen(pRMC[7U]) > 0U && ::strlen(pRMC[8U]) > 0U) {
		int bearing = ::atoi(pRMC[8U]);
		int speed   = ::atoi(pRMC[7U]);

		::sprintf((char*)data + ::strlen((char*)data), "%03d/%03d", bearing, speed);
	}

	return ::strlen((char*)data);
}

void CAPRSCollector::dstarCallsignToAPRS(const wxString& dstarCallsign, char* aprsCallsign) const
{
	wxASSERT(aprsCallsign != NULL);

	wxString first = dstarCallsign.BeforeFirst(wxT(' '));
	wxString last  = dstarCallsign.AfterLast(wxT(' '));

	if (last.IsEmpty() || first.IsSameAs(last)) {
		unsigned int n = 0U;
		for (unsigned int i = 0U; i < first.Len(); i++)
			aprsCallsign[n++] = first.GetChar(i);
		aprsCallsign[n++] = '\0';
	} else {
		unsigned int n = 0U;
		for (unsigned int i = 0U; i < first.Len(); i++)
			aprsCallsign[n++] = first.GetChar(i);
		aprsCallsign[n++] = '-';
		for (unsigned int i = 0U; i < last.Len(); i++)
			aprsCallsign[n++] = last.GetChar(i);
		aprsCallsign[n++] = '\0';
	}
}

// Source found at <http://unixpapa.com/incnote/string.html>
char* CAPRSCollector::mystrsep(char** sp, const char* sep) const
{
	if (sp == NULL || *sp == NULL || **sp == '\0')
		return NULL;

	char* s = *sp;
	char* p = s + ::strcspn(s, sep);

	if (*p != '\0')
		*p++ = '\0';

	*sp = p;

	return s;
}
