using System;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Drawing2D;
namespace WinFormsUI.Docking
{
	[TypeConverter(typeof(DockPaneStripConverter))]
	public class DockPaneStripSkin
	{
		private DockPaneStripGradient m_DocumentGradient;
		private DockPaneStripToolWindowGradient m_ToolWindowGradient;
		private Font m_textFont;
		public DockPaneStripGradient DocumentGradient
		{
			get
			{
				return this.m_DocumentGradient;
			}
			set
			{
				this.m_DocumentGradient = value;
			}
		}
		public DockPaneStripToolWindowGradient ToolWindowGradient
		{
			get
			{
				return this.m_ToolWindowGradient;
			}
			set
			{
				this.m_ToolWindowGradient = value;
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
		public DockPaneStripSkin()
		{
			this.m_DocumentGradient = new DockPaneStripGradient();
			this.m_DocumentGradient.DockStripGradient.StartColor = Color.FromArgb(41, 57, 85);
			this.m_DocumentGradient.DockStripGradient.EndColor = Color.FromArgb(41, 57, 85);
			this.m_DocumentGradient.ActiveTabGradient.StartColor = Color.White;
			this.m_DocumentGradient.ActiveTabGradient.EndColor = Color.FromArgb(255, 231, 165);
			this.m_DocumentGradient.ActiveTabGradient.LinearGradientMode = LinearGradientMode.Vertical;
			this.m_DocumentGradient.ActiveTabGradient.TextColor = Color.Black;
			this.m_DocumentGradient.InactiveTabGradient.StartColor = Color.FromArgb(41, 57, 85);
			this.m_DocumentGradient.InactiveTabGradient.EndColor = Color.FromArgb(41, 57, 85);
			this.m_DocumentGradient.InactiveTabGradient.TextColor = Color.White;
			this.m_DocumentGradient.InactiveTabGradient.LinearGradientMode = LinearGradientMode.Vertical;
			this.m_ToolWindowGradient = new DockPaneStripToolWindowGradient();
			this.m_ToolWindowGradient.DockStripGradient.StartColor = Color.FromArgb(41, 57, 85);
			this.m_ToolWindowGradient.DockStripGradient.EndColor = Color.FromArgb(41, 57, 85);
			this.m_ToolWindowGradient.ActiveCaptionGradient.StartColor = Color.White;
			this.m_ToolWindowGradient.ActiveCaptionGradient.EndColor = Color.FromArgb(255, 231, 165);
			this.m_ToolWindowGradient.ActiveCaptionGradient.LinearGradientMode = LinearGradientMode.Vertical;
			this.m_ToolWindowGradient.InactiveCaptionGradient.StartColor = Color.FromArgb(75, 94, 129);
			this.m_ToolWindowGradient.InactiveCaptionGradient.EndColor = Color.FromArgb(62, 83, 120);
			this.m_ToolWindowGradient.InactiveCaptionGradient.LinearGradientMode = LinearGradientMode.Vertical;
			this.m_ToolWindowGradient.InactiveCaptionGradient.TextColor = Color.White;
			this.m_ToolWindowGradient.ActiveTabGradient.StartColor = Color.White;
			this.m_ToolWindowGradient.ActiveTabGradient.EndColor = Color.FromArgb(255, 231, 165);
			this.m_ToolWindowGradient.ActiveTabGradient.LinearGradientMode = LinearGradientMode.Vertical;
			this.m_ToolWindowGradient.InactiveTabGradient.StartColor = Color.FromArgb(41, 57, 85);
			this.m_ToolWindowGradient.InactiveTabGradient.EndColor = Color.FromArgb(41, 57, 85);
			this.m_ToolWindowGradient.InactiveTabGradient.TextColor = Color.White;
			this.m_textFont = SystemFonts.MenuFont;
		}
	}
}
