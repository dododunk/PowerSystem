using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_67 : iForm
	{
		private IContainer components = null;
		private ComboBox comboBox1;
		private Label label1;
		public AFN04_67()
		{
			this.InitializeComponent();
			this.comboBox1.SelectedIndex = 0;
			base.HelpButton = true;
		}
		private void Button1Click(object sender, EventArgs e)
		{
			string empty = string.Empty;
			this.Data = empty;
			base.Close();
		}
		protected override void GetText()
		{
			this.Data = "";
			string empty = string.Empty;
			switch (this.comboBox1.SelectedIndex)
			{
			case 0:
				this.Data = "55";
				break;

			case 1:
				this.Data = "AA";
				break;

			default:
				this.Data = "00";
				break;
			}
		}
		public override void SetText()
		{
			if (!string.IsNullOrEmpty(this.Data))
			{
				string data = this.Data;
				string text = data.ToUpper();
				if (text != null)
				{
					if (text == "55")
					{
						this.comboBox1.SelectedIndex = 0;
						goto IL_6B;
					}
					if (text == "AA")
					{
						this.comboBox1.SelectedIndex = 1;
						goto IL_6B;
					}
				}
				this.comboBox1.SelectedIndex = 2;
				IL_6B:;
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
			this.label1 = new Label();
			this.comboBox1 = new ComboBox();
			base.SuspendLayout();
			this.label1.AutoSize = true;
			this.label1.Location = new Point(27, 25);
			this.label1.Name = "label1";
			this.label1.Size = new Size(83, 12);
			this.label1.TabIndex = 57;
			this.label1.Text = "启动/停止标志";
			this.comboBox1.DropDownStyle = ComboBoxStyle.DropDownList;
			this.comboBox1.FormattingEnabled = true;
			this.comboBox1.Items.AddRange(new object[]
			{
				"启动",
				"停止",
				"无效"
			});
			this.comboBox1.Location = new Point(116, 21);
			this.comboBox1.Name = "comboBox1";
			this.comboBox1.Size = new Size(93, 20);
			this.comboBox1.TabIndex = 58;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(242, 66);
			base.Controls.Add(this.comboBox1);
			base.Controls.Add(this.label1);
			base.Name = "AFN04_67";
			this.Text = "定时上报任务启动/停止";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
