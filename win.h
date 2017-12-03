#define _WIN32_WINNT 0x0500
#include "windows.h"
#include "Windowsx.h"
#include "rpc.h"

#define UNICODE
/* for unicode */
/*
#define UNICODE in each file that is used
char =>> TCHAR
char* =>> LPTSTR
const char* LPCTSTR
define const string =>> TEXT("some string")
*/
//COLORREF name of color value in RGB
COLORREF White = RGB(255,255,255);
COLORREF Red = RGB(255,0,0);
COLORREF Snow = RGB(255,250,250);
COLORREF GhostWhite = RGB(248,248,255);
COLORREF WhiteSmoke = RGB(245,245,245);
COLORREF Gainsboro = RGB(220,220,220);
COLORREF FloralWhite = RGB(255,250,240);
COLORREF OldLace = RGB(253,245,230);
COLORREF Linen = RGB(250,240,230);
COLORREF AntiqueWhite = RGB(250,235,215);
COLORREF PapayaWhip = RGB(255,239,213);
COLORREF BlanchedAlmond = RGB(255,235,205);
COLORREF Bisque = RGB(255,228,196);
COLORREF PeachPuff = RGB(255,218,185);
COLORREF NavajoWhite = RGB(255,222,173);
COLORREF Moccasin = RGB(255,228,181);
COLORREF Cornsilk = RGB(255,248,220);
COLORREF Ivory = RGB(255,255,240);
COLORREF LemonChiffon = RGB(255,250,205);
COLORREF Seashell = RGB(255,245,238);
COLORREF Honeydew = RGB(240,255,240);
COLORREF MintCream = RGB(245,255,250);
COLORREF Azure = RGB(240,255,255);
COLORREF AliceBlue = RGB(240,248,255);
COLORREF Lavender = RGB(230,230,250);
COLORREF LavenderBlush = RGB(255,240,245);
COLORREF MistyRose = RGB(255,228,225);
COLORREF Black = RGB(0,0,0);
COLORREF DarkSlateGrey = RGB(47,79,79);
COLORREF DimGrey = RGB(105,105,105);
COLORREF SlateGrey = RGB(112,128,144);
COLORREF LightSlateGrey = RGB(119,136,153);
COLORREF Grey = RGB(190,190,190);
COLORREF LightGrey = RGB(211,211,211);
COLORREF MidnightBlue = RGB(25,25,112);
COLORREF NavyBlue = RGB(0,0,128);
COLORREF CornflowerBlue = RGB(100,149,237);
COLORREF DarkSlateBlue = RGB(72,61,139);
COLORREF SlateBlue = RGB(106,90,205);
COLORREF MediumSlateBlue = RGB(123,104,238);
COLORREF LightSlateBlue = RGB(132,112,255);
COLORREF MediumBlue = RGB(0,0,205);
COLORREF RoyalBlue = RGB(65,105,225);
COLORREF Blue = RGB(0,0,255);
COLORREF DodgerBlue = RGB(30,144,255);
COLORREF DeepSkyBlue = RGB(0,191,255);
COLORREF SkyBlue = RGB(135,206,235);
COLORREF LightSkyBlue = RGB(135,206,255);
COLORREF SteelBlue = RGB(70,130,180);
COLORREF LightSteelBlue = RGB(176,196,222);
COLORREF LightBlue = RGB(173,216,230);
COLORREF PowderBlue = RGB(176,224,230);
COLORREF PaleTurquoise = RGB(175,238,238);
COLORREF DarkTurquoise = RGB(0,206,209);
COLORREF MediumTurquoise = RGB(72,209,204);
COLORREF Turquoise = RGB(64,224,208);
COLORREF Cyan = RGB(0,255,255);
COLORREF LightCyan = RGB(224,255,255);
COLORREF CadetBlue = RGB(95,158,160);
COLORREF MediumAquamarine = RGB(102,205,170);
COLORREF Aquamarine = RGB(127,255,212);
COLORREF DarkGreen = RGB(0,100,0);
COLORREF DarkOliveGreen = RGB(85,107,47);
COLORREF DarkSeaGreen = RGB(143,188,143);
COLORREF SeaGreen = RGB(46,139,87);
COLORREF MediumSeaGreen = RGB(60,179,113);
COLORREF LightSeaGreen = RGB(32,178,170);
COLORREF PaleGreen = RGB(152,251,152);
COLORREF SpringGreen = RGB(0,255,127);
COLORREF LawnGreen = RGB(124,252,0);
COLORREF Green = RGB(0,255,0);



