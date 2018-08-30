using Helper;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class A4 : iForm
	{
		private IContainer components = null;
		private Label label4;
		private ComboBox comboBox2;
		private MaskedTextBox maskedTextBox1;
		public A4()
		{
			this.InitializeComponent();
			this.NeedSave = true;
			this.comboBox2.SelectedIndex = 0;
		}
		protected override void GetText()
		{
			this.Data = "";
			this.maskedTextBox1.Text = this.maskedTextBox1.Text.PadLeft(2, '0');
			string data = string.Empty;
			data = (this.comboBox2.SelectedIndex << 3 | int.Parse(this.maskedTextBox1.Text.Substring(0, 1))).ToString("X") + this.maskedTextBox1.Text.Substring(1, 1);
			this.Data = data;
		}
		public override void SetText()
		{
			if (!string.IsNullOrEmpty(this.Data))
			{
				string data = this.Data;
				int num = DataConvert.HexToInt(data.Substring(0, 2));
				this.comboBox2.SelectedIndex = num >> 7;
				this.maskedTextBox1.Text = (num >> 4 & 7).ToString("X") + (num & 15).ToString("X");
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
			this.label4 = new Label();
			this.maskedTextBox1 = new MaskedTextBox();
			
			this.comboBox2.DropDownStyle = ComboBoxStyle.DropDownList;
			this.comboBox2.FormattingEnabled = true;
			this.comboBox2.Items.AddRange(new object[]
			{
				"上浮",
				"下浮"
			});
			this.comboBox2.Location = new Point(1, 1);
			this.comboBox2.Name = "comboBox2";
			this.comboBox2.Size = new Size(54, 20);
			this.comboBox2.TabIndex = 67;
			this.label4.AutoSize = true;
			this.label4.Font = new Font("Arial", 10.5f, FontStyle.Regular, GraphicsUnit.Point, 0);
			this.label4.Location = new Point(129, 3);
			this.label4.Name = "label4";
			this.label4.Size = new Size(20, 16);
			this.label4.TabIndex = 68;
			this.label4.Text = "%";
			this.maskedTextBox1.Location = new Point(56, 1);
			this.maskedTextBox1.Mask = "99";
			this.maskedTextBox1.Name = "maskedTextBox1";
			this.maskedTextBox1.Size = new Size(74, 21);
			this.maskedTextBox1.TabIndex = 69;
			this.maskedTextBox1.Text = "00";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(148, 23);
			base.Controls.Add(this.maskedTextBox1);
			base.Controls.Add(this.comboBox2);
			base.Controls.Add(this.label4);
			
			base.Name = "A4";
			this.Text = "数据格式 A4";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
