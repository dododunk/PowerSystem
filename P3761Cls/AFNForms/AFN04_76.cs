using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
	public class AFN04_76 : iForm
	{
		private IContainer components = null;
		private ComboBox comboBox1;
		private Label label6;
		public AFN04_76()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			this.comboBox1.SelectedIndex = 0;
		}
		protected override void GetText()
		{
			this.Data = "";
			string data = this.comboBox1.SelectedIndex.ToString("X2");
			this.Data = data;
		}
		public override void SetText()
		{
			if (!string.IsNullOrEmpty(this.Data))
			{
				string data = this.Data;
				this.comboBox1.SelectedIndex = DataConvert.HexToInt(data);
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
			this.comboBox1 = new ComboBox();
			base.SuspendLayout();
			this.label6.AutoSize = true;
			this.label6.Font = new Font("Arial", 9f);
			this.label6.Location = new Point(32, 27);
			this.label6.Name = "label6";
			this.label6.Size = new Size(55, 15);
			this.label6.TabIndex = 46;
			this.label6.Text = "控制方式";
			this.comboBox1.DropDownStyle = ComboBoxStyle.DropDownList;
			this.comboBox1.FormattingEnabled = true;
			this.comboBox1.Items.AddRange(new object[]
			{
				"",
				"当地控制",
				"远方遥控",
				"闭锁",
				"解锁"
			});
			this.comboBox1.Location = new Point(93, 26);
			this.comboBox1.Name = "comboBox1";
			this.comboBox1.Size = new Size(156, 20);
			this.comboBox1.TabIndex = 50;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(290, 74);
			base.Controls.Add(this.comboBox1);
			base.Controls.Add(this.label6);
			base.Name = "AFN04_76";
			this.Text = "电容器投切控制方式";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
