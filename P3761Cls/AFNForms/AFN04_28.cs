using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_28 : iForm
	{
		private IContainer components = null;
		private Button button2;
		private Button button1;
		private TextBox textBox1;
		private Label label2;
		private Label label4;
		private TextBox textBox3;
		public AFN04_28()
		{
			this.InitializeComponent();
			base.HelpButton = true;
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			text += this.textBox3.Text;
			text += this.textBox1.Text;
			this.Data = text;
		}
		public override void SetText()
		{
			if (!string.IsNullOrEmpty(this.Data))
			{
				string data = this.Data;
				this.textBox3.Text = data.Substring(0, 4);
				this.textBox1.Text = data.Substring(4, 4);
			}
		}
		private void Button1Click(object sender, EventArgs e)
		{
			iForm iForm = new A5();
			iForm.Data = this.textBox3.Text;
			iForm.SetText();
			iForm.ShowDialog();
			this.textBox3.Text = iForm.Data;
		}
		private void Button2Click(object sender, EventArgs e)
		{
			iForm iForm = new A5();
			iForm.Data = this.textBox1.Text;
			iForm.SetText();
			iForm.ShowDialog();
			this.textBox1.Text = iForm.Data;
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
			this.label2 = new Label();
			this.textBox1 = new TextBox();
			this.button1 = new Button();
			this.button2 = new Button();
			base.SuspendLayout();
			this.textBox3.Location = new Point(149, 26);
			this.textBox3.Name = "textBox3";
			this.textBox3.ReadOnly = true;
			this.textBox3.Size = new Size(71, 21);
			this.textBox3.TabIndex = 9;
			this.label4.AutoSize = true;
			this.label4.Font = new Font("Arial", 9f);
			this.label4.Location = new Point(33, 27);
			this.label4.Name = "label4";
			this.label4.Size = new Size(110, 15);
			this.label4.TabIndex = 48;
			this.label4.Text = "功率因数分段限值1";
			this.label2.AutoSize = true;
			this.label2.Font = new Font("Arial", 9f);
			this.label2.Location = new Point(33, 63);
			this.label2.Name = "label2";
			this.label2.Size = new Size(110, 15);
			this.label2.TabIndex = 51;
			this.label2.Text = "功率因数分段限值2";
			this.textBox1.Location = new Point(149, 62);
			this.textBox1.Name = "textBox1";
			this.textBox1.ReadOnly = true;
			this.textBox1.Size = new Size(71, 21);
			this.textBox1.TabIndex = 49;
			this.button1.Location = new Point(221, 25);
			this.button1.Name = "button1";
			this.button1.Size = new Size(16, 23);
			this.button1.TabIndex = 92;
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new EventHandler(this.Button1Click);
			this.button2.Location = new Point(221, 61);
			this.button2.Name = "button2";
			this.button2.Size = new Size(16, 23);
			this.button2.TabIndex = 93;
			this.button2.UseVisualStyleBackColor = true;
			this.button2.Click += new EventHandler(this.Button2Click);
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(274, 113);
			base.Controls.Add(this.button2);
			base.Controls.Add(this.button1);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.textBox1);
			base.Controls.Add(this.label4);
			base.Controls.Add(this.textBox3);
			base.Name = "AFN04_28";
			this.Text = "测量点功率因数分段限值";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
