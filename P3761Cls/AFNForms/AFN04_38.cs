using System;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
	public class AFN04_38 : iForm
	{
		private DataTable[] dt = new DataTable[16];
		private Label[] lb = new Label[32];
		private CheckBoxComboBox[] cb = new CheckBoxComboBox[32];
		private IContainer components = null;
		private GroupBox groupBox1;
		private DataGridViewCheckBoxColumn DataGridViewCheckBoxColumn9;
		private DataGridViewCheckBoxColumn DataGridViewCheckBoxColumn8;
		private DataGridViewCheckBoxColumn DataGridViewCheckBoxColumn7;
		private DataGridViewCheckBoxColumn DataGridViewCheckBoxColumn6;
		private DataGridViewCheckBoxColumn DataGridViewCheckBoxColumn5;
		private DataGridViewCheckBoxColumn DataGridViewCheckBoxColumn4;
		private DataGridViewCheckBoxColumn DataGridViewCheckBoxColumn3;
		private DataGridViewCheckBoxColumn DataGridViewCheckBoxColumn2;
		private DataGridViewCheckBoxColumn Column8;
		private DataGridViewCheckBoxColumn Column7;
		private DataGridViewCheckBoxColumn Column6;
		private DataGridViewCheckBoxColumn Column5;
		private DataGridViewCheckBoxColumn Column4;
		private DataGridViewCheckBoxColumn Column3;
		private DataGridViewCheckBoxColumn Column2;
		private DataGridViewCheckBoxColumn DataGridViewCheckBoxColumn1;
		private DataGridViewCheckBoxColumn Column1;
		private DataGridViewTextBoxColumn DataGridViewTextBoxColumn1;
		private DataGridView DataGridView2;
		private Label label6;
		private ComboBox textBox3;
		public AFN04_38()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			checked
			{
				for (int i = 0; i <= 15; i++)
				{
					this.textBox3.Items.Add(i.ToString());
				}
				this.DataGridView2.AllowUserToAddRows = false;
				this.DataGridView2.RowPostPaint += new DataGridViewRowPostPaintEventHandler(base.OnRowPostPaint);
				this.DataGridView2.CellPainting += new DataGridViewCellPaintingEventHandler(base.OnCellPainting);
			}
		}
		private void AFN04_38Load(object sender, EventArgs e)
		{
			checked
			{
				int i;
				for (i = 0; i < 16; i++)
				{
					this.DataGridView2.Rows.Add();
					this.DataGridView2.Rows[i].Cells[1].Value = i.ToString();
					this.DataGridView2.Rows[i].Cells[1].ReadOnly = true;
					this.dt[i] = new DataTable();
					this.dt[i].Columns.Add("col1");
					for (int j = 0; j < 32; j++)
					{
						DataRow dataRow = this.dt[i].NewRow();
						dataRow[0] = 0;
						this.dt[i].Rows.Add(dataRow);
					}
				}
				int num = 22;
				int num2 = 15;
				i = 0;
				while (i < 32)
				{
					if (i % 2 == 0)
					{
						num2 = 10;
					}
					if (i % 2 == 1)
					{
						num2 = 285;
					}
					this.lb[i] = new Label();
					this.lb[i].Width = 45;
					this.lb[i].Top = num;
					this.lb[i].Left = num2;
					this.lb[i].Parent = this.groupBox1;
					this.lb[i].Text = "第" + (i + 1).ToString() + "组";
					this.cb[i] = new CheckBoxComboBox();
					this.cb[i].Top = num - 2;
					this.cb[i].Width = 220;
					this.cb[i].Left = num2 + 45;
					this.cb[i].Parent = this.groupBox1;
					this.cb[i].Text = "";
					this.cb[i].DropDownHeight = 205;
					string[] array = this.Items(i);
					for (int j = 0; j < array.Length; j++)
					{
						if (!string.IsNullOrEmpty(array[j]))
						{
							this.cb[i].Items.Add(array[j]);
						}
					}
					this.cb[i].Name = "cb" + i.ToString("D2");
					this.cb[i].TextChanged += new EventHandler(this.CBTextChanged);
					i++;
					if (i % 2 == 0)
					{
						num += 24;
					}
				}
			}
		}
		private void CBTextChanged(object sender, EventArgs e)
		{
			int rowIndex = this.DataGridView2.CurrentCell.RowIndex;
			int num = int.Parse(((CheckBoxComboBox)sender).Name.Substring(2, 2));
			string[] array = ((CheckBoxComboBox)sender).Text.Split(new char[]
			{
				','
			});
			checked
			{
				if (array.Length > 0)
				{
					int num2 = 0;
					string[] array2 = this.Items(num);
					for (int i = 0; i < array.Length; i++)
					{
						if (!string.IsNullOrEmpty(array[i]))
						{
							num2 |= 1 << this.GetFn(array[i]);
						}
					}
					this.dt[rowIndex].Rows[num][0] = num2;
					Debug.Print(num2.ToString());
				}
			}
		}
		private int GetFn(string pn)
		{
			int num = int.Parse(pn.Split(new char[]
			{
				'F'
			})[1]);
			return checked(num - 1) % 8;
		}
		private string[] Items(int j)
		{
			string text = string.Empty;
			checked
			{
				for (int i = 0; i < 8; i++)
				{
					string itemAllStr = this.GetItemAllStr("F" + (8 * j + 1 + i).ToString(), (int.Parse(this.FN) == 38) ? base.ClassOne() : base.ClassTwo());
					text = text + itemAllStr + ",";
				}
				return text.Split(new char[]
				{
					','
				});
			}
		}
		protected override void GetText()
		{
			this.DataGridView2.EndEdit();
			this.Data = "";
			string str = base.OperaSend(this.textBox3.Text, 1, "BIN");
			int num = 0;
			string text = string.Empty;
			checked
			{
				for (int i = 0; i < 16; i++)
				{
					if (Convert.ToBoolean(this.DataGridView2.Rows[i].Cells[0].Value))
					{
						string str2 = base.OperaSend(this.DataGridView2.Rows[i].Cells[1].Value.ToString(), 1, "BIN");
						int num2 = 0;
						string text2 = string.Empty;
						for (int j = 0; j < 32; j++)
						{
							num2++;
							string text3 = this.dt[i].Rows[j][0].ToString();
							text2 += int.Parse(this.dt[i].Rows[j][0].ToString()).ToString("X2");
						}
						text2 = str2 + num2.ToString("X2") + text2;
						text += text2;
						num++;
					}
				}
				this.Data = str + num.ToString("X2") + text;
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
						this.textBox3.Text = base.OperaRec(data.Substring(num, 2), "BIN");
						num += 2;
						int num2 = DataConvert.HexToInt(data.Substring(num, 2));
						num += 2;
						do
						{
							int num3 = DataConvert.HexToInt(data.Substring(num, 2));
							num += 2;
							this.DataGridView2.Rows[num3].Cells[0].Value = 1;
							int num4 = DataConvert.HexToInt(data.Substring(num, 2));
							num += 2;
							for (int i = 0; i < num4; i++)
							{
								this.dt[num3].Rows[i][0] = DataConvert.HexToInt(data.Substring(num, 2));
								num += 2;
							}
						}
						while (num < data.Length);
					}
				}
			}
		}
		private void DataGridView2CellMouseClick(object sender, DataGridViewCellMouseEventArgs e)
		{
			int rowIndex = this.DataGridView2.CurrentCell.RowIndex;
			checked
			{
				for (int i = 0; i < 32; i++)
				{
					int num = int.Parse(this.dt[rowIndex].Rows[i][0].ToString());
					string text = string.Empty;
					for (int j = 0; j < 8; j++)
					{
						if ((num >> j & 1) == 1)
						{
							text = text + "F" + (8 * i + 1 + j).ToString() + ",";
							this.cb[i].CheckBoxItems[j].Checked = true;
						}
					}
					this.cb[i].Text = text;
				}
			}
		}
		private string GetItemAllStr(string pText, string[] allitem)
		{
			checked
			{
				string result;
				for (int i = 0; i < allitem.Length; i++)
				{
					if (allitem[i].Split(new char[]
					{
						' '
					})[0].IndexOf(pText) >= 0 & allitem[i].Split(new char[]
					{
						' '
					})[0] == pText)
					{
						result = pText;
						return result;
					}
				}
				result = "";
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
			this.label6 = new Label();
			this.DataGridViewCheckBoxColumn1 = new DataGridViewCheckBoxColumn();
			this.Column2 = new DataGridViewCheckBoxColumn();
			this.Column3 = new DataGridViewCheckBoxColumn();
			this.Column4 = new DataGridViewCheckBoxColumn();
			this.Column5 = new DataGridViewCheckBoxColumn();
			this.Column6 = new DataGridViewCheckBoxColumn();
			this.Column7 = new DataGridViewCheckBoxColumn();
			this.Column8 = new DataGridViewCheckBoxColumn();
			this.DataGridViewCheckBoxColumn2 = new DataGridViewCheckBoxColumn();
			this.DataGridViewCheckBoxColumn3 = new DataGridViewCheckBoxColumn();
			this.DataGridViewCheckBoxColumn4 = new DataGridViewCheckBoxColumn();
			this.DataGridViewCheckBoxColumn5 = new DataGridViewCheckBoxColumn();
			this.DataGridViewCheckBoxColumn6 = new DataGridViewCheckBoxColumn();
			this.DataGridViewCheckBoxColumn7 = new DataGridViewCheckBoxColumn();
			this.DataGridViewCheckBoxColumn8 = new DataGridViewCheckBoxColumn();
			this.DataGridViewCheckBoxColumn9 = new DataGridViewCheckBoxColumn();
			this.DataGridView2 = new DataGridView();
			this.Column1 = new DataGridViewCheckBoxColumn();
			this.DataGridViewTextBoxColumn1 = new DataGridViewTextBoxColumn();
			this.textBox3 = new ComboBox();
			this.groupBox1 = new GroupBox();
			((ISupportInitialize)this.DataGridView2).BeginInit();
			base.SuspendLayout();
			this.label6.AutoSize = true;
			this.label6.Location = new Point(15, 10);
			this.label6.Name = "label6";
			this.label6.Size = new Size(161, 12);
			this.label6.TabIndex = 8;
			this.label6.Text = "本次设置所对应的用户大类号";
			this.DataGridViewCheckBoxColumn1.HeaderText = "支持D0";
			this.DataGridViewCheckBoxColumn1.Name = "DataGridViewCheckBoxColumn1";
			this.DataGridViewCheckBoxColumn1.Width = 40;
			this.Column2.HeaderText = "支持D1";
			this.Column2.Name = "Column2";
			this.Column2.Width = 40;
			this.Column3.HeaderText = "支持D2";
			this.Column3.Name = "Column3";
			this.Column3.Width = 40;
			this.Column4.HeaderText = "支持D3";
			this.Column4.Name = "Column4";
			this.Column4.Width = 40;
			this.Column5.HeaderText = "支持D4";
			this.Column5.Name = "Column5";
			this.Column5.Width = 40;
			this.Column6.HeaderText = "支持D5";
			this.Column6.Name = "Column6";
			this.Column6.Width = 40;
			this.Column7.HeaderText = "支持D6";
			this.Column7.Name = "Column7";
			this.Column7.Width = 40;
			this.Column8.HeaderText = "支持D7";
			this.Column8.Name = "Column8";
			this.Column8.Width = 40;
			this.DataGridViewCheckBoxColumn2.HeaderText = "支持D0";
			this.DataGridViewCheckBoxColumn2.Name = "DataGridViewCheckBoxColumn2";
			this.DataGridViewCheckBoxColumn2.Width = 40;
			this.DataGridViewCheckBoxColumn3.HeaderText = "支持D1";
			this.DataGridViewCheckBoxColumn3.Name = "DataGridViewCheckBoxColumn3";
			this.DataGridViewCheckBoxColumn3.Width = 40;
			this.DataGridViewCheckBoxColumn4.HeaderText = "支持D2";
			this.DataGridViewCheckBoxColumn4.Name = "DataGridViewCheckBoxColumn4";
			this.DataGridViewCheckBoxColumn4.Width = 40;
			this.DataGridViewCheckBoxColumn5.HeaderText = "支持D3";
			this.DataGridViewCheckBoxColumn5.Name = "DataGridViewCheckBoxColumn5";
			this.DataGridViewCheckBoxColumn5.Width = 40;
			this.DataGridViewCheckBoxColumn6.HeaderText = "支持D4";
			this.DataGridViewCheckBoxColumn6.Name = "DataGridViewCheckBoxColumn6";
			this.DataGridViewCheckBoxColumn6.Width = 40;
			this.DataGridViewCheckBoxColumn7.HeaderText = "支持D5";
			this.DataGridViewCheckBoxColumn7.Name = "DataGridViewCheckBoxColumn7";
			this.DataGridViewCheckBoxColumn7.Width = 40;
			this.DataGridViewCheckBoxColumn8.HeaderText = "支持D6";
			this.DataGridViewCheckBoxColumn8.Name = "DataGridViewCheckBoxColumn8";
			this.DataGridViewCheckBoxColumn8.Width = 40;
			this.DataGridViewCheckBoxColumn9.HeaderText = "支持D7";
			this.DataGridViewCheckBoxColumn9.Name = "DataGridViewCheckBoxColumn9";
			this.DataGridViewCheckBoxColumn9.Width = 40;
			dataGridViewCellStyle.BackColor = Color.FromArgb(241, 244, 248);
			this.DataGridView2.AlternatingRowsDefaultCellStyle = dataGridViewCellStyle;
			this.DataGridView2.Anchor = (AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left);
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
			this.DataGridView2.GridColor = SystemColors.ActiveBorder;
			this.DataGridView2.Location = new Point(5, 38);
			this.DataGridView2.MultiSelect = false;
			this.DataGridView2.Name = "DataGridView2";
			this.DataGridView2.RowTemplate.Height = 23;
			this.DataGridView2.SelectionMode = DataGridViewSelectionMode.CellSelect;
			this.DataGridView2.Size = new Size(121, 406);
			this.DataGridView2.TabIndex = 68;
			this.DataGridView2.CellMouseClick += new DataGridViewCellMouseEventHandler(this.DataGridView2CellMouseClick);
			this.Column1.HeaderText = "";
			this.Column1.Name = "Column1";
			this.Column1.Width = 25;
			this.DataGridViewTextBoxColumn1.HeaderText = "小类号";
			this.DataGridViewTextBoxColumn1.Name = "DataGridViewTextBoxColumn1";
			this.DataGridViewTextBoxColumn1.Width = 50;
			this.textBox3.FormattingEnabled = true;
			this.textBox3.Location = new Point(182, 7);
			this.textBox3.Name = "textBox3";
			this.textBox3.Size = new Size(59, 20);
			this.textBox3.TabIndex = 70;
			this.textBox3.Text = "1";
			this.groupBox1.Anchor = (AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right);
			this.groupBox1.Location = new Point(130, 32);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new Size(562, 412);
			this.groupBox1.TabIndex = 71;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "支持的信息组";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(698, 450);
			base.Controls.Add(this.groupBox1);
			base.Controls.Add(this.textBox3);
			base.Controls.Add(this.DataGridView2);
			base.Controls.Add(this.label6);
			base.Name = "AFN04_38";
			this.Text = "1类,2类数据配置设置";
			base.Load += new EventHandler(this.AFN04_38Load);
			((ISupportInitialize)this.DataGridView2).EndInit();
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
