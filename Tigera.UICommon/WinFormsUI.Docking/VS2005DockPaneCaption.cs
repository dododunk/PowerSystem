using System;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;
namespace WinFormsUI.Docking
{
	internal class VS2005DockPaneCaption : DockPaneCaptionBase
	{
		private sealed class InertButton : InertButtonBase
		{
			private Bitmap m_image;
			private Bitmap m_imageAutoHide;
			private VS2005DockPaneCaption m_dockPaneCaption;
			private VS2005DockPaneCaption DockPaneCaption
			{
				get
				{
					return this.m_dockPaneCaption;
				}
			}
			public bool IsAutoHide
			{
				get
				{
					return this.DockPaneCaption.DockPane.IsAutoHide;
				}
			}
			public override Bitmap Image
			{
				get
				{
					return this.IsAutoHide ? this.m_imageAutoHide : this.m_image;
				}
			}
			public InertButton(VS2005DockPaneCaption dockPaneCaption, Bitmap image, Bitmap imageAutoHide)
			{
				this.m_dockPaneCaption = dockPaneCaption;
				this.m_image = image;
				this.m_imageAutoHide = imageAutoHide;
				base.RefreshChanges();
			}
			protected override void OnRefreshChanges()
			{
				if (this.DockPaneCaption.DockPane.DockPanel != null)
				{
					if (this.DockPaneCaption.TextColor != this.ForeColor)
					{
						this.ForeColor = this.DockPaneCaption.TextColor;
						base.Invalidate();
					}
				}
			}
		}
		private const int _TextGapTop = 2;
		private const int _TextGapBottom = 0;
		private const int _TextGapLeft = 3;
		private const int _TextGapRight = 3;
		private const int _ButtonGapTop = 2;
		private const int _ButtonGapBottom = 1;
		private const int _ButtonGapBetween = 1;
		private const int _ButtonGapLeft = 1;
		private const int _ButtonGapRight = 2;
		private static Bitmap _imageButtonClose;
		private VS2005DockPaneCaption.InertButton m_buttonClose;
		private static Bitmap _imageButtonAutoHide;
		private static Bitmap _imageButtonDock;
		private VS2005DockPaneCaption.InertButton m_buttonAutoHide;
		private static Bitmap _imageButtonOptions;
		private VS2005DockPaneCaption.InertButton m_buttonOptions;
		private IContainer m_components;
		private ToolTip m_toolTip;
		private static string _toolTipClose;
		private static string _toolTipOptions;
		private static string _toolTipAutoHide;
		private static Blend _activeBackColorGradientBlend;
		private static TextFormatFlags _textFormat = TextFormatFlags.EndEllipsis | TextFormatFlags.SingleLine | TextFormatFlags.VerticalCenter;
		private static Bitmap ImageButtonClose
		{
			get
			{
				if (VS2005DockPaneCaption._imageButtonClose == null)
				{
					VS2005DockPaneCaption._imageButtonClose = Resources.DockPane_Close;
				}
				return VS2005DockPaneCaption._imageButtonClose;
			}
		}
		private VS2005DockPaneCaption.InertButton ButtonClose
		{
			get
			{
				if (this.m_buttonClose == null)
				{
					this.m_buttonClose = new VS2005DockPaneCaption.InertButton(this, VS2005DockPaneCaption.ImageButtonClose, VS2005DockPaneCaption.ImageButtonClose);
					this.m_toolTip.SetToolTip(this.m_buttonClose, VS2005DockPaneCaption.ToolTipClose);
					this.m_buttonClose.Click += new EventHandler(this.Close_Click);
					base.Controls.Add(this.m_buttonClose);
				}
				return this.m_buttonClose;
			}
		}
		private static Bitmap ImageButtonAutoHide
		{
			get
			{
				if (VS2005DockPaneCaption._imageButtonAutoHide == null)
				{
					VS2005DockPaneCaption._imageButtonAutoHide = Resources.DockPane_AutoHide;
				}
				return VS2005DockPaneCaption._imageButtonAutoHide;
			}
		}
		private static Bitmap ImageButtonDock
		{
			get
			{
				if (VS2005DockPaneCaption._imageButtonDock == null)
				{
					VS2005DockPaneCaption._imageButtonDock = Resources.DockPane_Dock;
				}
				return VS2005DockPaneCaption._imageButtonDock;
			}
		}
		private VS2005DockPaneCaption.InertButton ButtonAutoHide
		{
			get
			{
				if (this.m_buttonAutoHide == null)
				{
					this.m_buttonAutoHide = new VS2005DockPaneCaption.InertButton(this, VS2005DockPaneCaption.ImageButtonDock, VS2005DockPaneCaption.ImageButtonAutoHide);
					this.m_toolTip.SetToolTip(this.m_buttonAutoHide, VS2005DockPaneCaption.ToolTipAutoHide);
					this.m_buttonAutoHide.Click += new EventHandler(this.AutoHide_Click);
					base.Controls.Add(this.m_buttonAutoHide);
				}
				return this.m_buttonAutoHide;
			}
		}
		private static Bitmap ImageButtonOptions
		{
			get
			{
				if (VS2005DockPaneCaption._imageButtonOptions == null)
				{
					VS2005DockPaneCaption._imageButtonOptions = Resources.DockPane_Option;
				}
				return VS2005DockPaneCaption._imageButtonOptions;
			}
		}
		private VS2005DockPaneCaption.InertButton ButtonOptions
		{
			get
			{
				if (this.m_buttonOptions == null)
				{
					this.m_buttonOptions = new VS2005DockPaneCaption.InertButton(this, VS2005DockPaneCaption.ImageButtonOptions, VS2005DockPaneCaption.ImageButtonOptions);
					this.m_toolTip.SetToolTip(this.m_buttonOptions, VS2005DockPaneCaption.ToolTipOptions);
					this.m_buttonOptions.Click += new EventHandler(this.Options_Click);
					base.Controls.Add(this.m_buttonOptions);
				}
				return this.m_buttonOptions;
			}
		}
		private IContainer Components
		{
			get
			{
				return this.m_components;
			}
		}
		private static int TextGapTop
		{
			get
			{
				return 2;
			}
		}
		public Font TextFont
		{
			get
			{
				return base.DockPane.DockPanel.Skin.DockPaneStripSkin.TextFont;
			}
		}
		private static int TextGapBottom
		{
			get
			{
				return 0;
			}
		}
		private static int TextGapLeft
		{
			get
			{
				return 3;
			}
		}
		private static int TextGapRight
		{
			get
			{
				return 3;
			}
		}
		private static int ButtonGapTop
		{
			get
			{
				return 2;
			}
		}
		private static int ButtonGapBottom
		{
			get
			{
				return 1;
			}
		}
		private static int ButtonGapLeft
		{
			get
			{
				return 1;
			}
		}
		private static int ButtonGapRight
		{
			get
			{
				return 2;
			}
		}
		private static int ButtonGapBetween
		{
			get
			{
				return 1;
			}
		}
		private static string ToolTipClose
		{
			get
			{
				if (VS2005DockPaneCaption._toolTipClose == null)
				{
					VS2005DockPaneCaption._toolTipClose = Strings.DockPaneCaption_ToolTipClose;
				}
				return VS2005DockPaneCaption._toolTipClose;
			}
		}
		private static string ToolTipOptions
		{
			get
			{
				if (VS2005DockPaneCaption._toolTipOptions == null)
				{
					VS2005DockPaneCaption._toolTipOptions = Strings.DockPaneCaption_ToolTipOptions;
				}
				return VS2005DockPaneCaption._toolTipOptions;
			}
		}
		private static string ToolTipAutoHide
		{
			get
			{
				if (VS2005DockPaneCaption._toolTipAutoHide == null)
				{
					VS2005DockPaneCaption._toolTipAutoHide = Strings.DockPaneCaption_ToolTipAutoHide;
				}
				return VS2005DockPaneCaption._toolTipAutoHide;
			}
		}
		private static Blend ActiveBackColorGradientBlend
		{
			get
			{
				if (VS2005DockPaneCaption._activeBackColorGradientBlend == null)
				{
					VS2005DockPaneCaption._activeBackColorGradientBlend = new Blend(2)
					{
						Factors = new float[]
						{
							0.5f,
							1f
						},
						Positions = new float[]
						{
							0f,
							1f
						}
					};
				}
				return VS2005DockPaneCaption._activeBackColorGradientBlend;
			}
		}
		private Color TextColor
		{
			get
			{
				Color textColor;
				if (base.DockPane.IsActivated)
				{
					textColor = base.DockPane.DockPanel.Skin.DockPaneStripSkin.ToolWindowGradient.ActiveCaptionGradient.TextColor;
				}
				else
				{
					textColor = base.DockPane.DockPanel.Skin.DockPaneStripSkin.ToolWindowGradient.InactiveCaptionGradient.TextColor;
				}
				return textColor;
			}
		}
		private TextFormatFlags TextFormat
		{
			get
			{
				TextFormatFlags result;
				if (this.RightToLeft == RightToLeft.No)
				{
					result = VS2005DockPaneCaption._textFormat;
				}
				else
				{
					result = (VS2005DockPaneCaption._textFormat | TextFormatFlags.RightToLeft | TextFormatFlags.Right);
				}
				return result;
			}
		}
		private bool CloseButtonEnabled
		{
			get
			{
				return base.DockPane.ActiveContent != null && base.DockPane.ActiveContent.DockHandler.CloseButton;
			}
		}
		private bool CloseButtonVisible
		{
			get
			{
				return base.DockPane.ActiveContent != null && base.DockPane.ActiveContent.DockHandler.CloseButtonVisible;
			}
		}
		private bool ShouldShowAutoHideButton
		{
			get
			{
				return !base.DockPane.IsFloat;
			}
		}
		public VS2005DockPaneCaption(DockPane pane) : base(pane)
		{
			base.SuspendLayout();
			this.m_components = new Container();
			this.m_toolTip = new ToolTip(this.Components);
			base.ResumeLayout();
		}
		protected override void Dispose(bool disposing)
		{
			if (disposing)
			{
				this.Components.Dispose();
			}
			base.Dispose(disposing);
		}
		protected internal override int MeasureHeight()
		{
			checked
			{
				int num = this.TextFont.Height + VS2005DockPaneCaption.TextGapTop + VS2005DockPaneCaption.TextGapBottom;
				if (num < this.ButtonClose.Image.Height + VS2005DockPaneCaption.ButtonGapTop + VS2005DockPaneCaption.ButtonGapBottom)
				{
					num = this.ButtonClose.Image.Height + VS2005DockPaneCaption.ButtonGapTop + VS2005DockPaneCaption.ButtonGapBottom;
				}
				return num;
			}
		}
		protected override void OnPaint(PaintEventArgs e)
		{
			base.OnPaint(e);
			this.DrawCaption(e.Graphics);
		}
		private void DrawCaption(Graphics g)
		{
			checked
			{
				if (base.ClientRectangle.Width != 0 && base.ClientRectangle.Height != 0)
				{
					if (base.DockPane.IsActivated)
					{
						Color startColor = base.DockPane.DockPanel.Skin.DockPaneStripSkin.ToolWindowGradient.ActiveCaptionGradient.StartColor;
						Color endColor = base.DockPane.DockPanel.Skin.DockPaneStripSkin.ToolWindowGradient.ActiveCaptionGradient.EndColor;
						LinearGradientMode linearGradientMode = base.DockPane.DockPanel.Skin.DockPaneStripSkin.ToolWindowGradient.ActiveCaptionGradient.LinearGradientMode;
						using (LinearGradientBrush linearGradientBrush = new LinearGradientBrush(base.ClientRectangle, startColor, endColor, linearGradientMode))
						{
							linearGradientBrush.Blend = VS2005DockPaneCaption.ActiveBackColorGradientBlend;
							g.FillRectangle(linearGradientBrush, base.ClientRectangle);
						}
					}
					else
					{
						Color startColor = base.DockPane.DockPanel.Skin.DockPaneStripSkin.ToolWindowGradient.InactiveCaptionGradient.StartColor;
						Color endColor = base.DockPane.DockPanel.Skin.DockPaneStripSkin.ToolWindowGradient.InactiveCaptionGradient.EndColor;
						LinearGradientMode linearGradientMode = base.DockPane.DockPanel.Skin.DockPaneStripSkin.ToolWindowGradient.InactiveCaptionGradient.LinearGradientMode;
						using (LinearGradientBrush linearGradientBrush = new LinearGradientBrush(base.ClientRectangle, startColor, endColor, linearGradientMode))
						{
							g.FillRectangle(linearGradientBrush, base.ClientRectangle);
						}
					}
					Rectangle clientRectangle = base.ClientRectangle;
					Rectangle rectangle = clientRectangle;
					rectangle.X += VS2005DockPaneCaption.TextGapLeft;
					rectangle.Width -= VS2005DockPaneCaption.TextGapLeft + VS2005DockPaneCaption.TextGapRight;
					rectangle.Width -= VS2005DockPaneCaption.ButtonGapLeft + this.ButtonClose.Width + VS2005DockPaneCaption.ButtonGapRight;
					if (this.ShouldShowAutoHideButton)
					{
						rectangle.Width -= this.ButtonAutoHide.Width + VS2005DockPaneCaption.ButtonGapBetween;
					}
					if (base.HasTabPageContextMenu)
					{
						rectangle.Width -= this.ButtonOptions.Width + VS2005DockPaneCaption.ButtonGapBetween;
					}
					rectangle.Y += VS2005DockPaneCaption.TextGapTop;
					rectangle.Height -= VS2005DockPaneCaption.TextGapTop + VS2005DockPaneCaption.TextGapBottom;
					Color textColor;
					if (base.DockPane.IsActivated)
					{
						textColor = base.DockPane.DockPanel.Skin.DockPaneStripSkin.ToolWindowGradient.ActiveCaptionGradient.TextColor;
					}
					else
					{
						textColor = base.DockPane.DockPanel.Skin.DockPaneStripSkin.ToolWindowGradient.InactiveCaptionGradient.TextColor;
					}
					TextRenderer.DrawText(g, base.DockPane.CaptionText, this.TextFont, DrawHelper.RtlTransform(this, rectangle), textColor, this.TextFormat);
				}
			}
		}
		protected override void OnLayout(LayoutEventArgs levent)
		{
			this.SetButtonsPosition();
			base.OnLayout(levent);
		}
		protected override void OnRefreshChanges()
		{
			this.SetButtons();
			base.Invalidate();
		}
		private void SetButtons()
		{
			this.ButtonClose.Enabled = this.CloseButtonEnabled;
			this.ButtonClose.Visible = this.CloseButtonVisible;
			this.ButtonAutoHide.Visible = this.ShouldShowAutoHideButton;
			this.ButtonOptions.Visible = base.HasTabPageContextMenu;
			this.ButtonClose.RefreshChanges();
			this.ButtonAutoHide.RefreshChanges();
			this.ButtonOptions.RefreshChanges();
			this.SetButtonsPosition();
		}
		private void SetButtonsPosition()
		{
			Rectangle clientRectangle = base.ClientRectangle;
			int num = this.ButtonClose.Image.Width;
			int num2 = this.ButtonClose.Image.Height;
			checked
			{
				int num3 = clientRectangle.Height - VS2005DockPaneCaption.ButtonGapTop - VS2005DockPaneCaption.ButtonGapBottom;
				if (num2 < num3)
				{
					num *= num3 / num2;
					num2 = num3;
				}
				Size size = new Size(num, num2);
				int x = clientRectangle.X + clientRectangle.Width - 1 - VS2005DockPaneCaption.ButtonGapRight - this.m_buttonClose.Width;
				int y = clientRectangle.Y + VS2005DockPaneCaption.ButtonGapTop;
				Point location = new Point(x, y);
				this.ButtonClose.Bounds = DrawHelper.RtlTransform(this, new Rectangle(location, size));
				if (this.CloseButtonVisible)
				{
					location.Offset(0 - (num + VS2005DockPaneCaption.ButtonGapBetween), 0);
				}
				this.ButtonAutoHide.Bounds = DrawHelper.RtlTransform(this, new Rectangle(location, size));
				if (this.ShouldShowAutoHideButton)
				{
					location.Offset(0 - (num + VS2005DockPaneCaption.ButtonGapBetween), 0);
				}
				this.ButtonOptions.Bounds = DrawHelper.RtlTransform(this, new Rectangle(location, size));
			}
		}
		private void Close_Click(object sender, EventArgs e)
		{
			base.DockPane.CloseActiveContent();
		}
		private void AutoHide_Click(object sender, EventArgs e)
		{
			base.DockPane.DockState = DockHelper.ToggleAutoHideState(base.DockPane.DockState);
			if (DockHelper.IsDockStateAutoHide(base.DockPane.DockState))
			{
				base.DockPane.DockPanel.ActiveAutoHideContent = null;
				base.DockPane.NestedDockingStatus.NestedPanes.SwitchPaneWithFirstChild(base.DockPane);
			}
		}
		private void Options_Click(object sender, EventArgs e)
		{
			base.ShowTabPageContextMenu(base.PointToClient(Control.MousePosition));
		}
		protected override void OnRightToLeftChanged(EventArgs e)
		{
			base.OnRightToLeftChanged(e);
			base.PerformLayout();
		}
	}
}
