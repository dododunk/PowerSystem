using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;
namespace WinFormsUI.Docking
{
	internal class VS2005DockPaneStrip : DockPaneStripBase
	{
		private class TabVS2005 : DockPaneStripBase.Tab
		{
			private int m_tabX;
			private int m_tabWidth;
			private int m_maxWidth;
			private bool m_flag;
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
			public int MaxWidth
			{
				get
				{
					return this.m_maxWidth;
				}
				set
				{
					this.m_maxWidth = value;
				}
			}
			protected internal bool Flag
			{
				get
				{
					return this.m_flag;
				}
				set
				{
					this.m_flag = value;
				}
			}
			public TabVS2005(IDockContent content) : base(content)
			{
			}
		}
		private sealed class InertButton : InertButtonBase
		{
			private Bitmap m_image0;
			private Bitmap m_image1;
			private int m_imageCategory = 0;
			public int ImageCategory
			{
				get
				{
					return this.m_imageCategory;
				}
				set
				{
					if (this.m_imageCategory != value)
					{
						this.m_imageCategory = value;
						base.Invalidate();
					}
				}
			}
			public override Bitmap Image
			{
				get
				{
					return (this.ImageCategory == 0) ? this.m_image0 : this.m_image1;
				}
			}
			public InertButton(Bitmap image0, Bitmap image1)
			{
				this.m_image0 = image0;
				this.m_image1 = image1;
			}
		}
		private const int _ToolWindowStripGapTop = 0;
		private const int _ToolWindowStripGapBottom = 1;
		private const int _ToolWindowStripGapLeft = 0;
		private const int _ToolWindowStripGapRight = 0;
		private const int _ToolWindowImageHeight = 16;
		private const int _ToolWindowImageWidth = 16;
		private const int _ToolWindowImageGapTop = 3;
		private const int _ToolWindowImageGapBottom = 1;
		private const int _ToolWindowImageGapLeft = 2;
		private const int _ToolWindowImageGapRight = 0;
		private const int _ToolWindowTextGapRight = 3;
		private const int _ToolWindowTabSeperatorGapTop = 3;
		private const int _ToolWindowTabSeperatorGapBottom = 3;
		private const int _DocumentStripGapTop = 0;
		private const int _DocumentStripGapBottom = 1;
		private const int _DocumentTabMaxWidth = 200;
		private const int _DocumentButtonGapTop = 4;
		private const int _DocumentButtonGapBottom = 4;
		private const int _DocumentButtonGapBetween = 0;
		private const int _DocumentButtonGapRight = 3;
		private const int _DocumentTabGapTop = 3;
		private const int _DocumentTabGapLeft = 3;
		private const int _DocumentTabGapRight = 3;
		private const int _DocumentIconGapBottom = 2;
		private const int _DocumentIconGapLeft = 8;
		private const int _DocumentIconGapRight = 0;
		private const int _DocumentIconHeight = 16;
		private const int _DocumentIconWidth = 16;
		private const int _DocumentTextGapRight = 3;
		private ContextMenuStrip m_selectMenu;
		private static Bitmap m_imageButtonClose;
		private VS2005DockPaneStrip.InertButton m_buttonClose;
		private static Bitmap m_imageButtonWindowList;
		private static Bitmap m_imageButtonWindowListOverflow;
		private VS2005DockPaneStrip.InertButton m_buttonWindowList;
		private IContainer m_components;
		private ToolTip m_toolTip;
		private Font m_font;
		private Font m_boldFont;
		private int m_startDisplayingTab = 0;
		private int m_endDisplayingTab = 0;
		private int m_firstDisplayingTab = 0;
		private bool m_documentTabsOverflow = false;
		private static string m_toolTipSelect;
		private static string m_toolTipClose;
		private bool m_closeButtonVisible = false;
		private Rectangle TabStripRectangle
		{
			get
			{
				Rectangle result;
				if (base.Appearance == DockPane.AppearanceStyle.Document)
				{
					result = this.TabStripRectangle_Document;
				}
				else
				{
					result = this.TabStripRectangle_ToolWindow;
				}
				return result;
			}
		}
		private Rectangle TabStripRectangle_ToolWindow
		{
			get
			{
				Rectangle clientRectangle = base.ClientRectangle;
				return checked(new Rectangle(clientRectangle.X, clientRectangle.Top + VS2005DockPaneStrip.ToolWindowStripGapTop, clientRectangle.Width, clientRectangle.Height - VS2005DockPaneStrip.ToolWindowStripGapTop - VS2005DockPaneStrip.ToolWindowStripGapBottom));
			}
		}
		private Rectangle TabStripRectangle_Document
		{
			get
			{
				Rectangle clientRectangle = base.ClientRectangle;
				return checked(new Rectangle(clientRectangle.X, clientRectangle.Top + VS2005DockPaneStrip.DocumentStripGapTop, clientRectangle.Width, clientRectangle.Height - VS2005DockPaneStrip.DocumentStripGapTop - VS2005DockPaneStrip.ToolWindowStripGapBottom));
			}
		}
		private Rectangle TabsRectangle
		{
			get
			{
				checked
				{
					Rectangle result;
					if (base.Appearance == DockPane.AppearanceStyle.ToolWindow)
					{
						result = this.TabStripRectangle;
					}
					else
					{
						Rectangle tabStripRectangle = this.TabStripRectangle;
						int num = tabStripRectangle.X;
						int y = tabStripRectangle.Y;
						int num2 = tabStripRectangle.Width;
						int height = tabStripRectangle.Height;
						num += VS2005DockPaneStrip.DocumentTabGapLeft;
						num2 -= VS2005DockPaneStrip.DocumentTabGapLeft + VS2005DockPaneStrip.DocumentTabGapRight + VS2005DockPaneStrip.DocumentButtonGapRight + this.ButtonClose.Width + this.ButtonWindowList.Width + 2 * VS2005DockPaneStrip.DocumentButtonGapBetween;
						result = new Rectangle(num, y, num2, height);
					}
					return result;
				}
			}
		}
		private ContextMenuStrip SelectMenu
		{
			get
			{
				return this.m_selectMenu;
			}
		}
		private static Bitmap ImageButtonClose
		{
			get
			{
				if (VS2005DockPaneStrip.m_imageButtonClose == null)
				{
					if (DockingHelper.UseLightDockStripImages)
					{
						VS2005DockPaneStrip.m_imageButtonClose = Resources.DockPane_Close_Light;
					}
					else
					{
						VS2005DockPaneStrip.m_imageButtonClose = Resources.DockPane_Close;
					}
				}
				return VS2005DockPaneStrip.m_imageButtonClose;
			}
		}
		private VS2005DockPaneStrip.InertButton ButtonClose
		{
			get
			{
				if (this.m_buttonClose == null)
				{
					this.m_buttonClose = new VS2005DockPaneStrip.InertButton(VS2005DockPaneStrip.ImageButtonClose, VS2005DockPaneStrip.ImageButtonClose);
					this.m_toolTip.SetToolTip(this.m_buttonClose, VS2005DockPaneStrip.ToolTipClose);
					this.m_buttonClose.Click += new EventHandler(this.Close_Click);
					base.Controls.Add(this.m_buttonClose);
				}
				return this.m_buttonClose;
			}
		}
		private static Bitmap ImageButtonWindowList
		{
			get
			{
				if (VS2005DockPaneStrip.m_imageButtonWindowList == null)
				{
					if (DockingHelper.UseLightDockStripImages)
					{
						VS2005DockPaneStrip.m_imageButtonWindowList = Resources.DockPane_Option_Light;
					}
					else
					{
						VS2005DockPaneStrip.m_imageButtonWindowList = Resources.DockPane_Option;
					}
				}
				return VS2005DockPaneStrip.m_imageButtonWindowList;
			}
		}
		private static Bitmap ImageButtonWindowListOverflow
		{
			get
			{
				if (VS2005DockPaneStrip.m_imageButtonWindowListOverflow == null)
				{
					if (DockingHelper.UseLightDockStripImages)
					{
						VS2005DockPaneStrip.m_imageButtonWindowListOverflow = Resources.DockPane_OptionOverflow_Light;
					}
					else
					{
						VS2005DockPaneStrip.m_imageButtonWindowListOverflow = Resources.DockPane_OptionOverflow;
					}
				}
				return VS2005DockPaneStrip.m_imageButtonWindowListOverflow;
			}
		}
		private VS2005DockPaneStrip.InertButton ButtonWindowList
		{
			get
			{
				if (this.m_buttonWindowList == null)
				{
					this.m_buttonWindowList = new VS2005DockPaneStrip.InertButton(VS2005DockPaneStrip.ImageButtonWindowList, VS2005DockPaneStrip.ImageButtonWindowListOverflow);
					this.m_toolTip.SetToolTip(this.m_buttonWindowList, VS2005DockPaneStrip.ToolTipSelect);
					this.m_buttonWindowList.Click += new EventHandler(this.WindowList_Click);
					base.Controls.Add(this.m_buttonWindowList);
				}
				return this.m_buttonWindowList;
			}
		}
		private static GraphicsPath GraphicsPath
		{
			get
			{
				return VS2005AutoHideStrip.GraphicsPath;
			}
		}
		private IContainer Components
		{
			get
			{
				return this.m_components;
			}
		}
		public Font TextFont
		{
			get
			{
				return base.DockPane.DockPanel.Skin.DockPaneStripSkin.TextFont;
			}
		}
		private Font BoldFont
		{
			get
			{
				Font result;
				if (base.IsDisposed)
				{
					result = null;
				}
				else
				{
					if (this.m_boldFont == null)
					{
						this.m_font = this.TextFont;
						this.m_boldFont = new Font(this.TextFont, FontStyle.Bold);
					}
					else
					{
						if (this.m_font != this.TextFont)
						{
							this.m_boldFont.Dispose();
							this.m_font = this.TextFont;
							this.m_boldFont = new Font(this.TextFont, FontStyle.Bold);
						}
					}
					result = this.m_boldFont;
				}
				return result;
			}
		}
		private int StartDisplayingTab
		{
			get
			{
				return this.m_startDisplayingTab;
			}
			set
			{
				this.m_startDisplayingTab = value;
				base.Invalidate();
			}
		}
		private int EndDisplayingTab
		{
			get
			{
				return this.m_endDisplayingTab;
			}
			set
			{
				this.m_endDisplayingTab = value;
			}
		}
		private int FirstDisplayingTab
		{
			get
			{
				return this.m_firstDisplayingTab;
			}
			set
			{
				this.m_firstDisplayingTab = value;
			}
		}
		private bool DocumentTabsOverflow
		{
			set
			{
				if (this.m_documentTabsOverflow != value)
				{
					this.m_documentTabsOverflow = value;
					if (value)
					{
						this.ButtonWindowList.ImageCategory = 1;
					}
					else
					{
						this.ButtonWindowList.ImageCategory = 0;
					}
				}
			}
		}
		private static int ToolWindowStripGapTop
		{
			get
			{
				return 0;
			}
		}
		private static int ToolWindowStripGapBottom
		{
			get
			{
				return 1;
			}
		}
		private static int ToolWindowStripGapLeft
		{
			get
			{
				return 0;
			}
		}
		private static int ToolWindowStripGapRight
		{
			get
			{
				return 0;
			}
		}
		private static int ToolWindowImageHeight
		{
			get
			{
				return 16;
			}
		}
		private static int ToolWindowImageWidth
		{
			get
			{
				return 16;
			}
		}
		private static int ToolWindowImageGapTop
		{
			get
			{
				return 3;
			}
		}
		private static int ToolWindowImageGapBottom
		{
			get
			{
				return 1;
			}
		}
		private static int ToolWindowImageGapLeft
		{
			get
			{
				return 2;
			}
		}
		private static int ToolWindowImageGapRight
		{
			get
			{
				return 0;
			}
		}
		private static int ToolWindowTextGapRight
		{
			get
			{
				return 3;
			}
		}
		private static int ToolWindowTabSeperatorGapTop
		{
			get
			{
				return 3;
			}
		}
		private static int ToolWindowTabSeperatorGapBottom
		{
			get
			{
				return 3;
			}
		}
		private static string ToolTipClose
		{
			get
			{
				if (VS2005DockPaneStrip.m_toolTipClose == null)
				{
					VS2005DockPaneStrip.m_toolTipClose = Strings.DockPaneStrip_ToolTipClose;
				}
				return VS2005DockPaneStrip.m_toolTipClose;
			}
		}
		private static string ToolTipSelect
		{
			get
			{
				if (VS2005DockPaneStrip.m_toolTipSelect == null)
				{
					VS2005DockPaneStrip.m_toolTipSelect = Strings.DockPaneStrip_ToolTipWindowList;
				}
				return VS2005DockPaneStrip.m_toolTipSelect;
			}
		}
		private TextFormatFlags ToolWindowTextFormat
		{
			get
			{
				TextFormatFlags textFormatFlags = TextFormatFlags.EndEllipsis | TextFormatFlags.HorizontalCenter | TextFormatFlags.SingleLine | TextFormatFlags.VerticalCenter;
				TextFormatFlags result;
				if (this.RightToLeft == RightToLeft.Yes)
				{
					result = (textFormatFlags | TextFormatFlags.RightToLeft | TextFormatFlags.Right);
				}
				else
				{
					result = textFormatFlags;
				}
				return result;
			}
		}
		private static int DocumentStripGapTop
		{
			get
			{
				return 0;
			}
		}
		private static int DocumentStripGapBottom
		{
			get
			{
				return 1;
			}
		}
		private TextFormatFlags DocumentTextFormat
		{
			get
			{
				TextFormatFlags textFormatFlags = TextFormatFlags.EndEllipsis | TextFormatFlags.HorizontalCenter | TextFormatFlags.SingleLine | TextFormatFlags.VerticalCenter;
				TextFormatFlags result;
				if (this.RightToLeft == RightToLeft.Yes)
				{
					result = (textFormatFlags | TextFormatFlags.RightToLeft);
				}
				else
				{
					result = textFormatFlags;
				}
				return result;
			}
		}
		private static int DocumentTabMaxWidth
		{
			get
			{
				return 200;
			}
		}
		private static int DocumentButtonGapTop
		{
			get
			{
				return 4;
			}
		}
		private static int DocumentButtonGapBottom
		{
			get
			{
				return 4;
			}
		}
		private static int DocumentButtonGapBetween
		{
			get
			{
				return 0;
			}
		}
		private static int DocumentButtonGapRight
		{
			get
			{
				return 3;
			}
		}
		private static int DocumentTabGapTop
		{
			get
			{
				return 3;
			}
		}
		private static int DocumentTabGapLeft
		{
			get
			{
				return 3;
			}
		}
		private static int DocumentTabGapRight
		{
			get
			{
				return 3;
			}
		}
		private static int DocumentIconGapBottom
		{
			get
			{
				return 2;
			}
		}
		private static int DocumentIconGapLeft
		{
			get
			{
				return 8;
			}
		}
		private static int DocumentIconGapRight
		{
			get
			{
				return 0;
			}
		}
		private static int DocumentIconWidth
		{
			get
			{
				return 16;
			}
		}
		private static int DocumentIconHeight
		{
			get
			{
				return 16;
			}
		}
		private static int DocumentTextGapRight
		{
			get
			{
				return 3;
			}
		}
		private static Pen PenToolWindowTabBorder
		{
			get
			{
				Pen result;
				if (DockingHelper.ThemeToolWindowTabBorder != Color.Empty)
				{
					result = new Pen(DockingHelper.ThemeToolWindowTabBorder);
				}
				else
				{
					result = SystemPens.GrayText;
				}
				return result;
			}
		}
		private static Pen PenDocumentTabActiveBorder
		{
			get
			{
				Pen result;
				if (DockingHelper.ThemeDocumentTabActiveBorder != Color.Empty)
				{
					result = new Pen(DockingHelper.ThemeDocumentTabActiveBorder);
				}
				else
				{
					result = SystemPens.ControlDarkDark;
				}
				return result;
			}
		}
		private static Pen PenDocumentTabInactiveBorder
		{
			get
			{
				Pen result;
				if (DockingHelper.ThemeDocumentTabInactiveBorder != Color.Empty)
				{
					result = new Pen(DockingHelper.ThemeDocumentTabInactiveBorder);
				}
				else
				{
					result = SystemPens.GrayText;
				}
				return result;
			}
		}
		protected internal override DockPaneStripBase.Tab CreateTab(IDockContent content)
		{
			return new VS2005DockPaneStrip.TabVS2005(content);
		}
		public VS2005DockPaneStrip(DockPane pane) : base(pane)
		{
			base.SetStyle(ControlStyles.UserPaint | ControlStyles.ResizeRedraw | ControlStyles.AllPaintingInWmPaint | ControlStyles.OptimizedDoubleBuffer, true);
			base.SuspendLayout();
			this.m_components = new Container();
			this.m_toolTip = new ToolTip(this.Components);
			this.m_selectMenu = new ContextMenuStrip(this.Components);
			base.ResumeLayout();
		}
		protected override void Dispose(bool disposing)
		{
			if (disposing)
			{
				this.Components.Dispose();
				if (this.m_boldFont != null)
				{
					this.m_boldFont.Dispose();
					this.m_boldFont = null;
				}
			}
			base.Dispose(disposing);
		}
		protected internal override int MeasureHeight()
		{
			int result;
			if (base.Appearance == DockPane.AppearanceStyle.ToolWindow)
			{
				result = this.MeasureHeight_ToolWindow();
			}
			else
			{
				result = this.MeasureHeight_Document();
			}
			return result;
		}
		private int MeasureHeight_ToolWindow()
		{
			int result;
			if (base.DockPane.IsAutoHide || base.Tabs.Count <= 1)
			{
				result = 0;
			}
			else
			{
				int num = checked(Math.Max(this.TextFont.Height, VS2005DockPaneStrip.ToolWindowImageHeight + VS2005DockPaneStrip.ToolWindowImageGapTop + VS2005DockPaneStrip.ToolWindowImageGapBottom) + VS2005DockPaneStrip.ToolWindowStripGapTop + VS2005DockPaneStrip.ToolWindowStripGapBottom);
				result = num;
			}
			return result;
		}
		private int MeasureHeight_Document()
		{
			return checked(Math.Max(this.TextFont.Height + VS2005DockPaneStrip.DocumentTabGapTop, this.ButtonClose.Height + VS2005DockPaneStrip.DocumentButtonGapTop + VS2005DockPaneStrip.DocumentButtonGapBottom) + VS2005DockPaneStrip.DocumentStripGapBottom + VS2005DockPaneStrip.DocumentStripGapTop);
		}
		protected override void OnPaint(PaintEventArgs e)
		{
			Rectangle tabsRectangle = this.TabsRectangle;
			checked
			{
				if (base.Appearance == DockPane.AppearanceStyle.Document)
				{
					tabsRectangle.X -= VS2005DockPaneStrip.DocumentTabGapLeft;
					tabsRectangle.Width += VS2005DockPaneStrip.DocumentTabGapLeft + VS2005DockPaneStrip.DocumentTabGapRight + VS2005DockPaneStrip.DocumentButtonGapRight + this.ButtonClose.Width + this.ButtonWindowList.Width;
					if (tabsRectangle.Width > 0 && tabsRectangle.Height > 0)
					{
						Color startColor = base.DockPane.DockPanel.Skin.DockPaneStripSkin.DocumentGradient.DockStripGradient.StartColor;
						Color endColor = base.DockPane.DockPanel.Skin.DockPaneStripSkin.DocumentGradient.DockStripGradient.EndColor;
						LinearGradientMode linearGradientMode = base.DockPane.DockPanel.Skin.DockPaneStripSkin.DocumentGradient.DockStripGradient.LinearGradientMode;
						using (LinearGradientBrush linearGradientBrush = new LinearGradientBrush(tabsRectangle, startColor, endColor, linearGradientMode))
						{
							e.Graphics.FillRectangle(linearGradientBrush, tabsRectangle);
						}
					}
				}
				else
				{
					Color startColor = base.DockPane.DockPanel.Skin.DockPaneStripSkin.ToolWindowGradient.DockStripGradient.StartColor;
					Color endColor = base.DockPane.DockPanel.Skin.DockPaneStripSkin.ToolWindowGradient.DockStripGradient.EndColor;
					LinearGradientMode linearGradientMode = base.DockPane.DockPanel.Skin.DockPaneStripSkin.ToolWindowGradient.DockStripGradient.LinearGradientMode;
					using (LinearGradientBrush linearGradientBrush = new LinearGradientBrush(tabsRectangle, startColor, endColor, linearGradientMode))
					{
						e.Graphics.FillRectangle(linearGradientBrush, tabsRectangle);
					}
				}
				base.OnPaint(e);
				this.CalculateTabs();
				if (base.Appearance == DockPane.AppearanceStyle.Document && base.DockPane.ActiveContent != null)
				{
					if (this.EnsureDocumentTabVisible(base.DockPane.ActiveContent, false))
					{
						this.CalculateTabs();
					}
				}
				this.DrawTabStrip(e.Graphics);
			}
		}
		protected override void OnRefreshChanges()
		{
			this.SetInertButtons();
			base.Invalidate();
		}
		protected internal override GraphicsPath GetOutline(int index)
		{
			GraphicsPath result;
			if (base.Appearance == DockPane.AppearanceStyle.Document)
			{
				result = this.GetOutline_Document(index);
			}
			else
			{
				result = this.GetOutline_ToolWindow(index);
			}
			return result;
		}
		private GraphicsPath GetOutline_Document(int index)
		{
			Rectangle rectangle = this.GetTabRectangle(index);
			checked
			{
				rectangle.X -= rectangle.Height / 2;
				rectangle.Intersect(this.TabsRectangle);
				rectangle = base.RectangleToScreen(DrawHelper.RtlTransform(this, rectangle));
				Rectangle rectangle2 = base.DockPane.RectangleToScreen(base.DockPane.ClientRectangle);
				GraphicsPath graphicsPath = new GraphicsPath();
				GraphicsPath tabOutline_Document = this.GetTabOutline_Document(base.Tabs[index], true, true, true);
				graphicsPath.AddPath(tabOutline_Document, true);
				if (base.DockPane.DockPanel.DocumentTabStripLocation == DocumentTabStripLocation.Bottom)
				{
					graphicsPath.AddLine(rectangle.Right, rectangle.Top, rectangle2.Right, rectangle.Top);
					graphicsPath.AddLine(rectangle2.Right, rectangle.Top, rectangle2.Right, rectangle2.Top);
					graphicsPath.AddLine(rectangle2.Right, rectangle2.Top, rectangle2.Left, rectangle2.Top);
					graphicsPath.AddLine(rectangle2.Left, rectangle2.Top, rectangle2.Left, rectangle.Top);
					graphicsPath.AddLine(rectangle2.Left, rectangle.Top, rectangle.Right, rectangle.Top);
				}
				else
				{
					graphicsPath.AddLine(rectangle.Right, rectangle.Bottom, rectangle2.Right, rectangle.Bottom);
					graphicsPath.AddLine(rectangle2.Right, rectangle.Bottom, rectangle2.Right, rectangle2.Bottom);
					graphicsPath.AddLine(rectangle2.Right, rectangle2.Bottom, rectangle2.Left, rectangle2.Bottom);
					graphicsPath.AddLine(rectangle2.Left, rectangle2.Bottom, rectangle2.Left, rectangle.Bottom);
					graphicsPath.AddLine(rectangle2.Left, rectangle.Bottom, rectangle.Right, rectangle.Bottom);
				}
				return graphicsPath;
			}
		}
		private GraphicsPath GetOutline_ToolWindow(int index)
		{
			Rectangle rectangle = this.GetTabRectangle(index);
			rectangle.Intersect(this.TabsRectangle);
			rectangle = base.RectangleToScreen(DrawHelper.RtlTransform(this, rectangle));
			Rectangle rectangle2 = base.DockPane.RectangleToScreen(base.DockPane.ClientRectangle);
			GraphicsPath graphicsPath = new GraphicsPath();
			GraphicsPath tabOutline = this.GetTabOutline(base.Tabs[index], true, true);
			graphicsPath.AddPath(tabOutline, true);
			graphicsPath.AddLine(rectangle.Left, rectangle.Top, rectangle2.Left, rectangle.Top);
			graphicsPath.AddLine(rectangle2.Left, rectangle.Top, rectangle2.Left, rectangle2.Top);
			graphicsPath.AddLine(rectangle2.Left, rectangle2.Top, rectangle2.Right, rectangle2.Top);
			graphicsPath.AddLine(rectangle2.Right, rectangle2.Top, rectangle2.Right, rectangle.Top);
			graphicsPath.AddLine(rectangle2.Right, rectangle.Top, rectangle.Right, rectangle.Top);
			return graphicsPath;
		}
		private void CalculateTabs()
		{
			if (base.Appearance == DockPane.AppearanceStyle.ToolWindow)
			{
				this.CalculateTabs_ToolWindow();
			}
			else
			{
				this.CalculateTabs_Document();
			}
		}
		private void CalculateTabs_ToolWindow()
		{
			checked
			{
				if (base.Tabs.Count > 1 && !base.DockPane.IsAutoHide)
				{
					Rectangle tabStripRectangle = this.TabStripRectangle;
					int count = base.Tabs.Count;
					using (IEnumerator<DockPaneStripBase.Tab> enumerator = ((IEnumerable<DockPaneStripBase.Tab>)base.Tabs).GetEnumerator())
					{
						while (enumerator.MoveNext())
						{
							VS2005DockPaneStrip.TabVS2005 tabVS = (VS2005DockPaneStrip.TabVS2005)enumerator.Current;
							tabVS.MaxWidth = this.GetMaxTabWidth(base.Tabs.IndexOf(tabVS));
							tabVS.Flag = false;
						}
					}
					bool flag = true;
					int num = tabStripRectangle.Width - VS2005DockPaneStrip.ToolWindowStripGapLeft - VS2005DockPaneStrip.ToolWindowStripGapRight;
					int num2 = 0;
					int num3 = num / count;
					int num4 = count;
					flag = true;
					while (flag && num4 > 0)
					{
						flag = false;
						using (IEnumerator<DockPaneStripBase.Tab> enumerator = ((IEnumerable<DockPaneStripBase.Tab>)base.Tabs).GetEnumerator())
						{
							while (enumerator.MoveNext())
							{
								VS2005DockPaneStrip.TabVS2005 tabVS = (VS2005DockPaneStrip.TabVS2005)enumerator.Current;
								if (!tabVS.Flag)
								{
									if (tabVS.MaxWidth <= num3)
									{
										tabVS.Flag = true;
										tabVS.TabWidth = tabVS.MaxWidth;
										num2 += tabVS.TabWidth;
										flag = true;
										num4--;
									}
								}
							}
						}
						if (num4 != 0)
						{
							num3 = (num - num2) / num4;
						}
					}
					if (num4 > 0)
					{
						int num5 = num - num2 - num3 * num4;
						using (IEnumerator<DockPaneStripBase.Tab> enumerator = ((IEnumerable<DockPaneStripBase.Tab>)base.Tabs).GetEnumerator())
						{
							while (enumerator.MoveNext())
							{
								VS2005DockPaneStrip.TabVS2005 tabVS = (VS2005DockPaneStrip.TabVS2005)enumerator.Current;
								if (!tabVS.Flag)
								{
									tabVS.Flag = true;
									if (num5 > 0)
									{
										tabVS.TabWidth = num3 + 1;
										num5--;
									}
									else
									{
										tabVS.TabWidth = num3;
									}
								}
							}
						}
					}
					int num6 = tabStripRectangle.X + VS2005DockPaneStrip.ToolWindowStripGapLeft;
					using (IEnumerator<DockPaneStripBase.Tab> enumerator = ((IEnumerable<DockPaneStripBase.Tab>)base.Tabs).GetEnumerator())
					{
						while (enumerator.MoveNext())
						{
							VS2005DockPaneStrip.TabVS2005 tabVS = (VS2005DockPaneStrip.TabVS2005)enumerator.Current;
							tabVS.TabX = num6;
							num6 += tabVS.TabWidth;
						}
					}
				}
			}
		}
		private bool CalculateDocumentTab(Rectangle rectTabStrip, ref int x, int index)
		{
			bool result = false;
			VS2005DockPaneStrip.TabVS2005 tabVS = base.Tabs[index] as VS2005DockPaneStrip.TabVS2005;
			tabVS.MaxWidth = this.GetMaxTabWidth(index);
			int num = Math.Min(tabVS.MaxWidth, VS2005DockPaneStrip.DocumentTabMaxWidth);
			checked
			{
				if (x + num < rectTabStrip.Right || index == this.StartDisplayingTab)
				{
					tabVS.TabX = x;
					tabVS.TabWidth = num;
					this.EndDisplayingTab = index;
				}
				else
				{
					tabVS.TabX = 0;
					tabVS.TabWidth = 0;
					result = true;
				}
				x += num;
				return result;
			}
		}
		private void CalculateTabs_Document()
		{
			if (this.m_startDisplayingTab >= base.Tabs.Count)
			{
				this.m_startDisplayingTab = 0;
			}
			Rectangle tabsRectangle = this.TabsRectangle;
			checked
			{
				int num = tabsRectangle.X + tabsRectangle.Height / 2;
				bool flag = false;
				if (this.m_startDisplayingTab > 0)
				{
					int num2 = num;
					VS2005DockPaneStrip.TabVS2005 tabVS = base.Tabs[this.m_startDisplayingTab] as VS2005DockPaneStrip.TabVS2005;
					tabVS.MaxWidth = this.GetMaxTabWidth(this.m_startDisplayingTab);
					for (int i = this.StartDisplayingTab; i >= 0; i--)
					{
						this.CalculateDocumentTab(tabsRectangle, ref num2, i);
					}
					this.FirstDisplayingTab = this.EndDisplayingTab;
					num2 = num;
					for (int i = this.EndDisplayingTab; i < base.Tabs.Count; i++)
					{
						flag = this.CalculateDocumentTab(tabsRectangle, ref num2, i);
					}
					if (this.FirstDisplayingTab != 0)
					{
						flag = true;
					}
				}
				else
				{
					for (int i = this.StartDisplayingTab; i < base.Tabs.Count; i++)
					{
						flag = this.CalculateDocumentTab(tabsRectangle, ref num, i);
					}
					for (int i = 0; i < this.StartDisplayingTab; i++)
					{
						flag = this.CalculateDocumentTab(tabsRectangle, ref num, i);
					}
					this.FirstDisplayingTab = this.StartDisplayingTab;
				}
				if (!flag)
				{
					this.m_startDisplayingTab = 0;
					this.FirstDisplayingTab = 0;
					num = tabsRectangle.X + tabsRectangle.Height / 2;
					using (IEnumerator<DockPaneStripBase.Tab> enumerator = ((IEnumerable<DockPaneStripBase.Tab>)base.Tabs).GetEnumerator())
					{
						while (enumerator.MoveNext())
						{
							VS2005DockPaneStrip.TabVS2005 tabVS = (VS2005DockPaneStrip.TabVS2005)enumerator.Current;
							tabVS.TabX = num;
							num += tabVS.TabWidth;
						}
					}
				}
				this.DocumentTabsOverflow = flag;
			}
		}
		protected internal override void EnsureTabVisible(IDockContent content)
		{
			if (base.Appearance == DockPane.AppearanceStyle.Document && base.Tabs.Contains(content))
			{
				this.CalculateTabs();
				this.EnsureDocumentTabVisible(content, true);
			}
		}
		private bool EnsureDocumentTabVisible(IDockContent content, bool repaint)
		{
			int num = base.Tabs.IndexOf(content);
			VS2005DockPaneStrip.TabVS2005 tabVS = base.Tabs[num] as VS2005DockPaneStrip.TabVS2005;
			bool result;
			if (tabVS.TabWidth != 0)
			{
				result = false;
			}
			else
			{
				this.StartDisplayingTab = num;
				if (repaint)
				{
					base.Invalidate();
				}
				result = true;
			}
			return result;
		}
		private int GetMaxTabWidth(int index)
		{
			int result;
			if (base.Appearance == DockPane.AppearanceStyle.ToolWindow)
			{
				result = this.GetMaxTabWidth_ToolWindow(index);
			}
			else
			{
				result = this.GetMaxTabWidth_Document(index);
			}
			return result;
		}
		private int GetMaxTabWidth_ToolWindow(int index)
		{
			IDockContent content = base.Tabs[index].Content;
			Size size = TextRenderer.MeasureText(content.DockHandler.TabText, this.TextFont);
			return checked(VS2005DockPaneStrip.ToolWindowImageWidth + size.Width + VS2005DockPaneStrip.ToolWindowImageGapLeft + VS2005DockPaneStrip.ToolWindowImageGapRight + VS2005DockPaneStrip.ToolWindowTextGapRight);
		}
		private int GetMaxTabWidth_Document(int index)
		{
			IDockContent content = base.Tabs[index].Content;
			int height = this.GetTabRectangle_Document(index).Height;
			Size size = TextRenderer.MeasureText(content.DockHandler.TabText, this.BoldFont, new Size(VS2005DockPaneStrip.DocumentTabMaxWidth, height), this.DocumentTextFormat);
			checked
			{
				int result;
				if (base.DockPane.DockPanel.ShowDocumentIcon)
				{
					result = size.Width + VS2005DockPaneStrip.DocumentIconWidth + VS2005DockPaneStrip.DocumentIconGapLeft + VS2005DockPaneStrip.DocumentIconGapRight + VS2005DockPaneStrip.DocumentTextGapRight;
				}
				else
				{
					result = size.Width + VS2005DockPaneStrip.DocumentIconGapLeft + VS2005DockPaneStrip.DocumentTextGapRight;
				}
				return result;
			}
		}
		private void DrawTabStrip(Graphics g)
		{
			if (base.Appearance == DockPane.AppearanceStyle.Document)
			{
				this.DrawTabStrip_Document(g);
			}
			else
			{
				this.DrawTabStrip_ToolWindow(g);
			}
		}
		private void DrawTabStrip_Document(Graphics g)
		{
			int count = base.Tabs.Count;
			checked
			{
				if (count != 0)
				{
					Rectangle tabStripRectangle = this.TabStripRectangle;
					Rectangle tabsRectangle = this.TabsRectangle;
					Rectangle rect = Rectangle.Empty;
					VS2005DockPaneStrip.TabVS2005 tabVS = null;
					g.SetClip(DrawHelper.RtlTransform(this, tabsRectangle));
					for (int i = 0; i < count; i++)
					{
						rect = this.GetTabRectangle(i);
						if (base.Tabs[i].Content == base.DockPane.ActiveContent)
						{
							tabVS = (base.Tabs[i] as VS2005DockPaneStrip.TabVS2005);
						}
						else
						{
							if (rect.IntersectsWith(tabsRectangle))
							{
								this.DrawTab(g, base.Tabs[i] as VS2005DockPaneStrip.TabVS2005, rect);
							}
						}
					}
					g.SetClip(tabStripRectangle);
					if (base.DockPane.DockPanel.DocumentTabStripLocation == DocumentTabStripLocation.Bottom)
					{
						g.DrawLine(VS2005DockPaneStrip.PenDocumentTabActiveBorder, tabStripRectangle.Left, tabStripRectangle.Top + 1, tabStripRectangle.Right, tabStripRectangle.Top + 1);
						g.DrawLine(VS2005DockPaneStrip.PenDocumentTabActiveBorder, tabStripRectangle.Left, tabStripRectangle.Top + 2, tabStripRectangle.Right, tabStripRectangle.Top + 2);
					}
					else
					{
						g.DrawLine(VS2005DockPaneStrip.PenDocumentTabActiveBorder, tabStripRectangle.Left, tabStripRectangle.Bottom - 1, tabStripRectangle.Right, tabStripRectangle.Bottom - 1);
						g.DrawLine(VS2005DockPaneStrip.PenDocumentTabActiveBorder, tabStripRectangle.Left, tabStripRectangle.Bottom - 2, tabStripRectangle.Right, tabStripRectangle.Bottom - 2);
					}
					g.SetClip(DrawHelper.RtlTransform(this, tabsRectangle));
					if (tabVS != null)
					{
						rect = this.GetTabRectangle(base.Tabs.IndexOf(tabVS));
						if (rect.IntersectsWith(tabsRectangle))
						{
							this.DrawTab(g, tabVS, rect);
						}
					}
				}
			}
		}
		private void DrawTabStrip_ToolWindow(Graphics g)
		{
			Rectangle tabStripRectangle = this.TabStripRectangle;
			g.DrawLine(VS2005DockPaneStrip.PenToolWindowTabBorder, tabStripRectangle.Left, tabStripRectangle.Top, tabStripRectangle.Right, tabStripRectangle.Top);
			checked
			{
				for (int i = 0; i < base.Tabs.Count; i++)
				{
					this.DrawTab(g, base.Tabs[i] as VS2005DockPaneStrip.TabVS2005, this.GetTabRectangle(i));
				}
			}
		}
		private Rectangle GetTabRectangle(int index)
		{
			Rectangle result;
			if (base.Appearance == DockPane.AppearanceStyle.ToolWindow)
			{
				result = this.GetTabRectangle_ToolWindow(index);
			}
			else
			{
				result = this.GetTabRectangle_Document(index);
			}
			return result;
		}
		private Rectangle GetTabRectangle_ToolWindow(int index)
		{
			Rectangle tabStripRectangle = this.TabStripRectangle;
			VS2005DockPaneStrip.TabVS2005 tabVS = (VS2005DockPaneStrip.TabVS2005)base.Tabs[index];
			return new Rectangle(tabVS.TabX, tabStripRectangle.Y, tabVS.TabWidth, tabStripRectangle.Height);
		}
		private Rectangle GetTabRectangle_Document(int index)
		{
			Rectangle tabStripRectangle = this.TabStripRectangle;
			VS2005DockPaneStrip.TabVS2005 tabVS = (VS2005DockPaneStrip.TabVS2005)base.Tabs[index];
			Rectangle result = default(Rectangle);
			result.X = tabVS.TabX;
			result.Width = tabVS.TabWidth;
			checked
			{
				result.Height = tabStripRectangle.Height - VS2005DockPaneStrip.DocumentTabGapTop;
				if (base.DockPane.DockPanel.DocumentTabStripLocation == DocumentTabStripLocation.Bottom)
				{
					result.Y = tabStripRectangle.Y + VS2005DockPaneStrip.DocumentStripGapBottom;
				}
				else
				{
					result.Y = tabStripRectangle.Y + VS2005DockPaneStrip.DocumentTabGapTop;
				}
				return result;
			}
		}
		private void DrawTab(Graphics g, VS2005DockPaneStrip.TabVS2005 tab, Rectangle rect)
		{
			if (base.Appearance == DockPane.AppearanceStyle.ToolWindow)
			{
				this.DrawTab_ToolWindow(g, tab, rect);
			}
			else
			{
				this.DrawTab_Document(g, tab, rect);
			}
		}
		private GraphicsPath GetTabOutline(DockPaneStripBase.Tab tab, bool rtlTransform, bool toScreen)
		{
			GraphicsPath result;
			if (base.Appearance == DockPane.AppearanceStyle.ToolWindow)
			{
				result = this.GetTabOutline_ToolWindow(tab, rtlTransform, toScreen);
			}
			else
			{
				result = this.GetTabOutline_Document(tab, rtlTransform, toScreen, false);
			}
			return result;
		}
		private GraphicsPath GetTabOutline_ToolWindow(DockPaneStripBase.Tab tab, bool rtlTransform, bool toScreen)
		{
			Rectangle rectangle = this.GetTabRectangle(base.Tabs.IndexOf(tab));
			if (rtlTransform)
			{
				rectangle = DrawHelper.RtlTransform(this, rectangle);
			}
			if (toScreen)
			{
				rectangle = base.RectangleToScreen(rectangle);
			}
			DrawHelper.GetRoundedCornerTab(VS2005DockPaneStrip.GraphicsPath, rectangle, false);
			return VS2005DockPaneStrip.GraphicsPath;
		}
		private GraphicsPath GetTabOutline_Document(DockPaneStripBase.Tab tab, bool rtlTransform, bool toScreen, bool full)
		{
			int num = 6;
			VS2005DockPaneStrip.GraphicsPath.Reset();
			Rectangle rectangle = this.GetTabRectangle(base.Tabs.IndexOf(tab));
			if (rtlTransform)
			{
				rectangle = DrawHelper.RtlTransform(this, rectangle);
			}
			if (toScreen)
			{
				rectangle = base.RectangleToScreen(rectangle);
			}
			checked
			{
				if (tab.Content == base.DockPane.ActiveContent || full || base.Tabs.IndexOf(tab) == this.FirstDisplayingTab)
				{
					if (this.RightToLeft == RightToLeft.Yes)
					{
						if (base.DockPane.DockPanel.DocumentTabStripLocation == DocumentTabStripLocation.Bottom)
						{
							VS2005DockPaneStrip.GraphicsPath.AddLine(rectangle.Right + rectangle.Height / 2, rectangle.Top, rectangle.Right - rectangle.Height / 2 + num / 2, rectangle.Bottom - num / 2);
						}
						else
						{
							VS2005DockPaneStrip.GraphicsPath.AddLine(rectangle.Right, rectangle.Bottom, rectangle.Right + rectangle.Height / 2, rectangle.Bottom);
							VS2005DockPaneStrip.GraphicsPath.AddLine(rectangle.Right + rectangle.Height / 2, rectangle.Bottom, rectangle.Right - rectangle.Height / 2 + num / 2, rectangle.Top + num / 2);
						}
					}
					else
					{
						if (base.DockPane.DockPanel.DocumentTabStripLocation == DocumentTabStripLocation.Bottom)
						{
							VS2005DockPaneStrip.GraphicsPath.AddLine(rectangle.Left - rectangle.Height / 2, rectangle.Top, rectangle.Left + rectangle.Height / 2 - num / 2, rectangle.Bottom - num / 2);
						}
						else
						{
							VS2005DockPaneStrip.GraphicsPath.AddLine(rectangle.Left, rectangle.Bottom, rectangle.Left - rectangle.Height / 2, rectangle.Bottom);
							VS2005DockPaneStrip.GraphicsPath.AddLine(rectangle.Left - rectangle.Height / 2, rectangle.Bottom, rectangle.Left + rectangle.Height / 2 - num / 2, rectangle.Top + num / 2);
						}
					}
				}
				else
				{
					if (this.RightToLeft == RightToLeft.Yes)
					{
						if (base.DockPane.DockPanel.DocumentTabStripLocation == DocumentTabStripLocation.Bottom)
						{
							VS2005DockPaneStrip.GraphicsPath.AddLine(rectangle.Right, rectangle.Top, rectangle.Right, rectangle.Top + rectangle.Height / 2);
							VS2005DockPaneStrip.GraphicsPath.AddLine(rectangle.Right, rectangle.Top + rectangle.Height / 2, rectangle.Right - rectangle.Height / 2 + num / 2, rectangle.Bottom - num / 2);
						}
						else
						{
							VS2005DockPaneStrip.GraphicsPath.AddLine(rectangle.Right, rectangle.Bottom, rectangle.Right, rectangle.Bottom - rectangle.Height / 2);
							VS2005DockPaneStrip.GraphicsPath.AddLine(rectangle.Right, rectangle.Bottom - rectangle.Height / 2, rectangle.Right - rectangle.Height / 2 + num / 2, rectangle.Top + num / 2);
						}
					}
					else
					{
						if (base.DockPane.DockPanel.DocumentTabStripLocation == DocumentTabStripLocation.Bottom)
						{
							VS2005DockPaneStrip.GraphicsPath.AddLine(rectangle.Left, rectangle.Top, rectangle.Left, rectangle.Top + rectangle.Height / 2);
							VS2005DockPaneStrip.GraphicsPath.AddLine(rectangle.Left, rectangle.Top + rectangle.Height / 2, rectangle.Left + rectangle.Height / 2 - num / 2, rectangle.Bottom - num / 2);
						}
						else
						{
							VS2005DockPaneStrip.GraphicsPath.AddLine(rectangle.Left, rectangle.Bottom, rectangle.Left, rectangle.Bottom - rectangle.Height / 2);
							VS2005DockPaneStrip.GraphicsPath.AddLine(rectangle.Left, rectangle.Bottom - rectangle.Height / 2, rectangle.Left + rectangle.Height / 2 - num / 2, rectangle.Top + num / 2);
						}
					}
				}
				if (this.RightToLeft == RightToLeft.Yes)
				{
					if (base.DockPane.DockPanel.DocumentTabStripLocation == DocumentTabStripLocation.Bottom)
					{
						VS2005DockPaneStrip.GraphicsPath.AddLine(rectangle.Right - rectangle.Height / 2 - num / 2, rectangle.Bottom, rectangle.Left + num / 2, rectangle.Bottom);
					}
					else
					{
						VS2005DockPaneStrip.GraphicsPath.AddLine(rectangle.Right - rectangle.Height / 2 - num / 2, rectangle.Top, rectangle.Left + num / 2, rectangle.Top);
						VS2005DockPaneStrip.GraphicsPath.AddArc(new Rectangle(rectangle.Left, rectangle.Top, num, num), 180f, 90f);
					}
				}
				else
				{
					if (base.DockPane.DockPanel.DocumentTabStripLocation == DocumentTabStripLocation.Bottom)
					{
						VS2005DockPaneStrip.GraphicsPath.AddLine(rectangle.Left + rectangle.Height / 2 + num / 2, rectangle.Bottom, rectangle.Right - num / 2, rectangle.Bottom);
					}
					else
					{
						VS2005DockPaneStrip.GraphicsPath.AddLine(rectangle.Left + rectangle.Height / 2 + num / 2, rectangle.Top, rectangle.Right - num / 2, rectangle.Top);
						VS2005DockPaneStrip.GraphicsPath.AddArc(new Rectangle(rectangle.Right - num, rectangle.Top, num, num), -90f, 90f);
					}
				}
				if (base.Tabs.IndexOf(tab) != this.EndDisplayingTab && base.Tabs.IndexOf(tab) != base.Tabs.Count - 1 && base.Tabs[base.Tabs.IndexOf(tab) + 1].Content == base.DockPane.ActiveContent && !full)
				{
					if (this.RightToLeft == RightToLeft.Yes)
					{
						if (base.DockPane.DockPanel.DocumentTabStripLocation == DocumentTabStripLocation.Bottom)
						{
							VS2005DockPaneStrip.GraphicsPath.AddLine(rectangle.Left, rectangle.Bottom - num / 2, rectangle.Left, rectangle.Bottom - rectangle.Height / 2);
							VS2005DockPaneStrip.GraphicsPath.AddLine(rectangle.Left, rectangle.Bottom - rectangle.Height / 2, rectangle.Left + rectangle.Height / 2, rectangle.Top);
						}
						else
						{
							VS2005DockPaneStrip.GraphicsPath.AddLine(rectangle.Left, rectangle.Top + num / 2, rectangle.Left, rectangle.Top + rectangle.Height / 2);
							VS2005DockPaneStrip.GraphicsPath.AddLine(rectangle.Left, rectangle.Top + rectangle.Height / 2, rectangle.Left + rectangle.Height / 2, rectangle.Bottom);
						}
					}
					else
					{
						if (base.DockPane.DockPanel.DocumentTabStripLocation == DocumentTabStripLocation.Bottom)
						{
							VS2005DockPaneStrip.GraphicsPath.AddLine(rectangle.Right, rectangle.Bottom - num / 2, rectangle.Right, rectangle.Bottom - rectangle.Height / 2);
							VS2005DockPaneStrip.GraphicsPath.AddLine(rectangle.Right, rectangle.Bottom - rectangle.Height / 2, rectangle.Right - rectangle.Height / 2, rectangle.Top);
						}
						else
						{
							VS2005DockPaneStrip.GraphicsPath.AddLine(rectangle.Right, rectangle.Top + num / 2, rectangle.Right, rectangle.Top + rectangle.Height / 2);
							VS2005DockPaneStrip.GraphicsPath.AddLine(rectangle.Right, rectangle.Top + rectangle.Height / 2, rectangle.Right - rectangle.Height / 2, rectangle.Bottom);
						}
					}
				}
				else
				{
					if (this.RightToLeft == RightToLeft.Yes)
					{
						if (base.DockPane.DockPanel.DocumentTabStripLocation == DocumentTabStripLocation.Bottom)
						{
							VS2005DockPaneStrip.GraphicsPath.AddLine(rectangle.Left, rectangle.Bottom - num / 2, rectangle.Left, rectangle.Top);
						}
						else
						{
							VS2005DockPaneStrip.GraphicsPath.AddLine(rectangle.Left, rectangle.Top + num / 2, rectangle.Left, rectangle.Bottom);
						}
					}
					else
					{
						if (base.DockPane.DockPanel.DocumentTabStripLocation == DocumentTabStripLocation.Bottom)
						{
							VS2005DockPaneStrip.GraphicsPath.AddLine(rectangle.Right, rectangle.Bottom - num / 2, rectangle.Right, rectangle.Top);
						}
						else
						{
							VS2005DockPaneStrip.GraphicsPath.AddLine(rectangle.Right, rectangle.Top + num / 2, rectangle.Right, rectangle.Bottom);
						}
					}
				}
				return VS2005DockPaneStrip.GraphicsPath;
			}
		}
		private void DrawTab_ToolWindow(Graphics g, VS2005DockPaneStrip.TabVS2005 tab, Rectangle rect)
		{
			checked
			{
				Rectangle rectangle = new Rectangle(rect.X + VS2005DockPaneStrip.ToolWindowImageGapLeft, rect.Y + rect.Height - 1 - VS2005DockPaneStrip.ToolWindowImageGapBottom - VS2005DockPaneStrip.ToolWindowImageHeight, VS2005DockPaneStrip.ToolWindowImageWidth, VS2005DockPaneStrip.ToolWindowImageHeight);
				Rectangle rectangle2 = rectangle;
				rectangle2.X += rectangle.Width + VS2005DockPaneStrip.ToolWindowImageGapRight;
				rectangle2.Width = rect.Width - rectangle.Width - VS2005DockPaneStrip.ToolWindowImageGapLeft - VS2005DockPaneStrip.ToolWindowImageGapRight - VS2005DockPaneStrip.ToolWindowTextGapRight;
				Rectangle rect2 = DrawHelper.RtlTransform(this, rect);
				rectangle2 = DrawHelper.RtlTransform(this, rectangle2);
				rectangle = DrawHelper.RtlTransform(this, rectangle);
				GraphicsPath tabOutline = this.GetTabOutline(tab, true, false);
				if (base.DockPane.ActiveContent == tab.Content)
				{
					Color startColor = base.DockPane.DockPanel.Skin.DockPaneStripSkin.ToolWindowGradient.ActiveTabGradient.StartColor;
					Color endColor = base.DockPane.DockPanel.Skin.DockPaneStripSkin.ToolWindowGradient.ActiveTabGradient.EndColor;
					LinearGradientMode linearGradientMode = base.DockPane.DockPanel.Skin.DockPaneStripSkin.ToolWindowGradient.ActiveTabGradient.LinearGradientMode;
					g.FillPath(new LinearGradientBrush(rect2, startColor, endColor, linearGradientMode), tabOutline);
					g.DrawPath(VS2005DockPaneStrip.PenToolWindowTabBorder, tabOutline);
					Color textColor = base.DockPane.DockPanel.Skin.DockPaneStripSkin.ToolWindowGradient.ActiveTabGradient.TextColor;
					TextRenderer.DrawText(g, tab.Content.DockHandler.TabText, this.TextFont, rectangle2, textColor, this.ToolWindowTextFormat);
				}
				else
				{
					Color startColor = base.DockPane.DockPanel.Skin.DockPaneStripSkin.ToolWindowGradient.InactiveTabGradient.StartColor;
					Color endColor = base.DockPane.DockPanel.Skin.DockPaneStripSkin.ToolWindowGradient.InactiveTabGradient.EndColor;
					LinearGradientMode linearGradientMode = base.DockPane.DockPanel.Skin.DockPaneStripSkin.ToolWindowGradient.InactiveTabGradient.LinearGradientMode;
					g.FillPath(new LinearGradientBrush(rect2, startColor, endColor, linearGradientMode), tabOutline);
					if (base.Tabs.IndexOf(base.DockPane.ActiveContent) != base.Tabs.IndexOf(tab) + 1)
					{
						Point point = new Point(rect.Right, rect.Top + VS2005DockPaneStrip.ToolWindowTabSeperatorGapTop);
						Point point2 = new Point(rect.Right, rect.Bottom - VS2005DockPaneStrip.ToolWindowTabSeperatorGapBottom);
						g.DrawLine(VS2005DockPaneStrip.PenToolWindowTabBorder, DrawHelper.RtlTransform(this, point), DrawHelper.RtlTransform(this, point2));
					}
					Color textColor = base.DockPane.DockPanel.Skin.DockPaneStripSkin.ToolWindowGradient.InactiveTabGradient.TextColor;
					TextRenderer.DrawText(g, tab.Content.DockHandler.TabText, this.TextFont, rectangle2, textColor, this.ToolWindowTextFormat);
				}
				if (rect2.Contains(rectangle))
				{
					g.DrawIcon(tab.Content.DockHandler.Icon, rectangle);
				}
			}
		}
		private void DrawTab_Document(Graphics g, VS2005DockPaneStrip.TabVS2005 tab, Rectangle rect)
		{
			checked
			{
				if (tab.TabWidth != 0)
				{
					Rectangle rectangle = new Rectangle(rect.X + VS2005DockPaneStrip.DocumentIconGapLeft, rect.Y + rect.Height - 1 - VS2005DockPaneStrip.DocumentIconGapBottom - VS2005DockPaneStrip.DocumentIconHeight, VS2005DockPaneStrip.DocumentIconWidth, VS2005DockPaneStrip.DocumentIconHeight);
					Rectangle rectangle2 = rectangle;
					if (base.DockPane.DockPanel.ShowDocumentIcon)
					{
						rectangle2.X += rectangle.Width + VS2005DockPaneStrip.DocumentIconGapRight;
						rectangle2.Y = rect.Y;
						rectangle2.Width = rect.Width - rectangle.Width - VS2005DockPaneStrip.DocumentIconGapLeft - VS2005DockPaneStrip.DocumentIconGapRight - VS2005DockPaneStrip.DocumentTextGapRight;
						rectangle2.Height = rect.Height;
					}
					else
					{
						rectangle2.Width = rect.Width - VS2005DockPaneStrip.DocumentIconGapLeft - VS2005DockPaneStrip.DocumentTextGapRight;
					}
					Rectangle rectangle3 = DrawHelper.RtlTransform(this, rect);
					Rectangle rect2 = DrawHelper.RtlTransform(this, rect);
					rect2.Width += rect.X;
					rect2.X = 0;
					rectangle2 = DrawHelper.RtlTransform(this, rectangle2);
					rectangle = DrawHelper.RtlTransform(this, rectangle);
					GraphicsPath tabOutline = this.GetTabOutline(tab, true, false);
					if (base.DockPane.ActiveContent == tab.Content)
					{
						Color startColor = base.DockPane.DockPanel.Skin.DockPaneStripSkin.DocumentGradient.ActiveTabGradient.StartColor;
						Color endColor = base.DockPane.DockPanel.Skin.DockPaneStripSkin.DocumentGradient.ActiveTabGradient.EndColor;
						LinearGradientMode linearGradientMode = base.DockPane.DockPanel.Skin.DockPaneStripSkin.DocumentGradient.ActiveTabGradient.LinearGradientMode;
						g.FillPath(new LinearGradientBrush(rect2, startColor, endColor, linearGradientMode), tabOutline);
						g.DrawPath(VS2005DockPaneStrip.PenDocumentTabActiveBorder, tabOutline);
						Color textColor = base.DockPane.DockPanel.Skin.DockPaneStripSkin.DocumentGradient.ActiveTabGradient.TextColor;
						if (base.DockPane.IsActiveDocumentPane)
						{
							TextRenderer.DrawText(g, tab.Content.DockHandler.TabText, this.BoldFont, rectangle2, textColor, this.DocumentTextFormat);
						}
						else
						{
							TextRenderer.DrawText(g, tab.Content.DockHandler.TabText, this.TextFont, rectangle2, textColor, this.DocumentTextFormat);
						}
					}
					else
					{
						Color startColor = base.DockPane.DockPanel.Skin.DockPaneStripSkin.DocumentGradient.InactiveTabGradient.StartColor;
						Color endColor = base.DockPane.DockPanel.Skin.DockPaneStripSkin.DocumentGradient.InactiveTabGradient.EndColor;
						LinearGradientMode linearGradientMode = base.DockPane.DockPanel.Skin.DockPaneStripSkin.DocumentGradient.InactiveTabGradient.LinearGradientMode;
						g.FillPath(new LinearGradientBrush(rect2, startColor, endColor, linearGradientMode), tabOutline);
						g.DrawPath(VS2005DockPaneStrip.PenDocumentTabInactiveBorder, tabOutline);
						Color textColor = base.DockPane.DockPanel.Skin.DockPaneStripSkin.DocumentGradient.InactiveTabGradient.TextColor;
						TextRenderer.DrawText(g, tab.Content.DockHandler.TabText, this.TextFont, rectangle2, textColor, this.DocumentTextFormat);
					}
					if (rectangle3.Contains(rectangle) && base.DockPane.DockPanel.ShowDocumentIcon)
					{
						g.DrawIcon(tab.Content.DockHandler.Icon, rectangle);
					}
				}
			}
		}
		private void WindowList_Click(object sender, EventArgs e)
		{
			int x = 0;
			int y = checked(this.ButtonWindowList.Location.Y + this.ButtonWindowList.Height);
			this.SelectMenu.Items.Clear();
			using (IEnumerator<DockPaneStripBase.Tab> enumerator = ((IEnumerable<DockPaneStripBase.Tab>)base.Tabs).GetEnumerator())
			{
				while (enumerator.MoveNext())
				{
					VS2005DockPaneStrip.TabVS2005 tabVS = (VS2005DockPaneStrip.TabVS2005)enumerator.Current;
					IDockContent content = tabVS.Content;
					ToolStripItem toolStripItem = this.SelectMenu.Items.Add(content.DockHandler.TabText, content.DockHandler.Icon.ToBitmap());
					toolStripItem.Tag = tabVS.Content;
					if (DockingHelper.ThemeMenuForeColor != Color.Empty)
					{
						toolStripItem.ForeColor = DockingHelper.ThemeMenuForeColor;
					}
					toolStripItem.Click += new EventHandler(this.ContextMenuItem_Click);
				}
			}
			this.SelectMenu.Show(this.ButtonWindowList, x, y);
		}
		private void ContextMenuItem_Click(object sender, EventArgs e)
		{
			ToolStripMenuItem toolStripMenuItem = sender as ToolStripMenuItem;
			if (toolStripMenuItem != null)
			{
				IDockContent activeContent = (IDockContent)toolStripMenuItem.Tag;
				base.DockPane.ActiveContent = activeContent;
			}
		}
		private void SetInertButtons()
		{
			checked
			{
				if (base.Appearance == DockPane.AppearanceStyle.ToolWindow)
				{
					if (this.m_buttonClose != null)
					{
						this.m_buttonClose.Left = 0 - this.m_buttonClose.Width;
					}
					if (this.m_buttonWindowList != null)
					{
						this.m_buttonWindowList.Left = 0 - this.m_buttonWindowList.Width;
					}
				}
				else
				{
					this.ButtonClose.Enabled = (base.DockPane.ActiveContent == null || base.DockPane.ActiveContent.DockHandler.CloseButton);
					this.m_closeButtonVisible = (base.DockPane.ActiveContent == null || base.DockPane.ActiveContent.DockHandler.CloseButtonVisible);
					this.ButtonClose.Visible = this.m_closeButtonVisible;
					this.ButtonClose.RefreshChanges();
					this.ButtonWindowList.RefreshChanges();
				}
			}
		}
		protected override void OnLayout(LayoutEventArgs levent)
		{
			if (base.Appearance == DockPane.AppearanceStyle.Document)
			{
				this.LayoutButtons();
				this.OnRefreshChanges();
			}
			base.OnLayout(levent);
		}
		private void LayoutButtons()
		{
			Rectangle tabStripRectangle = this.TabStripRectangle;
			int num = this.ButtonClose.Image.Width;
			int num2 = this.ButtonClose.Image.Height;
			checked
			{
				int num3 = tabStripRectangle.Height - VS2005DockPaneStrip.DocumentButtonGapTop - VS2005DockPaneStrip.DocumentButtonGapBottom;
				if (num2 < num3)
				{
					num *= num3 / num2;
					num2 = num3;
				}
				Size size = new Size(num, num2);
				int x = tabStripRectangle.X + tabStripRectangle.Width - VS2005DockPaneStrip.DocumentTabGapLeft - VS2005DockPaneStrip.DocumentButtonGapRight - num;
				int y = tabStripRectangle.Y + VS2005DockPaneStrip.DocumentButtonGapTop;
				Point location = new Point(x, y);
				this.ButtonClose.Bounds = DrawHelper.RtlTransform(this, new Rectangle(location, size));
				if (this.m_closeButtonVisible)
				{
					location.Offset(0 - (VS2005DockPaneStrip.DocumentButtonGapBetween + num), 0);
				}
				this.ButtonWindowList.Bounds = DrawHelper.RtlTransform(this, new Rectangle(location, size));
			}
		}
		private void Close_Click(object sender, EventArgs e)
		{
			base.DockPane.CloseActiveContent();
		}
		protected internal override int HitTest(Point ptMouse)
		{
			int result;
			if (!this.TabsRectangle.Contains(ptMouse))
			{
				result = -1;
			}
			else
			{
				foreach (DockPaneStripBase.Tab current in (IEnumerable<DockPaneStripBase.Tab>)base.Tabs)
				{
					GraphicsPath tabOutline = this.GetTabOutline(current, true, false);
					if (tabOutline.IsVisible(ptMouse))
					{
						result = base.Tabs.IndexOf(current);
						return result;
					}
				}
				result = -1;
			}
			return result;
		}
		protected override void OnMouseHover(EventArgs e)
		{
			int num = this.HitTest(base.PointToClient(Control.MousePosition));
			string text = string.Empty;
			base.OnMouseHover(e);
			if (num != -1)
			{
				VS2005DockPaneStrip.TabVS2005 tabVS = base.Tabs[num] as VS2005DockPaneStrip.TabVS2005;
				if (!string.IsNullOrEmpty(tabVS.Content.DockHandler.ToolTipText))
				{
					text = tabVS.Content.DockHandler.ToolTipText;
				}
				else
				{
					if (tabVS.MaxWidth > tabVS.TabWidth)
					{
						text = tabVS.Content.DockHandler.TabText;
					}
				}
			}
			if (this.m_toolTip.GetToolTip(this) != text)
			{
				this.m_toolTip.Active = false;
				this.m_toolTip.SetToolTip(this, text);
				this.m_toolTip.Active = true;
			}
			base.ResetMouseEventArgs();
		}
		protected override void OnRightToLeftChanged(EventArgs e)
		{
			base.OnRightToLeftChanged(e);
			base.PerformLayout();
		}
	}
}
