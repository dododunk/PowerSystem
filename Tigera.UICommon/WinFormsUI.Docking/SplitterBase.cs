using System;
using System.Drawing;
using System.Windows.Forms;
namespace WinFormsUI.Docking
{
	internal class SplitterBase : Control
	{
		public override DockStyle Dock
		{
			get
			{
				return base.Dock;
			}
			set
			{
				base.SuspendLayout();
				base.Dock = value;
				if (this.Dock == DockStyle.Left || this.Dock == DockStyle.Right)
				{
					base.Width = this.SplitterSize;
				}
				else
				{
					if (this.Dock == DockStyle.Top || this.Dock == DockStyle.Bottom)
					{
						base.Height = this.SplitterSize;
					}
					else
					{
						base.Bounds = Rectangle.Empty;
					}
				}
				if (this.Dock == DockStyle.Left || this.Dock == DockStyle.Right)
				{
					this.Cursor = Cursors.VSplit;
				}
				else
				{
					if (this.Dock == DockStyle.Top || this.Dock == DockStyle.Bottom)
					{
						this.Cursor = Cursors.HSplit;
					}
					else
					{
						this.Cursor = Cursors.Default;
					}
				}
				base.ResumeLayout();
			}
		}
		protected virtual int SplitterSize
		{
			get
			{
				return 0;
			}
		}
		public SplitterBase()
		{
			base.SetStyle(ControlStyles.Selectable, false);
		}
		protected override void OnMouseDown(MouseEventArgs e)
		{
			base.OnMouseDown(e);
			if (e.Button == MouseButtons.Left)
			{
				this.StartDrag();
			}
		}
		protected virtual void StartDrag()
		{
		}
		protected override void WndProc(ref Message m)
		{
			if (m.Msg != 33)
			{
				base.WndProc(ref m);
			}
		}
	}
}
