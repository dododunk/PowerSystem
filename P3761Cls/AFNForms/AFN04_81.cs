using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_81 : iForm
	{
		private IContainer components = null;
		private Button button2;
		private Button button1;
		private Label label6;
		private TextBox textBox3;
		private TextBox textBox2;
		private Label label2;
		public AFN04_81()
		{
			this.InitializeComponent();
			base.HelpButton = true;
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			text += this.textBox3.Text;
			text += this.textBox2.Text;
			this.Data = text;
		}
		public override void SetText()
		{
			if (!string.IsNullOrEmpty(this.Data))
			{
				string data = this.Data;
				this.textBox3.Text = data.Substring(0, 4);
				this.textBox2.Text = data.Substring(4, 4);
			}
		}
		private void Button1Click(object sender, EventArgs e)
		{
			iForm iForm = new A2();
			iForm.Data = this.textBox3.Text;
			iForm.SetText();
			iForm.ShowDialog();
			this.textBox3.Text = iForm.Data;
		}
		private void Button2Click(object sender, EventArgs e)
		{
			iForm iForm = new A2();
			iForm.Data = this.textBox2.Text;
			iForm.SetText();
			iForm.ShowDialog();
			this.textBox2.Text = iForm.Data;
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
			this.button1 = new Button();
			this.button2 = new Button();
			base.SuspendLayout();
			this.textBox3.Location = new Point(135, 31);
			this.textBox3.Name = "textBox3";
			this.textBox3.ReadOnly = true;
			this.textBox3.Size = new Size(132, 21);
			this.textBox3.TabIndex = 9;
			this.label6.AutoSize = true;
			this.label6.Location = new Point(40, 34);
			this.label6.Name = "label6";
			this.label6.Size = new Size(89, 12);
			this.label6.TabIndex = 8;
			this.label6.Text = "直流模拟量上限";
			this.textBox2.Location = new Point(135, 68);
			this.textBox2.Name = "textBox2";
			this.textBox2.ReadOnly = true;
			this.textBox2.Size = new Size(132, 21);
			this.textBox2.TabIndex = 22;
			this.label2.AutoSize = true;
			this.label2.Location = new Point(40, 71);
			this.label2.Name = "label2";
			this.label2.Size = new Size(89, 12);
			this.label2.TabIndex = 21;
			this.label2.Text = "直流模拟量下限";
			this.button1.Location = new Point(268, 30);
			this.button1.Name = "button1";
			this.button1.Size = new Size(16, 23);
			this.button1.TabIndex = 50;
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new EventHandler(this.Button1Click);
			this.button2.Location = new Point(268, 67);
			this.button2.Name = "button2";
			this.button2.Size = new Size(16, 23);
			this.button2.TabIndex = 51;
			this.button2.UseVisualStyleBackColor = true;
			this.button2.Click += new EventHandler(this.Button2Click);
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(327, 126);
			base.Controls.Add(this.button2);
			base.Controls.Add(this.button1);
			base.Controls.Add(this.textBox2);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.textBox3);
			base.Controls.Add(this.label6);
			base.Name = "AFN04_81";
			this.Text = "F81直流模拟量输入变比,F82直流模拟量限值";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
