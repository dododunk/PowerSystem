using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_04 : iForm
	{
		private IContainer components = null;
		private Label label6;
		private TextBox textBox3;
		private TextBox textBox2;
		private Label label2;
		public AFN04_04()
		{
			this.InitializeComponent();
			base.HelpButton = true;
		}
		protected override void GetText()
		{
			this.Data = "";
			string data = string.Empty;
			data = this.textBox3.Text.PadRight(16, 'F') + this.textBox2.Text.PadRight(16, 'F');
			this.Data = data;
		}
		public override void SetText()
		{
			if (!string.IsNullOrEmpty(this.Data))
			{
				string data = this.Data;
				string text = data.Substring(0, 16);
				text = text.Replace("F", "");
				text = text.Replace('A', ',');
				text = text.Replace('B', '#');
				this.textBox3.Text = text;
				text = data.Substring(16, 16);
				text = text.Replace("F", "");
				text = text.Replace('A', ',');
				text = text.Replace('B', '#');
				this.textBox2.Text = text;
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
			this.textBox3 = new TextBox();
			this.label6 = new Label();
			this.textBox2 = new TextBox();
			this.label2 = new Label();
			base.SuspendLayout();
			this.textBox3.Location = new Point(111, 22);
			this.textBox3.Name = "textBox3";
			this.textBox3.Size = new Size(109, 21);
			this.textBox3.TabIndex = 9;
			this.label6.AutoSize = true;
			this.label6.Location = new Point(28, 27);
			this.label6.Name = "label6";
			this.label6.Size = new Size(77, 12);
			this.label6.TabIndex = 8;
			this.label6.Text = "主站电话号码";
			this.textBox2.Location = new Point(111, 59);
			this.textBox2.Name = "textBox2";
			this.textBox2.Size = new Size(109, 21);
			this.textBox2.TabIndex = 22;
			this.label2.AutoSize = true;
			this.label2.Location = new Point(28, 64);
			this.label2.Name = "label2";
			this.label2.Size = new Size(77, 12);
			this.label2.TabIndex = 21;
			this.label2.Text = "短信中心号码";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(250, 108);
			base.Controls.Add(this.textBox2);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.textBox3);
			base.Controls.Add(this.label6);
			base.Name = "AFN04_04";
			this.Text = "主站电话号码和短信中心号码";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
