using System;
using System.ComponentModel;
namespace WinFormsUI.Docking
{
	[TypeConverter(typeof(DockPanelSkinConverter))]
	public class DockPanelSkin
	{
		private AutoHideStripSkin m_autoHideStripSkin;
		private DockPaneStripSkin m_dockPaneStripSkin;
		public AutoHideStripSkin AutoHideStripSkin
		{
			get
			{
				return this.m_autoHideStripSkin;
			}
			set
			{
				this.m_autoHideStripSkin = value;
			}
		}
		public DockPaneStripSkin DockPaneStripSkin
		{
			get
			{
				return this.m_dockPaneStripSkin;
			}
			set
			{
				this.m_dockPaneStripSkin = value;
			}
		}
		public DockPanelSkin()
		{
			this.m_autoHideStripSkin = new AutoHideStripSkin();
			this.m_dockPaneStripSkin = new DockPaneStripSkin();
		}
	}
}
