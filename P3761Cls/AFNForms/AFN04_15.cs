using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
	public class AFN04_15 : iForm
	{
		private IContainer components = null;
		private DataGridViewCheckBoxColumn Column6;
		private DataGridViewTextBoxColumn Column5;
		private DataGridViewTextBoxColumn Column4;
		private DataGridViewTextBoxColumn Column1;
		private DataGridViewComboBoxColumn Column3;
		private DataGridViewTextBoxColumn Column2;
		private DataGridViewTextBoxColumn DataGridViewTextBoxColumn1;
		private DataGridView DataGridView2;
		public AFN04_15()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			this.DataGridView2.AllowUserToAddRows = false;
			this.DataGridView2.RowPostPaint += new DataGridViewRowPostPaintEventHandler(base.OnRowPostPaint);
			this.DataGridView2.CellPainting += new DataGridViewCellPaintingEventHandler(base.OnCellPainting);
			checked
			{
				for (int i = 0; i < 8; i++)
				{
					this.DataGridView2.Rows.Add();
					this.DataGridView2.Rows[i].Cells[0].Value = 0;
				}
			}
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
							text += int.Parse(this.DataGridView2.Rows[i].Cells[1].Value.ToString()).ToString("X2");
							text += int.Parse(this.DataGridView2.Rows[i].Cells[2].Value.ToString()).ToString("X2");
							text += int.Parse(this.DataGridView2.Rows[i].Cells[3].Value.ToString()).ToString("X2");
							string text2 = this.DataGridView2.Rows[i].Cells[4].Value.ToString();
							int num2 = (text2.IndexOf("60分钟电量") >= 0) ? 0 : ((text2.IndexOf("30分钟电量") >= 0) ? 1 : 2);
							text += (num2 | ((text2.IndexOf("相对对比") >= 0) ? 0 : 1) << 7).ToString("X2");
							text += int.Parse(this.DataGridView2.Rows[i].Cells[5].Value.ToString()).ToString("X2");
							text += this.DataGridView2.Rows[i].Cells[6].Value.ToString();
							num++;
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
					int num = DataConvert.HexToInt(data.Substring(0, 2));
					int num2 = 2;
					for (int i = 0; i < num; i++)
					{
						this.DataGridView2.Rows[i].Cells[0].Value = 1;
						this.DataGridView2.Rows[i].Cells[1].Value = DataConvert.HexToInt(data.Substring(num2, 2)).ToString();
						num2 += 2;
						this.DataGridView2.Rows[i].Cells[2].Value = DataConvert.HexToInt(data.Substring(num2, 2)).ToString();
						num2 += 2;
						this.DataGridView2.Rows[i].Cells[3].Value = DataConvert.HexToInt(data.Substring(num2, 2)).ToString();
						num2 += 2;
						int num3 = DataConvert.HexToInt(data.Substring(num2, 2));
						string text = "60分钟电量|30分钟电量|15分钟电量".Split(new char[]
						{
							'|'
						})[num3 & 3];
						text += "相对对比|绝对对比".Split(new char[]
						{
							'|'
						})[num3 >> 7];
						this.DataGridView2.Rows[i].Cells[4].Value = text;
						num2 += 2;
						this.DataGridView2.Rows[i].Cells[5].Value = DataConvert.HexToInt(data.Substring(num2, 2)).ToString();
						num2 += 2;
						this.DataGridView2.Rows[i].Cells[6].Value = data.Substring(num2, 8);
						num2 += 8;
					}
				}
			}
		}
		private void DataGridView2CellDoubleClick(object sender, DataGridViewCellEventArgs e)
		{
			int columnIndex = e.ColumnIndex;
			int rowIndex = e.RowIndex;
			if (columnIndex == 6)
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
			this.Column6 = new DataGridViewCheckBoxColumn();
			this.DataGridViewTextBoxColumn1 = new DataGridViewTextBoxColumn();
			this.Column2 = new DataGridViewTextBoxColumn();
			this.Column1 = new DataGridViewTextBoxColumn();
			this.Column3 = new DataGridViewComboBoxColumn();
			this.Column4 = new DataGridViewTextBoxColumn();
			this.Column5 = new DataGridViewTextBoxColumn();
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
				this.Column6,
				this.DataGridViewTextBoxColumn1,
				this.Column2,
				this.Column1,
				this.Column3,
				this.Column4,
				this.Column5
			});
			this.DataGridView2.Dock = DockStyle.Fill;
			this.DataGridView2.GridColor = SystemColors.ActiveBorder;
			this.DataGridView2.Location = new Point(0, 0);
			this.DataGridView2.MultiSelect = false;
			this.DataGridView2.Name = "DataGridView2";
			this.DataGridView2.RowTemplate.Height = 23;
			this.DataGridView2.SelectionMode = DataGridViewSelectionMode.CellSelect;
			this.DataGridView2.Size = new Size(739, 269);
			this.DataGridView2.TabIndex = 22;
			this.DataGridView2.CellDoubleClick += new DataGridViewCellEventHandler(this.DataGridView2CellDoubleClick);
			this.Column6.HeaderText = "";
			this.Column6.Name = "Column6";
			this.Column6.Width = 25;
			this.DataGridViewTextBoxColumn1.HeaderText = "有功总电能量差动组序号";
			this.DataGridViewTextBoxColumn1.Name = "DataGridViewTextBoxColumn1";
			this.Column2.HeaderText = "对比的总加组序号";
			this.Column2.Name = "Column2";
			this.Column2.Resizable = DataGridViewTriState.True;
			this.Column2.SortMode = DataGridViewColumnSortMode.NotSortable;
			this.Column1.HeaderText = "参照的总加组序号";
			this.Column1.Name = "Column1";
			this.Column3.HeaderText = "参与差动的电能量的时间区间及对比方法标志";
			this.Column3.Items.AddRange(new object[]
			{
				"60分钟电量相对对比",
				"30分钟电量相对对比",
				"15分钟电量相对对比",
				"60分钟电量绝对对比",
				"30分钟电量绝对对比",
				"15分钟电量绝对对比"
			});
			this.Column3.Name = "Column3";
			this.Column3.Width = 150;
			this.Column4.HeaderText = "差动越限相对偏差值(%)";
			this.Column4.Name = "Column4";
			this.Column4.Resizable = DataGridViewTriState.True;
			this.Column4.SortMode = DataGridViewColumnSortMode.NotSortable;
			this.Column5.HeaderText = "差动越限绝对偏差值(kWh)";
			this.Column5.Name = "Column5";
			this.Column5.ReadOnly = true;
			this.Column5.Resizable = DataGridViewTriState.True;
			this.Column5.SortMode = DataGridViewColumnSortMode.NotSortable;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(739, 269);
			base.Controls.Add(this.DataGridView2);
			base.Name = "AFN04_15";
			this.Text = "有功总电能量差动越限事件参数设置";
			((ISupportInitialize)this.DataGridView2).EndInit();
			base.ResumeLayout(false);
		}
	}
}
