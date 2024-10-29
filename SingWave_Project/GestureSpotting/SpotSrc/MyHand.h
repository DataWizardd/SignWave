#define HK_DEBUG
//#define DIFF_IMAGE		1

#define MAX_LABEL		1000
#define MIN_GRAY		96
#define MAX_SEGMENT		48
#define SEG_THRESH		200	//350
#define MAX_RECT		30

#define FAR_DIST		1000
#define NEAR_DIST		50

typedef struct tagDIRECT {
	int v;
	int x, y;
} DIRECT;

class CMyHand
{
public:
	BYTE*	m_ImgBuf;
	BYTE***	m_savImg;
	BYTE**	m_curImg;
	BYTE**	m_preImg;
	BYTE**	m_difImg;
	class CStroke* m_pStroke;
	BOOL	m_bFirst;
	BOOL	m_bStartRecognize;
	SHORT	m_nCurFrame;
	SHORT	m_nWidth;
	SHORT	m_nHeight;
	SHORT	m_nPreHand;
	SHORT	m_nCurHand;

protected:
	USHORT*	m_Area;
	USHORT*	m_FaceArea;	// Number of segment pixels in OrgFaceRect
	RECT*	m_rcSegRect;
	BYTE*	m_Segment;
#ifdef USE_MOVE_DIRECTION
	POINT	m_ptPreMove;
#endif
	RECT	m_rcPreHandRect;
	RECT	m_rcPreFaceRect;
	RECT	m_rcOrgFaceRect;
	struct {
		BOOL	bNearFace: 2;
		BOOL	bOccluded: 2;
		BOOL	bSetOrgRect: 2;
	} m_Flags;
	USHORT	m_PreArea;
	SHORT	m_nNumSeg;
	SHORT	m_nMaxArea;		// assumed as face
	SHORT	m_n2ndMaxArea;
	BYTE	m_PreHandValue;
	BYTE	m_PreFaceValue;

public:
	CMyHand(SHORT nWidth, SHORT nHeight);
	~CMyHand();
	void	SetDumpBuffer(BOOL bDump);

	long	Boundary(BYTE** img, SHORT nHand);
	float	Compactness(SHORT nHand);
	float	Elongatedness(SHORT nHand);
	POINT	Centroid(SHORT nHand);
	POINT	Recognize(SHORT nCurFrame);
	void	DumpFrame(BYTE** img);

protected:
	POINT	ContourTracing(BYTE** img, SHORT label, int sx, int sy);
	BOOL	BackTracing(BYTE** img, SHORT label, SHORT oldlabel, 
						int sx, int sy);
	SHORT	Labelling(BYTE** img, SHORT nHeight, SHORT nWidth, USHORT nThreshold);
	RECT	FindRect(SHORT labelnum);
	void	CurToPre();
	void	ChangeHandPixel();
	BOOL	HandFromPreFace();
	void	GetCornerOfHand( int nDir, SHORT nSize );
	void	GetPixelsInOrgFace();
	BOOL	HandFromOrgFace();
	BOOL	IsFaceChanged();
	SHORT	FindHand(SHORT nHand);
	void	MarkHand(BYTE** img, RECT *prc, BYTE gray);
#ifdef DIFF_IMAGE
	SHORT	GetMaxSegmentRect();
	void	SetFaceDiffImage();
#endif
};

