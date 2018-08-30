using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Ctl
{
	public class UCNetSysConfig : UserControl
	{
		private IniFile ini = new IniFile(Program.SysPath + "Sys.ini");
		private IContainer components = null;
		private Label label11;
		private TextBox textBox6;
		private Label label12;
		private TextBox textBox7;
		private Label label13;
		private TextBox textBox8;
		private TabPage tabPage5;
		private Label label7;
		private TextBox DSJG;
		private CheckBox checkBox2;
		private TabPage tabPage4;
		private CheckBox checkBox1;
		private Label label6;
		private TextBox textBox4;
		private Label label3;
		private TextBox textBox3;
		private Button button2;
		private TabPage tabPage3;
		private Label label1;
		private Label label10;
		private ComboBox comboBox8;
		private ComboBox comboBox1;
		private TabPage tabPage2;
		private Label label2;
		private TextBox textBox1;
		private Label label4;
		private TextBox textBox2;
		private TabPage tabPage1;
		private TabControl tabControl1;
		private Label label5;
		private ComboBox comboBox3;
		private Panel panel1;
		private TextBox textBox5;
		private Label label8;
		
		private Label label9;
		public UCNetSysConfig()
		{
			this.InitializeComponent();
			this.InitComm();
			this.comboBox1.Text = "COM" + Program.gComPort.ToString("D2");
			this.comboBox8.Text = Program.gCommSetting.ToString();
			this.textBox1.Text = Program.gPort.ToString();
			this.textBox2.Text = Program.gDelay.ToString();
			this.textBox4.Text = Program.RemoteIP;
			this.textBox3.Text = Program.RemotePort.ToString();
			this.comboBox3.SelectedIndex = Program.gAnalysis;
			this.checkBox1.Checked = (Program.AutoSearch == 1);
			this.checkBox2.Checked = (Program.SaveLog == 1);
			this.DSJG.Text = Program.TimingTask_Time.ToString();
			this.textBox5.Text = Program.ReadTimeout.ToString();
			
			this.textBox7.Text = Program.UDP_RemoteAddress;
			this.textBox8.Text = Program.UDP_Port_Send.ToString();
			this.textBox6.Text = Program.UDP_Port_Recieve.ToString();
		}
		private void SysConfigLoad(object sender, EventArgs e)
		{
		}
		private void InitComm()
		{
			this.comboBox1.Items.Clear();
			checked
			{
                if (Program.gComList != null)
                {
                    for (int i = 0; i < Program.gComList.Length - 1; i++)
                    {
                        this.comboBox1.Items.Add(Program.gComList[i]);
                    }
                }
			}
		}
		private void Button2Click(object sender, EventArgs e)
		{
			this.ini.WriteIni("SYS", "ComPort", this.comboBox1.Text.Substring(3, 2));
			this.ini.WriteIni("SYS", "CommSetting", this.comboBox8.Text.Trim());
			this.ini.WriteIni("SYS", "gPort", this.textBox1.Text.Trim());
			this.ini.WriteIni("SYS", "gDelay", this.textBox2.Text.Trim());
			this.ini.WriteIni("SYS", "QZJ_IP", this.textBox4.Text);
			this.ini.WriteIni("SYS", "QZJ_PORT", this.textBox3.Text);
			this.ini.WriteIni("SYS", "AutoSearch", this.checkBox1.Checked ? "1" : "0");
			this.ini.WriteIni("SYS", "SaveLog", this.checkBox2.Checked ? "1" : "0");
			this.ini.WriteIni("SYS", "gAnalysis", this.comboBox3.SelectedIndex.ToString());
			this.ini.WriteIni("SYS", "TimingTask", this.DSJG.Text);
			this.ini.WriteIni("SYS", "ReadTimeout", this.textBox5.Text);
			
			this.ini.WriteIni("SYS", "UDP_Address", this.textBox7.Text);
			this.ini.WriteIni("SYS", "UDP_Port_S", this.textBox8.Text);
			this.ini.WriteIni("SYS", "UDP_Port_R", this.textBox6.Text);
			Program.LoadSysIni();
            (this.Parent as Form).Close();
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
            this.comboBox3 = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.textBox5 = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.comboBox8 = new System.Windows.Forms.ComboBox();
            this.label10 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.textBox4 = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.tabPage4 = new System.Windows.Forms.TabPage();
            
            this.label9 = new System.Windows.Forms.Label();
            this.DSJG = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.checkBox2 = new System.Windows.Forms.CheckBox();
            this.tabPage5 = new System.Windows.Forms.TabPage();
            this.textBox6 = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.textBox8 = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
            this.textBox7 = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.button2 = new System.Windows.Forms.Button();
            this.panel1.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.tabPage3.SuspendLayout();
            this.tabPage4.SuspendLayout();
            this.tabPage5.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(239)))), ((int)(((byte)(237)))), ((int)(((byte)(226)))));
            this.panel1.Controls.Add(this.comboBox3);
            this.panel1.Controls.Add(this.label5);
            this.panel1.Controls.Add(this.tabControl1);
            this.panel1.Controls.Add(this.button2);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(378, 231);
            this.panel1.TabIndex = 0;
            // 
            // comboBox3
            // 
            this.comboBox3.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox3.FormattingEnabled = true;
            this.comboBox3.Items.AddRange(new object[] {
            "直接解析",
            "弹窗解析"});
            this.comboBox3.Location = new System.Drawing.Point(81, 174);
            this.comboBox3.Name = "comboBox3";
            this.comboBox3.Size = new System.Drawing.Size(97, 21);
            this.comboBox3.TabIndex = 124;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.BackColor = System.Drawing.Color.Transparent;
            this.label5.Location = new System.Drawing.Point(4, 178);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(55, 13);
            this.label5.TabIndex = 123;
            this.label5.Text = "解析方式";
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Controls.Add(this.tabPage4);
            this.tabControl1.Controls.Add(this.tabPage5);
            this.tabControl1.HotTrack = true;
            this.tabControl1.Location = new System.Drawing.Point(3, 3);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(366, 147);
            this.tabControl1.TabIndex = 122;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.checkBox1);
            this.tabPage1.Controls.Add(this.textBox2);
            this.tabPage1.Controls.Add(this.label4);
            this.tabPage1.Controls.Add(this.textBox1);
            this.tabPage1.Controls.Add(this.label2);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(358, 121);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "网络参数";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Location = new System.Drawing.Point(27, 63);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(182, 17);
            this.checkBox1.TabIndex = 119;
            this.checkBox1.Text = "服务端模式自动侦测在线终端";
            this.checkBox1.UseVisualStyleBackColor = true;
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(201, 26);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(38, 20);
            this.textBox2.TabIndex = 118;
            this.textBox2.Text = "30";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.BackColor = System.Drawing.Color.Transparent;
            this.label4.Location = new System.Drawing.Point(166, 30);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(31, 13);
            this.label4.TabIndex = 117;
            this.label4.Text = "超时";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(102, 26);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(47, 20);
            this.textBox1.TabIndex = 88;
            this.textBox1.Text = "8002";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.BackColor = System.Drawing.Color.Transparent;
            this.label2.Location = new System.Drawing.Point(25, 30);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(76, 13);
            this.label2.TabIndex = 87;
            this.label2.Text = "TCP侦听端口";
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.textBox5);
            this.tabPage2.Controls.Add(this.label8);
            this.tabPage2.Controls.Add(this.comboBox1);
            this.tabPage2.Controls.Add(this.comboBox8);
            this.tabPage2.Controls.Add(this.label10);
            this.tabPage2.Controls.Add(this.label1);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(358, 121);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "串口参数";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // textBox5
            // 
            this.textBox5.Location = new System.Drawing.Point(106, 64);
            this.textBox5.Name = "textBox5";
            this.textBox5.Size = new System.Drawing.Size(69, 20);
            this.textBox5.TabIndex = 122;
            this.textBox5.Text = "1000";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.BackColor = System.Drawing.Color.Transparent;
            this.label8.Location = new System.Drawing.Point(31, 67);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(71, 13);
            this.label8.TabIndex = 121;
            this.label8.Text = "ReadTimeout";
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new System.Drawing.Point(106, 12);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(69, 21);
            this.comboBox1.TabIndex = 114;
            // 
            // comboBox8
            // 
            this.comboBox8.FormattingEnabled = true;
            this.comboBox8.Items.AddRange(new object[] {
            "300,E,8,1",
            "600,E,8,1",
            "1200,E,8,1",
            "2400,E,8,1",
            "4800,E,8,1",
            "9600,E,8,1",
            "19200,E,8,1"});
            this.comboBox8.Location = new System.Drawing.Point(106, 38);
            this.comboBox8.Name = "comboBox8";
            this.comboBox8.Size = new System.Drawing.Size(95, 21);
            this.comboBox8.TabIndex = 115;
            this.comboBox8.Text = "9600,E,8,1";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.BackColor = System.Drawing.Color.Transparent;
            this.label10.Location = new System.Drawing.Point(31, 41);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(55, 13);
            this.label10.TabIndex = 113;
            this.label10.Text = "串口设置";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.Color.Transparent;
            this.label1.Location = new System.Drawing.Point(31, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(49, 13);
            this.label1.TabIndex = 112;
            this.label1.Text = "485端口";
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.textBox3);
            this.tabPage3.Controls.Add(this.label3);
            this.tabPage3.Controls.Add(this.textBox4);
            this.tabPage3.Controls.Add(this.label6);
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage3.Size = new System.Drawing.Size(358, 121);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "前置机参数";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // textBox3
            // 
            this.textBox3.Location = new System.Drawing.Point(109, 55);
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(57, 20);
            this.textBox3.TabIndex = 122;
            this.textBox3.Text = "8025";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.BackColor = System.Drawing.Color.Transparent;
            this.label3.Location = new System.Drawing.Point(38, 58);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(67, 13);
            this.label3.TabIndex = 121;
            this.label3.Text = "前置机端口";
            // 
            // textBox4
            // 
            this.textBox4.Location = new System.Drawing.Point(109, 24);
            this.textBox4.Name = "textBox4";
            this.textBox4.Size = new System.Drawing.Size(99, 20);
            this.textBox4.TabIndex = 120;
            this.textBox4.Text = "192.168.0.1";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.BackColor = System.Drawing.Color.Transparent;
            this.label6.Location = new System.Drawing.Point(38, 27);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(53, 13);
            this.label6.TabIndex = 119;
            this.label6.Text = "前置机IP";
            // 
            // tabPage4
            // 
            
            this.tabPage4.Controls.Add(this.label9);
            this.tabPage4.Controls.Add(this.DSJG);
            this.tabPage4.Controls.Add(this.label7);
            this.tabPage4.Controls.Add(this.checkBox2);
            this.tabPage4.Location = new System.Drawing.Point(4, 22);
            this.tabPage4.Name = "tabPage4";
            this.tabPage4.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage4.Size = new System.Drawing.Size(358, 121);
            this.tabPage4.TabIndex = 3;
            this.tabPage4.Text = "系统参数";
            this.tabPage4.UseVisualStyleBackColor = true;
            // 
            // comboBox2
            // 
            
            
            
            
            
            
            
            
            
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.BackColor = System.Drawing.Color.Transparent;
            this.label9.Location = new System.Drawing.Point(18, 72);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(88, 13);
            this.label9.TabIndex = 115;
            this.label9.Text = "系统界面Theme";
            // 
            // DSJG
            // 
            this.DSJG.Location = new System.Drawing.Point(147, 39);
            this.DSJG.Name = "DSJG";
            this.DSJG.Size = new System.Drawing.Size(46, 20);
            this.DSJG.TabIndex = 31;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(18, 44);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(121, 13);
            this.label7.TabIndex = 30;
            this.label7.Text = "定时任务时间间隔(分)";
            // 
            // checkBox2
            // 
            this.checkBox2.AutoSize = true;
            this.checkBox2.Location = new System.Drawing.Point(20, 15);
            this.checkBox2.Name = "checkBox2";
            this.checkBox2.Size = new System.Drawing.Size(98, 17);
            this.checkBox2.TabIndex = 0;
            this.checkBox2.Text = "系统日志保存";
            this.checkBox2.UseVisualStyleBackColor = true;
            // 
            // tabPage5
            // 
            this.tabPage5.Controls.Add(this.textBox6);
            this.tabPage5.Controls.Add(this.label11);
            this.tabPage5.Controls.Add(this.textBox8);
            this.tabPage5.Controls.Add(this.label13);
            this.tabPage5.Controls.Add(this.textBox7);
            this.tabPage5.Controls.Add(this.label12);
            this.tabPage5.Location = new System.Drawing.Point(4, 22);
            this.tabPage5.Name = "tabPage5";
            this.tabPage5.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage5.Size = new System.Drawing.Size(358, 121);
            this.tabPage5.TabIndex = 4;
            this.tabPage5.Text = "UDP通讯设置";
            this.tabPage5.UseVisualStyleBackColor = true;
            // 
            // textBox6
            // 
            this.textBox6.Location = new System.Drawing.Point(107, 59);
            this.textBox6.Name = "textBox6";
            this.textBox6.Size = new System.Drawing.Size(41, 20);
            this.textBox6.TabIndex = 130;
            this.textBox6.Text = "8026";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.BackColor = System.Drawing.Color.Transparent;
            this.label11.Location = new System.Drawing.Point(12, 62);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(102, 13);
            this.label11.TabIndex = 129;
            this.label11.Text = "UDP接收数据端口";
            // 
            // textBox8
            // 
            this.textBox8.Location = new System.Drawing.Point(223, 23);
            this.textBox8.Name = "textBox8";
            this.textBox8.Size = new System.Drawing.Size(38, 20);
            this.textBox8.TabIndex = 128;
            this.textBox8.Text = "8025";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.BackColor = System.Drawing.Color.Transparent;
            this.label13.Location = new System.Drawing.Point(191, 26);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(31, 13);
            this.label13.TabIndex = 127;
            this.label13.Text = "端口";
            // 
            // textBox7
            // 
            this.textBox7.Location = new System.Drawing.Point(107, 23);
            this.textBox7.Name = "textBox7";
            this.textBox7.Size = new System.Drawing.Size(77, 20);
            this.textBox7.TabIndex = 124;
            this.textBox7.Text = "192.168.0.1";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.BackColor = System.Drawing.Color.Transparent;
            this.label12.Location = new System.Drawing.Point(12, 26);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(91, 13);
            this.label12.TabIndex = 123;
            this.label12.Text = "发送到前端地址";
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(292, 173);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(73, 23);
            this.button2.TabIndex = 121;
            this.button2.Text = "保存设置";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.Button2Click);
            // 
            // FormNetSysConfig
            // 
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(239)))), ((int)(((byte)(237)))), ((int)(((byte)(226)))));
            this.ClientSize = new System.Drawing.Size(378, 231);
            this.Controls.Add(this.panel1);
            
            
            this.Name = "FormNetSysConfig";
            
            this.Text = "系统参数配置";
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            this.tabPage3.ResumeLayout(false);
            this.tabPage3.PerformLayout();
            this.tabPage4.ResumeLayout(false);
            this.tabPage4.PerformLayout();
            this.tabPage5.ResumeLayout(false);
            this.tabPage5.PerformLayout();
            this.ResumeLayout(false);

		}
	}
}
