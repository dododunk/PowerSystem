using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
	public class AFN10_10 : iForm
	{
		private IContainer components = null;
		private Label label5;
		private ComboBox comboBox2;
		private Label label6;
		private TextBox textBox3;
		private Label label3;
		private CheckBox checkBox1;
		private Label label2;
		private TextBox textBox2;
		private DataGridViewTextBoxColumn Column1;
		private DataGridView DataGridView1;
		private Label label1;
		private ComboBox textBox1;
		public AFN10_10()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			checked
			{
				for (int i = 1; i <= 31; i++)
				{
					this.textBox1.Items.Add(i.ToString());
				}
				for (int i = 0; i <= 32; i++)
				{
					this.comboBox2.Items.Add(i.ToString());
				}
				this.comboBox2.Items.Add("255");
				this.comboBox2.SelectedIndex = 0;
				this.textBox1.SelectedIndex = 0;
				this.DataGridView1.RowPostPaint += new DataGridViewRowPostPaintEventHandler(base.OnRowPostPaint);
				this.DataGridView1.CellPainting += new DataGridViewCellPaintingEventHandler(base.OnCellPainting);
				this.DataGridView1.AllowUserToAddRows = false;
				this.DataGridView1.ContextMenuStrip = this.menu.contextMenuStrip;
				this.menu.Grid = this.DataGridView1;
			}
		}
		protected override void GetText()
		{
			this.Data = "";
			this.DataGridView1.EndEdit();
			string text = string.Empty;
			text += base.OperaSend(this.textBox1.Text, 1, "BIN");
			string text2 = string.Empty;
			checked
			{
				for (int i = 0; i < this.DataGridView1.Rows.Count; i++)
				{
					string value = Convert.ToString(this.DataGridView1.Rows[i].Cells[0].Value);
					if (!string.IsNullOrEmpty(value))
					{
						text2 += base.OperaSend(value, 6, "A12");
					}
				}
				text += base.OperaSend(this.comboBox2.Text, 1, "BIN");
				text += text2;
				text += base.OperaSend(this.textBox2.Text, 6, "A12");
				text += (this.checkBox1.Checked ? "55" : "AA");
				int num = this.textBox3.Text.Trim().Length / 2;
				string str = (num > 0) ? base.OperaSend(this.textBox3.Text.Trim(), num, "BIN") : "";
				text += num.ToString("X2");
				text += str;
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
					this.textBox1.Text = base.OperaRec(data.Substring(num, 2), "BIN");
					num += 2;
					int num2 = DataConvert.HexToInt(data.Substring(num, 2));
					this.comboBox2.Text = num2.ToString();
					num += 2;
					if (num2 != 255)
					{
						for (int i = 0; i < num2; i++)
						{
							this.DataGridView1.Rows.Add();
							this.DataGridView1.Rows[i].Cells[0].Value = base.OperaRec(data.Substring(num, 12), "A12");
							num += 12;
						}
					}
					this.textBox2.Text = base.OperaRec(data.Substring(num, 12), "A12");
					num += 12;
					this.checkBox1.Checked = (data.Substring(num, 2) == "55");
					num += 2;
					num += 2;
					this.textBox3.Text = base.OperaRec(data.Substring(num), "BIN");
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
			this.textBox1 = new ComboBox();
			this.label1 = new Label();
			this.DataGridView1 = new DataGridView();
			this.Column1 = new DataGridViewTextBoxColumn();
			this.textBox2 = new TextBox();
			this.label2 = new Label();
			this.checkBox1 = new CheckBox();
			this.label3 = new Label();
			this.textBox3 = new TextBox();
			this.label6 = new Label();
			this.comboBox2 = new ComboBox();
			this.label5 = new Label();
			((ISupportInitialize)this.DataGridView1).BeginInit();
			base.SuspendLayout();
			this.textBox1.DropDownStyle = ComboBoxStyle.DropDownList;
			this.textBox1.FormattingEnabled = true;
			this.textBox1.Location = new Point(102, 12);
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new Size(68, 21);
			this.textBox1.TabIndex = 27;
			this.label1.AutoSize = true;
			this.label1.Location = new Point(7, 15);
			this.label1.Name = "label1";
			this.label1.Size = new Size(91, 13);
			this.label1.TabIndex = 26;
			this.label1.Text = "终端通信端口号";
			dataGridViewCellStyle.BackColor = Color.FromArgb(241, 244, 248);
			this.DataGridView1.AlternatingRowsDefaultCellStyle = dataGridViewCellStyle;
			this.DataGridView1.BackgroundColor = Color.White;
			this.DataGridView1.BorderStyle = BorderStyle.Fixed3D;
			dataGridViewCellStyle2.Alignment = DataGridViewContentAlignment.MiddleCenter;
			dataGridViewCellStyle2.BackColor = SystemColors.Control;
			dataGridViewCellStyle2.Font = new Font("Microsoft Sans Serif", 8.25f);
			dataGridViewCellStyle2.ForeColor = SystemColors.WindowText;
			dataGridViewCellStyle2.SelectionBackColor = SystemColors.Highlight;
			dataGridViewCellStyle2.SelectionForeColor = SystemColors.HighlightText;
			dataGridViewCellStyle2.WrapMode = DataGridViewTriState.True;
			this.DataGridView1.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle2;
			this.DataGridView1.ColumnHeadersHeight = 32;
			this.DataGridView1.Columns.AddRange(new DataGridViewColumn[]
			{
				this.Column1
			});
			this.DataGridView1.GridColor = SystemColors.ActiveBorder;
			this.DataGridView1.Location = new Point(10, 68);
			this.DataGridView1.MultiSelect = false;
			this.DataGridView1.Name = "DataGridView1";
			this.DataGridView1.RowTemplate.Height = 23;
			this.DataGridView1.SelectionMode = DataGridViewSelectionMode.CellSelect;
			this.DataGridView1.Size = new Size(336, 128);
			this.DataGridView1.TabIndex = 28;
			this.Column1.HeaderText = "第 n 级转发中继地址";
			this.Column1.Name = "Column1";
			this.Column1.Width = 200;
			this.textBox2.Location = new Point(91, 210);
			this.textBox2.Name = "textBox2";
			this.textBox2.Size = new Size(142, 20);
			this.textBox2.TabIndex = 60;
			this.textBox2.Text = "0";
			this.label2.AutoSize = true;
			this.label2.Location = new Point(12, 212);
			this.label2.Name = "label2";
			this.label2.Size = new Size(79, 13);
			this.label2.TabIndex = 59;
			this.label2.Text = "转发目标地址";
			this.checkBox1.AutoSize = true;
			this.checkBox1.Location = new Point(253, 213);
			this.checkBox1.Name = "checkBox1";
			this.checkBox1.Size = new Size(74, 17);
			this.checkBox1.TabIndex = 61;
			this.checkBox1.Text = "允许合闸";
			this.checkBox1.UseVisualStyleBackColor = true;
			this.label3.AutoSize = true;
			this.label3.Location = new Point(12, 239);
			this.label3.Name = "label3";
			this.label3.Size = new Size(127, 13);
			this.label3.TabIndex = 62;
			this.label3.Text = "转发直接遥控命令密码";
			this.textBox3.Location = new Point(10, 255);
			this.textBox3.Multiline = true;
			this.textBox3.Name = "textBox3";
			this.textBox3.ScrollBars = ScrollBars.Both;
			this.textBox3.Size = new Size(336, 38);
			this.textBox3.TabIndex = 63;
			this.label6.ForeColor = SystemColors.AppWorkspace;
			this.label6.Location = new Point(175, 37);
			this.label6.Name = "label6";
			this.label6.Size = new Size(178, 28);
			this.label6.TabIndex = 70;
			this.label6.Text = "当n=0 时，表示无中继路由(直抄);n=255 时表示无指定中继路由";
			this.comboBox2.DropDownStyle = ComboBoxStyle.DropDownList;
			this.comboBox2.FormattingEnabled = true;
			this.comboBox2.Location = new Point(102, 40);
			this.comboBox2.Name = "comboBox2";
			this.comboBox2.Size = new Size(68, 21);
			this.comboBox2.TabIndex = 69;
			this.label5.AutoSize = true;
			this.label5.Location = new Point(9, 43);
			this.label5.Name = "label5";
			this.label5.Size = new Size(85, 13);
			this.label5.TabIndex = 68;
			this.label5.Text = "转发中继级数n";
			base.AutoScaleDimensions = new SizeF(6f, 13f);
			
			base.ClientSize = new Size(357, 305);
			base.Controls.Add(this.label6);
			base.Controls.Add(this.comboBox2);
			base.Controls.Add(this.label5);
			base.Controls.Add(this.textBox3);
			base.Controls.Add(this.label3);
			base.Controls.Add(this.checkBox1);
			base.Controls.Add(this.textBox2);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.DataGridView1);
			base.Controls.Add(this.textBox1);
			base.Controls.Add(this.label1);
			this.Font = new Font("Microsoft Sans Serif", 8.25f);
			base.Name = "AFN10_10";
			this.Text = "转发主站直接对电表的遥控跳闸/允许合闸命令";
			((ISupportInitialize)this.DataGridView1).EndInit();
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
