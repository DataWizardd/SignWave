#ifndef	_CFLIST_H
#define	_CFLIST_H

class CFilelist {
public:
  // constructor && deconstructor
	CFilelist(const SHORT nFile);
	CFilelist( const char *pszFileName );
	~CFilelist();

  // attributes
private:
	char	**m_szFile;

public:
	SHORT	m_nFile;
	SHORT	m_nMaxFile;

public:
	char*	GetFile(const SHORT idx);
	BOOL	PutFile(const SHORT idx, const char *szFName);
	BOOL	SplitFileName( SHORT nFile, char* pszPrefix, UINT* pnFileID );
	SHORT	FindFileName( const char* pszFileName );

private:
};

#endif
  