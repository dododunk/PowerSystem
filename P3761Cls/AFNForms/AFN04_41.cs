using Helper;
using System;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_41 : iForm
	{
		private DataTable[] dt = new DataTable[3];
		private IContainer components = null;
		private DataGridViewTextBoxColumn Column3;
		private DataGridViewCheckBoxColumn Column2;
		private DataGridViewTextBoxColumn DataGridViewTextBoxColumn1;
		private DataGridView DataGridView2;
		private DataGridView DataGridView1;
		private DataGridViewCheckBoxColumn Column1;
		private DataGridViewTextBoxColumn Column4;
		private DataGridViewButtonColumn Column5;
		public AFN04_41()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			this.DataGridView2.AllowUserToAddRows = false;
			this.DataGridView1.AllowUserToAddRows = false;
			this.DataGridView2.RowPostPaint += new DataGridViewRowPostPaintEventHandler(base.OnRowPostPaint);
			this.DataGridView1.RowPostPaint += new DataGridViewRowPostPaintEventHandler(base.OnRowPostPaint);
			this.DataGridView2.CellPainting += new DataGridViewCellPaintingEventHandler(base.OnCellPainting);
			this.DataGridView1.CellPainting += new DataGridViewCellPaintingEventHandler(base.OnCellPainting);
			checked
			{
				for (int i = 0; i < 3; i++)
				{
					this.DataGridView1.Rows.Add();
					this.DataGridView1.Rows[i].Cells[1].Value = (i + 1).ToString();
					this.dt[i] = new DataTable();
					this.dt[i].Columns.Add("col0");
					this.dt[i].Columns.Add("col1");
					for (int j = 0; j < 8; j++)
					{
						DataRow dataRow = this.dt[i].NewRow();
						dataRow[0] = "0";
						dataRow[1] = "";
						this.dt[i].Rows.Add(dataRow);
					}
				}
				for (int i = 0; i < 8; i++)
				{
					this.DataGridView2.Rows.Add();
					this.DataGridView2.Rows[i].Cells[0].Value = (i + 1).ToString();
				}
			}
		}
		protected override void GetText()
		{
			this.DataGridView2.EndEdit();
			this.DataGridView1.EndEdit();
			this.Data = "";
			string text = string.Empty;
			int num = 0;
			checked
			{
				for (int i = 0; i < 3; i++)
				{
					if (Convert.ToBoolean(this.DataGridView1.Rows[i].Cells[0].Value))
					{
						num |= 1 << i;
					}
				}
				text += num.ToString("X2");
				for (int i = 0; i < 3; i++)
				{
					int num2 = 0;
					string text2 = string.Empty;
					for (int j = 0; j < 8; j++)
					{
						if (int.Parse(this.dt[i].Rows[j][0].ToString()) == 1)
						{
							num2 |= 1 << j;
							text2 += this.dt[i].Rows[j][1].ToString();
						}
					}
					text = text + num2.ToString("X2") + text2;
				}
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
					int num = 0;
					int num2 = DataConvert.HexToInt(data.Substring(num, 2));
					num += 2;
					for (int i = 0; i < 3; i++)
					{
						this.DataGridView1.Rows[i].Cells[0].Value = (num2 >> i & 1);
					}
					for (int j = 0; j < 3; j++)
					{
						int num3 = DataConvert.HexToInt(data.Substring(num, 2));
						num += 2;
						for (int i = 0; i < 8; i++)
						{
							this.dt[j].Rows[i][0] = (num3 >> i & 1).ToString();
							if ((num3 >> i & 1) == 1)
							{
								this.dt[j].Rows[i][1] = data.Substring(num, 4);
								num += 4;
							}
						}
					}
				}
			}
		}
		private void DataGridView1CellClick(object sender, DataGridViewCellEventArgs e)
		{
			checked
			{
				if (e.ColumnIndex == 1)
				{
					int rowIndex = e.RowIndex;
					for (int i = 0; i < 8; i++)
					{
						try
						{
							this.DataGridView2.Rows[i].Cells[1].Value = int.Parse(this.dt[rowIndex].Rows[i][0].ToString());
						}
						catch
						{
						}
						try
						{
							this.DataGridView2.Rows[i].Cells[2].Value = this.dt[rowIndex].Rows[i][1].ToString();
						}
						catch
						{
						}
					}
				}
				if (e.ColumnIndex == 2)
				{
					try
					{
						for (int i = 0; i < 65; i++)
						{
							int rowIndex = e.RowIndex;
							this.dt[rowIndex].Rows[i][0] = (Convert.ToBoolean(this.DataGridView2.Rows[i].Cells[1].Value) ? "1" : "0");
							this.dt[rowIndex].Rows[i][1] = this.DataGridView2.Rows[i].Cells[2].Value.ToString();
						}
					}
					catch
					{
					}
				}
			}
		}
		private void DataGridView2CellDoubleClick(object sender, DataGridViewCellEventArgs e)
		{
			if (e.ColumnIndex == 2 && e.RowIndex != -1 && !this.DataGridView2.Rows[e.RowIndex].IsNewRow)
			{
				iForm iForm = new A2();
				iForm.Data = Convert.ToString(this.DataGridView2.Rows[e.RowIndex].Cells[e.ColumnIndex].Value);
				iForm.SetText();
				iForm.ShowDialog();
				this.DataGridView2.Rows[e.RowIndex].Cells[e.ColumnIndex].Value = iForm.Data;
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
			DataGridViewCellStyle dataGridViewCellStyle3 = new DataGridViewCellStyle();
			DataGridViewCellStyle dataGridViewCellStyle4 = new DataGridViewCellStyle();
			this.DataGridView1 = new DataGridView();
			this.Column1 = new DataGridViewCheckBoxColumn();
			this.Column4 = new DataGridViewTextBoxColumn();
			this.Column5 = new DataGridViewButtonColumn();
			this.DataGridView2 = new DataGridView();
			this.DataGridViewTextBoxColumn1 = new DataGridViewTextBoxColumn();
			this.Column2 = new DataGridViewCheckBoxColumn();
			this.Column3 = new DataGridViewTextBoxColumn();
			((ISupportInitialize)this.DataGridView1).BeginInit();
			((ISupportInitialize)this.DataGridView2).BeginInit();
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
				this.Column4,
				this.Column5
			});
			this.DataGridView1.GridColor = SystemColors.ActiveBorder;
			this.DataGridView1.Location = new Point(4, 4);
			this.DataGridView1.MultiSelect = false;
			this.DataGridView1.Name = "DataGridView1";
			this.DataGridView1.RowTemplate.Height = 23;
			this.DataGridView1.SelectionMode = DataGridViewSelectionMode.CellSelect;
			this.DataGridView1.Size = new Size(166, 268);
			this.DataGridView1.TabIndex = 21;
			this.DataGridView1.CellClick += new DataGridViewCellEventHandler(this.DataGridView1CellClick);
			this.Column1.HeaderText = "方案定值";
			this.Column1.Name = "Column1";
			this.Column1.Resizable = DataGridViewTriState.True;
			this.Column1.SortMode = DataGridViewColumnSortMode.Automatic;
			this.Column1.Width = 50;
			this.Column4.HeaderText = "方案号";
			this.Column4.Name = "Column4";
			this.Column4.Width = 50;
			this.Column5.HeaderText = "保存";
			this.Column5.Name = "Column5";
			this.Column5.Width = 20;
			dataGridViewCellStyle3.BackColor = Color.FromArgb(241, 244, 248);
			this.DataGridView2.AlternatingRowsDefaultCellStyle = dataGridViewCellStyle3;
			this.DataGridView2.BackgroundColor = Color.White;
			this.DataGridView2.BorderStyle = BorderStyle.Fixed3D;
			dataGridViewCellStyle4.Alignment = DataGridViewContentAlignment.MiddleCenter;
			dataGridViewCellStyle4.BackColor = SystemColors.Control;
			dataGridViewCellStyle4.Font = new Font("宋体", 9f, FontStyle.Regular, GraphicsUnit.Point, 134);
			dataGridViewCellStyle4.ForeColor = SystemColors.WindowText;
			dataGridViewCellStyle4.SelectionBackColor = SystemColors.Highlight;
			dataGridViewCellStyle4.SelectionForeColor = SystemColors.HighlightText;
			dataGridViewCellStyle4.WrapMode = DataGridViewTriState.True;
			this.DataGridView2.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle4;
			this.DataGridView2.ColumnHeadersHeight = 32;
			this.DataGridView2.Columns.AddRange(new DataGridViewColumn[]
			{
				this.DataGridViewTextBoxColumn1,
				this.Column2,
				this.Column3
			});
			this.DataGridView2.GridColor = SystemColors.ActiveBorder;
			this.DataGridView2.Location = new Point(173, 4);
			this.DataGridView2.MultiSelect = false;
			this.DataGridView2.Name = "DataGridView2";
			this.DataGridView2.RowTemplate.Height = 23;
			this.DataGridView2.SelectionMode = DataGridViewSelectionMode.CellSelect;
			this.DataGridView2.Size = new Size(247, 268);
			this.DataGridView2.TabIndex = 22;
			this.DataGridView2.CellDoubleClick += new DataGridViewCellEventHandler(this.DataGridView2CellDoubleClick);
			this.DataGridViewTextBoxColumn1.HeaderText = "时段号";
			this.DataGridViewTextBoxColumn1.Name = "DataGridViewTextBoxColumn1";
			this.DataGridViewTextBoxColumn1.Width = 40;
			this.Column2.HeaderText = "定值方案";
			this.Column2.Name = "Column2";
			this.Column2.Resizable = DataGridViewTriState.True;
			this.Column2.Width = 40;
			this.Column3.HeaderText = "功控定值[双击]";
			this.Column3.Name = "Column3";
			this.Column3.ReadOnly = true;
			this.Column3.Resizable = DataGridViewTriState.True;
			this.Column3.SortMode = DataGridViewColumnSortMode.NotSortable;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(424, 277);
			base.Controls.Add(this.DataGridView2);
			base.Controls.Add(this.DataGridView1);
			base.Name = "AFN04_41";
			this.Text = "时段功控定值";
			((ISupportInitialize)this.DataGridView1).EndInit();
			((ISupportInitialize)this.DataGridView2).EndInit();
			base.ResumeLayout(false);
		}
	}
}
