using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_17 : iForm
	{
		private IContainer components = null;
		private Button button1;
		private Label label1;
		private Label label6;
		private TextBox textBox3;
		public AFN04_17()
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
			iForm iForm = new A3();
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
			this.label6 = new Label();
			this.label1 = new Label();
			this.button1 = new Button();
			base.SuspendLayout();
			this.textBox3.Location = new Point(84, 26);
			this.textBox3.Name = "textBox3";
			this.textBox3.ReadOnly = true;
			this.textBox3.Size = new Size(146, 21);
			this.textBox3.TabIndex = 9;
			this.label6.AutoSize = true;
			this.label6.Location = new Point(25, 29);
			this.label6.Name = "label6";
			this.label6.Size = new Size(53, 12);
			this.label6.TabIndex = 8;
			this.label6.Text = "保安定值";
			this.label1.AutoSize = true;
			this.label1.Location = new Point(250, 31);
			this.label1.Name = "label1";
			this.label1.Size = new Size(17, 12);
			this.label1.TabIndex = 21;
			this.label1.Text = "kW";
			this.button1.FlatStyle = FlatStyle.System;
			this.button1.Location = new Point(230, 25);
			this.button1.Name = "button1";
			this.button1.Size = new Size(16, 23);
			this.button1.TabIndex = 22;
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new EventHandler(this.Button1Click);
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(292, 82);
			base.Controls.Add(this.button1);
			base.Controls.Add(this.label1);
			base.Controls.Add(this.textBox3);
			base.Controls.Add(this.label6);
			base.Name = "AFN04_17";
			this.Text = "终端保安定值";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
