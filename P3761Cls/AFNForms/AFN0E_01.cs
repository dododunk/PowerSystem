using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN0E_01 : iForm
	{
		private IContainer components = null;
		private Label label3;
		private Label label2;
		private ComboBox textBox2;
		private ComboBox textBox3;
		public AFN0E_01()
		{
			this.InitializeComponent();
			checked
			{
				for (int i = 0; i <= 255; i++)
				{
					this.textBox2.Items.Add(i.ToString());
					this.textBox3.Items.Add(i.ToString());
				}
			}
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			text += base.OperaSend(this.textBox2.Text, 1, "BIN");
			text += base.OperaSend(this.textBox3.Text, 1, "BIN");
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
					this.textBox2.Text = base.OperaRec(data.Substring(num, 2), "BIN");
					num += 2;
					this.textBox3.Text = base.OperaRec(data.Substring(num, 2), "BIN");
					num += 2;
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
			this.label2 = new Label();
			this.label3 = new Label();
			this.textBox2 = new ComboBox();
			this.textBox3 = new ComboBox();
			base.SuspendLayout();
			this.label2.AutoSize = true;
			this.label2.Location = new Point(22, 29);
			this.label2.Name = "label2";
			this.label2.Size = new Size(137, 12);
			this.label2.TabIndex = 7;
			this.label2.Text = "请求事件记录起始指针Pm";
			this.label3.AutoSize = true;
			this.label3.Location = new Point(22, 61);
			this.label3.Name = "label3";
			this.label3.Size = new Size(137, 12);
			this.label3.TabIndex = 9;
			this.label3.Text = "请求事件记录结束指针Pn";
			this.textBox2.FormattingEnabled = true;
			this.textBox2.Location = new Point(167, 26);
			this.textBox2.Name = "textBox2";
			this.textBox2.Size = new Size(65, 20);
			this.textBox2.TabIndex = 11;
			this.textBox2.Text = "0";
			this.textBox3.FormattingEnabled = true;
			this.textBox3.Location = new Point(167, 57);
			this.textBox3.Name = "textBox3";
			this.textBox3.Size = new Size(65, 20);
			this.textBox3.TabIndex = 12;
			this.textBox3.Text = "255";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(258, 106);
			base.Controls.Add(this.textBox3);
			base.Controls.Add(this.textBox2);
			base.Controls.Add(this.label3);
			base.Controls.Add(this.label2);
			base.Name = "AFN0E_01";
			this.Text = "请求事件";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
