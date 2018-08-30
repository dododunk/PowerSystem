using Helper;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_21 : iForm
	{
		private string[] Times;
		private ComboBox[] cb;
		private Label[] lb;
		private int num = 0;
		private IContainer components = null;
		private ComboBox fls;
		private Label label4;
		public AFN04_21()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			checked
			{
				int i;
				for (i = 1; i <= 48; i++)
				{
					this.fls.Items.Add(i.ToString());
				}
				this.Times = this.TimePeriods.Split(new char[]
				{
					'~'
				});
				this.num = this.Times.Length;
				this.lb = new Label[this.num];
				this.cb = new ComboBox[this.num];
				int num = 15;
				int num2 = 15;
				i = 0;
				while (i < this.num)
				{
					this.lb[i] = new Label();
					this.cb[i] = new ComboBox();
					this.lb[i].Text = this.Times[i];
					this.cb[i].DropDownStyle = ComboBoxStyle.DropDownList;
					this.cb[i].BringToFront();
					this.lb[i].AutoSize = true;
					this.cb[i].Width = 65;
					this.lb[i].Parent = this;
					this.cb[i].Parent = this;
					this.lb[i].Top = num;
					this.cb[i].Top = num - 2;
					this.lb[i].Left = num2;
					this.cb[i].Left = num2 + 75;
					num2 += 150;
					i++;
					if (i % 4 == 0)
					{
						num += 30;
					}
					if (i % 4 == 0)
					{
						num2 = 15;
					}
				}
				this.fls.SelectedIndex = 0;
			}
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			checked
			{
				for (int i = 0; i < this.num; i++)
				{
					text += this.cb[i].SelectedIndex.ToString("X2");
				}
				text += int.Parse(this.fls.Text).ToString("X2");
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
					this.fls.SelectedIndex = DataConvert.HexToInt(this.StrRight(data, 2)) - 1;
					int num = 0;
					for (int i = 0; i < this.num; i++)
					{
						this.cb[i].SelectedIndex = DataConvert.HexToInt(data.Substring(num, 2));
						num += 2;
					}
				}
			}
		}
		private string StrRight(string sSource, int iLength)
		{
			return sSource.Substring((iLength > sSource.Length) ? 0 : checked(sSource.Length - iLength));
		}
		private void FlsSelectedIndexChanged(object sender, EventArgs e)
		{
			checked
			{
				for (int i = 0; i < this.num; i++)
				{
					this.cb[i].Items.Clear();
					for (int j = 1; j <= int.Parse(this.fls.Text); j++)
					{
						this.cb[i].Items.Add("费率" + j.ToString());
					}
					this.cb[i].SelectedIndex = 0;
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
			this.label4 = new Label();
			this.fls = new ComboBox();
			base.SuspendLayout();
			this.label4.AutoSize = true;
			this.label4.Location = new Point(13, 382);
			this.label4.Name = "label4";
			this.label4.Size = new Size(41, 12);
			this.label4.TabIndex = 66;
			this.label4.Text = "费率数";
			this.fls.DropDownStyle = ComboBoxStyle.DropDownList;
			this.fls.FormattingEnabled = true;
			this.fls.Location = new Point(60, 378);
			this.fls.Name = "fls";
			this.fls.Size = new Size(74, 20);
			this.fls.TabIndex = 65;
			this.fls.SelectedIndexChanged += new EventHandler(this.FlsSelectedIndexChanged);
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(621, 410);
			base.Controls.Add(this.label4);
			base.Controls.Add(this.fls);
			base.Name = "AFN04_21";
			this.Text = "终端功控时段";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
