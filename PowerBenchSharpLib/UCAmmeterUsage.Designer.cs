namespace PowerBenchSharpLib
{
    partial class UCAmmeterUsage
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param _name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.flowLayoutPanel1 = new System.Windows.Forms.FlowLayoutPanel();
            this.ucFilterCombo_TimeRage = new PowerBenchSharpLib.ComboField();
            this.ucFilterCombo_Station = new PowerBenchSharpLib.ComboField();
            this.comboField1 = new PowerBenchSharpLib.ComboField();
            this.comboField2 = new PowerBenchSharpLib.ComboField();
            this.comboField3 = new PowerBenchSharpLib.ComboField();
            this.comboField4 = new PowerBenchSharpLib.ComboField();
            this.button_query = new System.Windows.Forms.Button();
            this.tableLayoutPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.flowLayoutPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Controls.Add(this.dataGridView1, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.flowLayoutPanel1, 0, 0);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 30.98268F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 69.01732F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(750, 509);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // dataGridView1
            // 
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dataGridView1.Location = new System.Drawing.Point(3, 160);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.Size = new System.Drawing.Size(744, 346);
            this.dataGridView1.TabIndex = 0;
            // 
            // flowLayoutPanel1
            // 
            this.flowLayoutPanel1.Controls.Add(this.ucFilterCombo_TimeRage);
            this.flowLayoutPanel1.Controls.Add(this.ucFilterCombo_Station);
            this.flowLayoutPanel1.Controls.Add(this.comboField1);
            this.flowLayoutPanel1.Controls.Add(this.comboField2);
            this.flowLayoutPanel1.Controls.Add(this.comboField3);
            this.flowLayoutPanel1.Controls.Add(this.comboField4);
            this.flowLayoutPanel1.Controls.Add(this.button_query);
            this.flowLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.flowLayoutPanel1.Location = new System.Drawing.Point(3, 3);
            this.flowLayoutPanel1.Name = "flowLayoutPanel1";
            this.flowLayoutPanel1.Size = new System.Drawing.Size(744, 151);
            this.flowLayoutPanel1.TabIndex = 1;
            // 
            // ucFilterCombo_TimeRage
            // 
            this.ucFilterCombo_TimeRage.Location = new System.Drawing.Point(3, 3);
            this.ucFilterCombo_TimeRage.Name = "ucFilterCombo_TimeRage";
            this.ucFilterCombo_TimeRage.ReadOnly = false;
            this.ucFilterCombo_TimeRage.Size = new System.Drawing.Size(305, 28);
            this.ucFilterCombo_TimeRage.TabIndex = 2;
            this.ucFilterCombo_TimeRage.Title = "属性:";
            // 
            // ucFilterCombo_Station
            // 
            this.ucFilterCombo_Station.Location = new System.Drawing.Point(314, 3);
            this.ucFilterCombo_Station.Name = "ucFilterCombo_Station";
            this.ucFilterCombo_Station.ReadOnly = false;
            this.ucFilterCombo_Station.Size = new System.Drawing.Size(305, 28);
            this.ucFilterCombo_Station.TabIndex = 3;
            this.ucFilterCombo_Station.Title = "属性:";
            // 
            // comboField1
            // 
            this.comboField1.Location = new System.Drawing.Point(3, 37);
            this.comboField1.Name = "comboField1";
            this.comboField1.ReadOnly = false;
            this.comboField1.Size = new System.Drawing.Size(305, 28);
            this.comboField1.TabIndex = 4;
            this.comboField1.Title = "属性:";
            // 
            // comboField2
            // 
            this.comboField2.Location = new System.Drawing.Point(314, 37);
            this.comboField2.Name = "comboField2";
            this.comboField2.ReadOnly = false;
            this.comboField2.Size = new System.Drawing.Size(305, 28);
            this.comboField2.TabIndex = 5;
            this.comboField2.Title = "属性:";
            // 
            // comboField3
            // 
            this.comboField3.Location = new System.Drawing.Point(3, 71);
            this.comboField3.Name = "comboField3";
            this.comboField3.ReadOnly = false;
            this.comboField3.Size = new System.Drawing.Size(305, 28);
            this.comboField3.TabIndex = 6;
            this.comboField3.Title = "属性:";
            // 
            // comboField4
            // 
            this.comboField4.Location = new System.Drawing.Point(314, 71);
            this.comboField4.Name = "comboField4";
            this.comboField4.ReadOnly = false;
            this.comboField4.Size = new System.Drawing.Size(305, 28);
            this.comboField4.TabIndex = 7;
            this.comboField4.Title = "属性:";
            // 
            // button_query
            // 
            this.button_query.Location = new System.Drawing.Point(625, 71);
            this.button_query.Name = "button_query";
            this.button_query.Size = new System.Drawing.Size(75, 23);
            this.button_query.TabIndex = 8;
            this.button_query.Text = "查询";
            this.button_query.UseVisualStyleBackColor = true;
            this.button_query.Click += new System.EventHandler(this.button_query_Click);
            // 
            // UCAmmeterUsage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.tableLayoutPanel1);
            this.Name = "UCAmmeterUsage";
            this.Size = new System.Drawing.Size(750, 509);
            this.tableLayoutPanel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.flowLayoutPanel1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1;
        private ComboField ucFilterCombo_TimeRage;
        private ComboField ucFilterCombo_Station;
        private ComboField comboField1;
        private ComboField comboField2;
        private ComboField comboField3;
        private ComboField comboField4;
        private System.Windows.Forms.Button button_query;
    }
}
