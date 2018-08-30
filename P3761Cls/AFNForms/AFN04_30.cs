using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_30 : iForm
	{
		private IContainer components = null;
		private Label label6;
		private ComboBox comboBox1;
		public AFN04_30()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			this.comboBox1.SelectedIndex = 0;
		}
		protected override void GetText()
		{
			this.Data = "";
			string data = OperaSend(this.comboBox1.SelectedIndex.ToString(), 1, "BIN");
			this.Data = data;
		}
		public override void SetText()
		{
			if (!string.IsNullOrEmpty(this.Data))
			{
				this.comboBox1.SelectedIndex = int.Parse(base.OperaRec(this.Data, "BIN"));
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
			base.SuspendLayout();
			this.label6.AutoSize = true;
			this.label6.Location = new Point(23, 34);
			this.label6.Name = "label6";
			this.label6.Size = new Size(155, 12);
			this.label6.TabIndex = 8;
			this.label6.Text = "台区集中抄表停抄/投抄设置";
			this.comboBox1.DropDownStyle = ComboBoxStyle.DropDownList;
			this.comboBox1.FormattingEnabled = true;
			this.comboBox1.Items.AddRange(new object[]
			{
				"不停抄",
				"停抄"
			});
			this.comboBox1.Location = new Point(184, 32);
			this.comboBox1.Name = "comboBox1";
			this.comboBox1.Size = new Size(74, 20);
			this.comboBox1.TabIndex = 22;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(286, 87);
			base.Controls.Add(this.comboBox1);
			base.Controls.Add(this.label6);
			base.Name = "AFN04_30";
			this.Text = "台区集中抄表停抄/投抄设置";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
