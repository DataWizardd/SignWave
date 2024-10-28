// #include "pch.h"
#include <SDKDDKVer.h>       // by hklee

#include "stdafx.h"
#include "Spot.h"
#include "CStroke.h"
#include "CMyMIL.h"
#include "MyHand.h"
#include "utils.h"

#include <math.h>

#define MAX_LOOP		100000L

// Annotated by hklee:		1996/7/11
//===================================================================
// Usage of variables x and y
//===================================================================
//	x denotes horizontal location of pixel
//	y denotes vertical location of pixel
//
//	for the index of image bitmap
//		img[vertical_location][horizontal_location]
//		==> img[y][x]
//		** Don't confuse with the index variables i and j



//#define TIME_CHECK 1

#ifdef TIME_CHECK
#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>

double lStartTm[10];
double lElapsedTm[10];

void StartCheck(int n)
{
	struct _timeb tm;
	
	_ftime(&tm);
	lStartTm[n] = (double)tm.time * 1000. + (double)tm.millitm;
}


double EndCheck(int n)
{
	struct _timeb tm;
	
	_ftime(&tm);
	lElapsedTm[n] = (double)tm.time * 1000. + (double)tm.millitm - lStartTm[n];
	return lElapsedTm[n];
}
#endif

CMyHand::CMyHand(SHORT nWidth, SHORT nHeight)
{
	m_nWidth  = nWidth;
	m_nHeight = nHeight;
	m_bStartRecognize = FALSE;

	m_ImgBuf = MallocBYTE(3*m_nHeight*m_nWidth);
	m_savImg = MallocBYTE(MAX_FRAME, m_nHeight, m_nWidth);
	m_curImg = MallocBYTE(m_nHeight, m_nWidth);
	m_preImg = MallocBYTE(m_nHeight, m_nWidth);
	m_difImg = MallocBYTE(m_nHeight, m_nWidth);
	m_Segment= MallocBYTE(MAX_SEGMENT);

	m_Area	 = new USHORT[MAX_SEGMENT];
	m_FaceArea	 = new USHORT[MAX_SEGMENT];
	m_rcSegRect = new RECT[MAX_SEGMENT];	

	m_pStroke = new CStroke;
}

CMyHand::~CMyHand()
{
	Mfree((void*)m_ImgBuf);
	Mfree((void**)m_curImg, m_nHeight);
	Mfree((void**)m_preImg, m_nHeight);
	Mfree((void**)m_difImg, m_nHeight);
	Mfree((void*)m_Segment);

	if (m_savImg)
		Mfree((void***)m_savImg, MAX_FRAME, m_nHeight);

	Mfree((void*)m_Area);
	Mfree((void*)m_FaceArea);
	Mfree((void*)m_rcSegRect);

	Mfree((void*)m_pStroke);
}

void CMyHand::SetDumpBuffer(BOOL bDump)
{
	if (!m_savImg)
		m_savImg = MallocBYTE(MAX_FRAME, m_nHeight, m_nWidth);
}

POINT CMyHand::ContourTracing(BYTE **img, SHORT label, int sx, int sy)
{
   int x, y, d, i, tempd;
   long cnt = 0L;
   DIRECT m[8];
   POINT stop;
    
   img[sy][sx] = (BYTE)label;
   x = sx; y = sy;
 
   d=0;

   do {
	    m[5].v=img[y-1][x-1];m[6].v=img[y-1][x  ];m[7].v=img[y-1][x+1];
        m[4].v=img[y  ][x-1];                     m[0].v=img[y  ][x+1];
        m[3].v=img[y+1][x-1];m[2].v=img[y+1][x  ];m[1].v=img[y+1][x+1];
        m[5].x = x-1; m[6].x = x  ; m[7].x = x+1;
        m[4].x = x-1;               m[0].x = x+1;
        m[3].x = x-1; m[2].x = x  ; m[1].x = x+1;
        m[5].y = y-1; m[6].y = y-1; m[7].y = y-1;
        m[4].y = y  ;               m[0].y = y  ;
        m[3].y = y+1; m[2].y = y+1; m[1].y = y+1;

        tempd = d;
        for (i = 0; i < 8; i++) {
			d = (tempd + i+ 6) % 8;
            if (m[d].v>0) {
                x = m[d].x; y = m[d].y;
                if (img[y][x] > 1 && img[y][x] != (BYTE)label) {
                    stop.x=x; stop.y=y;
                    return stop;
                }
                img[y][x] = (BYTE)label;
                break;
            }
        }
		cnt++;
    } while ( (cnt < MAX_LOOP) && ((x!=sx)||(y!=sy)) );

    if (cnt >= MAX_LOOP)
	{
		//MessageBox(NULL, "ContourTracing", "Warning", MB_OK);
    	theMIL->m_bGrabStart = FALSE;
		stop.x = -1;
		stop.y = -1;
		return stop;
	}

    stop.x=0; stop.y=0;
    return stop;
}

BOOL CMyHand::BackTracing(BYTE** img, SHORT label, SHORT oldlabel, int sx, int sy)
{
   int x, y, d, tempd, i;
   long cnt = 0L;
   BOOL start = TRUE;
   DIRECT m[8];
    
   img[sy][sx] = (BYTE)label;
   x = sx; y=sy;
 
   d=0;

   do {
	    m[3].v=img[y-1][x-1];m[2].v=img[y-1][x  ];m[1].v=img[y-1][x+1];
        m[4].v=img[y  ][x-1];                     m[0].v=img[y  ][x+1];
        m[5].v=img[y+1][x-1];m[6].v=img[y+1][x  ];m[7].v=img[y+1][x+1];
        m[3].x = x-1; m[2].x = x  ; m[1].x = x+1;
        m[4].x = x-1;               m[0].x = x+1;
        m[5].x = x-1; m[6].x = x  ; m[7].x = x+1;
        m[3].y = y-1; m[2].y = y-1; m[1].y = y-1;
        m[4].y = y  ;               m[0].y = y  ;
        m[5].y = y+1; m[6].y = y+1; m[7].y = y+1;
        
		if (start)
		{
			for (d=0; d<8; d++)
				if (m[d].v == oldlabel)
					break;
			if (d >= 8)
				break;
		}

		tempd = d;
        for (i = 0; i < 8; i++) {
			if (start)
				start = FALSE;
			else
				d = (tempd + i+ 6) % 8;
            if (m[d].v) {
                x = m[d].x; y = m[d].y; 
                img[y][x] = (BYTE)label;
                break;
            }
        }
		cnt++;
    } while ( (cnt < MAX_LOOP) && ((x!=sx)||(y!=sy)) );

    if (cnt >= MAX_LOOP)
	{
		//MessageBox(NULL, "BackTracking", "Warning", MB_OK);
    	theMIL->m_bGrabStart = FALSE;	
		return FALSE;
	}

	return TRUE;
}

