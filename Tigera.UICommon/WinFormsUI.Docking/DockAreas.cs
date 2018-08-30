using System;
using System.ComponentModel;
using System.Drawing.Design;
namespace WinFormsUI.Docking
{
	[Editor(typeof(DockAreasEditor), typeof(UITypeEditor)), Flags]
	[Serializable]
	public enum DockAreas
	{
		Float = 1,
		DockLeft = 2,
		DockRight = 4,
		DockTop = 8,
		DockBottom = 16,
		Document = 32
	}
}
