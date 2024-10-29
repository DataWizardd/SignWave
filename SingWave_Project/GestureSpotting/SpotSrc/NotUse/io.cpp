// #include "pch.h"
#include <SDKDDKVer.h>       // by hklee

#include "stdafx.h"
#include "Spot.h"
#include "utils.h"

FILE*	OpenListFile( const char *pszListFile, SHORT *pnModel, 
					 SHORT *pnData )
{
	FILE* fp;

	*pnModel = -1;
	*pnData = 0;
	if( !(fp = fopen( pszListFile, "r" )) ) 
	{
		Warning( "(OpenFileList) file <%s> not found", pszListFile );
		return( NULL );
	}

	if( !fscanf( fp, "# Label : %d\n", pnModel ) ||
		!fscanf( fp, "# NumData : %d\n", pnData ) )
	{
		Warning( "(OpenFileList) invalid list files" );
		fclose( fp );
		return( NULL );
	}

	if ( *pnModel < 0 || *pnData <= 0 )
	{
		Warning( "(OpenFileList) invalid label" );
		fclose( fp );
		*pnModel = -1;
		*pnData = 0;
		return( NULL );
	}

	return ( fp );
}


BOOL	GetData( SHORT **ppnData, SHORT *pnData, SHORT *pnTime, 
				SHORT nCodeSize, FILE* fp )
{
	int		i, j;
	SHORT	count;

	for ( i=0; i<*pnData; i++ )
	{
		if( !fscanf( fp, "%d", &count ) )
		{
			*pnData = i;
			return( FALSE );
		}
		if ( count <= 0 )
		{
			*pnData = i;
			return( FALSE );
		}
		
		ppnData[i] = MallocSHORT(count);
		for( j=0; j<count; j++ )
		{
			if( !fscanf( fp, "%d", &ppnData[i][j] ) )
			{
				*pnData = i;
				pnTime[i] = j;
				return( FALSE );
			}
			if ( ppnData[i][j] < 0 || ppnData[i][j] >= nCodeSize )
			{
				*pnData = i;
				pnTime[i] = j;
				return( FALSE );
			}
		}
		pnTime[i] = count;
	}
	
	return( TRUE );
}
