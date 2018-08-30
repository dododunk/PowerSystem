using System;
using System.Drawing;
using System.Runtime.InteropServices;
namespace System.Windows.Forms
{
	internal sealed class NativeMethods
	{
		public struct DLLVersionInfo
		{
			public int cbSize;
			public int dwMajorVersion;
			public int dwMinorVersion;
			public int dwBuildNumber;
			public int dwPlatformID;
		}
		public struct NCCALCSIZE_PARAMS
		{
			public NativeMethods.RECT rgrc0;
			public NativeMethods.RECT rgrc1;
			public NativeMethods.RECT rgrc2;
			public IntPtr lppos;
		}
		[Serializable]
		public struct RECT
		{
			public int Left;
			public int Top;
			public int Right;
			public int Bottom;
			public int Height
			{
				get
				{
					return checked(this.Bottom - this.Top + 1);
				}
			}
			public int Width
			{
				get
				{
					return checked(this.Right - this.Left + 1);
				}
			}
			public Size Size
			{
				get
				{
					return new Size(this.Width, this.Height);
				}
			}
			public Point Location
			{
				get
				{
					return new Point(this.Left, this.Top);
				}
			}
			public RECT(int left_, int top_, int right_, int bottom_)
			{
				this.Left = left_;
				this.Top = top_;
				this.Right = right_;
				this.Bottom = bottom_;
			}
			public Rectangle ToRectangle()
			{
				return Rectangle.FromLTRB(this.Left, this.Top, this.Right, this.Bottom);
			}
			public static NativeMethods.RECT FromRectangle(Rectangle rectangle)
			{
				return new NativeMethods.RECT(rectangle.Left, rectangle.Top, rectangle.Right, rectangle.Bottom);
			}
			public void Inflate(int width, int height)
			{
				checked
				{
					this.Left -= width;
					this.Top -= height;
					this.Right += width;
					this.Bottom += height;
				}
			}
			public override int GetHashCode()
			{
				return this.Left ^ (this.Top << 13 | this.Top >> 19) ^ (this.Width << 26 | this.Width >> 6) ^ (this.Height << 7 | this.Height >> 25);
			}
			public static implicit operator Rectangle(NativeMethods.RECT rect)
			{
				return Rectangle.FromLTRB(rect.Left, rect.Top, rect.Right, rect.Bottom);
			}
			public static implicit operator NativeMethods.RECT(Rectangle rect)
			{
				return new NativeMethods.RECT(rect.Left, rect.Top, rect.Right, rect.Bottom);
			}
		}
		public const int S_OK = 0;
		public const int EP_EDITTEXT = 1;
		public const int ETS_DISABLED = 4;
		public const int ETS_NORMAL = 1;
		public const int ETS_READONLY = 6;
		public const int WM_THEMECHANGED = 794;
		public const int WM_NCPAINT = 133;
		public const int WM_NCCALCSIZE = 131;
		public const int WS_EX_CLIENTEDGE = 512;
		public const int WVR_HREDRAW = 256;
		public const int WVR_VREDRAW = 512;
		public const int WVR_REDRAW = 768;
		static NativeMethods()
		{
		}
		[DllImport("user32.dll")]
		public static extern IntPtr GetWindowDC(IntPtr hWnd);
		[DllImport("user32.dll")]
		public static extern int ReleaseDC(IntPtr hWnd, IntPtr hDC);
		[DllImport("user32.dll")]
		public static extern bool GetWindowRect(IntPtr hWnd, out NativeMethods.RECT lpRect);
		[DllImport("gdi32.dll")]
		public static extern int ExcludeClipRect(IntPtr hdc, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect);
		[DllImport("UxTheme.dll", CharSet = CharSet.Auto)]
		public static extern bool IsAppThemed();
		[DllImport("UxTheme.dll", CharSet = CharSet.Auto)]
		public static extern bool IsThemeActive();
		[DllImport("comctl32.dll", CharSet = CharSet.Auto)]
		public static extern int DllGetVersion(ref NativeMethods.DLLVersionInfo version);
		[DllImport("uxtheme.dll", CharSet = CharSet.Unicode, ExactSpelling = true)]
		public static extern IntPtr OpenThemeData(IntPtr hWnd, string classList);
		[DllImport("uxtheme.dll", ExactSpelling = true)]
		public static extern int CloseThemeData(IntPtr hTheme);
		[DllImport("uxtheme", ExactSpelling = true)]
		public static extern int DrawThemeBackground(IntPtr hTheme, IntPtr hdc, int iPartId, int iStateId, ref NativeMethods.RECT pRect, IntPtr pClipRect);
		[DllImport("uxtheme", ExactSpelling = true)]
		public static extern int IsThemeBackgroundPartiallyTransparent(IntPtr hTheme, int iPartId, int iStateId);
		[DllImport("uxtheme", ExactSpelling = true)]
		public static extern int GetThemeBackgroundContentRect(IntPtr hTheme, IntPtr hdc, int iPartId, int iStateId, ref NativeMethods.RECT pBoundingRect, out NativeMethods.RECT pContentRect);
		[DllImport("uxtheme", ExactSpelling = true)]
		public static extern int DrawThemeParentBackground(IntPtr hWnd, IntPtr hdc, ref NativeMethods.RECT pRect);
		[DllImport("uxtheme", ExactSpelling = true)]
		public static extern int DrawThemeBackground(IntPtr hTheme, IntPtr hdc, int iPartId, int iStateId, ref NativeMethods.RECT pRect, ref NativeMethods.RECT pClipRect);
	}
}
