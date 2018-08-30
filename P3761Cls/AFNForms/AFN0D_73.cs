using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN0D_73 : iForm
	{
		private IContainer components = null;
		private DateTimePicker dateTimePicker1;
		private Label label3;
		private CheckBox checkBox1;
		private ComboBox comboBox1;
		private Label label2;
		private TextBox textBox1;
		private Label label1;
		public AFN0D_73()
		{
			this.InitializeComponent();
			this.comboBox1.SelectedIndex = 0;
			this.dateTimePicker1.Value = DateTime.Now;
		}
		protected override void GetText()
		{
			this.Data = "";
			int num = 0;
			if (this.comboBox1.SelectedIndex == 0)
			{
				num = 0;
			}
			if (this.comboBox1.SelectedIndex == 1)
			{
				num = 1;
			}
			if (this.comboBox1.SelectedIndex == 2)
			{
				num = 2;
			}
			if (this.comboBox1.SelectedIndex == 3)
			{
				num = 3;
			}
			if (this.comboBox1.SelectedIndex == 4)
			{
				num = 254;
			}
			if (this.comboBox1.SelectedIndex == 5)
			{
				num = 255;
			}
			if (this.checkBox1.Checked)
			{
				this.Data = base.OperaSend(num.ToString(), 1, "BIN") + base.OperaSend(this.textBox1.Text, 1, "BIN");
			}
			else
			{
				this.Data = base.OperaSend(this.dateTimePicker1.Text, 5, "A15") + base.OperaSend(num.ToString(), 1, "BIN") + base.OperaSend(this.textBox1.Text, 1, "BIN");
			}
		}
		public override void SetText()
		{
			if (!string.IsNullOrEmpty(this.Data))
			{
				string data = this.Data;
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
            this.label1 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.label3 = new System.Windows.Forms.Label();
            this.dateTimePicker1 = new System.Windows.Forms.DateTimePicker();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(22, 102);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(55, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "数据点数";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(81, 99);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(134, 20);
            this.textBox1.TabIndex = 1;
            this.textBox1.Text = "0";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(22, 77);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(55, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "数据密度";
            // 
            // comboBox1
            // 
            this.comboBox1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "无",
            "15分、30分、45分、0分",
            "30分、0分",
            "0分",
            "5分、10分、15分......、0分",
            "1分、2分、3分、......0分"});
            this.comboBox1.Location = new System.Drawing.Point(81, 74);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(134, 21);
            this.comboBox1.TabIndex = 4;
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Checked = true;
            this.checkBox1.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox1.Location = new System.Drawing.Point(81, 47);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(98, 17);
            this.checkBox1.TabIndex = 5;
            this.checkBox1.Text = "实时系统时间";
            this.checkBox1.UseVisualStyleBackColor = true;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(21, 23);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(31, 13);
            this.label3.TabIndex = 6;
            this.label3.Text = "时间";
            // 
            // dateTimePicker1
            // 
            this.dateTimePicker1.CustomFormat = "yy-MM-dd HH:mm:ss";
            this.dateTimePicker1.Format = System.Windows.Forms.DateTimePickerFormat.Custom;
            this.dateTimePicker1.Location = new System.Drawing.Point(81, 15);
            this.dateTimePicker1.Name = "dateTimePicker1";
            this.dateTimePicker1.Size = new System.Drawing.Size(134, 20);
            this.dateTimePicker1.TabIndex = 7;
            // 
            // AFN0D_73
            // 
            this.ClientSize = new System.Drawing.Size(238, 138);
            this.Controls.Add(this.dateTimePicker1);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.checkBox1);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.label1);
            this.Name = "AFN0D_73";
            this.Text = "冻结类数据时标";
            this.ResumeLayout(false);
            this.PerformLayout();

		}
	}
}
