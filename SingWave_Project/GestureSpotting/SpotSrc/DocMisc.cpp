// #include "pch.h"
#include <SDKDDKVer.h>       // by hklee

#include "stdafx.h"
#include "Spot.h"
#include "utils.h"
#include "CFlist.h"
#include "Cmgvq.h"
#include "Cdhmm.h"
#include "GestureDoc.h"


void CGestureDoc::ReadTrainedModel()
{
	if (!m_pMGVQ) {
		m_pMGVQ = new CMGVQ;
		m_pMGVQ->NewCodebook( m_nSymbol, TEST_DIMENSION );
		m_pMGVQ->Read( MakeMyFileName("VQ.out\\", "mgvq") );
	}
	if (!m_pMGVQ)
		return;

	PrintProgressString( "Reading trained models ..." );

	if (m_pHMM)
		delete[] m_pHMM;

	m_pHMM = new CDHmm[m_nModel];	
	for( int i=0; i<m_nModel; i++ ) {
		m_pHMM[i].Read( MakeMyFileName("Model\\", m_pModel[i].szName, "bmd") );
	}

	if (m_Flags.bTestUnitedModel) {
		m_pUnited = new CDHmm;	
		m_pUnited->Read( MakeMyFileName("Model\\", "united.bmd") );
	}
}

void CGestureDoc::InitializeAllModel()
{
	if (m_Flags.bLoadThresholdModel) {
		m_nModel--;
		m_Flags.bLoadThresholdModel = FALSE;
	}

	if (m_pHMM)
		delete[] m_pHMM;
	m_pHMM = new CDHmm[m_nModel];

	for(int i=0; i<m_nModel; i++) {
		m_pHMM[i].InitializeModel( m_pModel[i].nState, m_nSymbol );
		m_pHMM[i].WriteText( MakeMyFileName("Model\\", m_pModel[i].szName, "tmd") );
		m_pHMM[i].Write( MakeMyFileName("Model\\", m_pModel[i].szName, "bmd") );
	}
}


//#define SLOW_TEST

BOOL CGestureDoc::ReadDocument( FILE* fp )
{
	BOOL	bOK = TRUE;
	int		i, r1 = 0, r2 = 0, r3; // variables for integer reading
								// integer = 4bytes, short = 2bytes

	// read the num models and num symbols
	if ( !fscanf( fp, "# NumModels : %d\n", &r1 ) ||
		 !fscanf( fp, "# NumSymbols : %d\n", &r2 ) )
		 return FALSE;
	
	m_nModel = r1;
	m_nSymbol = r2;

	if ( m_nModel < 1 || m_nModel > 20 || m_nSymbol < 2 )
		return FALSE;

	m_pModel = new MODEL[m_nModel+1];

	for(i=0; i<m_nModel; i++) {
		r1 = 0; r2 = 0; r3 = 0;
		if ( !fscanf( fp, "%s%d%d%d", m_pModel[i].szName, &r1, &r2, &r3 ) )
			return FALSE;
		m_pModel[i].nState = r1;
		m_pModel[i].nNumFile = r2;
#ifdef SLOW_TEST
		m_pModel[i].nMinTime = r3 ;
#else
		m_pModel[i].nMinTime = r3 / 2 + 1;
#endif
	}

	if ( !strcmpi(m_pModel[m_nModel-1].szName, "etc") ) {
		m_Flags.bLoadThresholdModel = TRUE;
		m_nThresholdModel = m_nModel-1;
	} else {
		strcpy( m_pModel[m_nModel].szName, "etc" );
		m_pModel[m_nModel].nState = 0;
		for(i=0; i<m_nModel; i++)
			m_pModel[m_nModel].nState += m_pModel[i].nState - 2;
		m_pModel[m_nModel].nNumFile = 0;
		m_pModel[m_nModel].nMinTime = 0;
		m_nThresholdModel = m_nModel;

		if (m_Flags.bLoadThresholdModel)
			m_nModel++;
	}

	if ( !fscanf(fp, "%s", m_szBaseDir) )
		return FALSE;

	int len = strlen( m_szBaseDir );
	if ( len >= 1 ) {
		if ( m_szBaseDir[len-1] != '\\' && m_szBaseDir[len-1] != '/' )
			strcat( m_szBaseDir, "\\" );
		CorrectDirDelimeter( m_szBaseDir );
		SetBaseDir( m_szBaseDir );
	} else
		return FALSE;

	char* pszTmp = new char[MAX_BUFFER];

	if ( fscanf(fp, "%s", pszTmp) )
		Dir_sprintf( m_szTrainFile, "%sTrain\\%s", m_szBaseDir, pszTmp );
	else
		bOK = FALSE;

	if ( bOK && fscanf(fp, "%s", pszTmp) )
		Dir_sprintf( m_szTestFile, "%sTest\\%s", m_szBaseDir, pszTmp );
	else
		bOK = FALSE;

	if ( bOK && fscanf(fp, "%s", pszTmp) )
		Dir_sprintf( m_szModelDir, "%s%s\\", m_szBaseDir, pszTmp );
	else
		bOK = FALSE;

	delete[] pszTmp;

	return bOK;
}

