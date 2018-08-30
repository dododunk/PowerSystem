using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
	public class AFN04_37 : iForm
	{
		private IContainer components = null;
		private DataGridViewTextBoxColumn Column1;
		private DataGridViewTextBoxColumn DataGridViewTextBoxColumn1;
		private DataGridView DataGridView2;
		private Label label1;
		private Label label14;
		private TextBox textBox6;
		private Label label13;
		private TextBox textBox4;
		private CheckBox checkBox1;
		private CheckBox checkBox2;
		private CheckBox checkBox3;
		private Label label12;
		private ComboBox comboBox4;
		private Label label11;
		private ComboBox comboBox3;
		private GroupBox groupBox1;
		private Label label7;
		private ComboBox comboBox1;
		private Label label3;
		private TextBox textBox5;
		private Label label6;
		private TextBox textBox3;
		private TextBox textBox2;
		private Label label2;
		public AFN04_37()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			this.comboBox3.SelectedIndex = 0;
			this.comboBox4.SelectedIndex = 0;
			this.comboBox1.SelectedIndex = 0;
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
			text += base.OperaSend(this.textBox3.Text, 1, "BIN");
			int num = 0;
			num |= this.comboBox3.SelectedIndex << 5;
			num |= (this.checkBox1.Checked ? 1 : 0) << 4;
			num |= (this.checkBox2.Checked ? 1 : 0) << 3;
			num |= (this.checkBox3.Checked ? 1 : 0) << 2;
			text += (num | this.comboBox4.SelectedIndex).ToString("X2");
			text += base.OperaSend(this.textBox2.Text, 1, "BIN");
			text += base.OperaSend(this.textBox4.Text, 1, "BIN");
			text += base.OperaSend(this.textBox5.Text, 1, "BIN");
			text += base.OperaSend(this.textBox6.Text, 1, "BIN");
			num = 0;
			num |= this.comboBox1.SelectedIndex << 7;
			int num2 = 0;
			string text2 = string.Empty;
			checked
			{
				for (int i = 0; i < this.DataGridView2.Rows.Count; i++)
				{
					string value = Convert.ToString(this.DataGridView2.Rows[i].Cells[0].Value);
					string value2 = Convert.ToString(this.DataGridView2.Rows[i].Cells[1].Value);
					if (!string.IsNullOrEmpty(value))
					{
						text2 += base.OperaSend(value, 2, "BCD");
						text2 += base.OperaSend(value2, 2, "BCD");
						num2++;
					}
				}
				text += (num | num2).ToString("X2");
				text += text2;
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
					this.textBox3.Text = base.OperaRec(data.Substring(num, 2), "BIN");
					num += 2;
					int num2 = DataConvert.HexToInt(data.Substring(num, 2));
					num += 2;
					this.comboBox3.SelectedIndex = num2 >> 5;
					this.checkBox1.Checked = ((num2 >> 4 & 1) == 1);
					this.checkBox2.Checked = ((num2 >> 3 & 1) == 1);
					this.checkBox3.Checked = ((num2 >> 2 & 1) == 1);
					this.comboBox4.SelectedIndex = (num2 & 3);
					this.textBox2.Text = base.OperaRec(data.Substring(num, 2), "BIN");
					num += 2;
					this.textBox4.Text = base.OperaRec(data.Substring(num, 2), "BIN");
					num += 2;
					this.textBox5.Text = base.OperaRec(data.Substring(num, 2), "BIN");
					num += 2;
					this.textBox6.Text = base.OperaRec(data.Substring(num, 2), "BIN");
					num += 2;
					num2 = DataConvert.HexToInt(data.Substring(num, 2));
					num += 2;
					this.comboBox1.SelectedIndex = num2 >> 7;
					int num3 = num2 & 15;
					for (int i = 0; i < num3; i++)
					{
						this.DataGridView2.Rows.Add();
						this.DataGridView2.Rows[i].Cells[0].Value = base.OperaRec(data.Substring(num, 4), "BCD");
						num += 4;
						this.DataGridView2.Rows[i].Cells[1].Value = base.OperaRec(data.Substring(num, 4), "BCD");
						num += 4;
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
			this.textBox3 = new TextBox();
			this.label6 = new Label();
			this.textBox2 = new TextBox();
			this.label2 = new Label();
			this.textBox5 = new TextBox();
			this.label3 = new Label();
			this.comboBox1 = new ComboBox();
			this.label7 = new Label();
			this.groupBox1 = new GroupBox();
			this.comboBox4 = new ComboBox();
			this.label12 = new Label();
			this.checkBox3 = new CheckBox();
			this.checkBox2 = new CheckBox();
			this.checkBox1 = new CheckBox();
			this.comboBox3 = new ComboBox();
			this.label11 = new Label();
			this.textBox4 = new TextBox();
			this.label13 = new Label();
			this.textBox6 = new TextBox();
			this.label14 = new Label();
			this.label1 = new Label();
			this.DataGridView2 = new DataGridView();
			this.DataGridViewTextBoxColumn1 = new DataGridViewTextBoxColumn();
			this.Column1 = new DataGridViewTextBoxColumn();
			this.groupBox1.SuspendLayout();
			((ISupportInitialize)this.DataGridView2).BeginInit();
			base.SuspendLayout();
			this.textBox3.Location = new Point(137, 14);
			this.textBox3.Name = "textBox3";
			this.textBox3.Size = new Size(53, 21);
			this.textBox3.TabIndex = 9;
			this.textBox3.Text = "1";
			this.label6.AutoSize = true;
			this.label6.Location = new Point(18, 17);
			this.label6.Name = "label6";
			this.label6.Size = new Size(113, 12);
			this.label6.TabIndex = 8;
			this.label6.Text = "终端级联通信端口号";
			this.textBox2.Location = new Point(190, 113);
			this.textBox2.Name = "textBox2";
			this.textBox2.Size = new Size(63, 21);
			this.textBox2.TabIndex = 22;
			this.textBox2.Text = "1";
			this.label2.AutoSize = true;
			this.label2.Location = new Point(23, 117);
			this.label2.Name = "label2";
			this.label2.Size = new Size(167, 12);
			this.label2.TabIndex = 21;
			this.label2.Text = "接收等待报文超时时间(100ms)";
			this.textBox5.Location = new Point(215, 140);
			this.textBox5.Name = "textBox5";
			this.textBox5.Size = new Size(38, 21);
			this.textBox5.TabIndex = 26;
			this.textBox5.Text = "1";
			this.label3.AutoSize = true;
			this.label3.Location = new Point(23, 143);
			this.label3.Name = "label3";
			this.label3.Size = new Size(185, 12);
			this.label3.TabIndex = 25;
			this.label3.Text = "级联方(主动站)接收失败重发次数";
			this.comboBox1.DropDownStyle = ComboBoxStyle.DropDownList;
			this.comboBox1.FormattingEnabled = true;
			this.comboBox1.Items.AddRange(new object[]
			{
				"级联方",
				"被级联方"
			});
			this.comboBox1.Location = new Point(123, 168);
			this.comboBox1.Name = "comboBox1";
			this.comboBox1.Size = new Size(130, 20);
			this.comboBox1.TabIndex = 52;
			this.label7.AutoSize = true;
			this.label7.Font = new Font("Arial", 9f);
			this.label7.Location = new Point(23, 171);
			this.label7.Name = "label7";
			this.label7.Size = new Size(94, 15);
			this.label7.TabIndex = 51;
			this.label7.Text = "级联/被级联标志";
			this.groupBox1.Controls.Add(this.comboBox4);
			this.groupBox1.Controls.Add(this.label12);
			this.groupBox1.Controls.Add(this.checkBox3);
			this.groupBox1.Controls.Add(this.checkBox2);
			this.groupBox1.Controls.Add(this.checkBox1);
			this.groupBox1.Controls.Add(this.comboBox3);
			this.groupBox1.Controls.Add(this.label11);
			this.groupBox1.Location = new Point(12, 45);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new Size(507, 54);
			this.groupBox1.TabIndex = 55;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "终端级联通信控制字";
			this.comboBox4.DropDownStyle = ComboBoxStyle.DropDownList;
			this.comboBox4.FormattingEnabled = true;
			this.comboBox4.Items.AddRange(new object[]
			{
				"5",
				"6",
				"7",
				"8"
			});
			this.comboBox4.Location = new Point(436, 21);
			this.comboBox4.Name = "comboBox4";
			this.comboBox4.Size = new Size(50, 20);
			this.comboBox4.TabIndex = 59;
			this.label12.AutoSize = true;
			this.label12.Font = new Font("Arial", 9f);
			this.label12.Location = new Point(399, 24);
			this.label12.Name = "label12";
			this.label12.Size = new Size(31, 15);
			this.label12.TabIndex = 58;
			this.label12.Text = "位数";
			this.checkBox3.AutoSize = true;
			this.checkBox3.Location = new Point(316, 24);
			this.checkBox3.Name = "checkBox3";
			this.checkBox3.Size = new Size(60, 16);
			this.checkBox3.TabIndex = 57;
			this.checkBox3.Text = "奇校验";
			this.checkBox3.UseVisualStyleBackColor = true;
			this.checkBox2.AutoSize = true;
			this.checkBox2.Location = new Point(250, 24);
			this.checkBox2.Name = "checkBox2";
			this.checkBox2.Size = new Size(60, 16);
			this.checkBox2.TabIndex = 56;
			this.checkBox2.Text = "有校验";
			this.checkBox2.UseVisualStyleBackColor = true;
			this.checkBox1.AutoSize = true;
			this.checkBox1.Location = new Point(178, 24);
			this.checkBox1.Name = "checkBox1";
			this.checkBox1.Size = new Size(66, 16);
			this.checkBox1.TabIndex = 55;
			this.checkBox1.Text = "2停止位";
			this.checkBox1.UseVisualStyleBackColor = true;
			this.comboBox3.DropDownStyle = ComboBoxStyle.DropDownList;
			this.comboBox3.FormattingEnabled = true;
			this.comboBox3.Items.AddRange(new object[]
			{
				"300",
				"600",
				"1200",
				"2400",
				"4800",
				"7200",
				"9600",
				"19200",
				""
			});
			this.comboBox3.Location = new Point(85, 20);
			this.comboBox3.Name = "comboBox3";
			this.comboBox3.Size = new Size(75, 20);
			this.comboBox3.TabIndex = 54;
			this.label11.AutoSize = true;
			this.label11.Font = new Font("Arial", 9f);
			this.label11.Location = new Point(12, 22);
			this.label11.Name = "label11";
			this.label11.Size = new Size(67, 15);
			this.label11.TabIndex = 53;
			this.label11.Text = "Baud(bit/s)";
			this.textBox4.Location = new Point(435, 113);
			this.textBox4.Name = "textBox4";
			this.textBox4.Size = new Size(63, 21);
			this.textBox4.TabIndex = 57;
			this.textBox4.Text = "1";
			this.label13.AutoSize = true;
			this.label13.Location = new Point(268, 117);
			this.label13.Name = "label13";
			this.label13.Size = new Size(161, 12);
			this.label13.TabIndex = 56;
			this.label13.Text = "接收等待字节超时时间(10ms)";
			this.textBox6.Location = new Point(435, 143);
			this.textBox6.Name = "textBox6";
			this.textBox6.Size = new Size(63, 21);
			this.textBox6.TabIndex = 59;
			this.textBox6.Text = "1";
			this.label14.AutoSize = true;
			this.label14.Location = new Point(352, 146);
			this.label14.Name = "label14";
			this.label14.Size = new Size(77, 12);
			this.label14.TabIndex = 58;
			this.label14.Text = "级联巡测周期";
			this.label1.AutoSize = true;
			this.label1.Font = new Font("Times New Roman", 9f, FontStyle.Regular, GraphicsUnit.Point, 0);
			this.label1.ForeColor = SystemColors.AppWorkspace;
			this.label1.Location = new Point(259, 171);
			this.label1.Name = "label1";
			this.label1.Size = new Size(162, 15);
			this.label1.TabIndex = 60;
			this.label1.Text = "级联方:n=(0-3) / 被级联方:n=1";
			dataGridViewCellStyle.BackColor = Color.FromArgb(241, 244, 248);
			this.DataGridView2.AlternatingRowsDefaultCellStyle = dataGridViewCellStyle;
			this.DataGridView2.Anchor = (AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right);
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
				this.Column1
			});
			this.DataGridView2.GridColor = SystemColors.ActiveBorder;
			this.DataGridView2.Location = new Point(12, 198);
			this.DataGridView2.MultiSelect = false;
			this.DataGridView2.Name = "DataGridView2";
			this.DataGridView2.RowTemplate.Height = 23;
			this.DataGridView2.SelectionMode = DataGridViewSelectionMode.CellSelect;
			this.DataGridView2.Size = new Size(507, 206);
			this.DataGridView2.TabIndex = 61;
			this.DataGridViewTextBoxColumn1.HeaderText = "行政区划码";
			this.DataGridViewTextBoxColumn1.Name = "DataGridViewTextBoxColumn1";
			this.DataGridViewTextBoxColumn1.Width = 220;
			this.Column1.HeaderText = "终端地址";
			this.Column1.Name = "Column1";
			this.Column1.Width = 200;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(530, 416);
			base.Controls.Add(this.DataGridView2);
			base.Controls.Add(this.label1);
			base.Controls.Add(this.textBox6);
			base.Controls.Add(this.label14);
			base.Controls.Add(this.textBox4);
			base.Controls.Add(this.label13);
			base.Controls.Add(this.groupBox1);
			base.Controls.Add(this.comboBox1);
			base.Controls.Add(this.label7);
			base.Controls.Add(this.textBox5);
			base.Controls.Add(this.label3);
			base.Controls.Add(this.textBox2);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.textBox3);
			base.Controls.Add(this.label6);
			base.Name = "AFN04_37";
			this.Text = "终端级联通信参数";
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			((ISupportInitialize)this.DataGridView2).EndInit();
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
