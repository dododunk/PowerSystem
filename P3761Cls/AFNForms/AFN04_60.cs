using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_60 : iForm
	{
		private TextBox[] t1 = new TextBox[18];
		private TextBox[] t2 = new TextBox[18];
		private Button[] b1 = new Button[18];
		private Button[] b2 = new Button[18];
		private IContainer components = null;
		private Button button4;
		private Button button3;
		private Button button2;
		private Button button1;
		private Label label82;
		private TextBox textBox41;
		private Label label78;
		private Label label76;
		private Label label74;
		private Label label72;
		private Label label70;
		private Label label68;
		private Label label66;
		private Label label64;
		private Label label62;
		private Label label60;
		private Label label58;
		private Label label56;
		private Label label54;
		private Label label52;
		private Label label50;
		private Label label48;
		private Label label46;
		private Label label44;
		private Label label42;
		private Label label40;
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
		private Label label6;
		private TextBox textBox2;
		private Label label2;
		private TextBox textBox1;
		private Label label3;
		private TextBox textBox5;
		public AFN04_60()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			int num = 55;
			int num2 = 165;
			int i = 0;
			checked
			{
				while (i < 18)
				{
					if (i % 2 == 0)
					{
						num2 = 165;
					}
					if (i % 2 == 1)
					{
						num2 = 397;
					}
					this.t1[i] = new TextBox();
					this.t1[i].Width = 55;
					this.t1[i].Top = num;
					this.t1[i].Left = num2;
					this.t1[i].Parent = this;
					this.t1[i].Text = "0000";
					this.t1[i].ReadOnly = true;
					this.b1[i] = new Button();
					this.b1[i].Width = 16;
					this.b1[i].Height = 23;
					this.b1[i].Top = num;
					this.b1[i].Left = num2 + 55;
					this.b1[i].Parent = this;
					this.b1[i].Text = "";
					this.b1[i].Name = "B1" + i.ToString();
					this.b1[i].Click += new EventHandler(this.ButtonAClick);
					i++;
					if (i % 2 == 0)
					{
						num += 23;
					}
				}
				num = 300;
				num2 = 165;
				i = 0;
				while (i < 18)
				{
					if (i % 2 == 0)
					{
						num2 = 165;
					}
					if (i % 2 == 1)
					{
						num2 = 397;
					}
					this.t2[i] = new TextBox();
					this.t2[i].Width = 55;
					this.t2[i].Top = num;
					this.t2[i].Left = num2;
					this.t2[i].Parent = this;
					this.t2[i].Text = "0000";
					this.t2[i].ReadOnly = true;
					this.b2[i] = new Button();
					this.b2[i].Width = 16;
					this.b2[i].Height = 23;
					this.b2[i].Top = num;
					this.b2[i].Left = num2 + 55;
					this.b2[i].Parent = this;
					this.b2[i].Text = "";
					this.b2[i].Name = "B2" + i.ToString();
					this.b2[i].Click += new EventHandler(this.ButtonBClick);
					i++;
					if (i % 2 == 0)
					{
						num += 23;
					}
				}
			}
		}
		private string GetText(string ftext)
		{
			return ftext.Substring(2, checked(ftext.Length - 2));
		}
		private void ButtonAClick(object sender, EventArgs e)
		{
			int num = int.Parse(this.GetText(((Button)sender).Name));
			iForm iForm = new A5();
			iForm.Data = this.t1[num].Text;
			iForm.SetText();
			iForm.ShowDialog();
			this.t1[num].Text = iForm.Data;
		}
		private void ButtonBClick(object sender, EventArgs e)
		{
			int num = int.Parse(this.GetText(((Button)sender).Name));
			iForm iForm = new A6();
			iForm.Data = this.t2[num].Text;
			iForm.SetText();
			iForm.ShowDialog();
			this.t2[num].Text = iForm.Data;
		}
		protected override void GetText()
		{
			this.Data = "";
			string text = string.Empty;
			text += this.textBox5.Text;
			text += this.textBox1.Text;
			text += this.textBox2.Text;
			checked
			{
				for (int i = 0; i < 18; i++)
				{
					text += this.t1[i].Text;
				}
				text += this.textBox41.Text;
				for (int i = 0; i < 18; i++)
				{
					text += this.t2[i].Text;
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
					this.textBox5.Text = data.Substring(num, 4);
					num += 4;
					this.textBox1.Text = data.Substring(num, 4);
					num += 4;
					this.textBox2.Text = data.Substring(num, 4);
					num += 4;
					for (int i = 0; i < 18; i++)
					{
						this.t1[i].Text = data.Substring(num, 4);
						num += 4;
					}
					this.textBox41.Text = data.Substring(num, 4);
					num += 4;
					for (int i = 0; i < 18; i++)
					{
						this.t2[i].Text = data.Substring(num, 4);
						num += 4;
					}
				}
			}
		}
		private void Button1Click(object sender, EventArgs e)
		{
			iForm iForm = new A5();
			iForm.Data = this.textBox5.Text;
			iForm.SetText();
			iForm.ShowDialog();
			this.textBox5.Text = iForm.Data;
		}
		private void Button2Click(object sender, EventArgs e)
		{
			iForm iForm = new A5();
			iForm.Data = this.textBox1.Text;
			iForm.SetText();
			iForm.ShowDialog();
			this.textBox1.Text = iForm.Data;
		}
		private void Button4Click(object sender, EventArgs e)
		{
			iForm iForm = new A5();
			iForm.Data = this.textBox2.Text;
			iForm.SetText();
			iForm.ShowDialog();
			this.textBox2.Text = iForm.Data;
		}
		private void Button3Click(object sender, EventArgs e)
		{
			iForm iForm = new A6();
			iForm.Data = this.textBox41.Text;
			iForm.SetText();
			iForm.ShowDialog();
			this.textBox41.Text = iForm.Data;
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
			this.textBox5 = new TextBox();
			this.label3 = new Label();
			this.textBox1 = new TextBox();
			this.label2 = new Label();
			this.textBox2 = new TextBox();
			this.label6 = new Label();
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
			this.label40 = new Label();
			this.label42 = new Label();
			this.label44 = new Label();
			this.label46 = new Label();
			this.label48 = new Label();
			this.label50 = new Label();
			this.label52 = new Label();
			this.label54 = new Label();
			this.label56 = new Label();
			this.label58 = new Label();
			this.label60 = new Label();
			this.label62 = new Label();
			this.label64 = new Label();
			this.label66 = new Label();
			this.label68 = new Label();
			this.label70 = new Label();
			this.label72 = new Label();
			this.label74 = new Label();
			this.label76 = new Label();
			this.label78 = new Label();
			this.textBox41 = new TextBox();
			this.label82 = new Label();
			this.button1 = new Button();
			this.button2 = new Button();
			this.button3 = new Button();
			this.button4 = new Button();
			base.SuspendLayout();
			this.textBox5.Location = new Point(165, 6);
			this.textBox5.Name = "textBox5";
			this.textBox5.ReadOnly = true;
			this.textBox5.Size = new Size(55, 21);
			this.textBox5.TabIndex = 26;
			this.textBox5.Text = "0000";
			this.label3.AutoSize = true;
			this.label3.Location = new Point(22, 9);
			this.label3.Name = "label3";
			this.label3.Size = new Size(125, 12);
			this.label3.TabIndex = 25;
			this.label3.Text = "总畸变电压含有率上限";
			this.textBox1.Location = new Point(165, 32);
			this.textBox1.Name = "textBox1";
			this.textBox1.ReadOnly = true;
			this.textBox1.Size = new Size(55, 21);
			this.textBox1.TabIndex = 41;
			this.textBox1.Text = "0000";
			this.label2.AutoSize = true;
			this.label2.Location = new Point(22, 36);
			this.label2.Name = "label2";
			this.label2.Size = new Size(137, 12);
			this.label2.TabIndex = 40;
			this.label2.Text = "奇次谐波电压含有率上限";
			this.textBox2.Location = new Point(397, 32);
			this.textBox2.Name = "textBox2";
			this.textBox2.ReadOnly = true;
			this.textBox2.Size = new Size(55, 21);
			this.textBox2.TabIndex = 74;
			this.textBox2.Text = "0000";
			this.label6.AutoSize = true;
			this.label6.Location = new Point(254, 36);
			this.label6.Name = "label6";
			this.label6.Size = new Size(137, 12);
			this.label6.TabIndex = 73;
			this.label6.Text = "偶次谐波电压含有率上限";
			this.label8.AutoSize = true;
			this.label8.Location = new Point(22, 59);
			this.label8.Name = "label8";
			this.label8.Size = new Size(131, 12);
			this.label8.TabIndex = 76;
			this.label8.Text = "2次谐波电压含有率上限";
			this.label26.AutoSize = true;
			this.label26.Location = new Point(254, 59);
			this.label26.Name = "label26";
			this.label26.Size = new Size(131, 12);
			this.label26.TabIndex = 79;
			this.label26.Text = "3次谐波电压含有率上限";
			this.label28.AutoSize = true;
			this.label28.Location = new Point(254, 82);
			this.label28.Name = "label28";
			this.label28.Size = new Size(131, 12);
			this.label28.TabIndex = 85;
			this.label28.Text = "5次谐波电压含有率上限";
			this.label30.AutoSize = true;
			this.label30.Location = new Point(22, 82);
			this.label30.Name = "label30";
			this.label30.Size = new Size(131, 12);
			this.label30.TabIndex = 82;
			this.label30.Text = "4次谐波电压含有率上限";
			this.label10.AutoSize = true;
			this.label10.Location = new Point(254, 105);
			this.label10.Name = "label10";
			this.label10.Size = new Size(131, 12);
			this.label10.TabIndex = 91;
			this.label10.Text = "7次谐波电压含有率上限";
			this.label12.AutoSize = true;
			this.label12.Location = new Point(22, 105);
			this.label12.Name = "label12";
			this.label12.Size = new Size(131, 12);
			this.label12.TabIndex = 88;
			this.label12.Text = "6次谐波电压含有率上限";
			this.label14.AutoSize = true;
			this.label14.Location = new Point(254, 128);
			this.label14.Name = "label14";
			this.label14.Size = new Size(131, 12);
			this.label14.TabIndex = 97;
			this.label14.Text = "9次谐波电压含有率上限";
			this.label16.AutoSize = true;
			this.label16.Location = new Point(22, 128);
			this.label16.Name = "label16";
			this.label16.Size = new Size(131, 12);
			this.label16.TabIndex = 94;
			this.label16.Text = "8次谐波电压含有率上限";
			this.label18.AutoSize = true;
			this.label18.Location = new Point(254, 151);
			this.label18.Name = "label18";
			this.label18.Size = new Size(137, 12);
			this.label18.TabIndex = 103;
			this.label18.Text = "11次谐波电压含有率上限";
			this.label20.AutoSize = true;
			this.label20.Location = new Point(22, 151);
			this.label20.Name = "label20";
			this.label20.Size = new Size(137, 12);
			this.label20.TabIndex = 100;
			this.label20.Text = "10次谐波电压含有率上限";
			this.label22.AutoSize = true;
			this.label22.Location = new Point(254, 220);
			this.label22.Name = "label22";
			this.label22.Size = new Size(137, 12);
			this.label22.TabIndex = 121;
			this.label22.Text = "17次谐波电压含有率上限";
			this.label24.AutoSize = true;
			this.label24.Location = new Point(22, 220);
			this.label24.Name = "label24";
			this.label24.Size = new Size(137, 12);
			this.label24.TabIndex = 118;
			this.label24.Text = "16次谐波电压含有率上限";
			this.label32.AutoSize = true;
			this.label32.Location = new Point(254, 197);
			this.label32.Name = "label32";
			this.label32.Size = new Size(137, 12);
			this.label32.TabIndex = 115;
			this.label32.Text = "15次谐波电压含有率上限";
			this.label34.AutoSize = true;
			this.label34.Location = new Point(22, 197);
			this.label34.Name = "label34";
			this.label34.Size = new Size(137, 12);
			this.label34.TabIndex = 112;
			this.label34.Text = "14次谐波电压含有率上限";
			this.label36.AutoSize = true;
			this.label36.Location = new Point(254, 174);
			this.label36.Name = "label36";
			this.label36.Size = new Size(137, 12);
			this.label36.TabIndex = 109;
			this.label36.Text = "13次谐波电压含有率上限";
			this.label38.AutoSize = true;
			this.label38.Location = new Point(22, 174);
			this.label38.Name = "label38";
			this.label38.Size = new Size(137, 12);
			this.label38.TabIndex = 106;
			this.label38.Text = "12次谐波电压含有率上限";
			this.label40.AutoSize = true;
			this.label40.Location = new Point(254, 243);
			this.label40.Name = "label40";
			this.label40.Size = new Size(137, 12);
			this.label40.TabIndex = 127;
			this.label40.Text = "19次谐波电压含有率上限";
			this.label42.AutoSize = true;
			this.label42.Location = new Point(22, 243);
			this.label42.Name = "label42";
			this.label42.Size = new Size(137, 12);
			this.label42.TabIndex = 124;
			this.label42.Text = "18次谐波电压含有率上限";
			this.label44.AutoSize = true;
			this.label44.Location = new Point(254, 486);
			this.label44.Name = "label44";
			this.label44.Size = new Size(137, 12);
			this.label44.TabIndex = 187;
			this.label44.Text = "19次谐波电压含有率上限";
			this.label46.AutoSize = true;
			this.label46.Location = new Point(22, 486);
			this.label46.Name = "label46";
			this.label46.Size = new Size(137, 12);
			this.label46.TabIndex = 184;
			this.label46.Text = "18次谐波电压含有率上限";
			this.label48.AutoSize = true;
			this.label48.Location = new Point(254, 463);
			this.label48.Name = "label48";
			this.label48.Size = new Size(137, 12);
			this.label48.TabIndex = 181;
			this.label48.Text = "17次谐波电压含有率上限";
			this.label50.AutoSize = true;
			this.label50.Location = new Point(22, 463);
			this.label50.Name = "label50";
			this.label50.Size = new Size(137, 12);
			this.label50.TabIndex = 178;
			this.label50.Text = "16次谐波电压含有率上限";
			this.label52.AutoSize = true;
			this.label52.Location = new Point(254, 440);
			this.label52.Name = "label52";
			this.label52.Size = new Size(137, 12);
			this.label52.TabIndex = 175;
			this.label52.Text = "15次谐波电压含有率上限";
			this.label54.AutoSize = true;
			this.label54.Location = new Point(22, 440);
			this.label54.Name = "label54";
			this.label54.Size = new Size(137, 12);
			this.label54.TabIndex = 172;
			this.label54.Text = "14次谐波电压含有率上限";
			this.label56.AutoSize = true;
			this.label56.Location = new Point(254, 417);
			this.label56.Name = "label56";
			this.label56.Size = new Size(137, 12);
			this.label56.TabIndex = 169;
			this.label56.Text = "13次谐波电压含有率上限";
			this.label58.AutoSize = true;
			this.label58.Location = new Point(22, 417);
			this.label58.Name = "label58";
			this.label58.Size = new Size(137, 12);
			this.label58.TabIndex = 166;
			this.label58.Text = "12次谐波电压含有率上限";
			this.label60.AutoSize = true;
			this.label60.Location = new Point(254, 394);
			this.label60.Name = "label60";
			this.label60.Size = new Size(137, 12);
			this.label60.TabIndex = 163;
			this.label60.Text = "11次谐波电压含有率上限";
			this.label62.AutoSize = true;
			this.label62.Location = new Point(22, 394);
			this.label62.Name = "label62";
			this.label62.Size = new Size(137, 12);
			this.label62.TabIndex = 160;
			this.label62.Text = "10次谐波电压含有率上限";
			this.label64.AutoSize = true;
			this.label64.Location = new Point(254, 371);
			this.label64.Name = "label64";
			this.label64.Size = new Size(131, 12);
			this.label64.TabIndex = 157;
			this.label64.Text = "9次谐波电压含有率上限";
			this.label66.AutoSize = true;
			this.label66.Location = new Point(22, 371);
			this.label66.Name = "label66";
			this.label66.Size = new Size(131, 12);
			this.label66.TabIndex = 154;
			this.label66.Text = "8次谐波电压含有率上限";
			this.label68.AutoSize = true;
			this.label68.Location = new Point(254, 348);
			this.label68.Name = "label68";
			this.label68.Size = new Size(131, 12);
			this.label68.TabIndex = 151;
			this.label68.Text = "7次谐波电压含有率上限";
			this.label70.AutoSize = true;
			this.label70.Location = new Point(22, 348);
			this.label70.Name = "label70";
			this.label70.Size = new Size(131, 12);
			this.label70.TabIndex = 148;
			this.label70.Text = "6次谐波电压含有率上限";
			this.label72.AutoSize = true;
			this.label72.Location = new Point(254, 325);
			this.label72.Name = "label72";
			this.label72.Size = new Size(131, 12);
			this.label72.TabIndex = 145;
			this.label72.Text = "5次谐波电压含有率上限";
			this.label74.AutoSize = true;
			this.label74.Location = new Point(22, 325);
			this.label74.Name = "label74";
			this.label74.Size = new Size(131, 12);
			this.label74.TabIndex = 142;
			this.label74.Text = "4次谐波电压含有率上限";
			this.label76.AutoSize = true;
			this.label76.Location = new Point(254, 302);
			this.label76.Name = "label76";
			this.label76.Size = new Size(131, 12);
			this.label76.TabIndex = 139;
			this.label76.Text = "3次谐波电压含有率上限";
			this.label78.AutoSize = true;
			this.label78.Location = new Point(22, 302);
			this.label78.Name = "label78";
			this.label78.Size = new Size(131, 12);
			this.label78.TabIndex = 136;
			this.label78.Text = "2次谐波电压含有率上限";
			this.textBox41.Location = new Point(165, 276);
			this.textBox41.Name = "textBox41";
			this.textBox41.ReadOnly = true;
			this.textBox41.Size = new Size(55, 21);
			this.textBox41.TabIndex = 131;
			this.textBox41.Text = "0000";
			this.label82.AutoSize = true;
			this.label82.Location = new Point(22, 279);
			this.label82.Name = "label82";
			this.label82.Size = new Size(125, 12);
			this.label82.TabIndex = 130;
			this.label82.Text = "总畸变电流有效值上限";
			this.button1.Location = new Point(220, 5);
			this.button1.Name = "button1";
			this.button1.Size = new Size(16, 23);
			this.button1.TabIndex = 188;
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new EventHandler(this.Button1Click);
			this.button2.Location = new Point(220, 31);
			this.button2.Name = "button2";
			this.button2.Size = new Size(16, 23);
			this.button2.TabIndex = 189;
			this.button2.UseVisualStyleBackColor = true;
			this.button2.Click += new EventHandler(this.Button2Click);
			this.button3.Location = new Point(220, 275);
			this.button3.Name = "button3";
			this.button3.Size = new Size(16, 23);
			this.button3.TabIndex = 190;
			this.button3.UseVisualStyleBackColor = true;
			this.button3.Click += new EventHandler(this.Button3Click);
			this.button4.Location = new Point(452, 31);
			this.button4.Name = "button4";
			this.button4.Size = new Size(16, 23);
			this.button4.TabIndex = 191;
			this.button4.UseVisualStyleBackColor = true;
			this.button4.Click += new EventHandler(this.Button4Click);
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(488, 518);
			base.Controls.Add(this.button4);
			base.Controls.Add(this.button3);
			base.Controls.Add(this.button2);
			base.Controls.Add(this.button1);
			base.Controls.Add(this.label44);
			base.Controls.Add(this.label46);
			base.Controls.Add(this.label48);
			base.Controls.Add(this.label50);
			base.Controls.Add(this.label52);
			base.Controls.Add(this.label54);
			base.Controls.Add(this.label56);
			base.Controls.Add(this.label58);
			base.Controls.Add(this.label60);
			base.Controls.Add(this.label62);
			base.Controls.Add(this.label64);
			base.Controls.Add(this.label66);
			base.Controls.Add(this.label68);
			base.Controls.Add(this.label70);
			base.Controls.Add(this.label72);
			base.Controls.Add(this.label74);
			base.Controls.Add(this.label76);
			base.Controls.Add(this.label78);
			base.Controls.Add(this.textBox41);
			base.Controls.Add(this.label82);
			base.Controls.Add(this.label40);
			base.Controls.Add(this.label42);
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
			base.Controls.Add(this.textBox2);
			base.Controls.Add(this.label6);
			base.Controls.Add(this.textBox1);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.textBox5);
			base.Controls.Add(this.label3);
			base.Name = "AFN04_60";
			this.Text = "谐波限值";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
