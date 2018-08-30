using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_35 : iForm
	{
		private IContainer components = null;
		private DataGridViewTextBoxColumn DataGridViewTextBoxColumn1;
		private DataGridView DataGridView2;
		public AFN04_35()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			this.DataGridView2.RowPostPaint += new DataGridViewRowPostPaintEventHandler(base.OnRowPostPaint);
			this.DataGridView2.CellPainting += new DataGridViewCellPaintingEventHandler(base.OnCellPainting);
			this.DataGridView2.AllowUserToAddRows = false;
			this.DataGridView2.ContextMenuStrip = this.menu.contextMenuStrip;
			this.menu.Grid = this.DataGridView2;
		}
		protected override void GetText()
		{
			this.DataGridView2.EndEdit();
			this.Data = "";
			string text = string.Empty;
			int num = 0;
			checked
			{
				for (int i = 0; i < this.DataGridView2.Rows.Count; i++)
				{
					string value = Convert.ToString(this.DataGridView2.Rows[i].Cells[0].Value);
					if (!string.IsNullOrEmpty(value))
					{
						text += base.OperaSend(value, 2, "BIN");
						num++;
					}
				}
				this.Data = num.ToString("X2") + text;
			}
		}
		public override void SetText()
		{
			checked
			{
				if (!string.IsNullOrEmpty(this.Data))
				{
					string data = this.Data;
					int num = int.Parse(base.OperaRec(data.Substring(0, 2), "BIN"));
					int num2 = 2;
					for (int i = 0; i < num; i++)
					{
						this.DataGridView2.Rows.Add();
						this.DataGridView2.Rows[i].Cells[0].Value = base.OperaRec(data.Substring(num2, 4), "BIN");
						num2 += 4;
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
			this.DataGridView2 = new DataGridView();
			this.DataGridViewTextBoxColumn1 = new DataGridViewTextBoxColumn();
			((ISupportInitialize)this.DataGridView2).BeginInit();
			base.SuspendLayout();
			dataGridViewCellStyle.BackColor = Color.FromArgb(241, 244, 248);
			this.DataGridView2.AlternatingRowsDefaultCellStyle = dataGridViewCellStyle;
			this.DataGridView2.BackgroundColor = Color.White;
			this.DataGridView2.BorderStyle = BorderStyle.Fixed3D;
			dataGridViewCellStyle2.Alignment = DataGridViewContentAlignment.MiddleCenter;
			dataGridViewCellStyle2.BackColor = SystemColors.Control;
			dataGridViewCellStyle2.Font = new Font("宋体", 9f, FontStyle.Regular, GraphicsUnit.Point, 134);
			dataGridViewCellStyle2.ForeColor = SystemColors.WindowText;
			dataGridViewCellStyle2.SelectionBackColor = SystemColors.Highlight;
			dataGridViewCellStyle2.SelectionForeColor = SystemColors.HighlightText;
			dataGridViewCellStyle2.WrapMode = DataGridViewTriState.True;
			this.DataGridView2.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle2;
			this.DataGridView2.ColumnHeadersHeight = 32;
			this.DataGridView2.Columns.AddRange(new DataGridViewColumn[]
			{
				this.DataGridViewTextBoxColumn1
			});
			this.DataGridView2.Dock = DockStyle.Fill;
			this.DataGridView2.GridColor = SystemColors.ActiveBorder;
			this.DataGridView2.Location = new Point(0, 0);
			this.DataGridView2.MultiSelect = false;
			this.DataGridView2.Name = "DataGridView2";
			this.DataGridView2.RowTemplate.Height = 23;
			this.DataGridView2.SelectionMode = DataGridViewSelectionMode.CellSelect;
			this.DataGridView2.Size = new Size(317, 285);
			this.DataGridView2.TabIndex = 22;
			this.DataGridViewTextBoxColumn1.HeaderText = "第n个重点户的电能表/交流采样装置序号";
			this.DataGridViewTextBoxColumn1.Name = "DataGridViewTextBoxColumn1";
			this.DataGridViewTextBoxColumn1.Width = 250;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(317, 285);
			base.Controls.Add(this.DataGridView2);
			base.Name = "AFN04_35";
			this.Text = "台区集中抄表重点户设置";
			((ISupportInitialize)this.DataGridView2).EndInit();
			base.ResumeLayout(false);
		}
	}
}
