using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Ctl
{
	public class AF10F9Config : Form
	{
		private IniFile ini = new IniFile(Program.SysPath + "Sys.ini");
		private IContainer components = null;
		private Panel panel1;
		private Button button1;
		private Label label2;
		private TextBox textBox2;
		private TextBox textBox1;
		private Label label1;
		public AF10F9Config()
		{
			this.InitializeComponent();
			this.textBox1.Text = Program.LC_JG.ToString();
			this.textBox1.Text = Program.LC_ERR.ToString();
		}
		private void Button1Click(object sender, EventArgs e)
		{
			this.ini.WriteIni("SYS", "LC_JG", this.textBox1.Text.Trim());
			this.ini.WriteIni("SYS", "LC_ERR", this.textBox1.Text.Trim());
			Program.LoadSysIni();
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
			this.panel1 = new Panel();
			this.button1 = new Button();
			this.textBox2 = new TextBox();
			this.label2 = new Label();
			this.textBox1 = new TextBox();
			this.label1 = new Label();
			this.panel1.SuspendLayout();
			base.SuspendLayout();
			this.panel1.BackColor = Color.FromArgb(239, 237, 226);
			this.panel1.Controls.Add(this.button1);
			this.panel1.Controls.Add(this.textBox2);
			this.panel1.Controls.Add(this.label2);
			this.panel1.Controls.Add(this.textBox1);
			this.panel1.Controls.Add(this.label1);
			this.panel1.Dock = DockStyle.Fill;
			this.panel1.Location = new Point(3, 24);
			this.panel1.Name = "panel1";
			this.panel1.Size = new Size(218, 115);
			this.panel1.TabIndex = 0;
			this.button1.Location = new Point(137, 75);
			this.button1.Name = "button1";
			this.button1.Size = new Size(52, 22);
			this.button1.TabIndex = 9;
			this.button1.Text = "确定";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new EventHandler(this.Button1Click);
			this.textBox2.Location = new Point(137, 44);
			this.textBox2.Name = "textBox2";
			this.textBox2.Size = new Size(50, 21);
			this.textBox2.TabIndex = 8;
			this.textBox2.Text = "30";
			this.label2.AutoSize = true;
			this.label2.Location = new Point(30, 47);
			this.label2.Name = "label2";
			this.label2.Size = new Size(101, 12);
			this.label2.TabIndex = 7;
			this.label2.Text = "错误下发间隔(秒)";
			this.textBox1.Location = new Point(113, 17);
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new Size(74, 21);
			this.textBox1.TabIndex = 6;
			this.textBox1.Text = "30";
			this.label1.AutoSize = true;
			this.label1.Location = new Point(30, 20);
			this.label1.Name = "label1";
			this.label1.Size = new Size(77, 12);
			this.label1.TabIndex = 5;
			this.label1.Text = "轮抄间隔(秒)";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(224, 142);
			base.Controls.Add(this.panel1);
			base.MaximizeBox = false;
			base.MinimizeBox = false;
			base.Name = "AF10F9Config";
			base.StartPosition = FormStartPosition.CenterScreen;
			this.Text = "轮抄配置";
			this.panel1.ResumeLayout(false);
			this.panel1.PerformLayout();
			base.ResumeLayout(false);
		}
	}
}
