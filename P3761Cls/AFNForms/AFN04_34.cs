using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Cls
{
	public class AFN04_34 : iForm
	{
		private IContainer components = null;
		private DataGridViewTextBoxColumn Column40;
		private DataGridViewTextBoxColumn Column38;
		private DataGridViewTextBoxColumn DataGridViewTextBoxColumn1;
		private DataGridView DataGridView2;
		public AFN04_34()
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
					string str = Convert.ToString(this.DataGridView2.Rows[i].Cells[1].Value);
					string value2 = Convert.ToString(this.DataGridView2.Rows[i].Cells[2].Value);
					if (!string.IsNullOrEmpty(value))
					{
						text += base.OperaSend(value, 1, "BIN");
						text += str;
						text += base.OperaSend(value2, 4, "BIN");
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
						this.DataGridView2.Rows[i].Cells[0].Value = base.OperaRec(data.Substring(num2, 2), "BIN");
						num2 += 2;
						this.DataGridView2.Rows[i].Cells[1].Value = data.Substring(num2, 2);
						num2 += 2;
						this.DataGridView2.Rows[i].Cells[2].Value = base.OperaRec(data.Substring(num2, 8), "BIN");
						num2 += 8;
					}
				}
			}
		}
		private void DataGridView2CellMouseClick(object sender, DataGridViewCellMouseEventArgs e)
		{
			if (e.ColumnIndex == 1)
			{
				iForm iForm = new CtlWord();
				iForm.NeedSave = true;
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
			this.DataGridView2 = new DataGridView();
			this.DataGridViewTextBoxColumn1 = new DataGridViewTextBoxColumn();
			this.Column38 = new DataGridViewTextBoxColumn();
			this.Column40 = new DataGridViewTextBoxColumn();
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
				this.Column38,
				this.Column40
			});
			this.DataGridView2.Dock = DockStyle.Fill;
			this.DataGridView2.GridColor = SystemColors.ActiveBorder;
			this.DataGridView2.Location = new Point(0, 0);
			this.DataGridView2.MultiSelect = false;
			this.DataGridView2.Name = "DataGridView2";
			this.DataGridView2.RowTemplate.Height = 23;
			this.DataGridView2.SelectionMode = DataGridViewSelectionMode.CellSelect;
			this.DataGridView2.Size = new Size(406, 287);
			this.DataGridView2.TabIndex = 22;
			this.DataGridView2.CellMouseClick += new DataGridViewCellMouseEventHandler(this.DataGridView2CellMouseClick);
			this.DataGridViewTextBoxColumn1.HeaderText = "终端通信端口号";
			this.DataGridViewTextBoxColumn1.Name = "DataGridViewTextBoxColumn1";
			this.Column38.HeaderText = "与终端接口端的通信控制字";
			this.Column38.Name = "Column38";
			this.Column38.ReadOnly = true;
			this.Column38.Width = 120;
			this.Column40.HeaderText = "与终端接口对应端的通信速率(bps)";
			this.Column40.Name = "Column40";
			this.Column40.Width = 120;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(406, 287);
			base.Controls.Add(this.DataGridView2);
			base.Name = "AFN04_34";
			this.Text = "集中器下行通信模块的参数设置";
			((ISupportInitialize)this.DataGridView2).EndInit();
			base.ResumeLayout(false);
		}
	}
}
