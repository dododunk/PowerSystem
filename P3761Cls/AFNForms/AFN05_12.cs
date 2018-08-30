using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN05_12 : iForm
	{
		private IContainer components = null;
		private Button button1;
		private Label label16;
		private Label label15;
		private Label label13;
		private Label label12;
		private Label label11;
		private Label label10;
		private TextBox textBox8;
		private Label label9;
		private Label label8;
		private TextBox textBox7;
		private Label label7;
		private Label label4;
		private TextBox textBox6;
		private Label label3;
		private ComboBox textBox5;
		private TextBox textBox4;
		private Label label6;
		private ComboBox textBox3;
		private Label label5;
		private TextBox textBox2;
		private Label label2;
		private Label label1;
		private TextBox textBox1;
		public AFN05_12()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			checked
			{
				for (int i = 0; i <= 60; i++)
				{
					this.textBox3.Items.Add(i.ToString());
				}
				for (int i = 5; i <= 60; i++)
				{
					this.textBox5.Items.Add(i.ToString());
				}
				this.textBox3.SelectedIndex = 0;
				this.textBox5.SelectedIndex = 0;
			}
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			text += base.OperaSend(this.textBox3.Text, 1, "BIN");
			text += this.textBox2.Text;
			text += base.OperaSend(this.textBox5.Text, 1, "BIN");
			text += base.OperaSend(this.textBox7.Text, 1, "BIN");
			text += base.OperaSend(this.textBox1.Text, 1, "BIN");
			text += base.OperaSend(this.textBox4.Text, 1, "BIN");
			text += base.OperaSend(this.textBox6.Text, 1, "BIN");
			text += base.OperaSend(this.textBox8.Text, 1, "BIN");
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
					this.textBox3.Text = base.OperaRec(data.Substring(num, 2), "BIN");
					num += 2;
					this.textBox2.Text = data.Substring(num, 2);
					num += 2;
					this.textBox5.Text = base.OperaRec(data.Substring(num, 2), "BIN");
					num += 2;
					this.textBox7.Text = base.OperaRec(data.Substring(num, 2), "BIN");
					num += 2;
					this.textBox1.Text = base.OperaRec(data.Substring(num, 2), "BIN");
					num += 2;
					this.textBox4.Text = base.OperaRec(data.Substring(num, 2), "BIN");
					num += 2;
					this.textBox6.Text = base.OperaRec(data.Substring(num, 2), "BIN");
					num += 2;
					this.textBox8.Text = base.OperaRec(data.Substring(num, 2), "BIN");
					num += 2;
				}
			}
		}
		private void Button1Click(object sender, EventArgs e)
		{
			iForm iForm = new A4();
			iForm.Data = this.textBox2.Text;
			iForm.SetText();
			iForm.ShowDialog();
			this.textBox2.Text = iForm.Data;
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
			this.textBox2 = new TextBox();
			this.label2 = new Label();
			this.label3 = new Label();
			this.label7 = new Label();
			this.textBox7 = new TextBox();
			this.label8 = new Label();
			this.label13 = new Label();
			this.label15 = new Label();
			this.label16 = new Label();
			this.label4 = new Label();
			this.textBox4 = new TextBox();
			this.label5 = new Label();
			this.label9 = new Label();
			this.textBox6 = new TextBox();
			this.label10 = new Label();
			this.label11 = new Label();
			this.textBox8 = new TextBox();
			this.label12 = new Label();
			this.button1 = new Button();
			this.textBox3 = new ComboBox();
			this.textBox5 = new ComboBox();
			base.SuspendLayout();
			this.label6.AutoSize = true;
			this.label6.Location = new Point(32, 23);
			this.label6.Name = "label6";
			this.label6.Size = new Size(161, 12);
			this.label6.TabIndex = 8;
			this.label6.Text = "当前功率下浮控定值滑差时间";
			this.textBox1.Location = new Point(202, 128);
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new Size(70, 21);
			this.textBox1.TabIndex = 24;
			this.textBox1.Text = "0";
			this.label1.AutoSize = true;
			this.label1.Location = new Point(32, 131);
			this.label1.Name = "label1";
			this.label1.Size = new Size(167, 12);
			this.label1.TabIndex = 23;
			this.label1.Text = "当前功率下浮控第1轮告警时间";
			this.textBox2.Location = new Point(202, 47);
			this.textBox2.Name = "textBox2";
			this.textBox2.ReadOnly = true;
			this.textBox2.Size = new Size(70, 21);
			this.textBox2.TabIndex = 22;
			this.label2.AutoSize = true;
			this.label2.Location = new Point(32, 50);
			this.label2.Name = "label2";
			this.label2.Size = new Size(161, 12);
			this.label2.TabIndex = 21;
			this.label2.Text = "当前功率下浮控定值浮动系数";
			this.label3.AutoSize = true;
			this.label3.Location = new Point(32, 77);
			this.label3.Name = "label3";
			this.label3.Size = new Size(173, 12);
			this.label3.TabIndex = 25;
			this.label3.Text = "控后总加有功功率冻结延时时间";
			this.label7.AutoSize = true;
			this.label7.Location = new Point(278, 133);
			this.label7.Name = "label7";
			this.label7.Size = new Size(23, 12);
			this.label7.TabIndex = 29;
			this.label7.Text = "min";
			this.textBox7.Location = new Point(202, 101);
			this.textBox7.Name = "textBox7";
			this.textBox7.Size = new Size(70, 21);
			this.textBox7.TabIndex = 31;
			this.textBox7.Text = "0";
			this.label8.AutoSize = true;
			this.label8.Location = new Point(32, 105);
			this.label8.Name = "label8";
			this.label8.Size = new Size(149, 12);
			this.label8.TabIndex = 30;
			this.label8.Text = "当前功率下浮控的控制时间";
			this.label13.AutoSize = true;
			this.label13.Location = new Point(278, 23);
			this.label13.Name = "label13";
			this.label13.Size = new Size(23, 12);
			this.label13.TabIndex = 39;
			this.label13.Text = "min";
			this.label15.AutoSize = true;
			this.label15.Location = new Point(278, 78);
			this.label15.Name = "label15";
			this.label15.Size = new Size(23, 12);
			this.label15.TabIndex = 55;
			this.label15.Text = "min";
			this.label16.AutoSize = true;
			this.label16.Location = new Point(278, 106);
			this.label16.Name = "label16";
			this.label16.Size = new Size(29, 12);
			this.label16.TabIndex = 56;
			this.label16.Text = "0.5h";
			this.label4.AutoSize = true;
			this.label4.Location = new Point(278, 160);
			this.label4.Name = "label4";
			this.label4.Size = new Size(23, 12);
			this.label4.TabIndex = 59;
			this.label4.Text = "min";
			this.textBox4.Location = new Point(202, 155);
			this.textBox4.Name = "textBox4";
			this.textBox4.Size = new Size(70, 21);
			this.textBox4.TabIndex = 58;
			this.textBox4.Text = "0";
			this.label5.AutoSize = true;
			this.label5.Location = new Point(32, 159);
			this.label5.Name = "label5";
			this.label5.Size = new Size(167, 12);
			this.label5.TabIndex = 57;
			this.label5.Text = "当前功率下浮控第2轮告警时间";
			this.label9.AutoSize = true;
			this.label9.Location = new Point(278, 187);
			this.label9.Name = "label9";
			this.label9.Size = new Size(23, 12);
			this.label9.TabIndex = 62;
			this.label9.Text = "min";
			this.textBox6.Location = new Point(202, 182);
			this.textBox6.Name = "textBox6";
			this.textBox6.Size = new Size(70, 21);
			this.textBox6.TabIndex = 61;
			this.textBox6.Text = "0";
			this.label10.AutoSize = true;
			this.label10.Location = new Point(32, 186);
			this.label10.Name = "label10";
			this.label10.Size = new Size(167, 12);
			this.label10.TabIndex = 60;
			this.label10.Text = "当前功率下浮控第3轮告警时间";
			this.label11.AutoSize = true;
			this.label11.Location = new Point(278, 214);
			this.label11.Name = "label11";
			this.label11.Size = new Size(23, 12);
			this.label11.TabIndex = 65;
			this.label11.Text = "min";
			this.textBox8.Location = new Point(202, 209);
			this.textBox8.Name = "textBox8";
			this.textBox8.Size = new Size(70, 21);
			this.textBox8.TabIndex = 64;
			this.textBox8.Text = "0";
			this.label12.AutoSize = true;
			this.label12.Location = new Point(32, 213);
			this.label12.Name = "label12";
			this.label12.Size = new Size(167, 12);
			this.label12.TabIndex = 63;
			this.label12.Text = "当前功率下浮控第4轮告警时间";
			this.button1.Location = new Point(273, 46);
			this.button1.Name = "button1";
			this.button1.Size = new Size(16, 23);
			this.button1.TabIndex = 94;
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new EventHandler(this.Button1Click);
			this.textBox3.DropDownStyle = ComboBoxStyle.DropDownList;
			this.textBox3.FormattingEnabled = true;
			this.textBox3.Location = new Point(202, 19);
			this.textBox3.Name = "textBox3";
			this.textBox3.Size = new Size(70, 20);
			this.textBox3.TabIndex = 95;
			this.textBox5.DropDownStyle = ComboBoxStyle.DropDownList;
			this.textBox5.FormattingEnabled = true;
			this.textBox5.Location = new Point(209, 74);
			this.textBox5.Name = "textBox5";
			this.textBox5.Size = new Size(63, 20);
			this.textBox5.TabIndex = 96;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(329, 256);
			base.Controls.Add(this.textBox5);
			base.Controls.Add(this.textBox3);
			base.Controls.Add(this.button1);
			base.Controls.Add(this.label11);
			base.Controls.Add(this.textBox8);
			base.Controls.Add(this.label12);
			base.Controls.Add(this.label9);
			base.Controls.Add(this.textBox6);
			base.Controls.Add(this.label10);
			base.Controls.Add(this.label4);
			base.Controls.Add(this.textBox4);
			base.Controls.Add(this.label5);
			base.Controls.Add(this.label16);
			base.Controls.Add(this.label15);
			base.Controls.Add(this.label13);
			base.Controls.Add(this.textBox7);
			base.Controls.Add(this.label8);
			base.Controls.Add(this.label7);
			base.Controls.Add(this.label3);
			base.Controls.Add(this.textBox1);
			base.Controls.Add(this.label1);
			base.Controls.Add(this.textBox2);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.label6);
			base.Name = "AFN05_12";
			this.Text = "当前功率下浮控投入";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
