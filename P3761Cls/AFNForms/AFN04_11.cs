using System;
using System.ComponentModel;
using System.Drawing;
using System.Globalization;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
	public class AFN04_11 : iForm
	{
		private IContainer components = null;
		private DataGridViewTextBoxColumn Column3;
		private DataGridViewComboBoxColumn Column4;
		private DataGridViewTextBoxColumn Column2;
		private DataGridViewTextBoxColumn Column1;
		private DataGridView DataGridView2;
		public AFN04_11()
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
			int num = 0;
			string text = string.Empty;
			checked
			{
				for (int i = 0; i < this.DataGridView2.Rows.Count; i++)
				{
					string text2 = Convert.ToString(this.DataGridView2.Rows[i].Cells[0].Value);
					if (!string.IsNullOrEmpty(text2))
					{
						num++;
						text += DataConvert.ReverseStr(int.Parse(text2).ToString("X2"));
						string s = Convert.ToString(this.DataGridView2.Rows[i].Cells[1].Value);
						text += DataConvert.ReverseStr(int.Parse(s).ToString("X2"));
						string text3 = "正向有功,正向无功,反向有功,反向无功";
						string pText = Convert.ToString(this.DataGridView2.Rows[i].Cells[2].Value);
						text += this.GetIndex(pText, text3.Split(new char[]
						{
							','
						})).ToString("X2");
						string s2 = Convert.ToString(this.DataGridView2.Rows[i].Cells[3].Value);
						text += DataConvert.ReverseStr(int.Parse(s2).ToString("X4"));
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
					int num = DataConvert.HexToInt(DataConvert.ReverseStr(data.Substring(0, 2)));
					int num2 = 2;
					for (int i = 0; i < num; i++)
					{
						this.DataGridView2.Rows.Add();
						this.DataGridView2.Rows[i].Cells[0].Value = base.OperaRec(data.Substring(num2, 2), "BIN");
						num2 += 2;
						this.DataGridView2.Rows[i].Cells[1].Value = base.OperaRec(data.Substring(num2, 2), "BIN");
						num2 += 2;
						string s = data.Substring(num2, 2);
						num2 += 2;
						int num3 = int.Parse(s, NumberStyles.HexNumber);
						string text = "正向有功,正向无功,反向有功,反向无功";
						this.DataGridView2.Rows[i].Cells[2].Value = text.Split(new char[]
						{
							','
						})[num3];
						this.DataGridView2.Rows[i].Cells[3].Value = base.OperaRec(data.Substring(num2, 4), "BIN");
						num2 += 4;
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
			this.Column4 = new DataGridViewComboBoxColumn();
			this.Column3 = new DataGridViewTextBoxColumn();
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
				this.Column4,
				this.Column3
			});
			this.DataGridView2.Dock = DockStyle.Fill;
			this.DataGridView2.GridColor = SystemColors.ActiveBorder;
			this.DataGridView2.Location = new Point(0, 0);
			this.DataGridView2.MultiSelect = false;
			this.DataGridView2.Name = "DataGridView2";
			this.DataGridView2.RowTemplate.Height = 23;
			this.DataGridView2.SelectionMode = DataGridViewSelectionMode.CellSelect;
			this.DataGridView2.Size = new Size(347, 235);
			this.DataGridView2.TabIndex = 24;
			this.Column1.HeaderText = "脉冲输入端口号";
			this.Column1.Name = "Column1";
			this.Column1.Width = 60;
			this.Column2.HeaderText = "所属测量点号";
			this.Column2.Name = "Column2";
			this.Column2.Width = 60;
			this.Column4.HeaderText = "脉冲属性";
			this.Column4.Items.AddRange(new object[]
			{
				"正向有功",
				"正向无功",
				"反向有功",
				"反向无功",
				""
			});
			this.Column4.Name = "Column4";
			this.Column4.Width = 80;
			this.Column3.HeaderText = "电表常数";
			this.Column3.Name = "Column3";
			this.Column3.Width = 80;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(347, 235);
			base.Controls.Add(this.DataGridView2);
			base.Name = "AFN04_11";
			this.Text = "终端脉冲配置参数";
			((ISupportInitialize)this.DataGridView2).EndInit();
			base.ResumeLayout(false);
		}
	}
}
