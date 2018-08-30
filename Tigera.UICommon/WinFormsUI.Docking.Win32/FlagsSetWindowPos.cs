using System;
namespace WinFormsUI.Docking.Win32
{
	[Flags]
	internal enum FlagsSetWindowPos : uint
	{
		SWP_NOSIZE = 1u,
		SWP_NOMOVE = 2u,
		SWP_NOZORDER = 4u,
		SWP_NOREDRAW = 8u,
		SWP_NOACTIVATE = 16u,
		SWP_FRAMECHANGED = 32u,
		SWP_SHOWWINDOW = 64u,
		SWP_HIDEWINDOW = 128u,
		SWP_NOCOPYBITS = 256u,
		SWP_NOOWNERZORDER = 512u,
		SWP_NOSENDCHANGING = 1024u,
		SWP_DRAWFRAME = 32u,
		SWP_NOREPOSITION = 512u,
		SWP_DEFERERASE = 8192u,
		SWP_ASYNCWINDOWPOS = 16384u
	}
}
