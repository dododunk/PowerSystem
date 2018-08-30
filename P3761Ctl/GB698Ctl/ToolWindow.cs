using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using WinFormsUI.Docking;
namespace GB698Ctl
{
	public class ToolWindow : DockContent
	{
		private IContainer components = null;
		public ToolWindow()
		{
			this.InitializeComponent();
			base.HideOnClose = true;
			base.TabText = this.Text;
		}
		protected override void Dispose(bool disposing)
		{
			if (disposing && this.components != null)
			{
				this.components.Dispose();
			}
			base.Dispose(disposing);
		}
		private void InitializeComponent()
		{
			this.components = new Container();
			base.SuspendLayout();
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(193, 376);
			//base.DockAreas = (DockAreas.Float | DockAreas.DockLeft | DockAreas.DockRight | DockAreas.DockTop | DockAreas.DockBottom);
			this.Font = new Font("宋体", 9f, FontStyle.Regular, GraphicsUnit.Point, 134);
			base.Name = "ToolWindow";
			base.TabText = "ToolWindow";
			base.ResumeLayout(false);
		}
	}
}
