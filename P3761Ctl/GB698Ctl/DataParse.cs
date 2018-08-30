using GB698Cls;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;
namespace GB698Ctl
{
	public class FormDataParse : ToolWindow
	{
		public delegate void SetTextDelegate(string sValue, string AFN, string FN);
		public delegate void SetText645Delegate(string sValue, string AFN, string FN, string format);
		public DataGridViewEx grid3 = new DataGridViewEx();
		private DLT698_Recv gAS = new DLT698_Recv();
		public bool IsCustomize = false;
		public string CustomizeItems = string.Empty;
		private IContainer components = null;
		private ToolStripMenuItem 刷新ToolStripMenuItem;
		internal ContextMenuStrip ContextMenuDock;
		public FormDataParse()
		{
			this.InitializeComponent();
			this.grid3.Parent = this;
			this.grid3.Dock = DockStyle.Fill;
			this.grid3.CellMouseDoubleClick += new DataGridViewCellMouseEventHandler(this.DataGridViewCellMouseClick);
			Application.DoEvents();
			this.InitGridInfo(this.grid3);
			Application.DoEvents();
		}
		private void FrameDisplayFormClosing(object sender, FormClosingEventArgs e)
		{
		}
		private void 刷新ToolStripMenuItemClick(object sender, EventArgs e)
		{
			this.grid3.Rows.Clear();
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
			dataGridViewTextBoxColumn.Width = 370;
			dataGridViewTextBoxColumn.ReadOnly = true;
			dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewTextBoxColumn);
		}
		public void SetText(string sValue, string AFN, string FN)
		{
			Thread.Sleep(0);
			checked
			{
				if (base.InvokeRequired)
				{
					base.Invoke(new FormDataParse.SetTextDelegate(this.SetText), new object[]
					{
						sValue,
						AFN,
						FN
					});
				}
				else
				{
					this.grid3.Rows.Clear();
					if (!string.IsNullOrEmpty(sValue))
					{
						if (string.IsNullOrEmpty(sValue) | sValue.ToUpper().IndexOf("部分确认") >= 0)
						{
							sValue = sValue.Split(new char[]
							{
								':'
							})[1];
							AFN = "00";
							FN = "0003";
						}
						if (!(string.IsNullOrEmpty(sValue) | sValue.ToUpper().IndexOf("ERROR") >= 0 | sValue.ToUpper().IndexOf("确认") >= 0 | sValue.ToUpper().IndexOf("否认") >= 0))
						{
							this.gAS.DoInfo(AFN, FN, sValue, this.IsCustomize, this.CustomizeItems);
							this.grid3.Rows.Clear();
							for (int i = 0; i < this.gAS.ItemData.Count; i++)
							{
								if (!string.IsNullOrEmpty(this.gAS.ItemData[i].Items))
								{
									this.grid3.Rows.Add();
									this.grid3.Rows[i].Cells[0].Value = this.gAS.ItemData[i].Items;
									this.grid3.Rows[i].Cells[1].Value = this.gAS.ItemData[i].Values;
								}
							}
						}
					}
				}
			}
		}
		public void SetText645(string sValue, string AFN, string FN, string format)
		{
			Thread.Sleep(0);
			checked
			{
				if (base.InvokeRequired)
				{
					base.Invoke(new FormDataParse.SetText645Delegate(this.SetText645), new object[]
					{
						sValue,
						AFN,
						FN,
						format
					});
				}
				else
				{
					this.grid3.Rows.Clear();
					if (!string.IsNullOrEmpty(sValue))
					{
						if (string.IsNullOrEmpty(sValue) | sValue.ToUpper().IndexOf("部分确认") >= 0)
						{
							sValue = sValue.Split(new char[]
							{
								':'
							})[1];
							AFN = "00";
							FN = "0003";
						}
						if (!(string.IsNullOrEmpty(sValue) | sValue.ToUpper().IndexOf("ERROR") >= 0 | sValue.ToUpper().IndexOf("确认") >= 0 | sValue.ToUpper().IndexOf("否认") >= 0))
						{
							this.gAS.DoInfo(AFN, FN, sValue, this.IsCustomize, this.CustomizeItems, format);
							this.grid3.Rows.Clear();
							for (int i = 0; i < this.gAS.ItemData.Count; i++)
							{
								if (!string.IsNullOrEmpty(this.gAS.ItemData[i].Items))
								{
									this.grid3.Rows.Add();
									this.grid3.Rows[i].Cells[0].Value = this.gAS.ItemData[i].Items;
									this.grid3.Rows[i].Cells[1].Value = this.gAS.ItemData[i].Values;
								}
							}
						}
					}
				}
			}
		}
		private void DataGridViewCellMouseClick(object sender, DataGridViewCellMouseEventArgs e)
		{
			if (e.ColumnIndex == 1)
			{
				iForm iForm = new ShowTxt();
				if (iForm != null)
				{
					iForm.NeedSave = false;
					iForm.Data = Convert.ToString(this.grid3.Rows[e.RowIndex].Cells[1].Value);
					iForm.SetText();
					iForm.ShowDialog();
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
			this.components = new Container();
			this.ContextMenuDock = new ContextMenuStrip(this.components);
			this.刷新ToolStripMenuItem = new ToolStripMenuItem();
			this.ContextMenuDock.SuspendLayout();
			base.SuspendLayout();
			this.ContextMenuDock.Items.AddRange(new ToolStripItem[]
			{
				this.刷新ToolStripMenuItem
			});
			this.ContextMenuDock.Name = "ContextMenuStrip1";
			this.ContextMenuDock.Size = new Size(95, 26);
			this.ContextMenuDock.Text = "Window Position";
			this.刷新ToolStripMenuItem.Name = "刷新ToolStripMenuItem";
			this.刷新ToolStripMenuItem.Size = new Size(94, 22);
			this.刷新ToolStripMenuItem.Text = "清空";
			this.刷新ToolStripMenuItem.Click += new EventHandler(this.刷新ToolStripMenuItemClick);
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			this.BackColor = Color.FromArgb(239, 237, 226);
			base.ClientSize = new Size(595, 154);
			base.CloseButton = false;
			base.CloseButtonVisible = false;
			base.Name = "DataParse";
			base.TabPageContextMenuStrip = this.ContextMenuDock;
			this.Text = "数据解析";
			base.FormClosing += new FormClosingEventHandler(this.FrameDisplayFormClosing);
			this.ContextMenuDock.ResumeLayout(false);
			base.ResumeLayout(false);
		}
	}
}
