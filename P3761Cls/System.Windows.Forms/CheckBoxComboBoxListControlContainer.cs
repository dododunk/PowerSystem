using System;
using System.Drawing;
namespace System.Windows.Forms
{
	public class CheckBoxComboBoxListControlContainer : UserControl
	{
		public CheckBoxComboBoxListControlContainer()
		{
			this.BackColor = SystemColors.Window;
			base.BorderStyle = BorderStyle.FixedSingle;
			base.AutoScaleMode = AutoScaleMode.Inherit;
			base.ResizeRedraw = true;
			this.MinimumSize = new Size(1, 1);
			this.MaximumSize = new Size(500, 500);
		}
		protected override void WndProc(ref Message m)
		{
			if (!(base.Parent as Popup).ProcessResizing(ref m))
			{
				base.WndProc(ref m);
			}
		}
	}
}