// 1-pass labelling
SHORT CMyHand::Labelling(BYTE** img, SHORT nHeight, SHORT nWidth, USHORT nThreshold)
{
	USHORT	Equiv[MAX_LABEL];
    int		i, x, y;
    int		label=2, segnum=1;
    POINT	stop;

	// Reset image boundaries
	// Protect finding outter area, especially for boundary tracing
	for (y=0; y<nHeight; y++) {
        img[y][0] = 0;			// top
        img[y][nWidth-1] = 0;	// bottom
    }

	memset(img[0], 0, nWidth);		// left
	memset(img[nHeight-1], 0, nWidth);// right

    for (y=1; y<nHeight-1; y++) {
        for (x=1; x<nWidth-1; x++) {
            if (img[y][x] == 1) {
                if (img[y-1][x] > 1) {
                    img[y][x] = img[y-1][x];
                } else if (img[y-1][x-1] > 1) { 
                    img[y][x] = img[y-1][x-1];
                } else if (img[y][x-1] > 1) { 
                    img[y][x] = img[y][x-1];
                } else if (img[y+1][x-1] > 1) { 
                    img[y][x] = img[y+1][x-1];
                } else {
                    stop = ContourTracing(img, label, x, y);
					if (stop.x < 0)
						return -1;
                    if (stop.x!=0 || stop.y!=0) {
                        if (!BackTracing(img, img[stop.y][stop.x], label, stop.x, stop.y))
							return -1;
	                    label++;
                    }
					else
					{
						if (img[y-1][x-1]||img[y-1][x]||img[y-1][x+1]||
							img[y  ][x-1]        ||     img[y  ][x+1]||
							img[y+1][x-1]||img[y+1][x]||img[y+1][x+1])
							label++;
						else
							img[y][x] = 0;
					}
					
					// Too many labels
					if (label >= MAX_LABEL)
						goto loop_out;
                }
            }
        }
    }

loop_out:

	m_nMaxArea = 0;
	m_n2ndMaxArea = 0;
	memset(Equiv, 0, MAX_LABEL * sizeof(USHORT));
	memset(m_Area, 0, MAX_SEGMENT * sizeof(USHORT));
	memset(m_Segment, 0, MAX_SEGMENT);

    for (y=1; y<nHeight-1; y++) { 
        for (x=1; x<nWidth-1; x++) {
			if (img[y][x] > 1)
				Equiv[img[y][x]]++;
		}
	}

    for (i=2, segnum=1; i<label; i++) {
        if (Equiv[i] > nThreshold) {
            m_Area[segnum] = Equiv[i];
			if (m_Area[segnum] > m_Area[m_nMaxArea]) {
				if (m_Area[m_nMaxArea] > m_Area[m_n2ndMaxArea])
					m_n2ndMaxArea = m_nMaxArea;
				m_nMaxArea = segnum;
			} else if (m_Area[segnum] > m_Area[m_n2ndMaxArea])
				m_n2ndMaxArea = segnum;
			Equiv[i] = segnum++;
        } else
			Equiv[i] = 0;
    }

	if (segnum == 1)
		return 0;

	SHORT nLut = 160 / (segnum-1);
	for (i=0; i<segnum; i++)
		m_Segment[i] = (BYTE)min(255, i * nLut + MIN_GRAY);

    for (y=0; y<nHeight; y++) 
        for (x=0; x<nWidth; x++)
            img[y][x] = m_Segment[ Equiv[img[y][x]] ];

    return segnum-1;
}

RECT CMyHand::FindRect(SHORT labelnum)
{
    int x, y;
    RECT rc;

    rc.left = m_nWidth;
	rc.top  = m_nHeight;
	rc.right  = 0;
	rc.bottom = 0;

    for (y=0; y<m_nHeight; y++) {
        for (x=0; x<m_nWidth; x++) {
           if (m_curImg[y][x] == m_Segment[labelnum]) {
               rc.top = y; 
               break;
           }
        }
        if (rc.top != m_nHeight) break;
    }

    for (y=m_nHeight-1; y>=0; y--) {
        for (x=0; x<m_nWidth; x++) {
           if (m_curImg[y][x] == m_Segment[labelnum]) {
               rc.bottom = y;
               break;
           }
        }
        if (rc.bottom != 0) break;
    }

    for (x=0; x<m_nWidth; x++) {
        for (y=0; y<m_nHeight; y++) {
           if (m_curImg[y][x] == m_Segment[labelnum]) {
               rc.left = x;
               break;
           }
        }
        if (rc.left != m_nWidth) break;
    }

    for (x=m_nWidth-1; x>=0; x--) {
        for (y=0; y<m_nHeight; y++) {
           if (m_curImg[y][x] == m_Segment[labelnum]) {
               rc.right = x;
               break;
           }
        }
        if (rc.right != 0) break;
    }

    return (rc);
}