void MessageHandler(MSG *message)
{
	while(GetMessage(message,NULL,0,0))
	{
		TranslateMessage(message);
		DispatchMessage(message);
	}
}


class WINDOW
{
	public:
	WINDOW(
	LPCTSTR WindowName, HINSTANCE Instance, int ShowStyle, // TITLE, Handler, Show Style
	LRESULT(WINAPI *WinMesHandler)(HWND,UINT,WPARAM,LPARAM), // Message Handler	
	UINT CStyle = CS_HREDRAW|CS_VREDRAW, // redraw style
	int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int height = CW_USEDEFAULT, int width = CW_USEDEFAULT, // sizes and placement	
	HWND Parent = NULL, // parent window
	LPCTSTR MenuName = NULL, // menu	
	DWORD WindowStyle = WS_OVERLAPPEDWINDOW, // window style	
	DWORD WindowStyleEx = WS_EX_APPWINDOW,	
	LPCTSTR Icon = IDI_APPLICATION,
	LPCTSTR IconSm = IDI_APPLICATION,
	LPCTSTR Cursor = IDC_ARROW,
	int BRUSH = WHITE_BRUSH	
	);
	
	void Show(HWND Win, int ShowStyle = SW_NORMAL);
	HWND GetHandler(){return WinHand;}
	
	protected:
	HWND WinHand;
	WNDCLASSEX wc;
	
};

WINDOW::WINDOW(
		LPCTSTR WindowName, HINSTANCE Instance, int ShowStyle,
		LRESULT(WINAPI *WinMesHandler)(HWND,UINT,WPARAM,LPARAM),
		UINT CStyle,
		int x, int y, int height, int width,		
		HWND Parent,
		LPCTSTR MenuName ,		
		DWORD WindowStyle,
		DWORD WindowStyleEx,		
		LPCTSTR Icon,
		LPCTSTR IconSm,
		LPCTSTR Cursor,
		int BRUSH		
		)
	{		
		wc.cbSize = sizeof(wc);
		wc.style = CStyle;
		wc.lpfnWndProc = WinMesHandler;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = Instance;
		wc.hIcon = LoadIcon(NULL,Icon);
		wc.hCursor = LoadCursor(NULL,Cursor);
		wc.hbrBackground = (HBRUSH)GetStockObject(BRUSH);
		wc.lpszMenuName = MenuName;
		wc.lpszClassName = WindowName;
		wc.hIconSm = LoadIcon(NULL, IconSm);
		
		if(!RegisterClassEx(&wc)){MessageBox(NULL,TEXT("Class is not Registered!"),TEXT("ERROR MESSAGE"),MB_OK);return;}
		
		WinHand = CreateWindowEx(WindowStyleEx,WindowName,WindowName,WindowStyle,x,y,width,height,Parent,NULL,Instance,NULL);
		
		if(WinHand == NULL){MessageBox(NULL,TEXT("Window is not Created!"),TEXT("ERROR MESSAGE"),MB_OK);return;}		
	}
	
void WINDOW::Show(HWND Win, int ShowStyle)
{
	ShowWindow(Win, ShowStyle); return;
}

void DrawRect(HDC DC, RECT* rectangle)
{
	Rectangle(DC,rectangle->left, rectangle->top, rectangle->right, rectangle->bottom);
	return;
}

void SetPoint(POINT* point, int x, int y)
{
	point->x = x;
	point->y = y;
	return;
}

