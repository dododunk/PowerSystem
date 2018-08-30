using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_85 : iForm
	{
		private IContainer components = null;
		private TextBox textBox1;
		private TextBox textBox5;
		private Label label1;
		private Label label6;
		public AFN04_85()
		{
			this.InitializeComponent();
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			text += base.OperaSend(this.textBox5.Text.PadLeft(4, '0'), 2, "BCD");
			text += base.OperaSend(this.textBox1.Text.PadLeft(4, '0'), 2, "BIN");
			this.Data = text;
		}
		public override void SetText()
		{
			if (!string.IsNullOrEmpty(this.Data))
			{
				string data = this.Data;
				this.textBox5.Text = base.OperaRec(data.Substring(0, 4), "BCD");
				this.textBox1.Text = base.OperaRec(data.Substring(4, 4), "BIN");
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
			this.label6 = new Label();
			this.label1 = new Label();
			this.textBox5 = new TextBox();
			this.textBox1 = new TextBox();
			base.SuspendLayout();
			this.label6.AutoSize = true;
			this.label6.Font = new Font("Arial", 9f);
			this.label6.Location = new Point(29, 27);
			this.label6.Name = "label6";
			this.label6.Size = new Size(89, 15);
			this.label6.TabIndex = 46;
			this.label6.Text = "行政区划码(A1)";
			this.label1.AutoSize = true;
			this.label1.Font = new Font("Arial", 9f);
			this.label1.Location = new Point(29, 64);
			this.label1.Name = "label1";
			this.label1.Size = new Size(77, 15);
			this.label1.TabIndex = 47;
			this.label1.Text = "终端地址(A2)";
			this.textBox5.Location = new Point(124, 26);
			this.textBox5.Name = "textBox5";
			this.textBox5.Size = new Size(128, 21);
			this.textBox5.TabIndex = 48;
			this.textBox1.Location = new Point(124, 63);
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new Size(128, 21);
			this.textBox1.TabIndex = 49;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(287, 114);
			base.Controls.Add(this.textBox1);
			base.Controls.Add(this.textBox5);
			base.Controls.Add(this.label1);
			base.Controls.Add(this.label6);
			base.Name = "AFN04_85";
			this.Text = "终端通讯参数";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
