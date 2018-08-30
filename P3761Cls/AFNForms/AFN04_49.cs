using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_49 : iForm
	{
		private IContainer components = null;
		private Label label1;
		private Label label6;
		private TextBox textBox3;
		public AFN04_49()
		{
			this.InitializeComponent();
			base.HelpButton = true;
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
				this.textBox3.Text = data;
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
			this.label1 = new Label();
			base.SuspendLayout();
			this.textBox3.Location = new Point(115, 29);
			this.textBox3.Name = "textBox3";
			this.textBox3.Size = new Size(102, 21);
			this.textBox3.TabIndex = 9;
			this.textBox3.Text = "0";
			this.label6.AutoSize = true;
			this.label6.Location = new Point(32, 32);
			this.label6.Name = "label6";
			this.label6.Size = new Size(77, 12);
			this.label6.TabIndex = 8;
			this.label6.Text = "功控告警时间";
			this.label1.AutoSize = true;
			this.label1.Location = new Point(223, 33);
			this.label1.Name = "label1";
			this.label1.Size = new Size(23, 12);
			this.label1.TabIndex = 21;
			this.label1.Text = "min";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(274, 87);
			base.Controls.Add(this.label1);
			base.Controls.Add(this.textBox3);
			base.Controls.Add(this.label6);
			base.Name = "AFN04_49";
			this.Text = "功控告警时间";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
