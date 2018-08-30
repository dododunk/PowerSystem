using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_74 : iForm
	{
		private IContainer components = null;
		private Button button3;
		private Label label9;
		private Label label8;
		private Label label7;
		private TextBox textBox5;
		private Label label2;
		private TextBox textBox4;
		private Label label1;
		private TextBox textBox1;
		private Label label4;
		private Label label5;
		private Label label14;
		private Label label6;
		private TextBox textBox3;
		private TextBox textBox2;
		public AFN04_74()
		{
			this.InitializeComponent();
			base.HelpButton = true;
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			text += this.textBox3.Text;
			text += base.OperaSend(this.textBox1.Text, 3, "A23");
			text += base.OperaSend(this.textBox2.Text, 3, "A23");
			text += base.OperaSend(this.textBox4.Text, 1, "BIN");
			text += base.OperaSend(this.textBox5.Text, 1, "BIN");
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
					this.textBox3.Text = data.Substring(num, 4);
					num += 4;
					this.textBox1.Text = base.OperaRec(data.Substring(num, 6), "A23");
					num += 6;
					this.textBox2.Text = base.OperaRec(data.Substring(num, 6), "A23");
					num += 6;
					this.textBox4.Text = base.OperaRec(data.Substring(num, 2), "BIN");
					num += 2;
					this.textBox5.Text = base.OperaRec(data.Substring(num, 2), "BIN");
					num += 2;
				}
			}
		}
		private void Button3Click(object sender, EventArgs e)
		{
			iForm iForm = new A5();
			iForm.Data = this.textBox3.Text;
			iForm.SetText();
			iForm.ShowDialog();
			this.textBox3.Text = iForm.Data;
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
			this.textBox2 = new TextBox();
			this.label14 = new Label();
			this.label5 = new Label();
			this.label4 = new Label();
			this.textBox1 = new TextBox();
			this.label1 = new Label();
			this.textBox4 = new TextBox();
			this.label2 = new Label();
			this.textBox5 = new TextBox();
			this.label6 = new Label();
			this.label7 = new Label();
			this.label8 = new Label();
			this.label9 = new Label();
			this.button3 = new Button();
			base.SuspendLayout();
			this.textBox3.Location = new Point(142, 22);
			this.textBox3.Name = "textBox3";
			this.textBox3.ReadOnly = true;
			this.textBox3.Size = new Size(92, 21);
			this.textBox3.TabIndex = 9;
			this.textBox2.Location = new Point(142, 76);
			this.textBox2.Name = "textBox2";
			this.textBox2.Size = new Size(92, 21);
			this.textBox2.TabIndex = 22;
			this.textBox2.Text = "0";
			this.label14.AutoSize = true;
			this.label14.Font = new Font("Arial", 9f);
			this.label14.Location = new Point(33, 77);
			this.label14.Name = "label14";
			this.label14.Size = new Size(103, 15);
			this.label14.TabIndex = 40;
			this.label14.Text = "切除无功功率门限";
			this.label5.AutoSize = true;
			this.label5.Font = new Font("Arial", 9f);
			this.label5.Location = new Point(33, 50);
			this.label5.Name = "label5";
			this.label5.Size = new Size(103, 15);
			this.label5.TabIndex = 47;
			this.label5.Text = "投入无功功率门限";
			this.label4.AutoSize = true;
			this.label4.Font = new Font("Arial", 9f);
			this.label4.Location = new Point(57, 23);
			this.label4.Name = "label4";
			this.label4.Size = new Size(79, 15);
			this.label4.TabIndex = 48;
			this.label4.Text = "目标功率因数";
			this.textBox1.Location = new Point(142, 49);
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new Size(92, 21);
			this.textBox1.TabIndex = 49;
			this.textBox1.Text = "0";
			this.label1.AutoSize = true;
			this.label1.Font = new Font("Arial", 9f);
			this.label1.Location = new Point(81, 104);
			this.label1.Name = "label1";
			this.label1.Size = new Size(55, 15);
			this.label1.TabIndex = 51;
			this.label1.Text = "延时时间";
			this.textBox4.Location = new Point(142, 103);
			this.textBox4.Name = "textBox4";
			this.textBox4.Size = new Size(92, 21);
			this.textBox4.TabIndex = 50;
			this.textBox4.Text = "0";
			this.label2.AutoSize = true;
			this.label2.Font = new Font("Arial", 9f);
			this.label2.Location = new Point(57, 131);
			this.label2.Name = "label2";
			this.label2.Size = new Size(79, 15);
			this.label2.TabIndex = 53;
			this.label2.Text = "动作时间间隔";
			this.textBox5.Location = new Point(142, 130);
			this.textBox5.Name = "textBox5";
			this.textBox5.Size = new Size(92, 21);
			this.textBox5.TabIndex = 52;
			this.textBox5.Text = "0";
			this.label6.AutoSize = true;
			this.label6.Font = new Font("Arial", 9f);
			this.label6.Location = new Point(236, 52);
			this.label6.Name = "label6";
			this.label6.Size = new Size(29, 15);
			this.label6.TabIndex = 55;
			this.label6.Text = "kvar";
			this.label7.AutoSize = true;
			this.label7.Font = new Font("Arial", 9f);
			this.label7.Location = new Point(236, 78);
			this.label7.Name = "label7";
			this.label7.Size = new Size(29, 15);
			this.label7.TabIndex = 56;
			this.label7.Text = "kvar";
			this.label8.AutoSize = true;
			this.label8.Font = new Font("Arial", 9f);
			this.label8.Location = new Point(236, 106);
			this.label8.Name = "label8";
			this.label8.Size = new Size(27, 15);
			this.label8.TabIndex = 57;
			this.label8.Text = "sec";
			this.label9.AutoSize = true;
			this.label9.Font = new Font("Arial", 9f);
			this.label9.Location = new Point(236, 133);
			this.label9.Name = "label9";
			this.label9.Size = new Size(28, 15);
			this.label9.TabIndex = 58;
			this.label9.Text = "min";
			this.button3.Location = new Point(235, 21);
			this.button3.Name = "button3";
			this.button3.Size = new Size(16, 23);
			this.button3.TabIndex = 59;
			this.button3.UseVisualStyleBackColor = true;
			this.button3.Click += new EventHandler(this.Button3Click);
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(296, 181);
			base.Controls.Add(this.button3);
			base.Controls.Add(this.label9);
			base.Controls.Add(this.label8);
			base.Controls.Add(this.label7);
			base.Controls.Add(this.label6);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.textBox5);
			base.Controls.Add(this.label1);
			base.Controls.Add(this.textBox4);
			base.Controls.Add(this.textBox1);
			base.Controls.Add(this.label14);
			base.Controls.Add(this.label5);
			base.Controls.Add(this.label4);
			base.Controls.Add(this.textBox2);
			base.Controls.Add(this.textBox3);
			base.Name = "AFN04_74";
			this.Text = "电容器投切运行参数";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
