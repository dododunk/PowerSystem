using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
	public class AFN04_42 : iForm
	{
		private IContainer components = null;
		private Button button1;
		private Label label10;
		private TextBox textBox5;
		private Label label8;
		private TextBox textBox4;
		private Label label7;
		private Label label5;
		private Label label6;
		private TextBox textBox3;
		private CheckBox checkBox7;
		private CheckBox checkBox6;
		private CheckBox checkBox5;
		private CheckBox checkBox4;
		private Label label16;
		private CheckBox checkBox3;
		private CheckBox checkBox2;
		private CheckBox checkBox1;
		private Label label1;
		private TextBox textBox1;
		public AFN04_42()
		{
			this.InitializeComponent();
			base.HelpButton = true;
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			text += this.textBox1.Text;
			text += base.OperaSend(this.textBox3.Text + this.textBox4.Text, 2, "A19");
			text += base.OperaSend(this.textBox5.Text, 1, "BIN");
			int num = 0;
			num |= (this.checkBox1.Checked ? 1 : 0) << 1;
			num |= (this.checkBox2.Checked ? 1 : 0) << 2;
			num |= (this.checkBox3.Checked ? 1 : 0) << 3;
			num |= (this.checkBox4.Checked ? 1 : 0) << 4;
			num |= (this.checkBox5.Checked ? 1 : 0) << 5;
			num |= (this.checkBox6.Checked ? 1 : 0) << 6;
			text += (num | (this.checkBox7.Checked ? 1 : 0) << 7).ToString("X2");
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
					this.textBox1.Text = data.Substring(num, 4);
					num += 4;
					this.textBox4.Text = data.Substring(num, 2);
					num += 2;
					this.textBox3.Text = data.Substring(num, 2);
					num += 2;
					this.textBox5.Text = base.OperaRec(data.Substring(num, 2), "BIN");
					num += 2;
					int num2 = DataConvert.HexToInt(data.Substring(num, 2));
					this.checkBox1.Checked = ((num2 >> 1 & 1) == 1);
					this.checkBox2.Checked = ((num2 >> 2 & 1) == 1);
					this.checkBox3.Checked = ((num2 >> 3 & 1) == 1);
					this.checkBox4.Checked = ((num2 >> 4 & 1) == 1);
					this.checkBox5.Checked = ((num2 >> 5 & 1) == 1);
					this.checkBox6.Checked = ((num2 >> 6 & 1) == 1);
					this.checkBox7.Checked = ((num2 >> 7 & 1) == 1);
				}
			}
		}
		private void Button1Click(object sender, EventArgs e)
		{
			iForm iForm = new A2();
			iForm.Data = this.textBox1.Text;
			iForm.SetText();
			iForm.ShowDialog();
			this.textBox1.Text = iForm.Data;
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
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.label16 = new System.Windows.Forms.Label();
            this.checkBox2 = new System.Windows.Forms.CheckBox();
            this.checkBox3 = new System.Windows.Forms.CheckBox();
            this.checkBox4 = new System.Windows.Forms.CheckBox();
            this.checkBox5 = new System.Windows.Forms.CheckBox();
            this.checkBox6 = new System.Windows.Forms.CheckBox();
            this.checkBox7 = new System.Windows.Forms.CheckBox();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.textBox4 = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.textBox5 = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(92, 17);
            this.textBox1.Name = "textBox1";
            this.textBox1.ReadOnly = true;
            this.textBox1.Size = new System.Drawing.Size(110, 20);
            this.textBox1.TabIndex = 3;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(21, 21);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(67, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "厂休控定值";
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Location = new System.Drawing.Point(24, 127);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(38, 17);
            this.checkBox1.TabIndex = 14;
            this.checkBox1.Text = "一";
            this.checkBox1.UseVisualStyleBackColor = true;
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(21, 110);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(67, 13);
            this.label16.TabIndex = 31;
            this.label16.Text = "每周限电日";
            // 
            // checkBox2
            // 
            this.checkBox2.AutoSize = true;
            this.checkBox2.Location = new System.Drawing.Point(66, 127);
            this.checkBox2.Name = "checkBox2";
            this.checkBox2.Size = new System.Drawing.Size(38, 17);
            this.checkBox2.TabIndex = 34;
            this.checkBox2.Text = "二";
            this.checkBox2.UseVisualStyleBackColor = true;
            // 
            // checkBox3
            // 
            this.checkBox3.AutoSize = true;
            this.checkBox3.Location = new System.Drawing.Point(108, 127);
            this.checkBox3.Name = "checkBox3";
            this.checkBox3.Size = new System.Drawing.Size(38, 17);
            this.checkBox3.TabIndex = 35;
            this.checkBox3.Text = "三";
            this.checkBox3.UseVisualStyleBackColor = true;
            // 
            // checkBox4
            // 
            this.checkBox4.AutoSize = true;
            this.checkBox4.Location = new System.Drawing.Point(150, 127);
            this.checkBox4.Name = "checkBox4";
            this.checkBox4.Size = new System.Drawing.Size(38, 17);
            this.checkBox4.TabIndex = 36;
            this.checkBox4.Text = "四";
            this.checkBox4.UseVisualStyleBackColor = true;
            // 
            // checkBox5
            // 
            this.checkBox5.AutoSize = true;
            this.checkBox5.Location = new System.Drawing.Point(192, 127);
            this.checkBox5.Name = "checkBox5";
            this.checkBox5.Size = new System.Drawing.Size(38, 17);
            this.checkBox5.TabIndex = 37;
            this.checkBox5.Text = "五";
            this.checkBox5.UseVisualStyleBackColor = true;
            // 
            // checkBox6
            // 
            this.checkBox6.AutoSize = true;
            this.checkBox6.Location = new System.Drawing.Point(234, 127);
            this.checkBox6.Name = "checkBox6";
            this.checkBox6.Size = new System.Drawing.Size(38, 17);
            this.checkBox6.TabIndex = 38;
            this.checkBox6.Text = "六";
            this.checkBox6.UseVisualStyleBackColor = true;
            // 
            // checkBox7
            // 
            this.checkBox7.AutoSize = true;
            this.checkBox7.Location = new System.Drawing.Point(276, 127);
            this.checkBox7.Name = "checkBox7";
            this.checkBox7.Size = new System.Drawing.Size(38, 17);
            this.checkBox7.TabIndex = 39;
            this.checkBox7.Text = "七";
            this.checkBox7.UseVisualStyleBackColor = true;
            // 
            // textBox3
            // 
            this.textBox3.Location = new System.Drawing.Point(104, 44);
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(34, 20);
            this.textBox3.TabIndex = 58;
            this.textBox3.Text = "00";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(21, 48);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(79, 13);
            this.label6.TabIndex = 57;
            this.label6.Text = "限电起始时间";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(144, 48);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(19, 13);
            this.label5.TabIndex = 59;
            this.label5.Text = "时";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(207, 49);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(19, 13);
            this.label7.TabIndex = 61;
            this.label7.Text = "分";
            // 
            // textBox4
            // 
            this.textBox4.Location = new System.Drawing.Point(167, 45);
            this.textBox4.Name = "textBox4";
            this.textBox4.Size = new System.Drawing.Size(34, 20);
            this.textBox4.TabIndex = 60;
            this.textBox4.Text = "00";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(206, 75);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(28, 13);
            this.label8.TabIndex = 64;
            this.label8.Text = "0.5h";
            // 
            // textBox5
            // 
            this.textBox5.Location = new System.Drawing.Point(104, 72);
            this.textBox5.Name = "textBox5";
            this.textBox5.Size = new System.Drawing.Size(97, 20);
            this.textBox5.TabIndex = 63;
            this.textBox5.Text = "1";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(20, 76);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(79, 13);
            this.label10.TabIndex = 62;
            this.label10.Text = "限电延续时间";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(202, 16);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(16, 23);
            this.button1.TabIndex = 93;
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.Button1Click);
            // 
            // AFN04_42
            // 
            this.ClientSize = new System.Drawing.Size(329, 164);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.textBox5);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.textBox4);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.textBox3);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.checkBox7);
            this.Controls.Add(this.checkBox6);
            this.Controls.Add(this.checkBox5);
            this.Controls.Add(this.checkBox4);
            this.Controls.Add(this.checkBox3);
            this.Controls.Add(this.checkBox2);
            this.Controls.Add(this.label16);
            this.Controls.Add(this.checkBox1);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.label1);
            this.Name = "AFN04_42";
            this.Text = "厂休功控参数";
            this.ResumeLayout(false);
            this.PerformLayout();

		}
	}
}