void CMyHand::CurToPre()
{
	if (m_nCurHand == -1) {
#ifdef USE_MOVE_DIRECTION
		m_ptPreMove.x = 0;
		m_ptPreMove.y = 0;
#endif
		m_PreArea = 0;
		m_PreHandValue = 0;
		m_PreFaceValue = 0;
		SetRectEmpty(&m_rcPreHandRect); 
		SetRectEmpty(&m_rcPreFaceRect); 
		SetRectEmpty(&m_rcOrgFaceRect);
		m_Flags.bSetOrgRect = FALSE;
	} else {
#ifdef USE_MOVE_DIRECTION
		if (m_nPreHand > 0) {
			m_ptPreMove.x = (m_rcSegRect[m_nCurHand].left + m_rcSegRect[m_nCurHand].right) / 2
						  - (m_rcPreHandRect.left + m_rcPreHandRect.right) / 2;
			m_ptPreMove.y = (m_rcSegRect[m_nCurHand].top + m_rcSegRect[m_nCurHand].bottom) / 2
						  - (m_rcPreHandRect.top + m_rcPreHandRect.bottom) / 2;
		} else {
			m_ptPreMove.x = 0;
			m_ptPreMove.y = 0;
		}
#endif

		m_PreArea = m_Area[m_nCurHand];
		m_PreHandValue = m_Segment[m_nCurHand];
		m_PreFaceValue = m_Segment[m_nMaxArea];
		m_rcPreHandRect = m_rcSegRect[m_nCurHand];
		m_rcPreFaceRect = m_rcSegRect[m_nMaxArea];

		if ( !m_Flags.bOccluded && 
			 (m_rcPreHandRect.right < m_rcPreFaceRect.left ||
			  m_rcPreHandRect.top > m_rcPreFaceRect.bottom) ) {
			if ( m_nPreHand > 0 ) {
				m_rcOrgFaceRect = m_rcPreFaceRect;
				m_Flags.bSetOrgRect = TRUE;
			} else if ( m_nPreHand < 0 &&
				(m_rcPreFaceRect.right - m_rcPreFaceRect.left) <
				(m_rcPreFaceRect.bottom - m_rcPreFaceRect.top) ) {
				m_rcOrgFaceRect = m_rcPreFaceRect;
				m_Flags.bSetOrgRect = TRUE;
			}
		}
	}

	m_nPreHand = m_nCurHand;

	for(int i=0; i<m_nHeight; i++)
		memcpy(m_preImg[i], m_curImg[i], m_nWidth);
}

long CMyHand::Boundary(BYTE** img, SHORT nHand)
{
    long length = 0L;
    int  x, y;
	BYTE val;
    RECT rc;

    rc  = m_rcSegRect[nHand];
	val = m_Segment[nHand];

    for (y=rc.top; y<=rc.bottom; y++)
        for (x=rc.left; x<=rc.right; x++)
            if (img[y][x] == val)
			{
				if (img[y-1][x-1]!=val||img[y-1][x]!=val||img[y-1][x+1]!=val||
					img[y  ][x-1]!=val          ||        img[y  ][x+1]!=val||
					img[y+1][x-1]!=val||img[y+1][x]!=val||img[y+1][x+1]!=val)
					length++;
			}
 
    return length;
}
 
float CMyHand::Compactness(SHORT nHand)
{
	long  area;
	float compact;
	RECT rc = m_rcSegRect[nHand];

	area = m_Area[nHand];
	long bound = (long)(rc.right - rc.left + 1) 
				* (long)(rc.bottom - rc.top + 1);

	if (bound <= 5000L)
		compact = (float)area / (float)bound;
	else
		compact = (float)1.0;
 
    return (compact);
}
 
float CMyHand::Elongatedness(SHORT nHand)
{
    float elong, sizex, sizey;
    RECT rc;

    rc = m_rcSegRect[nHand];
 
    sizex = (float)(rc.right - rc.left);
    sizey = (float)(rc.bottom - rc.top);
 
    if (sizex > sizey)
       elong = sizex / sizey;
    else
       elong = -sizey / sizex;

    return (elong);
}

POINT CMyHand::Centroid(SHORT nHand)
{
    int x, y;
	long sumx, sumy, sump;
    POINT center;
    RECT rc;

    rc = m_rcSegRect[nHand];
 
    sumx = sumy = sump = 0;
 
    for (y=rc.top; y<=rc.bottom; y++) {
	    for (x=rc.left; x<=rc.right; x++) {
            if (m_curImg[y][x] == m_Segment[nHand]) {
               sumx += x;
               sumy += y;
               sump++;
            }
        }
    }
 
    center.x = sumx / sump;
    center.y = sumy / sump;
 
    return (center);
}

#define DIR_LEFT		0
#define DIR_TOP			1
#define DIR_RIGHT		2
#define DIR_BOTTOM		3
#define DIR_NOTHING		4

#define DIFF_THRESH		3
#define SIZE_THRESH		8

void CMyHand::ChangeHandPixel()
{
	int tmpx, tmpy;
	int nPreWid =	m_rcPreHandRect.right - m_rcPreHandRect.left;
	int nPreHt  =	m_rcPreHandRect.bottom - m_rcPreHandRect.top;

	for(int y=0; y<=nPreHt; y++) {
		for(int x=0; x<=nPreWid; x++) {
			if (m_preImg[y+m_rcPreHandRect.top][x+m_rcPreHandRect.left] == m_PreHandValue) {
				tmpy = y + m_rcSegRect[2].top;
				tmpx = x + m_rcSegRect[2].left;
				if (//tmpx >=0 && tmpx < m_nWidth && 
					//tmpy >= 0 && tmpy < m_nHeight &&
					tmpx >= m_rcSegRect[2].left && tmpx <= m_rcSegRect[2].right &&
					tmpy >= m_rcSegRect[2].top && tmpy <= m_rcSegRect[2].bottom)
					m_curImg[tmpy][tmpx] = m_Segment[2];
			}
		}
	}
}

