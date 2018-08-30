using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
	public class AFN04_33 : iForm
	{
		private IContainer components = null;
		private DataGridViewLinkColumn Column41;
		private DataGridViewTextBoxColumn Column40;
		private DataGridViewTextBoxColumn Column39;
		private DataGridViewTextBoxColumn Column38;
		private DataGridViewCheckBoxColumn Column37;
		private DataGridViewCheckBoxColumn Column36;
		private DataGridViewCheckBoxColumn Column35;
		private DataGridViewCheckBoxColumn Column34;
		private DataGridViewCheckBoxColumn Column33;
		private DataGridViewCheckBoxColumn Column32;
		private DataGridViewCheckBoxColumn Column31;
		private DataGridViewCheckBoxColumn Column30;
		private DataGridViewCheckBoxColumn Column29;
		private DataGridViewCheckBoxColumn Column28;
		private DataGridViewCheckBoxColumn Column27;
		private DataGridViewCheckBoxColumn Column26;
		private DataGridViewCheckBoxColumn Column25;
		private DataGridViewCheckBoxColumn Column24;
		private DataGridViewCheckBoxColumn Column23;
		private DataGridViewCheckBoxColumn Column22;
		private DataGridViewCheckBoxColumn Column21;
		private DataGridViewCheckBoxColumn Column20;
		private DataGridViewCheckBoxColumn Column19;
		private DataGridViewCheckBoxColumn Column18;
		private DataGridViewCheckBoxColumn Column17;
		private DataGridViewCheckBoxColumn Column16;
		private DataGridViewCheckBoxColumn Column15;
		private DataGridViewCheckBoxColumn Column14;
		private DataGridViewCheckBoxColumn Column13;
		private DataGridViewCheckBoxColumn Column12;
		private DataGridViewCheckBoxColumn Column11;
		private DataGridViewCheckBoxColumn Column10;
		private DataGridViewCheckBoxColumn Column9;
		private DataGridViewCheckBoxColumn Column8;
		private DataGridViewCheckBoxColumn Column7;
		private DataGridViewCheckBoxColumn Column6;
		private DataGridViewCheckBoxColumn Column5;
		private DataGridViewCheckBoxColumn Column4;
		private DataGridViewCheckBoxColumn Column1;
		private DataGridViewCheckBoxColumn Column3;
		private DataGridViewCheckBoxColumn Column2;
		private DataGridViewTextBoxColumn DataGridViewTextBoxColumn1;
		private DataGridView DataGridView2;
		public AFN04_33()
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
					int num2 = 0;
					string text2 = Convert.ToString(this.DataGridView2.Rows[i].Cells[num2].Value);
					num2++;
					if (!string.IsNullOrEmpty(text2))
					{
						num++;
						text += int.Parse(text2).ToString("X2");
						int num3 = 0;
						num3 |= (Convert.ToBoolean(this.DataGridView2.Rows[i].Cells[num2].Value) ? 1 : 0) << 5;
						num2++;
						num3 |= (Convert.ToBoolean(this.DataGridView2.Rows[i].Cells[num2].Value) ? 1 : 0) << 4;
						num2++;
						num3 |= (Convert.ToBoolean(this.DataGridView2.Rows[i].Cells[num2].Value) ? 1 : 0) << 3;
						num2++;
						num3 |= (Convert.ToBoolean(this.DataGridView2.Rows[i].Cells[num2].Value) ? 1 : 0) << 2;
						num2++;
						num3 |= (Convert.ToBoolean(this.DataGridView2.Rows[i].Cells[num2].Value) ? 1 : 0) << 1;
						num2++;
						num3 |= (Convert.ToBoolean(this.DataGridView2.Rows[i].Cells[num2].Value) ? 1 : 0);
						num2++;
						text += DataConvert.ReverseStr(num3.ToString("X4"));
						num3 = 0;
						for (int j = 0; j < 31; j++)
						{
							num3 |= (Convert.ToBoolean(this.DataGridView2.Rows[i].Cells[num2].Value) ? 1 : 0) << j;
							num2++;
						}
						text += DataConvert.ReverseStr(num3.ToString("X8"));
						string text3 = base.OperaSend(Convert.ToString(this.DataGridView2.Rows[i].Cells[num2].Value).Trim(), 2, "A19");
						if (string.IsNullOrEmpty(text3))
						{
							text3 = "0000";
						}
						text += text3;
						num2++;
						text3 = base.OperaSend(Convert.ToString(this.DataGridView2.Rows[i].Cells[num2].Value).Trim(), 1, "BIN");
						if (string.IsNullOrEmpty(text3))
						{
							text3 = "00";
						}
						text += text3;
						num2++;
						text3 = base.OperaSend(Convert.ToString(this.DataGridView2.Rows[i].Cells[num2].Value).Trim(), 3, "A18");
						if (string.IsNullOrEmpty(text3))
						{
							text3 = "000000";
						}
						text += text3;
						num2++;
						text3 = Convert.ToString(this.DataGridView2.Rows[i].Cells[num2].Value).Trim();
						if (string.IsNullOrEmpty(text3))
						{
							text3 = "00";
						}
						text += text3;
						num2++;
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
						int num3 = 0;
						this.DataGridView2.Rows.Add();
						this.DataGridView2.Rows[i].Cells[num3].Value = base.OperaRec(data.Substring(num, 2), "BIN");
						num += 2;
						num3++;
						int num4 = DataConvert.HexToInt(DataConvert.ReverseStr(data.Substring(num, 4)));
						num += 4;
						this.DataGridView2.Rows[i].Cells[num3].Value = (num4 >> 5 & 1);
						num3++;
						this.DataGridView2.Rows[i].Cells[num3].Value = (num4 >> 4 & 1);
						num3++;
						this.DataGridView2.Rows[i].Cells[num3].Value = (num4 >> 3 & 1);
						num3++;
						this.DataGridView2.Rows[i].Cells[num3].Value = (num4 >> 2 & 1);
						num3++;
						this.DataGridView2.Rows[i].Cells[num3].Value = (num4 >> 1 & 1);
						num3++;
						this.DataGridView2.Rows[i].Cells[num3].Value = (num4 & 1);
						num3++;
						long num5 = DataConvert.HexToLong(DataConvert.ReverseStr(data.Substring(num, 8)));
						num += 8;
						for (int j = 0; j < 31; j++)
						{
							this.DataGridView2.Rows[i].Cells[num3].Value = (num5 >> j & 1L);
							num3++;
						}
						this.DataGridView2.Rows[i].Cells[num3].Value = base.OperaRec(data.Substring(num, 4), "A19");
						num += 4;
						num3++;
						this.DataGridView2.Rows[i].Cells[num3].Value = base.OperaRec(data.Substring(num, 2), "BIN");
						num += 2;
						num3++;
						this.DataGridView2.Rows[i].Cells[num3].Value = base.OperaRec(data.Substring(num, 6), "A18");
						num += 6;
						num3++;
						num4 = DataConvert.HexToInt(DataConvert.ReverseStr(data.Substring(num, 2)));
						this.DataGridView2.Rows[i].Cells[num3].Value = data.Substring(num, num4 * 8 + 2);
						num += num4 * 8 + 2;
						num3++;
					}
				}
			}
		}
		private void DataGridView2CellMouseClick(object sender, DataGridViewCellMouseEventArgs e)
		{
			if (e.ColumnIndex == 41)
			{
				iForm iForm = new AFN04_33_SD();
				iForm.NeedSave = true;
				iForm.Data = Convert.ToString(this.DataGridView2.Rows[e.RowIndex].Cells[41].Value);
				iForm.SetText();
				iForm.ShowDialog();
				this.DataGridView2.Rows[e.RowIndex].Cells[41].Value = iForm.Data;
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
			this.Column1 = new DataGridViewCheckBoxColumn();
			this.Column2 = new DataGridViewCheckBoxColumn();
			this.Column3 = new DataGridViewCheckBoxColumn();
			this.Column4 = new DataGridViewCheckBoxColumn();
			this.Column5 = new DataGridViewCheckBoxColumn();
			this.Column6 = new DataGridViewCheckBoxColumn();
			this.Column7 = new DataGridViewCheckBoxColumn();
			this.Column8 = new DataGridViewCheckBoxColumn();
			this.Column9 = new DataGridViewCheckBoxColumn();
			this.Column10 = new DataGridViewCheckBoxColumn();
			this.Column11 = new DataGridViewCheckBoxColumn();
			this.Column12 = new DataGridViewCheckBoxColumn();
			this.Column13 = new DataGridViewCheckBoxColumn();
			this.Column14 = new DataGridViewCheckBoxColumn();
			this.Column15 = new DataGridViewCheckBoxColumn();
			this.Column16 = new DataGridViewCheckBoxColumn();
			this.Column17 = new DataGridViewCheckBoxColumn();
			this.Column18 = new DataGridViewCheckBoxColumn();
			this.Column19 = new DataGridViewCheckBoxColumn();
			this.Column20 = new DataGridViewCheckBoxColumn();
			this.Column21 = new DataGridViewCheckBoxColumn();
			this.Column22 = new DataGridViewCheckBoxColumn();
			this.Column23 = new DataGridViewCheckBoxColumn();
			this.Column24 = new DataGridViewCheckBoxColumn();
			this.Column25 = new DataGridViewCheckBoxColumn();
			this.Column26 = new DataGridViewCheckBoxColumn();
			this.Column27 = new DataGridViewCheckBoxColumn();
			this.Column28 = new DataGridViewCheckBoxColumn();
			this.Column29 = new DataGridViewCheckBoxColumn();
			this.Column30 = new DataGridViewCheckBoxColumn();
			this.Column31 = new DataGridViewCheckBoxColumn();
			this.Column32 = new DataGridViewCheckBoxColumn();
			this.Column33 = new DataGridViewCheckBoxColumn();
			this.Column34 = new DataGridViewCheckBoxColumn();
			this.Column35 = new DataGridViewCheckBoxColumn();
			this.Column36 = new DataGridViewCheckBoxColumn();
			this.Column37 = new DataGridViewCheckBoxColumn();
			this.Column38 = new DataGridViewTextBoxColumn();
			this.Column39 = new DataGridViewTextBoxColumn();
			this.Column40 = new DataGridViewTextBoxColumn();
			this.Column41 = new DataGridViewLinkColumn();
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
				this.DataGridViewTextBoxColumn1,
				this.Column1,
				this.Column2,
				this.Column3,
				this.Column4,
				this.Column5,
				this.Column6,
				this.Column7,
				this.Column8,
				this.Column9,
				this.Column10,
				this.Column11,
				this.Column12,
				this.Column13,
				this.Column14,
				this.Column15,
				this.Column16,
				this.Column17,
				this.Column18,
				this.Column19,
				this.Column20,
				this.Column21,
				this.Column22,
				this.Column23,
				this.Column24,
				this.Column25,
				this.Column26,
				this.Column27,
				this.Column28,
				this.Column29,
				this.Column30,
				this.Column31,
				this.Column32,
				this.Column33,
				this.Column34,
				this.Column35,
				this.Column36,
				this.Column37,
				this.Column38,
				this.Column39,
				this.Column40,
				this.Column41
			});
			this.DataGridView2.Dock = DockStyle.Fill;
			this.DataGridView2.GridColor = SystemColors.ActiveBorder;
			this.DataGridView2.Location = new Point(0, 0);
			this.DataGridView2.MultiSelect = false;
			this.DataGridView2.Name = "DataGridView2";
			this.DataGridView2.RowTemplate.Height = 23;
			this.DataGridView2.SelectionMode = DataGridViewSelectionMode.CellSelect;
			this.DataGridView2.Size = new Size(911, 321);
			this.DataGridView2.TabIndex = 22;
			this.DataGridView2.CellMouseClick += new DataGridViewCellMouseEventHandler(this.DataGridView2CellMouseClick);
			this.DataGridViewTextBoxColumn1.HeaderText = "端口号";
			this.DataGridViewTextBoxColumn1.Name = "DataGridViewTextBoxColumn1";
			this.DataGridViewTextBoxColumn1.Width = 40;
			this.Column1.HeaderText = "电表状态字";
			this.Column1.Name = "Column1";
			this.Column1.Width = 50;
			this.Column2.HeaderText = "搜寻新增或更换电表";
			this.Column2.Name = "Column2";
			this.Column2.Width = 80;
			this.Column3.HeaderText = "定时校时";
			this.Column3.Name = "Column3";
			this.Column3.Width = 40;
			this.Column4.HeaderText = "冻结抄表";
			this.Column4.Name = "Column4";
			this.Column4.Width = 40;
			this.Column5.HeaderText = "只抄重点表";
			this.Column5.Name = "Column5";
			this.Column5.Width = 50;
			this.Column6.HeaderText = "不允许自动抄表";
			this.Column6.Name = "Column6";
			this.Column6.Width = 60;
			this.Column7.HeaderText = "1日";
			this.Column7.Name = "Column7";
			this.Column7.Width = 25;
			this.Column8.HeaderText = "2日";
			this.Column8.Name = "Column8";
			this.Column8.Width = 25;
			this.Column9.HeaderText = "3日";
			this.Column9.Name = "Column9";
			this.Column9.Width = 25;
			this.Column10.HeaderText = "4日";
			this.Column10.Name = "Column10";
			this.Column10.Width = 25;
			this.Column11.HeaderText = "5日";
			this.Column11.Name = "Column11";
			this.Column11.Width = 25;
			this.Column12.HeaderText = "6日";
			this.Column12.Name = "Column12";
			this.Column12.Width = 25;
			this.Column13.HeaderText = "7日";
			this.Column13.Name = "Column13";
			this.Column13.Width = 25;
			this.Column14.HeaderText = "8日";
			this.Column14.Name = "Column14";
			this.Column14.Width = 25;
			this.Column15.HeaderText = "9日";
			this.Column15.Name = "Column15";
			this.Column15.Width = 25;
			this.Column16.HeaderText = "10日";
			this.Column16.Name = "Column16";
			this.Column16.Width = 25;
			this.Column17.HeaderText = "11日";
			this.Column17.Name = "Column17";
			this.Column17.Width = 25;
			this.Column18.HeaderText = "12日";
			this.Column18.Name = "Column18";
			this.Column18.Width = 25;
			this.Column19.HeaderText = "13日";
			this.Column19.Name = "Column19";
			this.Column19.Width = 25;
			this.Column20.HeaderText = "14日";
			this.Column20.Name = "Column20";
			this.Column20.Width = 25;
			this.Column21.HeaderText = "15日";
			this.Column21.Name = "Column21";
			this.Column21.Width = 25;
			this.Column22.HeaderText = "16日";
			this.Column22.Name = "Column22";
			this.Column22.Width = 25;
			this.Column23.HeaderText = "17日";
			this.Column23.Name = "Column23";
			this.Column23.Width = 25;
			this.Column24.HeaderText = "18日";
			this.Column24.Name = "Column24";
			this.Column24.Width = 25;
			this.Column25.HeaderText = "19日";
			this.Column25.Name = "Column25";
			this.Column25.Width = 25;
			this.Column26.HeaderText = "20日";
			this.Column26.Name = "Column26";
			this.Column26.Width = 25;
			this.Column27.HeaderText = "21日";
			this.Column27.Name = "Column27";
			this.Column27.Width = 25;
			this.Column28.HeaderText = "22日";
			this.Column28.Name = "Column28";
			this.Column28.Width = 25;
			this.Column29.HeaderText = "23日";
			this.Column29.Name = "Column29";
			this.Column29.Width = 25;
			this.Column30.HeaderText = "24日";
			this.Column30.Name = "Column30";
			this.Column30.Width = 25;
			this.Column31.HeaderText = "25日";
			this.Column31.Name = "Column31";
			this.Column31.Width = 25;
			this.Column32.HeaderText = "26日";
			this.Column32.Name = "Column32";
			this.Column32.Width = 25;
			this.Column33.HeaderText = "27日";
			this.Column33.Name = "Column33";
			this.Column33.Width = 25;
			this.Column34.HeaderText = "28日";
			this.Column34.Name = "Column34";
			this.Column34.Width = 25;
			this.Column35.HeaderText = "29日";
			this.Column35.Name = "Column35";
			this.Column35.Width = 25;
			this.Column36.HeaderText = "30日";
			this.Column36.Name = "Column36";
			this.Column36.Width = 25;
			this.Column37.HeaderText = "31日";
			this.Column37.Name = "Column37";
			this.Column37.Width = 25;
			this.Column38.HeaderText = "抄表(HHMM)";
			this.Column38.Name = "Column38";
			this.Column38.Width = 60;
			this.Column39.HeaderText = "间隔时间";
			this.Column39.Name = "Column39";
			this.Column39.Width = 60;
			this.Column40.HeaderText = "校时(DDHHmm)";
			this.Column40.Name = "Column40";
			this.Column40.Width = 60;
			this.Column41.HeaderText = "时段表";
			this.Column41.Name = "Column41";
			this.Column41.Text = "00";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(911, 321);
			base.Controls.Add(this.DataGridView2);
			base.Name = "AFN04_33";
			this.Text = "终端抄表运行参数设置";
			((ISupportInitialize)this.DataGridView2).EndInit();
			base.ResumeLayout(false);
		}
	}
}
