using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN06_01 : iForm
	{
		private IContainer components = null;
		private TextBox textBox1;
		private Label label1;
		public AFN06_01()
		{
			this.InitializeComponent();
		}
		protected override void GetText()
		{
			this.Data = "";
			this.Data = base.OperaSend(this.textBox1.Text.Trim(), 16, "BIN");
		}
		public override void SetText()
		{
			if (!string.IsNullOrEmpty(this.Data))
			{
				string data = this.Data;
				this.textBox1.Text = base.OperaRec(data, "BIN");
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
			this.label1 = new Label();
			this.textBox1 = new TextBox();
			base.SuspendLayout();
			this.label1.AutoSize = true;
			this.label1.Location = new Point(31, 32);
			this.label1.Name = "label1";
			this.label1.Size = new Size(77, 12);
			this.label1.TabIndex = 0;
			this.label1.Text = "认证请求信息";
			this.textBox1.Location = new Point(114, 29);
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new Size(107, 21);
			this.textBox1.TabIndex = 1;
			this.textBox1.Text = "0";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(259, 81);
			base.Controls.Add(this.textBox1);
			base.Controls.Add(this.label1);
			base.Name = "AFN06_01";
			this.Text = "身份认证请求";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