BOOL CMyHand::HandFromPreFace()
{
	int diff[4], abs_diff, lt_diff, rb_diff;
	int nDir = -1; 
	int nDiff = 0;

	diff[0] = m_rcPreFaceRect.left - m_rcSegRect[m_nMaxArea].left;
	diff[1] = m_rcPreFaceRect.top - m_rcSegRect[m_nMaxArea].top;
	diff[2] = m_rcPreFaceRect.right - m_rcSegRect[m_nMaxArea].right;
	diff[3] = m_rcPreFaceRect.bottom - m_rcSegRect[m_nMaxArea].bottom;

	for(int i=0; i<4; i++) {
		abs_diff = abs(diff[i]);
		if (abs_diff > DIFF_THRESH && abs_diff > abs(nDiff)) {
			nDir = i;
			nDiff = diff[i];
		}
	}

	m_nNumSeg = 2;
	m_n2ndMaxArea = 2;
	m_rcSegRect[2] = m_rcPreHandRect;
	m_Segment[2] = MIN_GRAY + 80;
	m_Area[2] = m_PreArea;
	
	int nPreWid =	m_rcPreHandRect.right - m_rcPreHandRect.left;
	int nPreHt  =	m_rcPreHandRect.bottom - m_rcPreHandRect.top;

	switch(nDir) {
		case DIR_LEFT:
			m_rcSegRect[2].left = m_rcSegRect[1].left;
		case DIR_RIGHT:
			if (nDir == DIR_RIGHT)
				m_rcSegRect[2].left = max(0, m_rcSegRect[1].right - nPreWid);
			m_rcSegRect[2].right = min(m_nWidth-1, m_rcSegRect[2].left + nPreWid);

			if (abs(diff[DIR_TOP]) > DIFF_THRESH || abs(diff[DIR_BOTTOM]) > DIFF_THRESH) {
				if ( abs(diff[DIR_TOP]) > abs(diff[DIR_BOTTOM]) )
					m_rcSegRect[2].top = m_rcSegRect[1].top;
				else
					m_rcSegRect[2].top = max(0, m_rcSegRect[1].bottom - nPreHt);
				m_rcSegRect[2].bottom = min(m_nHeight-1, m_rcSegRect[2].top + nPreHt);
			} else {
				lt_diff = m_rcPreHandRect.top - m_rcPreFaceRect.top;
				rb_diff = m_rcPreHandRect.bottom - m_rcPreFaceRect.bottom;
				if (rb_diff > 0) {
					if (lt_diff > 0 || abs(rb_diff) > abs(lt_diff))
						m_rcSegRect[2].top = max(0, m_rcSegRect[1].bottom-nPreHt);
					else
						m_rcSegRect[2].top = m_rcSegRect[1].top;
				} else {
					if (lt_diff < 0 || abs(rb_diff) > abs(lt_diff))
						m_rcSegRect[2].top = m_rcSegRect[1].top;
					else
						m_rcSegRect[2].top = max(0, m_rcSegRect[1].bottom-nPreHt);
				}
				m_rcSegRect[2].bottom = min(m_nHeight-1, m_rcSegRect[2].top+nPreHt);
			}
			break;
		case DIR_TOP:
			m_rcSegRect[2].top = m_rcSegRect[1].top;
		case DIR_BOTTOM:
			if (nDir == DIR_BOTTOM)
				m_rcSegRect[2].top = max(0, m_rcSegRect[1].bottom - nPreHt);
			m_rcSegRect[2].bottom = min(m_nHeight-1, m_rcSegRect[2].top + nPreHt);

			if (abs(diff[DIR_LEFT]) > DIFF_THRESH || abs(diff[DIR_RIGHT]) > DIFF_THRESH) {
				if ( abs(diff[DIR_LEFT]) > abs(diff[DIR_RIGHT]) )
					m_rcSegRect[2].left = m_rcSegRect[1].left;
				else
					m_rcSegRect[2].left = max(0, m_rcSegRect[1].right - nPreWid);
				m_rcSegRect[2].right = min(m_nWidth-1, m_rcSegRect[2].left+nPreWid);
			} else {
				lt_diff = m_rcPreHandRect.left - m_rcPreFaceRect.left;
				rb_diff = m_rcPreHandRect.right - m_rcPreFaceRect.right;
				if (rb_diff > 0) {
					if (lt_diff > 0 || abs(rb_diff) > abs(lt_diff))
						m_rcSegRect[2].left = max(0, m_rcSegRect[1].right-nPreWid);
					else
						m_rcSegRect[2].left = m_rcSegRect[1].left;
				} else {
					if (lt_diff < 0 || abs(rb_diff) > abs(lt_diff))
						m_rcSegRect[2].left = m_rcSegRect[1].left;
					else
						m_rcSegRect[2].left = max(0, m_rcSegRect[1].right-nPreWid);
				}
				m_rcSegRect[2].right = min(m_nWidth-1, m_rcSegRect[2].left+nPreWid);
			}
			break;
	}

	ChangeHandPixel();

	return TRUE;
}

void CMyHand::GetCornerOfHand( int nDir, SHORT nSize )
{
	int	x, y;
	int nSX, nEX, nSY, nEY;
	int nStart = -1, nEnd = -1;
	int n1st = -1, nLast = -1;

	switch (nDir) {
		case DIR_LEFT:
			nSX = m_rcSegRect[1].left;
			nEX = m_rcOrgFaceRect.left - 1;
		case DIR_RIGHT:
			if (nDir == DIR_RIGHT) {
				nSX = m_rcOrgFaceRect.right+1;
				nEX = m_rcSegRect[1].right;
			}
			nSY = m_rcSegRect[1].top;
			nEY = m_rcSegRect[1].bottom;

			for(y=nSY; y<=nEY; y++) {
				for(x=nSX; x<=nEX; x++) {
					if (m_curImg[y][x] > MIN_GRAY) {
						if (nStart == -1) 
							nStart = y;
						if ( (nDir == DIR_LEFT && x == nSX) || (nDir == DIR_RIGHT && x == nEX) ) {
							if (n1st == -1)
								n1st = y;
							nLast = y;
						}
						nEnd = y;
					}
				}
			}

			if (abs(nStart - n1st) + DIFF_THRESH < abs(nEnd - nLast)) {
				m_rcSegRect[2].top = nStart;
				m_rcSegRect[2].bottom = min(m_rcSegRect[1].bottom, m_rcSegRect[2].top + nSize);
			} else if (abs(nStart - n1st) > abs(nEnd - nLast) + DIFF_THRESH) {
				m_rcSegRect[2].bottom = nEnd;
				m_rcSegRect[2].top = max(m_rcSegRect[1].top, m_rcSegRect[2].bottom - nSize);
			} else {
				if ((nLast + n1st) / 2 > (m_rcSegRect[1].top + m_rcSegRect[1].bottom) / 2) {
					m_rcSegRect[2].bottom = nEnd;
					m_rcSegRect[2].top = max(m_rcSegRect[1].top, m_rcSegRect[2].bottom - nSize);
				} else {
					m_rcSegRect[2].top = nStart;
					m_rcSegRect[2].bottom = min(m_rcSegRect[1].bottom, m_rcSegRect[2].top + nSize);
				}
			}
			break;

		case DIR_TOP:
			nSY = m_rcSegRect[1].top;
			nEY = m_rcOrgFaceRect.top - 1;
		case DIR_BOTTOM:
			if (nDir == DIR_BOTTOM) {
				nSY = m_rcOrgFaceRect.bottom+1;
				nEY = m_rcSegRect[1].bottom;
			}
			nSX = m_rcSegRect[1].left;
			nEX = m_rcSegRect[1].right;

			for(x=nSX; x<=nEX; x++) {
				for(y=nSY; y<=nEY; y++) {
					if (m_curImg[y][x] > MIN_GRAY) {
						if (nStart == -1) 
							nStart = x;
						if ( (nDir == DIR_TOP && y == nSY) || (nDir == DIR_BOTTOM && y == nEY) ) {
							if (n1st == -1)
								n1st = x;
							nLast = x;
						}
						nEnd = y;
					}
				}
			}

			if (abs(nStart - n1st) + DIFF_THRESH < abs(nEnd - nLast)) {
				m_rcSegRect[2].left = nStart;
				m_rcSegRect[2].right = min(m_rcSegRect[1].right, m_rcSegRect[2].left + nSize);
			} else if (abs(nStart - n1st) > abs(nEnd - nLast) + DIFF_THRESH) {
				m_rcSegRect[2].right = nEnd;
				m_rcSegRect[2].left = max(m_rcSegRect[1].left, m_rcSegRect[2].right - nSize);
			} else {
				if ((nLast + n1st) / 2 > (m_rcSegRect[1].left + m_rcSegRect[1].right) / 2) {
					m_rcSegRect[2].right = nEnd;
					m_rcSegRect[2].left = max(m_rcSegRect[1].left, m_rcSegRect[2].right - nSize);
				} else {
					m_rcSegRect[2].left = nStart;
					m_rcSegRect[2].right = min(m_rcSegRect[1].right, m_rcSegRect[2].left + nSize);
				}
			}
			break;
	}
}

