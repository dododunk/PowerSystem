using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_75 : iForm
	{
		private IContainer components = null;
		private Button button4;
		private Button button3;
		private Button button2;
		private Button button1;
		private Label label12;
		private Label label11;
		private Label label10;
		private TextBox textBox8;
		private TextBox textBox6;
		private Label label7;
		private TextBox textBox4;
		private Label label9;
		private Label label8;
		private TextBox textBox7;
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
		public AFN04_75()
		{
			this.InitializeComponent();
			base.HelpButton = true;
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			text += base.OperaSend(this.textBox3.Text, 2, "A7");
			text += base.OperaSend(this.textBox2.Text, 2, "A7");
			text += base.OperaSend(this.textBox5.Text, 2, "A7");
			text += base.OperaSend(this.textBox1.Text, 2, "A7");
			text += this.textBox6.Text;
			text += this.textBox4.Text;
			text += this.textBox7.Text;
			text += this.textBox8.Text;
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
					this.textBox3.Text = base.OperaRec(data.Substring(num, 4), "A7");
					num += 4;
					this.textBox2.Text = base.OperaRec(data.Substring(num, 4), "A7");
					num += 4;
					this.textBox5.Text = base.OperaRec(data.Substring(num, 4), "A7");
					num += 4;
					this.textBox1.Text = base.OperaRec(data.Substring(num, 4), "A7");
					num += 4;
					this.textBox6.Text = data.Substring(num, 4);
					num += 4;
					this.textBox4.Text = data.Substring(num, 4);
					num += 4;
					this.textBox7.Text = data.Substring(num, 4);
					num += 4;
					this.textBox8.Text = data.Substring(num, 4);
					num += 4;
				}
			}
		}
		private void Button1Click(object sender, EventArgs e)
		{
			iForm iForm = new A5();
			iForm.Data = this.textBox6.Text;
			iForm.SetText();
			iForm.ShowDialog();
			this.textBox6.Text = iForm.Data;
		}
		private void Button2Click(object sender, EventArgs e)
		{
			iForm iForm = new A5();
			iForm.Data = this.textBox7.Text;
			iForm.SetText();
			iForm.ShowDialog();
			this.textBox7.Text = iForm.Data;
		}
		private void Button3Click(object sender, EventArgs e)
		{
			iForm iForm = new A5();
			iForm.Data = this.textBox4.Text;
			iForm.SetText();
			iForm.ShowDialog();
			this.textBox4.Text = iForm.Data;
		}
		private void Button4Click(object sender, EventArgs e)
		{
			iForm iForm = new A5();
			iForm.Data = this.textBox8.Text;
			iForm.SetText();
			iForm.ShowDialog();
			this.textBox8.Text = iForm.Data;
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
			this.textBox4 = new TextBox();
			this.label7 = new Label();
			this.textBox6 = new TextBox();
			this.label9 = new Label();
			this.textBox7 = new TextBox();
			this.label8 = new Label();
			this.textBox8 = new TextBox();
			this.label10 = new Label();
			this.label11 = new Label();
			this.label12 = new Label();
			this.label5 = new Label();
			this.button1 = new Button();
			this.button2 = new Button();
			this.button3 = new Button();
			this.button4 = new Button();
			base.SuspendLayout();
			this.textBox3.Location = new Point(76, 22);
			this.textBox3.Name = "textBox3";
			this.textBox3.Size = new Size(58, 21);
			this.textBox3.TabIndex = 9;
			this.textBox3.Text = "0";
			this.label6.AutoSize = true;
			this.label6.Location = new Point(29, 25);
			this.label6.Name = "label6";
			this.label6.Size = new Size(41, 12);
			this.label6.TabIndex = 8;
			this.label6.Text = "过电压";
			this.textBox1.Location = new Point(263, 49);
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new Size(57, 21);
			this.textBox1.TabIndex = 24;
			this.textBox1.Text = "0";
			this.label1.AutoSize = true;
			this.label1.Location = new Point(180, 52);
			this.label1.Name = "label1";
			this.label1.Size = new Size(77, 12);
			this.label1.TabIndex = 23;
			this.label1.Text = "欠电压回差值";
			this.textBox2.Location = new Point(263, 22);
			this.textBox2.Name = "textBox2";
			this.textBox2.Size = new Size(57, 21);
			this.textBox2.TabIndex = 22;
			this.textBox2.Text = "0";
			this.label2.AutoSize = true;
			this.label2.Location = new Point(180, 25);
			this.label2.Name = "label2";
			this.label2.Size = new Size(77, 12);
			this.label2.TabIndex = 21;
			this.label2.Text = "过电压回差值";
			this.textBox5.Location = new Point(76, 49);
			this.textBox5.Name = "textBox5";
			this.textBox5.Size = new Size(58, 21);
			this.textBox5.TabIndex = 26;
			this.textBox5.Text = "0";
			this.label3.AutoSize = true;
			this.label3.Location = new Point(29, 52);
			this.label3.Name = "label3";
			this.label3.Size = new Size(41, 12);
			this.label3.TabIndex = 25;
			this.label3.Text = "欠电压";
			this.label4.AutoSize = true;
			this.label4.Location = new Point(140, 25);
			this.label4.Name = "label4";
			this.label4.Size = new Size(11, 12);
			this.label4.TabIndex = 39;
			this.label4.Text = "V";
			this.textBox4.Location = new Point(196, 147);
			this.textBox4.Name = "textBox4";
			this.textBox4.ReadOnly = true;
			this.textBox4.Size = new Size(124, 21);
			this.textBox4.TabIndex = 42;
			this.label7.AutoSize = true;
			this.label7.Location = new Point(29, 150);
			this.label7.Name = "label7";
			this.label7.Size = new Size(161, 12);
			this.label7.TabIndex = 41;
			this.label7.Text = "总畸变电流含有率越限回差值";
			this.textBox6.Location = new Point(160, 85);
			this.textBox6.Name = "textBox6";
			this.textBox6.ReadOnly = true;
			this.textBox6.Size = new Size(160, 21);
			this.textBox6.TabIndex = 44;
			this.label9.AutoSize = true;
			this.label9.Location = new Point(29, 88);
			this.label9.Name = "label9";
			this.label9.Size = new Size(125, 12);
			this.label9.TabIndex = 43;
			this.label9.Text = "总畸变电流含有率上限";
			this.textBox7.Location = new Point(160, 112);
			this.textBox7.Name = "textBox7";
			this.textBox7.ReadOnly = true;
			this.textBox7.Size = new Size(160, 21);
			this.textBox7.TabIndex = 48;
			this.label8.AutoSize = true;
			this.label8.Location = new Point(29, 115);
			this.label8.Name = "label8";
			this.label8.Size = new Size(125, 12);
			this.label8.TabIndex = 47;
			this.label8.Text = "总畸变电压含有率上限";
			this.textBox8.Location = new Point(196, 174);
			this.textBox8.Name = "textBox8";
			this.textBox8.ReadOnly = true;
			this.textBox8.Size = new Size(124, 21);
			this.textBox8.TabIndex = 46;
			this.label10.AutoSize = true;
			this.label10.Location = new Point(29, 177);
			this.label10.Name = "label10";
			this.label10.Size = new Size(161, 12);
			this.label10.TabIndex = 45;
			this.label10.Text = "总畸变电压含有率越限回差值";
			this.label11.AutoSize = true;
			this.label11.Location = new Point(326, 25);
			this.label11.Name = "label11";
			this.label11.Size = new Size(11, 12);
			this.label11.TabIndex = 49;
			this.label11.Text = "V";
			this.label12.AutoSize = true;
			this.label12.Location = new Point(140, 53);
			this.label12.Name = "label12";
			this.label12.Size = new Size(11, 12);
			this.label12.TabIndex = 50;
			this.label12.Text = "V";
			this.label5.AutoSize = true;
			this.label5.Location = new Point(326, 53);
			this.label5.Name = "label5";
			this.label5.Size = new Size(11, 12);
			this.label5.TabIndex = 51;
			this.label5.Text = "V";
			this.button1.Location = new Point(321, 83);
			this.button1.Name = "button1";
			this.button1.Size = new Size(16, 23);
			this.button1.TabIndex = 52;
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new EventHandler(this.Button1Click);
			this.button2.Location = new Point(321, 110);
			this.button2.Name = "button2";
			this.button2.Size = new Size(16, 23);
			this.button2.TabIndex = 53;
			this.button2.UseVisualStyleBackColor = true;
			this.button2.Click += new EventHandler(this.Button2Click);
			this.button3.Location = new Point(321, 145);
			this.button3.Name = "button3";
			this.button3.Size = new Size(16, 23);
			this.button3.TabIndex = 54;
			this.button3.UseVisualStyleBackColor = true;
			this.button3.Click += new EventHandler(this.Button3Click);
			this.button4.Location = new Point(321, 172);
			this.button4.Name = "button4";
			this.button4.Size = new Size(16, 23);
			this.button4.TabIndex = 55;
			this.button4.UseVisualStyleBackColor = true;
			this.button4.Click += new EventHandler(this.Button4Click);
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(367, 222);
			base.Controls.Add(this.button4);
			base.Controls.Add(this.button3);
			base.Controls.Add(this.button2);
			base.Controls.Add(this.button1);
			base.Controls.Add(this.label5);
			base.Controls.Add(this.label12);
			base.Controls.Add(this.label11);
			base.Controls.Add(this.textBox7);
			base.Controls.Add(this.label8);
			base.Controls.Add(this.textBox8);
			base.Controls.Add(this.label10);
			base.Controls.Add(this.textBox6);
			base.Controls.Add(this.label9);
			base.Controls.Add(this.textBox4);
			base.Controls.Add(this.label7);
			base.Controls.Add(this.label4);
			base.Controls.Add(this.textBox5);
			base.Controls.Add(this.label3);
			base.Controls.Add(this.textBox1);
			base.Controls.Add(this.label1);
			base.Controls.Add(this.textBox2);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.textBox3);
			base.Controls.Add(this.label6);
			base.Name = "AFN04_75";
			this.Text = "电容器保护参数";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
