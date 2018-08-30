using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
	public class AFN04_03 : iForm
	{
		private IContainer components = null;
		private Label label10;
		private TextBox textBox5;
		private TextBox textBox4;
		private Label label6;
		private TextBox textBox3;
		private Label label5;
		private TextBox textBox2;
		private Label label2;
		private Label label1;
		private TextBox textBox1;
		public AFN04_03()
		{
			this.InitializeComponent();
			base.HelpButton = true;
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			string[] array = this.textBox3.Text.Split(new char[]
			{
				'.'
			});
			text = int.Parse(array[0]).ToString("X2") + int.Parse(array[1]).ToString("X2") + int.Parse(array[2]).ToString("X2") + int.Parse(array[3]).ToString("X2");
			text += DataConvert.ReverseStr(int.Parse(this.textBox4.Text).ToString("X4"));
			string[] array2 = this.textBox2.Text.Split(new char[]
			{
				'.'
			});
			string text2 = text;
			text = string.Concat(new string[]
			{
				text2,
				int.Parse(array2[0]).ToString("X2"),
				int.Parse(array2[1]).ToString("X2"),
				int.Parse(array2[2]).ToString("X2"),
				int.Parse(array2[3]).ToString("X2")
			});
			text += DataConvert.ReverseStr(int.Parse(this.textBox1.Text).ToString("X4"));
			text += base.OperaSend(this.textBox5.Text.Trim(), 16, "ASCII");
			this.Data = text;
		}
		public override void SetText()
		{
			if (!string.IsNullOrEmpty(this.Data))
			{
				string data = this.Data;
				this.textBox3.Text = DataConvert.HexStrToIp(data.Substring(0, 8));
				this.textBox4.Text = base.OperaRec(data.Substring(8, 4), "BIN");
				this.textBox2.Text = DataConvert.HexStrToIp(data.Substring(12, 8));
				this.textBox1.Text = base.OperaRec(data.Substring(20, 4), "BIN");
				this.textBox5.Text = base.OperaRec(data.Substring(24), "ASCII");
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
			this.textBox5 = new TextBox();
			this.label10 = new Label();
			this.textBox1 = new TextBox();
			this.label1 = new Label();
			this.textBox2 = new TextBox();
			this.label2 = new Label();
			base.SuspendLayout();
			this.label5.AutoSize = true;
			this.label5.Location = new Point(234, 29);
			this.label5.Name = "label5";
			this.label5.Size = new Size(29, 12);
			this.label5.TabIndex = 10;
			this.label5.Text = "端口";
			this.textBox3.Location = new Point(101, 26);
			this.textBox3.Name = "textBox3";
			this.textBox3.Size = new Size(117, 21);
			this.textBox3.TabIndex = 9;
			this.textBox3.Text = "0.0.0.0";
			this.label6.AutoSize = true;
			this.label6.Location = new Point(30, 29);
			this.label6.Name = "label6";
			this.label6.Size = new Size(65, 12);
			this.label6.TabIndex = 8;
			this.label6.Text = "主用IP地址";
			this.textBox4.Location = new Point(269, 26);
			this.textBox4.Name = "textBox4";
			this.textBox4.Size = new Size(46, 21);
			this.textBox4.TabIndex = 11;
			this.textBox4.Text = "0";
			this.textBox5.Location = new Point(101, 100);
			this.textBox5.Name = "textBox5";
			this.textBox5.Size = new Size(214, 21);
			this.textBox5.TabIndex = 18;
			this.label10.AutoSize = true;
			this.label10.Location = new Point(72, 103);
			this.label10.Name = "label10";
			this.label10.Size = new Size(23, 12);
			this.label10.TabIndex = 17;
			this.label10.Text = "APN";
			this.textBox1.Location = new Point(269, 63);
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new Size(46, 21);
			this.textBox1.TabIndex = 24;
			this.textBox1.Text = "0";
			this.label1.AutoSize = true;
			this.label1.Location = new Point(234, 66);
			this.label1.Name = "label1";
			this.label1.Size = new Size(29, 12);
			this.label1.TabIndex = 23;
			this.label1.Text = "端口";
			this.textBox2.Location = new Point(101, 63);
			this.textBox2.Name = "textBox2";
			this.textBox2.Size = new Size(117, 21);
			this.textBox2.TabIndex = 22;
			this.textBox2.Text = "0.0.0.0";
			this.label2.AutoSize = true;
			this.label2.Location = new Point(30, 66);
			this.label2.Name = "label2";
			this.label2.Size = new Size(65, 12);
			this.label2.TabIndex = 21;
			this.label2.Text = "备用IP地址";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(348, 152);
			base.Controls.Add(this.textBox1);
			base.Controls.Add(this.label1);
			base.Controls.Add(this.textBox2);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.textBox5);
			base.Controls.Add(this.label10);
			base.Controls.Add(this.textBox4);
			base.Controls.Add(this.label5);
			base.Controls.Add(this.textBox3);
			base.Controls.Add(this.label6);
			base.Name = "AFN04_03";
			this.Text = "主站IP地址和端口";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