void CGestureDoc::RemoveAllRawData()
{
	if (m_pFVec)
		delete[] m_pFVec;
	
	m_pFVec = NULL;
	m_nFVec = 0;
}

BOOL CGestureDoc::LoadAllRawData()
{
	if (m_pFVec)
		delete[] m_pFVec;

	CFilelist* pFList = new CFilelist( MakeMyFileName("RawData\\", "Raw.dat") );

	if ( !pFList || pFList->m_nFile <= 0 ) {
		if (pFList)
			delete pFList;
		return FALSE;
	}

	m_nFVec = pFList->m_nFile;
	m_pFVec = new CFVec[m_nFVec];

	for(int i=0; i<m_nFVec; i++)
		m_pFVec[i].Read( pFList->GetFile(i) );

	delete pFList;

	return TRUE;
}

BOOL CGestureDoc::GenerateMGVQ()
{
	if ( !LoadAllRawData() )
		return FALSE;

	if (m_pMGVQ)
		delete m_pMGVQ;

	m_pMGVQ = new CMGVQ;
	if ( !m_pMGVQ->GenCodebook(m_pFVec, m_nFVec, TEST_DIMENSION, TEST_LEVEL) ) {
		RemoveAllRawData();
		delete m_pMGVQ;
		m_pMGVQ = NULL;
		return FALSE;
	}

	RemoveAllRawData();

	m_pMGVQ->Write( MakeMyFileName("VQ.out\\", "mgvq") );
	m_pMGVQ->WriteText( MakeMyFileName("VQ.out\\", "mgvq") );

	return TRUE;
}

BOOL CGestureDoc::MakeRawList( const char* pStrokeFile, const char* pRawFile,
				 SHORT nFromModel, SHORT nToModel )
{
	int		i, j;
	FILE	*stk_fp, *raw_fp;

	if( !(stk_fp = fopen( MakeMyFileName("Stroke\\", pStrokeFile), "w" )) ||
		!(raw_fp = fopen( MakeMyFileName("RawData\\", pRawFile), "w" )) )
	{
		if (stk_fp) fclose( stk_fp );

		Warning( "(CGestureDoc::MakeRawList) can not open data file" );
		return FALSE;
	}

	SHORT nTotFile = 0;

	for(i=nFromModel; i<=nToModel; i++)
		nTotFile += m_pModel[i].nNumFile;

	fprintf(stk_fp, "%d\n\n", nTotFile );
	fprintf(raw_fp, "%d\n\n", nTotFile );

	for(i=nFromModel; i<=nToModel; i++) {
		for(j=0; j<m_pModel[i].nNumFile; j++) {
			Dir_fprintf(stk_fp, "%sStroke\\o%s.%03d\n", m_szBaseDir, m_pModel[i].szName, j );
			Dir_fprintf(raw_fp, "%sRawData\\%s.%03d\n", m_szBaseDir, m_pModel[i].szName, j );
		}
		fprintf( stk_fp, "\n" );
		fprintf( raw_fp, "\n" );
	}

	fclose(stk_fp);
	fclose(raw_fp);

	return TRUE;
}

