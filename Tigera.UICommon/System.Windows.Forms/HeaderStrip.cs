using Microsoft.Win32;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Drawing2D;
namespace System.Windows.Forms
{
	public class HeaderStrip : ToolStrip
	{
		private AreaHeaderStyle _headerStyle = AreaHeaderStyle.Large;
		private ToolStripProfessionalRenderer _pr = null;
		[DefaultValue(AreaHeaderStyle.Large)]
		public AreaHeaderStyle HeaderStyle
		{
			get
			{
				return this._headerStyle;
			}
			set
			{
				if (this._headerStyle != value)
				{
					this._headerStyle = value;
					this.SetHeaderStyle();
				}
			}
		}
		public HeaderStrip()
		{
			this.Dock = DockStyle.Top;
			base.GripStyle = ToolStripGripStyle.Hidden;
			this.AutoSize = false;
			this.SetRenderer();
			SystemEvents.UserPreferenceChanged += new UserPreferenceChangedEventHandler(this.HeaderStrip_UserPreferenceChanged);
			this.SetHeaderStyle();
		}
		protected override void OnRendererChanged(EventArgs e)
		{
			base.OnRendererChanged(e);
			this.SetRenderer();
		}
		private void SetHeaderStyle()
		{
			Font menuFont = SystemFonts.MenuFont;
			if (this._headerStyle == AreaHeaderStyle.Large)
			{
				this.Font = new Font("宋体", menuFont.SizeInPoints + 1f, FontStyle.Bold);
				base.ForeColor = Color.White;
			}
			else
			{
				this.Font = menuFont;
				base.ForeColor = Color.Black;
			}
			base.Height = checked(new ToolStripLabel
			{
				Font = this.Font,
				Text = "I"
			}.GetPreferredSize(Size.Empty).Height + 6);
		}
		private void SetRenderer()
		{
			if (base.Renderer is ToolStripProfessionalRenderer && base.Renderer != this._pr)
			{
				if (this._pr == null)
				{
					this._pr = new ToolStripProfessionalRenderer();
					this._pr.RoundedEdges = false;
					this._pr.RenderToolStripBackground += new ToolStripRenderEventHandler(this.Renderer_RenderToolStripBackground);
				}
				base.Renderer = this._pr;
			}
		}
		private void Renderer_RenderToolStripBackground(object sender, ToolStripRenderEventArgs e)
		{
			if (base.Renderer is ToolStripProfessionalRenderer)
			{
				ToolStripProfessionalRenderer toolStripProfessionalRenderer = base.Renderer as ToolStripProfessionalRenderer;
				Color color;
				Color color2;
				if (this._headerStyle == AreaHeaderStyle.Large)
				{
					color = toolStripProfessionalRenderer.ColorTable.OverflowButtonGradientMiddle;
					color2 = toolStripProfessionalRenderer.ColorTable.OverflowButtonGradientEnd;
				}
				else
				{
					color = toolStripProfessionalRenderer.ColorTable.MenuStripGradientEnd;
					color2 = toolStripProfessionalRenderer.ColorTable.MenuStripGradientBegin;
				}
				Rectangle rect = new Rectangle(Point.Empty, e.ToolStrip.Size);
				if (rect.Width > 0 && rect.Height > 0)
				{
					using (Brush brush = new LinearGradientBrush(rect, color, color2, LinearGradientMode.Vertical))
					{
						e.Graphics.FillRectangle(brush, rect);
					}
				}
			}
		}
		private void HeaderStrip_UserPreferenceChanged(object sender, UserPreferenceChangedEventArgs e)
		{
			this.SetHeaderStyle();
		}
	}
}
