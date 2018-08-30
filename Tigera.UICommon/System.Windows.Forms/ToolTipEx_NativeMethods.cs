using System;
using System.Drawing;
using System.Runtime.InteropServices;
namespace System.Windows.Forms
{
	internal class ToolTipEx_NativeMethods
	{
		public enum WindowMessages
		{
			WM_NULL,
			WM_CREATE,
			WM_DESTROY,
			WM_MOVE,
			WM_SIZE = 5,
			WM_ACTIVATE,
			WM_SETFOCUS,
			WM_KILLFOCUS,
			WM_ENABLE = 10,
			WM_SETREDRAW,
			WM_SETTEXT,
			WM_GETTEXT,
			WM_GETTEXTLENGTH,
			WM_PAINT,
			WM_CLOSE,
			WM_QUIT = 18,
			WM_ERASEBKGND = 20,
			WM_SYSCOLORCHANGE,
			WM_SHOWWINDOW = 24,
			WM_ACTIVATEAPP = 28,
			WM_SETCURSOR = 32,
			WM_MOUSEACTIVATE,
			WM_GETMINMAXINFO = 36,
			WM_WINDOWPOSCHANGING = 70,
			WM_WINDOWPOSCHANGED,
			WM_CONTEXTMENU = 123,
			WM_STYLECHANGING,
			WM_STYLECHANGED,
			WM_DISPLAYCHANGE,
			WM_GETICON,
			WM_SETICON,
			WM_NCCREATE,
			WM_NCDESTROY,
			WM_NCCALCSIZE,
			WM_NCHITTEST,
			WM_NCPAINT,
			WM_NCACTIVATE,
			WM_GETDLGCODE,
			WM_SYNCPAINT,
			WM_NCMOUSEMOVE = 160,
			WM_NCLBUTTONDOWN,
			WM_NCLBUTTONUP,
			WM_NCLBUTTONDBLCLK,
			WM_NCRBUTTONDOWN,
			WM_NCRBUTTONUP,
			WM_NCRBUTTONDBLCLK,
			WM_NCMBUTTONDOWN,
			WM_NCMBUTTONUP,
			WM_NCMBUTTONDBLCLK,
			WM_KEYDOWN = 256,
			WM_KEYUP,
			WM_CHAR,
			WM_SYSCOMMAND = 274,
			WM_INITMENU = 278,
			WM_INITMENUPOPUP,
			WM_MENUSELECT = 287,
			WM_MENUCHAR,
			WM_ENTERIDLE,
			WM_MENURBUTTONUP,
			WM_MENUDRAG,
			WM_MENUGETOBJECT,
			WM_UNINITMENUPOPUP,
			WM_MENUCOMMAND,
			WM_CHANGEUISTATE,
			WM_UPDATEUISTATE,
			WM_QUERYUISTATE,
			WM_MOUSEFIRST = 512,
			WM_MOUSEMOVE = 512,
			WM_LBUTTONDOWN,
			WM_LBUTTONUP,
			WM_LBUTTONDBLCLK,
			WM_RBUTTONDOWN,
			WM_RBUTTONUP,
			WM_RBUTTONDBLCLK,
			WM_MBUTTONDOWN,
			WM_MBUTTONUP,
			WM_MBUTTONDBLCLK,
			WM_MOUSEWHEEL,
			WM_MOUSELAST = 525,
			WM_PARENTNOTIFY = 528,
			WM_ENTERMENULOOP,
			WM_EXITMENULOOP,
			WM_NEXTMENU,
			WM_SIZING,
			WM_CAPTURECHANGED,
			WM_MOVING,
			WM_ENTERSIZEMOVE = 561,
			WM_EXITSIZEMOVE,
			WM_MOUSELEAVE = 675,
			WM_MOUSEHOVER = 673,
			WM_NCMOUSEHOVER = 672,
			WM_NCMOUSELEAVE = 674,
			WM_MDIACTIVATE = 546,
			WM_HSCROLL = 276,
			WM_VSCROLL,
			WM_PRINT = 791,
			WM_PRINTCLIENT,
			WM_PASTE = 770
		}
		public enum SystemCommands
		{
			SC_SIZE = 61440,
			SC_MOVE = 61456,
			SC_MINIMIZE = 61472,
			SC_MAXIMIZE = 61488,
			SC_MAXIMIZE2 = 61490,
			SC_NEXTWINDOW = 61504,
			SC_PREVWINDOW = 61520,
			SC_CLOSE = 61536,
			SC_VSCROLL = 61552,
			SC_HSCROLL = 61568,
			SC_MOUSEMENU = 61584,
			SC_KEYMENU = 61696,
			SC_ARRANGE = 61712,
			SC_RESTORE = 61728,
			SC_RESTORE2 = 61730,
			SC_TASKLIST = 61744,
			SC_SCREENSAVE = 61760,
			SC_HOTKEY = 61776,
			SC_DEFAULT = 61792,
			SC_MONITORPOWER = 61808,
			SC_CONTEXTHELP = 61824,
			SC_SEPARATOR = 61455
		}
		public enum NCHITTEST
		{
			HTERROR = -2,
			HTTRANSPARENT,
			HTNOWHERE,
			HTCLIENT,
			HTCAPTION,
			HTSYSMENU,
			HTGROWBOX,
			HTMENU,
			HTHSCROLL,
			HTVSCROLL,
			HTMINBUTTON,
			HTMAXBUTTON,
			HTLEFT,
			HTRIGHT,
			HTTOP,
			HTTOPLEFT,
			HTTOPRIGHT,
			HTBOTTOM,
			HTBOTTOMLEFT,
			HTBOTTOMRIGHT,
			HTBORDER,
			HTOBJECT,
			HTCLOSE,
			HTHELP
		}
		[Flags]
		public enum WindowStyle : uint
		{
			WS_OVERLAPPED = 0u,
			WS_POPUP = 2147483648u,
			WS_CHILD = 1073741824u,
			WS_MINIMIZE = 536870912u,
			WS_VISIBLE = 268435456u,
			WS_DISABLED = 134217728u,
			WS_CLIPSIBLINGS = 67108864u,
			WS_CLIPCHILDREN = 33554432u,
			WS_MAXIMIZE = 16777216u,
			WS_CAPTION = 12582912u,
			WS_BORDER = 8388608u,
			WS_DLGFRAME = 4194304u,
			WS_VSCROLL = 2097152u,
			WS_HSCROLL = 1048576u,
			WS_SYSMENU = 524288u,
			WS_THICKFRAME = 262144u,
			WS_GROUP = 131072u,
			WS_TABSTOP = 65536u,
			WS_MINIMIZEBOX = 131072u,
			WS_MAXIMIZEBOX = 65536u,
			WS_TILED = 0u,
			WS_ICONIC = 536870912u,
			WS_SIZEBOX = 262144u,
			WS_TILEDWINDOW = 13565952u,
			WS_OVERLAPPEDWINDOW = 13565952u,
			WS_POPUPWINDOW = 2156396544u,
			WS_CHILDWINDOW = 1073741824u
		}
		[Flags]
		public enum WindowStyleEx
		{
			WS_EX_DLGMODALFRAME = 1,
			WS_EX_NOPARENTNOTIFY = 4,
			WS_EX_TOPMOST = 8,
			WS_EX_ACCEPTFILES = 16,
			WS_EX_TRANSPARENT = 32,
			WS_EX_MDICHILD = 64,
			WS_EX_TOOLWINDOW = 128,
			WS_EX_WINDOWEDGE = 256,
			WS_EX_CLIENTEDGE = 512,
			WS_EX_CONTEXTHELP = 1024,
			WS_EX_RIGHT = 4096,
			WS_EX_LEFT = 0,
			WS_EX_RTLREADING = 8192,
			WS_EX_LTRREADING = 0,
			WS_EX_LEFTSCROLLBAR = 16384,
			WS_EX_RIGHTSCROLLBAR = 0,
			WS_EX_CONTROLPARENT = 65536,
			WS_EX_STATICEDGE = 131072,
			WS_EX_APPWINDOW = 262144,
			WS_EX_OVERLAPPEDWINDOW = 768,
			WS_EX_PALETTEWINDOW = 392,
			WS_EX_LAYERED = 524288,
			WS_EX_NOINHERITLAYOUT = 1048576,
			WS_EX_LAYOUTRTL = 4194304,
			WS_EX_COMPOSITED = 33554432,
			WS_EX_NOACTIVATE = 134217728
		}
		public struct RECT
		{
			public int Left;
			public int Top;
			public int Right;
			public int Bottom;
			public Rectangle Rect
			{
				get
				{
					return checked(new Rectangle(this.Left, this.Top, this.Right - this.Left, this.Bottom - this.Top));
				}
			}
			public RECT(int left, int top, int right, int bottom)
			{
				this.Left = left;
				this.Top = top;
				this.Right = right;
				this.Bottom = bottom;
			}
			public static ToolTipEx_NativeMethods.RECT FromXYWH(int x, int y, int width, int height)
			{
				return checked(new ToolTipEx_NativeMethods.RECT(x, y, x + width, y + height));
			}
			public static ToolTipEx_NativeMethods.RECT FromRectangle(Rectangle rect)
			{
				return new ToolTipEx_NativeMethods.RECT(rect.Left, rect.Top, rect.Right, rect.Bottom);
			}
		}
		public struct WINDOWPOS
		{
			public IntPtr hwnd;
			public IntPtr hWndInsertAfter;
			public int x;
			public int y;
			public int cx;
			public int cy;
			public uint flags;
		}
		public struct NCCALCSIZE_PARAMS
		{
			public ToolTipEx_NativeMethods.RECT rectProposed;
			public ToolTipEx_NativeMethods.RECT rectBeforeMove;
			public ToolTipEx_NativeMethods.RECT rectClientBeforeMove;
			public ToolTipEx_NativeMethods.WINDOWPOS lpPos;
		}
		public struct MINMAXINFO
		{
			public Point reserved;
			public Size maxSize;
			public Point maxPosition;
			public Size minTrackSize;
			public Size maxTrackSize;
		}
		public static readonly IntPtr TRUE = new IntPtr(1);
		public static readonly IntPtr FALSE = IntPtr.Zero;
		[DllImport("user32.dll")]
		public static extern bool ReleaseCapture();
		public static int LOWORD(int value)
		{
			return value & 65535;
		}
		public static int HIWORD(int value)
		{
			return value >> 16;
		}
	}
}
