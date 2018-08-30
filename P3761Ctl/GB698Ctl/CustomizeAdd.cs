using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Ctl
{
	public class FormCustomizeAdd : Form
	{
		private IContainer components = null;
		private Panel panel1;
		private DataGridViewEx grid1;
		private DataGridViewTextBoxColumn Column3;
		private DataGridViewComboBoxColumn Column2;
		private DataGridViewTextBoxColumn Column1;
		private Button button2;
		private Button button1;
		private TextBox textBox1;
		private Label label1;
		private Label label2;
		private ComboBox AFN;
		private Label label3;
		private ComboBox FN;
		public FormCustomizeAdd()
		{
			this.InitializeComponent();
			checked
			{
				for (int i = 1; i < 235; i++)
				{
					this.FN.Items.Add(i.ToString().PadLeft(4, '0'));
				}
			}
		}
		private void Button1Click(object sender, EventArgs e)
		{
			string text = string.Empty;
			checked
			{
				for (int i = 0; i < this.grid1.Rows.Count; i++)
				{
					if (!this.grid1.Rows[i].IsNewRow)
					{
						string text2 = Convert.ToString(this.grid1.Rows[i].Cells[0].Value);
						string text3 = Convert.ToString(this.grid1.Rows[i].Cells[1].Value);
						string text4 = Convert.ToString(this.grid1.Rows[i].Cells[2].Value);
						string text5 = text;
						text = string.Concat(new string[]
						{
							text5,
							text2,
							",",
							text3,
							",",
							text4,
							"|"
						});
					}
				}
				string name = "F" + int.Parse(this.FN.Text).ToString() + " " + this.textBox1.Text.Trim();
				Program.gFaDataBase.InsertCustomize(name, this.AFN.Text.Trim(), this.FN.Text.Trim(), text);
				MessageBox.Show("添加完成");
			}
		}
		private void Button2Click(object sender, EventArgs e)
		{
			base.Close();
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
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            this.panel1 = new System.Windows.Forms.Panel();
            this.grid1 = new System.Windows.Forms.DataGridViewEx();
            this.Column1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column2 = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.Column3 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.button2 = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.FN = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.AFN = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.grid1)).BeginInit();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.grid1);
            this.panel1.Controls.Add(this.button2);
            this.panel1.Controls.Add(this.button1);
            this.panel1.Controls.Add(this.textBox1);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Controls.Add(this.FN);
            this.panel1.Controls.Add(this.label3);
            this.panel1.Controls.Add(this.AFN);
            this.panel1.Controls.Add(this.label2);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(423, 420);
            this.panel1.TabIndex = 0;
            // 
            // grid1
            // 
            dataGridViewCellStyle1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(240)))), ((int)(((byte)(240)))), ((int)(((byte)(240)))));
            this.grid1.AlternatingRowsDefaultCellStyle = dataGridViewCellStyle1;
            this.grid1.BackgroundColor = System.Drawing.Color.White;
            this.grid1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.grid1.ColumnHeaderColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle2.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle2.Font = new System.Drawing.Font("SimSun", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            dataGridViewCellStyle2.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle2.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle2.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle2.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.grid1.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle2;
            this.grid1.ColumnHeadersHeight = 28;
            this.grid1.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Column1,
            this.Column2,
            this.Column3});
            this.grid1.GridColor = System.Drawing.SystemColors.ActiveBorder;
            this.grid1.Location = new System.Drawing.Point(6, 64);
            this.grid1.MultiSelect = false;
            this.grid1.Name = "grid1";
            this.grid1.RowHeaderColor = System.Drawing.SystemColors.Control;
            this.grid1.RowTemplate.Height = 23;
            this.grid1.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.CellSelect;
            this.grid1.Size = new System.Drawing.Size(404, 291);
            this.grid1.TabIndex = 23;
            // 
            // Column1
            // 
            this.Column1.HeaderText = "数据内容";
            this.Column1.Name = "Column1";
            this.Column1.Width = 200;
            // 
            // Column2
            // 
            this.Column2.HeaderText = "数据格式";
            this.Column2.Items.AddRange(new object[] {
            "BIN",
            "ASCII",
            "BCD",
            "HEX",
            "BS",
            "A1",
            "A2",
            "A3",
            "A4",
            "A5",
            "A6",
            "A7",
            "A8",
            "A9",
            "A10",
            "A11",
            "A12",
            "A13",
            "A14",
            "A15",
            "A16",
            "A17",
            "A18",
            "A19",
            "A20",
            "A21",
            "A22",
            "A23",
            "A24",
            "A25",
            "A26",
            "A27"});
            this.Column2.Name = "Column2";
            this.Column2.Width = 80;
            // 
            // Column3
            // 
            this.Column3.HeaderText = "字节数";
            this.Column3.Name = "Column3";
            this.Column3.Width = 60;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(362, 359);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(46, 23);
            this.button2.TabIndex = 22;
            this.button2.Text = "退出";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.Button2Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(310, 359);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(46, 23);
            this.button1.TabIndex = 21;
            this.button1.Text = "添加";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.Button1Click);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(47, 37);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(278, 20);
            this.textBox1.TabIndex = 20;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 40);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(31, 13);
            this.label1.TabIndex = 19;
            this.label1.Text = "名称";
            // 
            // FN
            // 
            this.FN.FormattingEnabled = true;
            this.FN.Location = new System.Drawing.Point(134, 11);
            this.FN.Name = "FN";
            this.FN.Size = new System.Drawing.Size(61, 21);
            this.FN.TabIndex = 18;
            this.FN.Text = "0001";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(111, 14);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(21, 13);
            this.label3.TabIndex = 17;
            this.label3.Text = "FN";
            // 
            // AFN
            // 
            this.AFN.FormattingEnabled = true;
            this.AFN.Items.AddRange(new object[] {
            "01",
            "02",
            "03",
            "04",
            "05",
            "06 ",
            "08",
            "09",
            "0A",
            "0B",
            "0C",
            "0D",
            "0E",
            "0F",
            "10"});
            this.AFN.Location = new System.Drawing.Point(47, 11);
            this.AFN.Name = "AFN";
            this.AFN.Size = new System.Drawing.Size(50, 21);
            this.AFN.TabIndex = 16;
            this.AFN.Text = "0A";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 14);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(28, 13);
            this.label2.TabIndex = 15;
            this.label2.Text = "AFN";
            // 
            // CustomizeAdd
            // 
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(239)))), ((int)(((byte)(237)))), ((int)(((byte)(226)))));
            this.ClientSize = new System.Drawing.Size(423, 420);
            this.Controls.Add(this.panel1);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "CustomizeAdd";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "自定义规约添加";
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.grid1)).EndInit();
            this.ResumeLayout(false);

		}
	}
}
