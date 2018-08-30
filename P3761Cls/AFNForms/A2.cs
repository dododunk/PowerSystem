using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
	public class A2 : iForm
	{
		private IContainer components = null;
		private Label label1;
		private ComboBox comboBox2;
		private MaskedTextBox maskedTextBox1;
		private ComboBox comboBox1;
		public A2()
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
			val = (this.comboBox1.SelectedIndex | this.comboBox2.SelectedIndex << 1).ToString("X") + this.maskedTextBox1.Text;
			this.Data = DataConvert.ReverseStr(val);
		}
		public override void SetText()
		{
			if (!string.IsNullOrEmpty(this.Data))
			{
				string text = DataConvert.ReverseStr(this.Data);
				int num = DataConvert.HexToInt(text.Substring(0, 1));
				this.comboBox1.SelectedIndex = (num & 1);
				this.comboBox2.SelectedIndex = num >> 1;
				this.maskedTextBox1.Text = int.Parse(text.Substring(1, 1)).ToString("X") + text.Substring(2, 2);
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
			this.comboBox1 = new ComboBox();
			this.maskedTextBox1 = new MaskedTextBox();
			this.comboBox2 = new ComboBox();
			this.label1 = new Label();
			base.SuspendLayout();
			this.comboBox1.DropDownStyle = ComboBoxStyle.DropDownList;
			this.comboBox1.FormattingEnabled = true;
			this.comboBox1.Items.AddRange(new object[]
			{
				"+",
				"-"
			});
			this.comboBox1.Location = new Point(1, 1);
			this.comboBox1.Name = "comboBox1";
			this.comboBox1.Size = new Size(40, 20);
			this.comboBox1.TabIndex = 0;
			this.maskedTextBox1.Location = new Point(42, 1);
			this.maskedTextBox1.Mask = "999";
			this.maskedTextBox1.Name = "maskedTextBox1";
			this.maskedTextBox1.Size = new Size(45, 21);
			this.maskedTextBox1.TabIndex = 1;
			this.maskedTextBox1.Text = "000";
			this.comboBox2.DropDownStyle = ComboBoxStyle.DropDownList;
			this.comboBox2.FormattingEnabled = true;
			this.comboBox2.Items.AddRange(new object[]
			{
				"10^4",
				"10^3",
				"10^2",
				"10^1",
				"10^0",
				"10^-1",
				"10^-2",
				"10^-3",
				""
			});
			this.comboBox2.Location = new Point(100, 1);
			this.comboBox2.Name = "comboBox2";
			this.comboBox2.Size = new Size(74, 20);
			this.comboBox2.TabIndex = 2;
			this.label1.AutoSize = true;
			this.label1.Location = new Point(86, 4);
			this.label1.Name = "label1";
			this.label1.Size = new Size(17, 12);
			this.label1.TabIndex = 3;
			this.label1.Text = "×";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(175, 22);
			base.Controls.Add(this.maskedTextBox1);
			base.Controls.Add(this.comboBox2);
			base.Controls.Add(this.comboBox1);
			base.Controls.Add(this.label1);
			
			base.Name = "A2";
			this.Text = "数据格式 A2";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
