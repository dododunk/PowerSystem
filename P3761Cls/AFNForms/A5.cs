using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
	public class A5 : iForm
	{
		private IContainer components = null;
		private Label label3;
		private ComboBox comboBox1;
		private MaskedTextBox maskedTextBox1;
		public A5()
		{
			this.InitializeComponent();
			this.NeedSave = true;
			this.comboBox1.SelectedIndex = 0;
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			this.maskedTextBox1.Text = decimal.Parse(this.maskedTextBox1.Text).ToString("000.0");
			text = (this.comboBox1.SelectedIndex << 3 | int.Parse(this.maskedTextBox1.Text.Substring(0, 1))).ToString("X");
			text += this.maskedTextBox1.Text.Replace(".", "").Substring(1, 3);
			this.Data = DataConvert.ReverseStr(text);
		}
		public override void SetText()
		{
			if (!string.IsNullOrEmpty(this.Data))
			{
				string text = DataConvert.ReverseStr(this.Data);
				int num = DataConvert.HexToInt(text.Substring(0, 2));
				this.comboBox1.SelectedIndex = num >> 7;
				this.maskedTextBox1.Text = (num & 127).ToString("X2") + text.Substring(2, 1) + "." + text.Substring(3, 1);
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
            base.SuspendLayout();
			this.comboBox1 = new ComboBox();
			this.label3 = new Label();
			this.maskedTextBox1 = new MaskedTextBox();
			
			this.comboBox1.DropDownStyle = ComboBoxStyle.DropDownList;
			this.comboBox1.FormattingEnabled = true;
			this.comboBox1.Items.AddRange(new object[]
			{
				"+",
				"-"
			});
			this.comboBox1.Location = new Point(1, 1);
			this.comboBox1.Name = "comboBox1";
			this.comboBox1.Size = new Size(42, 20);
			this.comboBox1.TabIndex = 67;
			this.label3.AutoSize = true;
			this.label3.Font = new Font("Arial", 9f);
			this.label3.Location = new Point(107, 3);
			this.label3.Name = "label3";
			this.label3.Size = new Size(18, 15);
			this.label3.TabIndex = 69;
			this.label3.Text = "%";
			this.maskedTextBox1.Location = new Point(44, 1);
			this.maskedTextBox1.Mask = "999.9";
			this.maskedTextBox1.Name = "maskedTextBox1";
			this.maskedTextBox1.Size = new Size(63, 21);
			this.maskedTextBox1.TabIndex = 68;
			this.maskedTextBox1.Text = "0000";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(126, 22);
			base.Controls.Add(this.maskedTextBox1);
			base.Controls.Add(this.comboBox1);
			base.Controls.Add(this.label3);
			
			base.Name = "A5";
			this.Text = "数据格式 A5";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
