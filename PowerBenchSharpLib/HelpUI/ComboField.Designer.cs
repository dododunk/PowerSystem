namespace PowerBenchSharpLib
{
    partial class ComboField
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
            this.flowLayoutPanel1 = new System.Windows.Forms.FlowLayoutPanel();
            this.label_Property = new System.Windows.Forms.Label();
            this.combBox1 = new System.Windows.Forms.ComboBox();
            this.label_ChangedNotify = new System.Windows.Forms.Label();
            this.flowLayoutPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // flowLayoutPanel1
            // 
            this.flowLayoutPanel1.Controls.Add(this.label_Property);
            this.flowLayoutPanel1.Controls.Add(this.combBox1);
            this.flowLayoutPanel1.Controls.Add(this.label_ChangedNotify);
            this.flowLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.flowLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.flowLayoutPanel1.Name = "flowLayoutPanel1";
            this.flowLayoutPanel1.Size = new System.Drawing.Size(298, 28);
            this.flowLayoutPanel1.TabIndex = 3;
            // 
            // label_Property
            // 
            this.label_Property.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.label_Property.Location = new System.Drawing.Point(3, 0);
            this.label_Property.Name = "label_Property";
            this.label_Property.Size = new System.Drawing.Size(72, 28);
            this.label_Property.TabIndex = 6;
            this.label_Property.Text = "属          性:";
            this.label_Property.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // combBox1
            // 
            this.combBox1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.combBox1.Location = new System.Drawing.Point(81, 3);
            this.combBox1.Name = "combBox1";
            this.combBox1.Size = new System.Drawing.Size(193, 21);
            this.combBox1.TabIndex = 4;
            // 
            // label_ChangedNotify
            // 
            this.label_ChangedNotify.AutoSize = true;
            this.label_ChangedNotify.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label_ChangedNotify.ForeColor = System.Drawing.Color.Red;
            this.label_ChangedNotify.Location = new System.Drawing.Point(280, 0);
            this.label_ChangedNotify.Name = "label_ChangedNotify";
            this.label_ChangedNotify.Size = new System.Drawing.Size(0, 28);
            this.label_ChangedNotify.TabIndex = 3;
            this.label_ChangedNotify.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // ComboField
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.flowLayoutPanel1);
            this.Name = "ComboField";
            this.Size = new System.Drawing.Size(298, 28);
            this.flowLayoutPanel1.ResumeLayout(false);
            this.flowLayoutPanel1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1;
        private System.Windows.Forms.ComboBox combBox1;
        private System.Windows.Forms.Label label_Property;
        private System.Windows.Forms.Label label_ChangedNotify;

    }
}
