using System;
using System.ComponentModel;
namespace WinFormsUI.Docking
{
	[TypeConverter(typeof(DockPaneStripGradientConverter))]
	public class DockPaneStripToolWindowGradient : DockPaneStripGradient
	{
		private TabGradient m_activeCaptionGradient;
		private TabGradient m_inactiveCaptionGradient;
		public TabGradient ActiveCaptionGradient
		{
			get
			{
				return this.m_activeCaptionGradient;
			}
			set
			{
				this.m_activeCaptionGradient = value;
			}
		}
		public TabGradient InactiveCaptionGradient
		{
			get
			{
				return this.m_inactiveCaptionGradient;
			}
			set
			{
				this.m_inactiveCaptionGradient = value;
			}
		}
		public DockPaneStripToolWindowGradient()
		{
			this.m_activeCaptionGradient = new TabGradient();
			this.m_inactiveCaptionGradient = new TabGradient();
		}
	}
}