BOOL CMyHand::HandFromOrgFace()
{
	int diff[4], max_diff;
	int nDir = -1; 

	diff[0] = m_rcOrgFaceRect.left - m_rcSegRect[m_nMaxArea].left;
	diff[1] = m_rcOrgFaceRect.top - m_rcSegRect[m_nMaxArea].top;
	diff[2] = m_rcSegRect[m_nMaxArea].right - m_rcOrgFaceRect.right;
	diff[3] = m_rcSegRect[m_nMaxArea].bottom - m_rcOrgFaceRect.bottom;

	nDir = DIR_NOTHING;
	max_diff = -1;
	for(int i=0; i<4; i++) {
		if (diff[i] < 0) diff[i] = 0;
		if (diff[i] > DIFF_THRESH && diff[i] > max_diff) {
			nDir = i;
			max_diff = diff[i];
		}
	}

	m_nNumSeg = 2;
	m_n2ndMaxArea = 2;
	m_rcSegRect[2] = m_rcSegRect[1];
	m_Segment[2] = MIN_GRAY + 80;
	m_Area[2] = m_PreArea;

	int nPreWid =	m_rcPreHandRect.right - m_rcPreHandRect.left;
	int nPreHt  =	m_rcPreHandRect.bottom - m_rcPreHandRect.top;

	switch(nDir) {
		case DIR_LEFT:
		case DIR_RIGHT:
			if (nDir == DIR_RIGHT)
				m_rcSegRect[2].left = max(0, m_rcSegRect[1].right - nPreWid);
			m_rcSegRect[2].right = min(m_nWidth-1, m_rcSegRect[2].left + nPreWid);
			if (diff[DIR_TOP] > DIFF_THRESH || diff[DIR_BOTTOM] > DIFF_THRESH) {
				if (diff[DIR_TOP] < diff[DIR_BOTTOM])
					m_rcSegRect[2].top = max(0, m_rcSegRect[1].bottom - nPreHt); 
				else
					m_rcSegRect[2].bottom = min(m_nHeight-1, m_rcSegRect[2].top + nPreHt);
			} else {
#ifdef USE_MOVE_DIRECTION
				m_rcSegRect[2].top = m_rcPreHandRect.top + m_ptPreMove.y;
				m_rcSegRect[2].bottom = m_rcPreHandRect.bottom + m_ptPreMove.y;
				if (m_ptPreMove.y < 0) {
					m_rcSegRect[2].top = max(m_rcSegRect[1].top, m_rcSegRect[2].top);
					m_rcSegRect[2].bottom = min(m_nHeight-1, m_rcSegRect[2].top + nPreHt);
				} else if (m_ptPreMove.y > 0) {
					m_rcSegRect[2].bottom = min(m_rcSegRect[1].bottom, m_rcSegRect[2].bottom);
					m_rcSegRect[2].top = max(0, m_rcSegRect[2].bottom - nPreHt); 
				}
#else
				GetCornerOfHand( nDir, nPreHt );
#endif
			}
			break;
		case DIR_TOP:
		case DIR_BOTTOM:
			if (nDir == DIR_BOTTOM)
				m_rcSegRect[2].top = max(0, m_rcSegRect[1].bottom - nPreHt);
			m_rcSegRect[2].bottom = min(m_nHeight-1, m_rcSegRect[2].top + nPreHt);
			if (diff[DIR_LEFT] > DIFF_THRESH || diff[DIR_RIGHT] > DIFF_THRESH) {
				if (diff[DIR_LEFT] < diff[DIR_RIGHT])
					m_rcSegRect[2].left = max(0, m_rcSegRect[1].right - nPreWid); 
				else
					m_rcSegRect[2].right = min(m_nWidth-1, m_rcSegRect[2].left + nPreWid);
			} else {
#ifdef USE_MOVE_DIRECTION
				m_rcSegRect[2].left = m_rcPreHandRect.left + m_ptPreMove.x;
				m_rcSegRect[2].right = m_rcPreHandRect.right + m_ptPreMove.x;
				if (m_ptPreMove.x < 0) {
					m_rcSegRect[2].left = max(m_rcSegRect[1].left, m_rcSegRect[2].left);
					m_rcSegRect[2].right = min(m_nHeight-1, m_rcSegRect[2].left + nPreHt);
				} else if (m_ptPreMove.x > 0) {
					m_rcSegRect[2].right = min(m_rcSegRect[1].right, m_rcSegRect[2].right);
					m_rcSegRect[2].left = max(0, m_rcSegRect[2].right - nPreHt); 
				}
#else
				GetCornerOfHand( nDir, nPreWid );
#endif
			}
			break;
		default:
			m_rcSegRect[2] = m_rcPreHandRect;
			if (m_rcPreHandRect.left < m_rcSegRect[1].left) {
				m_rcSegRect[2].left = m_rcSegRect[1].left;
				m_rcSegRect[2].right = min(m_rcSegRect[1].right, m_rcSegRect[1].left + nPreWid);
			} else if (m_rcPreHandRect.right > m_rcSegRect[1].right) {
				m_rcSegRect[2].right = m_rcSegRect[1].right;
				m_rcSegRect[2].left = max(m_rcSegRect[1].left, m_rcSegRect[1].right - nPreWid);
			}

			if (m_rcPreHandRect.top < m_rcSegRect[1].top) {
				m_rcSegRect[2].top = m_rcSegRect[1].top;
				m_rcSegRect[2].bottom = min(m_rcSegRect[1].bottom, m_rcSegRect[1].top + nPreHt);
			} else if (m_rcPreHandRect.bottom > m_rcSegRect[1].bottom) {
				m_rcSegRect[2].bottom = m_rcSegRect[1].bottom;
				m_rcSegRect[2].top = max(m_rcSegRect[1].top, m_rcSegRect[1].bottom - nPreHt);
			}
			break;
	}

	ChangeHandPixel();

	return TRUE;
}

