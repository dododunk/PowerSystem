using Helper;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN05_01 : iForm
	{
		private IContainer components = null;
		private Label label3;
		private Label label1;
		private Label label6;
		private ComboBox textBox3;
		private ComboBox textBox2;
		private Label label2;
		public AFN05_01()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			checked
			{
				for (int i = 0; i <= 15; i++)
				{
					this.textBox3.Items.Add(i.ToString());
					this.textBox2.Items.Add(i.ToString());
				}
				this.textBox3.SelectedIndex = 0;
				this.textBox2.SelectedIndex = 0;
			}
		}
		protected override void GetText()
		{
			this.Data = "";
			string data = string.Empty;
			int num = int.Parse(this.textBox3.Text) << 4;
			data = (num | int.Parse(this.textBox2.Text)).ToString("X2");
			this.Data = data;
		}
		public override void SetText()
		{
			if (!string.IsNullOrEmpty(this.Data))
			{
				string data = this.Data;
				int num = DataConvert.HexToInt(data);
				this.textBox3.Text = (num >> 4).ToString();
				this.textBox2.Text = (num & 15).ToString();
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
			this.label2 = new Label();
			this.label1 = new Label();
			this.textBox3 = new ComboBox();
			this.textBox2 = new ComboBox();
			this.label3 = new Label();
			base.SuspendLayout();
			this.label6.AutoSize = true;
			this.label6.Location = new Point(28, 28);
			this.label6.Name = "label6";
			this.label6.Size = new Size(77, 12);
			this.label6.TabIndex = 8;
			this.label6.Text = "告警延时时间";
			this.label2.AutoSize = true;
			this.label2.Location = new Point(28, 59);
			this.label2.Name = "label2";
			this.label2.Size = new Size(53, 12);
			this.label2.TabIndex = 21;
			this.label2.Text = "限电时间";
			this.label1.AutoSize = true;
			this.label1.Location = new Point(187, 59);
			this.label1.Name = "label1";
			this.label1.Size = new Size(29, 12);
			this.label1.TabIndex = 23;
			this.label1.Text = "0.5h";
			this.textBox3.DropDownStyle = ComboBoxStyle.DropDownList;
			this.textBox3.FormattingEnabled = true;
			this.textBox3.Location = new Point(111, 26);
			this.textBox3.Name = "textBox3";
			this.textBox3.Size = new Size(70, 20);
			this.textBox3.TabIndex = 96;
			this.textBox2.DropDownStyle = ComboBoxStyle.DropDownList;
			this.textBox2.FormattingEnabled = true;
			this.textBox2.Location = new Point(111, 56);
			this.textBox2.Name = "textBox2";
			this.textBox2.Size = new Size(70, 20);
			this.textBox2.TabIndex = 97;
			this.label3.AutoSize = true;
			this.label3.Location = new Point(187, 29);
			this.label3.Name = "label3";
			this.label3.Size = new Size(23, 12);
			this.label3.TabIndex = 98;
			this.label3.Text = "min";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(243, 104);
			base.Controls.Add(this.label3);
			base.Controls.Add(this.textBox2);
			base.Controls.Add(this.textBox3);
			base.Controls.Add(this.label1);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.label6);
			base.Name = "AFN05_01";
			this.Text = "遥控跳闸";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
