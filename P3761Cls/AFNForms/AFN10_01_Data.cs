using System;
using System.ComponentModel;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN10_01_Data : iForm
	{
		private DLT645 dlt = new DLT645();
		//ivate PubFuncHelper pf = new PubFuncHelper();
		private IContainer components = null;
		private Label label8;
		private TextBox textBox3;
		private Label label6;
		private Label label2;
		private ComboBox comboBox9;
		private Label label3;
		private ComboBox comboBox2;
		private Label label5;
		private ComboBox comboBox3;
		private ComboBox comboBox5;
		private CheckBox checkBox1;
		private RadioButton radioButton1;
		private RadioButton radioButton2;
		public AFN10_01_Data()
		{
			this.InitializeComponent();
			this.NeedSave = true;
		}
		protected override void GetText()
		{
			this.Data = "";
			this.dlt.MeterCortrol = this.comboBox2.Text.Trim();
			if (this.radioButton1.Checked)
			{
				this.dlt.IsRead = true;
			}
			else
			{
				this.dlt.IsRead = false;
			}
			this.dlt.MeterDataLength = 0;
			this.dlt.MeterIdentifier = this.comboBox3.Text.Trim();
			this.dlt.MeterAddress = this.comboBox9.Text.Trim();
			this.dlt.MeterPassWord = this.comboBox5.Text.Trim();
			this.dlt.MeterDataFormat = "";
			if (this.radioButton2.Checked)
			{
				if (this.checkBox1.Checked)
				{
					string meterSendDataInfo = PubFuncHelper.ASCIIToHexStr(this.textBox3.Text.Trim());
					this.dlt.MeterSendDataInfo = meterSendDataInfo;
				}
				else
				{
					this.dlt.MeterSendDataInfo = this.textBox3.Text.Trim();
				}
				this.dlt.OperatorID = ((this.comboBox3.Text.Trim().Length == 8) ? "00000000" : "");
			}
			else
			{
				this.dlt.MeterSendDataInfo = "";
				this.dlt.OperatorID = "";
			}
			this.Data = this.ByteToHexStr(this.dlt.Get645Frame());
		}
		public string ByteToHexStr(byte[] data)
		{
			StringBuilder stringBuilder = new StringBuilder(checked(data.Length * 3));
			for (int i = 0; i < data.Length; i++)
			{
				byte value = data[i];
				stringBuilder.Append(Convert.ToString(value, 16).PadLeft(2, '0'));
			}
			return stringBuilder.ToString().Trim().ToUpper();
		}
		public override void SetText()
		{
			if (!string.IsNullOrEmpty(this.Data))
			{
				string data = this.Data;
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
			this.radioButton2 = new RadioButton();
			this.radioButton1 = new RadioButton();
			this.checkBox1 = new CheckBox();
			this.comboBox5 = new ComboBox();
			this.comboBox3 = new ComboBox();
			this.label5 = new Label();
			this.comboBox2 = new ComboBox();
			this.label3 = new Label();
			this.comboBox9 = new ComboBox();
			this.label2 = new Label();
			this.label6 = new Label();
			this.textBox3 = new TextBox();
			this.label8 = new Label();
			base.SuspendLayout();
			this.radioButton2.AutoSize = true;
			this.radioButton2.BackColor = Color.Transparent;
			this.radioButton2.ForeColor = Color.Black;
			this.radioButton2.Location = new Point(359, 13);
			this.radioButton2.Name = "radioButton2";
			this.radioButton2.Size = new Size(37, 17);
			this.radioButton2.TabIndex = 126;
			this.radioButton2.Text = "写";
			this.radioButton2.UseVisualStyleBackColor = false;
			this.radioButton1.AutoSize = true;
			this.radioButton1.BackColor = Color.Transparent;
			this.radioButton1.Checked = true;
			this.radioButton1.ForeColor = Color.Black;
			this.radioButton1.Location = new Point(316, 13);
			this.radioButton1.Name = "radioButton1";
			this.radioButton1.Size = new Size(37, 17);
			this.radioButton1.TabIndex = 125;
			this.radioButton1.TabStop = true;
			this.radioButton1.Text = "读";
			this.radioButton1.UseVisualStyleBackColor = false;
			this.checkBox1.AutoSize = true;
			this.checkBox1.BackColor = Color.Transparent;
			this.checkBox1.Location = new Point(400, 14);
			this.checkBox1.Name = "checkBox1";
			this.checkBox1.Size = new Size(53, 17);
			this.checkBox1.TabIndex = 127;
			this.checkBox1.Text = "ASCII";
			this.checkBox1.UseVisualStyleBackColor = false;
			this.comboBox5.Enabled = false;
			this.comboBox5.FormattingEnabled = true;
			this.comboBox5.Items.AddRange(new object[]
			{
				"",
				"00000000",
				"00000002",
				"00000098"
			});
			this.comboBox5.Location = new Point(356, 40);
			this.comboBox5.Name = "comboBox5";
			this.comboBox5.Size = new Size(94, 21);
			this.comboBox5.TabIndex = 135;
			this.comboBox3.FormattingEnabled = true;
			this.comboBox3.Items.AddRange(new object[]
			{
				"",
				"00000000",
				"901F"
			});
			this.comboBox3.Location = new Point(188, 40);
			this.comboBox3.Name = "comboBox3";
			this.comboBox3.Size = new Size(99, 21);
			this.comboBox3.TabIndex = 133;
			this.comboBox3.Text = "00000000";
			this.label5.AutoSize = true;
			this.label5.BackColor = Color.Transparent;
			this.label5.Location = new Point(297, 44);
			this.label5.Name = "label5";
			this.label5.Size = new Size(55, 13);
			this.label5.TabIndex = 134;
			this.label5.Text = "编程密码";
			this.comboBox2.FormattingEnabled = true;
			this.comboBox2.Items.AddRange(new object[]
			{
				"01",
				"03",
				"04",
				"08",
				"0A",
				"11",
				"14",
				"16",
				"9A"
			});
			this.comboBox2.Location = new Point(67, 40);
			this.comboBox2.Name = "comboBox2";
			this.comboBox2.Size = new Size(50, 21);
			this.comboBox2.TabIndex = 132;
			this.comboBox2.Text = "11";
			this.label3.AutoSize = true;
			this.label3.BackColor = Color.Transparent;
			this.label3.ForeColor = Color.FromArgb(192, 0, 0);
			this.label3.Location = new Point(131, 44);
			this.label3.Name = "label3";
			this.label3.Size = new Size(55, 13);
			this.label3.TabIndex = 131;
			this.label3.Text = "标识编码";
			this.comboBox9.FormattingEnabled = true;
			this.comboBox9.Items.AddRange(new object[]
			{
				"",
				"999999999999",
				"AAAAAAAAAAAA"
			});
			this.comboBox9.Location = new Point(67, 12);
			this.comboBox9.Name = "comboBox9";
			this.comboBox9.Size = new Size(217, 21);
			this.comboBox9.TabIndex = 129;
			this.comboBox9.Text = "AAAAAAAAAAAA";
			this.label2.AutoSize = true;
			this.label2.BackColor = Color.Transparent;
			this.label2.Location = new Point(12, 43);
			this.label2.Name = "label2";
			this.label2.Size = new Size(43, 13);
			this.label2.TabIndex = 130;
			this.label2.Text = "控制码";
			this.label6.AutoSize = true;
			this.label6.BackColor = Color.Transparent;
			this.label6.Location = new Point(12, 15);
			this.label6.Name = "label6";
			this.label6.Size = new Size(55, 13);
			this.label6.TabIndex = 128;
			this.label6.Text = "电表地址";
			this.textBox3.BackColor = Color.White;
			this.textBox3.Location = new Point(67, 68);
			this.textBox3.Multiline = true;
			this.textBox3.Name = "textBox3";
			this.textBox3.ReadOnly = true;
			this.textBox3.ScrollBars = ScrollBars.Both;
			this.textBox3.Size = new Size(383, 150);
			this.textBox3.TabIndex = 137;
			this.label8.AutoSize = true;
			this.label8.BackColor = Color.Transparent;
			this.label8.Location = new Point(12, 70);
			this.label8.Name = "label8";
			this.label8.Size = new Size(55, 13);
			this.label8.TabIndex = 136;
			this.label8.Text = "发送数据";
			base.AutoScaleDimensions = new SizeF(6f, 13f);
			
			base.ClientSize = new Size(461, 229);
			base.Controls.Add(this.textBox3);
			base.Controls.Add(this.label8);
			base.Controls.Add(this.comboBox5);
			base.Controls.Add(this.comboBox3);
			base.Controls.Add(this.label5);
			base.Controls.Add(this.comboBox2);
			base.Controls.Add(this.label3);
			base.Controls.Add(this.comboBox9);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.label6);
			base.Controls.Add(this.radioButton2);
			base.Controls.Add(this.radioButton1);
			base.Controls.Add(this.checkBox1);
			this.Font = new Font("Microsoft Sans Serif", 8.25f);
			base.Name = "AFN10_01_Data";
			this.Text = "DLT645 数据帧生成";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
