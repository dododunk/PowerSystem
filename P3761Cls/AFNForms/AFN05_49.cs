using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN05_49 : iForm
	{
		private IContainer components = null;
		private Label label6;
		private ComboBox textBox3;
		public AFN05_49()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			checked
			{
				for (int i = 1; i <= 31; i++)
				{
					this.textBox3.Items.Add(i.ToString());
				}
				this.textBox3.SelectedIndex = 0;
			}
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			text += base.OperaSend(this.textBox3.Text, 1, "BIN");
			this.Data = text;
		}
		public override void SetText()
		{
			if (!string.IsNullOrEmpty(this.Data))
			{
				string data = this.Data;
				this.textBox3.Text = base.OperaRec(data, "BIN");
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
			this.textBox3 = new ComboBox();
			base.SuspendLayout();
			this.label6.AutoSize = true;
			this.label6.Location = new Point(24, 31);
			this.label6.Name = "label6";
			this.label6.Size = new Size(89, 12);
			this.label6.TabIndex = 8;
			this.label6.Text = "终端通信端口号";
			this.textBox3.DropDownStyle = ComboBoxStyle.DropDownList;
			this.textBox3.FormattingEnabled = true;
			this.textBox3.Location = new Point(119, 28);
			this.textBox3.Name = "textBox3";
			this.textBox3.Size = new Size(88, 20);
			this.textBox3.TabIndex = 22;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(234, 81);
			base.Controls.Add(this.textBox3);
			base.Controls.Add(this.label6);
			base.Name = "AFN05_49";
			this.Text = "命令指定通信端口暂停抄表";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
