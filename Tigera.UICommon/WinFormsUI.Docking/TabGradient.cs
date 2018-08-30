using System;
using System.ComponentModel;
using System.Drawing;
namespace WinFormsUI.Docking
{
	[TypeConverter(typeof(DockPaneTabGradientConverter))]
	public class TabGradient : DockPanelGradient
	{
		private Color m_textColor;
		[DefaultValue(typeof(SystemColors), "ControlText")]
		public Color TextColor
		{
			get
			{
				return this.m_textColor;
			}
			set
			{
				this.m_textColor = value;
			}
		}
		public TabGradient()
		{
			this.m_textColor = SystemColors.ControlText;
		}
	}
}
