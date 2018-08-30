using Helper;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class A6 : iForm
	{
		private IContainer components = null;
		private ComboBox comboBox1;
		private MaskedTextBox maskedTextBox1;
		public A6()
		{
			this.InitializeComponent();
			this.NeedSave = true;
			this.comboBox1.SelectedIndex = 0;
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			this.maskedTextBox1.Text = decimal.Parse(this.maskedTextBox1.Text).ToString("00.00");
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
				this.maskedTextBox1.Text = (num & 127).ToString("X2") + "." + text.Substring(2, 2);
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
            this.maskedTextBox1 = new System.Windows.Forms.MaskedTextBox();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.SuspendLayout();
            // 
            // maskedTextBox1
            // 
            this.maskedTextBox1.Dock = System.Windows.Forms.DockStyle.Right;
            this.maskedTextBox1.Location = new System.Drawing.Point(54, 0);
            this.maskedTextBox1.Mask = "99.99";
            this.maskedTextBox1.Name = "maskedTextBox1";
            this.maskedTextBox1.Size = new System.Drawing.Size(62, 20);
            this.maskedTextBox1.TabIndex = 6;
            this.maskedTextBox1.Text = "0000";
            // 
            // comboBox1
            // 
            this.comboBox1.Dock = System.Windows.Forms.DockStyle.Left;
            this.comboBox1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "+",
            "-"});
            this.comboBox1.Location = new System.Drawing.Point(0, 0);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(48, 21);
            this.comboBox1.TabIndex = 7;
            // 
            // A6
            // 
            this.ClientSize = new System.Drawing.Size(116, 21);
            this.Controls.Add(this.maskedTextBox1);
            this.Controls.Add(this.comboBox1);
            this.Name = "A6";
            this.Text = "数据格式 A6";
            this.ResumeLayout(false);
            this.PerformLayout();

		}
	}
}
