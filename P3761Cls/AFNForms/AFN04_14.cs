using System;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
	public class AFN04_14 : iForm
	{
		private DataTable[] dt = new DataTable[8];
		private IContainer components = null;
		private SplitContainer splitContainer1;
		private DataGridView DataGridView1;
		private DataGridView DataGridView2;
		private DataGridViewCheckBoxColumn DataGridViewTextBoxColumn1;
		private DataGridViewTextBoxColumn Column5;
		private DataGridViewComboBoxColumn Column2;
		private DataGridViewComboBoxColumn Column3;
		private DataGridViewCheckBoxColumn Column1;
		private DataGridViewTextBoxColumn Column4;
		private DataGridViewButtonColumn Column6;
		public AFN04_14()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			this.DataGridView1.AllowUserToAddRows = false;
			this.DataGridView2.AllowUserToAddRows = false;
			this.DataGridView1.RowPostPaint += new DataGridViewRowPostPaintEventHandler(base.OnRowPostPaint);
			this.DataGridView2.RowPostPaint += new DataGridViewRowPostPaintEventHandler(base.OnRowPostPaint);
			this.DataGridView1.CellPainting += new DataGridViewCellPaintingEventHandler(base.OnCellPainting);
			this.DataGridView2.CellPainting += new DataGridViewCellPaintingEventHandler(base.OnCellPainting);
			this.DataGridView1.CellClick += new DataGridViewCellEventHandler(this.DataGridView1CellClick);
			checked
			{
				for (int i = 0; i < 8; i++)
				{
					this.DataGridView1.Rows.Add();
					this.DataGridView1.Rows[i].Cells[1].Value = (i + 1).ToString();
					this.DataGridView1.Rows[i].Cells[1].ReadOnly = true;
					this.dt[i] = new DataTable();
					this.dt[i].Columns.Add("col0");
					this.dt[i].Columns.Add("col1");
					this.dt[i].Columns.Add("col2");
					this.dt[i].Columns.Add("col3");
					for (int j = 1; j < 65; j++)
					{
						DataRow dataRow = this.dt[i].NewRow();
						dataRow[0] = "0";
						dataRow[1] = "";
						dataRow[2] = "";
						dataRow[3] = "";
						this.dt[i].Rows.Add(dataRow);
					}
				}
				for (int i = 1; i < 65; i++)
				{
					this.DataGridView2.Rows.Add();
				}
			}
		}
		protected override void GetText()
		{
			this.DataGridView1.EndEdit();
			this.DataGridView2.EndEdit();
			this.Data = "";
			checked
			{
				try
				{
					string text = string.Empty;
					int num = 0;
					for (int i = 0; i < 8; i++)
					{
						string text2 = string.Empty;
						if (Convert.ToBoolean(this.DataGridView1.Rows[i].Cells[0].Value))
						{
							num++;
							text2 += int.Parse(this.DataGridView1.Rows[i].Cells[1].Value.ToString()).ToString("X2");
							int num2 = 0;
							string text3 = string.Empty;
							for (int j = 0; j < 64; j++)
							{
								if (this.dt[i].Rows[j][0].ToString() == "1")
								{
									num2++;
									int num3 = 0;
									num3 |= int.Parse(this.dt[i].Rows[j][1].ToString());
									string text4 = this.dt[i].Rows[j][2].ToString();
									if (text4.IndexOf("正") >= 0)
									{
										
									}
									else
									{
										num3 |= 64;
									}
									string text5 = this.dt[i].Rows[j][3].ToString();
									if (text5.IndexOf("加") >= 0)
									{
										
									}
									else
									{
										num3 |= 128;
									}
									text3 += num3.ToString("X2");
								}
							}
							text2 = text2 + num2.ToString("X2") + text3;
						}
						text += text2;
					}
					text = num.ToString("X2") + text;
					this.Data = text;
				}
				catch
				{
					MessageBox.Show("信息填写有错误或填写不完整");
				}
			}
		}
		public override void SetText()
		{
			checked
			{
				if (!string.IsNullOrEmpty(this.Data))
				{
					string data = this.Data;
					if (!string.IsNullOrEmpty(data))
					{
						int num = 0;
						int num2 = DataConvert.HexToInt(data.Substring(num, 2));
						num += 2;
						do
						{
							int num3 = DataConvert.HexToInt(data.Substring(num, 2));
							num += 2;
							this.DataGridView1.Rows[num3 - 1].Cells[0].Value = 1;
							int num4 = DataConvert.HexToInt(data.Substring(num, 2));
							num += 2;
							for (int i = 0; i < num4; i++)
							{
								int num5 = DataConvert.HexToInt(data.Substring(num, 2));
								num += 2;
								this.dt[num3 - 1].Rows[i][0] = "1";
								this.dt[num3 - 1].Rows[i][1] = (num5 & 63).ToString();
								this.dt[num3 - 1].Rows[i][2] = (((num5 >> 6 & 1) == 0) ? "正向" : "反向");
								this.dt[num3 - 1].Rows[i][3] = (((num5 >> 7 & 1) == 0) ? "加运算" : "减运算");
							}
						}
						while (num < data.Length);
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
					for (int i = 1; i < 65; i++)
					{
						try
						{
							this.DataGridView2.Rows[i - 1].Cells[0].Value = int.Parse(this.dt[rowIndex].Rows[i - 1][0].ToString());
						}
						catch
						{
						}
						try
						{
							this.DataGridView2.Rows[i - 1].Cells[1].Value = this.dt[rowIndex].Rows[i - 1][1].ToString();
						}
						catch
						{
						}
						try
						{
							this.DataGridView2.Rows[i - 1].Cells[2].Value = this.dt[rowIndex].Rows[i - 1][2].ToString();
						}
						catch
						{
						}
						try
						{
							this.DataGridView2.Rows[i - 1].Cells[3].Value = this.dt[rowIndex].Rows[i - 1][3].ToString();
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
						for (int i = 1; i < 65; i++)
						{
							int rowIndex = e.RowIndex;
							this.dt[rowIndex].Rows[i - 1][0] = (Convert.ToBoolean(this.DataGridView2.Rows[i - 1].Cells[0].Value) ? "1" : "0");
							this.dt[rowIndex].Rows[i - 1][1] = this.DataGridView2.Rows[i - 1].Cells[1].Value.ToString();
							this.dt[rowIndex].Rows[i - 1][2] = this.DataGridView2.Rows[i - 1].Cells[2].Value.ToString();
							this.dt[rowIndex].Rows[i - 1][3] = this.DataGridView2.Rows[i - 1].Cells[3].Value.ToString();
						}
					}
					catch
					{
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
			DataGridViewCellStyle dataGridViewCellStyle3 = new DataGridViewCellStyle();
			DataGridViewCellStyle dataGridViewCellStyle4 = new DataGridViewCellStyle();
			this.splitContainer1 = new SplitContainer();
			this.DataGridView1 = new DataGridView();
			this.DataGridView2 = new DataGridView();
			this.DataGridViewTextBoxColumn1 = new DataGridViewCheckBoxColumn();
			this.Column5 = new DataGridViewTextBoxColumn();
			this.Column2 = new DataGridViewComboBoxColumn();
			this.Column3 = new DataGridViewComboBoxColumn();
			this.Column1 = new DataGridViewCheckBoxColumn();
			this.Column4 = new DataGridViewTextBoxColumn();
			this.Column6 = new DataGridViewButtonColumn();
			((ISupportInitialize)this.splitContainer1).BeginInit();
			this.splitContainer1.Panel1.SuspendLayout();
			this.splitContainer1.Panel2.SuspendLayout();
			this.splitContainer1.SuspendLayout();
			((ISupportInitialize)this.DataGridView1).BeginInit();
			((ISupportInitialize)this.DataGridView2).BeginInit();
			base.SuspendLayout();
			this.splitContainer1.Dock = DockStyle.Fill;
			this.splitContainer1.FixedPanel = FixedPanel.Panel1;
			this.splitContainer1.IsSplitterFixed = true;
			this.splitContainer1.Location = new Point(0, 0);
			this.splitContainer1.Name = "splitContainer1";
			this.splitContainer1.Panel1.Controls.Add(this.DataGridView1);
			this.splitContainer1.Panel2.Controls.Add(this.DataGridView2);
			this.splitContainer1.Size = new Size(491, 285);
			this.splitContainer1.SplitterDistance = 160;
			this.splitContainer1.SplitterWidth = 2;
			this.splitContainer1.TabIndex = 23;
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
				this.Column6
			});
			this.DataGridView1.Dock = DockStyle.Fill;
			this.DataGridView1.GridColor = SystemColors.ActiveBorder;
			this.DataGridView1.Location = new Point(0, 0);
			this.DataGridView1.MultiSelect = false;
			this.DataGridView1.Name = "DataGridView1";
			this.DataGridView1.RowTemplate.Height = 23;
			this.DataGridView1.SelectionMode = DataGridViewSelectionMode.CellSelect;
			this.DataGridView1.Size = new Size(160, 285);
			this.DataGridView1.TabIndex = 22;
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
				this.Column5,
				this.Column2,
				this.Column3
			});
			this.DataGridView2.Dock = DockStyle.Fill;
			this.DataGridView2.GridColor = SystemColors.ActiveBorder;
			this.DataGridView2.Location = new Point(0, 0);
			this.DataGridView2.MultiSelect = false;
			this.DataGridView2.Name = "DataGridView2";
			this.DataGridView2.RowTemplate.Height = 23;
			this.DataGridView2.SelectionMode = DataGridViewSelectionMode.CellSelect;
			this.DataGridView2.Size = new Size(329, 285);
			this.DataGridView2.TabIndex = 23;
			this.DataGridViewTextBoxColumn1.HeaderText = "";
			this.DataGridViewTextBoxColumn1.Name = "DataGridViewTextBoxColumn1";
			this.DataGridViewTextBoxColumn1.Resizable = DataGridViewTriState.True;
			this.DataGridViewTextBoxColumn1.SortMode = DataGridViewColumnSortMode.Automatic;
			this.DataGridViewTextBoxColumn1.Width = 25;
			this.Column5.HeaderText = "测量点号";
			this.Column5.Name = "Column5";
			this.Column5.Width = 40;
			this.Column2.HeaderText = "正反向";
			this.Column2.Items.AddRange(new object[]
			{
				"正向",
				"反向",
				""
			});
			this.Column2.Name = "Column2";
			this.Column3.HeaderText = "总加运算符标志";
			this.Column3.Items.AddRange(new object[]
			{
				"加运算",
				"减运算",
				""
			});
			this.Column3.Name = "Column3";
			this.Column1.HeaderText = "";
			this.Column1.Name = "Column1";
			this.Column1.Resizable = DataGridViewTriState.True;
			this.Column1.SortMode = DataGridViewColumnSortMode.Automatic;
			this.Column1.Width = 25;
			this.Column4.HeaderText = "总加组序号";
			this.Column4.Name = "Column4";
			this.Column4.Width = 70;
			this.Column6.HeaderText = "保存";
			this.Column6.Name = "Column6";
			this.Column6.Width = 20;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(491, 285);
			base.Controls.Add(this.splitContainer1);
			base.Name = "AFN04_14";
			this.Text = "终端总加组配置参数";
			this.splitContainer1.Panel1.ResumeLayout(false);
			this.splitContainer1.Panel2.ResumeLayout(false);
			((ISupportInitialize)this.splitContainer1).EndInit();
			this.splitContainer1.ResumeLayout(false);
			((ISupportInitialize)this.DataGridView1).EndInit();
			((ISupportInitialize)this.DataGridView2).EndInit();
			base.ResumeLayout(false);
		}
	}
}
