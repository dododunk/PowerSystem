using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
	public class A9 : iForm
	{
		private IContainer components = null;
		private SplitContainer splitContainer1;
		private ComboBox comboBox1;
		private MaskedTextBox maskedTextBox1;
		public A9()
		{
			this.InitializeComponent();
			this.NeedSave = true;
			this.comboBox1.SelectedIndex = 0;
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			this.maskedTextBox1.Text = decimal.Parse(this.maskedTextBox1.Text).ToString("00.0000");
			text = (this.comboBox1.SelectedIndex << 3 | int.Parse(this.maskedTextBox1.Text.Substring(0, 1))).ToString("X");
			text += this.maskedTextBox1.Text.Replace(".", "").Substring(1, 5);
			this.Data = DataConvert.ReverseStr(text);
		}
		public override void SetText()
		{
			if (!string.IsNullOrEmpty(this.Data))
			{
				string text = DataConvert.ReverseStr(this.Data);
				int num = DataConvert.HexToInt(text.Substring(0, 2));
				this.comboBox1.SelectedIndex = (num & 128);
				this.maskedTextBox1.Text = (num & 127).ToString("X2") + "." + text.Substring(2, 4);
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
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.maskedTextBox1 = new System.Windows.Forms.MaskedTextBox();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.SuspendLayout();
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.comboBox1);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.maskedTextBox1);
            this.splitContainer1.Size = new System.Drawing.Size(120, 21);
            this.splitContainer1.SplitterDistance = 51;
            this.splitContainer1.SplitterWidth = 2;
            this.splitContainer1.TabIndex = 5;
            // 
            // comboBox1
            // 
            this.comboBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.comboBox1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "+",
            "-"});
            this.comboBox1.Location = new System.Drawing.Point(0, 0);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(51, 21);
            this.comboBox1.TabIndex = 5;
            // 
            // maskedTextBox1
            // 
            this.maskedTextBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.maskedTextBox1.Location = new System.Drawing.Point(0, 0);
            this.maskedTextBox1.Mask = "99.9999";
            this.maskedTextBox1.Name = "maskedTextBox1";
            this.maskedTextBox1.Size = new System.Drawing.Size(67, 20);
            this.maskedTextBox1.TabIndex = 2;
            this.maskedTextBox1.Text = "000000";
            // 
            // A9
            // 
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(120, 21);
            this.Controls.Add(this.splitContainer1);
            this.Name = "A9";
            this.Text = "数据格式 A9";
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.ResumeLayout(false);

		}
	}
}
