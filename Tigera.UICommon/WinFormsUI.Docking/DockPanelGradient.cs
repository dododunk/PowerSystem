using System;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Drawing2D;
namespace WinFormsUI.Docking
{
	[TypeConverter(typeof(DockPanelGradientConverter))]
	public class DockPanelGradient
	{
		private Color m_startColor;
		private Color m_endColor;
		private LinearGradientMode m_linearGradientMode;
		[DefaultValue(typeof(SystemColors), "Control")]
		public Color StartColor
		{
			get
			{
				return this.m_startColor;
			}
			set
			{
				this.m_startColor = value;
			}
		}
		[DefaultValue(typeof(SystemColors), "Control")]
		public Color EndColor
		{
			get
			{
				return this.m_endColor;
			}
			set
			{
				this.m_endColor = value;
			}
		}
		[DefaultValue(LinearGradientMode.Horizontal)]
		public LinearGradientMode LinearGradientMode
		{
			get
			{
				return this.m_linearGradientMode;
			}
			set
			{
				this.m_linearGradientMode = value;
			}
		}
		public DockPanelGradient()
		{
			this.m_startColor = SystemColors.Control;
			this.m_endColor = SystemColors.Control;
			this.m_linearGradientMode = LinearGradientMode.Horizontal;
		}
	}
}
