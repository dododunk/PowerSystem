namespace PowerBenchSharpLib.Test
{
    partial class Form1
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.button1 = new System.Windows.Forms.Button();
            this.propertyGrid1 = new System.Windows.Forms.PropertyGrid();
            this.button2 = new System.Windows.Forms.Button();
            this.ammeterInfoControl1 = new PowerBenchSharpLib.AmmeterInfoControl();
            this.ucAmmetersOpe1 = new PowerBenchSharpLib.UCAmmetersOpe();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(388, 519);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(97, 36);
            this.button1.TabIndex = 0;
            this.button1.Text = "button1";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // propertyGrid1
            // 
            this.propertyGrid1.Location = new System.Drawing.Point(2, 334);
            this.propertyGrid1.Name = "propertyGrid1";
            this.propertyGrid1.Size = new System.Drawing.Size(284, 230);
            this.propertyGrid1.TabIndex = 2;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(633, 528);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(83, 36);
            this.button2.TabIndex = 4;
            this.button2.Text = "button2";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.Button2Click);
            // 
            // ammeterInfoControl1
            // 
            this.ammeterInfoControl1.Location = new System.Drawing.Point(2, 12);
            this.ammeterInfoControl1.Name = "ammeterInfoControl1";
            this.ammeterInfoControl1.Size = new System.Drawing.Size(284, 316);
            this.ammeterInfoControl1.TabIndex = 3;
            // 
            // ucAmmetersOpe1
            // 
            this.ucAmmetersOpe1.Location = new System.Drawing.Point(292, 12);
            this.ucAmmetersOpe1.Name = "ucAmmetersOpe1";
            this.ucAmmetersOpe1.Size = new System.Drawing.Size(713, 385);
            this.ucAmmetersOpe1.TabIndex = 5;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(882, 567);
            this.Controls.Add(this.ucAmmetersOpe1);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.ammeterInfoControl1);
            this.Controls.Add(this.propertyGrid1);
            this.Controls.Add(this.button1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);

        }
        private System.Windows.Forms.Button button2;

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.PropertyGrid propertyGrid1;
        private AmmeterInfoControl ammeterInfoControl1;
        private UCAmmetersOpe ucAmmetersOpe1;
    }
}

