using Helper;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_61 : iForm
	{
		private CheckBox[] cb_1 = new CheckBox[8];
		private IContainer components = null;
		private Label label9;
		public AFN04_61()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			int num = 25;
			checked
			{
				for (int i = 0; i < 8; i++)
				{
					this.cb_1[i] = new CheckBox();
					this.cb_1[i].Text = (i + 1).ToString() + "路";
					this.cb_1[i].AutoSize = true;
					this.cb_1[i].Parent = this;
					this.cb_1[i].Top = 60;
					this.cb_1[i].Left = num;
					num += 50;
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
					int num = DataConvert.HexToInt(DataConvert.ReverseStr(data.Substring(0, 2)));
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
			this.label9.Location = new Point(22, 21);
			this.label9.Name = "label9";
			this.label9.Size = new Size(125, 12);
			this.label9.TabIndex = 13;
			this.label9.Text = "直流模拟量接入标志位";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(445, 119);
			base.Controls.Add(this.label9);
			base.Name = "AFN04_61";
			this.Text = "直流模拟量接入参数";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