BOOL CGestureDoc::MakeThresholdRawList( const char* pStrokeFile, const char* pRawFile,
				 SHORT* pnTotFile, BYTE** pcFlag )
{
	int		i, j;
	FILE	*stk_fp, *raw_fp;

	if( !(stk_fp = fopen( MakeMyFileName("Stroke\\", pStrokeFile), "w" )) ||
		!(raw_fp = fopen( MakeMyFileName("RawData\\", pRawFile), "w" )) )
	{
		if (stk_fp) fclose( stk_fp );

		Warning( "(CGestureDoc::MakeThresholdRawList) can not open data file" );
		return FALSE;
	}

	SHORT nTotFile = 0;

	for(i=0; i<m_nThresholdModel; i++)
		nTotFile += pnTotFile[i];
	nTotFile += m_pModel[m_nThresholdModel].nNumFile;

	fprintf(stk_fp, "%d\n\n", nTotFile );
	fprintf(raw_fp, "%d\n\n", nTotFile );

	for(i=0; i<m_nThresholdModel; i++) {
		for(j=0; j<m_pModel[i].nNumFile; j++) {
			if ( !pcFlag[i][j] ) {
				Dir_fprintf(stk_fp, "%sStroke\\o%s.%03d\n", m_szBaseDir, m_pModel[i].szName, j );
				Dir_fprintf(raw_fp, "%sRawData\\%s.%03d\n", m_szBaseDir, m_pModel[i].szName, j );
			}
		}
		fprintf( stk_fp, "\n" );
		fprintf( raw_fp, "\n" );
	}

	for(j=0; j<m_pModel[i].nNumFile; j++) {
		Dir_fprintf(stk_fp, "%sStroke\\o%s.%03d\n", m_szBaseDir, m_pModel[m_nThresholdModel].szName, j );
		Dir_fprintf(raw_fp, "%sRawData\\%s.%03d\n", m_szBaseDir, m_pModel[m_nThresholdModel].szName, j );
	}
	fprintf( stk_fp, "\n" );
	fprintf( raw_fp, "\n" );

	fclose(stk_fp);
	fclose(raw_fp);

	return TRUE;
}

