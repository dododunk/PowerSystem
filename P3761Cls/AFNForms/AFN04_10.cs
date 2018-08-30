using System;
using System.ComponentModel;
using System.Drawing;
using System.Globalization;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
	public class AFN04_10 : iForm
	{
		private IContainer components = null;
		private DataGridViewTextBoxColumn Column12;
		private DataGridViewTextBoxColumn Column11;
		private DataGridViewTextBoxColumn Column10;
		private DataGridViewComboBoxColumn Column9;
		private DataGridViewComboBoxColumn Column8;
		private DataGridViewTextBoxColumn Column7;
		private DataGridViewTextBoxColumn Column6;
		private DataGridViewTextBoxColumn Column5;
		private DataGridViewComboBoxColumn Column4;
		private DataGridViewTextBoxColumn Column13;
		private DataGridViewComboBoxColumn Column3;
		private DataGridViewTextBoxColumn Column2;
		private DataGridViewTextBoxColumn Column1;
		private DataGridView DataGridView2;
		public AFN04_10()
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
			checked
			{
				try
				{
					int num = 0;
					string text = string.Empty;
					for (int i = 0; i < this.DataGridView2.Rows.Count; i++)
					{
						string text2 = Convert.ToString(this.DataGridView2.Rows[i].Cells[0].Value);
						if (!string.IsNullOrEmpty(text2))
						{
							num++;
							text += DataConvert.ReverseStr(int.Parse(text2).ToString("X4"));
							string s = Convert.ToString(this.DataGridView2.Rows[i].Cells[1].Value);
							text += DataConvert.ReverseStr(int.Parse(s).ToString("X4"));
							string text3 = "使用默认值,600,1200,2400,4800,7200,9600,19200";
							string pText = Convert.ToString(this.DataGridView2.Rows[i].Cells[2].Value);
							int num2 = int.Parse(Convert.ToString(this.DataGridView2.Rows[i].Cells[3].Value));
							text += (this.GetIndex(pText, text3.Split(new char[]
							{
								','
							})) << 5 | num2).ToString("X2");
							text += int.Parse(Convert.ToString(this.DataGridView2.Rows[i].Cells[4].Value).Split(new char[]
							{
								'.'
							})[0]).ToString("X2");
							text += DataConvert.ReverseStr(Convert.ToString(this.DataGridView2.Rows[i].Cells[5].Value).PadLeft(12, '0'));
							text += DataConvert.ReverseStr(Convert.ToString(this.DataGridView2.Rows[i].Cells[6].Value).PadLeft(12, '0'));
							text += int.Parse(Convert.ToString(this.DataGridView2.Rows[i].Cells[7].Value)).ToString("X2");
							text += (int.Parse(Convert.ToString(this.DataGridView2.Rows[i].Cells[8].Value)) - 4 << 2 | int.Parse(Convert.ToString(this.DataGridView2.Rows[i].Cells[9].Value)) - 1).ToString("X2");
							text += DataConvert.ReverseStr(Convert.ToString(this.DataGridView2.Rows[i].Cells[10].Value).PadLeft(12, '0'));
							text += (int.Parse(Convert.ToString(this.DataGridView2.Rows[i].Cells[11].Value)) << 4 | int.Parse(Convert.ToString(this.DataGridView2.Rows[i].Cells[12].Value))).ToString("X2");
						}
					}
					this.Data = DataConvert.ReverseStr(num.ToString("X4")) + text;
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
					int num = DataConvert.HexToInt(DataConvert.ReverseStr(data.Substring(0, 4)));
					int num2 = 4;
					for (int i = 0; i < num; i++)
					{
						this.DataGridView2.Rows.Add();
						this.DataGridView2.Rows[i].Cells[0].Value = int.Parse(DataConvert.ReverseStr(data.Substring(num2, 4), 2), NumberStyles.HexNumber).ToString();
						num2 += 4;
						this.DataGridView2.Rows[i].Cells[1].Value = int.Parse(DataConvert.ReverseStr(data.Substring(num2, 4), 2), NumberStyles.HexNumber).ToString();
						num2 += 4;
						string text = data.Substring(num2, 2);
						num2 += 2;
						int num3 = int.Parse(text, NumberStyles.HexNumber);
						string text2 = "使用默认值,600,1200,2400,4800,7200,9600,19200";
						this.DataGridView2.Rows[i].Cells[2].Value = text2.Split(new char[]
						{
							','
						})[num3 >> 5];
						this.DataGridView2.Rows[i].Cells[3].Value = (num3 & 31).ToString();
						text = DataConvert.HexToInt(data.Substring(num2, 2)).ToString();
						num2 += 2;
						string[] array = "00.无需抄表,01.645-1997,02.交流采样装置通信协议,30.645-2007,31.串行接口连接窄带低压载波通信".Split(new char[]
						{
							','
						});
						this.DataGridView2.Rows[i].Cells[4].Value = array[this.GetIndex(text, array)];
						this.DataGridView2.Rows[i].Cells[5].Value = DataConvert.ReverseStr(data.Substring(num2, 12));
						num2 += 12;
						this.DataGridView2.Rows[i].Cells[6].Value = DataConvert.ReverseStr(data.Substring(num2, 12));
						num2 += 12;
						this.DataGridView2.Rows[i].Cells[7].Value = int.Parse(data.Substring(num2, 2), NumberStyles.HexNumber).ToString();
						num2 += 2;
						num3 = int.Parse(data.Substring(num2, 2), NumberStyles.HexNumber);
						num2 += 2;
						this.DataGridView2.Rows[i].Cells[8].Value = ((num3 >> 2) + 4).ToString();
						this.DataGridView2.Rows[i].Cells[9].Value = ((num3 & 3) + 1).ToString();
						this.DataGridView2.Rows[i].Cells[10].Value = DataConvert.ReverseStr(data.Substring(num2, 12), 2);
						num2 += 12;
						text = data.Substring(num2, 2);
						num2 += 2;
						num3 = int.Parse(text, NumberStyles.HexNumber);
						this.DataGridView2.Rows[i].Cells[11].Value = (num3 >> 4).ToString();
						this.DataGridView2.Rows[i].Cells[12].Value = (num3 & 15).ToString();
					}
				}
			}
		}
		private int GetIndex(string pText, string[] allitem)
		{
			checked
			{
				int result;
				for (int i = 0; i < allitem.Length; i++)
				{
					if (allitem[i].IndexOf(pText) >= 0)
					{
						result = i;
						return result;
					}
				}
				result = 0;
				return result;
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
			this.Column1 = new DataGridViewTextBoxColumn();
			this.Column2 = new DataGridViewTextBoxColumn();
			this.Column3 = new DataGridViewComboBoxColumn();
			this.Column13 = new DataGridViewTextBoxColumn();
			this.Column4 = new DataGridViewComboBoxColumn();
			this.Column5 = new DataGridViewTextBoxColumn();
			this.Column6 = new DataGridViewTextBoxColumn();
			this.Column7 = new DataGridViewTextBoxColumn();
			this.Column8 = new DataGridViewComboBoxColumn();
			this.Column9 = new DataGridViewComboBoxColumn();
			this.Column10 = new DataGridViewTextBoxColumn();
			this.Column11 = new DataGridViewTextBoxColumn();
			this.Column12 = new DataGridViewTextBoxColumn();
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
				this.Column2,
				this.Column3,
				this.Column13,
				this.Column4,
				this.Column5,
				this.Column6,
				this.Column7,
				this.Column8,
				this.Column9,
				this.Column10,
				this.Column11,
				this.Column12
			});
			this.DataGridView2.Dock = DockStyle.Fill;
			this.DataGridView2.GridColor = SystemColors.ActiveBorder;
			this.DataGridView2.Location = new Point(0, 0);
			this.DataGridView2.MultiSelect = false;
			this.DataGridView2.Name = "DataGridView2";
			this.DataGridView2.RowTemplate.Height = 23;
			this.DataGridView2.SelectionMode = DataGridViewSelectionMode.CellSelect;
			this.DataGridView2.Size = new Size(923, 322);
			this.DataGridView2.TabIndex = 23;
			this.Column1.HeaderText = "采样装置序号";
			this.Column1.Name = "Column1";
			this.Column1.Width = 50;
			this.Column2.HeaderText = "所属测量点号";
			this.Column2.Name = "Column2";
			this.Column2.Width = 50;
			this.Column3.HeaderText = "通信速率";
			this.Column3.Items.AddRange(new object[]
			{
				"使用默认值",
				"600",
				"1200",
				"2400",
				"4800",
				"7200",
				"9600",
				"19200"
			});
			this.Column3.Name = "Column3";
			this.Column3.Resizable = DataGridViewTriState.True;
			this.Column3.SortMode = DataGridViewColumnSortMode.Automatic;
			this.Column13.HeaderText = "通信端口号";
			this.Column13.Name = "Column13";
			this.Column13.Width = 50;
			this.Column4.HeaderText = "通信协议类型";
			this.Column4.Items.AddRange(new object[]
			{
				"00.无需抄表",
				"01.645-1997",
				"02.交流采样装置通信协议",
				"30.645-2007",
				"31.串行接口连接窄带低压载波通信"
			});
			this.Column4.Name = "Column4";
			this.Column4.Resizable = DataGridViewTriState.True;
			this.Column4.SortMode = DataGridViewColumnSortMode.Automatic;
			this.Column4.Width = 80;
			this.Column5.HeaderText = "通信地址";
			this.Column5.Name = "Column5";
			this.Column5.Width = 80;
			this.Column6.HeaderText = "通信密码";
			this.Column6.Name = "Column6";
			this.Column6.Width = 80;
			this.Column7.HeaderText = "电能费率个数";
			this.Column7.Name = "Column7";
			this.Column7.Width = 50;
			this.Column8.HeaderText = "有功电能整数个数";
			this.Column8.Items.AddRange(new object[]
			{
				"4",
				"5",
				"6",
				"7"
			});
			this.Column8.Name = "Column8";
			this.Column8.Resizable = DataGridViewTriState.True;
			this.Column8.SortMode = DataGridViewColumnSortMode.Automatic;
			this.Column8.Width = 70;
			this.Column9.HeaderText = "有功电能小数个数";
			this.Column9.Items.AddRange(new object[]
			{
				"1",
				"2",
				"3",
				"4"
			});
			this.Column9.Name = "Column9";
			this.Column9.Resizable = DataGridViewTriState.True;
			this.Column9.SortMode = DataGridViewColumnSortMode.Automatic;
			this.Column9.Width = 70;
			this.Column10.HeaderText = "所属采集器通信地址";
			this.Column10.Name = "Column10";
			this.Column10.Width = 80;
			this.Column11.HeaderText = "用户大类号";
			this.Column11.Name = "Column11";
			this.Column11.Width = 50;
			this.Column12.HeaderText = "用户小类号";
			this.Column12.Name = "Column12";
			this.Column12.Width = 50;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(923, 322);
			base.Controls.Add(this.DataGridView2);
			base.Name = "AFN04_10";
			this.Text = "终端电能表/交流采样装置配置参数";
			((ISupportInitialize)this.DataGridView2).EndInit();
			base.ResumeLayout(false);
		}
	}
}
