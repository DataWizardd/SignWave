// #include "pch.h"
#include <SDKDDKVer.h>       // by hklee#include <SDKDDKVer.h>       // by hklee

#include "stdafx.h"
#include "Spot.h"

void SaveBinaryImage(FILE* fp, BYTE** img, SHORT nHeight, SHORT nWidth)
{
	BYTE  IOBuf[2048+4];
	long  lBufSize = 0L;
	SHORT nBufPos = 0;
	BYTE  PixVal;
	SHORT nCnt, nWrite;
	long  lLoc;

	lLoc = ftell(fp);
	nWrite = fwrite(&lBufSize, sizeof(long), 1, fp);

	for(int y=0; y<nHeight; y++) {
		PixVal = 0;
		nCnt = 0;
		for(int x=0; x<nWidth; x++) {
			if (img[y][x] == PixVal) {
				if (nCnt == 255)	{
					IOBuf[nBufPos++] = 255;
					IOBuf[nBufPos++] = 0;
					nCnt = 0;
				}
				nCnt++;
			} else {
				IOBuf[nBufPos++] = (BYTE)nCnt;
				PixVal = img[y][x];
				nCnt = 1;
			}
			if (nBufPos >= 2048)
			{
				nWrite = fwrite(IOBuf, 1, nBufPos, fp);
				lBufSize += nBufPos;
				nBufPos = 0;
			}
		}
		IOBuf[nBufPos++] = (BYTE)nCnt;
	}

	nWrite = fwrite(IOBuf, 1, nBufPos, fp);
	lBufSize += nBufPos;

	fseek(fp, lLoc, SEEK_SET);
	nWrite = fwrite(&lBufSize, sizeof(long), 1, fp);
	fseek(fp, lBufSize, SEEK_CUR);
	lLoc = ftell(fp);
}

void LoadBinaryImage(FILE* fp, BYTE** img, SHORT nHeight, SHORT nWidth)
{
	BYTE  IOBuf[2048+4];
	long  lBufSize = 0L;
	SHORT nRead, nBufPos = 0;
	BYTE  PixVal = 0;
	int   x=0, y=0;

	fread(&lBufSize, sizeof(long), 1, fp);

	while(lBufSize > 0L)
	{
		if (lBufSize <= 2048L)
			nRead = fread(IOBuf, 1, lBufSize, fp);
		else
			nRead = fread(IOBuf, 1, 2048, fp);

		for(int i=0; i<nRead; i++)
		{
			for(int j=0; j<IOBuf[i]; j++)
				img[y][x+j] = PixVal;
			PixVal = PixVal ? 0 : 1;

			x += IOBuf[i];
			if (x >= nWidth) {
				PixVal = 0;
				x = 0;
				y++;
			} 
		}
		lBufSize -= 2048L;
	}
}

