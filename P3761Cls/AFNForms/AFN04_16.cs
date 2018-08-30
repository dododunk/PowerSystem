using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_16 : iForm
	{
		private IContainer components = null;
		private Label label6;
		private TextBox textBox3;
		private TextBox textBox2;
		private Label label2;
		public AFN04_16()
		{
			this.InitializeComponent();
			base.HelpButton = true;
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			text = base.OperaSend(this.textBox3.Text, 32, "ASCII");
			text += base.OperaSend(this.textBox2.Text, 32, "ASCII");
			this.Data = text;
		}
		public override void SetText()
		{
			if (!string.IsNullOrEmpty(this.Data))
			{
				string data = this.Data;
				this.textBox3.Text = base.OperaRec(data.Substring(0, 64), "ASCII");
				this.textBox2.Text = base.OperaRec(data.Substring(64, 64), "ASCII");
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
			this.textBox3 = new TextBox();
			this.label6 = new Label();
			this.textBox2 = new TextBox();
			this.label2 = new Label();
			base.SuspendLayout();
			this.textBox3.Location = new Point(120, 32);
			this.textBox3.Name = "textBox3";
			this.textBox3.Size = new Size(187, 21);
			this.textBox3.TabIndex = 9;
			this.label6.AutoSize = true;
			this.label6.Location = new Point(25, 35);
			this.label6.Name = "label6";
			this.label6.Size = new Size(89, 12);
			this.label6.TabIndex = 8;
			this.label6.Text = "虚拟专网用户名";
			this.textBox2.Location = new Point(120, 69);
			this.textBox2.Name = "textBox2";
			this.textBox2.Size = new Size(187, 21);
			this.textBox2.TabIndex = 22;
			this.label2.AutoSize = true;
			this.label2.Location = new Point(25, 72);
			this.label2.Name = "label2";
			this.label2.Size = new Size(77, 12);
			this.label2.TabIndex = 21;
			this.label2.Text = "虚拟专网密码";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(333, 126);
			base.Controls.Add(this.textBox2);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.textBox3);
			base.Controls.Add(this.label6);
			base.Name = "AFN04_16";
			this.Text = "虚拟专网用户名、密码";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
