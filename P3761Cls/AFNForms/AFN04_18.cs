using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
	public class AFN04_18 : iForm
	{
		private string[] Times;
		private ComboBox[] cb;
		private Label[] lb;
		private int num = 0;
		private IContainer components = null;
		private Button button2;
		private Button button3;
		private Button button4;
		private Button button5;
		public AFN04_18()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			this.Times = this.TimePeriods.Split(new char[]
			{
				'~'
			});
			this.num = this.Times.Length;
			this.lb = new Label[this.num];
			this.cb = new ComboBox[this.num];
			int num = 15;
			int num2 = 15;
			int i = 0;
			checked
			{
				while (i < this.num)
				{
					this.lb[i] = new Label();
					this.cb[i] = new ComboBox();
					this.lb[i].Text = this.Times[i];
					this.cb[i].Items.Add("不控制");
					this.cb[i].Items.Add("控制1");
					this.cb[i].Items.Add("控制2");
					this.cb[i].Items.Add("保留");
					this.cb[i].DropDownStyle = ComboBoxStyle.DropDownList;
					this.cb[i].SelectedIndex = 0;
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
			}
		}
		private void Button2Click(object sender, EventArgs e)
		{
			checked
			{
				for (int i = 0; i < this.num; i++)
				{
					this.cb[i].SelectedIndex = 0;
				}
			}
		}
		private void Button3Click(object sender, EventArgs e)
		{
			checked
			{
				for (int i = 0; i < this.num; i++)
				{
					this.cb[i].SelectedIndex = 1;
				}
			}
		}
		private void Button4Click(object sender, EventArgs e)
		{
			checked
			{
				for (int i = 0; i < this.num; i++)
				{
					this.cb[i].SelectedIndex = 2;
				}
			}
		}
		private void Button5Click(object sender, EventArgs e)
		{
			checked
			{
				for (int i = 0; i < this.num; i++)
				{
					this.cb[i].SelectedIndex = 3;
				}
			}
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			checked
			{
				for (int i = 0; i < this.num; i += 4)
				{
					int num = 0;
					text += (this.cb[i].SelectedIndex << 6 | this.cb[i + 1].SelectedIndex << 4 | num | this.cb[i + 2].SelectedIndex << 2 | num | this.cb[i + 3].SelectedIndex).ToString("X2");
				}
				this.Data = DataConvert.ReverseStr(text);
			}
		}
		public override void SetText()
		{
			checked
			{
				if (!string.IsNullOrEmpty(this.Data))
				{
					string text = DataConvert.ReverseStr(this.Data);
					int num = 0;
					for (int i = 0; i < this.num; i += 4)
					{
						int num2 = DataConvert.HexToInt(text.Substring(num, 2));
						num += 2;
						int selectedIndex = num2 >> 6;
						this.cb[i].SelectedIndex = selectedIndex;
						int selectedIndex2 = (num2 & 48) >> 4;
						this.cb[i + 1].SelectedIndex = selectedIndex2;
						int selectedIndex3 = (num2 & 12) >> 2;
						this.cb[i + 2].SelectedIndex = selectedIndex3;
						int selectedIndex4 = num2 & 3;
						this.cb[i + 3].SelectedIndex = selectedIndex4;
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
			this.button5 = new Button();
			this.button4 = new Button();
			this.button3 = new Button();
			this.button2 = new Button();
			base.SuspendLayout();
			this.button5.Anchor = (AnchorStyles.Bottom | AnchorStyles.Right);
			this.button5.Location = new Point(534, 382);
			this.button5.Name = "button5";
			this.button5.Size = new Size(75, 23);
			this.button5.TabIndex = 28;
			this.button5.Text = "保留";
			this.button5.UseVisualStyleBackColor = true;
			this.button5.Click += new EventHandler(this.Button5Click);
			this.button4.Anchor = (AnchorStyles.Bottom | AnchorStyles.Right);
			this.button4.Location = new Point(453, 382);
			this.button4.Name = "button4";
			this.button4.Size = new Size(75, 23);
			this.button4.TabIndex = 27;
			this.button4.Text = "控制2";
			this.button4.UseVisualStyleBackColor = true;
			this.button4.Click += new EventHandler(this.Button4Click);
			this.button3.Anchor = (AnchorStyles.Bottom | AnchorStyles.Right);
			this.button3.Location = new Point(372, 382);
			this.button3.Name = "button3";
			this.button3.Size = new Size(75, 23);
			this.button3.TabIndex = 26;
			this.button3.Text = "控制1";
			this.button3.UseVisualStyleBackColor = true;
			this.button3.Click += new EventHandler(this.Button3Click);
			this.button2.Anchor = (AnchorStyles.Bottom | AnchorStyles.Right);
			this.button2.Location = new Point(291, 382);
			this.button2.Name = "button2";
			this.button2.Size = new Size(75, 23);
			this.button2.TabIndex = 25;
			this.button2.Text = "不控制";
			this.button2.UseVisualStyleBackColor = true;
			this.button2.Click += new EventHandler(this.Button2Click);
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(621, 417);
			base.Controls.Add(this.button5);
			base.Controls.Add(this.button4);
			base.Controls.Add(this.button3);
			base.Controls.Add(this.button2);
			base.Name = "AFN04_18";
			this.Text = "终端电能量费率时段和费率数";
			base.ResumeLayout(false);
		}
	}
}
