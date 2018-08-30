using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.Windows.Forms;
namespace WinFormsUI.Docking
{
	internal abstract class InertButtonBase : Control
	{
		private bool m_isMouseOver = false;
		public abstract Bitmap Image
		{
			get;
		}
		protected bool IsMouseOver
		{
			get
			{
				return this.m_isMouseOver;
			}
			private set
			{
				if (this.m_isMouseOver != value)
				{
					this.m_isMouseOver = value;
					base.Invalidate();
				}
			}
		}
		protected override Size DefaultSize
		{
			get
			{
				return Resources.DockPane_Close.Size;
			}
		}
		protected InertButtonBase()
		{
			base.SetStyle(ControlStyles.SupportsTransparentBackColor, true);
			this.BackColor = Color.Transparent;
		}
		protected override void OnMouseMove(MouseEventArgs e)
		{
			base.OnMouseMove(e);
			bool flag = base.ClientRectangle.Contains(e.X, e.Y);
			if (this.IsMouseOver != flag)
			{
				this.IsMouseOver = flag;
			}
		}
		protected override void OnMouseEnter(EventArgs e)
		{
			base.OnMouseEnter(e);
			if (!this.IsMouseOver)
			{
				this.IsMouseOver = true;
			}
		}
		protected override void OnMouseLeave(EventArgs e)
		{
			base.OnMouseLeave(e);
			if (this.IsMouseOver)
			{
				this.IsMouseOver = false;
			}
		}
		protected override void OnPaint(PaintEventArgs e)
		{
			if (this.IsMouseOver && base.Enabled)
			{
				using (Pen pen = new Pen(this.ForeColor))
				{
					e.Graphics.DrawRectangle(pen, Rectangle.Inflate(base.ClientRectangle, -1, -1));
				}
			}
			using (ImageAttributes imageAttributes = new ImageAttributes())
			{
				ColorMap[] array = new ColorMap[2];
				array[0] = new ColorMap();
				array[0].OldColor = Color.FromArgb(0, 0, 0);
				array[0].NewColor = this.ForeColor;
				array[1] = new ColorMap();
				array[1].OldColor = this.Image.GetPixel(0, 0);
				array[1].NewColor = Color.Transparent;
				imageAttributes.SetRemapTable(array);
				e.Graphics.DrawImage(this.Image, new Rectangle(0, 0, this.Image.Width, this.Image.Height), 0, 0, this.Image.Width, this.Image.Height, GraphicsUnit.Pixel, imageAttributes);
			}
			base.OnPaint(e);
		}
		public void RefreshChanges()
		{
			if (!base.IsDisposed)
			{
				bool flag = base.ClientRectangle.Contains(base.PointToClient(Control.MousePosition));
				if (flag != this.IsMouseOver)
				{
					this.IsMouseOver = flag;
				}
				this.OnRefreshChanges();
			}
		}
		protected virtual void OnRefreshChanges()
		{
		}
	}
}
