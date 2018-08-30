using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_47 : iForm
	{
		private IContainer components = null;
		private Button button3;
		private Button button2;
		private Button button1;
		private Label label7;
		private ComboBox comboBox1;
		private Label label3;
		private TextBox textBox5;
		private Label label6;
		private TextBox textBox3;
		private TextBox textBox2;
		private Label label2;
		private Label label1;
		private TextBox textBox1;
		public AFN04_47()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			this.comboBox1.SelectedIndex = 0;
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			text += base.OperaSend(this.textBox3.Text, 4, "BIN");
			if (this.comboBox1.Text == "追加")
			{
				text += "55";
			}
			else
			{
				text += "AA";
			}
			text += this.textBox5.Text;
			text += this.textBox1.Text;
			text += this.textBox2.Text;
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
					this.textBox3.Text = base.OperaRec(data.Substring(num, 8), "BIN");
					num += 8;
					this.comboBox1.SelectedIndex = ((data.Substring(num, 2) == "55") ? 0 : 1);
					num += 2;
					this.textBox5.Text = data.Substring(num, 8);
					num += 8;
					this.textBox1.Text = data.Substring(num, 8);
					num += 8;
					this.textBox2.Text = data.Substring(num, 8);
					num += 8;
				}
			}
		}
		private void Button1Click(object sender, EventArgs e)
		{
			iForm iForm = new A3();
			iForm.Data = this.textBox5.Text;
			iForm.SetText();
			iForm.ShowDialog();
			this.textBox5.Text = iForm.Data;
		}
		private void Button2Click(object sender, EventArgs e)
		{
			iForm iForm = new A3();
			iForm.Data = this.textBox1.Text;
			iForm.SetText();
			iForm.ShowDialog();
			this.textBox1.Text = iForm.Data;
		}
		private void Button3Click(object sender, EventArgs e)
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
			this.textBox3 = new TextBox();
			this.label6 = new Label();
			this.textBox1 = new TextBox();
			this.label1 = new Label();
			this.textBox2 = new TextBox();
			this.label2 = new Label();
			this.textBox5 = new TextBox();
			this.label3 = new Label();
			this.comboBox1 = new ComboBox();
			this.label7 = new Label();
			this.button1 = new Button();
			this.button2 = new Button();
			this.button3 = new Button();
			base.SuspendLayout();
			this.textBox3.Location = new Point(113, 21);
			this.textBox3.Name = "textBox3";
			this.textBox3.Size = new Size(132, 21);
			this.textBox3.TabIndex = 9;
			this.textBox3.Text = "0";
			this.label6.AutoSize = true;
			this.label6.Location = new Point(54, 24);
			this.label6.Name = "label6";
			this.label6.Size = new Size(53, 12);
			this.label6.TabIndex = 8;
			this.label6.Text = "购电单号";
			this.textBox1.Location = new Point(113, 103);
			this.textBox1.Name = "textBox1";
			this.textBox1.ReadOnly = true;
			this.textBox1.Size = new Size(116, 21);
			this.textBox1.TabIndex = 24;
			this.label1.AutoSize = true;
			this.label1.Location = new Point(42, 106);
			this.label1.Name = "label1";
			this.label1.Size = new Size(65, 12);
			this.label1.TabIndex = 23;
			this.label1.Text = "报警门限值";
			this.textBox2.Location = new Point(113, 130);
			this.textBox2.Name = "textBox2";
			this.textBox2.ReadOnly = true;
			this.textBox2.Size = new Size(116, 21);
			this.textBox2.TabIndex = 22;
			this.label2.AutoSize = true;
			this.label2.Location = new Point(24, 51);
			this.label2.Name = "label2";
			this.label2.Size = new Size(83, 12);
			this.label2.TabIndex = 21;
			this.label2.Text = "追加/刷新标志";
			this.textBox5.Location = new Point(113, 76);
			this.textBox5.Name = "textBox5";
			this.textBox5.ReadOnly = true;
			this.textBox5.Size = new Size(116, 21);
			this.textBox5.TabIndex = 26;
			this.label3.AutoSize = true;
			this.label3.Location = new Point(30, 79);
			this.label3.Name = "label3";
			this.label3.Size = new Size(77, 12);
			this.label3.TabIndex = 25;
			this.label3.Text = "购电量(费)值";
			this.comboBox1.DropDownStyle = ComboBoxStyle.DropDownList;
			this.comboBox1.FormattingEnabled = true;
			this.comboBox1.Items.AddRange(new object[]
			{
				"追加",
				"刷新"
			});
			this.comboBox1.Location = new Point(113, 48);
			this.comboBox1.Name = "comboBox1";
			this.comboBox1.Size = new Size(132, 20);
			this.comboBox1.TabIndex = 52;
			this.label7.AutoSize = true;
			this.label7.Font = new Font("Arial", 9f);
			this.label7.Location = new Point(40, 130);
			this.label7.Name = "label7";
			this.label7.Size = new Size(67, 15);
			this.label7.TabIndex = 51;
			this.label7.Text = "跳闸门限值";
			this.button1.Location = new Point(230, 74);
			this.button1.Name = "button1";
			this.button1.Size = new Size(16, 23);
			this.button1.TabIndex = 95;
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new EventHandler(this.Button1Click);
			this.button2.Location = new Point(230, 101);
			this.button2.Name = "button2";
			this.button2.Size = new Size(16, 23);
			this.button2.TabIndex = 96;
			this.button2.UseVisualStyleBackColor = true;
			this.button2.Click += new EventHandler(this.Button2Click);
			this.button3.Location = new Point(230, 129);
			this.button3.Name = "button3";
			this.button3.Size = new Size(16, 23);
			this.button3.TabIndex = 97;
			this.button3.UseVisualStyleBackColor = true;
			this.button3.Click += new EventHandler(this.Button3Click);
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(274, 176);
			base.Controls.Add(this.button3);
			base.Controls.Add(this.button2);
			base.Controls.Add(this.button1);
			base.Controls.Add(this.comboBox1);
			base.Controls.Add(this.label7);
			base.Controls.Add(this.textBox5);
			base.Controls.Add(this.label3);
			base.Controls.Add(this.textBox1);
			base.Controls.Add(this.label1);
			base.Controls.Add(this.textBox2);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.textBox3);
			base.Controls.Add(this.label6);
			base.Name = "AFN04_47";
			this.Text = "购电量（费）控参数";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
