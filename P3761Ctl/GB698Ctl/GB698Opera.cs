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
	public class GB698Opera : DockContent
	{
		private delegate void cbHeader_OnCheckBoxClickedDelegate(bool state);
		public delegate void CheckALLDelegate(bool CK);
		private delegate void RunDelegate();
		public delegate void AddRowDelegate(string _Categories, string _Name, string iA1, string iA2, string iAFN, string iFN, string iPN, string iData);
		private DLT698_Recv gAS = new DLT698_Recv();
		public CollapseDataGridView grid1 = new CollapseDataGridView();
		private bool IsCustomize;
		private string CustomizeItems = string.Empty;
		private List<RW698Data> gThread = new List<RW698Data>();
		private IContainer components = null;
		private ToolStripMenuItem ToolStripMenuItemClearAll;
		private ToolStripMenuItem ToolStripMenuItemClearData;
		private ToolStripSeparator toolStripMenuItem1;
		private ToolStripSeparator toolStripSeparator1;
		private ToolStripButton toolStripButton4;
		private Panel panel1;
		private ToolStripSeparator toolStripSeparator2;
		private ToolStripButton toolStripButton3;
		private ToolStripMenuItem ToolStripMenuItemDeleteLine;
		private ContextMenuStrip contextMenuStrip1;
		private ToolStripSeparator toolStripSeparator6;
		private ToolStripButton toolStripButton_Start;
		private ToolStripSeparator toolStripSeparator5;
		private ToolStripButton button2;
		private ToolStripButton toolStripButton2;
		private ToolStripComboBox toolStripComboBox1;
		private ToolStripLabel toolStripLabel4;
		private ToolStrip toolStrip1;
		public GB698Opera()
		{
			this.InitializeComponent();
			this.grid1.Parent = this.panel1;
			this.grid1.Dock = DockStyle.Fill;
			this.grid1.CellDoubleClick += new DataGridViewCellEventHandler(this.GridCellClick);
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
				}
			}
		}
		private void InitGrid(DataGridView Grid, string user)
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
		private void cbHeader_OnCheckBoxClicked(bool state)
		{
			Thread.Sleep(0);
			if (base.InvokeRequired)
			{
				base.Invoke(new GB698Opera.cbHeader_OnCheckBoxClickedDelegate(this.cbHeader_OnCheckBoxClicked), new object[]
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
					base.Invoke(new GB698Opera.CheckALLDelegate(this.CheckALL), new object[]
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
		private void GridCellClick(object sender, DataGridViewCellEventArgs e)
		{
			int columnIndex = e.ColumnIndex;
			int rowIndex = e.RowIndex;
			if (columnIndex == 5 && e.RowIndex != -1 && !this.grid1.Rows[e.RowIndex].IsNewRow)
			{
				this.grid1.EndEdit();
				string text = Convert.ToString(this.grid1.Rows[rowIndex].Cells[2].Value);
				string text2 = Convert.ToString(this.grid1.Rows[rowIndex].Cells[3].Value);
				string iValues = Convert.ToString(this.grid1.Rows[rowIndex].Cells[columnIndex].Value);
				this.IsCustomize = (Convert.ToString(this.grid1.Rows[rowIndex].Cells[0].Value) == "自定义规约");
				this.CustomizeItems = Program.gFaDataBase.GetCustomizeItems(text, text2);
				FormFactory frmOut = new FormFactory();
				frmOut.IsCustomize = this.IsCustomize;
				frmOut.CustomizeItems = this.CustomizeItems;
				this.grid1.Rows[rowIndex].Cells[columnIndex].Value = frmOut.CreateForm(text, text2, iValues);
				this.grid1.EndEdit();
			}
			if (columnIndex == 4 && e.RowIndex != -1 && !this.grid1.Rows[e.RowIndex].IsNewRow)
			{
				string text = Convert.ToString(this.grid1.Rows[rowIndex].Cells[2].Value);
				string text2 = Convert.ToString(this.grid1.Rows[rowIndex].Cells[3].Value);
				this.grid1.Rows[rowIndex].Cells[columnIndex].Value = InputPN.GetPN(text, text2);
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
		private void Button2Click(object sender, EventArgs e)
		{
			checked
			{
				if (this.toolStripComboBox1.Text == "")
				{
					MessageBox.Show("请输入方案名", "提示", MessageBoxButtons.OK);
				}
				else
				{
					if (MessageBox.Show("确定保存方案配置", "确定保存", MessageBoxButtons.YesNo) == DialogResult.Yes)
					{
						Program.gFaDataBase.DeleteFa(this.toolStripComboBox1.Text);
						for (int i = 0; i < this.grid1.Rows.Count; i++)
						{
							if (this.grid1.Rows[i] is CollapseDataGridViewRow)
							{
								Program.gFaDataBase.InsertFa(this.toolStripComboBox1.Text.Trim(), Convert.ToString(this.grid1.Rows[i].Cells[0].Value), Convert.ToString(this.grid1.Rows[i].Cells[1].Value), Convert.ToString(this.grid1.Rows[i].Cells[2].Value), Convert.ToString(this.grid1.Rows[i].Cells[3].Value), Convert.ToString(this.grid1.Rows[i].Cells[4].Value), Convert.ToString(this.grid1.Rows[i].Cells[5].Value));
							}
						}
						MessageBox.Show("保存完成", "提示", MessageBoxButtons.OK);
						this.InitSys();
					}
				}
			}
		}
		private void ToolStripButton2Click(object sender, EventArgs e)
		{
			if (this.toolStripComboBox1.Text == "")
			{
				MessageBox.Show("请输入方案名", "提示", MessageBoxButtons.OK);
			}
			else
			{
				if (MessageBox.Show("确定删除方案配置？", "确定删除", MessageBoxButtons.YesNo) == DialogResult.Yes)
				{
					Program.gFaDataBase.DeleteFa(this.toolStripComboBox1.Text);
					this.InitSys();
				}
			}
		}
		private void ToolStripMenuItemClick_DeleteLine(object sender, EventArgs e)
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
		private void ToolStripButton3Click(object sender, EventArgs e)
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
		private void 全部删除ToolStripMenuItemClick(object sender, EventArgs e)
		{
			this.InitGrid(this.grid1, "");
		}
		private void 清空数据ToolStripMenuItemClick(object sender, EventArgs e)
		{
			this.ToolStripButton3Click(sender, e);
		}
		private void ToolStripComboBox1SelectedIndexChanged(object sender, EventArgs e)
		{
		}
		private void ToolStripButton4Click(object sender, EventArgs e)
		{
			foreach (RW698Data current in this.gThread)
			{
				current.needrun = false;
			}
		}
		private void ToolStripButton_Start_Click(object sender, EventArgs e)
		{
			this.toolStripComboBox1.Enabled = false;
			this.toolStripButton_Start.Enabled = false;
			this.toolStripButton4.Enabled = true;
			Application.DoEvents();
			this.Refresh();
			this.grid1.Refresh();
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
				this.Run();
				while (true)
				{
					if (!this.gThread.Exists((RW698Data g698) => g698.isruning))
					{
						break;
					}
					Application.DoEvents();
				}
				this.gThread.Clear();
				this.toolStripComboBox1.Enabled = true;
				this.toolStripButton_Start.Enabled = true;
				this.toolStripButton4.Enabled = false;
			}
		}
		private void Run()
		{
			Thread.Sleep(0);
			checked
			{
				if (base.InvokeRequired)
				{
					base.Invoke(new GB698Opera.RunDelegate(this.Run), new object[0]);
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
		public void AddRow(string _Categories, string _Name, string iA1, string iA2, string iAFN, string iFN, string iPN, string iData)
		{
			Thread.Sleep(0);
			if (base.InvokeRequired)
			{
				base.Invoke(new GB698Opera.AddRowDelegate(this.AddRow), new object[]
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
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.ToolStripMenuItemDeleteLine = new System.Windows.Forms.ToolStripMenuItem();
            this.ToolStripMenuItemClearAll = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.ToolStripMenuItemClearData = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.toolStripLabel4 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripComboBox1 = new System.Windows.Forms.ToolStripComboBox();
            this.toolStripButton2 = new System.Windows.Forms.ToolStripButton();
            this.button2 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator5 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton_Start = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator6 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton4 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton3 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.panel1 = new System.Windows.Forms.Panel();
            this.contextMenuStrip1.SuspendLayout();
            this.toolStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ToolStripMenuItemDeleteLine,
            this.ToolStripMenuItemClearAll,
            this.toolStripMenuItem1,
            this.ToolStripMenuItemClearData});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(153, 98);
            // 
            // ToolStripMenuItemDeleteLine
            // 
            this.ToolStripMenuItemDeleteLine.Name = "ToolStripMenuItemDeleteLine";
            this.ToolStripMenuItemDeleteLine.Size = new System.Drawing.Size(152, 22);
            this.ToolStripMenuItemDeleteLine.Text = "删除项目";
            this.ToolStripMenuItemDeleteLine.Click += new System.EventHandler(this.ToolStripMenuItemClick_DeleteLine);
            // 
            // ToolStripMenuItemClearAll
            // 
            this.ToolStripMenuItemClearAll.Name = "ToolStripMenuItemClearAll";
            this.ToolStripMenuItemClearAll.Size = new System.Drawing.Size(152, 22);
            this.ToolStripMenuItemClearAll.Text = "全部删除";
            this.ToolStripMenuItemClearAll.Click += new System.EventHandler(this.全部删除ToolStripMenuItemClick);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(149, 6);
            // 
            // ToolStripMenuItemClearData
            // 
            this.ToolStripMenuItemClearData.Name = "ToolStripMenuItemClearData";
            this.ToolStripMenuItemClearData.Size = new System.Drawing.Size(152, 22);
            this.ToolStripMenuItemClearData.Text = "清空数据";
            this.ToolStripMenuItemClearData.Click += new System.EventHandler(this.清空数据ToolStripMenuItemClick);
            // 
            // toolStrip1
            // 
            this.toolStrip1.CanOverflow = false;
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripLabel4,
            this.toolStripComboBox1,
            this.toolStripButton2,
            this.button2,
            this.toolStripSeparator5,
            this.toolStripButton_Start,
            this.toolStripSeparator6,
            this.toolStripButton4,
            this.toolStripSeparator1,
            this.toolStripButton3,
            this.toolStripSeparator2});
            this.toolStrip1.LayoutStyle = System.Windows.Forms.ToolStripLayoutStyle.HorizontalStackWithOverflow;
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(622, 25);
            this.toolStrip1.TabIndex = 4;
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
            this.toolStripComboBox1.Size = new System.Drawing.Size(300, 25);
            this.toolStripComboBox1.SelectedIndexChanged += new System.EventHandler(this.ToolStripComboBox1SelectedIndexChanged);
            // 
            // toolStripButton2
            // 
            this.toolStripButton2.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton2.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton2.Name = "toolStripButton2";
            this.toolStripButton2.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton2.Text = "删除";
            this.toolStripButton2.Click += new System.EventHandler(this.ToolStripButton2Click);
            // 
            // button2
            // 
            this.button2.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.button2.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(23, 22);
            this.button2.Text = "保存";
            this.button2.Click += new System.EventHandler(this.Button2Click);
            // 
            // toolStripSeparator5
            // 
            this.toolStripSeparator5.Name = "toolStripSeparator5";
            this.toolStripSeparator5.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton_Start
            // 
            this.toolStripButton_Start.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton_Start.Name = "toolStripButton_Start";
            this.toolStripButton_Start.Size = new System.Drawing.Size(59, 22);
            this.toolStripButton_Start.Text = "开始召测";
            this.toolStripButton_Start.Click += new System.EventHandler(this.ToolStripButton_Start_Click);
            // 
            // toolStripSeparator6
            // 
            this.toolStripSeparator6.Name = "toolStripSeparator6";
            this.toolStripSeparator6.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton4
            // 
            this.toolStripButton4.Enabled = false;
            this.toolStripButton4.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton4.Name = "toolStripButton4";
            this.toolStripButton4.Size = new System.Drawing.Size(59, 22);
            this.toolStripButton4.Text = "停止操作";
            this.toolStripButton4.Click += new System.EventHandler(this.ToolStripButton4Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton3
            // 
            this.toolStripButton3.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton3.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton3.Name = "toolStripButton3";
            this.toolStripButton3.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton3.Text = "清空";
            this.toolStripButton3.Click += new System.EventHandler(this.ToolStripButton3Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
            // 
            // panel1
            // 
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 25);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(622, 342);
            this.panel1.TabIndex = 5;
            // 
            // GB698Opera
            // 
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(239)))), ((int)(((byte)(237)))), ((int)(((byte)(226)))));
            this.ClientSize = new System.Drawing.Size(622, 367);
            this.CloseButton = false;
            this.CloseButtonVisible = false;
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.toolStrip1);
            this.Font = new System.Drawing.Font("SimSun", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Name = "GB698Opera";
            this.Text = "方案操作";
            this.contextMenuStrip1.ResumeLayout(false);
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

		}
	}
}
