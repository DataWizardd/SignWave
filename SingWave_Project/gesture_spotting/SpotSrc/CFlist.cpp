// #include "pch.h"
#include <SDKDDKVer.h>       // by hklee

#include "stdafx.h"
#include "Spot.h"
#include "utils.h"
#include "CFlist.h"

#define MAX_FILE	10000

CFilelist::CFilelist(const SHORT nFile)
{
	m_nMaxFile = m_nFile = nFile;

	m_szFile = new char *[nFile];
	for (int i=0; i<m_nFile; i++)
		m_szFile[i] = new char[MAX_BUFFER];
}

CFilelist::CFilelist( const char *pszFileName )
{
	FILE*	fpin;
	char	szFile[MAX_BUFFER];
	int		nFile;

	// file open and check the status of the fopen(...)
	if( !( fpin = fopen( pszFileName, "r" ) ) ) {
		Warning( "(CFilelist::Read) file <%s> not found", pszFileName );
		return;
	}

	// Read Header and check the header is correct.
	fscanf_s( fpin, "%d", &nFile );
	if (nFile < 1 || nFile >= MAX_FILE) {
		m_nMaxFile = 0;
		m_nFile = 0;
		m_szFile = NULL;
		return;
	}

	m_nMaxFile = (SHORT)nFile;
	m_szFile = new char *[m_nMaxFile];

	m_nFile = 0;
	while (fscanf_s( fpin, "%s", szFile ) != EOF) {
		m_szFile[m_nFile] = new char[MAX_BUFFER];
		strcpy( m_szFile[m_nFile], szFile );
		m_nFile++;

		if (m_nFile >= nFile)
			break;
	}
}

CFilelist::~CFilelist()
{
	if (m_szFile) {
		for (int i=0; i<m_nMaxFile; i++)
			delete[] m_szFile[i];

		delete[] m_szFile;
	}
}

char* CFilelist::GetFile(const SHORT idx)
{
	if (idx < 0 || idx >= m_nFile)
		return NULL;

	return m_szFile[idx];
}

BOOL CFilelist::PutFile(const SHORT idx, const char *szFName)
{
	if (idx < 0 || idx >= m_nFile)
		return FALSE;

	strcpy(m_szFile[idx], szFName);
	return TRUE;
}

BOOL CFilelist::SplitFileName( SHORT nFile, char* pszPrefix, UINT* pnFileID )
{
	SHORT		len, loc;
	char*		pszFile = GetFile(nFile);

	len = strlen(pszFile);
	if (len <= 0)
		return FALSE;

	for(loc=len-1; loc>=0; loc--) {
		if (pszFile[loc] == '\\' || pszFile[loc] == '/')
			break;
	}
	if (loc < 0 || loc == len-1)
		return FALSE;
	loc++;

	for(int i=loc; i<len; i++) {
		if (pszFile[i] == '.') {
			*pnFileID =   (pszFile[i+1] - '0') * 100 
						+ (pszFile[i+2] - '0') * 10 
						+ (pszFile[i+3] - '0'); 
			pszPrefix[i-loc] = 0;
			break;
		}
		pszPrefix[i-loc] = pszFile[i];
	}

	return TRUE;
}

SHORT CFilelist::FindFileName( const char* pszFileName )
{
	for(int i=0; i<m_nFile; i++) {
		if ( !_strcmpi(pszFileName, m_szFile[i]) )
			return i;
	}

	return -1;
}