BOOL CMyHand::IsFaceChanged()
{
	if (m_nPreHand < 1 || IsRectEmpty(&m_rcPreHandRect))
		return FALSE;

	// Compare with previous face because when hand move across the face,
	//				some part of face is overlapped
	int nPreWid =	m_rcPreFaceRect.right - m_rcPreFaceRect.left;
	int nPreHt  =	m_rcPreFaceRect.bottom - m_rcPreFaceRect.top;
	int nNewWid =	m_rcSegRect[m_nMaxArea].right - m_rcSegRect[m_nMaxArea].left;
	int nNewHt  =	m_rcSegRect[m_nMaxArea].bottom - m_rcSegRect[m_nMaxArea].top;

	if (abs(nPreWid - nNewWid) > SIZE_THRESH || abs(nPreHt - nNewHt) > SIZE_THRESH)
		return TRUE;

	return FALSE;
}

SHORT GetOverlappingPercent(RECT* prcOrg, RECT* prcNew )
{
	RECT rcTmp;
	int nOrg, nNew;

	IntersectRect(&rcTmp, prcOrg, prcNew);
	nOrg = (rcTmp.right - rcTmp.left) * (rcTmp.bottom - rcTmp.top);
	nNew = (prcNew->right - prcNew->left) * (prcNew->bottom - prcNew->top);

	return (SHORT)((nOrg * 100) / nNew);
}

void CMyHand::GetPixelsInOrgFace()
{
	memset(m_FaceArea, 0, sizeof(SHORT)*MAX_SEGMENT);
	for(int y=m_rcOrgFaceRect.top; y<=m_rcOrgFaceRect.bottom; y++) {
		for(int x=m_rcOrgFaceRect.left; x<=m_rcOrgFaceRect.right; x++) {
			if (m_curImg[y][x] > MIN_GRAY) {
				for(int i=1; i<=m_nNumSeg; i++) {
					if (m_curImg[y][x] == m_Segment[i]) {
						m_FaceArea[i]++;
						break;
					}
				}
			}
		}
	}
}

SHORT CMyHand::FindHand(SHORT nHand)
{
	int nNewHand;

	if (m_nNumSeg == 1) {
Find_Again:
		if (m_Flags.bNearFace || (m_nPreHand > 0 && IsFaceChanged())) {
			m_Flags.bOccluded = TRUE;
			m_Flags.bNearFace = TRUE;

			if (!m_Flags.bSetOrgRect || !HandFromOrgFace())
				HandFromPreFace();
			nNewHand = m_n2ndMaxArea;
		} else {
			m_Flags.bOccluded = FALSE;
			m_Flags.bNearFace = FALSE;
			nNewHand = -1;
		}
	} else {
		RECT rcFace, rcHand;

		if (m_Flags.bSetOrgRect) {
			SHORT nMinPercent = GetOverlappingPercent( &m_rcOrgFaceRect, 
													   &m_rcSegRect[m_n2ndMaxArea] );
			SHORT nPercent = GetOverlappingPercent( &m_rcOrgFaceRect, 
													&m_rcSegRect[m_nMaxArea] );
			if (nPercent < 70 || nPercent < nMinPercent) {
				GetPixelsInOrgFace();
#ifdef OLD_HEURISTICS
				nPercent = ((100*(int)m_FaceArea[m_nMaxArea]) / (int)m_Area[m_nMaxArea]);
				if (nPercent < 30) {
					m_n2ndMaxArea = m_nMaxArea;
					m_nMaxArea = 0;
					for(int i=1; i<=m_nNumSeg; i++) {
						if (m_FaceArea[i] > m_FaceArea[m_nMaxArea])
							m_nMaxArea = i;
					}
					// In some cases, m_nMaxArea is zero
					// If m_nMaxArea is zero, system is halted
					if (m_nMaxArea == 0) {
						if (m_n2ndMaxArea == 1)
							m_nMaxArea = 2;
						else
							m_nMaxArea = 1;
					}
				} else {
					nPercent = ((100*(int)m_FaceArea[m_n2ndMaxArea]) / (int)m_Area[m_n2ndMaxArea]);
					if (nPercent > 95 && m_nNumSeg == 2) {
						m_nNumSeg = 1;
						goto Find_Again;
					}
				}
#else
				SHORT n1stMax, n2ndMax;

				n1stMax = ( (100*(int)m_FaceArea[m_nMaxArea]) 
								/ (int)m_Area[m_nMaxArea] );
				n2ndMax = ( (100*(int)m_FaceArea[m_n2ndMaxArea]) 
								/ (int)m_Area[m_n2ndMaxArea] );
				if (m_nNumSeg == 2) {
					if (n2ndMax > 80) {
						if (n1stMax >= 30) {
							m_nNumSeg = 1;
							if (m_nMaxArea != 1) {
								m_Area[1] = m_Area[m_nMaxArea];
								m_rcSegRect[1] = m_rcSegRect[m_nMaxArea];
								m_Segment[1] = m_Segment[m_nMaxArea];
							}
							goto Find_Again;
						} else {
							SHORT nTmp = m_nMaxArea;

							m_nMaxArea = m_n2ndMaxArea;
							m_n2ndMaxArea = nTmp;
						}
					}
				} else {
					if (n1stMax < 30) {
						m_n2ndMaxArea = m_nMaxArea;
						m_nMaxArea = 0;
						for(int i=1; i<=m_nNumSeg; i++) {
							if (i!=m_n2ndMaxArea && m_FaceArea[i] > m_FaceArea[m_nMaxArea])
								m_nMaxArea = i;
						}
						// In some cases, m_nMaxArea is zero
						// If m_nMaxArea is zero, system is halted
						if (m_nMaxArea == 0) {
							if (m_n2ndMaxArea == 1)
								m_nMaxArea = 2;
							else
								m_nMaxArea = 1;
						}
					}
				}
#endif
			}
		}

		CopyRect(&rcFace, &m_rcSegRect[m_nMaxArea]);
		CopyRect(&rcHand, &m_rcSegRect[m_n2ndMaxArea]);

		if (m_nPreHand > 0 && m_nCurHand > 0) {
			POINT ptPre, ptCur;

			ptPre.x = (m_rcPreHandRect.left + m_rcPreHandRect.right) / 2; 
			ptPre.y = (m_rcPreHandRect.top + m_rcPreHandRect.bottom) / 2; 
			ptCur.x = (rcHand.left + rcHand.right) / 2; 
			ptCur.y = (rcHand.top + rcHand.bottom) / 2; 

			// Consider moving direction
			if (abs(ptPre.x - ptCur.x) > DIFF_THRESH) {
				if (ptPre.x > ptCur.x)
					rcHand.left -= 20;
				else if (ptPre.x < ptCur.x)
					rcHand.right += 20;
			}
			if (abs(ptPre.y - ptCur.y) > DIFF_THRESH) {
				if (ptPre.y > ptCur.y)
					rcHand.top -= 20;
				else if (ptPre.y < ptCur.y)
					rcHand.bottom += 20;
			}
		}
		InflateRect(&rcHand, 10, 10);
		m_Flags.bNearFace = IntersectRect(&rcFace, &rcFace, &rcHand);

		m_Flags.bOccluded = FALSE;
		nNewHand = m_n2ndMaxArea;
	}

	return nNewHand;
}

