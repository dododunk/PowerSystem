using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_59 : iForm
	{
		private IContainer components = null;
		private Label label4;
		private Label label3;
		private TextBox textBox5;
		private Label label6;
		private TextBox textBox3;
		private Label label5;
		private TextBox textBox2;
		private Label label2;
		private Label label1;
		private TextBox textBox1;
		public AFN04_59()
		{
			this.InitializeComponent();
			base.HelpButton = true;
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			text += base.OperaSend(this.textBox3.Text, 1, "A22");
			text += base.OperaSend(this.textBox2.Text, 1, "A22");
			text += base.OperaSend(this.textBox5.Text, 1, "BIN");
			text += base.OperaSend(this.textBox1.Text, 1, "BIN");
			this.Data = text;
		}
		public override void SetText()
		{
			checked
			{
				if (!string.IsNullOrEmpty(this.Data))
				{
					string data = this.Data;
					int num = 0;
					this.textBox3.Text = base.OperaRec(data.Substring(num, 2), "A22");
					num += 2;
					this.textBox2.Text = base.OperaRec(data.Substring(num, 2), "A22");
					num += 2;
					this.textBox5.Text = base.OperaRec(data.Substring(num, 2), "BIN");
					num += 2;
					this.textBox1.Text = base.OperaRec(data.Substring(num, 2), "BIN");
					num += 2;
				}
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
			this.textBox1 = new TextBox();
			this.label1 = new Label();
			this.textBox2 = new TextBox();
			this.label2 = new Label();
			this.textBox5 = new TextBox();
			this.label3 = new Label();
			this.label4 = new Label();
			this.label5 = new Label();
			base.SuspendLayout();
			this.textBox3.Location = new Point(120, 25);
			this.textBox3.Name = "textBox3";
			this.textBox3.Size = new Size(150, 21);
			this.textBox3.TabIndex = 9;
			this.textBox3.Text = "0";
			this.label6.AutoSize = true;
			this.label6.Location = new Point(25, 28);
			this.label6.Name = "label6";
			this.label6.Size = new Size(89, 12);
			this.label6.TabIndex = 8;
			this.label6.Text = "电能量超差阈值";
			this.textBox1.Location = new Point(120, 106);
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new Size(109, 21);
			this.textBox1.TabIndex = 24;
			this.textBox1.Text = "0";
			this.label1.AutoSize = true;
			this.label1.Location = new Point(25, 109);
			this.label1.Name = "label1";
			this.label1.Size = new Size(89, 12);
			this.label1.TabIndex = 23;
			this.label1.Text = "电能表校时阈值";
			this.textBox2.Location = new Point(120, 52);
			this.textBox2.Name = "textBox2";
			this.textBox2.Size = new Size(150, 21);
			this.textBox2.TabIndex = 22;
			this.textBox2.Text = "0";
			this.label2.AutoSize = true;
			this.label2.Location = new Point(25, 55);
			this.label2.Name = "label2";
			this.label2.Size = new Size(89, 12);
			this.label2.TabIndex = 21;
			this.label2.Text = "电能表飞走阈值";
			this.textBox5.Location = new Point(120, 79);
			this.textBox5.Name = "textBox5";
			this.textBox5.Size = new Size(109, 21);
			this.textBox5.TabIndex = 26;
			this.textBox5.Text = "0";
			this.label3.AutoSize = true;
			this.label3.Location = new Point(25, 82);
			this.label3.Name = "label3";
			this.label3.Size = new Size(89, 12);
			this.label3.TabIndex = 25;
			this.label3.Text = "电能表停走阈值";
			this.label4.AutoSize = true;
			this.label4.Location = new Point(235, 82);
			this.label4.Name = "label4";
			this.label4.Size = new Size(35, 12);
			this.label4.TabIndex = 27;
			this.label4.Text = "15min";
			this.label5.AutoSize = true;
			this.label5.Location = new Point(235, 109);
			this.label5.Name = "label5";
			this.label5.Size = new Size(23, 12);
			this.label5.TabIndex = 28;
			this.label5.Text = "min";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(297, 161);
			base.Controls.Add(this.label5);
			base.Controls.Add(this.label4);
			base.Controls.Add(this.textBox5);
			base.Controls.Add(this.label3);
			base.Controls.Add(this.textBox1);
			base.Controls.Add(this.label1);
			base.Controls.Add(this.textBox2);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.textBox3);
			base.Controls.Add(this.label6);
			base.Name = "AFN04_59";
			this.Text = "电能表异常判别阈值设定";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
