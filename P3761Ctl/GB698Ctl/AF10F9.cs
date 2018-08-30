using GB698Cls;
using System;
using System.Collections;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Threading;
using System.Windows.Forms;
using WinFormsUI.Docking;
using Helper;
namespace GB698Ctl
{
	public class AF10F9 : DockContent
	{
		private delegate void cbHeader_OnCheckBoxClickedDelegate(bool state);
		public delegate void CheckALLDelegate(bool CK);
		public delegate void AddRowDelegate(string dk, string bar, string biaozhi, string gshi);
		private delegate void AddDataDelegate(CollapseDataGridViewRow ROW, string iData, string Ival);
		public CollapseDataGridView grid1 = new CollapseDataGridView();
		private DLT698Opera dlt = new DLT698Opera();
		private bool RunCB = false;
		private IContainer components = null;
		private ToolStripSeparator toolStripSeparator5;
		private ToolStripButton toolStripButton5;
		private ToolStripSeparator toolStripSeparator4;
		private ToolStripButton toolStripButton3;
		private OpenFileDialog openFileDialog1;
		private ToolStripSeparator toolStripSeparator1;
		private ToolStripButton toolStripButton2;
		private ToolStripMenuItem 数据点抄ToolStripMenuItem;
		private ToolStripSeparator toolStripMenuItem3;
		private ToolStripSeparator toolStripSeparator6;
		private ToolStripButton toolStripButton4;
		private Panel Panel1;
		private ToolStripSeparator toolStripMenuItem2;
		private ToolStripMenuItem 添加项目ToolStripMenuItem;
		private ToolStripMenuItem 清空数据ToolStripMenuItem;
		private ToolStripSeparator toolStripMenuItem1;
		private ToolStripMenuItem 全部删除ToolStripMenuItem;
		private ToolStripMenuItem 删除行ToolStripMenuItem;
		private ContextMenuStrip contextMenuStrip1;
		private ToolStripSeparator toolStripSeparator3;
		private ToolStripSeparator toolStripSeparator2;
		private ToolStripTextBox toolStripTextBox1;
		private ToolStripLabel toolStripLabel1;
		private ToolStripButton toolStripButton1;
		private ToolStrip toolStrip1;
		public AF10F9()
		{
			this.InitializeComponent();
			this.grid1.Parent = this.Panel1;
			this.grid1.Dock = DockStyle.Fill;
			this.InitGrid(this.grid1);
			this.grid1.CellContentClick += new DataGridViewCellEventHandler(this.GridCellContentClick);
		}
		private void InitGrid(DataGridView Grid)
		{
			Grid.Columns.Clear();
			Grid.Rows.Clear();
			Grid.ContextMenuStrip = this.contextMenuStrip1;
			Grid.MultiSelect = false;
			Grid.BorderStyle = BorderStyle.None;
			Grid.BackgroundColor = Color.FromKnownColor(KnownColor.White);
			Grid.GridColor = Color.FromKnownColor(KnownColor.ActiveBorder);
			Grid.ColumnHeadersDefaultCellStyle.Alignment = DataGridViewContentAlignment.MiddleCenter;
			Grid.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.EnableResizing;
			Grid.ColumnHeadersHeight = 28;
			DataGridViewCheckBoxColumn dataGridViewCheckBoxColumn = new DataGridViewCheckBoxColumn();
			DatagridViewCheckBoxHeader.DatagridViewCheckBoxHeaderCell datagridViewCheckBoxHeaderCell = new DatagridViewCheckBoxHeader.DatagridViewCheckBoxHeaderCell();
			dataGridViewCheckBoxColumn.HeaderCell = datagridViewCheckBoxHeaderCell;
			dataGridViewCheckBoxColumn.Width = 25;
			Grid.Columns.Add(dataGridViewCheckBoxColumn);
			datagridViewCheckBoxHeaderCell.OnCheckBoxClicked += new DatagridViewCheckBoxHeader.CheckBoxClickedHandler(this.cbHeader_OnCheckBoxClicked);
			DataGridViewTextBoxColumn dataGridViewTextBoxColumn = new DataGridViewTextBoxColumn();
			dataGridViewTextBoxColumn.HeaderText = "端口号";
			dataGridViewTextBoxColumn.Name = "dkfhh";
			dataGridViewTextBoxColumn.Width = 60;
			dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewTextBoxColumn);
			dataGridViewTextBoxColumn = new DataGridViewTextBoxColumn();
			dataGridViewTextBoxColumn.HeaderText = "电表地址";
			dataGridViewTextBoxColumn.Name = "gybgfhz";
			dataGridViewTextBoxColumn.Width = 90;
			dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewTextBoxColumn);
			DataGridViewLinkColumn dataGridViewLinkColumn = new DataGridViewLinkColumn();
			dataGridViewLinkColumn.HeaderText = "规约标识";
			dataGridViewLinkColumn.Name = "xzgfgjs";
			dataGridViewLinkColumn.Width = 70;
			dataGridViewLinkColumn.ReadOnly = true;
			dataGridViewLinkColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewLinkColumn);
			dataGridViewTextBoxColumn = new DataGridViewTextBoxColumn();
			dataGridViewTextBoxColumn.HeaderText = "格式";
			dataGridViewTextBoxColumn.Name = "xzjhhhhs";
			dataGridViewTextBoxColumn.Width = 0;
			dataGridViewTextBoxColumn.ReadOnly = true;
			dataGridViewTextBoxColumn.Visible = false;
			dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewTextBoxColumn);
			dataGridViewLinkColumn = new DataGridViewLinkColumn();
			dataGridViewLinkColumn.HeaderText = "接收数据";
			dataGridViewLinkColumn.Name = "fghghffr";
			dataGridViewLinkColumn.Width = 180;
			dataGridViewLinkColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewLinkColumn);
			dataGridViewTextBoxColumn = new DataGridViewTextBoxColumn();
			dataGridViewTextBoxColumn.HeaderText = "抄收内容";
			dataGridViewTextBoxColumn.Name = "fghgddhffr";
			dataGridViewTextBoxColumn.Width = 180;
			dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewTextBoxColumn);
			dataGridViewTextBoxColumn = new DataGridViewTextBoxColumn();
			dataGridViewTextBoxColumn.HeaderText = "时间";
			dataGridViewTextBoxColumn.Name = "fghfgghffr";
			dataGridViewTextBoxColumn.Width = 60;
			dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewTextBoxColumn);
			Grid.AllowUserToAddRows = false;
		}
		private void cbHeader_OnCheckBoxClicked(bool state)
		{
			Thread.Sleep(0);
			if (base.InvokeRequired)
			{
				base.Invoke(new AF10F9.cbHeader_OnCheckBoxClickedDelegate(this.cbHeader_OnCheckBoxClicked), new object[]
				{
					state
				});
			}
			else
			{
				this.CheckALL(state);
			}
		}
		public void CheckALL(bool CK)
		{
			Thread.Sleep(0);
			checked
			{
				if (base.InvokeRequired)
				{
					base.Invoke(new AF10F9.CheckALLDelegate(this.CheckALL), new object[]
					{
						CK
					});
				}
				else
				{
					for (int i = 0; i < this.grid1.Rows.Count; i++)
					{
						this.grid1.Rows[i].Cells[0].Value = (CK ? 1 : 0);
					}
					this.grid1.Refresh();
				}
			}
		}
		private void 添加项目ToolStripMenuItemClick(object sender, EventArgs e)
		{
			this.AddRow("31", "", "00000000", "XXXXXX.XX");
		}
		public void AddRow(string dk, string bar, string biaozhi, string gshi)
		{
			Thread.Sleep(0);
			if (base.InvokeRequired)
			{
				base.Invoke(new AF10F9.AddRowDelegate(this.AddRow), new object[]
				{
					dk,
					bar,
					biaozhi,
					gshi
				});
			}
			else
			{
				Color backColor = Color.FromArgb(240, 240, 240);
				CollapseDataGridViewRow collapseDataGridViewRow = new CollapseDataGridViewRow();
				foreach (DataGridViewColumn dataGridViewColumn in this.grid1.Columns)
				{
					collapseDataGridViewRow.Cells.Add(dataGridViewColumn.CellTemplate.Clone() as DataGridViewCell);
				}
				collapseDataGridViewRow.IsCollapse = false;
				collapseDataGridViewRow.Cells[0].Value = 1;
				collapseDataGridViewRow.Cells[0].Style.BackColor = backColor;
				collapseDataGridViewRow.Cells[1].Value = dk;
				collapseDataGridViewRow.Cells[1].Style.BackColor = backColor;
				collapseDataGridViewRow.Cells[2].Value = bar;
				collapseDataGridViewRow.Cells[2].Style.BackColor = backColor;
				collapseDataGridViewRow.Cells[3].Value = biaozhi;
				collapseDataGridViewRow.Cells[3].Style.BackColor = backColor;
				collapseDataGridViewRow.Cells[4].Value = gshi;
				collapseDataGridViewRow.Cells[4].Style.BackColor = backColor;
				collapseDataGridViewRow.Cells[5].Value = "";
				collapseDataGridViewRow.Cells[5].Style.BackColor = backColor;
				collapseDataGridViewRow.Cells[6].Value = "";
				collapseDataGridViewRow.Cells[6].Style.BackColor = backColor;
				collapseDataGridViewRow.Cells[7].Value = "";
				collapseDataGridViewRow.Cells[7].Style.BackColor = backColor;
				this.grid1.Rows.Add(collapseDataGridViewRow);
			}
		}
		private void AddData(CollapseDataGridViewRow ROW, string iData, string Ival)
		{
			Thread.Sleep(0);
			if (this.grid1.InvokeRequired)
			{
				this.grid1.Invoke(new AF10F9.AddDataDelegate(this.AddData), new object[]
				{
					ROW,
					iData,
					Ival
				});
			}
			else
			{
				DataGridViewRow dataGridViewRow = new DataGridViewRow();
				foreach (DataGridViewColumn dataGridViewColumn in this.grid1.Columns)
				{
					dataGridViewRow.Cells.Add(dataGridViewColumn.CellTemplate.Clone() as DataGridViewCell);
				}
				dataGridViewRow.Cells[0].Value = 0;
				dataGridViewRow.Cells[1].Value = "";
				dataGridViewRow.Cells[2].Value = "";
				dataGridViewRow.Cells[3].Value = "";
				dataGridViewRow.Cells[4].Value = ROW.Cells[4].Value;
				dataGridViewRow.Cells[5].Value = iData;
				dataGridViewRow.Cells[6].Value = Ival;
				dataGridViewRow.Cells[7].Value = DateTime.Now.ToLongTimeString();
				ROW.Rows.Add(dataGridViewRow);
				if (!ROW.IsCollapse)
				{
					this.grid1.Rows.Insert(checked(ROW.Index + 1), dataGridViewRow);
				}
			}
		}
		private void 删除行ToolStripMenuItemClick(object sender, EventArgs e)
		{
			try
			{
				if (this.grid1.CurrentRow is CollapseDataGridViewRow)
				{
					this.grid1.RemoveAllSubRow(this.grid1.CurrentRow as CollapseDataGridViewRow, this.grid1, false);
				}
				this.grid1.Rows.Remove(this.grid1.CurrentRow);
				Application.DoEvents();
				this.grid1.Refresh();
			}
			catch
			{
			}
		}
		private void 全部删除ToolStripMenuItemClick(object sender, EventArgs e)
		{
			this.InitGrid(this.grid1);
		}
		private void 清空数据ToolStripMenuItemClick(object sender, EventArgs e)
		{
			checked
			{
				for (int i = this.grid1.Rows.Count - 1; i >= 0; i--)
				{
					DataGridViewRow dataGridViewRow = this.grid1.Rows[i];
					if (dataGridViewRow is CollapseDataGridViewRow)
					{
						(dataGridViewRow as CollapseDataGridViewRow).Rows.Clear();
					}
					else
					{
						this.grid1.Rows.Remove(dataGridViewRow);
					}
				}
			}
		}
		private void GridCellContentClick(object sender, DataGridViewCellEventArgs e)
		{
			int columnIndex = e.ColumnIndex;
			int rowIndex = e.RowIndex;
			checked
			{
				if (columnIndex == 5 && e.RowIndex != -1 && !this.grid1.Rows[e.RowIndex].IsNewRow)
				{
					string aFN = "10";
					string fN = "0009";
					string sValue = Convert.ToString(this.grid1.Rows[rowIndex].Cells[columnIndex].Value);
					string format = Convert.ToString(this.grid1.Rows[rowIndex].Cells[columnIndex - 1].Value);
					MainForm.gMainForm.gDataParse.Activate();
					MainForm.gMainForm.gDataParse.IsCustomize = false;
					MainForm.gMainForm.gDataParse.CustomizeItems = "";
					MainForm.gMainForm.gDataParse.SetText645(sValue, aFN, fN, format);
				}
				if (columnIndex == 3 && e.RowIndex != -1 && !this.grid1.Rows[e.RowIndex].IsNewRow)
				{
					iForm iForm = new DLT645Prot();
					iForm.Data = "00000000?XXXXXX.XX";
					iForm.SetText();
					iForm.NeedSave = true;
					iForm.ShowDialog();
					if (!string.IsNullOrEmpty(iForm.Data))
					{
						if (!string.IsNullOrEmpty(iForm.Data.Split(new char[]
						{
							'?'
						})[0]))
						{
							this.grid1.Rows[rowIndex].Cells[columnIndex].Value = iForm.Data.Split(new char[]
							{
								'?'
							})[0];
							this.grid1.Rows[rowIndex].Cells[columnIndex + 1].Value = iForm.Data.Split(new char[]
							{
								'?'
							})[1];
						}
					}
				}
			}
		}
		private void ToolStripButton4Click(object sender, EventArgs e)
		{
			this.RunCB = false;
		}
		private void ToolStripButton1Click(object sender, EventArgs e)
		{
			this.toolStripButton1.Enabled = false;
			this.toolStripButton4.Enabled = true;
			this.RunCB = true;
			this.grid1.EndEdit();
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
							if (Program.gList[i].Mode == 0)
							{
								this.dlt.FrameDelay = 5;
								this.dlt.Delay = Program.gDelay;
								this.dlt.ReadTimeout = Program.ReadTimeout;
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
								for (int j = 0; j < int.Parse(this.toolStripTextBox1.Text); j++)
								{
									foreach (DataGridViewRow dataGridViewRow in (IEnumerable)this.grid1.Rows)
									{
										if (dataGridViewRow is CollapseDataGridViewRow)
										{
											if (!this.RunCB)
											{
												goto IL_7B3;
											}
											if (Convert.ToBoolean(dataGridViewRow.Cells[0].Value))
											{
												this.dlt.AFN = "10";
												this.dlt.FN = "0009";
												this.dlt.PN = InputPN.GetPN("10", "0009");
												this.dlt.SendMSG = this.GetSendText(dataGridViewRow);
												this.dlt.ListenPort = Program.gPort;
												this.dlt.CID = Program.CID;
												this.dlt.Tp = Program.Tp;
												this.dlt.PW = Program.PW;
												this.dlt.Flag = Program.Flag;
												this.dlt.A1 = Program.gList[i].A1;
												this.dlt.A2 = Program.gList[i].A2;
												this.dlt.MSA = Program.MSA;
												bool flag2 = this.dlt.SendData();
												string text = this.dlt.ReceiveMSG;
												if (flag2)
												{
													text = this.dlt.ReceiveMSG;
												}
												else
												{
													text = "Error";
												}
												if (!string.IsNullOrEmpty(text))
												{
													if (string.IsNullOrEmpty(text) | text.ToUpper().IndexOf("ERROR") >= 0 | text.ToUpper().IndexOf("确认") >= 0 | text.ToUpper().IndexOf("否认") >= 0)
													{
														this.AddData(dataGridViewRow as CollapseDataGridViewRow, text, "");
														Program.gDBDataBase.InsertDataAF10F9(this.dlt.A1, this.dlt.A2, Convert.ToString(dataGridViewRow.Cells[2].Value), "数据转发", "F9 数据直抄", "00", "0009", "0000", text, text);
														if (text.ToUpper().IndexOf("ERROR") >= 0)
														{
															Thread.Sleep(Program.LC_ERR * 1000);
														}
													}
													else
													{
														DLT698_Recv dLT698_Recv = new DLT698_Recv();
														dLT698_Recv.DoInfo("10", "0009", text, false, "", Convert.ToString(dataGridViewRow.Cells[4].Value));
														this.AddData(dataGridViewRow as CollapseDataGridViewRow, text, dLT698_Recv.AF10_F9_Val);
														Program.gDBDataBase.InsertDataAF10F9(this.dlt.A1, this.dlt.A2, Convert.ToString(dataGridViewRow.Cells[2].Value), "数据转发", "F9 数据直抄", "00", "0009", "0000", text, dLT698_Recv.AF10_F9_Val);
													}
												}
												
											}
											Application.DoEvents();
										}
									}
									Thread.Sleep(Program.LC_JG * 1000);
								}
							}
						}
					}
				}
				IL_7B3:
				this.dlt.Close();
				this.toolStripButton1.Enabled = true;
				this.toolStripButton4.Enabled = false;
				this.RunCB = false;
			}
		}
		private void ToolStripButton3Click(object sender, EventArgs e)
		{
			AF10F9Config aF10F9Config = new AF10F9Config();
			aF10F9Config.ShowDialog();
		}
		private void 数据点抄ToolStripMenuItemClick(object sender, EventArgs e)
		{
			this.grid1.EndEdit();
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
                                    if (Program.gList[i].Mode == ComunicationType.TCPMyisClient)
									{
										this.dlt.FrameDelay = Program.gDelay;
										this.dlt.Delay = Program.gDelay;
										port = Program.RemotePort;
										temp = Program.RemoteIP;
										this.dlt.m_Port = Program.GetSocket(Program.gList[i].Mode, Program.gList[i].A1, Program.gList[i].A2);
									}
								}
							}
							this.dlt.OperType = Program.gList[i].Mode;
							bool flag = this.dlt.Open(port, temp);
							if (flag)
							{
								DataGridViewRow currentRow = this.grid1.CurrentRow;
								if (currentRow is CollapseDataGridViewRow)
								{
									this.dlt.AFN = "10";
									this.dlt.FN = "0009";
									this.dlt.PN = InputPN.GetPN("10", "0009");
									this.dlt.SendMSG = this.GetSendText(currentRow);
									this.dlt.ListenPort = Program.gPort;
									this.dlt.CID = Program.CID;
									this.dlt.Tp = Program.Tp;
									this.dlt.PW = Program.PW;
									this.dlt.Flag = Program.Flag;
									this.dlt.A1 = Program.gList[i].A1;
									this.dlt.A2 = Program.gList[i].A2;
									this.dlt.MSA = Program.MSA;
									bool flag2 = this.dlt.SendData();
									string text = this.dlt.ReceiveMSG;
									if (flag2)
									{
										text = this.dlt.ReceiveMSG;
									}
									else
									{
										text = "Error";
									}
									if (!string.IsNullOrEmpty(text))
									{
										if (string.IsNullOrEmpty(text) | text.ToUpper().IndexOf("ERROR") >= 0 | text.ToUpper().IndexOf("确认") >= 0 | text.ToUpper().IndexOf("否认") >= 0)
										{
											this.AddData(currentRow as CollapseDataGridViewRow, text, "");
										}
										else
										{
											DLT698_Recv dLT698_Recv = new DLT698_Recv();
											dLT698_Recv.DoInfo("10", "0009", text, false, "", Convert.ToString(currentRow.Cells[4].Value));
											this.AddData(currentRow as CollapseDataGridViewRow, text, dLT698_Recv.AF10_F9_Val);
										}
									}
								}
								Application.DoEvents();
							}
						}
					}
				}
				this.dlt.Close();
			}
		}
		private string GetSendText(DataGridViewRow row)
		{
			string str = string.Empty;
			str += this.OperaSend(Convert.ToString(row.Cells[1].Value), 1, "BIN");
			str += this.OperaSend("0", 1, "BIN");
			str += this.OperaSend(Convert.ToString(row.Cells[2].Value), 6, "A12");
			string text = Convert.ToString(row.Cells[3].Value);
			int num = 0;
			str += (num | ((text.Length == 4) ? 0 : 1)).ToString("X2");
			return str + this.OperaSend(text.PadLeft(8, '0'), 4, "BCD");
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
								if (text2 == "A12")
								{
									text = DataConvert.ReverseStr(Value.PadLeft(12, '0'));
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
		private void AF10F9Shown(object sender, EventArgs e)
		{
			this.LoadBar();
		}
		private void AF10F9FormClosing(object sender, FormClosingEventArgs e)
		{
			this.SaveBar();
		}
		private void ToolStripButton2Click(object sender, EventArgs e)
		{
			try
			{
				if (this.openFileDialog1.ShowDialog() == DialogResult.OK)
				{
					using (StreamReader streamReader = new StreamReader(new FileStream(this.openFileDialog1.FileName, FileMode.Open, FileAccess.Read)))
					{
						while (streamReader.Peek() > 0)
						{
							string text = streamReader.ReadLine();
							if (!string.IsNullOrEmpty(text))
							{
								this.AddRow("31", text, "00000000", "XXXXXX.XX");
							}
						}
						streamReader.Close();
					}
				}
			}
			catch
			{
			}
		}
		private void ToolStripButton5Click(object sender, EventArgs e)
		{
			MyExcel myExcel = new MyExcel();
			myExcel.Create();
			myExcel.DataTableOutPut(Program.gDBDataBase.GetTableAF10F9());
			myExcel.Save("AF10F9");
		}
		private void LoadBar()
		{
			string path = Program.SysPath + "\\AF10F9_Bar.txt";
			if (File.Exists(path))
			{
				using (StreamReader streamReader = new StreamReader(new FileStream(path, FileMode.Open, FileAccess.Read)))
				{
					while (streamReader.Peek() > 0)
					{
						string text = streamReader.ReadLine();
						if (!string.IsNullOrEmpty(text))
						{
							this.AddRow(text.Split(new char[]
							{
								','
							})[0], text.Split(new char[]
							{
								','
							})[1], text.Split(new char[]
							{
								','
							})[2], text.Split(new char[]
							{
								','
							})[3]);
						}
					}
					streamReader.Close();
				}
			}
		}
		private void SaveBar()
		{
			string path = Program.SysPath + "\\AF10F9_Bar.txt";
			if (File.Exists(path))
			{
				File.Delete(path);
			}
			FileStream fileStream = File.Create(path);
			fileStream.Close();
			if (File.Exists(path))
			{
				using (StreamWriter streamWriter = new StreamWriter(path))
				{
					foreach (DataGridViewRow dataGridViewRow in (IEnumerable)this.grid1.Rows)
					{
						if (dataGridViewRow is CollapseDataGridViewRow)
						{
							streamWriter.WriteLine(string.Concat(new string[]
							{
								Convert.ToString(dataGridViewRow.Cells[1].Value),
								",",
								Convert.ToString(dataGridViewRow.Cells[2].Value),
								",",
								Convert.ToString(dataGridViewRow.Cells[3].Value),
								",",
								Convert.ToString(dataGridViewRow.Cells[4].Value)
							}));
						}
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
            base.SuspendLayout();
			this.components = new Container();
			ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof(AF10F9));
			this.toolStrip1 = new ToolStrip();
			this.toolStripLabel1 = new ToolStripLabel();
			this.toolStripTextBox1 = new ToolStripTextBox();
			this.toolStripSeparator2 = new ToolStripSeparator();
			this.toolStripButton1 = new ToolStripButton();
			this.toolStripSeparator3 = new ToolStripSeparator();
			this.toolStripButton4 = new ToolStripButton();
			this.toolStripSeparator6 = new ToolStripSeparator();
			this.toolStripButton2 = new ToolStripButton();
			this.toolStripSeparator1 = new ToolStripSeparator();
			this.toolStripButton3 = new ToolStripButton();
			this.toolStripSeparator4 = new ToolStripSeparator();
			this.toolStripButton5 = new ToolStripButton();
			this.toolStripSeparator5 = new ToolStripSeparator();
			this.contextMenuStrip1 = new ContextMenuStrip(this.components);
			this.添加项目ToolStripMenuItem = new ToolStripMenuItem();
			this.toolStripMenuItem2 = new ToolStripSeparator();
			this.删除行ToolStripMenuItem = new ToolStripMenuItem();
			this.全部删除ToolStripMenuItem = new ToolStripMenuItem();
			this.toolStripMenuItem1 = new ToolStripSeparator();
			this.清空数据ToolStripMenuItem = new ToolStripMenuItem();
			this.toolStripMenuItem3 = new ToolStripSeparator();
			this.数据点抄ToolStripMenuItem = new ToolStripMenuItem();
			this.Panel1 = new Panel();
			this.openFileDialog1 = new OpenFileDialog();
			this.toolStrip1.SuspendLayout();
			this.contextMenuStrip1.SuspendLayout();
			
			this.toolStrip1.CanOverflow = false;
			this.toolStrip1.Items.AddRange(new ToolStripItem[]
			{
				this.toolStripLabel1,
				this.toolStripTextBox1,
				this.toolStripSeparator2,
				this.toolStripButton1,
				this.toolStripSeparator3,
				this.toolStripButton4,
				this.toolStripSeparator6,
				this.toolStripButton2,
				this.toolStripSeparator1,
				this.toolStripButton3,
				this.toolStripSeparator4,
				this.toolStripButton5,
				this.toolStripSeparator5
			});
			this.toolStrip1.LayoutStyle = ToolStripLayoutStyle.HorizontalStackWithOverflow;
			this.toolStrip1.Location = new Point(0, 0);
			this.toolStrip1.Name = "toolStrip1";
			this.toolStrip1.Size = new Size(531, 25);
			this.toolStrip1.TabIndex = 6;
			this.toolStripLabel1.Name = "toolStripLabel1";
			this.toolStripLabel1.Size = new Size(29, 22);
			this.toolStripLabel1.Text = "轮次";
			this.toolStripTextBox1.Name = "toolStripTextBox1";
			this.toolStripTextBox1.Size = new Size(50, 25);
			this.toolStripTextBox1.Text = "1";
			this.toolStripSeparator2.Name = "toolStripSeparator2";
			this.toolStripSeparator2.Size = new Size(6, 25);
			this.toolStripButton1.Image = (Image)componentResourceManager.GetObject("toolStripButton1.Image");
			this.toolStripButton1.ImageTransparentColor = Color.Magenta;
			this.toolStripButton1.Name = "toolStripButton1";
			this.toolStripButton1.Size = new Size(73, 22);
			this.toolStripButton1.Text = "开始召测";
			this.toolStripButton1.Click += new EventHandler(this.ToolStripButton1Click);
			this.toolStripSeparator3.Name = "toolStripSeparator3";
			this.toolStripSeparator3.Size = new Size(6, 25);
			this.toolStripButton4.Enabled = false;
			this.toolStripButton4.Image = (Image)componentResourceManager.GetObject("toolStripButton4.Image");
			this.toolStripButton4.ImageTransparentColor = Color.Magenta;
			this.toolStripButton4.Name = "toolStripButton4";
			this.toolStripButton4.Size = new Size(73, 22);
			this.toolStripButton4.Text = "停止操作";
			this.toolStripButton4.Click += new EventHandler(this.ToolStripButton4Click);
			this.toolStripSeparator6.Name = "toolStripSeparator6";
			this.toolStripSeparator6.Size = new Size(6, 25);
			this.toolStripButton2.Alignment = ToolStripItemAlignment.Right;
			this.toolStripButton2.DisplayStyle = ToolStripItemDisplayStyle.Image;
			this.toolStripButton2.Image = (Image)componentResourceManager.GetObject("toolStripButton2.Image");
			this.toolStripButton2.ImageTransparentColor = Color.Magenta;
			this.toolStripButton2.Name = "toolStripButton2";
			this.toolStripButton2.Size = new Size(23, 22);
			this.toolStripButton2.Text = "表号导入";
			this.toolStripButton2.Click += new EventHandler(this.ToolStripButton2Click);
			this.toolStripSeparator1.Alignment = ToolStripItemAlignment.Right;
			this.toolStripSeparator1.Name = "toolStripSeparator1";
			this.toolStripSeparator1.Size = new Size(6, 25);
			this.toolStripButton3.DisplayStyle = ToolStripItemDisplayStyle.Image;
			this.toolStripButton3.Image = (Image)componentResourceManager.GetObject("toolStripButton3.Image");
			this.toolStripButton3.ImageTransparentColor = Color.Magenta;
			this.toolStripButton3.Name = "toolStripButton3";
			this.toolStripButton3.Size = new Size(23, 22);
			this.toolStripButton3.Text = "配置";
			this.toolStripButton3.Click += new EventHandler(this.ToolStripButton3Click);
			this.toolStripSeparator4.Name = "toolStripSeparator4";
			this.toolStripSeparator4.Size = new Size(6, 25);
			this.toolStripButton5.DisplayStyle = ToolStripItemDisplayStyle.Image;
			this.toolStripButton5.Image = (Image)componentResourceManager.GetObject("toolStripButton5.Image");
			this.toolStripButton5.ImageTransparentColor = Color.Magenta;
			this.toolStripButton5.Name = "toolStripButton5";
			this.toolStripButton5.Size = new Size(23, 22);
			this.toolStripButton5.Text = "Excel导出";
			this.toolStripButton5.Click += new EventHandler(this.ToolStripButton5Click);
			this.toolStripSeparator5.Name = "toolStripSeparator5";
			this.toolStripSeparator5.Size = new Size(6, 25);
			this.contextMenuStrip1.Items.AddRange(new ToolStripItem[]
			{
				this.添加项目ToolStripMenuItem,
				this.toolStripMenuItem2,
				this.删除行ToolStripMenuItem,
				this.全部删除ToolStripMenuItem,
				this.toolStripMenuItem1,
				this.清空数据ToolStripMenuItem,
				this.toolStripMenuItem3,
				this.数据点抄ToolStripMenuItem
			});
			this.contextMenuStrip1.Name = "contextMenuStrip1";
			this.contextMenuStrip1.Size = new Size(153, 154);
			this.添加项目ToolStripMenuItem.Name = "添加项目ToolStripMenuItem";
			this.添加项目ToolStripMenuItem.Size = new Size(152, 22);
			this.添加项目ToolStripMenuItem.Text = "添加项目";
			this.添加项目ToolStripMenuItem.Click += new EventHandler(this.添加项目ToolStripMenuItemClick);
			this.toolStripMenuItem2.Name = "toolStripMenuItem2";
			this.toolStripMenuItem2.Size = new Size(149, 6);
			this.删除行ToolStripMenuItem.Name = "删除行ToolStripMenuItem";
			this.删除行ToolStripMenuItem.Size = new Size(152, 22);
			this.删除行ToolStripMenuItem.Text = "删除项目";
			this.删除行ToolStripMenuItem.Click += new EventHandler(this.删除行ToolStripMenuItemClick);
			this.全部删除ToolStripMenuItem.Name = "全部删除ToolStripMenuItem";
			this.全部删除ToolStripMenuItem.Size = new Size(152, 22);
			this.全部删除ToolStripMenuItem.Text = "全部删除";
			this.全部删除ToolStripMenuItem.Click += new EventHandler(this.全部删除ToolStripMenuItemClick);
			this.toolStripMenuItem1.Name = "toolStripMenuItem1";
			this.toolStripMenuItem1.Size = new Size(149, 6);
			this.清空数据ToolStripMenuItem.Name = "清空数据ToolStripMenuItem";
			this.清空数据ToolStripMenuItem.Size = new Size(152, 22);
			this.清空数据ToolStripMenuItem.Text = "清空数据";
			this.清空数据ToolStripMenuItem.Click += new EventHandler(this.清空数据ToolStripMenuItemClick);
			this.toolStripMenuItem3.Name = "toolStripMenuItem3";
			this.toolStripMenuItem3.Size = new Size(149, 6);
			this.数据点抄ToolStripMenuItem.Name = "数据点抄ToolStripMenuItem";
			this.数据点抄ToolStripMenuItem.Size = new Size(152, 22);
			this.数据点抄ToolStripMenuItem.Text = "数据点抄";
			this.数据点抄ToolStripMenuItem.Click += new EventHandler(this.数据点抄ToolStripMenuItemClick);
			this.Panel1.BackColor = Color.FromArgb(239, 237, 226);
			this.Panel1.Dock = DockStyle.Fill;
			this.Panel1.Location = new Point(0, 25);
			this.Panel1.Name = "Panel1";
			this.Panel1.Size = new Size(531, 321);
			this.Panel1.TabIndex = 7;
			this.openFileDialog1.Filter = "*.txt|*.txt";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(531, 346);
			base.Controls.Add(this.Panel1);
			base.Controls.Add(this.toolStrip1);
			this.Font = new Font("宋体", 9f, FontStyle.Regular, GraphicsUnit.Point, 134);
			base.Name = "AF10F9";
			this.Text = "F9 数据直抄";
			base.FormClosing += new FormClosingEventHandler(this.AF10F9FormClosing);
			base.Shown += new EventHandler(this.AF10F9Shown);
			this.toolStrip1.ResumeLayout(false);
			this.toolStrip1.PerformLayout();
			this.contextMenuStrip1.ResumeLayout(false);
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
