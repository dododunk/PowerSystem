using System;
namespace WinFormsUI.Docking.Win32
{
	internal enum ShowWindowStyles : short
	{
		SW_HIDE,
		SW_SHOWNORMAL,
		SW_NORMAL = 1,
		SW_SHOWMINIMIZED,
		SW_SHOWMAXIMIZED,
		SW_MAXIMIZE = 3,
		SW_SHOWNOACTIVATE,
		SW_SHOW,
		SW_MINIMIZE,
		SW_SHOWMINNOACTIVE,
		SW_SHOWNA,
		SW_RESTORE,
		SW_SHOWDEFAULT,
		SW_FORCEMINIMIZE,
		SW_MAX = 11
	}
}
