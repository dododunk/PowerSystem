using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
	public class AFN05_09 : iForm
	{
		private CheckBox[] cb_1 = new CheckBox[8];
		private IContainer components = null;
		private ComboBox comboBox1;
		private Label label1;
		private Label label9;
		public AFN05_09()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			this.comboBox1.SelectedIndex = 0;
			int num = 25;
			int num2 = 50;
			checked
			{
				for (int i = 0; i < 8; i++)
				{
					this.cb_1[i] = new CheckBox();
					this.cb_1[i].Text = "第" + (i + 1).ToString() + "时段标志";
					this.cb_1[i].AutoSize = true;
					this.cb_1[i].Parent = this;
					this.cb_1[i].Top = num2;
					this.cb_1[i].Left = num;
					num += this.cb_1[i].Width;
					if (i == 3)
					{
						num2 += 30;
						num = 25;
					}
				}
			}
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			int num = 0;
			checked
			{
				for (int i = 0; i < 8; i++)
				{
					num |= (this.cb_1[i].Checked ? 1 : 0) << i;
				}
				text += DataConvert.ReverseStr(num.ToString("X2"));
				text += this.comboBox1.SelectedIndex.ToString("X2");
				this.Data = text;
			}
		}
		public override void SetText()
		{
			checked
			{
				if (!string.IsNullOrEmpty(this.Data))
				{
					string data = this.Data;
					int num = DataConvert.HexToInt(data.Substring(0, 2));
					for (int i = 0; i < 8; i++)
					{
						this.cb_1[i].Checked = ((num & 1 << i) >> i == 1);
					}
					this.comboBox1.SelectedIndex = DataConvert.HexToInt(data.Substring(2, 2));
				}
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
			this.label9 = new Label();
			this.label1 = new Label();
			this.comboBox1 = new ComboBox();
			base.SuspendLayout();
			this.label9.AutoSize = true;
			this.label9.Location = new Point(22, 21);
			this.label9.Name = "label9";
			this.label9.Size = new Size(101, 12);
			this.label9.TabIndex = 13;
			this.label9.Text = "时段功控投入标志";
			this.label1.AutoSize = true;
			this.label1.Location = new Point(22, 127);
			this.label1.Name = "label1";
			this.label1.Size = new Size(113, 12);
			this.label1.TabIndex = 21;
			this.label1.Text = "时段功控定值方案号";
			this.comboBox1.DropDownStyle = ComboBoxStyle.DropDownList;
			this.comboBox1.FormattingEnabled = true;
			this.comboBox1.Items.AddRange(new object[]
			{
				"第1套方案",
				"第2套方案",
				"第3套方案"
			});
			this.comboBox1.Location = new Point(141, 124);
			this.comboBox1.Name = "comboBox1";
			this.comboBox1.Size = new Size(129, 20);
			this.comboBox1.TabIndex = 53;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(406, 174);
			base.Controls.Add(this.comboBox1);
			base.Controls.Add(this.label1);
			base.Controls.Add(this.label9);
			base.Name = "AFN05_09";
			this.Text = "时段功控投入";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
