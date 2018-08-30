using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;
namespace WinFormsUI.Docking
{
	internal static class DrawHelper
	{
		public static Point RtlTransform(Control control, Point point)
		{
			Point result;
			if (control.RightToLeft != RightToLeft.Yes)
			{
				result = point;
			}
			else
			{
				result = new Point(checked(control.Right - point.X), point.Y);
			}
			return result;
		}
		public static Rectangle RtlTransform(Control control, Rectangle rectangle)
		{
			Rectangle result;
			if (control.RightToLeft != RightToLeft.Yes)
			{
				result = rectangle;
			}
			else
			{
				result = new Rectangle(checked(control.ClientRectangle.Right - rectangle.Right), rectangle.Y, rectangle.Width, rectangle.Height);
			}
			return result;
		}
		public static GraphicsPath GetRoundedCornerTab(GraphicsPath graphicsPath, Rectangle rect, bool upCorner)
		{
			if (graphicsPath == null)
			{
				graphicsPath = new GraphicsPath();
			}
			else
			{
				graphicsPath.Reset();
			}
			int num = 6;
			checked
			{
				if (upCorner)
				{
					graphicsPath.AddLine(rect.Left, rect.Bottom, rect.Left, rect.Top + num / 2);
					graphicsPath.AddArc(new Rectangle(rect.Left, rect.Top, num, num), 180f, 90f);
					graphicsPath.AddLine(rect.Left + num / 2, rect.Top, rect.Right - num / 2, rect.Top);
					graphicsPath.AddArc(new Rectangle(rect.Right - num, rect.Top, num, num), -90f, 90f);
					graphicsPath.AddLine(rect.Right, rect.Top + num / 2, rect.Right, rect.Bottom);
				}
				else
				{
					graphicsPath.AddLine(rect.Right, rect.Top, rect.Right, rect.Bottom - num / 2);
					graphicsPath.AddArc(new Rectangle(rect.Right - num, rect.Bottom - num, num, num), 0f, 90f);
					graphicsPath.AddLine(rect.Right - num / 2, rect.Bottom, rect.Left + num / 2, rect.Bottom);
					graphicsPath.AddArc(new Rectangle(rect.Left, rect.Bottom - num, num, num), 90f, 90f);
					graphicsPath.AddLine(rect.Left, rect.Bottom - num / 2, rect.Left, rect.Top);
				}
				return graphicsPath;
			}
		}
		public static GraphicsPath CalculateGraphicsPathFromBitmap(Bitmap bitmap)
		{
			return DrawHelper.CalculateGraphicsPathFromBitmap(bitmap, Color.Empty);
		}
		public static GraphicsPath CalculateGraphicsPathFromBitmap(Bitmap bitmap, Color colorTransparent)
		{
			GraphicsPath graphicsPath = new GraphicsPath();
			if (colorTransparent == Color.Empty)
			{
				colorTransparent = bitmap.GetPixel(0, 0);
			}
			checked
			{
				for (int i = 0; i < bitmap.Height; i++)
				{
					for (int j = 0; j < bitmap.Width; j++)
					{
						if (bitmap.GetPixel(j, i) != colorTransparent)
						{
							int num = j;
							int k;
							for (k = num; k < bitmap.Width; k++)
							{
								if (bitmap.GetPixel(k, i) == colorTransparent)
								{
									break;
								}
							}
							graphicsPath.AddRectangle(new Rectangle(num, i, k - num, 1));
							j = k;
						}
					}
				}
				return graphicsPath;
			}
		}
	}
}
