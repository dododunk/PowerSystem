using EasyRender_CustomTheme;
using EasyRender_VS2010Theme;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Runtime.InteropServices;
namespace System.Windows.Forms
{
	public class SkinForm : Form
	{
		private SkinFormRenderer _renderer;
		private RoundStyle _roundStyle = RoundStyle.All;
		private int _radius = 8;
		private int _captionHeight = 24;
		private Font _captionFont = SystemFonts.CaptionFont;
		private int _borderWidth = 3;
		private Size _minimizeBoxSize = new Size(32, 18);
		private Size _maximizeBoxSize = new Size(32, 18);
		private Size _closeBoxSize = new Size(32, 18);
		private Point _controlBoxOffset = new Point(6, 0);
		private int _controlBoxSpace = -1;
		private bool _active;
		private ControlBoxManager _controlBoxManager;
		private Padding _padding;
		private bool _canResize = true;
		private bool _inPosChanged;
		private ToolTip _toolTip;
		private static readonly object EventRendererChanged = new object();
		public event EventHandler RendererChangled
		{
			add
			{
				base.Events.AddHandler(SkinForm.EventRendererChanged, value);
			}
			remove
			{
				base.Events.RemoveHandler(SkinForm.EventRendererChanged, value);
			}
		}
		[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
		public SkinFormRenderer Renderer
		{
			get
			{
				if (this._renderer == null)
				{
					this._renderer = new SkinFormProfessionalRenderer(new SkinFormColorTable_VS2010Theme());
				}
				return this._renderer;
			}
			set
			{
				this._renderer = value;
				this.OnRendererChanged(EventArgs.Empty);
			}
		}
		public override string Text
		{
			get
			{
				return base.Text;
			}
			set
			{
				base.Text = value;
				base.Invalidate(new Rectangle(0, 0, base.Width, checked(this.CaptionHeight + 1)));
			}
		}
		[DefaultValue(typeof(RoundStyle), "1")]
		public RoundStyle RoundStyle
		{
			get
			{
				return this._roundStyle;
			}
			set
			{
				if (this._roundStyle != value)
				{
					this._roundStyle = value;
					this.SetReion();
					base.Invalidate();
				}
			}
		}
		[DefaultValue(8)]
		public int Radius
		{
			get
			{
				return this._radius;
			}
			set
			{
				if (this._radius != value)
				{
					this._radius = ((value < 4) ? 4 : value);
					this.SetReion();
					base.Invalidate();
				}
			}
		}
		[DefaultValue(24)]
		public int CaptionHeight
		{
			get
			{
				return this._captionHeight;
			}
			set
			{
				if (this._captionHeight != value)
				{
					this._captionHeight = ((value < this._borderWidth) ? this._borderWidth : value);
					base.Invalidate();
				}
			}
		}
		[DefaultValue(3)]
		public int BorderWidth
		{
			get
			{
				return this._borderWidth;
			}
			set
			{
				if (this._borderWidth != value)
				{
					this._borderWidth = ((value < 1) ? 1 : value);
				}
			}
		}
		[DefaultValue(typeof(Font), "CaptionFont")]
		public Font CaptionFont
		{
			get
			{
				return this._captionFont;
			}
			set
			{
				if (value == null)
				{
					this._captionFont = SystemFonts.CaptionFont;
				}
				else
				{
					this._captionFont = value;
				}
				base.Invalidate(this.CaptionRect);
			}
		}
		[DefaultValue(typeof(Size), "32, 18")]
		public Size MinimizeBoxSize
		{
			get
			{
				return this._minimizeBoxSize;
			}
			set
			{
				if (this._minimizeBoxSize != value)
				{
					this._minimizeBoxSize = value;
					base.Invalidate();
				}
			}
		}
		[DefaultValue(typeof(Size), "32, 18")]
		public Size MaximizeBoxSize
		{
			get
			{
				return this._maximizeBoxSize;
			}
			set
			{
				if (this._maximizeBoxSize != value)
				{
					this._maximizeBoxSize = value;
					base.Invalidate();
				}
			}
		}
		[DefaultValue(typeof(Size), "32, 18")]
		public Size CloseBoxSize
		{
			get
			{
				return this._closeBoxSize;
			}
			set
			{
				if (this._closeBoxSize != value)
				{
					this._closeBoxSize = value;
					base.Invalidate();
				}
			}
		}
		[DefaultValue(typeof(Point), "6, 0")]
		public Point ControlBoxOffset
		{
			get
			{
				return this._controlBoxOffset;
			}
			set
			{
				if (this._controlBoxOffset != value)
				{
					this._controlBoxOffset = value;
					base.Invalidate();
				}
			}
		}
		[DefaultValue(-1)]
		public int ControlBoxSpace
		{
			get
			{
				return this._controlBoxSpace;
			}
			set
			{
				if (this._controlBoxSpace != value)
				{
					this._controlBoxSpace = ((value < 0) ? 0 : value);
					base.Invalidate();
				}
			}
		}
		[DefaultValue(true)]
		public bool CanResize
		{
			get
			{
				return this._canResize;
			}
			set
			{
				this._canResize = value;
			}
		}
		[DefaultValue(typeof(Padding), "0")]
		public new Padding Padding
		{
			get
			{
				return this._padding;
			}
			set
			{
				this._padding = value;
				base.Padding = checked(new Padding(this.BorderWidth + this._padding.Left, this.CaptionHeight + this._padding.Top, this.BorderWidth + this._padding.Right, this.BorderWidth + this._padding.Bottom));
			}
		}
		[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden), EditorBrowsable(EditorBrowsableState.Never)]
		public new FormBorderStyle FormBorderStyle
		{
			get
			{
				return base.FormBorderStyle;
			}
			set
			{
				base.FormBorderStyle = FormBorderStyle.None;
			}
		}
		protected override Padding DefaultPadding
		{
			get
			{
				return new Padding(this.BorderWidth, this.CaptionHeight, this.BorderWidth, this.BorderWidth);
			}
		}
		protected override CreateParams CreateParams
		{
			get
			{
				CreateParams createParams = base.CreateParams;
				if (!base.DesignMode)
				{
					createParams.Style |= 262144;
					if (base.ControlBox)
					{
						createParams.Style |= 524288;
					}
					if (base.MinimizeBox)
					{
						createParams.Style |= 131072;
					}
					if (!base.MaximizeBox)
					{
						createParams.Style &= -65537;
					}
					if (this._inPosChanged)
					{
						createParams.Style &= -786433;
						createParams.ExStyle &= -258;
					}
				}
				return createParams;
			}
		}
		internal Rectangle CaptionRect
		{
			get
			{
				return new Rectangle(0, 0, base.Width, this.CaptionHeight);
			}
		}
		internal ControlBoxManager ControlBoxManager
		{
			get
			{
				if (this._controlBoxManager == null)
				{
					this._controlBoxManager = new ControlBoxManager(this);
				}
				return this._controlBoxManager;
			}
		}
		internal Rectangle IconRect
		{
			get
			{
				checked
				{
					Rectangle result;
					if (base.ShowIcon && base.Icon != null)
					{
						int num = SystemInformation.SmallIconSize.Width;
						if (this.CaptionHeight - this.BorderWidth - 4 < num)
						{
							num = this.CaptionHeight - this.BorderWidth - 4;
						}
						result = new Rectangle(this.BorderWidth, this.BorderWidth + (this.CaptionHeight - this.BorderWidth - num) / 2, num, num);
					}
					else
					{
						result = Rectangle.Empty;
					}
					return result;
				}
			}
		}
		internal ToolTip ToolTip
		{
			get
			{
				return this._toolTip;
			}
		}
		public SkinForm()
		{
			this.ApplayTheme("VS2010");
		}
		protected virtual void OnRendererChanged(EventArgs e)
		{
			this.Renderer.InitSkinForm(this);
			EventHandler eventHandler = base.Events[SkinForm.EventRendererChanged] as EventHandler;
			if (eventHandler != null)
			{
				eventHandler(this, e);
			}
			base.Invalidate();
		}
		protected override void OnCreateControl()
		{
			base.OnCreateControl();
			this.SetReion();
		}
		protected override void OnSizeChanged(EventArgs e)
		{
			base.OnSizeChanged(e);
			this.SetReion();
		}
		protected override void OnMouseMove(MouseEventArgs e)
		{
			base.OnMouseMove(e);
			this.ControlBoxManager.ProcessMouseOperate(e.Location, MouseOperate.Move);
		}
		protected override void OnMouseDown(MouseEventArgs e)
		{
			base.OnMouseDown(e);
			this.ControlBoxManager.ProcessMouseOperate(e.Location, MouseOperate.Down);
		}
		protected override void OnMouseUp(MouseEventArgs e)
		{
			base.OnMouseUp(e);
			this.ControlBoxManager.ProcessMouseOperate(e.Location, MouseOperate.Up);
		}
		protected override void OnMouseLeave(EventArgs e)
		{
			base.OnMouseLeave(e);
			this.ControlBoxManager.ProcessMouseOperate(Point.Empty, MouseOperate.Leave);
		}
		protected override void OnMouseHover(EventArgs e)
		{
			base.OnMouseHover(e);
			this.ControlBoxManager.ProcessMouseOperate(base.PointToClient(Control.MousePosition), MouseOperate.Hover);
		}
		protected override void OnPaint(PaintEventArgs e)
		{
			Graphics graphics = e.Graphics;
			Rectangle clientRectangle = base.ClientRectangle;
			SkinFormRenderer renderer = this.Renderer;
			renderer.DrawSkinFormBackground(new SkinFormBackgroundRenderEventArgs(this, graphics, clientRectangle));
			renderer.DrawSkinFormCaption(new SkinFormCaptionRenderEventArgs(this, graphics, this.CaptionRect, this._active));
			renderer.DrawSkinFormBorder(new SkinFormBorderRenderEventArgs(this, graphics, clientRectangle, this._active));
			if (this.ControlBoxManager.CloseBoxVisibale)
			{
				renderer.DrawSkinFormControlBox(new SkinFormControlBoxRenderEventArgs(this, graphics, this.ControlBoxManager.CloseBoxRect, this._active, ControlBoxStyle.Close, this.ControlBoxManager.CloseBoxState));
			}
			if (this.ControlBoxManager.MaximizeBoxVisibale)
			{
				renderer.DrawSkinFormControlBox(new SkinFormControlBoxRenderEventArgs(this, graphics, this.ControlBoxManager.MaximizeBoxRect, this._active, ControlBoxStyle.Maximize, this.ControlBoxManager.MaximizeBoxState));
			}
			if (this.ControlBoxManager.MinimizeBoxVisibale)
			{
				renderer.DrawSkinFormControlBox(new SkinFormControlBoxRenderEventArgs(this, graphics, this.ControlBoxManager.MinimizeBoxRect, this._active, ControlBoxStyle.Minimize, this.ControlBoxManager.MinimizeBoxState));
			}
		}
		protected override void WndProc(ref Message m)
		{
			int msg = m.Msg;
			if (msg != 36)
			{
				if (msg != 71)
				{
					switch (msg)
					{
					case 131:
					case 133:
						break;

					case 132:
						this.WmNcHitTest(ref m);
						break;

					case 134:
						this.WmNcActive(ref m);
						break;

					default:
						base.WndProc(ref m);
						break;
					}
				}
				else
				{
					this._inPosChanged = true;
					base.WndProc(ref m);
					this._inPosChanged = false;
				}
			}
			else
			{
				this.WmGetMinMaxInfo(ref m);
			}
		}
		protected override void Dispose(bool disposing)
		{
			base.Dispose(disposing);
			if (disposing)
			{
				if (this._controlBoxManager != null)
				{
					this._controlBoxManager.Dispose();
					this._controlBoxManager = null;
				}
				this._renderer = null;
				this._toolTip.Dispose();
			}
		}
		private void WmNcHitTest(ref Message m)
		{
			int value = m.LParam.ToInt32();
			Point point = new Point(ToolTipEx_NativeMethods.LOWORD(value), ToolTipEx_NativeMethods.HIWORD(value));
			point = base.PointToClient(point);
			checked
			{
				if (this.IconRect.Contains(point))
				{
					m.Result = new IntPtr(3);
				}
				else
				{
					if (this._canResize)
					{
						if (point.X < 5 && point.Y < 5)
						{
							m.Result = new IntPtr(13);
							return;
						}
						if (point.X > base.Width - 5 && point.Y < 5)
						{
							m.Result = new IntPtr(14);
							return;
						}
						if (point.X < 5 && point.Y > base.Height - 5)
						{
							m.Result = new IntPtr(16);
							return;
						}
						if (point.X > base.Width - 5 && point.Y > base.Height - 5)
						{
							m.Result = new IntPtr(17);
							return;
						}
						if (point.Y < 3)
						{
							m.Result = new IntPtr(12);
							return;
						}
						if (point.Y > base.Height - 3)
						{
							m.Result = new IntPtr(15);
							return;
						}
						if (point.X < 3)
						{
							m.Result = new IntPtr(10);
							return;
						}
						if (point.X > base.Width - 3)
						{
							m.Result = new IntPtr(11);
							return;
						}
					}
					if (point.Y < this.CaptionHeight)
					{
						if (!this.ControlBoxManager.CloseBoxRect.Contains(point) && !this.ControlBoxManager.MaximizeBoxRect.Contains(point) && !this.ControlBoxManager.MinimizeBoxRect.Contains(point))
						{
							m.Result = new IntPtr(2);
							return;
						}
					}
					m.Result = new IntPtr(1);
				}
			}
		}
		private void WmGetMinMaxInfo(ref Message m)
		{
			ToolTipEx_NativeMethods.MINMAXINFO mINMAXINFO = (ToolTipEx_NativeMethods.MINMAXINFO)Marshal.PtrToStructure(m.LParam, typeof(ToolTipEx_NativeMethods.MINMAXINFO));
			checked
			{
				if (this.MaximumSize != Size.Empty)
				{
					mINMAXINFO.maxTrackSize = this.MaximumSize;
				}
				else
				{
					Rectangle workingArea = Screen.GetWorkingArea(this);
					mINMAXINFO.maxPosition = new Point(workingArea.X - this.BorderWidth, workingArea.Y);
					mINMAXINFO.maxTrackSize = new Size(workingArea.Width + this.BorderWidth * 2, workingArea.Height + this.BorderWidth);
				}
				if (this.MinimumSize != Size.Empty)
				{
					mINMAXINFO.minTrackSize = this.MinimumSize;
				}
				else
				{
					mINMAXINFO.minTrackSize = new Size(this.CloseBoxSize.Width + this.MinimizeBoxSize.Width + this.MaximizeBoxSize.Width + this.ControlBoxOffset.X + this.ControlBoxSpace * 2 + SystemInformation.SmallIconSize.Width + this.BorderWidth * 2 + 3, this.CaptionHeight);
				}
				Marshal.StructureToPtr(mINMAXINFO, m.LParam, false);
			}
		}
		private void WmNcActive(ref Message m)
		{
			if (m.WParam.ToInt32() == 1)
			{
				this._active = true;
			}
			else
			{
				this._active = false;
			}
			m.Result = ToolTipEx_NativeMethods.TRUE;
			base.Invalidate();
		}
		private void SetStyles()
		{
			base.SetStyle(ControlStyles.UserPaint | ControlStyles.ResizeRedraw | ControlStyles.AllPaintingInWmPaint | ControlStyles.OptimizedDoubleBuffer, true);
			base.UpdateStyles();
		}
		private void SetReion()
		{
			if (base.Region != null)
			{
				base.Region.Dispose();
			}
			base.Region = this.Renderer.CreateRegion(this);
		}
		public void ApplayTheme(string theme)
		{
			string text = theme.ToUpper();
			if (text != null)
			{
				if (text == "CUSTOM")
				{
					ToolStripManager.Renderer = new EasyRender_CustomTheme.EasyRender();
					this._renderer = new SkinFormProfessionalRenderer(new SkinFormColorTable_CustomTheme());
					goto IL_61;
				}
				if (!(text == "VS2010"))
				{
				}
			}
			ToolStripManager.Renderer = new EasyRender_VS2010Theme.EasyRender();
			this._renderer = new SkinFormProfessionalRenderer(new SkinFormColorTable_VS2010Theme());
			IL_61:
			this.SetStyles();
			this.Init();
		}
		private void Init()
		{
			this._toolTip = new ToolTip();
			base.FormBorderStyle = FormBorderStyle.None;
			this.Renderer.InitSkinForm(this);
			base.Padding = this.DefaultPadding;
		}
	}
}