BOOL CGestureDoc::MakeListFile()
{
	int		i, j;
	FILE	*fp[2], *trn_fp, *tst_fp, *tfp;

	PrintProgressString( "Making stroke/raw data list files" );
	if ( !MakeRawList("Stroke.dat", "Raw.dat", 0, m_nModel-1) )
		return FALSE;

	PrintProgressString( "Making train/test data list files" );

	if( !(trn_fp = fopen( m_szTrainFile, "w" )) ||
		!(tst_fp = fopen( m_szTestFile, "w" )) ) {
		if (trn_fp) fclose(trn_fp);

		Warning( "(CGestureDoc::OnMakeListFile) can not open list file" );
		return FALSE;
	}

	char*	pszTmp;
	BYTE**	pcFlag = new BYTE*[m_nModel];
	SHORT*	pnTotFile = new SHORT[m_nModel];
	SHORT	nTrain = 0;

	for(i=0; i<m_nModel; i++) {
		pcFlag[i] = new BYTE[m_pModel[i].nNumFile];

		pszTmp = MakeMyFileName( "Train\\", m_pModel[i].szName, "lst" );
		fprintf(trn_fp, "%s %s\n", m_pModel[i].szName, pszTmp );
		if( !(fp[0] = fopen( pszTmp, "w" )) ) {
			Warning( "(CGestureDoc::OnMakeListFile) can not open file %s", pszTmp );
			break;
		}

		pszTmp = MakeMyFileName( "Test\\", m_pModel[i].szName, "lst" );
		fprintf(tst_fp, "%s %s\n", m_pModel[i].szName, pszTmp );
		if( !(fp[1] = fopen( pszTmp, "w" )) ) {
			fclose( fp[0] );
			Warning( "(CGestureDoc::OnMakeListFile) can not open file %s", pszTmp );
			break;
		}

		nTrain = 0;

		for(j=0; j<m_pModel[i].nNumFile; j++) {
			float r = (float)rand() / (float)RAND_MAX * (float)100.0;
			if (r >= (float)20.0) {
				pcFlag[i][j] = TRUE;
				nTrain++;
			} else
				pcFlag[i][j] = FALSE;
		}

		if ( i == m_nThresholdModel) {
			fprintf(fp[0], "%d\n\n", m_pModel[i].nNumFile);
			fprintf(fp[1], "%d\n\n", m_pModel[i].nNumFile-nTrain);
		} else {
			fprintf(fp[0], "%d\n\n", nTrain);
			fprintf(fp[1], "%d\n\n", m_pModel[i].nNumFile-nTrain);
		}
		pnTotFile[i] = m_pModel[i].nNumFile-nTrain;

		for(j=0; j<m_pModel[i].nNumFile; j++) {
			if (i == m_nThresholdModel) {
				Dir_fprintf( fp[0], "%sRawData\\%s.%03d\n", m_szBaseDir, m_pModel[i].szName, j );
				if ( !pcFlag[i][j] ) {
					Dir_fprintf( fp[1], "%sRawData\\%s.%03d\n", m_szBaseDir, m_pModel[i].szName, j );
				}
			} else {
				if (pcFlag[i][j]) tfp = fp[0];
				else tfp = fp[1];

				Dir_fprintf( tfp, "%sRawData\\%s.%03d\n", m_szBaseDir, m_pModel[i].szName, j );
			}
		}

		fclose(fp[0]);
		fclose(fp[1]);
	}

	fclose(trn_fp);
	fclose(tst_fp);

	if (m_Flags.bLoadThresholdModel) {
		PrintProgressString( "Making threshold data list files" );
		if ( !MakeThresholdRawList("EtcStrk.dat", "EtcRaw.dat", pnTotFile, pcFlag) ) {
			for(i=0; i<m_nModel; i++)
				delete[] pcFlag[i];
			delete[] pcFlag;
			delete[] pnTotFile;

			return FALSE;
		}
	}

	for(i=0; i<m_nModel; i++)
		delete[] pcFlag[i];
	delete[] pcFlag;
	delete[] pnTotFile;

	PrintProgressString( "Done!!!" );

	return TRUE;
}

void CGestureDoc::GenerateThresholdModel( REAL rThreshProb )
{
	if ( !m_Flags.bLoadThresholdModel )	{
		m_Flags.bLoadThresholdModel = TRUE;
		m_nModel++;
	}
	SHORT nOrgModel = m_nModel;

	m_nModel--;

	// Model must always be reloaded because the HMM change prPi, pprA, pprB
	// in negative log scale for recognition
	ReadTrainedModel();

	CDHmm* pThresholdHmm = new CDHmm;
	pThresholdHmm->MakeThresholdModel( m_pHMM, m_nModel, m_nSymbol, 
				rThreshProb, m_Flags.bReducedThreshold );

	pThresholdHmm->WriteText( MakeMyFileName("Model\\", "etc.tmd") );
	pThresholdHmm->Write( MakeMyFileName("Model\\", "etc.bmd") );

	m_nModel = nOrgModel;

	delete pThresholdHmm;
	
	ReadTrainedModel();
}

BOOL CGestureDoc::GenerateUnitedModel( REAL rThreshProb )
{
	if ( !m_Flags.bLoadThresholdModel ) {
		m_Flags.bLoadThresholdModel = TRUE;
		m_nModel++;
	}

	ReadTrainedModel();

	if ( m_pUnited )
		delete m_pUnited;
	m_pUnited = new CDHmm;

	m_pUnited->MakeUnitedModel( m_pHMM, &m_pHMM[m_nThresholdModel], 
					m_nThresholdModel, m_nSymbol, rThreshProb );

	m_pUnited->WriteText( MakeMyFileName("Model\\", "united.tmd") );
	m_pUnited->Write( MakeMyFileName("Model\\", "united.bmd") );

	return TRUE;
}