void CMyHand::MarkHand(BYTE** img, RECT *prc, BYTE gray)
{
	int	i;

	for(i=prc->left; i<=prc->right; i++) {
		img[prc->top][i] = gray;
		img[prc->bottom][i] = gray;

#ifdef SHOW_COLOR_IMAGE
		m_ImgBuf[prc->top*m_nWidth + i] = gray;
		m_ImgBuf[(prc->top+m_nHeight)*m_nWidth + i] = gray;
		m_ImgBuf[(prc->top+2*m_nHeight)*m_nWidth + i] = gray;

		m_ImgBuf[prc->bottom*m_nWidth + i] = gray;
		m_ImgBuf[(prc->bottom+m_nHeight)*m_nWidth + i] = gray;
		m_ImgBuf[(prc->bottom+2*m_nHeight)*m_nWidth + i] = gray;
#endif
	}

	for(i=prc->top; i<=prc->bottom; i++) {
		img[i][prc->left] = gray;
		img[i][prc->right] = gray;

#ifdef SHOW_COLOR_IMAGE
		m_ImgBuf[i*m_nWidth + prc->left] = gray;
		m_ImgBuf[(i+m_nHeight)*m_nWidth + prc->left] = gray;
		m_ImgBuf[(i+2*m_nHeight)*m_nWidth + prc->left] = gray;

		m_ImgBuf[i*m_nWidth + prc->right] = gray;
		m_ImgBuf[(i+m_nHeight)*m_nWidth + prc->right] = gray;
		m_ImgBuf[(i+2*m_nHeight)*m_nWidth + prc->right] = gray;
#endif
	}
}

#ifdef DIFF_IMAGE
SHORT CMyHand::GetMaxSegmentRect()
{
	SHORT i, maxidx = 0;
	long  lcur, lmax = 0;

	for(i=1; i<=m_nNumSeg; i++)
	{
		lcur = (m_rcSegRect[i].right - m_rcSegRect[i].left + 1)
			 * (m_rcSegRect[i].bottom - m_rcSegRect[i].top + 1);

		if (lcur > lmax)
		{
			maxidx = i;
			lmax = lcur;
		}
	}
	
	return maxidx;
}

void CMyHand::SetFaceDiffImage()
{
	SHORT idx = GetMaxSegmentRect();

	if (idx < 1) 
		return;

	for(int y=m_rcSegRect[idx].top; y<=m_rcSegRect[idx].bottom; y++)
		for(int x=m_rcSegRect[idx].left; x<=m_rcSegRect[idx].right; x++)
		{
			if ( (m_curImg[y][x] == m_Segment[idx] && m_preImg[y][x] == MIN_GRAY) ||
				 (m_curImg[y][x] != m_Segment[idx] && m_preImg[y][x] > MIN_GRAY) )
				m_difImg[y][x] = m_Segment[idx];
			else
				m_difImg[y][x] = 0;
		}
}
#endif


#ifdef YIQ_COLOR

void CMyHand::DumpFrame(BYTE** img)
{ 
	int		tmpx, tmpy, x, y;
	int		nHalfWid = m_nWidth / 2;
	int		nHalfHt  = m_nHeight / 2;
	BYTE*	pBuf;

	if (theApp.m_Flags.bGetGray) {
		if (theApp.m_Flags.bGetY) {
			pBuf = m_ImgBuf;

			for(y=0; y<m_nHeight; y++)
				for(x=0; x<m_nWidth; x++)
					img[y][x] = *pBuf++;
		} else {
			pBuf = &m_ImgBuf[(m_nHeight+nHalfHt)*m_nWidth];

			for(y=0; y<nHalfHt; y++) {
				for(x=0; x<nHalfWid; x++) {
					tmpx = x << 1;
					tmpy = y << 1;

					img[tmpy][tmpx]  = img[tmpy][tmpx+1]  = pBuf[x];
					img[tmpy+1][tmpx]= img[tmpy+1][tmpx+1]= pBuf[nHalfWid+x];
				}
				pBuf += m_nWidth;
			}
		}
	} else {
		pBuf = &m_ImgBuf[(m_nHeight+nHalfHt)*m_nWidth];

		for(y=0; y<nHalfHt; y++) {
			for(x=0; x<nHalfWid; x++) {
				tmpx = x << 1;
				tmpy = y << 1;

				img[tmpy][tmpx] = img[tmpy][tmpx+1] 
						= (pBuf[x] & 0x80) ? 1 : 0;
				img[tmpy+1][tmpx] = img[tmpy+1][tmpx+1] 
						= (pBuf[nHalfWid+x] & 0x80) ? 1 : 0;
			}
			pBuf += m_nWidth;
		}
	}
}

