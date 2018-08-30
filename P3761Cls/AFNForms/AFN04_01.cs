using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
	public class AFN04_01 : iForm
	{
		private IContainer components = null;
		private Label label10;
		private TextBox textBox5;
		private Label label8;
		private CheckBox checkBox3;
		private CheckBox checkBox2;
		private CheckBox checkBox1;
		private Label label9;
		private ComboBox textBox4;
		private Label label7;
		private Label label6;
		private TextBox textBox3;
		private Label label5;
		private Label label4;
		private TextBox textBox2;
		private Label label3;
		private Label label2;
		private Label label1;
		private TextBox textBox1;
		public AFN04_01()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			checked
			{
				for (int i = 0; i <= 3; i++)
				{
					this.textBox4.Items.Add(i.ToString());
				}
				this.textBox4.SelectedIndex = 0;
			}
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			text = int.Parse(this.textBox1.Text).ToString("X2");
			text += int.Parse(this.textBox2.Text).ToString("X2");
			string val = ((int)ushort.Parse(this.textBox3.Text) | int.Parse(this.textBox4.Text) << 12).ToString("X4");
			text += DataConvert.ReverseStr(val);
			int num = 0;
			int num2 = this.checkBox1.Checked ? 1 : 0;
			num |= num2;
			num2 = (this.checkBox2.Checked ? 1 : 0);
			num |= num2 << 1;
			num2 = (this.checkBox3.Checked ? 1 : 0);
			text += (num | num2 << 2).ToString("X2");
			text += int.Parse(this.textBox5.Text).ToString("X2");
			this.Data = text;
		}
		public override void SetText()
		{
			if (!string.IsNullOrEmpty(this.Data))
			{
				string data = this.Data;
				this.textBox1.Text = DataConvert.HexToInt(data.Substring(0, 2)).ToString();
				this.textBox2.Text = DataConvert.HexToInt(data.Substring(2, 2)).ToString();
				int num = DataConvert.HexToInt(data.Substring(6, 2) + data.Substring(4, 2));
				this.textBox3.Text = (num & 4095).ToString();
				this.textBox4.Text = (num >> 12 & 3).ToString();
				byte b = byte.Parse(data.Substring(8, 2));
				this.checkBox1.Checked = ((b & 1) == 1);
				this.checkBox2.Checked = ((b & 2) == 2);
				this.checkBox3.Checked = ((b & 4) == 4);
				this.textBox5.Text = DataConvert.HexToInt(data.Substring(10, 2)).ToString();
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
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.checkBox2 = new System.Windows.Forms.CheckBox();
            this.checkBox3 = new System.Windows.Forms.CheckBox();
            this.label8 = new System.Windows.Forms.Label();
            this.textBox5 = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.textBox4 = new System.Windows.Forms.ComboBox();
            this.SuspendLayout();
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(234, 22);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(114, 20);
            this.textBox1.TabIndex = 3;
            this.textBox1.Text = "0";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(97, 25);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(137, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "终端数传机延时时间RTS";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(354, 25);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(32, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "20ms";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(354, 54);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(23, 13);
            this.label3.TabIndex = 7;
            this.label3.Text = "min";
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(234, 51);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(114, 20);
            this.textBox2.TabIndex = 6;
            this.textBox2.Text = "0";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(20, 54);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(211, 13);
            this.label4.TabIndex = 5;
            this.label4.Text = "终端作为启动站允许发送传输延时时间";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(283, 82);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(19, 13);
            this.label5.TabIndex = 10;
            this.label5.Text = "秒";
            // 
            // textBox3
            // 
            this.textBox3.Location = new System.Drawing.Point(234, 78);
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(43, 20);
            this.textBox3.TabIndex = 9;
            this.textBox3.Text = "0";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(20, 81);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(187, 13);
            this.label6.TabIndex = 8;
            this.label6.Text = "从动站响应的超时时间和重发次数";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(354, 81);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(19, 13);
            this.label7.TabIndex = 12;
            this.label7.Text = "次";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(20, 108);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(204, 13);
            this.label9.TabIndex = 13;
            this.label9.Text = "需要主站确认的通信服务(CON=1)标志";
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Location = new System.Drawing.Point(234, 108);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(116, 17);
            this.checkBox1.TabIndex = 14;
            this.checkBox1.Text = "1类数据自动上报";
            this.checkBox1.UseVisualStyleBackColor = true;
            // 
            // checkBox2
            // 
            this.checkBox2.AutoSize = true;
            this.checkBox2.Location = new System.Drawing.Point(234, 130);
            this.checkBox2.Name = "checkBox2";
            this.checkBox2.Size = new System.Drawing.Size(116, 17);
            this.checkBox2.TabIndex = 15;
            this.checkBox2.Text = "2类数据自动上报";
            this.checkBox2.UseVisualStyleBackColor = true;
            // 
            // checkBox3
            // 
            this.checkBox3.AutoSize = true;
            this.checkBox3.Location = new System.Drawing.Point(234, 152);
            this.checkBox3.Name = "checkBox3";
            this.checkBox3.Size = new System.Drawing.Size(116, 17);
            this.checkBox3.TabIndex = 16;
            this.checkBox3.Text = "3类数据自动上报";
            this.checkBox3.UseVisualStyleBackColor = true;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(354, 178);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(23, 13);
            this.label8.TabIndex = 19;
            this.label8.Text = "min";
            // 
            // textBox5
            // 
            this.textBox5.Location = new System.Drawing.Point(234, 174);
            this.textBox5.Name = "textBox5";
            this.textBox5.Size = new System.Drawing.Size(114, 20);
            this.textBox5.TabIndex = 18;
            this.textBox5.Text = "0";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(170, 178);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(55, 13);
            this.label10.TabIndex = 17;
            this.label10.Text = "心跳周期";
            // 
            // textBox4
            // 
            this.textBox4.FormattingEnabled = true;
            this.textBox4.Location = new System.Drawing.Point(306, 78);
            this.textBox4.Name = "textBox4";
            this.textBox4.Size = new System.Drawing.Size(42, 21);
            this.textBox4.TabIndex = 20;
            // 
            // AFN04_01
            // 
            this.ClientSize = new System.Drawing.Size(401, 223);
            this.Controls.Add(this.textBox4);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.textBox5);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.checkBox3);
            this.Controls.Add(this.checkBox2);
            this.Controls.Add(this.checkBox1);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.textBox3);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.textBox2);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.label1);
            this.Name = "AFN04_01";
            this.Text = "终端上行通信口通信参数设置";
            this.ResumeLayout(false);
            this.PerformLayout();

		}
	}
}
