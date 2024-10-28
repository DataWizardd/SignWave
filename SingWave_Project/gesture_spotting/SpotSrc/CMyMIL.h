#ifndef	_CCMYMIL_HPP
#define	_CMYMIL_HPP

//#define DEBUGGING_CODE
//#define USE_HOOK_FUNC
//#define YIQ_COLOR


// Added by hklee for removing mil*.h
#define M_NULL                        0x00000000L
#define M_FALSE                       0L
#define M_TRUE                        1L
#define M_NO                          0L
#define M_YES                         1L
#define M_OFF                         0L
#define M_ON                          1L
#define M_DEFAULT                     0x10000000L
#define M_QUIET                       0x08000000L
#define M_VALID                       0x00000001L
#define M_INVALID                     -1L
#define M_CLEAR                       0x00000001L
#define M_NO_CLEAR                    0x00000002L
#define M_LUT_OFFSET                  0x80000000L
#define M_EXTENDED                    0x80000000L  // Special parameter routed directly to the driver

/* buffer ID offset for defaults */
#define M_ID_OFFSET_OF_DEFAULT_KERNEL 0x00100000L

#define M_UNSIGNED                    0x00000000L
#define M_SIGNED                      0x10000000L

/* buffer attributes */
#define M_NO_ATTR                     0x0000
#define M_IN                          0x0001
#define M_OUT                         0x0002

#define M_IMAGE                       0x00000004L
#define M_GRAB                        0x00000008L
#define M_PROC                        0x00000010L
#define M_DISP                        0x00000020L
#define M_GRAPH                       0x00000040L
#define M_OVR                         0x00000080L
#define M_LUT                         0x00000100L
#define M_KERNEL                      0x00000200L
#define M_STRUCT_ELEMENT              0x00000400L
#define M_ARRAY                       0x00000800L
#define M_BINARY                      0x00001000L
#define M_HIST_LIST                   0x00002000L
#define M_PROJ_LIST                   0x00004000L
#define M_EVENT_LIST                  0x00008000L
#define M_EXTREME_LIST                0x00010000L
#define M_COUNT_LIST                  0x00020000L
#define M_FILE_FORMAT                 0x00040000L
#define M_WARP_COEFFICIENT            0x00080000L
#define M_DIGITIZER                   0x00100000L
#define M_DISPLAY                     0x00200000L
#define M_APPLICATION                 0x00400000L
#define M_SYSTEM                      0x00800000L
#define M_GRAPHIC_CONTEXT             0x01000000L
#define M_CALL_CONTEXT                0x02000000L
#define M_ERROR_CONTEXT               0x04000000L
#define M_OVERSCAN_BUFFER             0x08000000L
#define M_USER_HOST_POINTER           0x10000000L
#define M_USER_ATTRIBUTE              0x20000000L
#define M_EXTENDED_ATTRIBUTE          M_EXTENDED

#define M_USER_OBJECT_1               (M_USER_ATTRIBUTE | 0x00010000L)
#define M_USER_OBJECT_2               (M_USER_ATTRIBUTE | 0x00020000L)
#define M_BLOB_OBJECT                 (M_USER_ATTRIBUTE | 0x00040000L)
#define M_PAT_OBJECT                  (M_USER_ATTRIBUTE | 0x00080000L)
#define M_OCR_OBJECT                  (M_USER_ATTRIBUTE | 0x00100000L)
#define M_MEAS_OBJECT                 (M_USER_ATTRIBUTE | 0x00200000L)
#define M_FREE_OBJECT_1               (M_USER_ATTRIBUTE | 0x00400000L)
#define M_FREE_OBJECT_2               (M_USER_ATTRIBUTE | 0x00800000L)
#define M_FREE_OBJECT_3               (M_USER_ATTRIBUTE | 0x01000000L)
#define M_FREE_OBJECT_4               (M_USER_ATTRIBUTE | 0x02000000L)
#define M_FREE_OBJECT_5               (M_USER_ATTRIBUTE | 0x04000000L)
#define M_FREE_OBJECT_6               (M_USER_ATTRIBUTE | 0x08000000L)
#define M_USER_DEFINE_LOW_ATTRIBUTE   0x0000FFFFL

