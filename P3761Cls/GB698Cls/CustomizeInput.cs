namespace GB698Cls
{
    using System;
    using System.ComponentModel;
    using System.Diagnostics;
    using System.Drawing;
    using System.Windows.Forms;

    public class CustomizeInput : iForm
    {
        private DataGridViewTextBoxColumn Column1;
        private DataGridViewTextBoxColumn Column2;
        private DataGridViewTextBoxColumn Column3;
        private DataGridViewTextBoxColumn Column4;
        private IContainer components = null;
        private DataGridView DataGridView1;

        public CustomizeInput()
        {
            this.InitializeComponent();
            this.DataGridView1.AllowUserToAddRows = false;
            this.DataGridView1.RowPostPaint += new DataGridViewRowPostPaintEventHandler(this.OnRowPostPaint);
            this.DataGridView1.CellPainting += new DataGridViewCellPaintingEventHandler(this.OnCellPainting);
            this.DataGridView1.CellClick += new DataGridViewCellEventHandler(this.GridCellClick);
            base.NeedSave = true;
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing && (this.components != null))
            {
                this.components.Dispose();
            }
            base.Dispose(disposing);
        }

        protected override void GetText()
        {
            base.Data = "";
            this.DataGridView1.EndEdit();
            string str = string.Empty;
            for (int i = 0; i < this.DataGridView1.Rows.Count; i++)
            {
                string str2 = Convert.ToString(this.DataGridView1.Rows[i].Cells[1].Value);
                string s = Convert.ToString(this.DataGridView1.Rows[i].Cells[2].Value);
                string str4 = Convert.ToString(this.DataGridView1.Rows[i].Cells[3].Value);
                switch (str2.ToUpper())
                {
                    case "A2":
                    case "A3":
                    case "A4":
                    case "A5":
                    case "A6":
                    case "A9":
                    case "A25":
                        str = str + str4;
                        break;

                    default:
                        str = str + base.OperaSend(str4, int.Parse(s), str2.ToUpper());
                        break;
                }
            }
            base.Data = str;
        }

        private void GridCellClick(object sender, DataGridViewCellEventArgs e)
        {
            int columnIndex = e.ColumnIndex;
            int rowIndex = e.RowIndex;
            if (((columnIndex == 3) && (e.RowIndex != -1)) && !this.DataGridView1.Rows[e.RowIndex].IsNewRow)
            {
                iForm form;
                string str = Convert.ToString(this.DataGridView1.Rows[rowIndex].Cells[1].Value);
                string str2 = Convert.ToString(this.DataGridView1.Rows[rowIndex].Cells[3].Value);
                switch (str.ToUpper())
                {
                    case "A2":
                        form = new A2();
                        form.Data = str2;
                        form.SetText();
                        form.ShowDialog();
                        this.DataGridView1.Rows[rowIndex].Cells[3].Value = form.Data;
                        break;

                    case "A3":
                        form = new A3();
                        form.Data = str2;
                        form.SetText();
                        form.ShowDialog();
                        this.DataGridView1.Rows[rowIndex].Cells[3].Value = form.Data;
                        break;

                    case "A4":
                        form = new A4();
                        form.Data = str2;
                        form.SetText();
                        form.ShowDialog();
                        this.DataGridView1.Rows[rowIndex].Cells[3].Value = form.Data;
                        break;

                    case "A5":
                        form = new A5();
                        form.Data = str2;
                        form.SetText();
                        form.ShowDialog();
                        this.DataGridView1.Rows[rowIndex].Cells[3].Value = form.Data;
                        break;

                    case "A6":
                        form = new A6();
                        form.Data = str2;
                        form.SetText();
                        form.ShowDialog();
                        this.DataGridView1.Rows[rowIndex].Cells[3].Value = form.Data;
                        break;

                    case "A9":
                        form = new A9();
                        form.Data = str2;
                        form.SetText();
                        form.ShowDialog();
                        this.DataGridView1.Rows[rowIndex].Cells[3].Value = form.Data;
                        break;

                    case "A25":
                        form = new A25();
                        form.Data = str2;
                        form.SetText();
                        form.ShowDialog();
                        this.DataGridView1.Rows[rowIndex].Cells[3].Value = form.Data;
                        break;
                }
            }
        }

        private void InitializeComponent()
        {
            DataGridViewCellStyle style = new DataGridViewCellStyle();
            DataGridViewCellStyle style2 = new DataGridViewCellStyle();
            this.DataGridView1 = new DataGridView();
            this.Column1 = new DataGridViewTextBoxColumn();
            this.Column3 = new DataGridViewTextBoxColumn();
            this.Column4 = new DataGridViewTextBoxColumn();
            this.Column2 = new DataGridViewTextBoxColumn();
            ((ISupportInitialize)this.DataGridView1).BeginInit();
            base.SuspendLayout();
            style.BackColor = Color.FromArgb(0xf1, 0xf4, 0xf8);
            this.DataGridView1.AlternatingRowsDefaultCellStyle = style;
            this.DataGridView1.BackgroundColor = Color.White;
            this.DataGridView1.BorderStyle = BorderStyle.Fixed3D;
            style2.Alignment = DataGridViewContentAlignment.MiddleCenter;
            style2.BackColor = SystemColors.Control;
            style2.Font = new Font("宋体", 9f, FontStyle.Regular, GraphicsUnit.Point, 0x86);
            style2.ForeColor = SystemColors.WindowText;
            style2.SelectionBackColor = SystemColors.Highlight;
            style2.SelectionForeColor = SystemColors.HighlightText;
            style2.WrapMode = DataGridViewTriState.True;
            this.DataGridView1.ColumnHeadersDefaultCellStyle = style2;
            this.DataGridView1.ColumnHeadersHeight = 0x20;
            this.DataGridView1.Columns.AddRange(new DataGridViewColumn[] { this.Column1, this.Column3, this.Column4, this.Column2 });
            this.DataGridView1.Dock = DockStyle.Fill;
            this.DataGridView1.GridColor = SystemColors.ActiveBorder;
            this.DataGridView1.Location = new Point(0, 0);
            this.DataGridView1.MultiSelect = false;
            this.DataGridView1.Name = "DataGridView1";
            this.DataGridView1.RowTemplate.Height = 0x17;
            this.DataGridView1.SelectionMode = DataGridViewSelectionMode.CellSelect;
            this.DataGridView1.Size = new Size(0x20a, 0x188);
            this.DataGridView1.TabIndex = 2;
            this.Column1.HeaderText = "数据内容";
            this.Column1.Name = "Column1";
            this.Column1.ReadOnly = true;
            this.Column1.SortMode = DataGridViewColumnSortMode.NotSortable;
            this.Column1.Width = 150;
            this.Column3.HeaderText = "数据格式";
            this.Column3.Name = "Column3";
            this.Column3.ReadOnly = true;
            this.Column3.SortMode = DataGridViewColumnSortMode.NotSortable;
            this.Column3.Width = 80;
            this.Column4.HeaderText = "字节数";
            this.Column4.Name = "Column4";
            this.Column4.ReadOnly = true;
            this.Column4.SortMode = DataGridViewColumnSortMode.NotSortable;
            this.Column4.Width = 80;
            this.Column2.HeaderText = "输入值";
            this.Column2.Name = "Column2";
            this.Column2.SortMode = DataGridViewColumnSortMode.NotSortable;
            this.Column2.Width = 150;
            base.AutoScaleDimensions = new SizeF(6f, 12f);
            
            base.ClientSize = new Size(0x20a, 0x188);
            base.Controls.Add(this.DataGridView1);
            base.Name = "CustomizeInput";
            this.Text = "自定义规约数据输入";
            ((ISupportInitialize)this.DataGridView1).EndInit();
            base.ResumeLayout(false);
        }

        public override void SetText()
        {
            int num;
            string[] strArray2;
            Color color = Color.FromArgb(0xef, 0xed, 0xe2);
            string[] strArray = base.CustomizeItems.Split(new char[] { '|' });
            for (num = 0; num < strArray.Length; num++)
            {
                strArray2 = strArray[num].Split(new char[] { ',' });
                if (strArray2.Length > 1)
                {
                    this.DataGridView1.Rows.Add();
                    this.DataGridView1.Rows[num].Cells[0].Value = strArray2[0];
                    this.DataGridView1.Rows[num].Cells[0].Style.BackColor = color;
                    this.DataGridView1.Rows[num].Cells[1].Value = strArray2[1];
                    this.DataGridView1.Rows[num].Cells[1].Style.BackColor = color;
                    this.DataGridView1.Rows[num].Cells[2].Value = strArray2[2];
                    this.DataGridView1.Rows[num].Cells[2].Style.BackColor = color;
                }
            }
            if (!string.IsNullOrEmpty(base.Data))
            {
                string data = base.Data;
                Debug.Print(data);
                int startIndex = 0;
                for (num = 0; num < this.DataGridView1.Rows.Count; num++)
                {
                    strArray2 = strArray[num].Split(new char[] { ',' });
                    string str2 = data.Substring(startIndex, 2 * int.Parse(strArray2[2]));
                    switch (strArray2[1].ToUpper())
                    {
                        case "A2":
                        case "A3":
                        case "A4":
                        case "A5":
                        case "A6":
                        case "A9":
                        case "A25":
                            this.DataGridView1.Rows[num].Cells[3].Value = str2;
                            break;

                        default:
                            this.DataGridView1.Rows[num].Cells[3].Value = base.OperaRec(str2, strArray2[1]);
                            break;
                    }
                    startIndex += 2 * int.Parse(strArray2[2]);
                }
            }
        }
    }
}

