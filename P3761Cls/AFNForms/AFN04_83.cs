using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
	public class AFN04_83 : iForm
	{
		private IContainer components = null;
		private ComboBox comboBox3;
		private Label label2;
		public AFN04_83()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			this.comboBox3.SelectedIndex = 0;
		}
		protected override void GetText()
		{
			this.Data = "";
			string empty = string.Empty;
			int num = 0;
			switch (this.comboBox3.SelectedIndex)
			{
			case 0:
			case 1:
			case 2:
			case 3:
				num = this.comboBox3.SelectedIndex;
				break;

			case 4:
				num = 254;
				break;

			case 5:
				num = 255;
				break;
			}
			this.Data = num.ToString("X2");
		}
		public override void SetText()
		{
			if (!string.IsNullOrEmpty(this.Data))
			{
				string data = this.Data;
				int num = DataConvert.HexToInt(data);
				int num2 = num;
				switch (num2)
				{
				case 0:
				case 1:
				case 2:
				case 3:
					this.comboBox3.SelectedIndex = num;
					break;

				default:
					switch (num2)
					{
					case 254:
						this.comboBox3.SelectedIndex = 4;
						break;

					case 255:
						this.comboBox3.SelectedIndex = 5;
						break;
					}
					break;
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
			this.label2 = new Label();
			this.comboBox3 = new ComboBox();
			base.SuspendLayout();
			this.label2.AutoSize = true;
			this.label2.Location = new Point(35, 41);
			this.label2.Name = "label2";
			this.label2.Size = new Size(113, 12);
			this.label2.TabIndex = 21;
			this.label2.Text = "直流模拟量冻结密度";
			this.comboBox3.DropDownStyle = ComboBoxStyle.DropDownList;
			this.comboBox3.FormattingEnabled = true;
			this.comboBox3.Items.AddRange(new object[]
			{
				"无",
				"15分、30分、45分、0分",
				"30分、0分",
				"0分",
				"5分、10分、15分......、0分",
				"1分、2分、3分、......0分"
			});
			this.comboBox3.Location = new Point(154, 38);
			this.comboBox3.Name = "comboBox3";
			this.comboBox3.Size = new Size(172, 20);
			this.comboBox3.TabIndex = 31;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(373, 108);
			base.Controls.Add(this.comboBox3);
			base.Controls.Add(this.label2);
			base.Name = "AFN04_83";
			this.Text = "直流模拟量冻结参数";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
