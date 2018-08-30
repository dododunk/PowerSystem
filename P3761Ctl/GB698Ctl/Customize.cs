using GB698Cls;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;
using WinFormsUI.Docking;
namespace GB698Ctl
{
	public class FormCustomize : DockContent
	{
		private delegate void RunDelegate();
		private delegate void OperaDelegate(string iA1, string iA2);
		private DLT698Opera dlt = new DLT698Opera();
		private IContainer components = null;
		private Label label5;
		private Label label1;
		private TextBox textBox2;
		private TextBox textBox1;
		private TextBox Data;
		private Button button1;
		private SplitContainer splitContainer1;
		private Label label8;
		private Label label4;
		private ComboBox PN;
		private Label label3;
		private ComboBox FN;
		private Label label2;
		private ComboBox AFN;
		public FormCustomize()
		{
			this.InitializeComponent();
			checked
			{
				for (int i = 1; i < 235; i++)
				{
					this.FN.Items.Add(i.ToString().PadLeft(4, '0'));
				}
				for (int i = 0; i < 2041; i++)
				{
					this.PN.Items.Add(i.ToString().PadLeft(4, '0'));
				}
			}
		}
		private void Button1Click(object sender, EventArgs e)
		{
			Program.gList.Clear();
			DataGridView gridV = MainForm.gMainForm.gAddressList.GridV;
			checked
			{
				for (int i = 0; i < gridV.Rows.Count; i++)
				{
					Program.AddList item = default(Program.AddList);
					if (!gridV.Rows[i].IsNewRow)
					{
						item.Checked = Convert.ToBoolean(gridV.Rows[i].Cells[0].Value);
						item.A1 = Convert.ToString(gridV.Rows[i].Cells[2].Value);
						item.A2 = Convert.ToString(gridV.Rows[i].Cells[3].Value);
						item.Mode = Program.GetLeiXing(Convert.ToString(gridV.Rows[i].Cells[4].Value));
						Program.gList.Add(item);
					}
				}
				this.dlt.ListenPort = Program.gPort;
				this.dlt.CID = Program.CID;
				this.dlt.Tp = Program.Tp;
				this.dlt.PW = Program.PW;
				this.dlt.Flag = Program.Flag;
				this.dlt.Assert.SEQ = (Program.AssertSEQ == 1);
				this.dlt.Assert.Tpv = (Program.AssertTpv == 1);
				this.dlt.ReadTimeout = Program.ReadTimeout;
			}
		}
		private void Run()
		{
			Thread.Sleep(0);
			checked
			{
				if (base.InvokeRequired)
				{
					base.Invoke(new FormCustomize.RunDelegate(this.Run), new object[0]);
				}
				else
				{
					int port = 0;
					string temp = "";
					Application.DoEvents();
					for (int i = 0; i < Program.gList.Count; i++)
					{
						Application.DoEvents();
						if (Program.gList[i].Checked)
						{
							if (Program.gList[i].Mode == 0)
							{
								this.dlt.FrameDelay = 5;
								this.dlt.Delay = Program.gDelay;
								port = Program.gComPort;
								temp = Program.gCommSetting;
							}
							else
							{
								if (Program.gList[i].Mode == ComunicationType.TCPMyisServer)
								{
									this.dlt.FrameDelay = Program.gDelay;
									this.dlt.Delay = Program.gDelay;
									this.dlt.m_Port = Program.GetSocket(Program.gList[i].Mode, Program.gList[i].A1, Program.gList[i].A2);
								}
								else
								{
                                    if (Program.gList[i].Mode == ComunicationType.TCPMyisServer)
									{
										this.dlt.FrameDelay = Program.gDelay;
										this.dlt.Delay = Program.gDelay;
										port = Program.RemotePort;
										temp = Program.RemoteIP;
										this.dlt.m_Port = Program.GetSocket(Program.gList[i].Mode, Program.gList[i].A1, Program.gList[i].A2);
									}
									else
									{
                                        if (Program.gList[i].Mode == ComunicationType.UDP)
										{
											this.dlt.FrameDelay = 5;
											this.dlt.Delay = Program.gDelay;
										}
									}
								}
							}
							this.dlt.OperType = Program.gList[i].Mode;
                            bool flag = (this.dlt.OperType == ComunicationType.UDP) ? this.dlt.Open(Program.UdpOpera, Program.UDP_Port_Send, Program.UDP_Port_Recieve, Program.UDP_RemoteAddress) : this.dlt.Open(port, temp);
							if (flag)
							{
								this.Opera(Program.gList[i].A1, Program.gList[i].A2);
							}
							Application.DoEvents();
							this.dlt.Close();
						}
					}
				}
			}
		}
		private void Opera(string iA1, string iA2)
		{
			Thread.Sleep(0);
			if (base.InvokeRequired)
			{
				base.Invoke(new FormCustomize.OperaDelegate(this.Opera), new object[]
				{
					iA1,
					iA2
				});
			}
			else
			{
				iA1 = iA1.PadLeft(4, '0');
				iA2 = iA2.PadLeft(4, '0');
				this.dlt.A1 = iA1;
				this.dlt.A2 = iA2;
				this.dlt.MSA = Program.MSA;
				this.dlt.AFN = Convert.ToString(this.AFN.Text);
				this.dlt.FN = Convert.ToString(this.FN.Text).PadLeft(4, '0');
				this.dlt.PN = Convert.ToString(this.PN.Text).PadLeft(4, '0');
				this.dlt.SendMSG = Convert.ToString(this.Data.Text);
				bool flag = this.dlt.SendData();
				string text = string.Empty;
				if (flag)
				{
					text = this.dlt.ReceiveMSG;
				}
				Application.DoEvents();
				this.textBox1.Text = this.dlt.ShowSendFrameInfo;
				this.textBox2.Text = this.dlt.ShowReceiveFrameInfo;
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
			this.AFN = new ComboBox();
			this.label2 = new Label();
			this.FN = new ComboBox();
			this.label3 = new Label();
			this.PN = new ComboBox();
			this.label4 = new Label();
			this.label8 = new Label();
			this.Data = new TextBox();
			this.splitContainer1 = new SplitContainer();
			this.textBox1 = new TextBox();
			this.label1 = new Label();
			this.textBox2 = new TextBox();
			this.label5 = new Label();
			this.button1 = new Button();
			((ISupportInitialize)this.splitContainer1).BeginInit();
			this.splitContainer1.Panel1.SuspendLayout();
			this.splitContainer1.Panel2.SuspendLayout();
			this.splitContainer1.SuspendLayout();
			base.SuspendLayout();
			this.AFN.FormattingEnabled = true;
			this.AFN.Items.AddRange(new object[]
			{
				"01",
				"02",
				"03",
				"04",
				"05",
				"06 ",
				"08",
				"09",
				"0A",
				"0B",
				"0C",
				"0D",
				"0E",
				"0F",
				"10"
			});
			this.AFN.Location = new Point(46, 9);
			this.AFN.Name = "AFN";
			this.AFN.Size = new Size(40, 20);
			this.AFN.TabIndex = 3;
			this.AFN.Text = "0A";
			this.label2.AutoSize = true;
			this.label2.Location = new Point(17, 12);
			this.label2.Name = "label2";
			this.label2.Size = new Size(23, 12);
			this.label2.TabIndex = 2;
			this.label2.Text = "AFN";
			this.FN.FormattingEnabled = true;
			this.FN.Location = new Point(125, 9);
			this.FN.Name = "FN";
			this.FN.Size = new Size(61, 20);
			this.FN.TabIndex = 5;
			this.FN.Text = "0001";
			this.label3.AutoSize = true;
			this.label3.Location = new Point(102, 12);
			this.label3.Name = "label3";
			this.label3.Size = new Size(17, 12);
			this.label3.TabIndex = 4;
			this.label3.Text = "FN";
			this.PN.FormattingEnabled = true;
			this.PN.Location = new Point(220, 9);
			this.PN.Name = "PN";
			this.PN.Size = new Size(61, 20);
			this.PN.TabIndex = 7;
			this.PN.Text = "0000";
			this.label4.AutoSize = true;
			this.label4.Location = new Point(197, 12);
			this.label4.Name = "label4";
			this.label4.Size = new Size(17, 12);
			this.label4.TabIndex = 6;
			this.label4.Text = "PN";
			this.label8.AutoSize = true;
			this.label8.Location = new Point(13, 38);
			this.label8.Name = "label8";
			this.label8.Size = new Size(29, 12);
			this.label8.TabIndex = 14;
			this.label8.Text = "Data";
			this.Data.Anchor = (AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right);
			this.Data.Location = new Point(46, 35);
			this.Data.Multiline = true;
			this.Data.Name = "Data";
			this.Data.ScrollBars = ScrollBars.Both;
			this.Data.Size = new Size(565, 40);
			this.Data.TabIndex = 15;
			this.splitContainer1.Anchor = (AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right);
			this.splitContainer1.Location = new Point(9, 81);
			this.splitContainer1.Name = "splitContainer1";
			this.splitContainer1.Panel1.Controls.Add(this.textBox1);
			this.splitContainer1.Panel1.Controls.Add(this.label1);
			this.splitContainer1.Panel2.Controls.Add(this.textBox2);
			this.splitContainer1.Panel2.Controls.Add(this.label5);
			this.splitContainer1.Size = new Size(605, 330);
			this.splitContainer1.SplitterDistance = 294;
			this.splitContainer1.TabIndex = 16;
			this.textBox1.Dock = DockStyle.Fill;
			this.textBox1.Location = new Point(0, 18);
			this.textBox1.Multiline = true;
			this.textBox1.Name = "textBox1";
			this.textBox1.ScrollBars = ScrollBars.Both;
			this.textBox1.Size = new Size(294, 312);
			this.textBox1.TabIndex = 19;
			this.label1.BackColor = Color.FromArgb(26, 78, 168);
			this.label1.Dock = DockStyle.Top;
			this.label1.Font = new Font("新宋体", 9f, FontStyle.Bold, GraphicsUnit.Point, 134);
			this.label1.ForeColor = SystemColors.Info;
			this.label1.Location = new Point(0, 0);
			this.label1.Name = "label1";
			this.label1.Size = new Size(294, 18);
			this.label1.TabIndex = 18;
			this.label1.Text = "发送数据解析";
			this.label1.TextAlign = ContentAlignment.MiddleLeft;
			this.textBox2.Dock = DockStyle.Fill;
			this.textBox2.Location = new Point(0, 18);
			this.textBox2.Multiline = true;
			this.textBox2.Name = "textBox2";
			this.textBox2.ScrollBars = ScrollBars.Both;
			this.textBox2.Size = new Size(307, 312);
			this.textBox2.TabIndex = 21;
			this.label5.BackColor = Color.FromArgb(26, 78, 168);
			this.label5.Dock = DockStyle.Top;
			this.label5.Font = new Font("新宋体", 9f, FontStyle.Bold, GraphicsUnit.Point, 134);
			this.label5.ForeColor = SystemColors.Info;
			this.label5.Location = new Point(0, 0);
			this.label5.Name = "label5";
			this.label5.Size = new Size(307, 18);
			this.label5.TabIndex = 20;
			this.label5.Text = "接收数据解析";
			this.label5.TextAlign = ContentAlignment.MiddleLeft;
			this.button1.Anchor = (AnchorStyles.Top | AnchorStyles.Right);
			this.button1.Location = new Point(549, 7);
			this.button1.Name = "button1";
			this.button1.Size = new Size(62, 23);
			this.button1.TabIndex = 17;
			this.button1.Text = "发送";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new EventHandler(this.Button1Click);
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			this.BackColor = Color.FromArgb(239, 237, 226);
			base.ClientSize = new Size(623, 419);
			base.Controls.Add(this.button1);
			base.Controls.Add(this.splitContainer1);
			base.Controls.Add(this.Data);
			base.Controls.Add(this.label8);
			base.Controls.Add(this.PN);
			base.Controls.Add(this.label4);
			base.Controls.Add(this.FN);
			base.Controls.Add(this.label3);
			base.Controls.Add(this.AFN);
			base.Controls.Add(this.label2);
			this.Font = new Font("宋体", 9f, FontStyle.Regular, GraphicsUnit.Point, 134);
			base.Name = "Customize";
			this.Text = "自定义规约";
			this.splitContainer1.Panel1.ResumeLayout(false);
			this.splitContainer1.Panel1.PerformLayout();
			this.splitContainer1.Panel2.ResumeLayout(false);
			this.splitContainer1.Panel2.PerformLayout();
			((ISupportInitialize)this.splitContainer1).EndInit();
			this.splitContainer1.ResumeLayout(false);
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
