using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_58 : iForm
	{
		private IContainer components = null;
		private Label label1;
		private TextBox textBox1;
		private Label label6;
		public AFN04_58()
		{
			this.InitializeComponent();
			base.HelpButton = true;
		}
		protected override void GetText()
		{
			this.Data = "";
			string data = string.Empty;
			data = base.OperaSend(this.textBox1.Text, 1, "BIN");
			this.Data = data;
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
			this.label6 = new Label();
			this.textBox1 = new TextBox();
			this.label1 = new Label();
			base.SuspendLayout();
			this.label6.AutoSize = true;
			this.label6.Font = new Font("Arial", 9f);
			this.label6.Location = new Point(22, 32);
			this.label6.Name = "label6";
			this.label6.Size = new Size(151, 15);
			this.label6.TabIndex = 46;
			this.label6.Text = "允许与主站连续无通信时间";
			this.textBox1.Location = new Point(179, 29);
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new Size(50, 21);
			this.textBox1.TabIndex = 47;
			this.textBox1.Text = "0";
			this.label1.AutoSize = true;
			this.label1.Font = new Font("Arial", 9f);
			this.label1.Location = new Point(232, 32);
			this.label1.Name = "label1";
			this.label1.Size = new Size(14, 15);
			this.label1.TabIndex = 48;
			this.label1.Text = "h";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(274, 85);
			base.Controls.Add(this.label1);
			base.Controls.Add(this.textBox1);
			base.Controls.Add(this.label6);
			base.Name = "AFN04_58";
			this.Text = "终端自动保电参数";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
