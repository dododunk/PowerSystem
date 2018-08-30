using Helper;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_25 : iForm
	{
		private IContainer components = null;
		private Label label9;
		private Label label4;
		private Label label5;
		private Label label10;
		private ComboBox comboBox2;
		private Label label7;
		private ComboBox comboBox1;
		private Label label8;
		private TextBox textBox7;
		private Label label3;
		private TextBox textBox5;
		private Label label6;
		private TextBox textBox3;
		private TextBox textBox2;
		private Label label2;
		private Label label1;
		private TextBox textBox1;
		public AFN04_25()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			this.comboBox1.SelectedIndex = 1;
			this.comboBox2.SelectedIndex = 0;
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			text += base.OperaSend(this.textBox3.Text, 2, "BIN");
			text += base.OperaSend(this.textBox2.Text, 2, "BIN");
			text += base.OperaSend(this.textBox5.Text, 2, "A7");
			text += base.OperaSend(this.textBox7.Text, 1, "A22");
			text += base.OperaSend(this.textBox1.Text, 3, "A23");
			text += (this.comboBox1.SelectedIndex | this.comboBox2.SelectedIndex << 2).ToString("X2");
			this.Data = text;
		}
		public override void SetText()
		{
			if (!string.IsNullOrEmpty(this.Data))
			{
				string data = this.Data;
				this.textBox3.Text = base.OperaRec(data.Substring(0, 4), "BIN");
				this.textBox2.Text = base.OperaRec(data.Substring(4, 4), "BIN");
				this.textBox5.Text = base.OperaRec(data.Substring(8, 4), "A7");
				this.textBox7.Text = base.OperaRec(data.Substring(12, 2), "A22");
				this.textBox1.Text = base.OperaRec(data.Substring(14, 6), "A23");
				int num = DataConvert.HexToInt(data.Substring(20, 2));
				this.comboBox1.SelectedIndex = (num & 3);
				this.comboBox2.SelectedIndex = (num >> 2 & 3);
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
			this.textBox2 = new TextBox();
			this.label2 = new Label();
			this.comboBox1 = new ComboBox();
			this.label7 = new Label();
			this.comboBox2 = new ComboBox();
			this.label10 = new Label();
			this.label5 = new Label();
			this.label4 = new Label();
			this.label9 = new Label();
			this.textBox7 = new TextBox();
			this.label8 = new Label();
			this.textBox5 = new TextBox();
			this.label3 = new Label();
			this.textBox1 = new TextBox();
			this.label1 = new Label();
			base.SuspendLayout();
			this.textBox3.Location = new Point(118, 22);
			this.textBox3.Name = "textBox3";
			this.textBox3.Size = new Size(58, 21);
			this.textBox3.TabIndex = 9;
			this.textBox3.Text = "0";
			this.label6.AutoSize = true;
			this.label6.Location = new Point(23, 25);
			this.label6.Name = "label6";
			this.label6.Size = new Size(89, 12);
			this.label6.TabIndex = 8;
			this.label6.Text = "电压互感器倍率";
			this.textBox2.Location = new Point(304, 22);
			this.textBox2.Name = "textBox2";
			this.textBox2.Size = new Size(58, 21);
			this.textBox2.TabIndex = 22;
			this.textBox2.Text = "0";
			this.label2.AutoSize = true;
			this.label2.Location = new Point(209, 25);
			this.label2.Name = "label2";
			this.label2.Size = new Size(89, 12);
			this.label2.TabIndex = 21;
			this.label2.Text = "电流互感器倍率";
			this.comboBox1.DropDownStyle = ComboBoxStyle.DropDownList;
			this.comboBox1.FormattingEnabled = true;
			this.comboBox1.Items.AddRange(new object[]
			{
				"[备用]",
				"三相三线",
				"三相四线",
				"单相表"
			});
			this.comboBox1.Location = new Point(118, 103);
			this.comboBox1.Name = "comboBox1";
			this.comboBox1.Size = new Size(244, 20);
			this.comboBox1.TabIndex = 52;
			this.label7.AutoSize = true;
			this.label7.Font = new Font("Arial", 9f);
			this.label7.Location = new Point(33, 105);
			this.label7.Name = "label7";
			this.label7.Size = new Size(79, 15);
			this.label7.TabIndex = 51;
			this.label7.Text = "电源接线方式";
			this.comboBox2.DropDownStyle = ComboBoxStyle.DropDownList;
			this.comboBox2.FormattingEnabled = true;
			this.comboBox2.Items.AddRange(new object[]
			{
				"不确定",
				"A相",
				"B相",
				"C相"
			});
			this.comboBox2.Location = new Point(118, 129);
			this.comboBox2.Name = "comboBox2";
			this.comboBox2.Size = new Size(244, 20);
			this.comboBox2.TabIndex = 54;
			this.label10.AutoSize = true;
			this.label10.Font = new Font("Arial", 9f);
			this.label10.Location = new Point(33, 130);
			this.label10.Name = "label10";
			this.label10.Size = new Size(79, 15);
			this.label10.TabIndex = 53;
			this.label10.Text = "单相表接线相";
			this.label5.AutoSize = true;
			this.label5.Location = new Point(182, 79);
			this.label5.Name = "label5";
			this.label5.Size = new Size(23, 12);
			this.label5.TabIndex = 63;
			this.label5.Text = "kVA";
			this.label4.AutoSize = true;
			this.label4.Location = new Point(182, 52);
			this.label4.Name = "label4";
			this.label4.Size = new Size(11, 12);
			this.label4.TabIndex = 62;
			this.label4.Text = "V";
			this.label9.AutoSize = true;
			this.label9.Location = new Point(368, 52);
			this.label9.Name = "label9";
			this.label9.Size = new Size(11, 12);
			this.label9.TabIndex = 61;
			this.label9.Text = "A";
			this.textBox7.Location = new Point(304, 49);
			this.textBox7.Name = "textBox7";
			this.textBox7.Size = new Size(58, 21);
			this.textBox7.TabIndex = 60;
			this.textBox7.Text = "0";
			this.label8.AutoSize = true;
			this.label8.Location = new Point(245, 52);
			this.label8.Name = "label8";
			this.label8.Size = new Size(53, 12);
			this.label8.TabIndex = 59;
			this.label8.Text = "额定电流";
			this.textBox5.Location = new Point(118, 49);
			this.textBox5.Name = "textBox5";
			this.textBox5.Size = new Size(58, 21);
			this.textBox5.TabIndex = 58;
			this.textBox5.Text = "0";
			this.label3.AutoSize = true;
			this.label3.Location = new Point(59, 52);
			this.label3.Name = "label3";
			this.label3.Size = new Size(53, 12);
			this.label3.TabIndex = 57;
			this.label3.Text = "额定电压";
			this.textBox1.Location = new Point(118, 76);
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new Size(58, 21);
			this.textBox1.TabIndex = 56;
			this.textBox1.Text = "0";
			this.label1.AutoSize = true;
			this.label1.Location = new Point(59, 79);
			this.label1.Name = "label1";
			this.label1.Size = new Size(53, 12);
			this.label1.TabIndex = 55;
			this.label1.Text = "额定负荷";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(403, 176);
			base.Controls.Add(this.label5);
			base.Controls.Add(this.label4);
			base.Controls.Add(this.label9);
			base.Controls.Add(this.textBox7);
			base.Controls.Add(this.label8);
			base.Controls.Add(this.textBox5);
			base.Controls.Add(this.label3);
			base.Controls.Add(this.textBox1);
			base.Controls.Add(this.label1);
			base.Controls.Add(this.comboBox2);
			base.Controls.Add(this.label10);
			base.Controls.Add(this.comboBox1);
			base.Controls.Add(this.label7);
			base.Controls.Add(this.textBox2);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.textBox3);
			base.Controls.Add(this.label6);
			base.Name = "AFN04_25";
			this.Text = "测量点基本参数";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
