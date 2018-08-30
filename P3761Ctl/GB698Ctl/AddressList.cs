using GB698Cls;
using GB698Ctl.Properties;
using System;
using System.Collections;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Globalization;
using System.IO;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using WinFormsUI.Docking;
using Helper;
namespace GB698Ctl
{
    public class AddressList : ToolWindow
    {
        private delegate void cbHeader_OnCheckBoxClickedDelegate(bool state);
        private delegate void CheckALLDelegate(bool CK);
        private delegate void AddClientDelegate(string obj);
        //只有这个是公开的暴露给其它使用
        public DataGridView GridV = new DataGridView();
        private bool inited = false;
        private IContainer components = null;
        private ToolStripMenuItem 终端列表ToolStripMenuItem;
        private ToolStripSeparator toolStripMenuItem3;
        private ToolStripMenuItem 断开连接ToolStripMenuItem;
        private ToolStripSeparator toolStripMenuItem2;
        private ToolStripMenuItem 清空列表ToolStripMenuItem;
        private ToolStripSeparator toolStripMenuItem1;
        private System.Windows.Forms.Timer timer1;
        private ToolStripMenuItem 删除终端ToolStripMenuItem;
        private ToolStripMenuItem 添加终端ToolStripMenuItem;
        private ContextMenuStrip contextMenuStrip1;
        public AddressList()
        {
            this.InitializeComponent();
            this.InitGrid();
            this.GridV.Parent = this;
            Application.DoEvents();
            this.GridV.CellPainting += new DataGridViewCellPaintingEventHandler(this.OnCellPainting);
            this.LoadTerminal();
            this.timer1.Interval = 5000;
            this.timer1.Enabled = true;
            Program.CheckClients = true;
            ThreadPool.QueueUserWorkItem(new WaitCallback(this.CheckOnlineTerminal), null);
        }
        private void CheckOnlineTerminal(object obj)
        {
            Thread.CurrentThread.IsBackground = true;
            return;
            checked
            {
                while (Program.CheckClients)
                {
                    Application.DoEvents();
                    Thread.Sleep(1);
                    if (Program.AutoSearch == 1 && Program.tcplistener != null)
                    {
                        for (int i = 0; i < Program.tcplistener.clients.Count; i++)
                        {
                            Application.DoEvents();
                            try
                            {
                                this.AddClient(Program.tcplistener.clients[i].A1 + "," + Program.tcplistener.clients[i].A2 + ",1");
                            }
                            catch
                            {
                            }
                        }
                    }
                }
            }
        }
        private void LoadTerminal()
        {
            string path = Program.SysPath + "\\Terminal.txt";
            if (File.Exists(path))
            {
                using (StreamReader streamReader = new StreamReader(new FileStream(path, FileMode.Open, FileAccess.Read)))
                {
                    while (streamReader.Peek() > 0)
                    {
                        string text = streamReader.ReadLine();
                        if (!string.IsNullOrEmpty(text))
                        {
                            if (!string.IsNullOrEmpty(text.Split(new char[]
							{
								','
							})[0]) & !string.IsNullOrEmpty(text.Split(new char[]
							{
								','
							})[1]))
                            {
                                this.AddClient(string.Concat(new string[]
								{
									text.Split(new char[]
									{
										','
									})[0],
									",",
									text.Split(new char[]
									{
										','
									})[1],
									",",
									text.Split(new char[]
									{
										','
									})[2]
								}));
                            }
                        }
                    }
                    streamReader.Close();
                }
            }
        }
        private void SaveTerminal()
        {
            string path = Program.SysPath + "\\Terminal.txt";
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
                    foreach (DataGridViewRow dataGridViewRow in (IEnumerable)this.GridV.Rows)
                    {
                        if (!dataGridViewRow.IsNewRow)
                        {
                            string value = string.Empty;
                            string text = Convert.ToString(dataGridViewRow.Cells[4].Value).ToUpper().Trim();
                            string text2 = text;
                            if (text2 != null)
                            {
                                if (!(text2 == "串口模式"))
                                {
                                    if (!(text2 == "GPRS(服务端)"))
                                    {
                                        if (!(text2 == "GPRS(客户端)"))
                                        {
                                            if (text2 == "UDP模式")
                                            {
                                                value = Convert.ToString(dataGridViewRow.Cells[2].Value) + "," + Convert.ToString(dataGridViewRow.Cells[3].Value) + ",3";
                                            }
                                        }
                                        else
                                        {
                                            value = Convert.ToString(dataGridViewRow.Cells[2].Value) + "," + Convert.ToString(dataGridViewRow.Cells[3].Value) + ",2";
                                        }
                                    }
                                    else
                                    {
                                        value = Convert.ToString(dataGridViewRow.Cells[2].Value) + "," + Convert.ToString(dataGridViewRow.Cells[3].Value) + ",1";
                                    }
                                }
                                else
                                {
                                    value = Convert.ToString(dataGridViewRow.Cells[2].Value) + "," + Convert.ToString(dataGridViewRow.Cells[3].Value) + ",0";
                                }
                            }
                            streamWriter.WriteLine(value);
                        }
                    }
                }
            }
        }
        private void InitGrid()
        {
            if (!this.inited)
            {
                this.GridV.Columns.Clear();
                this.GridV.Rows.Clear();
                this.GridV.ContextMenuStrip = this.contextMenuStrip1;
                this.GridV.RowHeadersVisible = false;
                this.GridV.AllowUserToAddRows = true;
                this.GridV.BorderStyle = BorderStyle.Fixed3D;
                this.GridV.Dock = DockStyle.Fill;
                this.GridV.MultiSelect = false;
                this.GridV.BackgroundColor = Color.FromKnownColor(KnownColor.White);
                this.GridV.GridColor = Color.FromKnownColor(KnownColor.ActiveBorder);
                this.GridV.ColumnHeadersDefaultCellStyle.Alignment = DataGridViewContentAlignment.MiddleCenter;
                this.GridV.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.EnableResizing;
                this.GridV.ColumnHeadersHeight = 31;
                this.GridV.AlternatingRowsDefaultCellStyle.BackColor = Color.FromArgb(240, 240, 240);
                DataGridViewCheckBoxColumn dataGridViewCheckBoxColumn = new DataGridViewCheckBoxColumn();
                DatagridViewCheckBoxHeader.DatagridViewCheckBoxHeaderCell datagridViewCheckBoxHeaderCell = new DatagridViewCheckBoxHeader.DatagridViewCheckBoxHeaderCell();
                dataGridViewCheckBoxColumn.HeaderCell = datagridViewCheckBoxHeaderCell;
                dataGridViewCheckBoxColumn.Width = 25;
                this.GridV.Columns.Add(dataGridViewCheckBoxColumn);
                datagridViewCheckBoxHeaderCell.OnCheckBoxClicked += new DatagridViewCheckBoxHeader.CheckBoxClickedHandler(this.cbHeader_OnCheckBoxClicked);
                DataGridViewTextBoxColumn dataGridViewTextBoxColumn = new DataGridViewTextBoxColumn();
                dataGridViewTextBoxColumn.HeaderText = "终端名称";
                dataGridViewTextBoxColumn.Name = "zdipdz";
                dataGridViewTextBoxColumn.Width = 60;
                dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
                this.GridV.Columns.Add(dataGridViewTextBoxColumn);
                dataGridViewTextBoxColumn = new DataGridViewTextBoxColumn();
                dataGridViewTextBoxColumn.HeaderText = "行政区划码A1";
                dataGridViewTextBoxColumn.Name = "zdmc";
                dataGridViewTextBoxColumn.Width = 50;
                dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
                this.GridV.Columns.Add(dataGridViewTextBoxColumn);
                dataGridViewTextBoxColumn = new DataGridViewTextBoxColumn();
                dataGridViewTextBoxColumn.HeaderText = "终端地址A2";
                dataGridViewTextBoxColumn.Name = "gybz";
                dataGridViewTextBoxColumn.Width = 50;
                dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
                this.GridV.Columns.Add(dataGridViewTextBoxColumn);
                DataGridViewComboBoxColumn dataGridViewComboBoxColumn = new DataGridViewComboBoxColumn();
                dataGridViewComboBoxColumn.HeaderText = "操作模式";
                dataGridViewComboBoxColumn.Name = "czmsxz";
                dataGridViewComboBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
                dataGridViewComboBoxColumn.Items.Add("串口模式");
                dataGridViewComboBoxColumn.Items.Add("GPRS(服务端)");
                dataGridViewComboBoxColumn.Items.Add("GPRS(客户端)");
                dataGridViewComboBoxColumn.Items.Add("UDP模式");
                this.GridV.Columns.Add(dataGridViewComboBoxColumn);
                DataGridViewImageColumn dataGridViewImageColumn = new DataGridViewImageColumn();
                dataGridViewImageColumn.HeaderText = "状态";
                dataGridViewImageColumn.Name = "jg";
                dataGridViewImageColumn.Width = 22;
                dataGridViewImageColumn.ReadOnly = true;
                dataGridViewImageColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
                this.GridV.Columns.Add(dataGridViewImageColumn);
                this.GridV.AllowUserToAddRows = false;
                this.inited = true;
            }
        }
        private void 添加终端ToolStripMenuItemClick(object sender, EventArgs e)
        {
            this.GridV.Rows.Add();
            int index = checked(this.GridV.Rows.Count - 1);
            this.GridV.Rows[index].Cells[0].Value = 1;
            this.GridV.Rows[index].Cells[1].Value = "终端";
            this.GridV.Rows[index].Cells[2].Value = "";
            this.GridV.Rows[index].Cells[3].Value = "";
            this.GridV.Rows[index].Cells[4].Value = "串口模式";
            this.GridV.Rows[index].Cells[5].Value = Resources.NONE;
        }
        private void 删除终端ToolStripMenuItemClick(object sender, EventArgs e)
        {
            try
            {
                int index = this.GridV.CurrentRow.Index;
                string text = Convert.ToString(this.GridV.Rows[index].Cells[1].Value);
                string text2 = Convert.ToString(this.GridV.Rows[index].Cells[2].Value);
                string text3 = Convert.ToString(this.GridV.Rows[index].Cells[3].Value);
                this.GridV.Rows.Remove(this.GridV.CurrentRow);
                
            }
            catch (Exception)
            {
            }
        }
        private void 清空列表ToolStripMenuItemClick(object sender, EventArgs e)
        {
            checked
            {
                for (int i = this.GridV.Rows.Count - 1; i >= 0; i--)
                {
                    try
                    {
                        this.GridV.Rows[i].Cells[1].Selected = true;
                        int index = this.GridV.CurrentRow.Index;
                        string text = Convert.ToString(this.GridV.Rows[index].Cells[1].Value);
                        string text2 = Convert.ToString(this.GridV.Rows[index].Cells[2].Value);
                        string text3 = Convert.ToString(this.GridV.Rows[index].Cells[3].Value);
                        this.GridV.Rows.Remove(this.GridV.CurrentRow);
                        
                    }
                    catch (Exception)
                    {
                    }
                }
            }
        }
        private void 断开连接ToolStripMenuItemClick(object sender, EventArgs e)
        {
            try
            {
                int index = this.GridV.CurrentRow.Index;
                string leiX = Convert.ToString(this.GridV.Rows[index].Cells[4].Value);
                string a = Convert.ToString(this.GridV.Rows[index].Cells[2].Value);
                string a2 = Convert.ToString(this.GridV.Rows[index].Cells[3].Value);
                ComunicationType leiXing = Program.GetLeiXing(leiX);
                if (leiXing != 0)
                {
                    Socket socket = Program.GetSocket(leiXing, a, a2);
                    socket.Close();
                }
            }
            catch
            {
            }
        }
        private void cbHeader_OnCheckBoxClicked(bool state)
        {
            Thread.Sleep(0);
            if (base.InvokeRequired)
            {
                base.Invoke(new AddressList.cbHeader_OnCheckBoxClickedDelegate(this.cbHeader_OnCheckBoxClicked), new object[]
				{
					state
				});
            }
            else
            {
                this.CheckALL(state);
            }
        }
        private void CheckALL(bool CK)
        {
            Thread.Sleep(0);
            checked
            {
                if (base.InvokeRequired)
                {
                    base.Invoke(new AddressList.CheckALLDelegate(this.CheckALL), new object[]
					{
						CK
					});
                }
                else
                {
                    for (int i = 0; i < this.GridV.Rows.Count; i++)
                    {
                        this.GridV.Rows[i].Cells[0].Value = (CK ? 1 : 0);
                    }
                    this.GridV.Refresh();
                    Application.DoEvents();
                }
            }
        }
        private void AddClient(string obj)
        {
            Thread.Sleep(0);
            checked
            {
                if (base.InvokeRequired)
                {
                    base.Invoke(new AddressList.AddClientDelegate(this.AddClient), new object[]
					{
						obj
					});
                }
                else
                {
                    try
                    {
                        string text = obj.Split(new char[]
						{
							','
						})[0];
                        string text2 = obj.Split(new char[]
						{
							','
						})[1];
                        string a = obj.Split(new char[]
						{
							','
						})[2];
                        bool flag = true;
                        Application.DoEvents();
                        for (int i = this.GridV.Rows.Count - 1; i >= 0; i--)
                        {
                            string b = string.Empty;
                            string b2 = string.Empty;
                            string leiX = string.Empty;
                            Application.DoEvents();
                            if (!this.GridV.Rows[i].IsNewRow)
                            {
                                b = Convert.ToString(this.GridV.Rows[i].Cells[2].Value);
                                b2 = Convert.ToString(this.GridV.Rows[i].Cells[3].Value);
                                leiX = Convert.ToString(this.GridV.Rows[i].Cells[4].Value);
                            }
                            Application.DoEvents();
                            if (text == b & text2 == b2 & Program.GetLeiXing(leiX) == ComunicationType.TCPMyisServer)
                            {
                                flag = false;
                                break;
                            }
                        }
                        Application.DoEvents();
                        if (flag)
                        {
                            this.GridV.Rows.Add();
                            int index = this.GridV.Rows.Count - 1;
                            this.GridV.Rows[index].Cells[0].Value = 1;
                            this.GridV.Rows[index].Cells[1].Value = "在线终端";
                            this.GridV.Rows[index].Cells[2].Value = text;
                            this.GridV.Rows[index].Cells[3].Value = text2;
                            this.GridV.Rows[index].Cells[4].Value = ((a == "1") ? "GPRS(服务端)" : ((a == "0") ? "串口模式" : ((a == "3") ? "UDP模式" : "GPRS(客户端)")));
                            this.GridV.Rows[index].Cells[5].Value = Resources.NONE;
                        }
                    }
                    catch
                    {
                    }
                }
            }
        }
        private void Timer1Tick(object sender, EventArgs e)
        {
            checked
            {
                try
                {
                    for (int i = this.GridV.Rows.Count - 1; i >= 0; i--)
                    {
                        if (Program.GetLeiXing(Convert.ToString(this.GridV.Rows[i].Cells[4].Value)) == ComunicationType.TCPMyisServer)
                        {
                            Application.DoEvents();
                            Thread.Sleep(1);
                            string a1 = Convert.ToString(this.GridV.Rows[i].Cells[2].Value);
                            string a2 = Convert.ToString(this.GridV.Rows[i].Cells[3].Value);
                            try
                            {
                                if (Program.tcplistener.clients.Exists((TCPClientInfo gcl) => gcl.A1 == a1 & gcl.A2 == a2))
                                {
                                    this.GridV.Rows[i].Cells[5].Value = Resources.RIGHT;
                                }
                                else
                                {
                                    this.GridV.Rows[i].Cells[5].Value = Resources.WRONG;
                                }
                            }
                            catch
                            {
                            }
                        }
                        else
                        {
                            if (Program.GetLeiXing(Convert.ToString(this.GridV.Rows[i].Cells[4].Value)) == ComunicationType.TCPMyisClient)
                            {
                                bool flag = Program.Connecter_Socket.Connected & !Program.Connecter_Socket.Poll(1000, SelectMode.SelectRead);
                                try
                                {
                                    this.GridV.Rows[i].Cells[5].Value = (flag ? Resources.RIGHT : Resources.WRONG);
                                }
                                catch
                                {
                                }
                            }
                            else
                            {
                                if (Program.GetLeiXing(Convert.ToString(this.GridV.Rows[i].Cells[4].Value)) == ComunicationType.Serial)
                                {
                                    if (this.GetIndex("COM" + Program.gComPort.ToString("D2"), Program.gComList) >= 0)
                                    {
                                        this.GridV.Rows[i].Cells[5].Value = Resources.RIGHT;
                                    }
                                }
                                else
                                {
                                    if (Program.GetLeiXing(Convert.ToString(this.GridV.Rows[i].Cells[4].Value)) == ComunicationType.UDP)
                                    {
                                        this.GridV.Rows[i].Cells[5].Value = Resources.RIGHT;
                                    }
                                }
                            }
                        }
                    }
                }
                catch
                {
                }
            }
        }
        private int GetIndex(string pText, string[] allitem)
        {
            checked
            {
                int result;
                for (int i = 0; i < allitem.Length; i++)
                {
                    if (allitem[i].IndexOf(pText) >= 0)
                    {
                        result = i;
                        return result;
                    }
                }
                result = -1;
                return result;
            }
        }
        private void 终端列表ToolStripMenuItemClick(object sender, EventArgs e)
        {
            this.清空列表ToolStripMenuItemClick(sender, e);
            DLT698Opera dLT698Opera = new DLT698Opera();
            dLT698Opera.ListenPort = Program.gPort;
            dLT698Opera.CID = Program.CID;
            dLT698Opera.Tp = Program.Tp;
            dLT698Opera.PW = "";
            dLT698Opera.Flag = Program.Flag;
            dLT698Opera.FrameDelay = Program.gDelay;
            dLT698Opera.Delay = Program.gDelay;
            dLT698Opera.Assert.SEQ = false;
            dLT698Opera.Assert.Tpv = false;
            dLT698Opera.A1 = "0";
            dLT698Opera.A2 = "0";
            dLT698Opera.MSA = Program.MSA;
            dLT698Opera.AFN = "00";
            dLT698Opera.FN = "0009";
            dLT698Opera.PN = "0000";
            dLT698Opera.SendMSG = "";
            dLT698Opera.m_Port = Program.GetSocket(ComunicationType.TCPMyisClient, "", "");
            dLT698Opera.OperType = ComunicationType.TCPMyisClient;
            bool flag = dLT698Opera.Open(Program.RemotePort, Program.RemoteIP);
            checked
            {
                if (flag)
                {
                    bool flag2 = dLT698Opera.SendData();
                    if (flag2)
                    {
                        string text = DataConvert.HexStrToASCII(dLT698Opera.ReceiveMSG);
                        if (text.Length > 0)
                        {
                            string[] array = text.Split(new char[]
							{
								','
							});
                            for (int i = 0; i < array.Length; i++)
                            {
                                string[] array2 = array[i].Split(new char[]
								{
									'|'
								});
                                if (array2.Length > 1)
                                {
                                    this.AddClient(array2[0] + "," + array2[1] + ",2");
                                }
                            }
                        }
                    }
                }
                dLT698Opera.Close();
                this.GridV.EndEdit();
            }
        }
        private string HexStrToASCII(string strValue)
        {
            byte[] array = new byte[strValue.Length / 2];
            int num = 0;
            checked
            {
                for (int i = 0; i < strValue.Length / 2; i++)
                {
                    if ((byte)int.Parse(strValue.Substring(i * 2, 2), NumberStyles.HexNumber) != 0)
                    {
                        array[num] = (byte)int.Parse(strValue.Substring(i * 2, 2), NumberStyles.HexNumber);
                        num++;
                    }
                }
                return Encoding.Default.GetString(array, 0, num);
            }
        }
        private void OnCellPainting(object sender, DataGridViewCellPaintingEventArgs e)
        {
            try
            {
                Color color = Color.FromKnownColor(KnownColor.Control);
                Color color2 = Color.FromKnownColor(KnownColor.Control);
                Rectangle rect = checked(new Rectangle(e.CellBounds.X - 1, e.CellBounds.Y - 1, e.CellBounds.Width, e.CellBounds.Height));
                if (e.ColumnIndex == -1)
                {
                    Color color3 = Color.FromArgb(241, 244, 248);
                    Color color4 = color2;
                    using (Brush brush = new LinearGradientBrush(e.CellBounds, color3, color4, LinearGradientMode.Vertical))
                    {
                        e.Graphics.FillRectangle(brush, e.CellBounds);
                        e.Graphics.DrawRectangle(Pens.Silver, rect);
                    }
                    DataGridViewPaintParts paintParts = DataGridViewPaintParts.Border | DataGridViewPaintParts.ContentBackground | DataGridViewPaintParts.ContentForeground | DataGridViewPaintParts.ErrorIcon | DataGridViewPaintParts.Focus | DataGridViewPaintParts.SelectionBackground;
                    e.Paint(e.ClipBounds, paintParts);
                    e.Handled = true;
                }
                if (e.RowIndex == -1)
                {
                    Color color3 = Color.FromArgb(241, 244, 248);
                    Color color4 = color;
                    using (Brush brush = new LinearGradientBrush(e.CellBounds, color3, color4, LinearGradientMode.Vertical))
                    {
                        e.Graphics.FillRectangle(brush, e.CellBounds);
                        e.Graphics.DrawRectangle(Pens.Silver, rect);
                    }
                    DataGridViewPaintParts paintParts = DataGridViewPaintParts.Border | DataGridViewPaintParts.ContentBackground | DataGridViewPaintParts.ContentForeground | DataGridViewPaintParts.ErrorIcon | DataGridViewPaintParts.Focus | DataGridViewPaintParts.SelectionBackground;
                    e.Paint(e.ClipBounds, paintParts);
                    e.Handled = true;
                }
                if (e.ColumnIndex == -1 && e.RowIndex == -1)
                {
                    e.Graphics.DrawRectangle(Pens.Silver, rect);
                }
            }
            catch
            {
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
            this.SaveTerminal();
            base.Dispose(disposing);
        }
        private void InitializeComponent()
        {
            base.SuspendLayout();
            this.components = new Container();
            this.contextMenuStrip1 = new ContextMenuStrip(this.components);
            this.添加终端ToolStripMenuItem = new ToolStripMenuItem();
            this.删除终端ToolStripMenuItem = new ToolStripMenuItem();
            this.toolStripMenuItem1 = new ToolStripSeparator();
            this.清空列表ToolStripMenuItem = new ToolStripMenuItem();
            this.toolStripMenuItem2 = new ToolStripSeparator();
            this.断开连接ToolStripMenuItem = new ToolStripMenuItem();
            this.toolStripMenuItem3 = new ToolStripSeparator();
            this.终端列表ToolStripMenuItem = new ToolStripMenuItem();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.contextMenuStrip1.SuspendLayout();

            this.contextMenuStrip1.Items.AddRange(new ToolStripItem[]
			{
				this.添加终端ToolStripMenuItem,
				this.删除终端ToolStripMenuItem,
				this.toolStripMenuItem1,
				this.清空列表ToolStripMenuItem,
				this.toolStripMenuItem2,
				this.断开连接ToolStripMenuItem,
				this.toolStripMenuItem3,
				this.终端列表ToolStripMenuItem
			});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new Size(153, 154);
            this.添加终端ToolStripMenuItem.Name = "添加终端ToolStripMenuItem";
            this.添加终端ToolStripMenuItem.Size = new Size(118, 22);
            this.添加终端ToolStripMenuItem.Text = "添加终端";
            this.添加终端ToolStripMenuItem.Click += new EventHandler(this.添加终端ToolStripMenuItemClick);
            this.删除终端ToolStripMenuItem.Name = "删除终端ToolStripMenuItem";
            this.删除终端ToolStripMenuItem.Size = new Size(118, 22);
            this.删除终端ToolStripMenuItem.Text = "删除终端";
            this.删除终端ToolStripMenuItem.Click += new EventHandler(this.删除终端ToolStripMenuItemClick);
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new Size(115, 6);
            this.清空列表ToolStripMenuItem.Name = "清空列表ToolStripMenuItem";
            this.清空列表ToolStripMenuItem.Size = new Size(118, 22);
            this.清空列表ToolStripMenuItem.Text = "清空列表";
            this.清空列表ToolStripMenuItem.Click += new EventHandler(this.清空列表ToolStripMenuItemClick);
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new Size(115, 6);
            this.断开连接ToolStripMenuItem.Name = "断开连接ToolStripMenuItem";
            this.断开连接ToolStripMenuItem.Size = new Size(118, 22);
            this.断开连接ToolStripMenuItem.Text = "断开连接";
            this.断开连接ToolStripMenuItem.Click += new EventHandler(this.断开连接ToolStripMenuItemClick);
            this.toolStripMenuItem3.Name = "toolStripMenuItem3";
            this.toolStripMenuItem3.Size = new Size(115, 6);
            this.终端列表ToolStripMenuItem.Name = "终端列表ToolStripMenuItem";
            this.终端列表ToolStripMenuItem.Size = new Size(152, 22);
            this.终端列表ToolStripMenuItem.Text = "终端列表";
            this.终端列表ToolStripMenuItem.Click += new EventHandler(this.终端列表ToolStripMenuItemClick);
            this.timer1.Tick += new EventHandler(this.Timer1Tick);
            base.AutoScaleDimensions = new SizeF(6f, 12f);

            this.BackColor = Color.FromArgb(239, 237, 226);
            base.ClientSize = new Size(188, 387);
            base.CloseButton = false;
            base.CloseButtonVisible = false;
            base.Name = "AddressList";
            base.ShowHint = DockState.DockLeft;
            base.TabPageContextMenuStrip = this.contextMenuStrip1;
            this.Text = "终端列表";
            this.contextMenuStrip1.ResumeLayout(false);
            base.ResumeLayout(false);
        }
    }
}
