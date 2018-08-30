using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
	public class AFN05_41 : iForm
	{
		private ComboBox[] t1 = new ComboBox[16];
		private IContainer components = null;
		private Label label38;
		private Label label36;
		private Label label34;
		private Label label32;
		private Label label30;
		private Label label28;
		private Label label26;
		private Label label8;
		private Label label24;
		private Label label22;
		private Label label20;
		private Label label18;
		private Label label16;
		private Label label14;
		private Label label12;
		private Label label10;
		public AFN05_41()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			int num = 20;
			int left = 80;
			int i = 0;
			checked
			{
				while (i < 16)
				{
					if (i % 2 == 0)
					{
						left = 80;
					}
					if (i % 2 == 1)
					{
						left = 300;
					}
					this.t1[i] = new ComboBox();
					this.t1[i].Top = num;
					this.t1[i].Left = left;
					this.t1[i].Parent = this;
					this.t1[i].Items.Add("保持");
					this.t1[i].Items.Add("投入");
					this.t1[i].DropDownStyle = ComboBoxStyle.DropDownList;
					this.t1[i].SelectedIndex = 0;
					i++;
					if (i % 2 == 0)
					{
						num += 23;
					}
				}
			}
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			int num = 0;
			checked
			{
				for (int i = 0; i < 16; i++)
				{
					num |= this.t1[i].SelectedIndex << i;
				}
				text += DataConvert.ReverseStr(num.ToString("X2"));
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
					int num = DataConvert.HexToInt(DataConvert.ReverseStr(data));
					for (int i = 0; i < 16; i++)
					{
						this.t1[i].SelectedIndex = (num & 1 << i) >> i;
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
			this.label8 = new Label();
			this.label26 = new Label();
			this.label28 = new Label();
			this.label30 = new Label();
			this.label10 = new Label();
			this.label12 = new Label();
			this.label14 = new Label();
			this.label16 = new Label();
			this.label18 = new Label();
			this.label20 = new Label();
			this.label22 = new Label();
			this.label24 = new Label();
			this.label32 = new Label();
			this.label34 = new Label();
			this.label36 = new Label();
			this.label38 = new Label();
			base.SuspendLayout();
			this.label8.AutoSize = true;
			this.label8.Location = new Point(24, 21);
			this.label8.Name = "label8";
			this.label8.Size = new Size(47, 12);
			this.label8.TabIndex = 76;
			this.label8.Text = "电容器1";
			this.label26.AutoSize = true;
			this.label26.Location = new Point(244, 21);
			this.label26.Name = "label26";
			this.label26.Size = new Size(47, 12);
			this.label26.TabIndex = 79;
			this.label26.Text = "电容器2";
			this.label28.AutoSize = true;
			this.label28.Location = new Point(244, 44);
			this.label28.Name = "label28";
			this.label28.Size = new Size(47, 12);
			this.label28.TabIndex = 85;
			this.label28.Text = "电容器4";
			this.label30.AutoSize = true;
			this.label30.Location = new Point(24, 44);
			this.label30.Name = "label30";
			this.label30.Size = new Size(47, 12);
			this.label30.TabIndex = 82;
			this.label30.Text = "电容器3";
			this.label10.AutoSize = true;
			this.label10.Location = new Point(244, 67);
			this.label10.Name = "label10";
			this.label10.Size = new Size(47, 12);
			this.label10.TabIndex = 91;
			this.label10.Text = "电容器6";
			this.label12.AutoSize = true;
			this.label12.Location = new Point(24, 67);
			this.label12.Name = "label12";
			this.label12.Size = new Size(47, 12);
			this.label12.TabIndex = 88;
			this.label12.Text = "电容器5";
			this.label14.AutoSize = true;
			this.label14.Location = new Point(244, 90);
			this.label14.Name = "label14";
			this.label14.Size = new Size(47, 12);
			this.label14.TabIndex = 97;
			this.label14.Text = "电容器8";
			this.label16.AutoSize = true;
			this.label16.Location = new Point(24, 90);
			this.label16.Name = "label16";
			this.label16.Size = new Size(47, 12);
			this.label16.TabIndex = 94;
			this.label16.Text = "电容器7";
			this.label18.AutoSize = true;
			this.label18.Location = new Point(244, 113);
			this.label18.Name = "label18";
			this.label18.Size = new Size(53, 12);
			this.label18.TabIndex = 103;
			this.label18.Text = "电容器10";
			this.label20.AutoSize = true;
			this.label20.Location = new Point(24, 113);
			this.label20.Name = "label20";
			this.label20.Size = new Size(47, 12);
			this.label20.TabIndex = 100;
			this.label20.Text = "电容器9";
			this.label22.AutoSize = true;
			this.label22.Location = new Point(244, 182);
			this.label22.Name = "label22";
			this.label22.Size = new Size(53, 12);
			this.label22.TabIndex = 121;
			this.label22.Text = "电容器16";
			this.label24.AutoSize = true;
			this.label24.Location = new Point(24, 182);
			this.label24.Name = "label24";
			this.label24.Size = new Size(53, 12);
			this.label24.TabIndex = 118;
			this.label24.Text = "电容器15";
			this.label32.AutoSize = true;
			this.label32.Location = new Point(244, 159);
			this.label32.Name = "label32";
			this.label32.Size = new Size(53, 12);
			this.label32.TabIndex = 115;
			this.label32.Text = "电容器14";
			this.label34.AutoSize = true;
			this.label34.Location = new Point(24, 159);
			this.label34.Name = "label34";
			this.label34.Size = new Size(53, 12);
			this.label34.TabIndex = 112;
			this.label34.Text = "电容器13";
			this.label36.AutoSize = true;
			this.label36.Location = new Point(244, 136);
			this.label36.Name = "label36";
			this.label36.Size = new Size(53, 12);
			this.label36.TabIndex = 109;
			this.label36.Text = "电容器12";
			this.label38.AutoSize = true;
			this.label38.Location = new Point(24, 136);
			this.label38.Name = "label38";
			this.label38.Size = new Size(53, 12);
			this.label38.TabIndex = 106;
			this.label38.Text = "电容器11";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(445, 223);
			base.Controls.Add(this.label22);
			base.Controls.Add(this.label24);
			base.Controls.Add(this.label32);
			base.Controls.Add(this.label34);
			base.Controls.Add(this.label36);
			base.Controls.Add(this.label38);
			base.Controls.Add(this.label18);
			base.Controls.Add(this.label20);
			base.Controls.Add(this.label14);
			base.Controls.Add(this.label16);
			base.Controls.Add(this.label10);
			base.Controls.Add(this.label12);
			base.Controls.Add(this.label28);
			base.Controls.Add(this.label30);
			base.Controls.Add(this.label26);
			base.Controls.Add(this.label8);
			base.Name = "AFN05_41";
			this.Text = "电容器控制投入";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
