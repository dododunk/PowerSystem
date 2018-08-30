using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Ctl
{
	public class FormSysConst : Form
	{
		private IniFile ini = new IniFile(Program.SysPath + "Sys.ini");
		private IContainer components = null;
		private Panel panel1;
		private ComboBox MSA;
		private Label label1;
		private CheckBox checkBox2;
		private CheckBox checkBox1;
		private Button button2;
		private Label label5;
		private ComboBox CID;
		private Label label9;
		private ComboBox PW;
		public FormSysConst()
		{
			this.InitializeComponent();
		}
		private void Button2Click(object sender, EventArgs e)
		{
			this.ini.WriteIni("SYS", "CID", this.CID.Text.Trim());
			this.ini.WriteIni("SYS", "PW", this.PW.Text.Trim());
			this.ini.WriteIni("SYS", "MSA", this.MSA.Text.Trim());
			this.ini.WriteIni("SYS", "Tp", this.checkBox1.Checked ? "1" : "0");
			this.ini.WriteIni("SYS", "Flag", this.checkBox2.Checked ? "1" : "0");
			Program.LoadSysIni();
			base.Close();
		}
		private void SysConstLoad(object sender, EventArgs e)
		{
			this.CID.Text = Program.CID.ToString();
			this.PW.Text = Program.PW.ToString();
			this.MSA.Text = Program.MSA.ToString();
			this.checkBox1.Checked = !(Program.Tp == "0");
			this.checkBox2.Checked = !(Program.Flag == "0");
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
            this.MSA = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.checkBox2 = new System.Windows.Forms.CheckBox();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.button2 = new System.Windows.Forms.Button();
            this.PW = new System.Windows.Forms.ComboBox();
            this.label9 = new System.Windows.Forms.Label();
            this.CID = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(239)))), ((int)(((byte)(237)))), ((int)(((byte)(226)))));
            this.panel1.Controls.Add(this.MSA);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Controls.Add(this.checkBox2);
            this.panel1.Controls.Add(this.checkBox1);
            this.panel1.Controls.Add(this.button2);
            this.panel1.Controls.Add(this.PW);
            this.panel1.Controls.Add(this.label9);
            this.panel1.Controls.Add(this.CID);
            this.panel1.Controls.Add(this.label5);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(344, 167);
            this.panel1.TabIndex = 0;
            // 
            // MSA
            // 
            this.MSA.FormattingEnabled = true;
            this.MSA.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9",
            "10",
            "11",
            "12",
            "13",
            "14",
            "15",
            "16",
            "17",
            "18",
            "19",
            "20",
            "21",
            "22",
            "23",
            "24",
            "25",
            "26",
            "27",
            "28",
            "29",
            "30",
            "31",
            "32",
            "33",
            "34",
            "35",
            "36",
            "37",
            "38",
            "39",
            "40",
            "41",
            "42",
            "43",
            "44",
            "45",
            "46",
            "47",
            "48",
            "49",
            "50",
            "51",
            "52",
            "53",
            "54",
            "55",
            "56",
            "57",
            "58",
            "59",
            "60",
            "61",
            "62",
            "63",
            "64",
            "65",
            "66",
            "67",
            "68",
            "69",
            "70",
            "71",
            "72",
            "73",
            "74",
            "75",
            "76",
            "77",
            "78",
            "79",
            "80",
            "81",
            "82",
            "83",
            "84",
            "85",
            "86",
            "87",
            "88",
            "89",
            "90",
            "91",
            "92",
            "93",
            "94",
            "95",
            "96",
            "97",
            "98",
            "99",
            "100",
            "101",
            "102",
            "103",
            "104",
            "105",
            "106",
            "107",
            "108",
            "109",
            "110",
            "111",
            "112",
            "113",
            "114",
            "115",
            "116",
            "117",
            "118",
            "119",
            "120",
            "121",
            "122",
            "123",
            "124",
            "125",
            "126",
            "127"});
            this.MSA.Location = new System.Drawing.Point(99, 74);
            this.MSA.Name = "MSA";
            this.MSA.Size = new System.Drawing.Size(54, 21);
            this.MSA.TabIndex = 180;
            this.MSA.Text = "1";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.Color.Transparent;
            this.label1.Location = new System.Drawing.Point(16, 77);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(78, 13);
            this.label1.TabIndex = 179;
            this.label1.Text = "主站地址MSA";
            // 
            // checkBox2
            // 
            this.checkBox2.AutoSize = true;
            this.checkBox2.BackColor = System.Drawing.Color.Transparent;
            this.checkBox2.Location = new System.Drawing.Point(260, 19);
            this.checkBox2.Name = "checkBox2";
            this.checkBox2.Size = new System.Drawing.Size(62, 17);
            this.checkBox2.TabIndex = 178;
            this.checkBox2.Text = "组地址";
            this.checkBox2.UseVisualStyleBackColor = false;
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.BackColor = System.Drawing.Color.Transparent;
            this.checkBox1.Location = new System.Drawing.Point(182, 19);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(75, 17);
            this.checkBox1.TabIndex = 177;
            this.checkBox1.Text = "带Tp时标";
            this.checkBox1.UseVisualStyleBackColor = false;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(245, 101);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 176;
            this.button2.Text = "保存设置";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.Button2Click);
            // 
            // PW
            // 
            this.PW.FormattingEnabled = true;
            this.PW.Location = new System.Drawing.Point(99, 48);
            this.PW.Name = "PW";
            this.PW.Size = new System.Drawing.Size(221, 21);
            this.PW.TabIndex = 175;
            this.PW.Text = "00000000000000000000000000000000";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.BackColor = System.Drawing.Color.Transparent;
            this.label9.Location = new System.Drawing.Point(16, 51);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(85, 13);
            this.label9.TabIndex = 174;
            this.label9.Text = "消息认证码PW";
            // 
            // CID
            // 
            this.CID.FormattingEnabled = true;
            this.CID.Items.AddRange(new object[] {
            "10",
            "11"});
            this.CID.Location = new System.Drawing.Point(47, 16);
            this.CID.Name = "CID";
            this.CID.Size = new System.Drawing.Size(53, 21);
            this.CID.TabIndex = 173;
            this.CID.Text = "11";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.BackColor = System.Drawing.Color.Transparent;
            this.label5.Location = new System.Drawing.Point(16, 19);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(25, 13);
            this.label5.TabIndex = 172;
            this.label5.Text = "CID";
            // 
            // SysConst
            // 
            this.ClientSize = new System.Drawing.Size(344, 167);
            this.Controls.Add(this.panel1);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "SysConst";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "抄读参数";
            this.Load += new System.EventHandler(this.SysConstLoad);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);

		}
	}
}
