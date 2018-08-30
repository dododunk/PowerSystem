using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_43 : iForm
	{
		private IContainer components = null;
		private Label label3;
		private Label label6;
		private ComboBox textBox3;
		public AFN04_43()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			checked
			{
				for (int i = 1; i <= 60; i++)
				{
					this.textBox3.Items.Add(i.ToString());
				}
				this.textBox3.SelectedIndex = 0;
			}
		}
		protected override void GetText()
		{
			this.Data = "";
			string data = string.Empty;
			data = base.OperaSend(this.textBox3.Text, 1, "BIN");
			this.Data = data;
		}
		public override void SetText()
		{
			if (!string.IsNullOrEmpty(this.Data))
			{
				string data = this.Data;
				this.textBox3.Text = base.OperaRec(data, "BIN");
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
			this.label3 = new Label();
			this.textBox3 = new ComboBox();
			base.SuspendLayout();
			this.label6.AutoSize = true;
			this.label6.Location = new Point(26, 34);
			this.label6.Name = "label6";
			this.label6.Size = new Size(161, 12);
			this.label6.TabIndex = 8;
			this.label6.Text = "功率控制的功率计算滑差时间";
			this.label3.AutoSize = true;
			this.label3.Location = new Point(268, 34);
			this.label3.Name = "label3";
			this.label3.Size = new Size(23, 12);
			this.label3.TabIndex = 25;
			this.label3.Text = "min";
			this.textBox3.DropDownStyle = ComboBoxStyle.DropDownList;
			this.textBox3.FormattingEnabled = true;
			this.textBox3.Location = new Point(193, 31);
			this.textBox3.Name = "textBox3";
			this.textBox3.Size = new Size(69, 20);
			this.textBox3.TabIndex = 97;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(321, 84);
			base.Controls.Add(this.textBox3);
			base.Controls.Add(this.label3);
			base.Controls.Add(this.label6);
			base.Name = "AFN04_43";
			this.Text = "功率控制的功率计算滑差时间";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
