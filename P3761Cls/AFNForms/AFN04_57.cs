using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
	public class AFN04_57 : iForm
	{
		private string[] times = new string[24];
		private CheckBox[] cb = new CheckBox[24];
		private IContainer components = null;
		private Label label1;
		private CheckBox checkBox1;
		public AFN04_57()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			this.times = this.TimePeriods2.Split(new char[]
			{
				'~'
			});
			int num = 0;
			int num2 = 35;
			checked
			{
				for (int i = 0; i < 24; i++)
				{
					this.cb[i] = new CheckBox();
					this.cb[i].Text = this.times[i];
					this.cb[i].Parent = this;
					this.cb[i].AutoSize = true;
					num += 25;
					if (i % 4 == 0)
					{
						num2 += 25;
					}
					if (i % 4 != 0)
					{
						num += 75;
					}
					else
					{
						num = 25;
					}
					this.cb[i].Top = num2;
					this.cb[i].Left = num;
				}
			}
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			long num = 0L;
			checked
			{
				for (int i = 0; i < 24; i++)
				{
					num |= (this.cb[i].Checked ? 1L : 0L) << (i & 31);
				}
				text += DataConvert.ReverseStr(num.ToString("X6"));
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
					long num = DataConvert.HexToLong(DataConvert.ReverseStr(data));
					for (int i = 0; i < 24; i++)
					{
						this.cb[i].Checked = ((num >> i & 1L) == 1L);
					}
				}
			}
		}
		private void checkBox1_CheckStateChanged(object sender, EventArgs e)
		{
			if (this.checkBox1.Checked)
			{
				base.SetCheck(true);
			}
			else
			{
				base.SetCheck(false);
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
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(30, 24);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(146, 13);
            this.label1.TabIndex = 61;
            this.label1.Text = "声音告警允许∕禁止标志位";
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Location = new System.Drawing.Point(185, 23);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(50, 17);
            this.checkBox1.TabIndex = 62;
            this.checkBox1.Text = "全选";
            this.checkBox1.UseVisualStyleBackColor = true;
            this.checkBox1.CheckStateChanged += new System.EventHandler(this.checkBox1_CheckStateChanged);
            // 
            // AFN04_57
            // 
            this.ClientSize = new System.Drawing.Size(439, 231);
            this.Controls.Add(this.checkBox1);
            this.Controls.Add(this.label1);
            this.Name = "AFN04_57";
            this.Text = "终端声音告警允许∕禁止设置";
            this.ResumeLayout(false);
            this.PerformLayout();

		}
	}
}
