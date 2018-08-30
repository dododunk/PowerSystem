using GB698Cls;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using WinFormsUI.Docking;
namespace GB698Ctl
{
	public class FormDataOpera : DockContent
	{
		private DLT698_Recv gAS = new DLT698_Recv();
		private DBDataBase gDBDataBase = new DBDataBase();
		private string file = string.Empty;
		public DataGridViewEx grid1 = new DataGridViewEx();
		public DataGridViewEx grid2 = new DataGridViewEx();
		private bool IsCustomize;
		private string CustomizeItems = string.Empty;
		private IContainer components = null;
		private ToolStripSeparator toolStripSeparator2;
		private OpenFileDialog openFileDialog1;
		private ToolStripButton toolStripButton2;
		private ToolStripTextBox toolStripTextBox1;
		private ToolStripLabel toolStripLabel4;
		private ToolStrip toolStrip1;
		private SplitContainer splitContainer1;
		private ToolStripContentPanel ContentPanel;
		private ToolStripPanel LeftToolStripPanel;
		private ToolStripPanel RightToolStripPanel;
		private ToolStripPanel TopToolStripPanel;
		private ToolStripPanel BottomToolStripPanel;
		public FormDataOpera()
		{
			this.InitializeComponent();
			this.grid1.Parent = this.splitContainer1.Panel2;
			this.grid2.Parent = this.splitContainer1.Panel1;
			this.grid1.Dock = DockStyle.Fill;
			this.grid2.Dock = DockStyle.Fill;
			Application.DoEvents();
			this.InitGrid(this.grid1, "");
			Application.DoEvents();
			this.InitGrid(this.grid2);
			Application.DoEvents();
			this.grid2.CellClick += new DataGridViewCellEventHandler(this.GridCellClick);
			this.grid1.CellContentClick += new DataGridViewCellEventHandler(this.GridCellContentClick);
		}
		private void GridCellContentClick(object sender, DataGridViewCellEventArgs e)
		{
			int columnIndex = e.ColumnIndex;
			int rowIndex = e.RowIndex;
			if (columnIndex == 6 && e.RowIndex != -1 && !this.grid1.Rows[e.RowIndex].IsNewRow)
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
			if (columnIndex == 5 && e.RowIndex != -1 && !this.grid1.Rows[e.RowIndex].IsNewRow)
			{
				string text = Convert.ToString(this.grid1.Rows[rowIndex].Cells[2].Value);
				string text2 = Convert.ToString(this.grid1.Rows[rowIndex].Cells[3].Value);
				string text3 = Convert.ToString(this.grid1.Rows[rowIndex].Cells[columnIndex].Value);
				new FormFactory
				{
					IsCustomize = this.IsCustomize,
					CustomizeItems = this.CustomizeItems
				}.CreateForm(text, text2, text3);
			}
		}
		private void GridCellClick(object sender, DataGridViewCellEventArgs e)
		{
			int columnIndex = e.ColumnIndex;
			int rowIndex = e.RowIndex;
			string iA = Convert.ToString(this.grid2.Rows[rowIndex].Cells[0].Value);
			string iA2 = Convert.ToString(this.grid2.Rows[rowIndex].Cells[1].Value);
			this.LoadInformation(iA, iA2);
		}
		private void InitGrid(DataGridView Grid, string user)
		{
			Grid.Columns.Clear();
			Grid.Rows.Clear();
			Grid.AlternatingRowsDefaultCellStyle.BackColor = Color.FromArgb(240, 240, 240);
			Grid.MultiSelect = false;
			Grid.BorderStyle = BorderStyle.Fixed3D;
			Grid.BackgroundColor = Color.FromKnownColor(KnownColor.White);
			Grid.GridColor = Color.FromKnownColor(KnownColor.ActiveBorder);
			Grid.ColumnHeadersDefaultCellStyle.Alignment = DataGridViewContentAlignment.MiddleCenter;
			Grid.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.EnableResizing;
			Grid.ColumnHeadersHeight = 25;
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
			dataGridViewTextBoxColumn.Width = 150;
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
			dataGridViewTextBoxColumn.ReadOnly = true;
			dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewTextBoxColumn);
			DataGridViewLinkColumn dataGridViewLinkColumn = new DataGridViewLinkColumn();
			dataGridViewLinkColumn.HeaderText = "发送数据";
			dataGridViewLinkColumn.Name = "ckz";
			dataGridViewLinkColumn.Width = 80;
			dataGridViewLinkColumn.ReadOnly = true;
			dataGridViewLinkColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewLinkColumn);
			dataGridViewLinkColumn = new DataGridViewLinkColumn();
			dataGridViewLinkColumn.HeaderText = "接收数据";
			dataGridViewLinkColumn.Name = "ckz";
			dataGridViewLinkColumn.Width = 200;
			dataGridViewLinkColumn.ReadOnly = true;
			dataGridViewLinkColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewLinkColumn);
			dataGridViewTextBoxColumn = new DataGridViewTextBoxColumn();
			dataGridViewTextBoxColumn.HeaderText = "时间";
			dataGridViewTextBoxColumn.Name = "kddzm";
			dataGridViewTextBoxColumn.ReadOnly = true;
			dataGridViewTextBoxColumn.Width = 80;
			dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewTextBoxColumn);
			Grid.AllowUserToAddRows = false;
		}
		private void InitGrid(DataGridView Grid)
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
			dataGridViewTextBoxColumn.HeaderText = "行政区划码A1";
			dataGridViewTextBoxColumn.Name = "zdmc";
			dataGridViewTextBoxColumn.Width = 85;
			dataGridViewTextBoxColumn.ReadOnly = true;
			Grid.Columns.Add(dataGridViewTextBoxColumn);
			dataGridViewTextBoxColumn = new DataGridViewTextBoxColumn();
			dataGridViewTextBoxColumn.HeaderText = "终端地址A2";
			dataGridViewTextBoxColumn.Name = "gybz";
			dataGridViewTextBoxColumn.Width = 80;
			dataGridViewTextBoxColumn.ReadOnly = true;
			Grid.Columns.Add(dataGridViewTextBoxColumn);
		}
		private void LoadBars()
		{
			string[] aLLBars = this.gDBDataBase.GetALLBars();
			this.grid2.Rows.Clear();
			checked
			{
				for (int i = 0; i < aLLBars.Length; i++)
				{
					if (aLLBars[i].Length > 0)
					{
						string[] array = aLLBars[i].Split(new char[]
						{
							','
						});
						this.grid2.Rows.Add();
						this.grid2.Rows[i].Cells[0].Value = array[0].ToString();
						this.grid2.Rows[i].Cells[1].Value = array[1].ToString();
					}
				}
			}
		}
		private void LoadInformation(string iA1, string iA2)
		{
			string[] aLLItems = this.gDBDataBase.GetALLItems(iA1, iA2);
			this.grid1.Rows.Clear();
			checked
			{
				for (int i = 0; i < aLLItems.Length; i++)
				{
					if (aLLItems[i].Length > 0)
					{
						string[] array = aLLItems[i].Split(new char[]
						{
							','
						});
						this.grid1.Rows.Add();
						this.grid1.Rows[i].Cells[0].Value = array[0].ToString();
						this.grid1.Rows[i].Cells[1].Value = array[1].ToString();
						this.grid1.Rows[i].Cells[2].Value = array[2].ToString();
						this.grid1.Rows[i].Cells[3].Value = array[3].ToString();
						this.grid1.Rows[i].Cells[4].Value = array[4].ToString();
						this.grid1.Rows[i].Cells[5].Value = array[5].ToString();
						this.grid1.Rows[i].Cells[6].Value = array[6].ToString();
						this.grid1.Rows[i].Cells[7].Value = array[7].ToString();
					}
				}
			}
		}
		private void ToolStripButton2Click(object sender, EventArgs e)
		{
			this.openFileDialog1.Filter = "*.mdb|*.mdb";
			this.openFileDialog1.FileName = "";
			this.openFileDialog1.InitialDirectory = Program.SysPath;
			this.openFileDialog1.ShowDialog();
			if (!string.IsNullOrEmpty(this.openFileDialog1.FileName))
			{
				this.file = this.openFileDialog1.FileName;
				this.gDBDataBase.dbconnectstring = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + this.file + ";User Id=admin;Password=;";
				this.gDBDataBase.InitSys();
				this.toolStripTextBox1.Text = this.file;
				this.LoadBars();
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
			ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof(FormDataOpera));
			this.BottomToolStripPanel = new ToolStripPanel();
			this.TopToolStripPanel = new ToolStripPanel();
			this.RightToolStripPanel = new ToolStripPanel();
			this.LeftToolStripPanel = new ToolStripPanel();
			this.ContentPanel = new ToolStripContentPanel();
			this.openFileDialog1 = new OpenFileDialog();
			this.toolStrip1 = new ToolStrip();
			this.toolStripLabel4 = new ToolStripLabel();
			this.toolStripTextBox1 = new ToolStripTextBox();
			this.toolStripButton2 = new ToolStripButton();
			this.toolStripSeparator2 = new ToolStripSeparator();
			this.splitContainer1 = new SplitContainer();
			this.toolStrip1.SuspendLayout();
			((ISupportInitialize)this.splitContainer1).BeginInit();
			this.splitContainer1.SuspendLayout();
			base.SuspendLayout();
			this.BottomToolStripPanel.Location = new Point(0, 0);
			this.BottomToolStripPanel.Name = "BottomToolStripPanel";
			this.BottomToolStripPanel.Orientation = Orientation.Horizontal;
			this.BottomToolStripPanel.RowMargin = new Padding(3, 0, 0, 0);
			this.BottomToolStripPanel.Size = new Size(0, 0);
			this.TopToolStripPanel.Location = new Point(0, 0);
			this.TopToolStripPanel.Name = "TopToolStripPanel";
			this.TopToolStripPanel.Orientation = Orientation.Horizontal;
			this.TopToolStripPanel.RowMargin = new Padding(3, 0, 0, 0);
			this.TopToolStripPanel.Size = new Size(0, 0);
			this.RightToolStripPanel.Location = new Point(0, 0);
			this.RightToolStripPanel.Name = "RightToolStripPanel";
			this.RightToolStripPanel.Orientation = Orientation.Horizontal;
			this.RightToolStripPanel.RowMargin = new Padding(3, 0, 0, 0);
			this.RightToolStripPanel.Size = new Size(0, 0);
			this.LeftToolStripPanel.Location = new Point(0, 0);
			this.LeftToolStripPanel.Name = "LeftToolStripPanel";
			this.LeftToolStripPanel.Orientation = Orientation.Horizontal;
			this.LeftToolStripPanel.RowMargin = new Padding(3, 0, 0, 0);
			this.LeftToolStripPanel.Size = new Size(0, 0);
			this.ContentPanel.Size = new Size(710, 402);
			this.openFileDialog1.FileName = "openFileDialog1";
			this.openFileDialog1.Filter = "*.xml|*.xml";
			this.toolStrip1.CanOverflow = false;
			this.toolStrip1.Items.AddRange(new ToolStripItem[]
			{
				this.toolStripLabel4,
				this.toolStripTextBox1,
				this.toolStripButton2,
				this.toolStripSeparator2
			});
			this.toolStrip1.LayoutStyle = ToolStripLayoutStyle.HorizontalStackWithOverflow;
			this.toolStrip1.Location = new Point(0, 0);
			this.toolStrip1.Name = "toolStrip1";
			this.toolStrip1.Size = new Size(558, 25);
			this.toolStrip1.TabIndex = 4;
			this.toolStripLabel4.Name = "toolStripLabel4";
			this.toolStripLabel4.Size = new Size(41, 22);
			this.toolStripLabel4.Text = "数据库";
			this.toolStripTextBox1.Name = "toolStripTextBox1";
			this.toolStripTextBox1.Size = new Size(400, 25);
			this.toolStripButton2.DisplayStyle = ToolStripItemDisplayStyle.Image;
			this.toolStripButton2.Image = (Image)componentResourceManager.GetObject("toolStripButton2.Image");
			this.toolStripButton2.ImageTransparentColor = Color.Magenta;
			this.toolStripButton2.Name = "toolStripButton2";
			this.toolStripButton2.Size = new Size(23, 22);
			this.toolStripButton2.Text = "删除";
			this.toolStripButton2.Click += new EventHandler(this.ToolStripButton2Click);
			this.toolStripSeparator2.Name = "toolStripSeparator2";
			this.toolStripSeparator2.Size = new Size(6, 25);
			this.splitContainer1.Cursor = Cursors.Default;
			this.splitContainer1.Dock = DockStyle.Fill;
			this.splitContainer1.FixedPanel = FixedPanel.Panel1;
			this.splitContainer1.Location = new Point(0, 25);
			this.splitContainer1.Name = "splitContainer1";
			this.splitContainer1.Panel1MinSize = 0;
			this.splitContainer1.Panel2MinSize = 0;
			this.splitContainer1.Size = new Size(558, 329);
			this.splitContainer1.SplitterDistance = 213;
			this.splitContainer1.SplitterWidth = 2;
			this.splitContainer1.TabIndex = 5;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			this.BackColor = Color.FromArgb(239, 237, 226);
			base.ClientSize = new Size(558, 354);
			base.Controls.Add(this.splitContainer1);
			base.Controls.Add(this.toolStrip1);
			this.Font = new Font("宋体", 9f, FontStyle.Regular, GraphicsUnit.Point, 134);
			base.Name = "DataOpera";
			base.StartPosition = FormStartPosition.CenterScreen;
			this.Text = "数据查询";
			base.WindowState = FormWindowState.Maximized;
			this.toolStrip1.ResumeLayout(false);
			this.toolStrip1.PerformLayout();
			((ISupportInitialize)this.splitContainer1).EndInit();
			this.splitContainer1.ResumeLayout(false);
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
