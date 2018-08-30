using System;
using System.ComponentModel;
namespace WinFormsUI.Docking
{
	[TypeConverter(typeof(DockPaneStripGradientConverter))]
	public class DockPaneStripGradient
	{
		private DockPanelGradient m_dockStripGradient;
		private TabGradient m_activeTabGradient;
		private TabGradient m_inactiveTabGradient;
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
		public TabGradient ActiveTabGradient
		{
			get
			{
				return this.m_activeTabGradient;
			}
			set
			{
				this.m_activeTabGradient = value;
			}
		}
		public TabGradient InactiveTabGradient
		{
			get
			{
				return this.m_inactiveTabGradient;
			}
			set
			{
				this.m_inactiveTabGradient = value;
			}
		}
		public DockPaneStripGradient()
		{
			this.m_dockStripGradient = new DockPanelGradient();
			this.m_activeTabGradient = new TabGradient();
			this.m_inactiveTabGradient = new TabGradient();
		}
	}
}