void SetLogBrush(LOGBRUSH* brush, UINT Style, COLORREF Color, ULONG_PTR Hatch = HS_CROSS)
{
	brush->lbStyle = Style;
	brush->lbColor = Color;
	if(Style == BS_HATCHED)brush->lbHatch = Hatch;
	else return;
}
/* ****************************************************************************************** Help *************************************************************************************** */
/* *****Types of DATA***** */
// BOOL
// BYTE			8-bit num unsigned
// DWORD		32-bit num unsigned
// HANDLE		object descriptor
// HBITMAP		pixel picture descriptor
// HBRUSH		brush descriptor
// HCURSOR		cursor descriptor
// HDC			device context descriptor
// HFONT		font descriptor
// HICON		icon descriptor
// HINSTANCE 	app descriptor
// HMENU		menu descriptor
// HPEN			pen descriptor
// HWND			window descriptor
// INT			32-bit num signed
// LONG			32-bit num signed
// LPARAM		param of window process 
// LPCSTR		costant string pointer
// LPCTSTR		?
// LPCWSTR		constant unicode-string pointer
// LPSTR		string pointer
// LPTSTR
// LPWSTR
// LRESULT		LONG type value, returning from window process
// NULL			((void*)0)
// TCHAR		Wchar_t(unicode-char)
// UINT			INT unsigned
// WPARAM		wParam type (wndproc)
/* *****Defined Classes***** */
// CS = class style option
// CW = create window option
// DT = draw text option
// IDC = Redefined cursor ID
// IDI = Redefined icon ID
// WM = window message
// WS = window style
/* *****Window Styles***** */
// CS_GLOBALCLASS = Create class for all users
// CS_HREDRAW = Redraw all window if it changed horizontal
// CS_VREDRAW = -//- vertical
// CS_NOCLOSE = Block close cmd in window
// CS_OWNDC = pick out unic context of device for each window of this class
// CS_DROPSHADOW
// CS_CLASSDC
// CS_BYTEALIGNCLIENT
// CS_BYTEALIGNWINDOW
// CS_SAVEBITS
/* *****Draw Text Options***** */
// DT_BOTTOM
// DT_CALCRECT
// DT_CENTER
// DT_EDITCONTROL
// DT_END_ELLIPSIS
// DT_EXPANDTABS
// DT_EXTERNALLEADING
// DT_HIDEPREFIX
// DT_INFERNAL
// DT_LEFT
// DT_MODIFYSTRING
// DT_NOCLIP
// DT_NOFULLWIDTHCHARBREAK
// DT_NOPREFIX
// DT_PATH_ELLIPSIS
// DT_PREFIXONLY
// DT_RIGHT
// DT_RTLREADING
// DT_SINGLELINE
// DT_TABSTOP
// DT_TOP
// DT_VCENTER
// DT_WORDBREAK
// DT_WORD_ELLIPSIS
/* *****Icon Styles***** */
// IDI_APPLICATION = default app icon
// IDI_ASTERISK = IDI_INFORMATION
// IDI_ERROR = error window icon
// IDI_EXCLAMATION = IDI_WARNING
// IDI_HAND = IDI_ERROR;
// IDI_INFORMATION = info window message
// IDI_QUESTION = "?"
// IDI_WARNING = warning message icon
// IDI_WINLOGO
/* *****Cursor Styles***** */
// IDC_APPSTARTING = standart arrow and sand watch
// IDC_ARROW = standart arrow
// IDC_CROSS = "+"
// IDC_HELP = arrow and "?"
// IDC_IBEAM = text cursor
// IDC_NO = strucked-through circle
// IDC_SIZEALL = 4-end arrow:
// IDC_SIZENESW
// IDC_SIZENS
// IDC_SIZENWSE
// IDC_SIZEWE
// IDC_UPARROW
// IDC_WAIT
/* *****Map Modes***** */
// MM_TEXT X->right Y->down pixel
// MM_LOMETRIC X->right Y->up 0.1 mm
// MM_HIMETRIC X->right Y->up 0.01 mm
// MM_LOENGLISH X->right Y->up 0.01 inch
// MM_HIENGLISH X->right Y->up 0.001 inch
// MM_TWIPS X->right Y->up 1/1440 inch
// MM_ISOTROPIC
// MM_ANISOTROPIC
/* *****Message Box Buttons***** */ // int MessageBox(HWND Parent, "Inner text", "Caption", MB_Buttons)
// MB_ABORTRETRYIGNORE
// MB_CANCELTRYCONTINUE
// MB_HELP
// MB_OK
// MB_OKCANCEL
// MB_RETRYCANCEL
// MB_YESNO
// MB_YESNOCANCEL
/* *****Message Box Icons***** */
// MB_ICONEXCLAMATION
// MB_ICONWARNING
// MB_ICONINFORMATION
// MB_ICONASTERISK
// MB_ICONQUESTION
// MB_ICONSTOP
// MB_ICONERROR
// MB_ICONHAND
/* *****Message Box Modality***** */
// MB_APPLMODAL
// MB_SYSTEMMODAL
// MB_TASKMODAL
/* *****Message Box Other Options***** */
// MB_DEFAULT_DESKTOP_ONLY
// MB_RIGHT
// MB_RTLREADING
// MB_SETFOREGROUND
// MB_TOPMOST
// MB_SERVICE_NOTIFICATION
/* *****Message Box Return Values***** */
// IDABORT = 3
// IDCANCEL = 2
// IDCONTINUE = 11
// IDIGNORE = 5
// IDNO = 7
// IDOK = 1
// IDRETRY = 4
// IDTRYAGAIN = 10
// IDYES = 6
/* *****Window Standart Classes***** */
// BS = BUTTON
// CBS = COMBOBOX
// ES = EDIT = RICHEDIT = RICHEDIT_CLASS
// LBS = LISTBOX
// MDI = MDICLIENT
// SBS = SCROLLBAR
// SS = STATIC
/* *****Window Styles***** */
// WS_BORDER = Create window with frame as a thin line
// WS_CAPTION = Create window with title area
// WS_CHILD = create child window
// WS_CLIPCHILDREN = cancel redrawing of child windows of current parent window
// WS_DLGFRAME = Dialog Window
// WS_GROUP 
// WS_HSCROLL = Create window with the horizontal scroll bar
// WS_MAXIMIZE
// WS_MAXIMIZEBOX = with maximize button
// WS_MINIMIZE = create minimized window
// WS_MINIMIZEBOX
// WS_OVERLAPPED = create window with title and box
// WS_OVERLAPPEDWINDOW
// WS_POPUP
// WS_POPUPWINDOW
// WS_SYSMENU = Create window with system menu
// WS_TABSTOP = Activate TAB control
// WS_THICKFRAME = Window with dynamic box
// WS_VISIBLE 
// WS_VSCROLL = vertical scroll bar
// WS_EX_ACCEPTFILES = accepts dragged files
// WS_EX_APPWINDOW
// WS_EX_CLIENTEDGE = box with not sharp angle
// WS_EX_COMPOSITED
// WS_EX_CONTEXTHELP
// WS_EX_CONTROLPARENT = jump on child windows with TAB-key
// WS_EX_DLGMODALFRAME
// WS_EX_LAYERED
// WS_EX_LAYOURTL
// WS_EX_LEFT
// WS_EX_LEFTSCROLLBAR
// WS_EX_LTRREADING
// WS_EX_MDICHILD 
// WS_EX_NOACTIVE
// WS_EX_NOINHERITLAYOUT
// WS_EX_NOPARENTNOTIFY
// WS_EX_NOREDIRECTIONBITMAP
// WS_EX_OVERLAPPEDWINDOW
// WS_EX_PALETTEWINDOW
// WS_EX_RIGHT
// WS_EX_RIGHTSCROLLBAR
// WS_EX_RTLREADING
// WS_EX_TOPMOST
// WS_EX_STATICEDGE = Window with 3D box (don't have a write method);
// WS_EX_TOOLWINDOW = Window with tools for creating float tools panel
// WS_EX_TRANSPARENT
// WS_EX_WINDOWEDGE
/* *****Show Window***** */
// SW_HIDE
// SW_MAXIMIZE
// SW_MINIMIZE
// SW_SHOW
// SW_SHOWMINNOACTIVE
// SW_FORCEMINIMIZE
// SW_RESTORE
// SW_SHOWDEFAULT
// SW_SHOWNA -- show and DO NOT activate
// SW_SHOWNORMAL
/* *****Messages***** */
// WM_CLOSE
// WM_COMMAND -- after sending command from control element
// WM_CREATE -- after createwindow() is done
// WM_DESTROY
// WM_INITDIALOG
// WM_MOVE
// WM_PAINT
// WM_SIZE
// WM_TIMER -- setting timer
/* *****Supply Funcs***** */ // (write full bodies of them)
// BringWindowToTop
// CloseWindow
// DestroyWindow(HWND)
// EnableWindow
// FindWindow
// GetActiveWindow
// GetClassInfo
// GetClassLong
// GetClientRect
// GetFocus
// GetParent
// GetWindow
// GetWindowInfo
// GetWindowLong
// GetWindowRect
// IsChild
// IsIconic
// IsWindowEnabled
// MoveWindow
// SetActiveWindow
// SetGlassLong
// SetFocus
// SetWindowLong
// SetWindowPos
// SetWindowText
// ShowWindow(HWND Win, int ShowStyle)
// UpdateWindow
/* *****Window Modify and Curious Funcs***** */

