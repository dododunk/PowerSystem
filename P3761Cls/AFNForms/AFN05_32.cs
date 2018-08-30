using System;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
	public class AFN05_32 : iForm
	{
		private IContainer components = null;
		private ComboBox comboBox1;
		private TextBox textBox7;
		private Label label3;
		private Label label6;
		private TextBox textBox2;
		private Label label2;
		public AFN05_32()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			this.comboBox1.SelectedIndex = 0;
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			int num = this.comboBox1.SelectedIndex << 4;
			text += (num | int.Parse(this.textBox2.Text)).ToString("X2");
			string text2 = this.textBox7.Text.Trim();
			string text3 = string.Empty;
			int num2 = 0;
			checked
			{
				for (int i = 0; i < text2.Length; i++)
				{
					int num3 = 0;
					string val = this.GB2312ToHexStr(text2.Substring(i, 1), ref num3);
					text3 += DataConvert.ReverseStr(val);
					num2 += 2;
				}
				string str = num2.ToString("X2");
				text = text + str + text3;
				this.Data = text;
			}
		}
		private string GB2312ToHexStr(string strSrc, ref int num)
		{
			byte[] bytes = Encoding.GetEncoding("GB2312").GetBytes(strSrc.Trim());
			num = bytes.Length;
			StringBuilder stringBuilder = new StringBuilder(checked(strSrc.Length * 2));
			byte[] array = bytes;
			for (int i = 0; i < array.Length; i++)
			{
				byte value = array[i];
				stringBuilder.Append(Convert.ToString(value, 16).PadLeft(2, '0'));
			}
			return stringBuilder.ToString().Trim().ToUpper().PadLeft(4, '0');
		}
		public override void SetText()
		{
			checked
			{
				if (!string.IsNullOrEmpty(this.Data))
				{
					string data = this.Data;
					int num = 0;
					int num2 = DataConvert.HexToInt(data.Substring(num, 2));
					num += 2;
					this.comboBox1.SelectedIndex = num2 >> 4;
					this.textBox2.Text = (num2 & 15).ToString();
					int num3 = DataConvert.HexToInt(data.Substring(num, 2));
					num += 2;
					string text = data.Substring(num);
					string text2 = string.Empty;
					for (int i = 0; i < num3 / 2; i++)
					{
						text2 += this.HexStrToGB2312(DataConvert.ReverseStr(text.Substring(i * 4, 4)));
					}
					this.textBox7.Text = text2;
				}
			}
		}
		private string HexStrToGB2312(string strSrc)
		{
			Debug.Print("strSrc=" + strSrc);
			if (strSrc.Substring(0, 2) == "00")
			{
				strSrc = strSrc.Substring(2, 2);
			}
			byte[] bytes = PubFuncHelper.HexStrToByte(strSrc);
			return Encoding.GetEncoding("GB2312").GetString(bytes);
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
			this.textBox2 = new TextBox();
			this.label2 = new Label();
			this.label3 = new Label();
			this.textBox7 = new TextBox();
			this.comboBox1 = new ComboBox();
			base.SuspendLayout();
			this.label6.AutoSize = true;
			this.label6.Location = new Point(13, 15);
			this.label6.Name = "label6";
			this.label6.Size = new Size(77, 12);
			this.label6.TabIndex = 8;
			this.label6.Text = "中文信息种类";
			this.textBox2.Location = new Point(281, 12);
			this.textBox2.Name = "textBox2";
			this.textBox2.Size = new Size(33, 21);
			this.textBox2.TabIndex = 22;
			this.textBox2.Text = "0";
			this.label2.AutoSize = true;
			this.label2.Location = new Point(198, 15);
			this.label2.Name = "label2";
			this.label2.Size = new Size(77, 12);
			this.label2.TabIndex = 21;
			this.label2.Text = "中文信息编号";
			this.label3.AutoSize = true;
			this.label3.Location = new Point(13, 44);
			this.label3.Name = "label3";
			this.label3.Size = new Size(53, 12);
			this.label3.TabIndex = 25;
			this.label3.Text = "汉字信息";
			this.textBox7.Location = new Point(13, 59);
			this.textBox7.Multiline = true;
			this.textBox7.Name = "textBox7";
			this.textBox7.ScrollBars = ScrollBars.Both;
			this.textBox7.Size = new Size(312, 132);
			this.textBox7.TabIndex = 31;
			this.comboBox1.DropDownStyle = ComboBoxStyle.DropDownList;
			this.comboBox1.FormattingEnabled = true;
			this.comboBox1.Items.AddRange(new object[]
			{
				"普通信息",
				"重要信息"
			});
			this.comboBox1.Location = new Point(96, 12);
			this.comboBox1.Name = "comboBox1";
			this.comboBox1.Size = new Size(86, 20);
			this.comboBox1.TabIndex = 54;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(339, 206);
			base.Controls.Add(this.comboBox1);
			base.Controls.Add(this.textBox7);
			base.Controls.Add(this.label3);
			base.Controls.Add(this.textBox2);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.label6);
			base.Name = "AFN05_32";
			this.Text = "中文信息";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
