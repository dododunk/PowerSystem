using Helper;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_05 : iForm
	{
		private IContainer components = null;
		private Label label6;
		private ComboBox textBox3;
		private TextBox textBox2;
		private Label label2;
		public AFN04_05()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			checked
			{
				for (int i = 0; i <= 255; i++)
				{
					this.textBox3.Items.Add(i.ToString());
				}
				this.textBox3.SelectedIndex = 0;
			}
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			text = int.Parse(this.textBox3.Text).ToString("X2");
			text += DataConvert.ReverseStr(int.Parse(this.textBox2.Text).ToString("X4"));
			this.Data = text;
		}
		public override void SetText()
		{
			if (!string.IsNullOrEmpty(this.Data))
			{
				string data = this.Data;
				this.textBox3.Text = DataConvert.HexToInt(data.Substring(0, 2)).ToString();
				this.textBox2.Text = base.OperaRec(data.Substring(2, 4), "BIN");
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
			this.label6 = new Label();
			this.textBox2 = new TextBox();
			this.label2 = new Label();
			this.textBox3 = new ComboBox();
			base.SuspendLayout();
			this.label6.AutoSize = true;
			this.label6.Location = new Point(27, 28);
			this.label6.Name = "label6";
			this.label6.Size = new Size(89, 12);
			this.label6.TabIndex = 8;
			this.label6.Text = "消息认证方案号";
			this.textBox2.Location = new Point(134, 60);
			this.textBox2.Name = "textBox2";
			this.textBox2.Size = new Size(97, 21);
			this.textBox2.TabIndex = 22;
			this.textBox2.Text = "0";
			this.label2.AutoSize = true;
			this.label2.Location = new Point(27, 63);
			this.label2.Name = "label2";
			this.label2.Size = new Size(101, 12);
			this.label2.TabIndex = 21;
			this.label2.Text = "消息认证方案参数";
			this.textBox3.DropDownStyle = ComboBoxStyle.DropDownList;
			this.textBox3.FormattingEnabled = true;
			this.textBox3.Location = new Point(134, 25);
			this.textBox3.Name = "textBox3";
			this.textBox3.Size = new Size(97, 20);
			this.textBox3.TabIndex = 24;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(264, 112);
			base.Controls.Add(this.textBox3);
			base.Controls.Add(this.textBox2);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.label6);
			base.Name = "AFN04_05";
			this.Text = "终端上行通信消息认证参数设置";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
