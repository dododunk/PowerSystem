using Helper;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class CtlWord : iForm
	{
		private IContainer components = null;
		private Label label11;
		private ComboBox comboBox3;
		private CheckBox checkBox1;
		private CheckBox checkBox2;
		private CheckBox checkBox3;
		private Label label12;
		private ComboBox comboBox4;
		public CtlWord()
		{
			this.InitializeComponent();
			this.NeedSave = true;
			this.comboBox3.SelectedIndex = 3;
			this.comboBox4.SelectedIndex = 3;
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			int num = 0;
			num |= this.comboBox3.SelectedIndex << 5;
			num |= (this.checkBox1.Checked ? 1 : 0) << 4;
			num |= (this.checkBox2.Checked ? 1 : 0) << 3;
			num |= (this.checkBox3.Checked ? 1 : 0) << 2;
			text += (num | this.comboBox4.SelectedIndex).ToString("X2");
			this.Data = DataConvert.ReverseStr(text);
		}
		public override void SetText()
		{
			if (!string.IsNullOrEmpty(this.Data))
			{
				int num = DataConvert.HexToInt(this.Data);
				this.comboBox3.SelectedIndex = num >> 5;
				this.checkBox1.Checked = ((num >> 4 & 1) == 1);
				this.checkBox2.Checked = ((num >> 3 & 1) == 1);
				this.checkBox3.Checked = ((num >> 2 & 1) == 1);
				this.comboBox4.SelectedIndex = (num & 3);
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
            this.comboBox4 = new System.Windows.Forms.ComboBox();
            this.label12 = new System.Windows.Forms.Label();
            this.checkBox3 = new System.Windows.Forms.CheckBox();
            this.checkBox2 = new System.Windows.Forms.CheckBox();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.comboBox3 = new System.Windows.Forms.ComboBox();
            this.label11 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // comboBox4
            // 
            this.comboBox4.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox4.FormattingEnabled = true;
            this.comboBox4.Items.AddRange(new object[] {
            "5",
            "6",
            "7",
            "8"});
            this.comboBox4.Location = new System.Drawing.Point(423, 14);
            this.comboBox4.Name = "comboBox4";
            this.comboBox4.Size = new System.Drawing.Size(64, 21);
            this.comboBox4.TabIndex = 66;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Font = new System.Drawing.Font("Arial", 9F);
            this.label12.Location = new System.Drawing.Point(386, 17);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(31, 15);
            this.label12.TabIndex = 65;
            this.label12.Text = "位数";
            // 
            // checkBox3
            // 
            this.checkBox3.AutoSize = true;
            this.checkBox3.Location = new System.Drawing.Point(314, 17);
            this.checkBox3.Name = "checkBox3";
            this.checkBox3.Size = new System.Drawing.Size(62, 17);
            this.checkBox3.TabIndex = 64;
            this.checkBox3.Text = "奇校验";
            this.checkBox3.UseVisualStyleBackColor = true;
            // 
            // checkBox2
            // 
            this.checkBox2.AutoSize = true;
            this.checkBox2.Checked = true;
            this.checkBox2.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox2.Location = new System.Drawing.Point(248, 17);
            this.checkBox2.Name = "checkBox2";
            this.checkBox2.Size = new System.Drawing.Size(62, 17);
            this.checkBox2.TabIndex = 63;
            this.checkBox2.Text = "有校验";
            this.checkBox2.UseVisualStyleBackColor = true;
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Location = new System.Drawing.Point(176, 17);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(68, 17);
            this.checkBox1.TabIndex = 62;
            this.checkBox1.Text = "2停止位";
            this.checkBox1.UseVisualStyleBackColor = true;
            // 
            // comboBox3
            // 
            this.comboBox3.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox3.FormattingEnabled = true;
            this.comboBox3.Items.AddRange(new object[] {
            "300",
            "600",
            "1200",
            "2400",
            "4800",
            "7200",
            "9600",
            "19200",
            ""});
            this.comboBox3.Location = new System.Drawing.Point(83, 13);
            this.comboBox3.Name = "comboBox3";
            this.comboBox3.Size = new System.Drawing.Size(75, 21);
            this.comboBox3.TabIndex = 61;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Font = new System.Drawing.Font("Arial", 9F);
            this.label11.Location = new System.Drawing.Point(10, 15);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(67, 15);
            this.label11.TabIndex = 60;
            this.label11.Text = "Baud(bit/s)";
            // 
            // CtlWord
            // 
            this.ClientSize = new System.Drawing.Size(501, 49);
            this.Controls.Add(this.comboBox4);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.checkBox3);
            this.Controls.Add(this.checkBox2);
            this.Controls.Add(this.checkBox1);
            this.Controls.Add(this.comboBox3);
            this.Controls.Add(this.label11);
            this.Name = "CtlWord";
            this.Text = "通讯控制字";
            this.ResumeLayout(false);
            this.PerformLayout();

		}
	}
}
