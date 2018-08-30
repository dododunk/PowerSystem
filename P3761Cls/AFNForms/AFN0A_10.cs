using Helper;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN0A_10 : iForm
	{
		private IContainer components = null;
		private DataGridViewTextBoxColumn Column1;
		private DataGridView DataGridView1;
		public AFN0A_10()
		{
			this.InitializeComponent();
			this.DataGridView1.RowPostPaint += new DataGridViewRowPostPaintEventHandler(base.OnRowPostPaint);
			this.DataGridView1.CellPainting += new DataGridViewCellPaintingEventHandler(base.OnCellPainting);
			this.DataGridView1.AllowUserToAddRows = false;
			this.DataGridView1.ContextMenuStrip = this.menu.contextMenuStrip;
			this.menu.Grid = this.DataGridView1;
		}
		protected override void GetText()
		{
			this.DataGridView1.EndEdit();
			this.Data = "";
			int num = 0;
			string text = string.Empty;
			checked
			{
				for (int i = 0; i < this.DataGridView1.Rows.Count; i++)
				{
					if (!string.IsNullOrEmpty(Convert.ToString(this.DataGridView1.Rows[i].Cells[0].Value)))
					{
						text += base.OperaSend(this.DataGridView1.Rows[i].Cells[0].Value.ToString(), this.Len, "BIN");
						num++;
					}
				}
				this.Data = base.OperaSend(num.ToString(), this.Len, "BIN") + text;
			}
		}
		public override void SetText()
		{
			checked
			{
				if (!string.IsNullOrEmpty(this.Data))
				{
					string data = this.Data;
					int num = 0;
					int num2 = DataConvert.HexToInt(DataConvert.ReverseStr(data.Substring(num, this.Len * 2)));
					num += this.Len * 2;
					for (int i = 0; i < num2; i++)
					{
						this.DataGridView1.Rows.Add();
						this.DataGridView1.Rows[i].Cells[0].Value = base.OperaRec(data.Substring(num, this.Len * 2), "BIN");
						num += this.Len * 2;
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
			DataGridViewCellStyle dataGridViewCellStyle = new DataGridViewCellStyle();
			DataGridViewCellStyle dataGridViewCellStyle2 = new DataGridViewCellStyle();
			this.DataGridView1 = new DataGridView();
			this.Column1 = new DataGridViewTextBoxColumn();
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
				this.Column1
			});
			this.DataGridView1.Dock = DockStyle.Fill;
			this.DataGridView1.GridColor = SystemColors.ActiveBorder;
			this.DataGridView1.Location = new Point(0, 0);
			this.DataGridView1.MultiSelect = false;
			this.DataGridView1.Name = "DataGridView1";
			this.DataGridView1.RowTemplate.Height = 23;
			this.DataGridView1.SelectionMode = DataGridViewSelectionMode.CellSelect;
			this.DataGridView1.Size = new Size(263, 260);
			this.DataGridView1.TabIndex = 0;
			this.Column1.HeaderText = "查询的对象序号";
			this.Column1.Name = "Column1";
			this.Column1.Width = 200;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(263, 260);
			base.Controls.Add(this.DataGridView1);
			base.Name = "AFN0A_10";
			this.Text = "查询参数";
			((ISupportInitialize)this.DataGridView1).EndInit();
			base.ResumeLayout(false);
		}
	}
}
