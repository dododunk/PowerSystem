using System;
using System.Drawing;
using System.Drawing.Drawing2D;
namespace System.Windows.Forms
{
	public class SkinFormProfessionalRenderer : SkinFormRenderer
	{
		private SkinFormColorTable _colorTable;
		public SkinFormColorTable ColorTable
		{
			get
			{
				if (this._colorTable == null)
				{
					this._colorTable = new SkinFormColorTable();
				}
				return this._colorTable;
			}
		}
		public SkinFormProfessionalRenderer()
		{
		}
		public SkinFormProfessionalRenderer(SkinFormColorTable colortable)
		{
			this._colorTable = colortable;
		}
		public override Region CreateRegion(SkinForm form)
		{
			Rectangle rect = new Rectangle(Point.Empty, form.Size);
			Region result;
			using (GraphicsPath graphicsPath = GraphicsPathHelper.CreatePath(rect, form.Radius, form.RoundStyle, false))
			{
				result = new Region(graphicsPath);
			}
			return result;
		}
		public override void InitSkinForm(SkinForm form)
		{
			form.BackColor = this.ColorTable.Back;
		}
		protected override void OnRenderSkinFormCaption(SkinFormCaptionRenderEventArgs e)
		{
			Graphics graphics = e.Graphics;
			Rectangle clipRectangle = e.ClipRectangle;
			SkinForm skinForm = e.SkinForm;
			Rectangle iconRect = skinForm.IconRect;
			Rectangle empty = Rectangle.Empty;
			bool controlBox = skinForm.ControlBox;
			bool flag = skinForm.ControlBox && skinForm.MinimizeBox;
			bool flag2 = skinForm.ControlBox && skinForm.MaximizeBox;
			int num = 0;
			checked
			{
				if (controlBox)
				{
					num += skinForm.CloseBoxSize.Width + skinForm.ControlBoxOffset.X;
				}
				if (flag2)
				{
					num += skinForm.MaximizeBoxSize.Width + skinForm.ControlBoxSpace;
				}
				if (flag)
				{
					num += skinForm.MinimizeBoxSize.Width + skinForm.ControlBoxSpace;
				}
				empty = new Rectangle(iconRect.Right + 3, skinForm.BorderWidth, clipRectangle.Width - iconRect.Right - num - 6, clipRectangle.Height - skinForm.BorderWidth);
				using (new AntiAliasGraphics(graphics))
				{
					this.DrawCaptionBackground(graphics, clipRectangle, e.Active);
					if (skinForm.ShowIcon && skinForm.Icon != null)
					{
						this.DrawIcon(graphics, iconRect, skinForm.Icon);
					}
					if (!string.IsNullOrEmpty(skinForm.Text))
					{
						this.DrawCaptionText(graphics, empty, skinForm.Text, skinForm.CaptionFont);
					}
				}
			}
		}
		protected override void OnRenderSkinFormBorder(SkinFormBorderRenderEventArgs e)
		{
			Graphics graphics = e.Graphics;
			using (new AntiAliasGraphics(graphics))
			{
				this.DrawBorder(graphics, e.ClipRectangle, e.SkinForm.RoundStyle, e.SkinForm.Radius);
			}
		}
		protected override void OnRenderSkinFormBackground(SkinFormBackgroundRenderEventArgs e)
		{
			Graphics graphics = e.Graphics;
			Rectangle clipRectangle = e.ClipRectangle;
			SkinForm skinForm = e.SkinForm;
			using (new AntiAliasGraphics(graphics))
			{
				using (Brush brush = new SolidBrush(this.ColorTable.Back))
				{
					using (GraphicsPath graphicsPath = GraphicsPathHelper.CreatePath(clipRectangle, skinForm.Radius, skinForm.RoundStyle, false))
					{
						graphics.FillPath(brush, graphicsPath);
					}
				}
			}
		}
		protected override void OnRenderSkinFormControlBox(SkinFormControlBoxRenderEventArgs e)
		{
			SkinForm form = e.Form;
			Graphics graphics = e.Graphics;
			Rectangle clipRectangle = e.ClipRectangle;
			ControlBoxState controlBoxtate = e.ControlBoxtate;
			bool active = e.Active;
			bool minimizeBox = form.ControlBox && form.MinimizeBox;
			bool maximizeBox = form.ControlBox && form.MaximizeBox;
			switch (e.ControlBoxStyle)
			{
			case ControlBoxStyle.Minimize:
				this.RenderSkinFormMinimizeBoxInternal(graphics, clipRectangle, controlBoxtate, active);
				break;

			case ControlBoxStyle.Maximize:
				this.RenderSkinFormMaximizeBoxInternal(graphics, clipRectangle, controlBoxtate, active, minimizeBox, form.WindowState == FormWindowState.Maximized);
				break;

			case ControlBoxStyle.Close:
				this.RenderSkinFormCloseBoxInternal(graphics, clipRectangle, controlBoxtate, active, minimizeBox, maximizeBox);
				break;
			}
		}
		private void DrawCaptionBackground(Graphics g, Rectangle captionRect, bool active)
		{
			Color baseColor = active ? this.ColorTable.CaptionActive : this.ColorTable.CaptionDeactive;
			RenderHelper.RenderBackgroundInternal(g, captionRect, baseColor, this.ColorTable.Border, this.ColorTable.InnerBorder, RoundStyle.None, 0, 0.02f, false, false, LinearGradientMode.Vertical);
		}
		private void DrawIcon(Graphics g, Rectangle iconRect, Icon icon)
		{
			g.InterpolationMode = InterpolationMode.HighQualityBicubic;
			g.DrawIcon(icon, iconRect);
		}
		private void DrawCaptionText(Graphics g, Rectangle textRect, string text, Font font)
		{
			TextRenderer.DrawText(g, text, font, textRect, this.ColorTable.CaptionText, TextFormatFlags.SingleLine | TextFormatFlags.VerticalCenter | TextFormatFlags.WordEllipsis);
		}
		private void DrawBorder(Graphics g, Rectangle rect, RoundStyle roundStyle, int radius)
		{
			checked
			{
				rect.Width--;
				rect.Height--;
				using (GraphicsPath graphicsPath = GraphicsPathHelper.CreatePath(rect, radius, roundStyle, false))
				{
					using (Pen pen = new Pen(this.ColorTable.Border))
					{
						g.DrawPath(pen, graphicsPath);
					}
				}
				rect.Inflate(-1, -1);
				using (GraphicsPath graphicsPath = GraphicsPathHelper.CreatePath(rect, radius, roundStyle, false))
				{
					using (Pen pen = new Pen(this.ColorTable.InnerBorder))
					{
						g.DrawPath(pen, graphicsPath);
					}
				}
			}
		}
		private void RenderSkinFormMinimizeBoxInternal(Graphics g, Rectangle rect, ControlBoxState state, bool active)
		{
			Color color = this.ColorTable.ControlBoxActive;
			if (state == ControlBoxState.Pressed)
			{
				color = this.ColorTable.ControlBoxPressed;
			}
			else
			{
				if (state == ControlBoxState.Hover)
				{
					color = this.ColorTable.ControlBoxHover;
				}
				else
				{
					color = (active ? this.ColorTable.ControlBoxActive : this.ColorTable.ControlBoxDeactive);
				}
			}
			RoundStyle style = RoundStyle.BottomLeft;
			using (new AntiAliasGraphics(g))
			{
				RenderHelper.RenderBackgroundInternal(g, rect, color, color, this.ColorTable.ControlBoxInnerBorder, style, 6, 0.38f, true, false, LinearGradientMode.Vertical);
				using (Pen pen = new Pen(this.ColorTable.Border))
				{
					g.DrawLine(pen, rect.X, rect.Y, rect.Right, rect.Y);
				}
				using (GraphicsPath graphicsPath = this.CreateMinimizeFlagPath(rect))
				{
					g.FillPath(Brushes.White, graphicsPath);
					using (Pen pen = new Pen(color))
					{
						g.DrawPath(pen, graphicsPath);
					}
				}
			}
		}
		private void RenderSkinFormMaximizeBoxInternal(Graphics g, Rectangle rect, ControlBoxState state, bool active, bool minimizeBox, bool maximize)
		{
			Color color = this.ColorTable.ControlBoxActive;
			if (state == ControlBoxState.Pressed)
			{
				color = this.ColorTable.ControlBoxPressed;
			}
			else
			{
				if (state == ControlBoxState.Hover)
				{
					color = this.ColorTable.ControlBoxHover;
				}
				else
				{
					color = (active ? this.ColorTable.ControlBoxActive : this.ColorTable.ControlBoxDeactive);
				}
			}
			RoundStyle style = minimizeBox ? RoundStyle.None : RoundStyle.BottomLeft;
			using (new AntiAliasGraphics(g))
			{
				RenderHelper.RenderBackgroundInternal(g, rect, color, color, this.ColorTable.ControlBoxInnerBorder, style, 6, 0.38f, true, false, LinearGradientMode.Vertical);
				using (Pen pen = new Pen(this.ColorTable.Border))
				{
					g.DrawLine(pen, rect.X, rect.Y, rect.Right, rect.Y);
				}
				using (GraphicsPath graphicsPath = this.CreateMaximizeFlafPath(rect, maximize))
				{
					g.FillPath(Brushes.White, graphicsPath);
					using (Pen pen = new Pen(color))
					{
						g.DrawPath(pen, graphicsPath);
					}
				}
			}
		}
		private void RenderSkinFormCloseBoxInternal(Graphics g, Rectangle rect, ControlBoxState state, bool active, bool minimizeBox, bool maximizeBox)
		{
			Color color = this.ColorTable.ControlBoxActive;
			if (state == ControlBoxState.Pressed)
			{
				color = this.ColorTable.ControlCloseBoxPressed;
			}
			else
			{
				if (state == ControlBoxState.Hover)
				{
					color = this.ColorTable.ControlCloseBoxHover;
				}
				else
				{
					color = (active ? this.ColorTable.ControlBoxActive : this.ColorTable.ControlBoxDeactive);
				}
			}
			RoundStyle style = (minimizeBox || maximizeBox) ? RoundStyle.BottomRight : RoundStyle.Bottom;
			using (new AntiAliasGraphics(g))
			{
				RenderHelper.RenderBackgroundInternal(g, rect, color, color, this.ColorTable.ControlBoxInnerBorder, style, 6, 0.38f, true, false, LinearGradientMode.Vertical);
				using (Pen pen = new Pen(this.ColorTable.Border))
				{
					g.DrawLine(pen, rect.X, rect.Y, rect.Right, rect.Y);
				}
				using (GraphicsPath graphicsPath = this.CreateCloseFlagPath(rect))
				{
					g.FillPath(Brushes.White, graphicsPath);
					using (Pen pen = new Pen(color))
					{
						g.DrawPath(pen, graphicsPath);
					}
				}
			}
		}
		private GraphicsPath CreateCloseFlagPath(Rectangle rect)
		{
			PointF pointF = new PointF((float)rect.X + (float)rect.Width / 2f, (float)rect.Y + (float)rect.Height / 2f);
			GraphicsPath graphicsPath = new GraphicsPath();
			graphicsPath.AddLine(pointF.X, pointF.Y - 2f, pointF.X - 2f, pointF.Y - 4f);
			graphicsPath.AddLine(pointF.X - 2f, pointF.Y - 4f, pointF.X - 6f, pointF.Y - 4f);
			graphicsPath.AddLine(pointF.X - 6f, pointF.Y - 4f, pointF.X - 2f, pointF.Y);
			graphicsPath.AddLine(pointF.X - 2f, pointF.Y, pointF.X - 6f, pointF.Y + 4f);
			graphicsPath.AddLine(pointF.X - 6f, pointF.Y + 4f, pointF.X - 2f, pointF.Y + 4f);
			graphicsPath.AddLine(pointF.X - 2f, pointF.Y + 4f, pointF.X, pointF.Y + 2f);
			graphicsPath.AddLine(pointF.X, pointF.Y + 2f, pointF.X + 2f, pointF.Y + 4f);
			graphicsPath.AddLine(pointF.X + 2f, pointF.Y + 4f, pointF.X + 6f, pointF.Y + 4f);
			graphicsPath.AddLine(pointF.X + 6f, pointF.Y + 4f, pointF.X + 2f, pointF.Y);
			graphicsPath.AddLine(pointF.X + 2f, pointF.Y, pointF.X + 6f, pointF.Y - 4f);
			graphicsPath.AddLine(pointF.X + 6f, pointF.Y - 4f, pointF.X + 2f, pointF.Y - 4f);
			graphicsPath.CloseFigure();
			return graphicsPath;
		}
		private GraphicsPath CreateMinimizeFlagPath(Rectangle rect)
		{
			PointF pointF = new PointF((float)rect.X + (float)rect.Width / 2f, (float)rect.Y + (float)rect.Height / 2f);
			GraphicsPath graphicsPath = new GraphicsPath();
			graphicsPath.AddRectangle(new RectangleF(pointF.X - 6f, pointF.Y + 1f, 12f, 3f));
			return graphicsPath;
		}
		private GraphicsPath CreateMaximizeFlafPath(Rectangle rect, bool maximize)
		{
			PointF pointF = new PointF((float)rect.X + (float)rect.Width / 2f, (float)rect.Y + (float)rect.Height / 2f);
			GraphicsPath graphicsPath = new GraphicsPath();
			if (maximize)
			{
				graphicsPath.AddLine(pointF.X - 3f, pointF.Y - 3f, pointF.X - 6f, pointF.Y - 3f);
				graphicsPath.AddLine(pointF.X - 6f, pointF.Y - 3f, pointF.X - 6f, pointF.Y + 5f);
				graphicsPath.AddLine(pointF.X - 6f, pointF.Y + 5f, pointF.X + 3f, pointF.Y + 5f);
				graphicsPath.AddLine(pointF.X + 3f, pointF.Y + 5f, pointF.X + 3f, pointF.Y + 1f);
				graphicsPath.AddLine(pointF.X + 3f, pointF.Y + 1f, pointF.X + 6f, pointF.Y + 1f);
				graphicsPath.AddLine(pointF.X + 6f, pointF.Y + 1f, pointF.X + 6f, pointF.Y - 6f);
				graphicsPath.AddLine(pointF.X + 6f, pointF.Y - 6f, pointF.X - 3f, pointF.Y - 6f);
				graphicsPath.CloseFigure();
				graphicsPath.AddRectangle(new RectangleF(pointF.X - 4f, pointF.Y, 5f, 3f));
				graphicsPath.AddLine(pointF.X - 1f, pointF.Y - 4f, pointF.X + 4f, pointF.Y - 4f);
				graphicsPath.AddLine(pointF.X + 4f, pointF.Y - 4f, pointF.X + 4f, pointF.Y - 1f);
				graphicsPath.AddLine(pointF.X + 4f, pointF.Y - 1f, pointF.X + 3f, pointF.Y - 1f);
				graphicsPath.AddLine(pointF.X + 3f, pointF.Y - 1f, pointF.X + 3f, pointF.Y - 3f);
				graphicsPath.AddLine(pointF.X + 3f, pointF.Y - 3f, pointF.X - 1f, pointF.Y - 3f);
				graphicsPath.CloseFigure();
			}
			else
			{
				graphicsPath.AddRectangle(new RectangleF(pointF.X - 6f, pointF.Y - 4f, 12f, 8f));
				graphicsPath.AddRectangle(new RectangleF(pointF.X - 3f, pointF.Y - 1f, 6f, 3f));
			}
			return graphicsPath;
		}
	}
}
