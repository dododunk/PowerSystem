namespace PowerBenchSharpLib
{
    partial class FormAmmMod
    {
       
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
            this.button_OK = new System.Windows.Forms.Button();
            this.SuspendLayout();
           
            // 
            // button_OK
            // 
            this.button_OK.Location = new System.Drawing.Point(389, 30);
            this.button_OK.Name = "button_OK";
            this.button_OK.Size = new System.Drawing.Size(75, 23);
            this.button_OK.TabIndex = 3;
            this.button_OK.Text = "修改";
            this.button_OK.UseVisualStyleBackColor = true;
            this.button_OK.Click += new System.EventHandler(this.button_OK_Click);

            this.panel1.Controls.Add(this.button_OK);
            // 
            // FormAmmMod
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(640, 483);
            this.Location = new System.Drawing.Point(0, 0);
            this.Name = "FormAmmMod";
            this.Text = "FormModiAmm";
            this.ResumeLayout(false);

        }

        #endregion

        protected System.Windows.Forms.Button button1;
        protected System.Windows.Forms.Button button_OK;
    }
}