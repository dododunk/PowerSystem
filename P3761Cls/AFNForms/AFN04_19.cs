using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_19 : iForm
	{
		private IContainer components = null;
		private Button button1;
		private Label label4;
		private TextBox textBox3;
		public AFN04_19()
		{
			this.InitializeComponent();
			base.HelpButton = true;
		}
		protected override void GetText()
		{
			this.Data = this.textBox3.Text;
		}
		public override void SetText()
		{
			if (!string.IsNullOrEmpty(this.Data))
			{
				this.textBox3.Text = this.Data;
			}
		}
		private void Button1Click(object sender, EventArgs e)
		{
			iForm iForm = new A4();
			iForm.Data = this.textBox3.Text;
			iForm.SetText();
			iForm.ShowDialog();
			this.textBox3.Text = iForm.Data;
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
			this.label4 = new Label();
			this.button1 = new Button();
			base.SuspendLayout();
			this.textBox3.Location = new Point(168, 26);
			this.textBox3.Name = "textBox3";
			this.textBox3.ReadOnly = true;
			this.textBox3.Size = new Size(126, 21);
			this.textBox3.TabIndex = 9;
			this.label4.AutoSize = true;
			this.label4.Font = new Font("Arial", 9f);
			this.label4.Location = new Point(28, 27);
			this.label4.Name = "label4";
			this.label4.Size = new Size(139, 15);
			this.label4.TabIndex = 48;
			this.label4.Text = "月电能量控定值浮动系数";
			this.button1.Location = new Point(295, 25);
			this.button1.Name = "button1";
			this.button1.Size = new Size(16, 23);
			this.button1.TabIndex = 49;
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new EventHandler(this.Button1Click);
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(345, 76);
			base.Controls.Add(this.button1);
			base.Controls.Add(this.label4);
			base.Controls.Add(this.textBox3);
			base.Name = "AFN04_19";
			this.Text = "F19终端时段功控定值浮动系数,F20终端月电能量控定值浮动系数";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
