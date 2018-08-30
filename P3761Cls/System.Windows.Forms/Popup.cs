using System;
using System.ComponentModel;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Security.Permissions;
using System.Threading;
using System.Windows.Forms.VisualStyles;
namespace System.Windows.Forms
{
	public class Popup : ToolStripDropDown
	{
		private const int frames = 1;
		private const int totalduration = 0;
		private const int frameduration = 0;
		private IContainer components = null;
		private Control content;
		private bool fade;
		private bool focusOnOpen = true;
		private bool acceptAlt = true;
		private Popup ownerPopup;
		private Popup childPopup;
		private bool _resizable;
		private bool resizable;
		private ToolStripControlHost host;
		private Size minSize;
		private Size maxSize;
		private bool resizableTop;
		private bool resizableRight;
		public DateTime LastClosedTimeStamp = DateTime.Now;
		private VisualStyleRenderer sizeGripRenderer;
		public Control Content
		{
			get
			{
				return this.content;
			}
		}
		public bool UseFadeEffect
		{
			get
			{
				return this.fade;
			}
			set
			{
				if (this.fade != value)
				{
					this.fade = value;
				}
			}
		}
		public bool FocusOnOpen
		{
			get
			{
				return this.focusOnOpen;
			}
			set
			{
				this.focusOnOpen = value;
			}
		}
		public bool AcceptAlt
		{
			get
			{
				return this.acceptAlt;
			}
			set
			{
				this.acceptAlt = value;
			}
		}
		public bool Resizable
		{
			get
			{
				return this.resizable && this._resizable;
			}
			set
			{
				this.resizable = value;
			}
		}
		public new Size MinimumSize
		{
			get
			{
				return this.minSize;
			}
			set
			{
				this.minSize = value;
			}
		}
		public new Size MaximumSize
		{
			get
			{
				return this.maxSize;
			}
			set
			{
				this.maxSize = value;
			}
		}
		protected override CreateParams CreateParams
		{
			[SecurityPermission(SecurityAction.LinkDemand, Flags = SecurityPermissionFlag.UnmanagedCode)]
			get
			{
				CreateParams createParams = base.CreateParams;
				createParams.ExStyle |= 134217728;
				return createParams;
			}
		}
		protected override void Dispose(bool disposing)
		{
			if (disposing)
			{
				if (this.components != null)
				{
					this.components.Dispose();
				}
				if (this.content != null)
				{
					Control control = this.content;
					this.content = null;
					control.Dispose();
				}
			}
			base.Dispose(disposing);
		}
		private void InitializeComponent()
		{
			this.components = new Container();
		}
		public Popup(Control content)
		{
			var tmp = this;
			if (content == null)
			{
				throw new ArgumentNullException("content");
			}
			this.content = content;
			this.fade = (SystemInformation.IsMenuAnimationEnabled && SystemInformation.IsMenuFadeEnabled);
			this._resizable = true;
			this.InitializeComponent();
			this.AutoSize = false;
			this.DoubleBuffered = true;
			base.ResizeRedraw = true;
			this.host = new ToolStripControlHost(content);
			base.Padding = (base.Margin = (this.host.Padding = (this.host.Margin = Padding.Empty)));
			this.MinimumSize = content.MinimumSize;
			content.MinimumSize = content.Size;
			this.MaximumSize = content.MaximumSize;
			content.MaximumSize = content.Size;
			base.Size = content.Size;
			content.Location = Point.Empty;
			this.Items.Add(this.host);
			content.Disposed += delegate(object sender, EventArgs e)
			{
				content = null;
				tmp.Dispose(true);
			}
			;
			content.RegionChanged += delegate(object sender, EventArgs e)
			{
				this.UpdateRegion();
			}
			;
			content.Paint += delegate(object sender, PaintEventArgs e)
			{
				this.PaintSizeGrip(e);
			}
			;
			this.UpdateRegion();
		}
		protected override bool ProcessDialogKey(Keys keyData)
		{
			return (!this.acceptAlt || (keyData & Keys.Alt) != Keys.Alt) && base.ProcessDialogKey(keyData);
		}
		protected void UpdateRegion()
		{
			if (base.Region != null)
			{
				base.Region.Dispose();
				base.Region = null;
			}
			if (this.content.Region != null)
			{
				base.Region = this.content.Region.Clone();
			}
		}
		public void Show(Control control)
		{
			if (control == null)
			{
				throw new ArgumentNullException("control");
			}
			this.SetOwnerItem(control);
			this.Show(control, control.ClientRectangle);
		}
		public void Show(Control control, Rectangle area)
		{
			if (control == null)
			{
				throw new ArgumentNullException("control");
			}
			this.SetOwnerItem(control);
			this.resizableTop = (this.resizableRight = false);
			checked
			{
				Point point = control.PointToScreen(new Point(area.Left, area.Top + area.Height));
				Rectangle workingArea = Screen.FromControl(control).WorkingArea;
				if (point.X + base.Size.Width > workingArea.Left + workingArea.Width)
				{
					this.resizableRight = true;
					point.X = workingArea.Left + workingArea.Width - base.Size.Width;
				}
				if (point.Y + base.Size.Height > workingArea.Top + workingArea.Height)
				{
					this.resizableTop = true;
					point.Y -= base.Size.Height + area.Height;
				}
				point = control.PointToClient(point);
				base.Show(control, point, ToolStripDropDownDirection.BelowRight);
			}
		}
		protected override void SetVisibleCore(bool visible)
		{
			double opacity = base.Opacity;
			if (visible && this.fade && this.focusOnOpen)
			{
				base.Opacity = 0.0;
			}
			base.SetVisibleCore(visible);
			checked
			{
				if (visible && this.fade && this.focusOnOpen)
				{
					for (int i = 1; i <= 1; i++)
					{
						if (i > 1)
						{
							Thread.Sleep(0);
						}
						base.Opacity = unchecked(opacity * (double)i) / 1.0;
					}
					base.Opacity = opacity;
				}
			}
		}
		private void SetOwnerItem(Control control)
		{
			if (control != null)
			{
				if (control is Popup)
				{
					Popup popup = control as Popup;
					this.ownerPopup = popup;
					this.ownerPopup.childPopup = this;
					base.OwnerItem = popup.Items[0];
				}
				else
				{
					if (control.Parent != null)
					{
						this.SetOwnerItem(control.Parent);
					}
				}
			}
		}
		protected override void OnSizeChanged(EventArgs e)
		{
			this.content.MinimumSize = base.Size;
			this.content.MaximumSize = base.Size;
			this.content.Size = base.Size;
			this.content.Location = Point.Empty;
			base.OnSizeChanged(e);
		}
		protected override void OnOpening(CancelEventArgs e)
		{
			if (this.content.IsDisposed || this.content.Disposing)
			{
				e.Cancel = true;
			}
			else
			{
				this.UpdateRegion();
				base.OnOpening(e);
			}
		}
		protected override void OnOpened(EventArgs e)
		{
			if (this.ownerPopup != null)
			{
				this.ownerPopup._resizable = false;
			}
			if (this.focusOnOpen)
			{
				this.content.Focus();
			}
			base.OnOpened(e);
		}
		protected override void OnClosed(ToolStripDropDownClosedEventArgs e)
		{
			if (this.ownerPopup != null)
			{
				this.ownerPopup._resizable = true;
			}
			base.OnClosed(e);
		}
		protected override void OnVisibleChanged(EventArgs e)
		{
			if (!base.Visible)
			{
				this.LastClosedTimeStamp = DateTime.Now;
			}
			base.OnVisibleChanged(e);
		}
		protected override void WndProc(ref Message m)
		{
			if (!this.InternalProcessResizing(ref m, false))
			{
				base.WndProc(ref m);
			}
		}
		public bool ProcessResizing(ref Message m)
		{
			return this.InternalProcessResizing(ref m, true);
		}
		private bool InternalProcessResizing(ref Message m, bool contentControl)
		{
			if (m.Msg == 134 && m.WParam != IntPtr.Zero && this.childPopup != null && this.childPopup.Visible)
			{
				this.childPopup.Hide();
			}
			bool result;
			if (!this.Resizable)
			{
				result = false;
			}
			else
			{
				if (m.Msg == 132)
				{
					result = this.OnNcHitTest(ref m, contentControl);
				}
				else
				{
					result = (m.Msg == 36 && this.OnGetMinMaxInfo(ref m));
				}
			}
			return result;
		}
		private bool OnGetMinMaxInfo(ref Message m)
		{
			NativeMethods.MINMAXINFO mINMAXINFO = (NativeMethods.MINMAXINFO)Marshal.PtrToStructure(m.LParam, typeof(NativeMethods.MINMAXINFO));
			mINMAXINFO.maxTrackSize = this.MaximumSize;
			mINMAXINFO.minTrackSize = this.MinimumSize;
			Marshal.StructureToPtr(mINMAXINFO, m.LParam, false);
			return true;
		}
		private bool OnNcHitTest(ref Message m, bool contentControl)
		{
			int x = NativeMethods.LOWORD(m.LParam);
			int y = NativeMethods.HIWORD(m.LParam);
			Point pt = base.PointToClient(new Point(x, y));
			GripBounds gripBounds = new GripBounds(contentControl ? this.content.ClientRectangle : base.ClientRectangle);
			IntPtr intPtr = new IntPtr(-1);
			bool result;
			if (this.resizableTop)
			{
				if (this.resizableRight && gripBounds.TopLeft.Contains(pt))
				{
					m.Result = (contentControl ? intPtr : ((IntPtr)13));
					result = true;
					return result;
				}
				if (!this.resizableRight && gripBounds.TopRight.Contains(pt))
				{
					m.Result = (contentControl ? intPtr : ((IntPtr)14));
					result = true;
					return result;
				}
				if (gripBounds.Top.Contains(pt))
				{
					m.Result = (contentControl ? intPtr : ((IntPtr)12));
					result = true;
					return result;
				}
			}
			else
			{
				if (this.resizableRight && gripBounds.BottomLeft.Contains(pt))
				{
					m.Result = (contentControl ? intPtr : ((IntPtr)16));
					result = true;
					return result;
				}
				if (!this.resizableRight && gripBounds.BottomRight.Contains(pt))
				{
					m.Result = (contentControl ? intPtr : ((IntPtr)17));
					result = true;
					return result;
				}
				if (gripBounds.Bottom.Contains(pt))
				{
					m.Result = (contentControl ? intPtr : ((IntPtr)15));
					result = true;
					return result;
				}
			}
			if (this.resizableRight && gripBounds.Left.Contains(pt))
			{
				m.Result = (contentControl ? intPtr : ((IntPtr)10));
				result = true;
			}
			else
			{
				if (!this.resizableRight && gripBounds.Right.Contains(pt))
				{
					m.Result = (contentControl ? intPtr : ((IntPtr)11));
					result = true;
				}
				else
				{
					result = false;
				}
			}
			return result;
		}
		public void PaintSizeGrip(PaintEventArgs e)
		{
			checked
			{
				if (e != null && e.Graphics != null && this.resizable)
				{
					Size clientSize = this.content.ClientSize;
					if (Application.RenderWithVisualStyles)
					{
						if (this.sizeGripRenderer == null)
						{
							this.sizeGripRenderer = new VisualStyleRenderer(VisualStyleElement.Status.Gripper.Normal);
						}
						this.sizeGripRenderer.DrawBackground(e.Graphics, new Rectangle(clientSize.Width - 16, clientSize.Height - 16, 16, 16));
					}
					else
					{
						ControlPaint.DrawSizeGrip(e.Graphics, this.content.BackColor, clientSize.Width - 16, clientSize.Height - 16, 16, 16);
					}
				}
			}
		}
	}
}
