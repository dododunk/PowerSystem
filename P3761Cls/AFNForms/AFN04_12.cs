using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
	public class AFN04_12 : iForm
	{
		private CheckBox[] cb_1 = new CheckBox[8];
		private CheckBox[] cb_2 = new CheckBox[8];
		private IContainer components = null;
		private Label label9;
		private Label label1;
		public AFN04_12()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			int num = 25;
			checked
			{
				for (int i = 0; i < 8; i++)
				{
					this.cb_1[i] = new CheckBox();
					this.cb_2[i] = new CheckBox();
					this.cb_1[i].Text = (i + 1).ToString() + "路";
					this.cb_2[i].Text = (i + 1).ToString() + "路";
					this.cb_1[i].AutoSize = true;
					this.cb_2[i].AutoSize = true;
					this.cb_1[i].Parent = this;
					this.cb_2[i].Parent = this;
					this.cb_1[i].Top = 40;
					this.cb_2[i].Top = 100;
					this.cb_1[i].Left = num;
					this.cb_2[i].Left = num;
					num += 50;
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
				num = 0;
				for (int i = 0; i < 8; i++)
				{
					num |= (this.cb_2[i].Checked ? 1 : 0) << i;
				}
				text += DataConvert.ReverseStr(num.ToString("X2"));
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
					int num = DataConvert.HexToInt(DataConvert.ReverseStr(data.Substring(0, 2)));
					for (int i = 0; i < 8; i++)
					{
						this.cb_1[i].Checked = ((num >> i & 1) == 1);
					}
					num = DataConvert.HexToInt(DataConvert.ReverseStr(data.Substring(2, 2)));
					for (int i = 0; i < 8; i++)
					{
						this.cb_2[i].Checked = ((num >> i & 1) == 1);
					}
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
			base.SuspendLayout();
			this.label9.AutoSize = true;
			this.label9.Location = new Point(21, 23);
			this.label9.Name = "label9";
			this.label9.Size = new Size(101, 12);
			this.label9.TabIndex = 13;
			this.label9.Text = "状态量接入标志位";
			this.label1.AutoSize = true;
			this.label1.Location = new Point(21, 82);
			this.label1.Name = "label1";
			this.label1.Size = new Size(101, 12);
			this.label1.TabIndex = 49;
			this.label1.Text = "状态量属性标志位";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(433, 148);
			base.Controls.Add(this.label1);
			base.Controls.Add(this.label9);
			base.Name = "AFN04_12";
			this.Text = "终端状态量输入参数";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
