using System;
using System.Drawing;
using System.Drawing.Drawing2D;
namespace System.Windows.Forms
{
	public static class GraphicsPathHelper
	{
		internal static void RenderSeparatorLine(Graphics g, Rectangle rect, Color baseColor, Color backColor, Color shadowColor, bool vertical)
		{
			float angle;
			if (vertical)
			{
				angle = 90f;
			}
			else
			{
				angle = 180f;
			}
			checked
			{
				using (LinearGradientBrush linearGradientBrush = new LinearGradientBrush(rect, baseColor, backColor, angle))
				{
					linearGradientBrush.Blend = new Blend
					{
						Positions = new float[]
						{
							0f,
							0.3f,
							0.5f,
							0.7f,
							1f
						},
						Factors = new float[]
						{
							1f,
							0.3f,
							0f,
							0.3f,
							1f
						}
					};
					using (Pen pen = new Pen(linearGradientBrush))
					{
						if (vertical)
						{
							g.DrawLine(pen, rect.X, rect.Y, rect.X, rect.Bottom);
						}
						else
						{
							g.DrawLine(pen, rect.X, rect.Y, rect.Right, rect.Y);
						}
						linearGradientBrush.LinearColors = new Color[]
						{
							shadowColor,
							backColor
						};
						pen.Brush = linearGradientBrush;
						if (vertical)
						{
							g.DrawLine(pen, rect.X + 1, rect.Y, rect.X + 1, rect.Bottom);
						}
						else
						{
							g.DrawLine(pen, rect.X, rect.Y + 1, rect.Right, rect.Y + 1);
						}
					}
				}
			}
		}
		public static GraphicsPath CreatePath(Rectangle rect, int radius, RoundStyle style, bool correction)
		{
			GraphicsPath graphicsPath = new GraphicsPath();
			int num = correction ? 1 : 0;
			checked
			{
				switch (style)
				{
				case RoundStyle.None:
					graphicsPath.AddRectangle(rect);
					break;

				case RoundStyle.All:
					graphicsPath.AddArc(rect.X, rect.Y, radius, radius, 180f, 90f);
					graphicsPath.AddArc(rect.Right - radius - num, rect.Y, radius, radius, 270f, 90f);
					graphicsPath.AddArc(rect.Right - radius - num, rect.Bottom - radius - num, radius, radius, 0f, 90f);
					graphicsPath.AddArc(rect.X, rect.Bottom - radius - num, radius, radius, 90f, 90f);
					break;

				case RoundStyle.Left:
					graphicsPath.AddArc(rect.X, rect.Y, radius, radius, 180f, 90f);
					graphicsPath.AddLine(rect.Right - num, rect.Y, rect.Right - num, rect.Bottom - num);
					graphicsPath.AddArc(rect.X, rect.Bottom - radius - num, radius, radius, 90f, 90f);
					break;

				case RoundStyle.Right:
					graphicsPath.AddArc(rect.Right - radius - num, rect.Y, radius, radius, 270f, 90f);
					graphicsPath.AddArc(rect.Right - radius - num, rect.Bottom - radius - num, radius, radius, 0f, 90f);
					graphicsPath.AddLine(rect.X, rect.Bottom - num, rect.X, rect.Y);
					break;

				case RoundStyle.Top:
					graphicsPath.AddArc(rect.X, rect.Y, radius, radius, 180f, 90f);
					graphicsPath.AddArc(rect.Right - radius - num, rect.Y, radius, radius, 270f, 90f);
					graphicsPath.AddLine(rect.Right - num, rect.Bottom - num, rect.X, rect.Bottom - num);
					break;

				case RoundStyle.Bottom:
					graphicsPath.AddArc(rect.Right - radius - num, rect.Bottom - radius - num, radius, radius, 0f, 90f);
					graphicsPath.AddArc(rect.X, rect.Bottom - radius - num, radius, radius, 90f, 90f);
					graphicsPath.AddLine(rect.X, rect.Y, rect.Right - num, rect.Y);
					break;

				case RoundStyle.BottomLeft:
					graphicsPath.AddArc(rect.X, rect.Bottom - radius - num, radius, radius, 90f, 90f);
					graphicsPath.AddLine(rect.X, rect.Y, rect.Right - num, rect.Y);
					graphicsPath.AddLine(rect.Right - num, rect.Y, rect.Right - num, rect.Bottom - num);
					break;

				case RoundStyle.BottomRight:
					graphicsPath.AddArc(rect.Right - radius - num, rect.Bottom - radius - num, radius, radius, 0f, 90f);
					graphicsPath.AddLine(rect.X, rect.Bottom - num, rect.X, rect.Y);
					graphicsPath.AddLine(rect.X, rect.Y, rect.Right - num, rect.Y);
					break;
				}
				graphicsPath.CloseFigure();
				return graphicsPath;
			}
		}
	}
}
