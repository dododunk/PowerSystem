using System;
namespace WinFormsUI.Docking
{
	public class DockContentEventArgs : EventArgs
	{
		private IDockContent m_content;
		public IDockContent Content
		{
			get
			{
				return this.m_content;
			}
		}
		public DockContentEventArgs(IDockContent content)
		{
			this.m_content = content;
		}
	}
}
