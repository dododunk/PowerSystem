using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_89 : iForm
	{
		private IContainer components = null;
		private Label label4;
		private ComboBox comboBox5;
		private Label label3;
		private ComboBox comboBox4;
		private Label label2;
		private ComboBox comboBox3;
		private Label label1;
		private ComboBox comboBox2;
		private ComboBox comboBox1;
		private Label label6;
		public AFN04_89()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			checked
			{
				for (int i = 0; i < 64; i++)
				{
					this.comboBox1.Items.Add(i.ToString());
				}
				this.comboBox1.SelectedIndex = 0;
				this.comboBox2.SelectedIndex = 0;
				this.comboBox3.SelectedIndex = 2;
				this.comboBox5.SelectedIndex = 3;
			}
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = this.comboBox1.SelectedIndex.ToString("X2");
			text += this.comboBox2.SelectedIndex.ToString("X2");
			text += this.comboBox3.SelectedIndex.ToString("X2");
			text += base.OperaSend(this.comboBox4.Text, 2, "BIN");
			text += this.comboBox5.SelectedIndex.ToString("X2");
			text += "0000";
			this.Data = text;
		}
		public override void SetText()
		{
			checked
			{
				if (!string.IsNullOrEmpty(this.Data))
				{
					string data = this.Data;
					int num = 0;
					this.comboBox1.SelectedIndex = int.Parse(base.OperaRec(data.Substring(num, 2), "BIN"));
					num += 2;
					this.comboBox2.SelectedIndex = int.Parse(base.OperaRec(data.Substring(num, 2), "BIN"));
					num += 2;
					this.comboBox3.SelectedIndex = int.Parse(base.OperaRec(data.Substring(num, 2), "BIN"));
					num += 2;
					this.comboBox4.Text = base.OperaRec(data.Substring(num, 4), "BIN");
					num += 4;
					this.comboBox5.SelectedIndex = int.Parse(base.OperaRec(data.Substring(num, 2), "BIN"));
					num += 2;
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
			this.label6 = new Label();
			this.comboBox1 = new ComboBox();
			this.comboBox2 = new ComboBox();
			this.label1 = new Label();
			this.comboBox3 = new ComboBox();
			this.label2 = new Label();
			this.comboBox4 = new ComboBox();
			this.label3 = new Label();
			this.comboBox5 = new ComboBox();
			this.label4 = new Label();
			base.SuspendLayout();
			this.label6.AutoSize = true;
			this.label6.Font = new Font("Arial", 9f);
			this.label6.Location = new Point(68, 27);
			this.label6.Name = "label6";
			this.label6.Size = new Size(67, 15);
			this.label6.TabIndex = 46;
			this.label6.Text = "无线信道号";
			this.comboBox1.DropDownStyle = ComboBoxStyle.DropDownList;
			this.comboBox1.FormattingEnabled = true;
			this.comboBox1.Location = new Point(141, 26);
			this.comboBox1.Name = "comboBox1";
			this.comboBox1.Size = new Size(137, 20);
			this.comboBox1.TabIndex = 50;
			this.comboBox2.DropDownStyle = ComboBoxStyle.DropDownList;
			this.comboBox2.FormattingEnabled = true;
			this.comboBox2.Items.AddRange(new object[]
			{
				"最大发射功率",
				"等级1发射功率",
				"等级2发射功率",
				"等级3发射功率",
				"等级4发射功率",
				"等级5发射功率",
				"等级6发射功率",
				"最小发射功率"
			});
			this.comboBox2.Location = new Point(141, 52);
			this.comboBox2.Name = "comboBox2";
			this.comboBox2.Size = new Size(137, 20);
			this.comboBox2.TabIndex = 52;
			this.label1.AutoSize = true;
			this.label1.Font = new Font("Arial", 9f);
			this.label1.Location = new Point(20, 53);
			this.label1.Name = "label1";
			this.label1.Size = new Size(115, 15);
			this.label1.TabIndex = 51;
			this.label1.Text = "主无线模块发射功率";
			this.comboBox3.DropDownStyle = ComboBoxStyle.DropDownList;
			this.comboBox3.FormattingEnabled = true;
			this.comboBox3.Items.AddRange(new object[]
			{
				"",
				"1200",
				"2400",
				"4800",
				"7200",
				"9600",
				"19200",
				"38400"
			});
			this.comboBox3.Location = new Point(141, 78);
			this.comboBox3.Name = "comboBox3";
			this.comboBox3.Size = new Size(137, 20);
			this.comboBox3.TabIndex = 54;
			this.label2.AutoSize = true;
			this.label2.Font = new Font("Arial", 9f);
			this.label2.Location = new Point(44, 79);
			this.label2.Name = "label2";
			this.label2.Size = new Size(91, 15);
			this.label2.TabIndex = 53;
			this.label2.Text = "无线空中波特率";
			this.comboBox4.FormattingEnabled = true;
			this.comboBox4.Location = new Point(141, 104);
			this.comboBox4.Name = "comboBox4";
			this.comboBox4.Size = new Size(137, 20);
			this.comboBox4.TabIndex = 56;
			this.comboBox4.Text = "0";
			this.label3.AutoSize = true;
			this.label3.Font = new Font("Arial", 9f);
			this.label3.Location = new Point(56, 105);
			this.label3.Name = "label3";
			this.label3.Size = new Size(79, 15);
			this.label3.TabIndex = 55;
			this.label3.Text = "无线网络标识";
			this.comboBox5.DropDownStyle = ComboBoxStyle.DropDownList;
			this.comboBox5.FormattingEnabled = true;
			this.comboBox5.Items.AddRange(new object[]
			{
				"不使用路由",
				"使用固定路由",
				"使用实时自动路由",
				"使用源路由"
			});
			this.comboBox5.Location = new Point(141, 130);
			this.comboBox5.Name = "comboBox5";
			this.comboBox5.Size = new Size(137, 20);
			this.comboBox5.TabIndex = 58;
			this.label4.AutoSize = true;
			this.label4.Font = new Font("Arial", 9f);
			this.label4.Location = new Point(80, 131);
			this.label4.Name = "label4";
			this.label4.Size = new Size(55, 15);
			this.label4.TabIndex = 57;
			this.label4.Text = "路由方式";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(303, 182);
			base.Controls.Add(this.comboBox5);
			base.Controls.Add(this.label4);
			base.Controls.Add(this.comboBox4);
			base.Controls.Add(this.label3);
			base.Controls.Add(this.comboBox3);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.comboBox2);
			base.Controls.Add(this.label1);
			base.Controls.Add(this.comboBox1);
			base.Controls.Add(this.label6);
			base.Name = "AFN04_89";
			this.Text = "设置无线通信参数";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
