using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN05_59 : iForm
	{
		private IContainer components = null;
		private DateTimePicker dateTimePicker1;
		private Label label4;
		private ComboBox comboBox1;
		private Label label3;
		private Label label6;
		private ComboBox textBox2;
		private Label label2;
		public AFN05_59()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			this.dateTimePicker1.Value = DateTime.Now;
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			text += base.OperaSend(this.dateTimePicker1.Value.ToString(), 6, "A1");
			text += base.OperaSend(this.textBox2.Text, 1, "BIN");
			text += base.OperaSend(this.comboBox1.Text, 2, "BIN");
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
					this.dateTimePicker1.Value = DateTime.Parse(base.OperaRec(data.Substring(num, 12), "A1"));
					num += 12;
					this.textBox2.Text = base.OperaRec(data.Substring(num, 2), "BIN");
					num += 2;
					this.comboBox1.Text = base.OperaRec(data.Substring(num, 4), "BIN");
					num += 4;
				}
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
			this.label2 = new Label();
			this.textBox2 = new ComboBox();
			this.comboBox1 = new ComboBox();
			this.label3 = new Label();
			this.label4 = new Label();
			this.dateTimePicker1 = new DateTimePicker();
			base.SuspendLayout();
			this.label6.AutoSize = true;
			this.label6.Location = new Point(27, 25);
			this.label6.Name = "label6";
			this.label6.Size = new Size(53, 12);
			this.label6.TabIndex = 8;
			this.label6.Text = "开始时间";
			this.label2.AutoSize = true;
			this.label2.Location = new Point(27, 53);
			this.label2.Name = "label2";
			this.label2.Size = new Size(77, 12);
			this.label2.TabIndex = 21;
			this.label2.Text = "新无线信道号";
			this.textBox2.FormattingEnabled = true;
			this.textBox2.Location = new Point(110, 50);
			this.textBox2.Name = "textBox2";
			this.textBox2.Size = new Size(143, 20);
			this.textBox2.TabIndex = 97;
			this.comboBox1.FormattingEnabled = true;
			this.comboBox1.Location = new Point(139, 76);
			this.comboBox1.Name = "comboBox1";
			this.comboBox1.Size = new Size(95, 20);
			this.comboBox1.TabIndex = 100;
			this.label3.AutoSize = true;
			this.label3.Location = new Point(237, 80);
			this.label3.Name = "label3";
			this.label3.Size = new Size(17, 12);
			this.label3.TabIndex = 99;
			this.label3.Text = "秒";
			this.label4.AutoSize = true;
			this.label4.Location = new Point(27, 79);
			this.label4.Name = "label4";
			this.label4.Size = new Size(101, 12);
			this.label4.TabIndex = 98;
			this.label4.Text = "延时切换信道时间";
			this.dateTimePicker1.CustomFormat = "yy-MM-dd HH:mm:ss";
			this.dateTimePicker1.Format = DateTimePickerFormat.Custom;
			this.dateTimePicker1.Location = new Point(110, 21);
			this.dateTimePicker1.Name = "dateTimePicker1";
			this.dateTimePicker1.Size = new Size(143, 21);
			this.dateTimePicker1.TabIndex = 101;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(282, 122);
			base.Controls.Add(this.dateTimePicker1);
			base.Controls.Add(this.comboBox1);
			base.Controls.Add(this.label3);
			base.Controls.Add(this.label4);
			base.Controls.Add(this.textBox2);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.label6);
			base.Name = "AFN05_59";
			this.Text = "切换信道命令";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