// DWORD SetClassLong(HWND hWnd, int nIndex, LONG dwNewLong); --> window descriptor, index of value to change, new value

// (LONG) CreateSolidBrush(RGB(200,160,255)) // brush with rgb color

// SetBkMode(HDC, int iBkMode)

// (HDC)BeginPaint(HWND, &PAINTSTRUCT)

// GetClientRect(HWND, &RECT)

// DrawText(HDC,LPSTR,int measure, &RECT, DT_)\

// HDC GetDC(HWND) ---> gets device context

// Release DC(HWND, HDC) --> clears up device context (region of painting)

// BOOL IvalidateRect(HWND, CONST *RECT, BOOL bErase)

// BOOL IvalidateRgn(HWND, HRGN hRgn, BOOL bErase)

// LRESULT SendMessage(HWND Window, UINT Message, WPARAM wParam, LPARAM lParam)

// (HINSTANCE)GetClassLong(HWND, GCL_HMODULE)

// BOOL PeekMessage(LPMSG (structure adress with message), HWND Win, UINT(first message),UINT(last message),UINT (flag of removing message)) -- can be used to pretend the lags in app
// the last param gets values: PM_NOREMOVE | PM_REMOVE - DON'T DELETE | DELETE message from queue


/* HDC CreateIC(
	LPCTSTR lpszDriver // driver name
	LPCTSTR lpszDevice // device name
	LPCTSTR lpszOutput // name of port or file
	CONST DEVMODE* lpDvm // pointer on struct DEVMODE
);
*/
/*
HRGN CreateRectRgn(
  _In_ int nLeftRect,
  _In_ int nTopRect,
  _In_ int nRightRect,
  _In_ int nBottomRect
);

SelectClipRgn(DC,hrgn);

SetWindowRgn(
	HWND Window,
	HRGN region,
	BOOL REDRAW
);

SelectObject(HDC,HGDIOBJECT);

RECT Rectangle(
	HDC DC
  _In_ int nLeftRect,
  _In_ int nTopRect,
  _In_ int nRightRect,
  _In_ int nBottomRect
);

BOOL SetWindowOrgEx(
  _In_  HDC     hdc,
  _In_  int     X,
  _In_  int     Y,
  _Out_ LPPOINT lpPoint
);

BOOL ScreenToClient(
  _In_ HWND    hWnd,
       LPPOINT lpPoint
);

BOOL WINAPI SetWindowPos(
  _In_     HWND hWnd,
  _In_opt_ HWND hWndInsertAfter,
  _In_     int  X,
  _In_     int  Y,
  _In_     int  cx,
  _In_     int  cy,
  _In_     UINT uFlags
);

CreatePen(PS_SOLID,5,RGB(0,255,0));
*/
/* nIndex Values */
// GCL_HBRBACKGROUND
// GCL_HCURSOR
// GCL_HICON
// GCL_HICONSM
// GCL_MENUNAME
// GCL_STYLE
// GCL_WNDPROC
// GCL_HMODULE

/* *****STRUCTURES***** */
/*
tagPAINTSTRUCT
{
	HDC hdc;		// device context
	BOOL fErase;	// sign of background clearing in client space
	RECT rcPaint;	// measures of unreacheable rectangle
	BOOL fRestore;
	BOOL fIncUpdate;
	BYTE rgbReserved[32];
}PAINSTRUCT;

struct tagMSG{
	HWND   hwnd;
  UINT   message;
  WPARAM wParam;
  LPARAM lParam;
  DWORD  time;
  POINT  pt;
} MSG, *PMSG, *LPMSG;

*/

