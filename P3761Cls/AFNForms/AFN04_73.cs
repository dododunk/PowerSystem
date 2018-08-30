using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
	public class AFN04_73 : iForm
	{
		private Label[] lb = new Label[16];
		private ComboBox[] cb = new ComboBox[16];
		private TextBox[] tb = new TextBox[16];
		private Button[] bt = new Button[16];
		private IContainer components = null;
		private Label label2;
		private Label label1;
		private Label label4;
		public AFN04_73()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			int num = 50;
			checked
			{
				for (int i = 0; i < 16; i++)
				{
					this.lb[i] = new Label();
					this.cb[i] = new ComboBox();
					this.tb[i] = new TextBox();
					this.bt[i] = new Button();
					this.bt[i].Width = 16;
					this.tb[i].ReadOnly = true;
					this.tb[i].Text = "0000";
					this.bt[i].Name = "bt" + i.ToString("D2");
					this.lb[i].Text = "第" + (i + 1).ToString() + "组";
					this.cb[i].Items.Add("共补");
					this.cb[i].Items.Add("分补A");
					this.cb[i].Items.Add("分补B");
					this.cb[i].Items.Add("分补C");
					this.cb[i].Items.Add("分补AB");
					this.cb[i].Items.Add("分补AC");
					this.cb[i].Items.Add("分补BC");
					this.cb[i].DropDownStyle = ComboBoxStyle.DropDownList;
					this.cb[i].SelectedIndex = 0;
					this.lb[i].AutoSize = true;
					this.lb[i].Parent = this;
					this.cb[i].Parent = this;
					this.tb[i].Parent = this;
					this.bt[i].Parent = this;
					this.bt[i].Click += new EventHandler(this.ButtonClick);
					this.lb[i].Top = num;
					this.cb[i].Top = num - 1;
					this.tb[i].Top = num - 1;
					this.bt[i].Top = num - 2;
					num += 25;
					this.lb[i].Left = 50;
					this.cb[i].Left = 100;
					this.tb[i].Left = 230;
					this.bt[i].Left = this.tb[i].Left + this.tb[i].Width + 1;
				}
			}
		}
		private void ButtonClick(object sender, EventArgs e)
		{
			int num = int.Parse(((Button)sender).Name.Substring(2, 2));
			iForm iForm = new A2();
			iForm.Data = this.tb[num].Text;
			iForm.SetText();
			iForm.ShowDialog();
			this.tb[num].Text = iForm.Data;
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			checked
			{
				for (int i = 0; i < 16; i++)
				{
					text += (((this.cb[i].Text.IndexOf("共补") >= 0) ? 1 : 2) << 6 | ((this.cb[i].Text.IndexOf("A") >= 0) ? 1 : 0) | ((this.cb[i].Text.IndexOf("B") >= 0) ? 1 : 0) << 1 | ((this.cb[i].Text.IndexOf("C") >= 0) ? 1 : 0) << 2).ToString("X2");
					text += this.tb[i].Text;
				}
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
					int num = 0;
					for (int i = 0; i < 16; i++)
					{
						int num2 = DataConvert.HexToInt(data.Substring(num, 2));
						string text = (num2 >> 6 == 1) ? "共补" : "分补";
						text += (((num2 & 1) == 1) ? "A" : "");
						text += (((num2 & 2) >> 1 == 1) ? "B" : "");
						text += (((num2 & 4) >> 2 == 1) ? "C" : "");
						this.cb[i].Text = text;
						num += 2;
						this.tb[i].Text = data.Substring(num, 4);
						num += 4;
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
			this.label4 = new Label();
			this.label1 = new Label();
			this.label2 = new Label();
			base.SuspendLayout();
			this.label4.AutoSize = true;
			this.label4.Font = new Font("Arial", 9f);
			this.label4.Location = new Point(52, 18);
			this.label4.Name = "label4";
			this.label4.Size = new Size(31, 15);
			this.label4.TabIndex = 49;
			this.label4.Text = "组号";
			this.label1.AutoSize = true;
			this.label1.Font = new Font("Arial", 9f);
			this.label1.Location = new Point(141, 18);
			this.label1.Name = "label1";
			this.label1.Size = new Size(55, 15);
			this.label1.TabIndex = 50;
			this.label1.Text = "补偿方式";
			this.label2.AutoSize = true;
			this.label2.Font = new Font("Arial", 9f);
			this.label2.Location = new Point(271, 18);
			this.label2.Name = "label2";
			this.label2.Size = new Size(43, 15);
			this.label2.TabIndex = 51;
			this.label2.Text = "补偿值";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(389, 469);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.label1);
			base.Controls.Add(this.label4);
			base.Name = "AFN04_73";
			this.Text = "电容器参数";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
