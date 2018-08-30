using System;
namespace WinFormsUI.Docking
{
	public interface IDockContent
	{
		DockContentHandler DockHandler
		{
			get;
		}
		void OnActivated(EventArgs e);
		void OnDeactivate(EventArgs e);
	}
}
