using Helper;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN03_01 : iForm
	{
		private IContainer components = null;
		private Label label1;
		private ComboBox comboBox1;
		private Label label6;
		private ComboBox textBox3;
		public AFN03_01()
		{
			this.InitializeComponent();
			this.textBox3.SelectedIndex = 0;
			this.comboBox1.SelectedIndex = 0;
		}
		protected override void GetText()
		{
			this.Data = "";
			string data = (this.textBox3.SelectedIndex | this.comboBox1.SelectedIndex << 2).ToString("X2");
			this.Data = data;
		}
		public override void SetText()
		{
			if (!string.IsNullOrEmpty(this.Data))
			{
				string data = this.Data;
				int num = DataConvert.HexToInt(data);
				this.textBox3.SelectedIndex = (num & 3);
				this.comboBox1.SelectedIndex = (num >> 2 & 3);
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
			this.textBox3 = new ComboBox();
			this.comboBox1 = new ComboBox();
			this.label1 = new Label();
			base.SuspendLayout();
			this.label6.AutoSize = true;
			this.label6.Location = new Point(27, 28);
			this.label6.Name = "label6";
			this.label6.Size = new Size(131, 12);
			this.label6.TabIndex = 8;
			this.label6.Text = "值班机/备份机切换控制";
			this.textBox3.DropDownStyle = ComboBoxStyle.DropDownList;
			this.textBox3.FormattingEnabled = true;
			this.textBox3.Items.AddRange(new object[]
			{
				"不切换",
				"",
				"切换"
			});
			this.textBox3.Location = new Point(169, 25);
			this.textBox3.Name = "textBox3";
			this.textBox3.Size = new Size(97, 20);
			this.textBox3.TabIndex = 24;
			this.comboBox1.DropDownStyle = ComboBoxStyle.DropDownList;
			this.comboBox1.FormattingEnabled = true;
			this.comboBox1.Items.AddRange(new object[]
			{
				"不允许",
				"",
				"允许"
			});
			this.comboBox1.Location = new Point(169, 62);
			this.comboBox1.Name = "comboBox1";
			this.comboBox1.Size = new Size(97, 20);
			this.comboBox1.TabIndex = 26;
			this.label1.AutoSize = true;
			this.label1.Location = new Point(27, 65);
			this.label1.Name = "label1";
			this.label1.Size = new Size(137, 12);
			this.label1.TabIndex = 25;
			this.label1.Text = "值班机中继转发允许标志";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(294, 112);
			base.Controls.Add(this.comboBox1);
			base.Controls.Add(this.label1);
			base.Controls.Add(this.textBox3);
			base.Controls.Add(this.label6);
			base.Name = "AFN03_01";
			this.Text = "中继站工作状态控制";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
