using GB698Cls;
using System;
using System.Collections;
using System.Threading;
using System.Windows.Forms;
namespace GB698Ctl
{
	public class RW698Data
	{
		private delegate void OperaDelegate(string iA1, string iA2);
		private delegate void AddRowDelegate(CollapseDataGridViewRow ROW, string _Categories, string _Name, string iA1, string iA2, string iAFN, string iFN, string iPN, string iData);
		private DLT698Opera dlt = new DLT698Opera();
		public bool isruning = false;
		public bool needrun = false;
		public int ListIndex = 0;
		public CollapseDataGridView grid1 = new CollapseDataGridView();
		public RW698Data()
		{
			this.dlt.ListenPort = Program.gPort;
			this.dlt.CID = Program.CID;
			this.dlt.Tp = Program.Tp;
			this.dlt.PW = Program.PW;
			this.dlt.Flag = Program.Flag;
			this.dlt.FrameDelay = Program.gDelay;
			this.dlt.Delay = Program.gDelay;
			this.dlt.Assert.SEQ = (Program.AssertSEQ == 1);
			this.dlt.Assert.Tpv = (Program.AssertTpv == 1);
			this.dlt.ReadTimeout = Program.ReadTimeout;
		}
		public void Run()
		{
			this.isruning = true;
			this.needrun = true;
			Thread.CurrentThread.IsBackground = true;
			int port = 0;
			string temp = "";
			if (Program.gList[this.ListIndex].Mode == 0)
			{
				port = Program.gComPort;
				temp = Program.gCommSetting;
			}
			else
			{
                if (Program.gList[this.ListIndex].Mode == ComunicationType.TCPMyisServer)
				{
					this.dlt.m_Port = Program.GetSocket(Program.gList[this.ListIndex].Mode, Program.gList[this.ListIndex].A1, Program.gList[this.ListIndex].A2);
				}
				else
				{
                    if (Program.gList[this.ListIndex].Mode == ComunicationType.TCPMyisClient)
					{
						port = Program.RemotePort;
						temp = Program.RemoteIP;
						this.dlt.m_Port = Program.GetSocket(Program.gList[this.ListIndex].Mode, Program.gList[this.ListIndex].A1, Program.gList[this.ListIndex].A2);
					}
					else
					{
                        if (Program.gList[this.ListIndex].Mode == ComunicationType.UDP)
						{
							this.dlt.FrameDelay = 5;
							this.dlt.Delay = Program.gDelay;
						}
					}
				}
			}
			this.dlt.OperType = Program.gList[this.ListIndex].Mode;
            bool flag = (this.dlt.OperType == ComunicationType.UDP) ? this.dlt.Open(Program.UdpOpera, Program.UDP_Port_Send, Program.UDP_Port_Recieve, Program.UDP_RemoteAddress) : this.dlt.Open(port, temp);
			if (flag)
			{
				this.Opera(Program.gList[this.ListIndex].A1, Program.gList[this.ListIndex].A2);
			}
			this.isruning = false;
			this.dlt.Close();
		}
		private void Opera(string iA1, string iA2)
		{
			Thread.Sleep(0);
			if (this.grid1.InvokeRequired)
			{
				this.grid1.Invoke(new RW698Data.OperaDelegate(this.Opera), new object[]
				{
					iA1,
					iA2
				});
			}
			else
			{
				this.dlt.A1 = iA1;
				this.dlt.A2 = iA2;
				this.dlt.MSA = Program.MSA;
				foreach (DataGridViewRow dataGridViewRow in (IEnumerable)this.grid1.Rows)
				{
					
					if (dataGridViewRow is CollapseDataGridViewRow)
					{
						if (Convert.ToBoolean(dataGridViewRow.Cells[6].Value) & this.needrun)
						{
							string categories = Convert.ToString(dataGridViewRow.Cells[0].Value);
							string name = Convert.ToString(dataGridViewRow.Cells[1].Value);
							string text = Convert.ToString(dataGridViewRow.Cells[2].Value);
							string text2 = Convert.ToString(dataGridViewRow.Cells[3].Value).PadLeft(4, '0');
							string text3 = Convert.ToString(dataGridViewRow.Cells[4].Value).PadLeft(4, '0');
							string text4 = Convert.ToString(dataGridViewRow.Cells[5].Value);
							this.dlt.AFN = text;
							this.dlt.FN = text2;
							this.dlt.PN = text3;
							this.dlt.SendMSG = text4;
							bool flag = this.dlt.SendData();
							string text5 = string.Empty;
							if (flag)
							{
								text5 = this.dlt.ReceiveMSG;
							}
							else
							{
								text5 = "Error";
							}
							Application.DoEvents();
							this.AddRow(dataGridViewRow as CollapseDataGridViewRow, "", "", iA1, iA2, text, text2, text3, text5);
							Application.DoEvents();
							this.grid1.Refresh();
							if (!string.IsNullOrEmpty(text5))
							{
								Program.gDBDataBase.InsertData(iA1, iA2, categories, name, text, text2, text3, text5, text4);
							}
						}
					}
				}
			}
		}
		private void AddRow(CollapseDataGridViewRow ROW, string _Categories, string _Name, string iA1, string iA2, string iAFN, string iFN, string iPN, string iData)
		{
			Thread.Sleep(0);
			if (this.grid1.InvokeRequired)
			{
				this.grid1.Invoke(new RW698Data.AddRowDelegate(this.AddRow), new object[]
				{
					ROW,
					_Categories,
					_Name,
					iA1,
					iA2,
					iAFN,
					iFN,
					iPN,
					iData
				});
			}
			else
			{
				DataGridViewRow dataGridViewRow = new DataGridViewRow();
				foreach (DataGridViewColumn dataGridViewColumn in this.grid1.Columns)
				{
					dataGridViewRow.Cells.Add(dataGridViewColumn.CellTemplate.Clone() as DataGridViewCell);
				}
				dataGridViewRow.Cells[0].Value = _Categories.Trim();
				dataGridViewRow.Cells[1].Value = _Name;
				dataGridViewRow.Cells[2].Value = iAFN;
				dataGridViewRow.Cells[3].Value = iFN.PadLeft(4, '0');
				dataGridViewRow.Cells[4].Value = iPN;
				dataGridViewRow.Cells[5].Value = "";
				dataGridViewRow.Cells[6].Value = 1;
				dataGridViewRow.Cells[7].Value = iA1;
				dataGridViewRow.Cells[8].Value = iA2;
				dataGridViewRow.Cells[9].Value = iData;
				dataGridViewRow.Cells[10].Value = DateTime.Now.ToLongTimeString();
				ROW.Rows.Add(dataGridViewRow);
				if (!ROW.IsCollapse)
				{
					this.grid1.Rows.Insert(checked(ROW.Index + 1), dataGridViewRow);
				}
			}
		}
	}
}
