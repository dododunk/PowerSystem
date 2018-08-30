using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_46 : iForm
	{
		private IContainer components = null;
		private Button button1;
		private Label label7;
		private TextBox textBox2;
		public AFN04_46()
		{
			this.InitializeComponent();
			base.HelpButton = true;
		}
		protected override void GetText()
		{
			this.Data = "";
			string data = string.Empty;
			data = base.OperaSend(this.textBox2.Text, 1, "BIN");
			this.Data = data;
		}
		public override void SetText()
		{
			if (!string.IsNullOrEmpty(this.Data))
			{
				string data = this.Data;
				this.textBox2.Text = data;
			}
		}
		private void Button1Click(object sender, EventArgs e)
		{
			iForm iForm = new A3();
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
			this.textBox2 = new TextBox();
			this.label7 = new Label();
			this.button1 = new Button();
			base.SuspendLayout();
			this.textBox2.Location = new Point(111, 25);
			this.textBox2.Name = "textBox2";
			this.textBox2.ReadOnly = true;
			this.textBox2.Size = new Size(106, 21);
			this.textBox2.TabIndex = 22;
			this.label7.AutoSize = true;
			this.label7.Font = new Font("Arial", 9f);
			this.label7.Location = new Point(26, 26);
			this.label7.Name = "label7";
			this.label7.Size = new Size(79, 15);
			this.label7.TabIndex = 51;
			this.label7.Text = "月电量控定值";
			this.button1.Location = new Point(218, 24);
			this.button1.Name = "button1";
			this.button1.Size = new Size(16, 23);
			this.button1.TabIndex = 94;
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new EventHandler(this.Button1Click);
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(265, 79);
			base.Controls.Add(this.button1);
			base.Controls.Add(this.label7);
			base.Controls.Add(this.textBox2);
			base.Name = "AFN04_46";
			this.Text = "月电量控定值";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
