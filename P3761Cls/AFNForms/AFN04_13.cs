using System;
using System.ComponentModel;
using System.Drawing;
using System.Globalization;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
	public class AFN04_13 : iForm
	{
		private IContainer components = null;
		private DataGridViewComboBoxColumn Column4;
		private DataGridViewTextBoxColumn Column2;
		private DataGridViewTextBoxColumn Column1;
		private DataGridView DataGridView2;
		public AFN04_13()
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
					string text2 = Convert.ToString(this.DataGridView2.Rows[i].Cells[0].Value);
					if (!string.IsNullOrEmpty(text2))
					{
						num++;
						text += DataConvert.ReverseStr(int.Parse(text2).ToString("X2"));
						string s = Convert.ToString(this.DataGridView2.Rows[i].Cells[1].Value);
						text += DataConvert.ReverseStr(int.Parse(s).ToString("X2"));
						string text3 = "A相电压,B相电压,C相电压,A相电流,B相电流,C相电流";
						string pText = Convert.ToString(this.DataGridView2.Rows[i].Cells[2].Value);
						text += this.GetIndex(pText, text3.Split(new char[]
						{
							','
						})).ToString("X2");
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
						string text = "A相电压,B相电压,C相电压,A相电流,B相电流,C相电流";
						this.DataGridView2.Rows[i].Cells[2].Value = text.Split(new char[]
						{
							','
						})[num3];
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
				this.Column4
			});
			this.DataGridView2.Dock = DockStyle.Fill;
			this.DataGridView2.GridColor = SystemColors.ActiveBorder;
			this.DataGridView2.Location = new Point(0, 0);
			this.DataGridView2.MultiSelect = false;
			this.DataGridView2.Name = "DataGridView2";
			this.DataGridView2.RowTemplate.Height = 23;
			this.DataGridView2.SelectionMode = DataGridViewSelectionMode.CellSelect;
			this.DataGridView2.Size = new Size(286, 196);
			this.DataGridView2.TabIndex = 25;
			this.Column1.HeaderText = "输入端口号";
			this.Column1.Name = "Column1";
			this.Column1.Width = 60;
			this.Column2.HeaderText = "所属测量点号";
			this.Column2.Name = "Column2";
			this.Column2.Width = 60;
			this.Column4.HeaderText = "模拟量属性";
			this.Column4.Items.AddRange(new object[]
			{
				"A相电压",
				"B相电压",
				"C相电压",
				"A相电流",
				"B相电流",
				"C相电流"
			});
			this.Column4.Name = "Column4";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(286, 196);
			base.Controls.Add(this.DataGridView2);
			base.Name = "AFN04_13";
			this.Text = "终端电压/电流模拟量配置参数";
			((ISupportInitialize)this.DataGridView2).EndInit();
			base.ResumeLayout(false);
		}
	}
}
