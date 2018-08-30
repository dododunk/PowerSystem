using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
	public class AFN04_07 : iForm
	{
		private IContainer components = null;
		private ComboBox comboBox2;
		private ComboBox comboBox1;
		private Label label12;
		private TextBox textBox10;
		private Label label11;
		private TextBox textBox9;
		private Label label10;
		private TextBox textBox8;
		private Label label8;
		private TextBox textBox7;
		private Label label4;
		private Label label3;
		private TextBox textBox5;
		private TextBox textBox4;
		private Label label6;
		private TextBox textBox3;
		private Label label5;
		private TextBox textBox2;
		private Label label2;
		private Label label1;
		public AFN04_07()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			this.comboBox1.SelectedIndex = 0;
			this.comboBox2.SelectedIndex = 0;
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			text += DataConvert.IpToHexStr(this.textBox3.Text);
			text += DataConvert.IpToHexStr(this.textBox2.Text);
			text += DataConvert.IpToHexStr(this.textBox5.Text);
			text += this.comboBox1.SelectedIndex.ToString("X2");
			text += DataConvert.IpToHexStr(this.textBox7.Text);
			text += DataConvert.ReverseStr(int.Parse(this.textBox4.Text).ToString("X4"));
			text += this.comboBox2.SelectedIndex.ToString("X2");
			text += this.textBox8.Text.Trim().Length.ToString("X2");
			text += DataConvert.ReverseStr(DataConvert.ASCIIToHexStr(this.textBox8.Text.Trim()));
			text += this.textBox9.Text.Trim().Length.ToString("X2");
            text += DataConvert.ReverseStr(DataConvert.ASCIIToHexStr(this.textBox9.Text.Trim()));
			text += DataConvert.ReverseStr(int.Parse(this.textBox10.Text).ToString("X4"));
			this.Data = text;
		}
		public override void SetText()
		{
			checked
			{
				if (!string.IsNullOrEmpty(this.Data))
				{
					string data = this.Data;
					this.textBox3.Text = DataConvert.HexStrToIp(DataConvert.ReverseStr(data.Substring(0, 8), 2));
					this.textBox2.Text = DataConvert.HexStrToIp(DataConvert.ReverseStr(data.Substring(8, 8), 2));
					this.textBox5.Text = DataConvert.HexStrToIp(DataConvert.ReverseStr(data.Substring(16, 8), 2));
					this.comboBox1.SelectedIndex = DataConvert.HexToInt(data.Substring(24, 2));
					this.textBox7.Text = DataConvert.HexStrToIp(DataConvert.ReverseStr(data.Substring(26, 8), 2));
					this.textBox4.Text = base.OperaRec(data.Substring(34, 4), "BIN");
					this.comboBox2.SelectedIndex = DataConvert.HexToInt(data.Substring(38, 2));
					int num = 40;
					int num2 = DataConvert.HexToInt(data.Substring(num, 2));
					num += 2;
					this.textBox8.Text = DataConvert.HexStrToASCII(DataConvert.ReverseStr(data.Substring(num, 2 * num2)));
					num += 2 * num2;
					int num3 = DataConvert.HexToInt(data.Substring(num, 2));
					num += 2;
					this.textBox9.Text = DataConvert.HexStrToASCII(DataConvert.ReverseStr(data.Substring(num, 2 * num3), 2));
					num += 2 * num3;
					this.textBox10.Text = base.OperaRec(data.Substring(num, 4), "BIN");
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
			this.label5 = new Label();
			this.textBox3 = new TextBox();
			this.label6 = new Label();
			this.textBox4 = new TextBox();
			this.label1 = new Label();
			this.textBox2 = new TextBox();
			this.label2 = new Label();
			this.textBox5 = new TextBox();
			this.label3 = new Label();
			this.label4 = new Label();
			this.textBox7 = new TextBox();
			this.label8 = new Label();
			this.textBox8 = new TextBox();
			this.label10 = new Label();
			this.textBox9 = new TextBox();
			this.label11 = new Label();
			this.textBox10 = new TextBox();
			this.label12 = new Label();
			this.comboBox1 = new ComboBox();
			this.comboBox2 = new ComboBox();
			base.SuspendLayout();
			this.label5.AutoSize = true;
			this.label5.Location = new Point(219, 78);
			this.label5.Name = "label5";
			this.label5.Size = new Size(89, 12);
			this.label5.TabIndex = 10;
			this.label5.Text = "代理服务器端口";
			this.textBox3.Location = new Point(112, 21);
			this.textBox3.Name = "textBox3";
			this.textBox3.Size = new Size(100, 21);
			this.textBox3.TabIndex = 9;
			this.textBox3.Text = "0.0.0.0";
			this.label6.AutoSize = true;
			this.label6.Location = new Point(41, 24);
			this.label6.Name = "label6";
			this.label6.Size = new Size(65, 12);
			this.label6.TabIndex = 8;
			this.label6.Text = "终端IP地址";
			this.textBox4.Location = new Point(314, 75);
			this.textBox4.Name = "textBox4";
			this.textBox4.Size = new Size(88, 21);
			this.textBox4.TabIndex = 11;
			this.textBox4.Text = "0";
			this.label1.AutoSize = true;
			this.label1.Location = new Point(17, 105);
			this.label1.Name = "label1";
			this.label1.Size = new Size(113, 12);
			this.label1.TabIndex = 23;
			this.label1.Text = "代理服务器连接方式";
			this.textBox2.Location = new Point(314, 21);
			this.textBox2.Name = "textBox2";
			this.textBox2.Size = new Size(88, 21);
			this.textBox2.TabIndex = 22;
			this.textBox2.Text = "255.255.255.0";
			this.label2.AutoSize = true;
			this.label2.Location = new Point(219, 24);
			this.label2.Name = "label2";
			this.label2.Size = new Size(77, 12);
			this.label2.TabIndex = 21;
			this.label2.Text = "子网掩码地址";
			this.textBox5.Location = new Point(112, 48);
			this.textBox5.Name = "textBox5";
			this.textBox5.Size = new Size(100, 21);
			this.textBox5.TabIndex = 26;
			this.textBox5.Text = "0.0.0.0";
			this.label3.AutoSize = true;
			this.label3.Location = new Point(53, 51);
			this.label3.Name = "label3";
			this.label3.Size = new Size(53, 12);
			this.label3.TabIndex = 25;
			this.label3.Text = "网关地址";
			this.label4.AutoSize = true;
			this.label4.Location = new Point(219, 51);
			this.label4.Name = "label4";
			this.label4.Size = new Size(53, 12);
			this.label4.TabIndex = 27;
			this.label4.Text = "代理类型";
			this.textBox7.Location = new Point(112, 75);
			this.textBox7.Name = "textBox7";
			this.textBox7.Size = new Size(100, 21);
			this.textBox7.TabIndex = 31;
			this.textBox7.Text = "0.0.0.0";
			this.label8.AutoSize = true;
			this.label8.Location = new Point(17, 79);
			this.label8.Name = "label8";
			this.label8.Size = new Size(89, 12);
			this.label8.TabIndex = 30;
			this.label8.Text = "代理服务器地址";
			this.textBox8.Location = new Point(112, 128);
			this.textBox8.Name = "textBox8";
			this.textBox8.Size = new Size(290, 21);
			this.textBox8.TabIndex = 34;
			this.label10.AutoSize = true;
			this.label10.Location = new Point(65, 131);
			this.label10.Name = "label10";
			this.label10.Size = new Size(41, 12);
			this.label10.TabIndex = 33;
			this.label10.Text = "用户名";
			this.textBox9.Location = new Point(112, 155);
			this.textBox9.Name = "textBox9";
			this.textBox9.Size = new Size(290, 21);
			this.textBox9.TabIndex = 36;
			this.label11.AutoSize = true;
			this.label11.Location = new Point(77, 158);
			this.label11.Name = "label11";
			this.label11.Size = new Size(29, 12);
			this.label11.TabIndex = 35;
			this.label11.Text = "密码";
			this.textBox10.Location = new Point(112, 182);
			this.textBox10.Name = "textBox10";
			this.textBox10.Size = new Size(100, 21);
			this.textBox10.TabIndex = 38;
			this.textBox10.Text = "0";
			this.label12.AutoSize = true;
			this.label12.Location = new Point(29, 185);
			this.label12.Name = "label12";
			this.label12.Size = new Size(77, 12);
			this.label12.TabIndex = 37;
			this.label12.Text = "终端侦听端口";
			this.comboBox1.DropDownStyle = ComboBoxStyle.DropDownList;
			this.comboBox1.FormattingEnabled = true;
			this.comboBox1.Items.AddRange(new object[]
			{
				"不使用代理",
				"http connect代理",
				"socks4代理",
				"socks5代理"
			});
			this.comboBox1.Location = new Point(278, 48);
			this.comboBox1.Name = "comboBox1";
			this.comboBox1.Size = new Size(124, 20);
			this.comboBox1.TabIndex = 39;
			this.comboBox2.DropDownStyle = ComboBoxStyle.DropDownList;
			this.comboBox2.FormattingEnabled = true;
			this.comboBox2.Items.AddRange(new object[]
			{
				"无需验证",
				"需要用户名及密码"
			});
			this.comboBox2.Location = new Point(136, 102);
			this.comboBox2.Name = "comboBox2";
			this.comboBox2.Size = new Size(266, 20);
			this.comboBox2.TabIndex = 40;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(422, 228);
			base.Controls.Add(this.comboBox2);
			base.Controls.Add(this.comboBox1);
			base.Controls.Add(this.textBox10);
			base.Controls.Add(this.label12);
			base.Controls.Add(this.textBox9);
			base.Controls.Add(this.label11);
			base.Controls.Add(this.textBox8);
			base.Controls.Add(this.label10);
			base.Controls.Add(this.textBox7);
			base.Controls.Add(this.label8);
			base.Controls.Add(this.label4);
			base.Controls.Add(this.textBox5);
			base.Controls.Add(this.label3);
			base.Controls.Add(this.label1);
			base.Controls.Add(this.textBox2);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.textBox4);
			base.Controls.Add(this.label5);
			base.Controls.Add(this.textBox3);
			base.Controls.Add(this.label6);
			base.Name = "AFN04_07";
			this.Text = "终端IP地址和端口";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
