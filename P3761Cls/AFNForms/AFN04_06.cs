using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_06 : iForm
	{
		private IContainer components = null;
		private TextBox textBox8;
		private Label label8;
		private TextBox textBox7;
		private TextBox textBox6;
		private Label label5;
		private TextBox textBox5;
		private Label label4;
		private Label label3;
		private TextBox textBox4;
		private Label label1;
		private TextBox textBox1;
		private Label label7;
		private Label label6;
		private TextBox textBox3;
		private TextBox textBox2;
		private Label label2;
		public AFN04_06()
		{
			this.InitializeComponent();
			base.HelpButton = true;
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			text = base.OperaSend(this.textBox1.Text, 2, "BIN");
			text += base.OperaSend(this.textBox2.Text, 2, "BIN");
			text += base.OperaSend(this.textBox3.Text, 2, "BIN");
			text += base.OperaSend(this.textBox4.Text, 2, "BIN");
			text += base.OperaSend(this.textBox5.Text, 2, "BIN");
			text += base.OperaSend(this.textBox6.Text, 2, "BIN");
			text += base.OperaSend(this.textBox7.Text, 2, "BIN");
			text += base.OperaSend(this.textBox8.Text, 2, "BIN");
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
					this.textBox1.Text = base.OperaRec(data.Substring(num, 4), "BIN");
					num += 4;
					this.textBox2.Text = base.OperaRec(data.Substring(num, 4), "BIN");
					num += 4;
					this.textBox3.Text = base.OperaRec(data.Substring(num, 4), "BIN");
					num += 4;
					this.textBox4.Text = base.OperaRec(data.Substring(num, 4), "BIN");
					num += 4;
					this.textBox5.Text = base.OperaRec(data.Substring(num, 4), "BIN");
					num += 4;
					this.textBox6.Text = base.OperaRec(data.Substring(num, 4), "BIN");
					num += 4;
					this.textBox7.Text = base.OperaRec(data.Substring(num, 4), "BIN");
					num += 4;
					this.textBox8.Text = base.OperaRec(data.Substring(num, 4), "BIN");
					num += 4;
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
			this.textBox1 = new TextBox();
			this.label6 = new Label();
			this.textBox2 = new TextBox();
			this.label2 = new Label();
			this.textBox3 = new TextBox();
			this.label1 = new Label();
			this.textBox4 = new TextBox();
			this.label3 = new Label();
			this.label4 = new Label();
			this.textBox5 = new TextBox();
			this.label5 = new Label();
			this.textBox6 = new TextBox();
			this.label7 = new Label();
			this.textBox7 = new TextBox();
			this.label8 = new Label();
			this.textBox8 = new TextBox();
			base.SuspendLayout();
			this.textBox1.Location = new Point(113, 21);
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new Size(147, 21);
			this.textBox1.TabIndex = 9;
			this.textBox1.Text = "0";
			this.label6.AutoSize = true;
			this.label6.Location = new Point(27, 24);
			this.label6.Name = "label6";
			this.label6.Size = new Size(71, 12);
			this.label6.TabIndex = 8;
			this.label6.Text = "终端组地址1";
			this.textBox2.Location = new Point(113, 48);
			this.textBox2.Name = "textBox2";
			this.textBox2.Size = new Size(147, 21);
			this.textBox2.TabIndex = 22;
			this.textBox2.Text = "0";
			this.label2.AutoSize = true;
			this.label2.Location = new Point(27, 51);
			this.label2.Name = "label2";
			this.label2.Size = new Size(71, 12);
			this.label2.TabIndex = 21;
			this.label2.Text = "终端组地址2";
			this.textBox3.Location = new Point(113, 75);
			this.textBox3.Name = "textBox3";
			this.textBox3.Size = new Size(147, 21);
			this.textBox3.TabIndex = 26;
			this.textBox3.Text = "0";
			this.label1.AutoSize = true;
			this.label1.Location = new Point(27, 105);
			this.label1.Name = "label1";
			this.label1.Size = new Size(71, 12);
			this.label1.TabIndex = 25;
			this.label1.Text = "终端组地址4";
			this.textBox4.Location = new Point(113, 102);
			this.textBox4.Name = "textBox4";
			this.textBox4.Size = new Size(147, 21);
			this.textBox4.TabIndex = 24;
			this.textBox4.Text = "0";
			this.label3.AutoSize = true;
			this.label3.Location = new Point(27, 78);
			this.label3.Name = "label3";
			this.label3.Size = new Size(71, 12);
			this.label3.TabIndex = 23;
			this.label3.Text = "终端组地址3";
			this.label4.AutoSize = true;
			this.label4.Location = new Point(27, 132);
			this.label4.Name = "label4";
			this.label4.Size = new Size(71, 12);
			this.label4.TabIndex = 28;
			this.label4.Text = "终端组地址5";
			this.textBox5.Location = new Point(113, 129);
			this.textBox5.Name = "textBox5";
			this.textBox5.Size = new Size(147, 21);
			this.textBox5.TabIndex = 27;
			this.textBox5.Text = "0";
			this.label5.AutoSize = true;
			this.label5.Location = new Point(27, 159);
			this.label5.Name = "label5";
			this.label5.Size = new Size(71, 12);
			this.label5.TabIndex = 30;
			this.label5.Text = "终端组地址6";
			this.textBox6.Location = new Point(113, 156);
			this.textBox6.Name = "textBox6";
			this.textBox6.Size = new Size(147, 21);
			this.textBox6.TabIndex = 29;
			this.textBox6.Text = "0";
			this.label7.AutoSize = true;
			this.label7.Location = new Point(27, 186);
			this.label7.Name = "label7";
			this.label7.Size = new Size(71, 12);
			this.label7.TabIndex = 32;
			this.label7.Text = "终端组地址7";
			this.textBox7.Location = new Point(113, 183);
			this.textBox7.Name = "textBox7";
			this.textBox7.Size = new Size(147, 21);
			this.textBox7.TabIndex = 31;
			this.textBox7.Text = "0";
			this.label8.AutoSize = true;
			this.label8.Location = new Point(27, 213);
			this.label8.Name = "label8";
			this.label8.Size = new Size(71, 12);
			this.label8.TabIndex = 34;
			this.label8.Text = "终端组地址8";
			this.textBox8.Location = new Point(113, 210);
			this.textBox8.Name = "textBox8";
			this.textBox8.Size = new Size(147, 21);
			this.textBox8.TabIndex = 33;
			this.textBox8.Text = "0";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(287, 255);
			base.Controls.Add(this.label8);
			base.Controls.Add(this.textBox8);
			base.Controls.Add(this.label7);
			base.Controls.Add(this.textBox7);
			base.Controls.Add(this.label5);
			base.Controls.Add(this.textBox6);
			base.Controls.Add(this.label4);
			base.Controls.Add(this.textBox5);
			base.Controls.Add(this.textBox3);
			base.Controls.Add(this.label1);
			base.Controls.Add(this.textBox4);
			base.Controls.Add(this.label3);
			base.Controls.Add(this.textBox2);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.textBox1);
			base.Controls.Add(this.label6);
			base.Name = "AFN04_06";
			this.Text = "终端组地址设置";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
