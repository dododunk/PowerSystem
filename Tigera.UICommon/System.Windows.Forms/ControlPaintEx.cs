using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
namespace System.Windows.Forms
{
	public sealed class ControlPaintEx
	{
		public static void DrawCheckedFlag(Graphics graphics, Rectangle rect, Color color)
		{
			PointF[] points = new PointF[]
			{
				new PointF((float)rect.X + (float)rect.Width / 4.5f, (float)rect.Y + (float)rect.Height / 2.5f),
				new PointF((float)rect.X + (float)rect.Width / 2.5f, (float)rect.Bottom - (float)rect.Height / 3f),
				new PointF((float)rect.Right - (float)rect.Width / 4f, (float)rect.Y + (float)rect.Height / 4.5f)
			};
			using (Pen pen = new Pen(color, 2f))
			{
				graphics.DrawLines(pen, points);
			}
		}
		public static void DrawGlass(Graphics g, RectangleF glassRect, int alphaCenter, int alphaSurround)
		{
			ControlPaintEx.DrawGlass(g, glassRect, Color.White, alphaCenter, alphaSurround);
		}
		public static void DrawGlass(Graphics g, RectangleF glassRect, Color glassColor, int alphaCenter, int alphaSurround)
		{
			using (GraphicsPath graphicsPath = new GraphicsPath())
			{
				graphicsPath.AddEllipse(glassRect);
				using (PathGradientBrush pathGradientBrush = new PathGradientBrush(graphicsPath))
				{
					pathGradientBrush.CenterColor = Color.FromArgb(alphaCenter, glassColor);
					pathGradientBrush.SurroundColors = new Color[]
					{
						Color.FromArgb(alphaSurround, glassColor)
					};
					pathGradientBrush.CenterPoint = new PointF(glassRect.X + glassRect.Width / 2f, glassRect.Y + glassRect.Height / 2f);
					g.FillPath(pathGradientBrush, graphicsPath);
				}
			}
		}
		public static void DrawBackgroundImage(Graphics g, Image backgroundImage, Color backColor, ImageLayout backgroundImageLayout, Rectangle bounds, Rectangle clipRect)
		{
			ControlPaintEx.DrawBackgroundImage(g, backgroundImage, backColor, backgroundImageLayout, bounds, clipRect, Point.Empty, RightToLeft.No);
		}
		public static void DrawBackgroundImage(Graphics g, Image backgroundImage, Color backColor, ImageLayout backgroundImageLayout, Rectangle bounds, Rectangle clipRect, Point scrollOffset)
		{
			ControlPaintEx.DrawBackgroundImage(g, backgroundImage, backColor, backgroundImageLayout, bounds, clipRect, scrollOffset, RightToLeft.No);
		}
		public static void DrawBackgroundImage(Graphics g, Image backgroundImage, Color backColor, ImageLayout backgroundImageLayout, Rectangle bounds, Rectangle clipRect, Point scrollOffset, RightToLeft rightToLeft)
		{
			if (g == null)
			{
				throw new ArgumentNullException("g");
			}
			if (backgroundImageLayout == ImageLayout.Tile)
			{
				using (TextureBrush textureBrush = new TextureBrush(backgroundImage, WrapMode.Tile))
				{
					if (scrollOffset != Point.Empty)
					{
						Matrix transform = textureBrush.Transform;
						transform.Translate((float)scrollOffset.X, (float)scrollOffset.Y);
						textureBrush.Transform = transform;
					}
					g.FillRectangle(textureBrush, clipRect);
					return;
				}
			}
			Rectangle rectangle = ControlPaintEx.CalculateBackgroundImageRectangle(bounds, backgroundImage, backgroundImageLayout);
			checked
			{
				if (rightToLeft == RightToLeft.Yes && backgroundImageLayout == ImageLayout.None)
				{
					rectangle.X += clipRect.Width - rectangle.Width;
				}
				using (SolidBrush solidBrush = new SolidBrush(backColor))
				{
					g.FillRectangle(solidBrush, clipRect);
				}
				if (!clipRect.Contains(rectangle))
				{
					if (backgroundImageLayout == ImageLayout.Stretch || backgroundImageLayout == ImageLayout.Zoom)
					{
						rectangle.Intersect(clipRect);
						g.DrawImage(backgroundImage, rectangle);
					}
					else
					{
						if (backgroundImageLayout == ImageLayout.None)
						{
							rectangle.Offset(clipRect.Location);
							Rectangle destRect = rectangle;
							destRect.Intersect(clipRect);
							Rectangle rectangle2 = new Rectangle(Point.Empty, destRect.Size);
							g.DrawImage(backgroundImage, destRect, rectangle2.X, rectangle2.Y, rectangle2.Width, rectangle2.Height, GraphicsUnit.Pixel);
						}
						else
						{
							Rectangle destRect2 = rectangle;
							destRect2.Intersect(clipRect);
							Rectangle rectangle3 = new Rectangle(new Point(destRect2.X - rectangle.X, destRect2.Y - rectangle.Y), destRect2.Size);
							g.DrawImage(backgroundImage, destRect2, rectangle3.X, rectangle3.Y, rectangle3.Width, rectangle3.Height, GraphicsUnit.Pixel);
						}
					}
				}
				else
				{
					ImageAttributes imageAttributes = new ImageAttributes();
					imageAttributes.SetWrapMode(WrapMode.TileFlipXY);
					g.DrawImage(backgroundImage, rectangle, 0, 0, backgroundImage.Width, backgroundImage.Height, GraphicsUnit.Pixel, imageAttributes);
					imageAttributes.Dispose();
				}
			}
		}
		internal static Rectangle CalculateBackgroundImageRectangle(Rectangle bounds, Image backgroundImage, ImageLayout imageLayout)
		{
			Rectangle rectangle = bounds;
			checked
			{
				Rectangle result;
				if (backgroundImage != null)
				{
					switch (imageLayout)
					{
					case ImageLayout.None:
						rectangle.Size = backgroundImage.Size;
						result = rectangle;
						return result;

					case ImageLayout.Tile:
						result = rectangle;
						return result;

					case ImageLayout.Center:
						{
							rectangle.Size = backgroundImage.Size;
							Size size = bounds.Size;
							if (size.Width > rectangle.Width)
							{
								rectangle.X = (size.Width - rectangle.Width) / 2;
							}
							if (size.Height > rectangle.Height)
							{
								rectangle.Y = (size.Height - rectangle.Height) / 2;
							}
							result = rectangle;
							return result;
						}

					case ImageLayout.Stretch:
						rectangle.Size = bounds.Size;
						result = rectangle;
						return result;

					case ImageLayout.Zoom:
						{
							Size size2 = backgroundImage.Size;
							float num = (float)bounds.Width / (float)size2.Width;
							float num2 = (float)bounds.Height / (float)size2.Height;
							if (num >= num2)
							{
								rectangle.Height = bounds.Height;
								rectangle.Width = (int)unchecked((double)((float)size2.Width * num2) + 0.5);
								if (bounds.X >= 0)
								{
									rectangle.X = (bounds.Width - rectangle.Width) / 2;
								}
								result = rectangle;
								return result;
							}
							rectangle.Width = bounds.Width;
							rectangle.Height = (int)unchecked((double)((float)size2.Height * num) + 0.5);
							if (bounds.Y >= 0)
							{
								rectangle.Y = (bounds.Height - rectangle.Height) / 2;
							}
							result = rectangle;
							return result;
						}
					}
				}
				result = rectangle;
				return result;
			}
		}
	}
}
