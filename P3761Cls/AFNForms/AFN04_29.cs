using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_29 : iForm
	{
		private IContainer components = null;
		private Label label6;
		private TextBox textBox3;
		public AFN04_29()
		{
			this.InitializeComponent();
			base.HelpButton = true;
		}
		protected override void GetText()
		{
			this.Data = "";
			string data = base.OperaSend(this.textBox3.Text, 12, "ASCII");
			this.Data = data;
		}
		public override void SetText()
		{
			if (!string.IsNullOrEmpty(this.Data))
			{
				string data = this.Data;
				this.textBox3.Text = base.OperaRec(data, "ASCII");
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
			base.SuspendLayout();
			this.textBox3.Location = new Point(154, 31);
			this.textBox3.Name = "textBox3";
			this.textBox3.Size = new Size(109, 21);
			this.textBox3.TabIndex = 9;
			this.textBox3.Text = "0";
			this.label6.AutoSize = true;
			this.label6.Location = new Point(23, 34);
			this.label6.Name = "label6";
			this.label6.Size = new Size(125, 12);
			this.label6.TabIndex = 8;
			this.label6.Text = "终端当地电能表显示号";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(290, 89);
			base.Controls.Add(this.textBox3);
			base.Controls.Add(this.label6);
			base.Name = "AFN04_29";
			this.Text = "终端当地电能表显示号";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
