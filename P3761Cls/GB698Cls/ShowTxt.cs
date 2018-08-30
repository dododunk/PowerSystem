using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class ShowTxt : iForm
	{
		private IContainer components = null;
		private TextBox textBox1;
		public ShowTxt()
		{
			this.InitializeComponent();
			this.NeedSave = false;
		}
		protected override void GetText()
		{
			this.Data = this.Data;
		}
		public override void SetText()
		{
			if (!string.IsNullOrEmpty(this.Data))
			{
				string data = this.Data;
				this.textBox1.Text = data;
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
			}
			base.Dispose(disposing);
		}
		private void InitializeComponent()
		{
            base.SuspendLayout();
			this.textBox1 = new TextBox();

			this.textBox1.Dock = DockStyle.Fill;
			this.textBox1.Location = new Point(0, 0);
			this.textBox1.Multiline = true;
			this.textBox1.Name = "textBox1";
			this.textBox1.ScrollBars = ScrollBars.Both;
			this.textBox1.Size = new Size(562, 473);
			this.textBox1.TabIndex = 0;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(562, 473);
			base.Controls.Add(this.textBox1);
			
			base.Name = "ShowTxt";
			this.Text = "数据显示";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
