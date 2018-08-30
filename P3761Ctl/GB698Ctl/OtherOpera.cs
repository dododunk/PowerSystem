using GB698Cls;
using System;
using System.Threading;
using System.Windows.Forms;
namespace GB698Ctl
{
	public class OtherOpera
	{
		private static DLT698Opera dlt = new DLT698Opera();
		private static DLT698_Recv gAS = new DLT698_Recv();
		public static void ReadAndWrite(string iAFN, string iFN, string iValues)
		{
			string pN = InputPN.GetPN(iAFN, iFN);
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
					OtherOpera.dlt.AFN = iAFN;
					OtherOpera.dlt.FN = iFN;
					OtherOpera.dlt.PN = pN;
					OtherOpera.dlt.SendMSG = iValues;
					OtherOpera.dlt.ListenPort = Program.gPort;
					OtherOpera.dlt.CID = Program.CID;
					OtherOpera.dlt.Tp = Program.Tp;
					OtherOpera.dlt.PW = Program.PW;
					OtherOpera.dlt.Flag = Program.Flag;
					OtherOpera.dlt.ReadTimeout = Program.ReadTimeout;
					new Thread(new ThreadStart(OtherOpera.Run))
					{
						IsBackground = true
					}.Start();
				}
			}
		}
		private static void Run()
		{
			int port = 0;
			string temp = "";
			Application.DoEvents();
			checked
			{
				for (int i = 0; i < Program.gList.Count; i++)
				{
					Application.DoEvents();
					if (Program.gList[i].Checked)
					{
						if (Program.gList[i].Mode == 0)
						{
							OtherOpera.dlt.FrameDelay = 5;
							OtherOpera.dlt.Delay = Program.gDelay;
							port = Program.gComPort;
							temp = Program.gCommSetting;
						}
						else
						{
                            if (Program.gList[i].Mode == ComunicationType.TCPMyisServer)
							{
								OtherOpera.dlt.FrameDelay = Program.gDelay;
								OtherOpera.dlt.Delay = Program.gDelay;
								OtherOpera.dlt.m_Port = Program.GetSocket(Program.gList[i].Mode, Program.gList[i].A1, Program.gList[i].A2);
							}
							else
							{
                                if (Program.gList[i].Mode == ComunicationType.TCPMyisClient)
								{
									OtherOpera.dlt.FrameDelay = Program.gDelay;
									OtherOpera.dlt.Delay = Program.gDelay;
									port = Program.RemotePort;
									temp = Program.RemoteIP;
									OtherOpera.dlt.m_Port = Program.GetSocket(Program.gList[i].Mode, Program.gList[i].A1, Program.gList[i].A2);
								}
								else
								{
                                    if (Program.gList[i].Mode == ComunicationType.UDP)
									{
										OtherOpera.dlt.FrameDelay = 5;
										OtherOpera.dlt.Delay = Program.gDelay;
									}
								}
							}
						}
						OtherOpera.dlt.OperType = Program.gList[i].Mode;
                        bool flag = (OtherOpera.dlt.OperType == ComunicationType.UDP) ? OtherOpera.dlt.Open(Program.UdpOpera, Program.UDP_Port_Send, Program.UDP_Port_Recieve, Program.UDP_RemoteAddress) : OtherOpera.dlt.Open(port, temp);
						if (flag)
						{
							OtherOpera.Opera(Program.gList[i].A1, Program.gList[i].A2);
						}
						Application.DoEvents();
						OtherOpera.dlt.Close();
					}
				}
			}
		}
		private static void Opera(string iA1, string iA2)
		{
			iA1 = iA1.PadLeft(4, '0');
			iA2 = iA2.PadLeft(4, '0');
			OtherOpera.dlt.A1 = iA1;
			OtherOpera.dlt.A2 = iA2;
			OtherOpera.dlt.MSA = Program.MSA;
			bool flag = OtherOpera.dlt.SendData();
			string receiveMSG = OtherOpera.dlt.ReceiveMSG;
			string text = "A1=" + iA1 + ",A2=" + iA2;
			if (string.IsNullOrEmpty(receiveMSG) | receiveMSG.ToUpper().IndexOf("ERROR") >= 0 | receiveMSG.ToUpper().IndexOf("确认") >= 0 | receiveMSG.ToUpper().IndexOf("否认") >= 0)
			{
				MessageBox.Show(receiveMSG.ToString(), text, MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
			}
			else
			{
				new FormFactory
				{
					CaptionText = text,
					IsCustomize = false
				}.DisplayR(OtherOpera.dlt.AFN, OtherOpera.dlt.FN, receiveMSG);
			}
		}
	}
}
