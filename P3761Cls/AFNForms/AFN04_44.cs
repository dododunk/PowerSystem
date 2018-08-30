using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_44 : iForm
	{
		private IContainer components = null;
		private Button button1;
		private Label label1;
		private TextBox textBox1;
		private Label label6;
		private TextBox textBox3;
		private TextBox textBox2;
		private Label label2;
		public AFN04_44()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			this.textBox2.Text = DateTime.Now.ToString("yy-MM-dd");
			this.textBox3.Text = DateTime.Now.ToString("yy-MM-dd");
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			text += base.OperaSend(this.textBox2.Text, 3, "A20");
			text += base.OperaSend(this.textBox3.Text, 3, "A20");
			text += this.textBox1.Text;
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
					this.textBox2.Text = base.OperaRec(data.Substring(num, 6), "A20");
					num += 6;
					this.textBox3.Text = base.OperaRec(data.Substring(num, 6), "A20");
					num += 6;
					this.textBox1.Text = data.Substring(num, 4);
					num += 4;
				}
			}
		}
		private void Button1Click(object sender, EventArgs e)
		{
			iForm iForm = new A2();
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
			this.label6 = new Label();
			this.textBox2 = new TextBox();
			this.label2 = new Label();
			this.textBox1 = new TextBox();
			this.label1 = new Label();
			this.button1 = new Button();
			base.SuspendLayout();
			this.textBox3.Location = new Point(117, 22);
			this.textBox3.Name = "textBox3";
			this.textBox3.Size = new Size(113, 21);
			this.textBox3.TabIndex = 9;
			this.label6.AutoSize = true;
			this.label6.Location = new Point(24, 25);
			this.label6.Name = "label6";
			this.label6.Size = new Size(77, 12);
			this.label6.TabIndex = 8;
			this.label6.Text = "报停起始时间";
			this.textBox2.Location = new Point(117, 49);
			this.textBox2.Name = "textBox2";
			this.textBox2.Size = new Size(113, 21);
			this.textBox2.TabIndex = 22;
			this.label2.AutoSize = true;
			this.label2.Location = new Point(24, 52);
			this.label2.Name = "label2";
			this.label2.Size = new Size(77, 12);
			this.label2.TabIndex = 21;
			this.label2.Text = "报停结束时间";
			this.textBox1.Location = new Point(117, 76);
			this.textBox1.Name = "textBox1";
			this.textBox1.ReadOnly = true;
			this.textBox1.Size = new Size(96, 21);
			this.textBox1.TabIndex = 24;
			this.label1.AutoSize = true;
			this.label1.Location = new Point(24, 79);
			this.label1.Name = "label1";
			this.label1.Size = new Size(89, 12);
			this.label1.TabIndex = 23;
			this.label1.Text = "报停控功率定值";
			this.button1.Location = new Point(214, 75);
			this.button1.Name = "button1";
			this.button1.Size = new Size(16, 23);
			this.button1.TabIndex = 94;
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new EventHandler(this.Button1Click);
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(258, 125);
			base.Controls.Add(this.button1);
			base.Controls.Add(this.textBox1);
			base.Controls.Add(this.label1);
			base.Controls.Add(this.textBox2);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.textBox3);
			base.Controls.Add(this.label6);
			base.Name = "AFN04_44";
			this.Text = "营业报停控参数";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