#define M_HOOK_CONTEXT                (M_EXTENDED_ATTRIBUTE | 0x00000001L)
#define M_ON_BOARD                    (M_EXTENDED_ATTRIBUTE | 0x00040000L)
#define M_OFF_BOARD                   (M_EXTENDED_ATTRIBUTE | 0x00080000L)
#define M_AS_SPECIFIED                (M_EXTENDED_ATTRIBUTE | 0x00100000L)

#define M_SYSTEM_ALLOCATED            0x00000001L
#define M_USER_ALLOCATED              0xFFFFFFFEL


#define M_DEF_IMAGE_NUMBANDS_MIN   1L
#define M_DEF_IMAGE_SIZE_X_MIN     512
#define M_DEF_IMAGE_SIZE_Y_MIN     480
#define M_DEF_IMAGE_SIZE_X_MAX     1024
#define M_DEF_IMAGE_SIZE_Y_MAX     1024
#define M_DEF_IMAGE_TYPE           8+M_UNSIGNED
#define M_DEF_IMAGE_ATTRIBUTE_MIN  M_IMAGE+M_PROC



#define SHOW_COLOR_IMAGE

#define MAX_RECENT		7
#define MIN_MOVE		7

// parameters for DisplayFrame & ProcessFrame
#define OP_FRAMEDUMP	0
#define OP_REALTIME		1
#define OP_GETFEATURE	2

class CMyMIL
{
public:
	long	m_lSizeX;		// Buffer width
	long	m_lSizeY;		// Buffer height
	long	m_ldigSizeX;	// input width
	long	m_ldigSizeY;	// input height
	long	m_lBand;		// number of input color bands
	long	m_lMaxDisplay;	// maximum number of display
	BOOL	m_bGrabStart;	// Is grabbing?
#ifdef USE_HOOK_FUNC
	BOOL	m_bInProcessing;
#endif
	MIL_ID	m_milAppl;		// Application ID
	MIL_ID	m_milSystem;	// System ID
	MIL_ID	m_milDigitizer;	// Digitizer ID
	class	CMyHand	*m_myHand;
	CView*	m_theView;		// the child view currently grabbing
	BOOL*	m_pbSelDisplay;	// Is display selected?

protected:
	POINT	m_ptAllDiff;
	POINT	m_ptRecent[MAX_RECENT];
	SHORT	m_nRecent;

public:
	CMyMIL();
	~CMyMIL();

	BOOL	InitMILDocument(long* plDispIdx, MIL_ID* pmilImage,
							 MIL_ID* pmilDispImg);
	void	CloseMILDocument(MIL_ID* pmilImage, MIL_ID* pmilDispImg);
	void	RemoveMILDisplay(CView* pView, MIL_ID* pmilDisplay, 
							 MIL_ID milDispImg);
	POINT	ProcessFrame(MIL_ID milDispImg, SHORT nOnline, SHORT nCurFrame);
	void	StartGrab(MIL_ID milImage, MIL_ID milDispImg, CView* pView);
	void	FinishGrab();
	void	InitMILUpdate(HWND hWnd, MIL_ID* pmilDisplay, long lDispIdx, 
							 MIL_ID milDispImg);
	BOOL	DestroyMILDisplay(CView* pView, long lDispIdx, MIL_ID milDispImg, 
							 MIL_ID* pmilDisplay);
	BOOL	ConsiderSpotting( SHORT nOldLoc, POINT ptCur, REAL rWait );
	BOOL	StartFrameRecognize( BOOL bUseFrameID );
	void	EndFrameRecognize(REAL rWait);
	void	GrabOneFrame(MIL_ID milImage, MIL_ID milDispImg);

protected:
	BOOL	InitMILInstance();
	void	ProcessGrab(MIL_ID milImage, MIL_ID milDispImg);
	void	DisplayFrame(MIL_ID milDispImg, SHORT nOnline);
	BOOL	IsStayLong( POINT ptCur );
#ifdef DEBUGGING_CODE
	void	DebugProcessGrab(MIL_ID milImage, MIL_ID milDispImg);
#endif
};

extern CMyMIL* theMIL;

#endif	// _CMYMIL_HPP
