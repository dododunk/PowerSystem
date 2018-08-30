using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
	public class A3 : iForm
	{
		private IContainer components = null;
		private ComboBox comboBox1;
		private ComboBox comboBox2;
		private MaskedTextBox maskedTextBox1;
		public A3()
		{
			this.InitializeComponent();
			this.NeedSave = true;
			this.comboBox1.SelectedIndex = 0;
			this.comboBox2.SelectedIndex = 0;
		}
		protected override void GetText()
		{
			this.Data = "";
			string val = string.Empty;
			val = (this.comboBox1.SelectedIndex | this.comboBox2.SelectedIndex << 2).ToString("X") + this.maskedTextBox1.Text.PadLeft(7, '0');
			this.Data = DataConvert.ReverseStr(val);
		}
		public override void SetText()
		{
			if (!string.IsNullOrEmpty(this.Data))
			{
				string text = DataConvert.ReverseStr(this.Data);
				int num = DataConvert.HexToInt(text.Substring(0, 1));
				this.comboBox2.SelectedIndex = num >> 2;
				this.comboBox1.SelectedIndex = (num & 1);
				this.maskedTextBox1.Text = (int.Parse(text.Substring(1, 1)).ToString("X") + text.Substring(2, 6)).PadLeft(7, '0');
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

            this.comboBox2 = new ComboBox();
            this.comboBox1 = new ComboBox();
            this.maskedTextBox1 = new MaskedTextBox();
			this.maskedTextBox1.Location = new Point(45, 1);
			this.maskedTextBox1.Mask = "9999999";
			this.maskedTextBox1.Name = "maskedTextBox1";
			this.maskedTextBox1.Size = new Size(74, 21);
			this.maskedTextBox1.TabIndex = 1;
			this.maskedTextBox1.Text = "0000000";
			this.comboBox2.DropDownStyle = ComboBoxStyle.DropDownList;
			this.comboBox2.FormattingEnabled = true;
			this.comboBox2.Items.AddRange(new object[]
			{
				"kWh、厘",
				"MWh、元"
			});
			this.comboBox2.Location = new Point(120, 1);
			this.comboBox2.Name = "comboBox2";
			this.comboBox2.Size = new Size(83, 20);
			this.comboBox2.TabIndex = 2;
			this.comboBox1.DropDownStyle = ComboBoxStyle.DropDownList;
			this.comboBox1.FormattingEnabled = true;
			this.comboBox1.Items.AddRange(new object[]
			{
				"+",
				"-"
			});
			this.comboBox1.Location = new Point(0, 1);
			this.comboBox1.Name = "comboBox1";
			this.comboBox1.Size = new Size(44, 20);
			this.comboBox1.TabIndex = 3;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(204, 22);
			base.Controls.Add(this.comboBox1);
			base.Controls.Add(this.comboBox2);
			base.Controls.Add(this.maskedTextBox1);
			
			base.Name = "A3";
			this.Text = "数据格式 A3";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
