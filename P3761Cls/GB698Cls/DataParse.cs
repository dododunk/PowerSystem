using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class DataParse : iForm
	{
		private DLT698_Recv gAS = new DLT698_Recv();
		private IContainer components = null;
		private DataGridViewTextBoxColumn Column2;
		private DataGridViewTextBoxColumn Column1;
		private DataGridView DataGridView1;
		public DataParse()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			this.DataGridView1.AllowUserToAddRows = false;
			this.DataGridView1.RowPostPaint += new DataGridViewRowPostPaintEventHandler(base.OnRowPostPaint);
			this.NeedSave = false;
			this.DataGridView1.CellMouseDoubleClick += new DataGridViewCellMouseEventHandler(this.DataGridView1CellMouseClick);
			this.DataGridView1.CellPainting += new DataGridViewCellPaintingEventHandler(base.OnCellPainting);
		}
		protected override void GetText()
		{
			this.Data = this.Data;
		}
		public override void SetText()
		{
			checked
			{
				if (!string.IsNullOrEmpty(this.Data))
				{
					string data = this.Data;
					this.gAS.DoInfo(this.AFN, this.FN, this.Data, this.IsCustomize, this.CustomizeItems);
					this.DataGridView1.Rows.Clear();
					for (int i = 0; i < this.gAS.ItemData.Count; i++)
					{
						if (!string.IsNullOrEmpty(this.gAS.ItemData[i].Items))
						{
							this.DataGridView1.Rows.Add();
							this.DataGridView1.Rows[i].Cells[0].Value = this.gAS.ItemData[i].Items;
							this.DataGridView1.Rows[i].Cells[0].Style.BackColor = Color.FromArgb(239, 237, 226);
							this.DataGridView1.Rows[i].Cells[1].Value = this.gAS.ItemData[i].Values;
						}
					}
				}
			}
		}
		private void DataGridView1CellMouseClick(object sender, DataGridViewCellMouseEventArgs e)
		{
			if (e.ColumnIndex == 1)
			{
				iForm iForm = new ShowTxt();
				if (iForm != null)
				{
					iForm.NeedSave = false;
					iForm.Data = Convert.ToString(this.DataGridView1.Rows[e.RowIndex].Cells[1].Value);
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
			DataGridViewCellStyle dataGridViewCellStyle = new DataGridViewCellStyle();
			DataGridViewCellStyle dataGridViewCellStyle2 = new DataGridViewCellStyle();
			this.DataGridView1 = new DataGridView();
			this.Column1 = new DataGridViewTextBoxColumn();
			this.Column2 = new DataGridViewTextBoxColumn();
			((ISupportInitialize)this.DataGridView1).BeginInit();
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
				this.Column2
			});
			this.DataGridView1.Dock = DockStyle.Fill;
			this.DataGridView1.GridColor = SystemColors.ActiveBorder;
			this.DataGridView1.Location = new Point(0, 0);
			this.DataGridView1.MultiSelect = false;
			this.DataGridView1.Name = "DataGridView1";
			this.DataGridView1.RowTemplate.Height = 23;
			this.DataGridView1.SelectionMode = DataGridViewSelectionMode.CellSelect;
			this.DataGridView1.Size = new Size(713, 556);
			this.DataGridView1.TabIndex = 2;
			this.Column1.HeaderText = "字段名";
			this.Column1.Name = "Column1";
			this.Column1.ReadOnly = true;
			this.Column1.SortMode = DataGridViewColumnSortMode.NotSortable;
			this.Column1.Width = 300;
			this.Column2.HeaderText = "内容";
			this.Column2.Name = "Column2";
			this.Column2.ReadOnly = true;
			this.Column2.SortMode = DataGridViewColumnSortMode.NotSortable;
			this.Column2.Width = 350;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(713, 556);
			base.Controls.Add(this.DataGridView1);
			base.Name = "DataParse";
			this.Text = "数据解析";
			((ISupportInitialize)this.DataGridView1).EndInit();
			base.ResumeLayout(false);
		}
	}
}
