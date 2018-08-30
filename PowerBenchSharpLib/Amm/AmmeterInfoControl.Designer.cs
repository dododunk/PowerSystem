namespace PowerBenchSharpLib
{
    partial class AmmeterInfoControl
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(AmmeterInfoControl));
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.treeView_Ammeter = new PowerBenchSharpLib.AmmeterTree();
            this.autoToolStrip1 = new PowerBenchSharpLib.AutoToolStrip();
            this.toolStripButton_LoadData = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButtonAddItem = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton_Select = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
            this.tableLayoutPanel1.SuspendLayout();
            this.autoToolStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Controls.Add(this.treeView_Ammeter, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.autoToolStrip1, 0, 1);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 40F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(289, 315);
            this.tableLayoutPanel1.TabIndex = 3;
            // 
            // treeView_Ammeter
            // 
            this.treeView_Ammeter.CheckBoxes = true;
            this.treeView_Ammeter.Dock = System.Windows.Forms.DockStyle.Fill;
            this.treeView_Ammeter.ImageIndex = 0;
            this.treeView_Ammeter.Location = new System.Drawing.Point(3, 3);
            this.treeView_Ammeter.Name = "treeView_Ammeter";
            this.treeView_Ammeter.SelectedImageIndex = 0;
            this.treeView_Ammeter.ShowNodeToolTips = true;
            this.treeView_Ammeter.Size = new System.Drawing.Size(283, 269);
            this.treeView_Ammeter.TabIndex = 3;
            // 
            // autoToolStrip1
            // 
            this.autoToolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton_LoadData,
            this.toolStripSeparator2,
            this.toolStripSeparator1,
            this.toolStripButtonAddItem,
            this.toolStripSeparator3,
            this.toolStripSeparator4,
            this.toolStripButton_Select});
            this.autoToolStrip1.Location = new System.Drawing.Point(0, 275);
            this.autoToolStrip1.Name = "autoToolStrip1";
            this.autoToolStrip1.Size = new System.Drawing.Size(289, 25);
            this.autoToolStrip1.TabIndex = 4;
            this.autoToolStrip1.Text = "autoToolStrip1";
            // 
            // toolStripButton_LoadData
            // 
            this.toolStripButton_LoadData.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.toolStripButton_LoadData.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton_LoadData.Image")));
            this.toolStripButton_LoadData.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton_LoadData.Name = "toolStripButton_LoadData";
            this.toolStripButton_LoadData.Size = new System.Drawing.Size(59, 22);
            this.toolStripButton_LoadData.Text = "加载数据";
            this.toolStripButton_LoadData.ToolTipText = "从数据库加载数据";
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButtonAddItem
            // 
            this.toolStripButtonAddItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.toolStripButtonAddItem.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButtonAddItem.Image")));
            this.toolStripButtonAddItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButtonAddItem.Name = "toolStripButtonAddItem";
            this.toolStripButtonAddItem.Size = new System.Drawing.Size(59, 22);
            this.toolStripButtonAddItem.Text = "添加电表";
            this.toolStripButtonAddItem.ToolTipText = "新增电表信息";
            // 
            // toolStripButton_Select
            // 
            this.toolStripButton_Select.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.toolStripButton_Select.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton_Select.Image")));
            this.toolStripButton_Select.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton_Select.Name = "toolStripButton_Select";
            this.toolStripButton_Select.Size = new System.Drawing.Size(59, 22);
            this.toolStripButton_Select.Text = "选择操作";
            this.toolStripButton_Select.ToolTipText = "对勾选的电表进行批量操作";
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripSeparator4
            // 
            this.toolStripSeparator4.Name = "toolStripSeparator4";
            this.toolStripSeparator4.Size = new System.Drawing.Size(6, 25);
            // 
            // AmmeterInfoControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.tableLayoutPanel1);
            this.Name = "AmmeterInfoControl";
            this.Size = new System.Drawing.Size(289, 315);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.autoToolStrip1.ResumeLayout(false);
            this.autoToolStrip1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private AmmeterTree treeView_Ammeter;
        private AutoToolStrip autoToolStrip1;
        private System.Windows.Forms.ToolStripButton toolStripButton_LoadData;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripButton toolStripButtonAddItem;
        private System.Windows.Forms.ToolStripButton toolStripButton_Select;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;

    }
}
