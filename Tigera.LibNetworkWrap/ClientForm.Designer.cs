namespace Tigera.LibNetworkWrap
{
    partial class ClientForm
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
            this.messageHost1 = new Tigera.LibNetworkWrap.UCMessageHost();
            this.SuspendLayout();
            // 
            // messageHost1
            // 
            this.messageHost1.ClientMode = false;
            this.messageHost1.Location = new System.Drawing.Point(31, 38);

            this.messageHost1.Name = "messageHost1";
            this.messageHost1.Size = new System.Drawing.Size(522, 309);
            this.messageHost1.TabIndex = 0;
            // 
            // ClientForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(604, 377);
            this.Controls.Add(this.messageHost1);
            this.Name = "ClientForm";
            this.Text = "ClientForm";
            this.ResumeLayout(false);

        }

        #endregion

        private UCMessageHost messageHost1;
    }
}