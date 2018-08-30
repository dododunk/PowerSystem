using System;
using System.Drawing;
namespace WinFormsUI.Docking
{
	public static class DockingHelper
	{
		public static Color ThemeMenuForeColor
		{
			get;
			set;
		}
		public static Color ThemeDocumentTabActiveBorder
		{
			get;
			set;
		}
		public static Color ThemeDocumentTabInactiveBorder
		{
			get;
			set;
		}
		public static Color ThemeToolWindowTabBorder
		{
			get;
			set;
		}
		public static bool HideDocumentWindowBorder
		{
			get;
			set;
		}
		public static bool UseLightDockStripImages
		{
			get;
			set;
		}
		static DockingHelper()
		{
			DockingHelper.ThemeMenuForeColor = Color.Empty;
			DockingHelper.ThemeDocumentTabActiveBorder = Color.Empty;
			DockingHelper.ThemeDocumentTabInactiveBorder = Color.Empty;
			DockingHelper.ThemeToolWindowTabBorder = Color.Empty;
			DockingHelper.HideDocumentWindowBorder = true;
			DockingHelper.UseLightDockStripImages = true;
		}
	}
}
