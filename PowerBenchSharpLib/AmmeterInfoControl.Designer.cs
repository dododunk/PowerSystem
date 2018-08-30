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
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.treeView_Ammeter = new PowerBenchSharpLib.AmmeterTree();
            this.autoToolStrip1 = new PowerBenchSharpLib.AutoToolStrip();
            this.tableLayoutPanel1.SuspendLayout();
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
            this.autoToolStrip1.Location = new System.Drawing.Point(0, 275);
            this.autoToolStrip1.Name = "autoToolStrip1";
            this.autoToolStrip1.Size = new System.Drawing.Size(289, 25);
            this.autoToolStrip1.TabIndex = 4;
            this.autoToolStrip1.Text = "autoToolStrip1";
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
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private AmmeterTree treeView_Ammeter;
        private AutoToolStrip autoToolStrip1;

    }
}
