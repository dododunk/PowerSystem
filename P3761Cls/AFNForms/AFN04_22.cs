using Helper;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_22 : iForm
	{
		private IContainer components = null;
		private DataGridViewCheckBoxColumn Column1;
		private DataGridViewTextBoxColumn DataGridViewTextBoxColumn1;
		private DataGridView DataGridView2;
		public AFN04_22()
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
					try
					{
						if (Convert.ToBoolean(this.DataGridView2.Rows[i].Cells[0].Value))
						{
							num++;
							text += this.DataGridView2.Rows[i].Cells[1].Value.ToString();
						}
					}
					catch
					{
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
					int num2 = DataConvert.HexToInt(data.Substring(0, 2));
					num += 2;
					for (int i = 0; i < num2; i++)
					{
						this.DataGridView2.Rows.Add();
						this.DataGridView2.Rows[i].Cells[0].Value = 1;
						this.DataGridView2.Rows[i].Cells[1].Value = data.Substring(num, 8);
						num += 8;
					}
				}
			}
		}
		private void DataGridView2CellDoubleClick(object sender, DataGridViewCellEventArgs e)
		{
			int columnIndex = e.ColumnIndex;
			int rowIndex = e.RowIndex;
			if (columnIndex == 1)
			{
				string data = Convert.ToString(this.DataGridView2.Rows[rowIndex].Cells[columnIndex].Value);
				iForm iForm = new A3();
				iForm.Data = data;
				iForm.SetText();
				iForm.ShowDialog();
				this.DataGridView2.Rows[rowIndex].Cells[columnIndex].Value = iForm.Data;
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
			this.Column1 = new DataGridViewCheckBoxColumn();
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
				this.Column1,
				this.DataGridViewTextBoxColumn1
			});
			this.DataGridView2.Dock = DockStyle.Fill;
			this.DataGridView2.GridColor = SystemColors.ActiveBorder;
			this.DataGridView2.Location = new Point(0, 0);
			this.DataGridView2.MultiSelect = false;
			this.DataGridView2.Name = "DataGridView2";
			this.DataGridView2.RowTemplate.Height = 23;
			this.DataGridView2.SelectionMode = DataGridViewSelectionMode.CellSelect;
			this.DataGridView2.Size = new Size(239, 210);
			this.DataGridView2.TabIndex = 22;
			this.DataGridView2.CellDoubleClick += new DataGridViewCellEventHandler(this.DataGridView2CellDoubleClick);
			this.Column1.HeaderText = "";
			this.Column1.Name = "Column1";
			this.Column1.Width = 25;
			this.DataGridViewTextBoxColumn1.HeaderText = "第M费率 (单位:厘/元)";
			this.DataGridViewTextBoxColumn1.Name = "DataGridViewTextBoxColumn1";
			this.DataGridViewTextBoxColumn1.ReadOnly = true;
			this.DataGridViewTextBoxColumn1.Resizable = DataGridViewTriState.True;
			this.DataGridViewTextBoxColumn1.Width = 150;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(239, 210);
			base.Controls.Add(this.DataGridView2);
			base.Name = "AFN04_22";
			this.Text = "终端电能量费率";
			((ISupportInitialize)this.DataGridView2).EndInit();
			base.ResumeLayout(false);
		}
	}
}
