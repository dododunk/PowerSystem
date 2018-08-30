using Helper;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_33_SD : iForm
	{
		private IContainer components = null;
		private DataGridViewTextBoxColumn Column3;
		private DataGridViewTextBoxColumn Column2;
		private DataGridViewTextBoxColumn Column1;
		private DataGridView DataGridView1;
		public AFN04_33_SD()
		{
			this.InitializeComponent();
			this.NeedSave = true;
			this.DataGridView1.AllowUserToAddRows = false;
			this.DataGridView1.RowPostPaint += new DataGridViewRowPostPaintEventHandler(base.OnRowPostPaint);
			this.DataGridView1.CellPainting += new DataGridViewCellPaintingEventHandler(base.OnCellPainting);
			checked
			{
				for (int i = 1; i <= 24; i++)
				{
					this.DataGridView1.Rows.Add();
					this.DataGridView1.Rows[i - 1].Cells[0].Value = "第" + i.ToString() + "个允许抄表时段";
				}
			}
		}
		protected override void GetText()
		{
			this.DataGridView1.EndEdit();
			this.Data = "";
			int num = 0;
			string text = string.Empty;
			checked
			{
				for (int i = 1; i <= 24; i++)
				{
					string value = Convert.ToString(this.DataGridView1.Rows[i - 1].Cells[1].Value).Replace(":", "");
					string value2 = Convert.ToString(this.DataGridView1.Rows[i - 1].Cells[2].Value).Replace(":", "");
					if (!string.IsNullOrEmpty(value))
					{
						text += base.OperaSend(value, 2, "A19");
						text += base.OperaSend(value2, 2, "A19");
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
					int num = 0;
					int num2 = DataConvert.HexToInt(data.Substring(num, 2));
					num += 2;
					for (int i = 0; i < num2; i++)
					{
						string value = base.OperaRec(data.Substring(num, 4), "A19");
						num += 4;
						string value2 = base.OperaRec(data.Substring(num, 4), "A19");
						num += 4;
						this.DataGridView1.Rows[i].Cells[1].Value = value;
						this.DataGridView1.Rows[i].Cells[2].Value = value2;
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
			this.Column2 = new DataGridViewTextBoxColumn();
			this.Column3 = new DataGridViewTextBoxColumn();
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
			this.DataGridView1.Size = new Size(374, 473);
			this.DataGridView1.TabIndex = 3;
			this.Column1.HeaderText = "时段名";
			this.Column1.Name = "Column1";
			this.Column1.ReadOnly = true;
			this.Column1.Width = 150;
			this.Column2.HeaderText = "起始";
			this.Column2.Name = "Column2";
			this.Column2.Width = 80;
			this.Column3.HeaderText = "终止";
			this.Column3.Name = "Column3";
			this.Column3.Width = 80;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(374, 473);
			base.Controls.Add(this.DataGridView1);
			
			base.Name = "AFN04_33_SD";
			this.Text = "时段编辑  [格式 00:00]";
			((ISupportInitialize)this.DataGridView1).EndInit();
			base.ResumeLayout(false);
		}
	}
}
