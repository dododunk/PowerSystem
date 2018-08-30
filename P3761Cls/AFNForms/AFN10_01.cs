using System;
using System.ComponentModel;
using System.Drawing;
using System.Globalization;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
	public class AFN10_01 : iForm
	{
		private iForm giForm;
		private IContainer components = null;
		private Button button1;
		private TextBox textBox4;
		private GroupBox groupBox2;
		private Label label4;
		private Label label3;
		private TextBox textBox3;
		private ComboBox comboBox1;
		private Label label2;
		private TextBox textBox2;
		private Label label11;
		private ComboBox comboBox3;
		private CheckBox checkBox1;
		private CheckBox checkBox2;
		private CheckBox checkBox3;
		private Label label12;
		private ComboBox comboBox4;
		private GroupBox groupBox1;
		private Label label1;
		private ComboBox textBox1;
		public AFN10_01()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			checked
			{
				for (int i = 1; i <= 31; i++)
				{
					this.textBox1.Items.Add(i.ToString());
				}
				this.textBox1.SelectedIndex = 0;
				this.comboBox1.SelectedIndex = 0;
				this.comboBox3.SelectedIndex = 3;
				this.comboBox4.SelectedIndex = 3;
			}
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			text += base.OperaSend(this.textBox1.Text, 1, "BIN");
			int num = 0;
			num |= this.comboBox3.SelectedIndex << 5;
			num |= (this.checkBox1.Checked ? 1 : 0) << 4;
			num |= (this.checkBox2.Checked ? 1 : 0) << 3;
			num |= (this.checkBox3.Checked ? 1 : 0) << 2;
			text += (num | this.comboBox4.SelectedIndex).ToString("X2");
			num = 0;
			num |= this.comboBox1.SelectedIndex << 5;
			text += (num | int.Parse(this.textBox2.Text)).ToString("X2");
			text += base.OperaSend(this.textBox3.Text, 1, "BIN");
			text += DataConvert.ReverseStr((this.textBox4.Text.Trim().Length / 2).ToString("X4"));
			text += this.textBox4.Text.Trim();
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
					this.textBox1.Text = base.OperaRec(data.Substring(num, 2), "BIN");
					num += 2;
					int num2 = DataConvert.HexToInt(data.Substring(num, 2));
					num += 2;
					this.comboBox3.SelectedIndex = num2 >> 5;
					this.checkBox1.Checked = ((num2 >> 4 & 1) == 1);
					this.checkBox2.Checked = ((num2 >> 3 & 1) == 1);
					this.checkBox3.Checked = ((num2 >> 2 & 1) == 1);
					this.comboBox4.SelectedIndex = (num2 & 3);
					num2 = DataConvert.HexToInt(data.Substring(num, 2));
					num += 2;
					this.comboBox1.SelectedIndex = num2 >> 7;
					this.textBox2.Text = (num2 & 127).ToString();
					this.textBox3.Text = base.OperaRec(data.Substring(num, 2), "BIN");
					num += 2;
					num += 4;
					this.textBox4.Text = data.Substring(num);
				}
			}
		}
		private void Button1Click(object sender, EventArgs e)
		{
			this.giForm = new AFN10_01_Data();
			this.giForm.Data = this.textBox4.Text;
			this.NeedSave = true;
			this.giForm.SetText();
			this.giForm.ShowDialog();
			this.textBox4.Text = this.giForm.Data;
			this.giForm = null;
		}
		private string DataClass(string strRecvData)
		{
			byte[] array = new byte[strRecvData.Length / 2];
			checked
			{
				for (int i = 0; i < array.Length; i++)
				{
					array[i] = byte.Parse(strRecvData.Substring(i * 2, 2), NumberStyles.HexNumber);
				}
				int j;
				for (j = 0; j < array.Length; j++)
				{
					if (array[j] == 104)
					{
						break;
					}
				}
				int num = (int)array[j + 9];
				return strRecvData.Substring((10 + j) * 2, num * 2);
			}
		}
		private string DataReversal(string strValue)
		{
			string hexChar = string.Empty;
			string text = string.Empty;
			checked
			{
				for (int i = 0; i < strValue.Length / 2; i++)
				{
					hexChar = strValue.Substring(i * 2, 2);
					text = ((byte)(DataConvert.HexToInt(hexChar) - 51)).ToString("X2") + text;
				}
				return text;
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
			this.textBox1 = new ComboBox();
			this.label1 = new Label();
			this.groupBox1 = new GroupBox();
			this.comboBox4 = new ComboBox();
			this.label12 = new Label();
			this.checkBox3 = new CheckBox();
			this.checkBox2 = new CheckBox();
			this.checkBox1 = new CheckBox();
			this.comboBox3 = new ComboBox();
			this.label11 = new Label();
			this.textBox2 = new TextBox();
			this.label2 = new Label();
			this.comboBox1 = new ComboBox();
			this.textBox3 = new TextBox();
			this.label3 = new Label();
			this.label4 = new Label();
			this.groupBox2 = new GroupBox();
			this.button1 = new Button();
			this.textBox4 = new TextBox();
			this.groupBox1.SuspendLayout();
			this.groupBox2.SuspendLayout();
			base.SuspendLayout();
			this.textBox1.DropDownStyle = ComboBoxStyle.DropDownList;
			this.textBox1.FormattingEnabled = true;
			this.textBox1.Location = new Point(113, 12);
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new Size(59, 20);
			this.textBox1.TabIndex = 25;
			this.label1.AutoSize = true;
			this.label1.Location = new Point(18, 15);
			this.label1.Name = "label1";
			this.label1.Size = new Size(89, 12);
			this.label1.TabIndex = 24;
			this.label1.Text = "终端通信端口号";
			this.groupBox1.Controls.Add(this.comboBox4);
			this.groupBox1.Controls.Add(this.label12);
			this.groupBox1.Controls.Add(this.checkBox3);
			this.groupBox1.Controls.Add(this.checkBox2);
			this.groupBox1.Controls.Add(this.checkBox1);
			this.groupBox1.Controls.Add(this.comboBox3);
			this.groupBox1.Controls.Add(this.label11);
			this.groupBox1.Location = new Point(12, 38);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new Size(507, 49);
			this.groupBox1.TabIndex = 56;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "透明转发通信控制字";
			this.comboBox4.DropDownStyle = ComboBoxStyle.DropDownList;
			this.comboBox4.FormattingEnabled = true;
			this.comboBox4.Items.AddRange(new object[]
			{
				"5",
				"6",
				"7",
				"8"
			});
			this.comboBox4.Location = new Point(425, 19);
			this.comboBox4.Name = "comboBox4";
			this.comboBox4.Size = new Size(64, 20);
			this.comboBox4.TabIndex = 59;
			this.label12.AutoSize = true;
			this.label12.Font = new Font("Arial", 9f);
			this.label12.Location = new Point(388, 22);
			this.label12.Name = "label12";
			this.label12.Size = new Size(31, 15);
			this.label12.TabIndex = 58;
			this.label12.Text = "位数";
			this.checkBox3.AutoSize = true;
			this.checkBox3.Location = new Point(316, 22);
			this.checkBox3.Name = "checkBox3";
			this.checkBox3.Size = new Size(60, 16);
			this.checkBox3.TabIndex = 57;
			this.checkBox3.Text = "奇校验";
			this.checkBox3.UseVisualStyleBackColor = true;
			this.checkBox2.AutoSize = true;
			this.checkBox2.Checked = true;
			this.checkBox2.CheckState = CheckState.Checked;
			this.checkBox2.Location = new Point(250, 22);
			this.checkBox2.Name = "checkBox2";
			this.checkBox2.Size = new Size(60, 16);
			this.checkBox2.TabIndex = 56;
			this.checkBox2.Text = "有校验";
			this.checkBox2.UseVisualStyleBackColor = true;
			this.checkBox1.AutoSize = true;
			this.checkBox1.Location = new Point(178, 22);
			this.checkBox1.Name = "checkBox1";
			this.checkBox1.Size = new Size(66, 16);
			this.checkBox1.TabIndex = 55;
			this.checkBox1.Text = "2停止位";
			this.checkBox1.UseVisualStyleBackColor = true;
			this.comboBox3.DropDownStyle = ComboBoxStyle.DropDownList;
			this.comboBox3.FormattingEnabled = true;
			this.comboBox3.Items.AddRange(new object[]
			{
				"300",
				"600",
				"1200",
				"2400",
				"4800",
				"7200",
				"9600",
				"19200",
				""
			});
			this.comboBox3.Location = new Point(85, 18);
			this.comboBox3.Name = "comboBox3";
			this.comboBox3.Size = new Size(75, 20);
			this.comboBox3.TabIndex = 54;
			this.label11.AutoSize = true;
			this.label11.Font = new Font("Arial", 9f);
			this.label11.Location = new Point(12, 20);
			this.label11.Name = "label11";
			this.label11.Size = new Size(67, 15);
			this.label11.TabIndex = 53;
			this.label11.Text = "Baud(bit/s)";
			this.textBox2.Location = new Point(197, 97);
			this.textBox2.Name = "textBox2";
			this.textBox2.Size = new Size(45, 21);
			this.textBox2.TabIndex = 58;
			this.textBox2.Text = "20";
			this.label2.AutoSize = true;
			this.label2.Location = new Point(18, 100);
			this.label2.Name = "label2";
			this.label2.Size = new Size(173, 12);
			this.label2.TabIndex = 57;
			this.label2.Text = "透明转发接收等待报文超时时间";
			this.comboBox1.DropDownStyle = ComboBoxStyle.DropDownList;
			this.comboBox1.FormattingEnabled = true;
			this.comboBox1.Items.AddRange(new object[]
			{
				"10ms",
				"1s"
			});
			this.comboBox1.Location = new Point(247, 97);
			this.comboBox1.Name = "comboBox1";
			this.comboBox1.Size = new Size(49, 20);
			this.comboBox1.TabIndex = 59;
			this.textBox3.Location = new Point(197, 124);
			this.textBox3.Name = "textBox3";
			this.textBox3.Size = new Size(45, 21);
			this.textBox3.TabIndex = 61;
			this.textBox3.Text = "20";
			this.label3.AutoSize = true;
			this.label3.Location = new Point(18, 127);
			this.label3.Name = "label3";
			this.label3.Size = new Size(173, 12);
			this.label3.TabIndex = 60;
			this.label3.Text = "透明转发接收等待字节超时时间";
			this.label4.AutoSize = true;
			this.label4.Location = new Point(247, 128);
			this.label4.Name = "label4";
			this.label4.Size = new Size(29, 12);
			this.label4.TabIndex = 62;
			this.label4.Text = "10ms";
			this.groupBox2.Controls.Add(this.button1);
			this.groupBox2.Controls.Add(this.textBox4);
			this.groupBox2.Location = new Point(13, 152);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new Size(507, 229);
			this.groupBox2.TabIndex = 63;
			this.groupBox2.TabStop = false;
			this.groupBox2.Text = "透明转发内容";
			this.button1.Font = new Font("宋体", 9f, FontStyle.Regular, GraphicsUnit.Point, 0);
			this.button1.Location = new Point(451, 0);
			this.button1.Name = "button1";
			this.button1.Size = new Size(45, 19);
			this.button1.TabIndex = 63;
			this.button1.Text = "645↓";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new EventHandler(this.Button1Click);
			this.textBox4.Anchor = (AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right);
			this.textBox4.Location = new Point(11, 20);
			this.textBox4.Multiline = true;
			this.textBox4.Name = "textBox4";
			this.textBox4.ScrollBars = ScrollBars.Both;
			this.textBox4.Size = new Size(485, 198);
			this.textBox4.TabIndex = 62;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(533, 392);
			base.Controls.Add(this.groupBox2);
			base.Controls.Add(this.label4);
			base.Controls.Add(this.textBox3);
			base.Controls.Add(this.label3);
			base.Controls.Add(this.comboBox1);
			base.Controls.Add(this.textBox2);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.groupBox1);
			base.Controls.Add(this.textBox1);
			base.Controls.Add(this.label1);
			base.Name = "AFN10_01";
			this.Text = "透明转发";
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			this.groupBox2.ResumeLayout(false);
			this.groupBox2.PerformLayout();
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
