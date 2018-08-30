using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
	public class AFN04_65 : iForm
	{
		private IContainer components = null;
		private DateTimePicker dateTimePicker1;
		private DataGridView DataGridView2;
		private Label label14;
		private ComboBox textBox6;
		private Label label13;
		private TextBox textBox4;
		private ComboBox comboBox1;
		private Label label3;
		private Label label2;
		public AFN04_65()
		{
			this.InitializeComponent();
			base.HelpButton = true;
		}
		private void InitGrid()
		{
			this.DataGridView2.Rows.Clear();
			this.DataGridView2.Columns.Clear();
			DataGridViewComboBoxColumn dataGridViewComboBoxColumn = new DataGridViewComboBoxColumn();
			dataGridViewComboBoxColumn.HeaderText = "功能号";
			dataGridViewComboBoxColumn.Name = "zdipdz";
			dataGridViewComboBoxColumn.Width = 280;
			dataGridViewComboBoxColumn.Items.Add("");
			string[] array = new string[0];
			if (int.Parse(this.FN) == 65)
			{
				array = base.ClassOne();
			}
			else
			{
				array = base.ClassTwo();
			}
			checked
			{
				for (int i = 0; i < array.Length; i++)
				{
					dataGridViewComboBoxColumn.Items.Add(array[i]);
				}
				dataGridViewComboBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
				this.DataGridView2.Columns.Add(dataGridViewComboBoxColumn);
				dataGridViewComboBoxColumn = new DataGridViewComboBoxColumn();
				dataGridViewComboBoxColumn.HeaderText = "测量点";
				dataGridViewComboBoxColumn.Name = "zdipdk";
				dataGridViewComboBoxColumn.Width = 80;
				dataGridViewComboBoxColumn.Items.Add("");
				for (int i = 0; i < 2041; i++)
				{
					dataGridViewComboBoxColumn.Items.Add(i.ToString().PadLeft(4, '0'));
				}
				dataGridViewComboBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
				this.DataGridView2.Columns.Add(dataGridViewComboBoxColumn);
				for (int i = 1; i <= 96; i++)
				{
					this.textBox6.Items.Add(i.ToString());
				}
				this.comboBox1.SelectedIndex = 0;
				this.textBox6.SelectedIndex = 0;
				this.DataGridView2.RowPostPaint += new DataGridViewRowPostPaintEventHandler(base.OnRowPostPaint);
				this.DataGridView2.CellPainting += new DataGridViewCellPaintingEventHandler(base.OnCellPainting);
				this.DataGridView2.AllowUserToAddRows = false;
				this.DataGridView2.ContextMenuStrip = this.menu.contextMenuStrip;
				this.menu.Grid = this.DataGridView2;
			}
		}
		protected override void GetText()
		{
			this.DataGridView2.EndEdit();
			this.Data = "";
			string text = string.Empty;
			int num = 0;
			num |= this.comboBox1.SelectedIndex << 6;
			text += (num | int.Parse(this.textBox4.Text)).ToString("X2");
			text += base.OperaSend(this.dateTimePicker1.Text, 6, "A1");
			text += base.OperaSend(this.textBox6.Text, 1, "BIN");
			int num2 = 0;
			string text2 = string.Empty;
			checked
			{
				for (int i = 0; i < this.DataGridView2.Rows.Count; i++)
				{
					if (Convert.ToString(this.DataGridView2.Rows[i].Cells[0].Value) != "" | Convert.ToString(this.DataGridView2.Rows[i].Cells[1].Value) != "")
					{
						string s = this.GetItemSubStr(this.DataGridView2.Rows[i].Cells[0].Value.ToString()).PadLeft(4, '0');
						string s2 = this.DataGridView2.Rows[i].Cells[1].Value.ToString().PadLeft(4, '0');
						text2 += this.GetDataCellMark(ushort.Parse(s), ushort.Parse(s2));
						num2++;
					}
				}
				text = text + num2.ToString("X2") + text2;
				this.Data = text;
			}
		}
		public override void SetText()
		{
			this.InitGrid();
			checked
			{
				if (!string.IsNullOrEmpty(this.Data))
				{
					string data = this.Data;
					int num = 0;
					int num2 = DataConvert.HexToInt(data.Substring(num, 2));
					this.comboBox1.SelectedIndex = num2 >> 6;
					this.textBox4.Text = (num2 & 63).ToString();
					num += 2;
					try
					{
						this.dateTimePicker1.Value = DateTime.Parse(base.OperaRec(data.Substring(num, 12), "A1"));
					}
					catch
					{
					}
					num += 12;
					this.textBox6.Text = base.OperaRec(data.Substring(num, 2), "BIN");
					num += 2;
					num2 = DataConvert.HexToInt(data.Substring(num, 2));
					num += 2;
					for (int i = 0; i < num2; i++)
					{
						this.DataGridView2.Rows.Add();
						string empty = string.Empty;
						string empty2 = string.Empty;
						this.GetDataCellMark(data.Substring(num, 8), ref empty, ref empty2);
						num += 8;
						this.DataGridView2.Rows[i].Cells[0].Value = this.GetItemAllStr(empty, (int.Parse(this.FN) == 65) ? base.ClassOne() : base.ClassTwo());
						this.DataGridView2.Rows[i].Cells[1].Value = empty2;
					}
				}
			}
		}
		private string GetDataCellMark(ushort iFN, ushort iPN)
		{
			ushort num = 0;
			checked
			{
				if (iFN == 0)
				{
					num = iFN;
				}
				else
				{
					num = (ushort)((int)num | (int)((iFN - 1) / 8) << 8);
					num = (ushort)((int)num | 1 << (int)((iFN - 1) % 8));
				}
				ushort num2 = 0;
				if (iPN == 0 || iPN == 65535)
				{
					num2 = iPN;
				}
				else
				{
					num2 = (ushort)((int)num2 | (int)((iPN - 1) / 8 + 1) << 8);
					num2 = (ushort)((int)num2 | 1 << (int)(iPN % 8 - 1));
				}
				string text = num.ToString("X4") + num2.ToString("X4");
				return text.Substring(6, 2) + text.Substring(4, 2) + text.Substring(2, 2) + text.Substring(0, 2);
			}
		}
		public void GetDataCellMark(string strValue, ref string strFN, ref string strPN)
		{
			strFN = this.FNToDec(strValue.Substring(4, 4));
			strPN = this.PNToDec(strValue.Substring(0, 4));
		}
		private string PNToDec(string strValue)
		{
			checked
			{
				string result;
				if (strValue == "0000" || strValue == "FFFF")
				{
					result = strValue;
				}
				else
				{
					int num = DataConvert.HexToInt(strValue.Substring(0, 2));
					int num2 = DataConvert.HexToInt(strValue.Substring(2, 2));
					num2 *= 8;
					for (int i = 0; i < 8; i++)
					{
						if (num >> i == 1)
						{
							num2 += i + 1;
							break;
						}
					}
					num2 -= 8;
					if (num2 <= 0)
					{
						result = "Invalid";
					}
					else
					{
						result = num2.ToString("0000");
					}
				}
				return result;
			}
		}
		private string FNToDec(string strValue)
		{
			int num = DataConvert.HexToInt(strValue.Substring(0, 2));
			int num2 = DataConvert.HexToInt(strValue.Substring(2, 2));
			checked
			{
				string result;
				if (num2 > 30)
				{
					result = "Invalid";
				}
				else
				{
					num2 *= 8;
					for (int i = 0; i < 8; i++)
					{
						if (num >> i == 1)
						{
							num2 += i + 1;
							break;
						}
					}
					result = num2.ToString("0000");
				}
				return result;
			}
		}
		private string GetItemAllStr(string pText, string[] allitem)
		{
			checked
			{
				string result;
				for (int i = 0; i < allitem.Length; i++)
				{
					if (allitem[i].IndexOf(pText) >= 0)
					{
						result = allitem[i];
						return result;
					}
				}
				result = "";
				return result;
			}
		}
		private string GetItemSubStr(string pText)
		{
			return pText.Split(new char[]
			{
				'|'
			})[1];
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
			this.label2 = new Label();
			this.label3 = new Label();
			this.comboBox1 = new ComboBox();
			this.textBox4 = new TextBox();
			this.label13 = new Label();
			this.label14 = new Label();
			this.DataGridView2 = new DataGridView();
			this.textBox6 = new ComboBox();
			this.dateTimePicker1 = new DateTimePicker();
			((ISupportInitialize)this.DataGridView2).BeginInit();
			base.SuspendLayout();
			this.label2.AutoSize = true;
			this.label2.Location = new Point(14, 15);
			this.label2.Name = "label2";
			this.label2.Size = new Size(101, 12);
			this.label2.TabIndex = 21;
			this.label2.Text = "定时上报周期单位";
			this.label3.AutoSize = true;
			this.label3.Location = new Point(14, 41);
			this.label3.Name = "label3";
			this.label3.Size = new Size(77, 12);
			this.label3.TabIndex = 25;
			this.label3.Text = "上报基准时间";
			this.comboBox1.DropDownStyle = ComboBoxStyle.DropDownList;
			this.comboBox1.FormattingEnabled = true;
			this.comboBox1.Items.AddRange(new object[]
			{
				"分",
				"时",
				"日",
				"月"
			});
			this.comboBox1.Location = new Point(121, 12);
			this.comboBox1.Name = "comboBox1";
			this.comboBox1.Size = new Size(59, 20);
			this.comboBox1.TabIndex = 52;
			this.textBox4.Location = new Point(250, 11);
			this.textBox4.Name = "textBox4";
			this.textBox4.Size = new Size(28, 21);
			this.textBox4.TabIndex = 57;
			this.textBox4.Text = "0";
			this.label13.AutoSize = true;
			this.label13.Location = new Point(191, 15);
			this.label13.Name = "label13";
			this.label13.Size = new Size(53, 12);
			this.label13.TabIndex = 56;
			this.label13.Text = "上报周期";
			this.label14.AutoSize = true;
			this.label14.Location = new Point(292, 14);
			this.label14.Name = "label14";
			this.label14.Size = new Size(77, 12);
			this.label14.TabIndex = 58;
			this.label14.Text = "抽取数据倍率";
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
			this.DataGridView2.GridColor = SystemColors.ActiveBorder;
			this.DataGridView2.Location = new Point(6, 67);
			this.DataGridView2.MultiSelect = false;
			this.DataGridView2.Name = "DataGridView2";
			this.DataGridView2.RowTemplate.Height = 23;
			this.DataGridView2.SelectionMode = DataGridViewSelectionMode.CellSelect;
			this.DataGridView2.Size = new Size(424, 211);
			this.DataGridView2.TabIndex = 61;
			this.textBox6.FormattingEnabled = true;
			this.textBox6.Location = new Point(375, 11);
			this.textBox6.Name = "textBox6";
			this.textBox6.Size = new Size(42, 20);
			this.textBox6.TabIndex = 62;
			this.dateTimePicker1.CustomFormat = "yy-MM-dd HH:mm:ss";
			this.dateTimePicker1.Format = DateTimePickerFormat.Custom;
			this.dateTimePicker1.Location = new Point(121, 37);
			this.dateTimePicker1.Name = "dateTimePicker1";
			this.dateTimePicker1.Size = new Size(157, 21);
			this.dateTimePicker1.TabIndex = 63;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(436, 285);
			base.Controls.Add(this.dateTimePicker1);
			base.Controls.Add(this.textBox6);
			base.Controls.Add(this.DataGridView2);
			base.Controls.Add(this.label14);
			base.Controls.Add(this.textBox4);
			base.Controls.Add(this.label13);
			base.Controls.Add(this.comboBox1);
			base.Controls.Add(this.label3);
			base.Controls.Add(this.label2);
			base.Name = "AFN04_65";
			this.Text = "定时上报1,2类数据任务设置";
			((ISupportInitialize)this.DataGridView2).EndInit();
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
