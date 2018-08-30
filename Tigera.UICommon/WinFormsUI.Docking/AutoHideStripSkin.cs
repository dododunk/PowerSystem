using System;
using System.ComponentModel;
using System.Drawing;
namespace WinFormsUI.Docking
{
	[TypeConverter(typeof(AutoHideStripConverter))]
	public class AutoHideStripSkin
	{
		private DockPanelGradient m_dockStripGradient;
		private TabGradient m_TabGradient;
		private Font m_textFont;
		public DockPanelGradient DockStripGradient
		{
			get
			{
				return this.m_dockStripGradient;
			}
			set
			{
				this.m_dockStripGradient = value;
			}
		}
		public TabGradient TabGradient
		{
			get
			{
				return this.m_TabGradient;
			}
			set
			{
				this.m_TabGradient = value;
			}
		}
		public Font TextFont
		{
			get
			{
				return this.m_textFont;
			}
			set
			{
				this.m_textFont = value;
			}
		}
		public AutoHideStripSkin()
		{
			this.m_dockStripGradient = new DockPanelGradient();
			this.m_dockStripGradient.StartColor = Color.FromArgb(41, 57, 85);
			this.m_dockStripGradient.EndColor = Color.FromArgb(41, 57, 85);
			this.m_TabGradient = new TabGradient();
			this.m_TabGradient.StartColor = Color.FromArgb(61, 82, 119);
			this.m_TabGradient.EndColor = Color.FromArgb(61, 82, 119);
			this.m_TabGradient.TextColor = Color.White;
			this.m_textFont = SystemFonts.MenuFont;
		}
	}
}
