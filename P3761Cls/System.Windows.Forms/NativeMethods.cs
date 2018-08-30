using System;
using System.Drawing;
namespace System.Windows.Forms
{
	internal static class NativeMethods
	{
		internal struct MINMAXINFO
		{
			public Size minTrackSize;
			public Size maxTrackSize;
		}
		internal const int WM_NCHITTEST = 132;
		internal const int WM_NCACTIVATE = 134;
		internal const int WS_EX_NOACTIVATE = 134217728;
		internal const int HTTRANSPARENT = -1;
		internal const int HTLEFT = 10;
		internal const int HTRIGHT = 11;
		internal const int HTTOP = 12;
		internal const int HTTOPLEFT = 13;
		internal const int HTTOPRIGHT = 14;
		internal const int HTBOTTOM = 15;
		internal const int HTBOTTOMLEFT = 16;
		internal const int HTBOTTOMRIGHT = 17;
		internal const int WM_USER = 1024;
		internal const int WM_REFLECT = 8192;
		internal const int WM_COMMAND = 273;
		internal const int CBN_DROPDOWN = 7;
		internal const int WM_GETMINMAXINFO = 36;
		internal static int HIWORD(int n)
		{
			return n >> 16 & 65535;
		}
		internal static int HIWORD(IntPtr n)
		{
			return NativeMethods.HIWORD((int)((long)n));
		}
		internal static int LOWORD(int n)
		{
			return n & 65535;
		}
		internal static int LOWORD(IntPtr n)
		{
			return NativeMethods.LOWORD((int)((long)n));
		}
	}
}
