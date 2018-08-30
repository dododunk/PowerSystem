using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Ctl
{
	public class FormSysAssert : Form
	{
		private IniFile ini = new IniFile(Program.SysPath + "Sys.ini");
		private IContainer components = null;
		private CheckBox checkBox;
		private Button button2;
		private CheckBox checkBox1;
		private CheckBox checkBox2;
		private Panel panel1;
		public FormSysAssert()
		{
			this.InitializeComponent();
		}
		private void Button2Click(object sender, EventArgs e)
		{
			this.ini.WriteIni("SYS", "AssertSEQ", this.checkBox1.Checked ? "1" : "0");
			this.ini.WriteIni("SYS", "AssertTpv", this.checkBox2.Checked ? "1" : "0");
			Program.LoadSysIni();
			base.Close();
		}
		private void SysAssertLoad(object sender, EventArgs e)
		{
			this.checkBox1.Checked = (Program.AssertSEQ != 0);
			this.checkBox2.Checked = (Program.AssertTpv != 0);
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
            this.panel1 = new System.Windows.Forms.Panel();
            this.checkBox = new System.Windows.Forms.CheckBox();
            this.checkBox2 = new System.Windows.Forms.CheckBox();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.button2 = new System.Windows.Forms.Button();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(239)))), ((int)(((byte)(237)))), ((int)(((byte)(226)))));
            this.panel1.Controls.Add(this.checkBox);
            this.panel1.Controls.Add(this.checkBox2);
            this.panel1.Controls.Add(this.checkBox1);
            this.panel1.Controls.Add(this.button2);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(305, 171);
            this.panel1.TabIndex = 1;
            // 
            // checkBox
            // 
            this.checkBox.AutoSize = true;
            this.checkBox.BackColor = System.Drawing.Color.Transparent;
            this.checkBox.Checked = true;
            this.checkBox.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox.Enabled = false;
            this.checkBox.Location = new System.Drawing.Point(23, 20);
            this.checkBox.Name = "checkBox";
            this.checkBox.Size = new System.Drawing.Size(103, 17);
            this.checkBox.TabIndex = 182;
            this.checkBox.Text = "CS 校验位判断";
            this.checkBox.UseVisualStyleBackColor = false;
            // 
            // checkBox2
            // 
            this.checkBox2.AutoSize = true;
            this.checkBox2.BackColor = System.Drawing.Color.Transparent;
            this.checkBox2.Checked = true;
            this.checkBox2.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox2.Location = new System.Drawing.Point(23, 68);
            this.checkBox2.Name = "checkBox2";
            this.checkBox2.Size = new System.Drawing.Size(114, 17);
            this.checkBox2.TabIndex = 181;
            this.checkBox2.Text = "Tp 时标有效判断";
            this.checkBox2.UseVisualStyleBackColor = false;
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.BackColor = System.Drawing.Color.Transparent;
            this.checkBox1.Checked = true;
            this.checkBox1.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox1.Location = new System.Drawing.Point(23, 44);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(111, 17);
            this.checkBox1.TabIndex = 180;
            this.checkBox1.Text = "SEQ 帧序列判断";
            this.checkBox1.UseVisualStyleBackColor = false;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(199, 105);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 179;
            this.button2.Text = "保存设置";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.Button2Click);
            // 
            // SysAssert
            // 
            this.ClientSize = new System.Drawing.Size(305, 171);
            this.Controls.Add(this.panel1);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "SysAssert";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "接收帧有效性判断";
            this.Load += new System.EventHandler(this.SysAssertLoad);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);

		}
	}
}
