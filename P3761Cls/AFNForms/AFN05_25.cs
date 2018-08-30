using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN05_25 : iForm
	{
		private IContainer components = null;
		private ComboBox textBox3;
		private Label label1;
		private Label label6;
		public AFN05_25()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			checked
			{
				for (int i = 0; i <= 48; i++)
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
			this.label1 = new Label();
			this.textBox3 = new ComboBox();
			base.SuspendLayout();
			this.label6.AutoSize = true;
			this.label6.Location = new Point(36, 32);
			this.label6.Name = "label6";
			this.label6.Size = new Size(77, 12);
			this.label6.TabIndex = 8;
			this.label6.Text = "保电持续时间";
			this.label1.AutoSize = true;
			this.label1.Location = new Point(209, 32);
			this.label1.Name = "label1";
			this.label1.Size = new Size(29, 12);
			this.label1.TabIndex = 23;
			this.label1.Text = "0.5h";
			this.textBox3.DropDownStyle = ComboBoxStyle.DropDownList;
			this.textBox3.FormattingEnabled = true;
			this.textBox3.Location = new Point(115, 29);
			this.textBox3.Name = "textBox3";
			this.textBox3.Size = new Size(88, 20);
			this.textBox3.TabIndex = 24;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(273, 78);
			base.Controls.Add(this.textBox3);
			base.Controls.Add(this.label1);
			base.Controls.Add(this.label6);
			base.Name = "AFN05_25";
			this.Text = "终端保电投入";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
