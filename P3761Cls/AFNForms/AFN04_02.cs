using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
	public class AFN04_02 : iForm
	{
		private IContainer components = null;
		private DataGridViewTextBoxColumn Column1;
		private DataGridView DataGridView1;
		private CheckBox checkBox1;
		private Label label4;
		private Label label1;
		private ComboBox textBox1;
		public AFN04_02()
		{
			this.InitializeComponent();
			base.HelpButton = true;
			checked
			{
				for (int i = 0; i <= 16; i++)
				{
					this.textBox1.Items.Add(i.ToString());
				}
				this.textBox1.SelectedIndex = 0;
				this.DataGridView1.AllowUserToAddRows = false;
				this.DataGridView1.RowPostPaint += new DataGridViewRowPostPaintEventHandler(base.OnRowPostPaint);
				this.DataGridView1.CellPainting += new DataGridViewCellPaintingEventHandler(base.OnCellPainting);
			}
		}
		protected override void GetText()
		{
			this.DataGridView1.EndEdit();
			this.Data = "";
			string text = string.Empty;
			int num = 0;
			int num2 = this.checkBox1.Checked ? 1 : 0;
			num |= num2 << 7;
			text = (num | int.Parse(this.textBox1.Text)).ToString("X2");
			checked
			{
				for (int i = 0; i < int.Parse(this.textBox1.Text); i++)
				{
					string text2 = Convert.ToString(this.DataGridView1.Rows[i].Cells[0].Value);
					if (!string.IsNullOrEmpty(text2))
					{
						text += base.OperaSend(text2.PadLeft(4, '0'), 2, "BCD");
					}
				}
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
					int num = DataConvert.HexToInt(data.Substring(0, 2));
					this.checkBox1.Checked = (num >> 7 == 1);
					this.textBox1.SelectedIndex = num - (num >> 7 << 7);
					int num2 = 2;
					int selectedIndex = this.textBox1.SelectedIndex;
					for (int i = 0; i < selectedIndex; i++)
					{
						this.DataGridView1.Rows[i].Cells[0].Value = base.OperaRec(data.Substring(num2, 4), "BCD");
						num2 += 4;
					}
				}
			}
		}
		private void TextBox1SelectedIndexChanged(object sender, EventArgs e)
		{
			this.DataGridView1.Rows.Clear();
			int num = int.Parse(this.textBox1.Text);
			checked
			{
				for (int i = 0; i < num; i++)
				{
					this.DataGridView1.Rows.Add();
				}
			}
		}
		private void DataGridView1MouseLeave(object sender, EventArgs e)
		{
			this.DataGridView1.EndEdit();
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
            this.label1 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.DataGridView1 = new System.Windows.Forms.DataGridView();
            this.Column1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.textBox1 = new System.Windows.Forms.ComboBox();
            ((System.ComponentModel.ISupportInitialize)(this.DataGridView1)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(16, 16);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(115, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "被转发的终端地址数";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(16, 45);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(91, 13);
            this.label4.TabIndex = 5;
            this.label4.Text = "被转发终端地址";
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Location = new System.Drawing.Point(207, 15);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(79, 17);
            this.checkBox1.TabIndex = 21;
            this.checkBox1.Text = "允许/禁止";
            this.checkBox1.UseVisualStyleBackColor = true;
            // 
            // DataGridView1
            // 
            dataGridViewCellStyle1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(241)))), ((int)(((byte)(244)))), ((int)(((byte)(248)))));
            this.DataGridView1.AlternatingRowsDefaultCellStyle = dataGridViewCellStyle1;
            this.DataGridView1.BackgroundColor = System.Drawing.Color.White;
            this.DataGridView1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle2.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle2.Font = new System.Drawing.Font("SimSun", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            dataGridViewCellStyle2.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle2.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle2.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle2.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.DataGridView1.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle2;
            this.DataGridView1.ColumnHeadersHeight = 32;
            this.DataGridView1.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Column1});
            this.DataGridView1.GridColor = System.Drawing.SystemColors.ActiveBorder;
            this.DataGridView1.Location = new System.Drawing.Point(7, 60);
            this.DataGridView1.MultiSelect = false;
            this.DataGridView1.Name = "DataGridView1";
            this.DataGridView1.RowTemplate.Height = 23;
            this.DataGridView1.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.CellSelect;
            this.DataGridView1.Size = new System.Drawing.Size(278, 145);
            this.DataGridView1.TabIndex = 22;
            this.DataGridView1.MouseLeave += new System.EventHandler(this.DataGridView1MouseLeave);
            // 
            // Column1
            // 
            this.Column1.HeaderText = "被转发终端地址";
            this.Column1.Name = "Column1";
            this.Column1.Width = 210;
            // 
            // textBox1
            // 
            this.textBox1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.textBox1.FormattingEnabled = true;
            this.textBox1.Location = new System.Drawing.Point(135, 13);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(59, 21);
            this.textBox1.TabIndex = 23;
            this.textBox1.SelectedIndexChanged += new System.EventHandler(this.TextBox1SelectedIndexChanged);
            // 
            // AFN04_02
            // 
            this.ClientSize = new System.Drawing.Size(292, 212);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.DataGridView1);
            this.Controls.Add(this.checkBox1);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label1);
            this.Name = "AFN04_02";
            this.Text = "终端上行通信口无线中继转发设置";
            ((System.ComponentModel.ISupportInitialize)(this.DataGridView1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

		}
	}
}
