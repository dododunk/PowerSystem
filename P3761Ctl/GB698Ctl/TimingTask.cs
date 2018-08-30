using GB698Cls;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;
using WinFormsUI.Docking;
namespace GB698Ctl
{
	public class TimingTask : DockContent
	{
		private delegate void cbHeader_OnCheckBoxClickedDelegate(bool state);
		public delegate void CheckALLDelegate(bool CK);
		private delegate void TimeRunDelegate();
		private delegate void RunDelegate();
		public delegate void AddRowDelegate(string _Categories, string _Name, string iA1, string iA2, string iAFN, string iFN, string iPN, string iData);
		private DLT698_Recv gAS = new DLT698_Recv();
		public CollapseDataGridView grid1 = new CollapseDataGridView();
		private bool IsCustomize;
		private string CustomizeItems = string.Empty;
		private List<RW698Data> gThread = new List<RW698Data>();
		private long i = 0L;
		private IContainer components = null;
		private ToolStripLabel toolStripLabel2;
		private ToolStripSeparator toolStripSeparator2;
		private ToolStripButton toolStripButton5;
		private ToolStripSeparator toolStripSeparator1;
		private ToolStripButton toolStripButton4;
		private ToolStripSeparator toolStripSeparator6;
		private ToolStripButton toolStripButton3;
		private ToolStripSeparator toolStripSeparator5;
		private ToolStripComboBox toolStripComboBox1;
		private ToolStripLabel toolStripLabel4;
		private ToolStrip toolStrip1;
		private System.Windows.Forms.Timer timer1;
		private Panel panel1;
		public TimingTask()
		{
			this.InitializeComponent();
			this.timer1.Interval = 1000;
			this.grid1.Parent = this.panel1;
			this.grid1.Dock = DockStyle.Fill;
			this.grid1.CellContentClick += new DataGridViewCellEventHandler(this.GridCellContentClick);
			Application.DoEvents();
			this.InitSys();
			Application.DoEvents();
			this.InitGrid(this.grid1, "");
			Application.DoEvents();
		}
		private void InitSys()
		{
			this.toolStripComboBox1.Items.Clear();
			string[] faNames = Program.gFaDataBase.GetFaNames();
			checked
			{
				for (int i = 0; i < faNames.Length; i++)
				{
					if (!string.IsNullOrEmpty(faNames[i]))
					{
						this.toolStripComboBox1.Items.Add(faNames[i]);
					}
				}
			}
		}
		private void InitGrid(DataGridView Grid, string user)
		{
			Grid.Columns.Clear();
			Grid.Rows.Clear();
			Grid.MultiSelect = false;
			Grid.BorderStyle = BorderStyle.None;
			Grid.BackgroundColor = Color.FromKnownColor(KnownColor.White);
			Grid.GridColor = Color.FromKnownColor(KnownColor.ActiveBorder);
			Grid.ColumnHeadersDefaultCellStyle.Alignment = DataGridViewContentAlignment.MiddleCenter;
			Grid.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.EnableResizing;
			Grid.ColumnHeadersHeight = 28;
			DataGridViewTextBoxColumn dataGridViewTextBoxColumn = new DataGridViewTextBoxColumn();
			dataGridViewTextBoxColumn.HeaderText = "项目分类";
			dataGridViewTextBoxColumn.Name = "zdmc";
			dataGridViewTextBoxColumn.Width = 80;
			dataGridViewTextBoxColumn.ReadOnly = true;
			dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewTextBoxColumn);
			dataGridViewTextBoxColumn = new DataGridViewTextBoxColumn();
			dataGridViewTextBoxColumn.HeaderText = "项目名称";
			dataGridViewTextBoxColumn.Name = "gybz";
			dataGridViewTextBoxColumn.Width = 120;
			dataGridViewTextBoxColumn.ReadOnly = true;
			dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewTextBoxColumn);
			dataGridViewTextBoxColumn = new DataGridViewTextBoxColumn();
			dataGridViewTextBoxColumn.HeaderText = "AFN";
			dataGridViewTextBoxColumn.Name = "gygs";
			dataGridViewTextBoxColumn.Width = 35;
			dataGridViewTextBoxColumn.ReadOnly = true;
			dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewTextBoxColumn);
			dataGridViewTextBoxColumn = new DataGridViewTextBoxColumn();
			dataGridViewTextBoxColumn.HeaderText = "FN";
			dataGridViewTextBoxColumn.Name = "xzjs";
			dataGridViewTextBoxColumn.Width = 35;
			dataGridViewTextBoxColumn.ReadOnly = true;
			dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewTextBoxColumn);
			dataGridViewTextBoxColumn = new DataGridViewTextBoxColumn();
			dataGridViewTextBoxColumn.HeaderText = "PN";
			dataGridViewTextBoxColumn.Name = "kzm";
			dataGridViewTextBoxColumn.Width = 35;
			dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewTextBoxColumn);
			dataGridViewTextBoxColumn = new DataGridViewTextBoxColumn();
			dataGridViewTextBoxColumn.HeaderText = "发送数据";
			dataGridViewTextBoxColumn.Name = "ckz";
			dataGridViewTextBoxColumn.Width = 80;
			dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewTextBoxColumn);
			DataGridViewCheckBoxColumn dataGridViewCheckBoxColumn = new DataGridViewCheckBoxColumn();
			DatagridViewCheckBoxHeader.DatagridViewCheckBoxHeaderCell datagridViewCheckBoxHeaderCell = new DatagridViewCheckBoxHeader.DatagridViewCheckBoxHeaderCell();
			dataGridViewCheckBoxColumn.HeaderCell = datagridViewCheckBoxHeaderCell;
			dataGridViewCheckBoxColumn.Width = 25;
			Grid.Columns.Add(dataGridViewCheckBoxColumn);
			datagridViewCheckBoxHeaderCell.OnCheckBoxClicked += new DatagridViewCheckBoxHeader.CheckBoxClickedHandler(this.cbHeader_OnCheckBoxClicked);
			dataGridViewTextBoxColumn = new DataGridViewTextBoxColumn();
			dataGridViewTextBoxColumn.HeaderText = "A1";
			dataGridViewTextBoxColumn.Name = "ckzA1";
			dataGridViewTextBoxColumn.Width = 35;
			dataGridViewTextBoxColumn.ReadOnly = true;
			dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewTextBoxColumn);
			dataGridViewTextBoxColumn = new DataGridViewTextBoxColumn();
			dataGridViewTextBoxColumn.HeaderText = "A2";
			dataGridViewTextBoxColumn.Name = "ckzA2";
			dataGridViewTextBoxColumn.Width = 40;
			dataGridViewTextBoxColumn.ReadOnly = true;
			dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewTextBoxColumn);
			DataGridViewLinkColumn dataGridViewLinkColumn = new DataGridViewLinkColumn();
			dataGridViewLinkColumn.HeaderText = "接收数据";
			dataGridViewLinkColumn.Name = "ckz";
			dataGridViewLinkColumn.Width = 123;
			dataGridViewLinkColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewLinkColumn);
			dataGridViewTextBoxColumn = new DataGridViewTextBoxColumn();
			dataGridViewTextBoxColumn.HeaderText = "时间";
			dataGridViewTextBoxColumn.Name = "ckzsj";
			dataGridViewTextBoxColumn.ReadOnly = true;
			dataGridViewTextBoxColumn.Width = 60;
			dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewTextBoxColumn);
			Grid.AllowUserToAddRows = false;
			checked
			{
				if (!string.IsNullOrEmpty(user))
				{
					string[] aLLItems = Program.gFaDataBase.GetALLItems(user);
					for (int i = 0; i < aLLItems.Length; i++)
					{
						if (aLLItems[i].Length > 0)
						{
							string[] array = aLLItems[i].Split(new char[]
							{
								','
							});
							this.AddRow(array[0], array[1], "", "", array[2], array[3], array[4], array[5]);
						}
					}
				}
			}
		}
		private void GridCellContentClick(object sender, DataGridViewCellEventArgs e)
		{
			int columnIndex = e.ColumnIndex;
			int rowIndex = e.RowIndex;
			if (columnIndex == 9 && e.RowIndex != -1 && !this.grid1.Rows[e.RowIndex].IsNewRow)
			{
				string text = Convert.ToString(this.grid1.Rows[rowIndex].Cells[2].Value);
				string text2 = Convert.ToString(this.grid1.Rows[rowIndex].Cells[3].Value);
				string text3 = Convert.ToString(this.grid1.Rows[rowIndex].Cells[columnIndex].Value);
				this.IsCustomize = (Convert.ToString(this.grid1.Rows[rowIndex].Cells[0].Value) == "自定义规约");
				this.CustomizeItems = Program.gFaDataBase.GetCustomizeItems(text, text2);
				if (Program.gAnalysis == 0)
				{
					MainForm.gMainForm.gDataParse.Activate();
					MainForm.gMainForm.gDataParse.IsCustomize = this.IsCustomize;
					MainForm.gMainForm.gDataParse.CustomizeItems = this.CustomizeItems;
					MainForm.gMainForm.gDataParse.SetText(text3, text, text2);
				}
				else
				{
					new FormFactory
					{
						IsCustomize = this.IsCustomize,
						CustomizeItems = this.CustomizeItems
					}.DisplayR(text, text2, text3);
				}
			}
		}
		private void cbHeader_OnCheckBoxClicked(bool state)
		{
			Thread.Sleep(0);
			if (base.InvokeRequired)
			{
				base.Invoke(new TimingTask.cbHeader_OnCheckBoxClickedDelegate(this.cbHeader_OnCheckBoxClicked), new object[]
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
					base.Invoke(new TimingTask.CheckALLDelegate(this.CheckALL), new object[]
					{
						CK
					});
				}
				else
				{
					for (int i = 0; i < this.grid1.Rows.Count; i++)
					{
						this.grid1.Rows[i].Cells[6].Value = (CK ? 1 : 0);
					}
					this.grid1.Refresh();
				}
			}
		}
		private void ToolStripButton3Click(object sender, EventArgs e)
		{
			this.timer1.Enabled = true;
		}
		private void ToolStripButton4Click(object sender, EventArgs e)
		{
			this.timer1.Enabled = false;
			this.toolStripLabel2.Text = "倒计时:0秒";
		}
		private void TimeRun()
		{
			Thread.Sleep(0);
			checked
			{
				if (base.InvokeRequired)
				{
					base.Invoke(new TimingTask.TimeRunDelegate(this.TimeRun), new object[0]);
				}
				else
				{
					this.grid1.Refresh();
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
				}
			}
		}
		private void Run()
		{
			Thread.Sleep(0);
			checked
			{
				if (base.InvokeRequired)
				{
					base.Invoke(new TimingTask.RunDelegate(this.Run), new object[0]);
				}
				else
				{
					for (int i = 0; i < this.grid1.Rows.Count; i++)
					{
						if (this.grid1.Rows[i] is CollapseDataGridViewRow)
						{
							string aFN = Convert.ToString(this.grid1.Rows[i].Cells[2].Value);
							string fN = Convert.ToString(this.grid1.Rows[i].Cells[3].Value);
							string value = Convert.ToString(this.grid1.Rows[i].Cells[4].Value);
							string value2 = Convert.ToString(this.grid1.Rows[i].Cells[5].Value);
							if (string.IsNullOrEmpty(value))
							{
								this.grid1.Rows[i].Cells[4].Value = InputPN.GetPN(aFN, fN);
							}
							if (string.IsNullOrEmpty(value2))
							{
								this.grid1.Rows[i].Cells[5].Value = InputPN.GetData(aFN, fN);
							}
						}
					}
					for (int i = 0; i < Program.gList.Count; i++)
					{
						Application.DoEvents();
						if (Program.gList[i].Checked)
						{
							RW698Data rW698Data = new RW698Data();
							rW698Data.ListIndex = i;
							rW698Data.grid1 = this.grid1;
							rW698Data.needrun = true;
							rW698Data.isruning = true;
							new Thread(new ThreadStart(rW698Data.Run))
							{
								IsBackground = true
							}.Start();
							this.gThread.Add(rW698Data);
							Application.DoEvents();
						}
					}
				}
			}
		}
		private void Timer1Tick(object sender, EventArgs e)
		{
			int num;
			checked
			{
				this.i += 1L;
				num = Program.TimingTask_Time * 60;
				this.toolStripLabel2.Text = "倒计时:" + (unchecked((long)num) - this.i).ToString() + "秒";
			}
			if (this.i == (long)num)
			{
				this.i = 0L;
				new Thread(new ThreadStart(this.TimeRun))
				{
					IsBackground = true
				}.Start();
			}
		}
		public void AddRow(string _Categories, string _Name, string iA1, string iA2, string iAFN, string iFN, string iPN, string iData)
		{
			Thread.Sleep(0);
			if (base.InvokeRequired)
			{
				base.Invoke(new TimingTask.AddRowDelegate(this.AddRow), new object[]
				{
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
				Color backColor = Color.FromArgb(240, 240, 240);
				CollapseDataGridViewRow collapseDataGridViewRow = new CollapseDataGridViewRow();
				foreach (DataGridViewColumn dataGridViewColumn in this.grid1.Columns)
				{
					collapseDataGridViewRow.Cells.Add(dataGridViewColumn.CellTemplate.Clone() as DataGridViewCell);
				}
				collapseDataGridViewRow.IsCollapse = false;
				collapseDataGridViewRow.Cells[0].Value = _Categories.Trim();
				collapseDataGridViewRow.Cells[0].Style.BackColor = backColor;
				collapseDataGridViewRow.Cells[1].Value = _Name;
				collapseDataGridViewRow.Cells[1].Style.BackColor = backColor;
				collapseDataGridViewRow.Cells[2].Value = iAFN;
				collapseDataGridViewRow.Cells[2].Style.BackColor = backColor;
				collapseDataGridViewRow.Cells[3].Value = iFN.PadLeft(4, '0');
				collapseDataGridViewRow.Cells[3].Style.BackColor = backColor;
				collapseDataGridViewRow.Cells[4].Value = iPN;
				collapseDataGridViewRow.Cells[4].Style.BackColor = backColor;
				collapseDataGridViewRow.Cells[5].Value = "";
				collapseDataGridViewRow.Cells[5].Style.BackColor = backColor;
				collapseDataGridViewRow.Cells[6].Value = 1;
				collapseDataGridViewRow.Cells[6].Style.BackColor = backColor;
				collapseDataGridViewRow.Cells[7].Value = "";
				collapseDataGridViewRow.Cells[7].Style.BackColor = backColor;
				collapseDataGridViewRow.Cells[8].Value = "";
				collapseDataGridViewRow.Cells[8].Style.BackColor = backColor;
				collapseDataGridViewRow.Cells[9].Value = "";
				collapseDataGridViewRow.Cells[9].Style.BackColor = backColor;
				collapseDataGridViewRow.Cells[10].Value = "";
				collapseDataGridViewRow.Cells[10].Style.BackColor = backColor;
				this.grid1.Rows.Add(collapseDataGridViewRow);
			}
		}
		private void ToolStripButton5Click(object sender, EventArgs e)
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
            this.components = new System.ComponentModel.Container();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.toolStripLabel4 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripComboBox1 = new System.Windows.Forms.ToolStripComboBox();
            this.toolStripSeparator5 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton3 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator6 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton4 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton5 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripLabel2 = new System.Windows.Forms.ToolStripLabel();
            this.panel1 = new System.Windows.Forms.Panel();
            this.toolStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // timer1
            // 
            this.timer1.Interval = 1000;
            this.timer1.Tick += new System.EventHandler(this.Timer1Tick);
            // 
            // toolStrip1
            // 
            this.toolStrip1.BackColor = System.Drawing.Color.Transparent;
            this.toolStrip1.CanOverflow = false;
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripLabel4,
            this.toolStripComboBox1,
            this.toolStripSeparator5,
            this.toolStripButton3,
            this.toolStripSeparator6,
            this.toolStripButton4,
            this.toolStripSeparator1,
            this.toolStripButton5,
            this.toolStripSeparator2,
            this.toolStripLabel2});
            this.toolStrip1.LayoutStyle = System.Windows.Forms.ToolStripLayoutStyle.HorizontalStackWithOverflow;
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(586, 25);
            this.toolStrip1.TabIndex = 33;
            // 
            // toolStripLabel4
            // 
            this.toolStripLabel4.Name = "toolStripLabel4";
            this.toolStripLabel4.Size = new System.Drawing.Size(55, 22);
            this.toolStripLabel4.Text = "用户方案";
            // 
            // toolStripComboBox1
            // 
            this.toolStripComboBox1.Name = "toolStripComboBox1";
            this.toolStripComboBox1.Size = new System.Drawing.Size(150, 25);
            // 
            // toolStripSeparator5
            // 
            this.toolStripSeparator5.Name = "toolStripSeparator5";
            this.toolStripSeparator5.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton3
            // 
            this.toolStripButton3.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton3.Name = "toolStripButton3";
            this.toolStripButton3.Size = new System.Drawing.Size(35, 22);
            this.toolStripButton3.Text = "开始";
            this.toolStripButton3.ToolTipText = "开始";
            this.toolStripButton3.Click += new System.EventHandler(this.ToolStripButton3Click);
            // 
            // toolStripSeparator6
            // 
            this.toolStripSeparator6.Name = "toolStripSeparator6";
            this.toolStripSeparator6.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton4
            // 
            this.toolStripButton4.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton4.Name = "toolStripButton4";
            this.toolStripButton4.Size = new System.Drawing.Size(35, 22);
            this.toolStripButton4.Text = "停止";
            this.toolStripButton4.Click += new System.EventHandler(this.ToolStripButton4Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton5
            // 
            this.toolStripButton5.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton5.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton5.Name = "toolStripButton5";
            this.toolStripButton5.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton5.Text = "清空";
            this.toolStripButton5.Click += new System.EventHandler(this.ToolStripButton5Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripLabel2
            // 
            this.toolStripLabel2.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.toolStripLabel2.Name = "toolStripLabel2";
            this.toolStripLabel2.Size = new System.Drawing.Size(64, 22);
            this.toolStripLabel2.Text = "倒计时:0秒";
            // 
            // panel1
            // 
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 25);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(586, 365);
            this.panel1.TabIndex = 34;
            // 
            // TimingTask
            // 
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(239)))), ((int)(((byte)(237)))), ((int)(((byte)(226)))));
            this.ClientSize = new System.Drawing.Size(586, 390);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.toolStrip1);
            this.Font = new System.Drawing.Font("SimSun", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Name = "TimingTask";
            this.Text = "定时任务";
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

		}
	}
}