#else

#	define	GET_I_COMPONENT		1
#	define	BIN_THRESHOLD		0x80
#	define	MIN_BIN_THRESHOLD	0x40 
#	define	MAX_BIN_THRESHOLD	0x80

void CMyHand::DumpFrame(BYTE** img)
{ 
	int		x, y;
	int		nHalfWid = m_nWidth / 2;
	int		nHalfHt  = m_nHeight / 2;
	BYTE	*pRbuf, *pGbuf, *pBbuf;
	long	lR, lG, lB, lAdd, lDiv;

	pRbuf = m_ImgBuf;
	pGbuf = &m_ImgBuf[m_nHeight*m_nWidth];
	pBbuf = &m_ImgBuf[m_nHeight*m_nWidth*2];

	if (theApp.m_Flags.bGetGray) {
		if (theApp.m_Flags.bGetY) {	// Y-component
			// R: 0.30, G: 0.59, B: 0.11
			// ((R + 4.5907G + 0.0601B) * 1.45568) + 0.5
			lR = 30; lG = 59; lB = 11;
			lAdd = 0; lDiv = 25500;
		} else {
#ifdef GET_I_COMPONENT
			// I-component
			// R: 0.60, G: -0.27, B: -0.32
			// Min: -150.45,  Max: +153.00
			lR = 60; lG = -27; lB = -32;
			lAdd = 15045;		// -150.45 * 100
			lDiv = 30345;		// (150.45 + 153.00) * 100
#else
			// Q-component
			// R: 0.21, G: -0.52, B: 0.31
			// Min: -132.60,  Max: +132.60
			lR = 21; lG = -52; lB = 31;
			lAdd = 13260;		// -132.60 * 100
			lDiv = 26520;		// (132.60 + 132.60) * 100
#endif
		}

		for(y=0; y<m_nHeight; y++) {
			for(x=0; x<m_nWidth; x++) {
				img[y][x]
					= (BYTE) (((lR*(*pRbuf) + lG*(*pGbuf) + lB*(*pBbuf) + lAdd) 
								* 255L) / lDiv);
				pRbuf++; pGbuf++; pBbuf++;
			}
		}
	} else {
#ifdef GET_I_COMPONENT
		// I-component
		// R: 0.60, G: -0.27, B: -0.32
		// Min: -150.45,  Max: +153.00
		lR = 60; lG = -27; lB = -32;
		lAdd = 15045;		// -150.45 * 100
		lDiv = 30345;		// (150.45 + 153.00) * 100
#else
		// Q-component
		// R: 0.21, G: -0.52, B: 0.31
		// Min: -132.60,  Max: +132.60
		lR = 21; lG = -52; lB = 31;
		lAdd = 13260;		// -132.60 * 100
		lDiv = 26520;		// (132.60 + 132.60) * 100
#endif

#ifdef DEBUGGING_CODE
		BYTE cTmp;
#endif

		for(y=0; y<m_nHeight; y++) {
			for(x=0; x<m_nWidth; x++) {
#ifdef DEBUGGING_CODE
				cTmp = (BYTE)(((lR*(*pRbuf) + lG*(*pGbuf) + lB*(*pBbuf) + lAdd) 
							* 255L) / lDiv);
				img[y][x] 
					= ( cTmp >= MIN_BIN_THRESHOLD && cTmp <= MAX_BIN_THRESHOLD) ? 255 : 0;
#else
				img[y][x] 
					= ( (((lR*(*pRbuf) + lG*(*pGbuf) + lB*(*pBbuf) + lAdd) 
							* 255L) / lDiv) >= BIN_THRESHOLD) ? 1 : 0;
#endif
				pRbuf++; pGbuf++; pBbuf++;
			}
		}
	}
}

#endif


POINT CMyHand::Recognize(SHORT nCurFrame)
{
	POINT pt = {-1, -1};
	int	  i;

	m_nNumSeg = Labelling(m_curImg, m_nHeight, m_nWidth, SEG_THRESH);

#ifdef DEBUGGING_CODE
	return pt;
#endif

	if (m_nNumSeg < 1)
		return pt;

	for (int i=1; i<=m_nNumSeg; i++)
		m_rcSegRect[i] = FindRect(i);

	if (m_bFirst) {
		m_nCurHand = -1;
		m_bFirst = FALSE;
		m_Flags.bNearFace = FALSE;
		m_Flags.bOccluded = FALSE;
		m_Flags.bSetOrgRect = FALSE;
		SetRectEmpty(&m_rcOrgFaceRect);
		CurToPre();
	}

	m_nCurHand = FindHand(m_nPreHand);

	if (m_nCurHand > 0) {
		pt.x = (m_rcSegRect[m_nCurHand].left + m_rcSegRect[m_nCurHand].right) / 2;
		pt.y = (m_rcSegRect[m_nCurHand].top + m_rcSegRect[m_nCurHand].bottom) / 2;
		pt.x = m_nWidth - pt.x;	// frame image is mirrored image
		if (m_bStartRecognize)
			m_pStroke->AddHandPosition( pt, nCurFrame );
	}

#ifdef DIFF_IMAGE
	for(i=0; i<m_nHeight; i++)
		memcpy(m_difImg[i], m_curImg[i], m_nWidth);
	SetFaceDiffImage();
#endif

	CurToPre();

#ifdef DIFF_IMAGE
	for(i=0; i<m_nHeight; i++)
		memcpy(m_curImg[i], m_difImg[i], m_nWidth);
#endif

#ifdef HK_DEBUG
	for(i=1; i<=m_nNumSeg; i++) {
		if (i == m_nCurHand)
			MarkHand(m_curImg, &m_rcSegRect[i], 255);
		else
			MarkHand(m_curImg, &m_rcSegRect[i], 160);
	}
#endif

	return pt;
}
