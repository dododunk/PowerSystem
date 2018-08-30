using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;
namespace WinFormsUI.Docking
{
	internal class VS2005AutoHideStrip : AutoHideStripBase
	{
		private class TabVS2005 : AutoHideStripBase.Tab
		{
			private int m_tabX = 0;
			private int m_tabWidth = 0;
			public int TabX
			{
				get
				{
					return this.m_tabX;
				}
				set
				{
					this.m_tabX = value;
				}
			}
			public int TabWidth
			{
				get
				{
					return this.m_tabWidth;
				}
				set
				{
					this.m_tabWidth = value;
				}
			}
			internal TabVS2005(IDockContent content) : base(content)
			{
			}
		}
		private const int _ImageHeight = 16;
		private const int _ImageWidth = 16;
		private const int _ImageGapTop = 2;
		private const int _ImageGapLeft = 4;
		private const int _ImageGapRight = 2;
		private const int _ImageGapBottom = 2;
		private const int _TextGapLeft = 0;
		private const int _TextGapRight = 0;
		private const int _TabGapTop = 3;
		private const int _TabGapLeft = 4;
		private const int _TabGapBetween = 10;
		private static StringFormat _stringFormatTabHorizontal;
		private static StringFormat _stringFormatTabVertical;
		private static Matrix _matrixIdentity = new Matrix();
		private static DockState[] _dockStates;
		private static GraphicsPath _graphicsPath;
		public Font TextFont
		{
			get
			{
				return base.DockPanel.Skin.AutoHideStripSkin.TextFont;
			}
		}
		private StringFormat StringFormatTabHorizontal
		{
			get
			{
				if (VS2005AutoHideStrip._stringFormatTabHorizontal == null)
				{
					VS2005AutoHideStrip._stringFormatTabHorizontal = new StringFormat();
					VS2005AutoHideStrip._stringFormatTabHorizontal.Alignment = StringAlignment.Near;
					VS2005AutoHideStrip._stringFormatTabHorizontal.LineAlignment = StringAlignment.Center;
					VS2005AutoHideStrip._stringFormatTabHorizontal.FormatFlags = StringFormatFlags.NoWrap;
					VS2005AutoHideStrip._stringFormatTabHorizontal.Trimming = StringTrimming.None;
				}
				if (this.RightToLeft == RightToLeft.Yes)
				{
					VS2005AutoHideStrip._stringFormatTabHorizontal.FormatFlags |= StringFormatFlags.DirectionRightToLeft;
				}
				else
				{
					VS2005AutoHideStrip._stringFormatTabHorizontal.FormatFlags &= ~StringFormatFlags.DirectionRightToLeft;
				}
				return VS2005AutoHideStrip._stringFormatTabHorizontal;
			}
		}
		private StringFormat StringFormatTabVertical
		{
			get
			{
				if (VS2005AutoHideStrip._stringFormatTabVertical == null)
				{
					VS2005AutoHideStrip._stringFormatTabVertical = new StringFormat();
					VS2005AutoHideStrip._stringFormatTabVertical.Alignment = StringAlignment.Near;
					VS2005AutoHideStrip._stringFormatTabVertical.LineAlignment = StringAlignment.Center;
					VS2005AutoHideStrip._stringFormatTabVertical.FormatFlags = (StringFormatFlags.DirectionVertical | StringFormatFlags.NoWrap);
					VS2005AutoHideStrip._stringFormatTabVertical.Trimming = StringTrimming.None;
				}
				if (this.RightToLeft == RightToLeft.Yes)
				{
					VS2005AutoHideStrip._stringFormatTabVertical.FormatFlags |= StringFormatFlags.DirectionRightToLeft;
				}
				else
				{
					VS2005AutoHideStrip._stringFormatTabVertical.FormatFlags &= ~StringFormatFlags.DirectionRightToLeft;
				}
				return VS2005AutoHideStrip._stringFormatTabVertical;
			}
		}
		private static int ImageHeight
		{
			get
			{
				return 16;
			}
		}
		private static int ImageWidth
		{
			get
			{
				return 16;
			}
		}
		private static int ImageGapTop
		{
			get
			{
				return 2;
			}
		}
		private static int ImageGapLeft
		{
			get
			{
				return 4;
			}
		}
		private static int ImageGapRight
		{
			get
			{
				return 2;
			}
		}
		private static int ImageGapBottom
		{
			get
			{
				return 2;
			}
		}
		private static int TextGapLeft
		{
			get
			{
				return 0;
			}
		}
		private static int TextGapRight
		{
			get
			{
				return 0;
			}
		}
		private static int TabGapTop
		{
			get
			{
				return 3;
			}
		}
		private static int TabGapLeft
		{
			get
			{
				return 4;
			}
		}
		private static int TabGapBetween
		{
			get
			{
				return 10;
			}
		}
		private static Pen PenTabBorder
		{
			get
			{
				return SystemPens.ControlDarkDark;
			}
		}
		private static Matrix MatrixIdentity
		{
			get
			{
				return VS2005AutoHideStrip._matrixIdentity;
			}
		}
		private static DockState[] DockStates
		{
			get
			{
				if (VS2005AutoHideStrip._dockStates == null)
				{
					VS2005AutoHideStrip._dockStates = new DockState[4];
					VS2005AutoHideStrip._dockStates[0] = DockState.DockLeftAutoHide;
					VS2005AutoHideStrip._dockStates[1] = DockState.DockRightAutoHide;
					VS2005AutoHideStrip._dockStates[2] = DockState.DockTopAutoHide;
					VS2005AutoHideStrip._dockStates[3] = DockState.DockBottomAutoHide;
				}
				return VS2005AutoHideStrip._dockStates;
			}
		}
		internal static GraphicsPath GraphicsPath
		{
			get
			{
				if (VS2005AutoHideStrip._graphicsPath == null)
				{
					VS2005AutoHideStrip._graphicsPath = new GraphicsPath();
				}
				return VS2005AutoHideStrip._graphicsPath;
			}
		}
		public VS2005AutoHideStrip(DockPanel panel) : base(panel)
		{
			base.SetStyle(ControlStyles.UserPaint | ControlStyles.ResizeRedraw | ControlStyles.AllPaintingInWmPaint | ControlStyles.OptimizedDoubleBuffer, true);
		}
		protected override void OnPaint(PaintEventArgs e)
		{
			Graphics graphics = e.Graphics;
			Color startColor = base.DockPanel.Skin.AutoHideStripSkin.DockStripGradient.StartColor;
			Color endColor = base.DockPanel.Skin.AutoHideStripSkin.DockStripGradient.EndColor;
			LinearGradientMode linearGradientMode = base.DockPanel.Skin.AutoHideStripSkin.DockStripGradient.LinearGradientMode;
			using (LinearGradientBrush linearGradientBrush = new LinearGradientBrush(base.ClientRectangle, startColor, endColor, linearGradientMode))
			{
				graphics.FillRectangle(linearGradientBrush, base.ClientRectangle);
			}
			this.DrawTabStrip(graphics);
		}
		protected override void OnLayout(LayoutEventArgs levent)
		{
			this.CalculateTabs();
			base.OnLayout(levent);
		}
		private void DrawTabStrip(Graphics g)
		{
			this.DrawTabStrip(g, DockState.DockTopAutoHide);
			this.DrawTabStrip(g, DockState.DockBottomAutoHide);
			this.DrawTabStrip(g, DockState.DockLeftAutoHide);
			this.DrawTabStrip(g, DockState.DockRightAutoHide);
		}
		private void DrawTabStrip(Graphics g, DockState dockState)
		{
			Rectangle logicalTabStripRectangle = this.GetLogicalTabStripRectangle(dockState);
			if (!logicalTabStripRectangle.IsEmpty)
			{
				Matrix transform = g.Transform;
				if (dockState == DockState.DockLeftAutoHide || dockState == DockState.DockRightAutoHide)
				{
					Matrix matrix = new Matrix();
					matrix.RotateAt(90f, new PointF((float)logicalTabStripRectangle.X + (float)logicalTabStripRectangle.Height / 2f, (float)logicalTabStripRectangle.Y + (float)logicalTabStripRectangle.Height / 2f));
					g.Transform = matrix;
				}
				foreach (AutoHideStripBase.Pane current in (IEnumerable<AutoHideStripBase.Pane>)base.GetPanes(dockState))
				{
					using (IEnumerator<AutoHideStripBase.Tab> enumerator2 = ((IEnumerable<AutoHideStripBase.Tab>)current.AutoHideTabs).GetEnumerator())
					{
						while (enumerator2.MoveNext())
						{
							VS2005AutoHideStrip.TabVS2005 tab = (VS2005AutoHideStrip.TabVS2005)enumerator2.Current;
							this.DrawTab(g, tab);
						}
					}
				}
				g.Transform = transform;
			}
		}
		private void CalculateTabs()
		{
			this.CalculateTabs(DockState.DockTopAutoHide);
			this.CalculateTabs(DockState.DockBottomAutoHide);
			this.CalculateTabs(DockState.DockLeftAutoHide);
			this.CalculateTabs(DockState.DockRightAutoHide);
		}
		private void CalculateTabs(DockState dockState)
		{
			Rectangle logicalTabStripRectangle = this.GetLogicalTabStripRectangle(dockState);
			checked
			{
				int num = logicalTabStripRectangle.Height - VS2005AutoHideStrip.ImageGapTop - VS2005AutoHideStrip.ImageGapBottom;
				int num2 = VS2005AutoHideStrip.ImageWidth;
				if (num > VS2005AutoHideStrip.ImageHeight)
				{
					num2 = VS2005AutoHideStrip.ImageWidth * (num / VS2005AutoHideStrip.ImageHeight);
				}
				int num3 = VS2005AutoHideStrip.TabGapLeft + logicalTabStripRectangle.X;
				foreach (AutoHideStripBase.Pane current in (IEnumerable<AutoHideStripBase.Pane>)base.GetPanes(dockState))
				{
					using (IEnumerator<AutoHideStripBase.Tab> enumerator2 = ((IEnumerable<AutoHideStripBase.Tab>)current.AutoHideTabs).GetEnumerator())
					{
						while (enumerator2.MoveNext())
						{
							VS2005AutoHideStrip.TabVS2005 tabVS = (VS2005AutoHideStrip.TabVS2005)enumerator2.Current;
							int num4 = num2 + VS2005AutoHideStrip.ImageGapLeft + VS2005AutoHideStrip.ImageGapRight + TextRenderer.MeasureText(tabVS.Content.DockHandler.TabText, this.TextFont).Width + VS2005AutoHideStrip.TextGapLeft + VS2005AutoHideStrip.TextGapRight;
							tabVS.TabX = num3;
							tabVS.TabWidth = num4;
							num3 += num4;
						}
					}
					num3 += VS2005AutoHideStrip.TabGapBetween;
				}
			}
		}
		private Rectangle RtlTransform(Rectangle rect, DockState dockState)
		{
			Rectangle result;
			if (dockState == DockState.DockLeftAutoHide || dockState == DockState.DockRightAutoHide)
			{
				result = rect;
			}
			else
			{
				result = DrawHelper.RtlTransform(this, rect);
			}
			return result;
		}
		private GraphicsPath GetTabOutline(VS2005AutoHideStrip.TabVS2005 tab, bool transformed, bool rtlTransform)
		{
			DockState dockState = tab.Content.DockHandler.DockState;
			Rectangle rect = this.GetTabRectangle(tab, transformed);
			if (rtlTransform)
			{
				rect = this.RtlTransform(rect, dockState);
			}
			bool upCorner = dockState == DockState.DockLeftAutoHide || dockState == DockState.DockBottomAutoHide;
			DrawHelper.GetRoundedCornerTab(VS2005AutoHideStrip.GraphicsPath, rect, upCorner);
			return VS2005AutoHideStrip.GraphicsPath;
		}
		private void DrawTab(Graphics g, VS2005AutoHideStrip.TabVS2005 tab)
		{
			Rectangle tabRectangle = this.GetTabRectangle(tab);
			checked
			{
				if (!tabRectangle.IsEmpty)
				{
					DockState dockState = tab.Content.DockHandler.DockState;
					IDockContent content = tab.Content;
					GraphicsPath tabOutline = this.GetTabOutline(tab, false, true);
					Color startColor = base.DockPanel.Skin.AutoHideStripSkin.TabGradient.StartColor;
					Color endColor = base.DockPanel.Skin.AutoHideStripSkin.TabGradient.EndColor;
					LinearGradientMode linearGradientMode = base.DockPanel.Skin.AutoHideStripSkin.TabGradient.LinearGradientMode;
					g.FillPath(new LinearGradientBrush(tabRectangle, startColor, endColor, linearGradientMode), tabOutline);
					g.DrawPath(VS2005AutoHideStrip.PenTabBorder, tabOutline);
					Matrix transform = g.Transform;
					g.Transform = VS2005AutoHideStrip.MatrixIdentity;
					Rectangle rect = tabRectangle;
					rect.X += VS2005AutoHideStrip.ImageGapLeft;
					rect.Y += VS2005AutoHideStrip.ImageGapTop;
					int num = tabRectangle.Height - VS2005AutoHideStrip.ImageGapTop - VS2005AutoHideStrip.ImageGapBottom;
					int num2 = VS2005AutoHideStrip.ImageWidth;
					if (num > VS2005AutoHideStrip.ImageHeight)
					{
						num2 = VS2005AutoHideStrip.ImageWidth * (num / VS2005AutoHideStrip.ImageHeight);
					}
					rect.Height = num;
					rect.Width = num2;
					rect = this.GetTransformedRectangle(dockState, rect);
					if (dockState == DockState.DockLeftAutoHide || dockState == DockState.DockRightAutoHide)
					{
						Rectangle rectangle = this.RtlTransform(rect, dockState);
						Point[] destPoints = new Point[]
						{
							new Point(rectangle.X + rectangle.Width, rectangle.Y),
							new Point(rectangle.X + rectangle.Width, rectangle.Y + rectangle.Height),
							new Point(rectangle.X, rectangle.Y)
						};
						using (Icon icon = new Icon(((Form)content).Icon, 16, 16))
						{
							g.DrawImage(icon.ToBitmap(), destPoints);
						}
					}
					else
					{
						g.DrawIcon(((Form)content).Icon, this.RtlTransform(rect, dockState));
					}
					Rectangle rectangle2 = tabRectangle;
					rectangle2.X += VS2005AutoHideStrip.ImageGapLeft + num2 + VS2005AutoHideStrip.ImageGapRight + VS2005AutoHideStrip.TextGapLeft;
					rectangle2.Width -= VS2005AutoHideStrip.ImageGapLeft + num2 + VS2005AutoHideStrip.ImageGapRight + VS2005AutoHideStrip.TextGapLeft;
					rectangle2 = this.RtlTransform(this.GetTransformedRectangle(dockState, rectangle2), dockState);
					Color textColor = base.DockPanel.Skin.AutoHideStripSkin.TabGradient.TextColor;
					if (dockState == DockState.DockLeftAutoHide || dockState == DockState.DockRightAutoHide)
					{
						g.DrawString(content.DockHandler.TabText, this.TextFont, new SolidBrush(textColor), rectangle2, this.StringFormatTabVertical);
					}
					else
					{
						g.DrawString(content.DockHandler.TabText, this.TextFont, new SolidBrush(textColor), rectangle2, this.StringFormatTabHorizontal);
					}
					g.Transform = transform;
				}
			}
		}
		private Rectangle GetLogicalTabStripRectangle(DockState dockState)
		{
			return this.GetLogicalTabStripRectangle(dockState, false);
		}
		private Rectangle GetLogicalTabStripRectangle(DockState dockState, bool transformed)
		{
			checked
			{
				Rectangle result;
				if (!DockHelper.IsDockStateAutoHide(dockState))
				{
					result = Rectangle.Empty;
				}
				else
				{
					int count = base.GetPanes(DockState.DockLeftAutoHide).Count;
					int count2 = base.GetPanes(DockState.DockRightAutoHide).Count;
					int count3 = base.GetPanes(DockState.DockTopAutoHide).Count;
					int count4 = base.GetPanes(DockState.DockBottomAutoHide).Count;
					int num = this.MeasureHeight();
					int num2;
					int num3;
					int width;
					if (dockState == DockState.DockLeftAutoHide && count > 0)
					{
						num2 = 0;
						num3 = ((count3 == 0) ? 0 : num);
						width = base.Height - ((count3 == 0) ? 0 : num) - ((count4 == 0) ? 0 : num);
					}
					else
					{
						if (dockState == DockState.DockRightAutoHide && count2 > 0)
						{
							num2 = base.Width - num;
							if (count != 0 && num2 < num)
							{
								num2 = num;
							}
							num3 = ((count3 == 0) ? 0 : num);
							width = base.Height - ((count3 == 0) ? 0 : num) - ((count4 == 0) ? 0 : num);
						}
						else
						{
							if (dockState == DockState.DockTopAutoHide && count3 > 0)
							{
								num2 = ((count == 0) ? 0 : num);
								num3 = 0;
								width = base.Width - ((count == 0) ? 0 : num) - ((count2 == 0) ? 0 : num);
							}
							else
							{
								if (dockState != DockState.DockBottomAutoHide || count4 <= 0)
								{
									result = Rectangle.Empty;
									return result;
								}
								num2 = ((count == 0) ? 0 : num);
								num3 = base.Height - num;
								if (count3 != 0 && num3 < num)
								{
									num3 = num;
								}
								width = base.Width - ((count == 0) ? 0 : num) - ((count2 == 0) ? 0 : num);
							}
						}
					}
					if (!transformed)
					{
						result = new Rectangle(num2, num3, width, num);
					}
					else
					{
						result = this.GetTransformedRectangle(dockState, new Rectangle(num2, num3, width, num));
					}
				}
				return result;
			}
		}
		private Rectangle GetTabRectangle(VS2005AutoHideStrip.TabVS2005 tab)
		{
			return this.GetTabRectangle(tab, false);
		}
		private Rectangle GetTabRectangle(VS2005AutoHideStrip.TabVS2005 tab, bool transformed)
		{
			DockState dockState = tab.Content.DockHandler.DockState;
			Rectangle logicalTabStripRectangle = this.GetLogicalTabStripRectangle(dockState);
			checked
			{
				Rectangle result;
				if (logicalTabStripRectangle.IsEmpty)
				{
					result = Rectangle.Empty;
				}
				else
				{
					int tabX = tab.TabX;
					int y = logicalTabStripRectangle.Y + ((dockState == DockState.DockTopAutoHide || dockState == DockState.DockRightAutoHide) ? 0 : VS2005AutoHideStrip.TabGapTop);
					int tabWidth = tab.TabWidth;
					int height = logicalTabStripRectangle.Height - VS2005AutoHideStrip.TabGapTop;
					if (!transformed)
					{
						result = new Rectangle(tabX, y, tabWidth, height);
					}
					else
					{
						result = this.GetTransformedRectangle(dockState, new Rectangle(tabX, y, tabWidth, height));
					}
				}
				return result;
			}
		}
		private Rectangle GetTransformedRectangle(DockState dockState, Rectangle rect)
		{
			Rectangle result;
			if (dockState != DockState.DockLeftAutoHide && dockState != DockState.DockRightAutoHide)
			{
				result = rect;
			}
			else
			{
				PointF[] array = new PointF[1];
				array[0].X = (float)rect.X + (float)rect.Width / 2f;
				array[0].Y = (float)rect.Y + (float)rect.Height / 2f;
				Rectangle logicalTabStripRectangle = this.GetLogicalTabStripRectangle(dockState);
				Matrix matrix = new Matrix();
				matrix.RotateAt(90f, new PointF((float)logicalTabStripRectangle.X + (float)logicalTabStripRectangle.Height / 2f, (float)logicalTabStripRectangle.Y + (float)logicalTabStripRectangle.Height / 2f));
				matrix.TransformPoints(array);
				result = checked(new Rectangle((int)unchecked(array[0].X - (float)rect.Height / 2f + 0.5f), (int)unchecked(array[0].Y - (float)rect.Width / 2f + 0.5f), rect.Height, rect.Width));
			}
			return result;
		}
		protected override IDockContent HitTest(Point ptMouse)
		{
			DockState[] dockStates = VS2005AutoHideStrip.DockStates;
			IDockContent result;
			for (int i = 0; i < dockStates.Length; i++)
			{
				DockState dockState = dockStates[i];
				if (this.GetLogicalTabStripRectangle(dockState, true).Contains(ptMouse))
				{
					foreach (AutoHideStripBase.Pane current in (IEnumerable<AutoHideStripBase.Pane>)base.GetPanes(dockState))
					{
						using (IEnumerator<AutoHideStripBase.Tab> enumerator2 = ((IEnumerable<AutoHideStripBase.Tab>)current.AutoHideTabs).GetEnumerator())
						{
							while (enumerator2.MoveNext())
							{
								VS2005AutoHideStrip.TabVS2005 tabVS = (VS2005AutoHideStrip.TabVS2005)enumerator2.Current;
								GraphicsPath tabOutline = this.GetTabOutline(tabVS, true, true);
								if (tabOutline.IsVisible(ptMouse))
								{
									result = tabVS.Content;
									return result;
								}
							}
						}
					}
				}
			}
			result = null;
			return result;
		}
		protected internal override int MeasureHeight()
		{
			return checked(Math.Max(VS2005AutoHideStrip.ImageGapBottom + VS2005AutoHideStrip.ImageGapTop + VS2005AutoHideStrip.ImageHeight, this.TextFont.Height) + VS2005AutoHideStrip.TabGapTop);
		}
		protected override void OnRefreshChanges()
		{
			this.CalculateTabs();
			base.Invalidate();
		}
		protected override AutoHideStripBase.Tab CreateTab(IDockContent content)
		{
			return new VS2005AutoHideStrip.TabVS2005(content);
		}
	}
}
