using System;
using System.ComponentModel;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_09 : iForm
	{
		private delegate void InitLoadDelegate();
		private string[] ERC;
		private IContainer components = null;
		private ToolStripMenuItem ToolStripMenuItemSelectAll;
		private ContextMenuStrip contextMenuStrip1;
		private DataGridViewCheckBoxColumn Column3;
		private DataGridViewCheckBoxColumn Column2;
		private DataGridViewTextBoxColumn Column1;
		private DataGridView DataGridView1;
		public AFN04_09()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			this.DataGridView1.AllowUserToAddRows = false;
			this.DataGridView1.ContextMenuStrip = this.contextMenuStrip1;
			this.DataGridView1.RowPostPaint += new DataGridViewRowPostPaintEventHandler(base.OnRowPostPaint);
			this.DataGridView1.CellPainting += new DataGridViewCellPaintingEventHandler(base.OnCellPainting);
			this.InitLoad();
		}
		private void InitLoad()
		{
			//Thread.Sleep(0);
			checked
			{
				if (base.InvokeRequired)
				{
					base.Invoke(new AFN04_09.InitLoadDelegate(this.InitLoad), new object[0]);
				}
				else
				{
					this.ERC = this.ALLERC.Split(new char[]
					{
						'~'
					});
					for (int i = 0; i < 64; i++)
					{
						this.DataGridView1.Rows.Add();
						this.DataGridView1.Rows[i].Cells[1].Value = 0;
						this.DataGridView1.Rows[i].Cells[2].Value = 0;
						if (!string.IsNullOrEmpty(this.ERC[i]))
						{
							this.DataGridView1.Rows[i].Cells[0].Value = "ERC" + (i + 1).ToString() + " " + this.ERC[i];
						}
						else
						{
							this.DataGridView1.Rows[i].Visible = false;
						}
					}
				}
			}
		}
		protected override void GetText()
		{
			this.Data = "";
			this.DataGridView1.EndEdit();
			string text = string.Empty;
			string text2 = "";
			checked
			{
				for (int i = 0; i < 64; i++)
				{
					bool flag = Convert.ToBoolean(this.DataGridView1.Rows[i].Cells[1].Value);
					text2 += (flag ? "1" : "0");
				}
				text += base.OperaSend(text2, 16, "BS");
				string text3 = "";
				for (int i = 0; i < 64; i++)
				{
					bool flag = Convert.ToBoolean(this.DataGridView1.Rows[i].Cells[2].Value);
					text3 += (flag ? "1" : "0");
				}
				text += base.OperaSend(text3, 16, "BS");
				this.Data = text;
			}
		}
		public override void SetText()
		{
			checked
			{
				if (!string.IsNullOrEmpty(this.Data))
				{
					string data = this.Data;
					string text = base.OperaRec(data.Substring(0, 16), "BS");
					for (int i = 0; i < 64; i++)
					{
						if (text.Substring(i, 1) == "1")
						{
							this.DataGridView1.Rows[i].Cells[1].Value = 1;
						}
					}
					text = base.OperaRec(data.Substring(16, 16), "BS");
					for (int i = 0; i < 64; i++)
					{
						if (text.Substring(i, 1) == "1")
						{
							this.DataGridView1.Rows[i].Cells[2].Value = 1;
						}
					}
				}
			}
		}
		private void 全选ToolStripMenuItemClick(object sender, EventArgs e)
		{
			int columnIndex = this.DataGridView1.CurrentCell.ColumnIndex;
			checked
			{
				if (columnIndex == 1 | columnIndex == 2)
				{
					this.ERC = this.ALLERC.Split(new char[]
					{
						'~'
					});
					for (int i = 0; i < 64; i++)
					{
						if (!string.IsNullOrEmpty(this.ERC[i]))
						{
							bool flag = Convert.ToBoolean(this.DataGridView1.Rows[i].Cells[columnIndex].Value);
							this.DataGridView1.Rows[i].Cells[columnIndex].Value = (flag ? 0 : 1);
						}
					}
				}
				this.DataGridView1.EndEdit();
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
			DataGridViewCellStyle dataGridViewCellStyle = new DataGridViewCellStyle();
			DataGridViewCellStyle dataGridViewCellStyle2 = new DataGridViewCellStyle();
			this.DataGridView1 = new DataGridView();
			this.Column1 = new DataGridViewTextBoxColumn();
			this.Column2 = new DataGridViewCheckBoxColumn();
			this.Column3 = new DataGridViewCheckBoxColumn();
			this.contextMenuStrip1 = new ContextMenuStrip(this.components);
			this.ToolStripMenuItemSelectAll = new ToolStripMenuItem();
			((ISupportInitialize)this.DataGridView1).BeginInit();
			this.contextMenuStrip1.SuspendLayout();
			base.SuspendLayout();
			dataGridViewCellStyle.BackColor = Color.FromArgb(241, 244, 248);
			this.DataGridView1.AlternatingRowsDefaultCellStyle = dataGridViewCellStyle;
			this.DataGridView1.BackgroundColor = Color.White;
			this.DataGridView1.BorderStyle = BorderStyle.Fixed3D;
			dataGridViewCellStyle2.Alignment = DataGridViewContentAlignment.MiddleCenter;
			dataGridViewCellStyle2.BackColor = SystemColors.Control;
			dataGridViewCellStyle2.Font = new Font("宋体", 9f, FontStyle.Regular, GraphicsUnit.Point, 134);
			dataGridViewCellStyle2.ForeColor = SystemColors.WindowText;
			dataGridViewCellStyle2.SelectionBackColor = SystemColors.Highlight;
			dataGridViewCellStyle2.SelectionForeColor = SystemColors.HighlightText;
			dataGridViewCellStyle2.WrapMode = DataGridViewTriState.True;
			this.DataGridView1.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle2;
			this.DataGridView1.ColumnHeadersHeight = 32;
			this.DataGridView1.Columns.AddRange(new DataGridViewColumn[]
			{
				this.Column1,
				this.Column2,
				this.Column3
			});
			this.DataGridView1.Dock = DockStyle.Fill;
			this.DataGridView1.GridColor = SystemColors.ActiveBorder;
			this.DataGridView1.Location = new Point(0, 0);
			this.DataGridView1.MultiSelect = false;
			this.DataGridView1.Name = "DataGridView1";
			this.DataGridView1.RowTemplate.Height = 23;
			this.DataGridView1.SelectionMode = DataGridViewSelectionMode.CellSelect;
			this.DataGridView1.Size = new Size(432, 523);
			this.DataGridView1.TabIndex = 22;
			this.Column1.HeaderText = "事件名称";
			this.Column1.Name = "Column1";
			this.Column1.ReadOnly = true;
			this.Column1.Width = 300;
			this.Column2.HeaderText = "记录";
			this.Column2.Name = "Column2";
			this.Column2.Width = 35;
			this.Column3.HeaderText = "重要";
			this.Column3.Name = "Column3";
			this.Column3.Width = 35;
			this.contextMenuStrip1.Items.AddRange(new ToolStripItem[]
			{
				this.ToolStripMenuItemSelectAll
			});
			this.contextMenuStrip1.Name = "contextMenuStrip1";
			this.contextMenuStrip1.Size = new Size(153, 48);
			this.ToolStripMenuItemSelectAll.Name = "全选ToolStripMenuItem";
			this.ToolStripMenuItemSelectAll.Size = new Size(152, 22);
			this.ToolStripMenuItemSelectAll.Text = "全选";
			this.ToolStripMenuItemSelectAll.Click += new EventHandler(this.全选ToolStripMenuItemClick);
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(432, 523);
			base.Controls.Add(this.DataGridView1);
			base.Name = "AFN04_09";
			this.Text = "终端事件记录配置设置";
			((ISupportInitialize)this.DataGridView1).EndInit();
			this.contextMenuStrip1.ResumeLayout(false);
			base.ResumeLayout(false);
		}
	}
}
