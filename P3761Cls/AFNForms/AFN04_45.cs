using Helper;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_45 : iForm
	{
		private CheckBox[] cb_1 = new CheckBox[8];
		private IContainer components = null;
		private Label label9;
		public AFN04_45()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			int left = 50;
			int num = 50;
			checked
			{
				for (int i = 0; i < 8; i++)
				{
					this.cb_1[i] = new CheckBox();
					this.cb_1[i].Text = "第" + (i + 1).ToString() + "轮次开关";
					this.cb_1[i].AutoSize = true;
					this.cb_1[i].Parent = this;
					this.cb_1[i].Top = num;
					this.cb_1[i].Left = left;
					num += 30;
				}
			}
		}
		protected override void GetText()
		{
			this.Data = "";
			string data = string.Empty;
			int num = 0;
			checked
			{
				for (int i = 0; i < 8; i++)
				{
					num |= (this.cb_1[i].Checked ? 1 : 0) << i;
				}
				data = DataConvert.ReverseStr(num.ToString("X2"));
				this.Data = data;
			}
		}
		public override void SetText()
		{
			checked
			{
				if (!string.IsNullOrEmpty(this.Data))
				{
					string data = this.Data;
					int num = DataConvert.HexToInt(data);
					for (int i = 0; i < 8; i++)
					{
						this.cb_1[i].Checked = ((num >> i & 1) == 1);
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
			base.SuspendLayout();
			this.label9.AutoSize = true;
			this.label9.Location = new Point(52, 21);
			this.label9.Name = "label9";
			this.label9.Size = new Size(77, 12);
			this.label9.TabIndex = 13;
			this.label9.Text = "功控轮次设定";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(208, 304);
			base.Controls.Add(this.label9);
			base.Name = "AFN04_45";
			this.Text = "功控轮次设定";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
