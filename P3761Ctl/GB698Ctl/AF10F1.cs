using Helper;
using GB698Cls;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Globalization;
using System.Text;
using System.Windows.Forms;
using WinFormsUI.Docking;
namespace GB698Ctl
{
	public class AF10F1 : DockContent
	{
		public DataGridViewEx grid3 = new DataGridViewEx();
		private DLT698_Recv gAS = new DLT698_Recv();
		private DLT645 dlt645 = new DLT645();
		private DLT698Opera dlt = new DLT698Opera();
		private PubFunction pf = new PubFunction();
		private IContainer components = null;
		private ToolStripLabel toolStripLabel5;
		private Panel panel1;
		private ToolStripSeparator toolStripSeparator4;
		private ToolStripButton toolStripButton4;
		private ToolStripLabel toolStripLabel3;
		private ToolStripSeparator toolStripSeparator3;
		private ToolStripTextBox toolStripTextBox2;
		private ToolStripLabel toolStripLabel2;
		private ToolStrip toolStrip2;
		private ToolStripSeparator toolStripSeparator2;
		private ToolStripSeparator toolStripSeparator1;
		private ToolStripTextBox toolStripTextBox1;
		private ToolStripLabel toolStripLabel1;
		private ToolStripButton toolStripButton2;
		private ToolStripSeparator toolStripSeparator6;
		private ToolStripButton toolStripButton1;
		private ToolStripComboBox toolStripComboBox1;
		private ToolStripLabel toolStripLabel4;
		private ToolStrip toolStrip1;
		public AF10F1()
		{
			this.InitializeComponent();
			this.grid3.Parent = this.panel1;
			this.grid3.Dock = DockStyle.Fill;
			checked
			{
				for (int i = 1; i <= 31; i++)
				{
					this.toolStripComboBox1.Items.Add(i.ToString());
				}
				this.toolStripComboBox1.SelectedIndex = 0;
				this.InitGridInfo(this.grid3);
			}
		}
		private void InitGridInfo(DataGridView Grid)
		{
			Grid.Columns.Clear();
			Grid.Rows.Clear();
			Grid.AllowUserToAddRows = false;
			Grid.AlternatingRowsDefaultCellStyle.BackColor = Color.FromArgb(240, 240, 240);
			Grid.MultiSelect = false;
			Grid.BorderStyle = BorderStyle.Fixed3D;
			Grid.BackgroundColor = Color.FromKnownColor(KnownColor.White);
			Grid.GridColor = Color.FromKnownColor(KnownColor.ActiveBorder);
			Grid.ColumnHeadersDefaultCellStyle.Alignment = DataGridViewContentAlignment.MiddleCenter;
			Grid.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.EnableResizing;
			Grid.ColumnHeadersHeight = 25;
			DataGridViewTextBoxColumn dataGridViewTextBoxColumn = new DataGridViewTextBoxColumn();
			dataGridViewTextBoxColumn.HeaderText = "字段名";
			dataGridViewTextBoxColumn.Name = "zdmc";
			dataGridViewTextBoxColumn.Width = 270;
			dataGridViewTextBoxColumn.ReadOnly = true;
			dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewTextBoxColumn);
			dataGridViewTextBoxColumn = new DataGridViewTextBoxColumn();
			dataGridViewTextBoxColumn.HeaderText = "内容";
			dataGridViewTextBoxColumn.Name = "gybz";
			dataGridViewTextBoxColumn.Width = 380;
			dataGridViewTextBoxColumn.ReadOnly = true;
			dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewTextBoxColumn);
		}
		private void ToolStripButton2Click(object sender, EventArgs e)
		{
			string data = string.Empty;
			try
			{
				data = this.toolStripButton2.Text.Split(new char[]
				{
					'-'
				})[1];
			}
			catch
			{
			}
			iForm iForm = new CtlWord();
			iForm.Data = data;
			iForm.SetText();
			iForm.NeedSave = true;
			iForm.ShowDialog();
			this.toolStripButton2.Text = "通讯速率-" + iForm.Data;
		}
		private void ToolStripButton1Click(object sender, EventArgs e)
		{
			checked
			{
				if (string.IsNullOrEmpty(this.toolStripTextBox2.Text))
				{
					MessageBox.Show("请选择抄读规约");
				}
				else
				{
					this.toolStripButton1.Enabled = false;
					string text = string.Empty;
					text += this.OperaSend(this.toolStripComboBox1.Text, 1, "BIN");
					string str = string.Empty;
					try
					{
						str = this.toolStripButton2.Text.Split(new char[]
						{
							'-'
						})[1];
					}
					catch
					{
						goto IL_7CE;
					}
					text += str;
					int num = 0;
					
					text += (num | 30).ToString("X2");
					text += this.OperaSend("30", 1, "BIN");
					string text2 = this.Get645Frame();
					text += DataConvert.ReverseStr((text2.Trim().Length / 2).ToString("X4"));
					text += text2.Trim();
					if (text2.Trim().Length != 0)
					{
						this.dlt.AFN = "10";
						this.dlt.FN = "0001";
						this.dlt.PN = InputPN.GetPN("10", "0001");
						this.dlt.SendMSG = text;
						this.dlt.ListenPort = Program.gPort;
						this.dlt.CID = Program.CID;
						this.dlt.Tp = Program.Tp;
						this.dlt.PW = Program.PW;
						this.dlt.Flag = Program.Flag;
						this.dlt.ReadTimeout = Program.ReadTimeout;
						Program.gList.Clear();
						DataGridView gridV = MainForm.gMainForm.gAddressList.GridV;
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
						if (Program.gList.Count == 0)
						{
							MessageBox.Show("请先初始化终端列表 !", "失败", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
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
                                    if (Program.gList[i].Mode == ComunicationType.Serial)
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
                                            if (Program.gList[i].Mode == ComunicationType.TCPMyisClient)
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
										this.dlt.A1 = Program.gList[i].A1;
										this.dlt.A2 = Program.gList[i].A2;
										this.dlt.MSA = Program.MSA;
										bool flag2 = this.dlt.SendData();
										string receiveMSG = this.dlt.ReceiveMSG;
										string caption = "A1=" + this.dlt.A1 + ",A2=" + this.dlt.A2;
										if (string.IsNullOrEmpty(receiveMSG))
										{
											MessageBox.Show("无数据返回");
											break;
										}
										if (receiveMSG.ToUpper().IndexOf("ERROR") >= 0 | receiveMSG.ToUpper().IndexOf("确认") >= 0 | receiveMSG.ToUpper().IndexOf("否认") >= 0)
										{
											MessageBox.Show(receiveMSG.ToString(), caption, MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
											break;
										}
										this.gAS.DoInfo("10", "0001", receiveMSG, false, "", this.toolStripLabel3.Text);
										this.grid3.Rows.Clear();
										for (int j = 0; j < this.gAS.ItemData.Count; j++)
										{
											if (!string.IsNullOrEmpty(this.gAS.ItemData[j].Items))
											{
												this.grid3.Rows.Add();
												this.grid3.Rows[j].Cells[0].Value = this.gAS.ItemData[j].Items;
												this.grid3.Rows[j].Cells[1].Value = this.gAS.ItemData[j].Values;
											}
										}
									}
									Application.DoEvents();
								}
							}
						}
					}
					IL_7CE:
					this.dlt.Close();
					this.toolStripButton1.Enabled = true;
				}
			}
		}
		private string AF10_F1(string Value)
		{
			return Value.Substring(6);
		}
		private string Get645Frame()
		{
			this.dlt645.MeterCortrol = ((this.toolStripTextBox2.Text.Trim().Length == 8) ? "11" : "01");
			this.dlt645.IsRead = true;
			this.dlt645.MeterDataLength = int.Parse(this.toolStripLabel5.Text);
			this.dlt645.MeterIdentifier = this.toolStripTextBox2.Text.Trim();
			this.dlt645.MeterAddress = this.toolStripTextBox1.Text.Trim();
			this.dlt645.MeterPassWord = "";
			this.dlt645.MeterDataFormat = this.toolStripLabel3.Text.Trim();
			this.dlt645.MeterSendDataInfo = "";
			this.dlt645.OperatorID = "";
			return this.ByteToHexStr(this.dlt645.Get645Frame());
		}
		private int HexToInt(string HexChar)
		{
			int result = 0;
			bool flag = int.TryParse(HexChar, NumberStyles.HexNumber, null, out result);
			return result;
		}
		private string ByteToHexStr(byte[] data)
		{
			StringBuilder stringBuilder = new StringBuilder(checked(data.Length * 3));
			for (int i = 0; i < data.Length; i++)
			{
				byte value = data[i];
				stringBuilder.Append(Convert.ToString(value, 16).PadLeft(2, '0'));
			}
			return stringBuilder.ToString().Trim().ToUpper();
		}
		private string OperaSend(string Value, int Num, string type)
		{
			checked
			{
				string result;
				if (string.IsNullOrEmpty(Value))
				{
					result = "";
				}
				else
				{
					string text = string.Empty;
					Value = Value.Trim();
					string text2 = type.ToUpper();
					if (text2 != null)
					{
						if (!(text2 == "BIN"))
						{
							if (!(text2 == "") && !(text2 == "BCD"))
							{
								if (text2 == "ASCII")
								{
									text = this.ASCIIToHexStr(Value).PadLeft(Num * 2, '0');
								}
							}
							else
							{
								text = DataConvert.ReverseStr(Value.PadLeft(Num * 2, '0'));
							}
						}
						else
						{
							string val = long.Parse(Value).ToString("X" + (Num * 2).ToString());
							text = DataConvert.ReverseStr(val);
						}
					}
					result = text;
				}
				return result;
			}
		}
		private string ReverseStr(string val)
		{
			string text = string.Empty;
			checked
			{
				if (val.Length > 0)
				{
					for (int i = 0; i < val.Length; i += 2)
					{
						text = val.Substring(i, 2) + text;
					}
				}
				return text;
			}
		}
		private string ASCIIToHexStr(string strValue)
		{
			byte[] bytes = Encoding.ASCII.GetBytes(strValue);
			string text = string.Empty;
			checked
			{
				for (int i = 0; i < bytes.Length; i++)
				{
					text += bytes[i].ToString("X2");
				}
				return text;
			}
		}
		private void ToolStripButton4Click(object sender, EventArgs e)
		{
			iForm iForm = new DLT645Prot();
			iForm.Data = "00000000";
			iForm.SetText();
			iForm.NeedSave = true;
			iForm.ShowDialog();
			this.toolStripTextBox2.Text = iForm.Data.Split(new char[]
			{
				'?'
			})[0];
			this.toolStripLabel3.Text = iForm.Data.Split(new char[]
			{
				'?'
			})[1];
			this.toolStripLabel5.Text = iForm.Data.Split(new char[]
			{
				'?'
			})[2];
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
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.toolStripLabel4 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripComboBox1 = new System.Windows.Forms.ToolStripComboBox();
            this.toolStripButton2 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripLabel1 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripTextBox1 = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton1 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator6 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStrip2 = new System.Windows.Forms.ToolStrip();
            this.toolStripLabel2 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripTextBox2 = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripLabel3 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripButton4 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripLabel5 = new System.Windows.Forms.ToolStripLabel();
            this.panel1 = new System.Windows.Forms.Panel();
            this.toolStrip1.SuspendLayout();
            this.toolStrip2.SuspendLayout();
            this.SuspendLayout();
            // 
            // toolStrip1
            // 
            this.toolStrip1.CanOverflow = false;
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripLabel4,
            this.toolStripComboBox1,
            this.toolStripButton2,
            this.toolStripSeparator2,
            this.toolStripLabel1,
            this.toolStripTextBox1,
            this.toolStripSeparator1,
            this.toolStripButton1,
            this.toolStripSeparator6});
            this.toolStrip1.LayoutStyle = System.Windows.Forms.ToolStripLayoutStyle.HorizontalStackWithOverflow;
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(567, 25);
            this.toolStrip1.TabIndex = 5;
            // 
            // toolStripLabel4
            // 
            this.toolStripLabel4.Name = "toolStripLabel4";
            this.toolStripLabel4.Size = new System.Drawing.Size(91, 22);
            this.toolStripLabel4.Text = "终端通信端口号";
            // 
            // toolStripComboBox1
            // 
            this.toolStripComboBox1.Name = "toolStripComboBox1";
            this.toolStripComboBox1.Size = new System.Drawing.Size(75, 25);
            // 
            // toolStripButton2
            // 
            this.toolStripButton2.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton2.Name = "toolStripButton2";
            this.toolStripButton2.Size = new System.Drawing.Size(77, 22);
            this.toolStripButton2.Text = "通讯速率-6B";
            this.toolStripButton2.Click += new System.EventHandler(this.ToolStripButton2Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripLabel1
            // 
            this.toolStripLabel1.Name = "toolStripLabel1";
            this.toolStripLabel1.Size = new System.Drawing.Size(55, 22);
            this.toolStripLabel1.Text = "电表地址";
            // 
            // toolStripTextBox1
            // 
            this.toolStripTextBox1.Name = "toolStripTextBox1";
            this.toolStripTextBox1.Size = new System.Drawing.Size(100, 25);
            this.toolStripTextBox1.Text = "AAAAAAAAAAAA";
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton1
            // 
            this.toolStripButton1.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton1.Name = "toolStripButton1";
            this.toolStripButton1.Size = new System.Drawing.Size(35, 22);
            this.toolStripButton1.Text = "召测";
            this.toolStripButton1.ToolTipText = "召测";
            this.toolStripButton1.Click += new System.EventHandler(this.ToolStripButton1Click);
            // 
            // toolStripSeparator6
            // 
            this.toolStripSeparator6.Name = "toolStripSeparator6";
            this.toolStripSeparator6.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStrip2
            // 
            this.toolStrip2.BackColor = System.Drawing.Color.Transparent;
            this.toolStrip2.CanOverflow = false;
            this.toolStrip2.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.toolStrip2.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripLabel2,
            this.toolStripTextBox2,
            this.toolStripSeparator3,
            this.toolStripLabel3,
            this.toolStripButton4,
            this.toolStripSeparator4,
            this.toolStripLabel5});
            this.toolStrip2.LayoutStyle = System.Windows.Forms.ToolStripLayoutStyle.HorizontalStackWithOverflow;
            this.toolStrip2.Location = new System.Drawing.Point(0, 354);
            this.toolStrip2.Name = "toolStrip2";
            this.toolStrip2.Size = new System.Drawing.Size(567, 25);
            this.toolStrip2.TabIndex = 6;
            // 
            // toolStripLabel2
            // 
            this.toolStripLabel2.Name = "toolStripLabel2";
            this.toolStripLabel2.Size = new System.Drawing.Size(55, 22);
            this.toolStripLabel2.Text = "规约标识";
            // 
            // toolStripTextBox2
            // 
            this.toolStripTextBox2.Name = "toolStripTextBox2";
            this.toolStripTextBox2.Size = new System.Drawing.Size(70, 25);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripLabel3
            // 
            this.toolStripLabel3.Name = "toolStripLabel3";
            this.toolStripLabel3.Size = new System.Drawing.Size(0, 22);
            this.toolStripLabel3.Visible = false;
            // 
            // toolStripButton4
            // 
            this.toolStripButton4.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton4.Name = "toolStripButton4";
            this.toolStripButton4.Size = new System.Drawing.Size(59, 22);
            this.toolStripButton4.Text = "规约选择";
            this.toolStripButton4.Click += new System.EventHandler(this.ToolStripButton4Click);
            // 
            // toolStripSeparator4
            // 
            this.toolStripSeparator4.Name = "toolStripSeparator4";
            this.toolStripSeparator4.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripLabel5
            // 
            this.toolStripLabel5.Name = "toolStripLabel5";
            this.toolStripLabel5.Size = new System.Drawing.Size(0, 22);
            this.toolStripLabel5.Visible = false;
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(239)))), ((int)(((byte)(237)))), ((int)(((byte)(226)))));
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 25);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(567, 329);
            this.panel1.TabIndex = 7;
            // 
            // AF10F1
            // 
            this.ClientSize = new System.Drawing.Size(567, 379);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.toolStrip2);
            this.Controls.Add(this.toolStrip1);
            this.Font = new System.Drawing.Font("SimSun", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Name = "AF10F1";
            this.Text = "F1 透明转发";
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.toolStrip2.ResumeLayout(false);
            this.toolStrip2.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

		}
	}
}
