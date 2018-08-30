using System;
using System.Windows.Forms;
namespace WinFormsUI.Docking
{
	internal interface IDragSource
	{
		Control DragControl
		{
			get;
		}
	}
}
