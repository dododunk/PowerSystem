using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
	public class AFN04_08 : iForm
	{
		private string[] times = new string[24];
		private CheckBox[] cb = new CheckBox[24];
		private IContainer components = null;
		private Label label16;
		private TextBox textBox6;
		private Label label15;
		private ComboBox comboBox3;
		private ComboBox comboBox2;
		private ComboBox comboBox1;
		private Label label14;
		private Label label13;
		private Label label12;
		private Label label11;
		private Label label9;
		private Label label4;
		private TextBox textBox2;
		private Label label3;
		private Label label2;
		private Label label1;
		private TextBox textBox1;
		private CheckBox checkBox1;
		public AFN04_08()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			this.times = this.TimePeriods2.Split(new char[]
			{
				'~'
			});
			this.comboBox1.SelectedIndex = 0;
			this.comboBox2.SelectedIndex = 0;
			this.comboBox3.SelectedIndex = 0;
			int num = 0;
			int num2 = 200;
			checked
			{
				for (int i = 0; i < 24; i++)
				{
					this.cb[i] = new CheckBox();
					this.cb[i].Text = this.times[i];
					this.cb[i].Parent = this;
					this.cb[i].AutoSize = true;
					num += 25;
					if (i % 4 == 0)
					{
						num2 += 17;
					}
					if (i % 4 != 0)
					{
						num += 70;
					}
					else
					{
						num = 65;
					}
					this.cb[i].Top = num2;
					this.cb[i].Left = num;
				}
			}
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			byte b = 0;
			checked
			{
				b = (byte)((int)b | this.comboBox1.SelectedIndex << 7);
				b = (byte)((int)b | this.comboBox2.SelectedIndex << 4);
				text = ((byte)((int)b | this.comboBox3.SelectedIndex + 1)).ToString("X2");
				text += DataConvert.ReverseStr(int.Parse(this.textBox1.Text).ToString("X4"));
				text += int.Parse(this.textBox6.Text).ToString("X2");
				text += int.Parse(this.textBox2.Text).ToString("X2");
				long num = 0L;
				for (int i = 0; i < 24; i++)
				{
					num |= (this.cb[i].Checked ? 1L : 0L) << (i & 31);
				}
				text += DataConvert.ReverseStr(num.ToString("X6"));
				this.Data = text;
			}
		}
		public override void SetText()
		{
			checked
			{
				if (!string.IsNullOrEmpty(this.Data))
				{
					string data = this.Data;
					int num = DataConvert.HexToInt(data.Substring(0, 2));
					this.comboBox1.SelectedIndex = num >> 7;
					this.comboBox2.SelectedIndex = (num >> 4 & 3);
					this.comboBox3.SelectedIndex = (num & 2);
					this.textBox1.Text = DataConvert.HexToInt(DataConvert.ReverseStr(data.Substring(2, 4), 2)).ToString();
					this.textBox6.Text = DataConvert.HexToInt(data.Substring(6, 2)).ToString();
					this.textBox2.Text = DataConvert.HexToInt(data.Substring(8, 2)).ToString();
					long num2 = DataConvert.HexToLong(DataConvert.ReverseStr(data.Substring(10, 6)));
					for (int i = 0; i < 24; i++)
					{
						this.cb[i].Checked = ((num2 >> i & 1L) == 1L);
					}
				}
			}
		}
		private void checkBox1_CheckStateChanged(object sender, EventArgs e)
		{
			if (this.checkBox1.Checked)
			{
				base.SetCheck(true);
			}
			else
			{
				base.SetCheck(false);
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
            this.label9 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.comboBox2 = new System.Windows.Forms.ComboBox();
            this.comboBox3 = new System.Windows.Forms.ComboBox();
            this.label15 = new System.Windows.Forms.Label();
            this.textBox6 = new System.Windows.Forms.TextBox();
            this.label16 = new System.Windows.Forms.Label();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(223, 105);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(134, 20);
            this.textBox1.TabIndex = 3;
            this.textBox1.Text = "0";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(32, 108);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(187, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "永久在线、时段在线模式重拨间隔";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(361, 109);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(67, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "秒 (1-65535)";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(361, 163);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(55, 13);
            this.label3.TabIndex = 7;
            this.label3.Text = "分 (0-255)";
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(223, 159);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(134, 20);
            this.textBox2.TabIndex = 6;
            this.textBox2.Text = "0";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(9, 162);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(211, 13);
            this.label4.TabIndex = 5;
            this.label4.Text = "被动激活模式连续无通信自动断线时间";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(12, 194);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(175, 13);
            this.label9.TabIndex = 13;
            this.label9.Text = "时段在线模式允许在线时段标志";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(23, 22);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(58, 13);
            this.label11.TabIndex = 21;
            this.label11.Text = "工作模式:";
            // 
            // label12
            // 
            this.label12.Font = new System.Drawing.Font("Tahoma", 9F);
            this.label12.Location = new System.Drawing.Point(95, 72);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(53, 15);
            this.label12.TabIndex = 25;
            this.label12.Text = "D1-D0位";
            // 
            // label13
            // 
            this.label13.Font = new System.Drawing.Font("Tahoma", 9F);
            this.label13.Location = new System.Drawing.Point(95, 46);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(53, 15);
            this.label13.TabIndex = 26;
            this.label13.Text = "D5-D4位";
            // 
            // label14
            // 
            this.label14.Font = new System.Drawing.Font("Tahoma", 9F);
            this.label14.Location = new System.Drawing.Point(95, 19);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(53, 15);
            this.label14.TabIndex = 27;
            this.label14.Text = "D7位";
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "TCP",
            "UDP"});
            this.comboBox1.Location = new System.Drawing.Point(154, 18);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(203, 21);
            this.comboBox1.TabIndex = 28;
            // 
            // comboBox2
            // 
            this.comboBox2.FormattingEnabled = true;
            this.comboBox2.Items.AddRange(new object[] {
            "混合模式",
            "客户机模式",
            "服务器模式"});
            this.comboBox2.Location = new System.Drawing.Point(154, 44);
            this.comboBox2.Name = "comboBox2";
            this.comboBox2.Size = new System.Drawing.Size(203, 21);
            this.comboBox2.TabIndex = 29;
            // 
            // comboBox3
            // 
            this.comboBox3.FormattingEnabled = true;
            this.comboBox3.Items.AddRange(new object[] {
            "永久在线模式",
            "被动激活模式",
            "时段在线模式"});
            this.comboBox3.Location = new System.Drawing.Point(154, 70);
            this.comboBox3.Name = "comboBox3";
            this.comboBox3.Size = new System.Drawing.Size(203, 21);
            this.comboBox3.TabIndex = 30;
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(361, 136);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(55, 13);
            this.label15.TabIndex = 33;
            this.label15.Text = "次 (1-255)";
            // 
            // textBox6
            // 
            this.textBox6.Location = new System.Drawing.Point(223, 132);
            this.textBox6.Name = "textBox6";
            this.textBox6.Size = new System.Drawing.Size(134, 20);
            this.textBox6.TabIndex = 32;
            this.textBox6.Text = "0";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(92, 135);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(127, 13);
            this.label16.TabIndex = 31;
            this.label16.Text = "被动激活模式重拨次数";
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Location = new System.Drawing.Point(191, 193);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(50, 17);
            this.checkBox1.TabIndex = 34;
            this.checkBox1.Text = "全选";
            this.checkBox1.UseVisualStyleBackColor = true;
            this.checkBox1.CheckStateChanged += new System.EventHandler(this.checkBox1_CheckStateChanged);
            // 
            // AFN04_08
            // 
            this.ClientSize = new System.Drawing.Size(453, 333);
            this.Controls.Add(this.checkBox1);
            this.Controls.Add(this.label15);
            this.Controls.Add(this.textBox6);
            this.Controls.Add(this.label16);
            this.Controls.Add(this.comboBox3);
            this.Controls.Add(this.comboBox2);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.label14);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.textBox2);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.label1);
            this.Name = "AFN04_08";
            this.Text = "终端上行通信工作方式";
            this.ResumeLayout(false);
            this.PerformLayout();

		}
	}
}
