using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace PowerBenchSharpLib
{
    
    public partial class FormContainer<T> : Form where T :Control ,new ()
    {
        public FormContainer()
        {
            InitializeComponent();
            _hold = new T();
            _hold.Parent = this;
            this.ClientSize = _hold.Size;

            _hold.Dock = System.Windows.Forms.DockStyle.Fill;
            _hold.Location = new System.Drawing.Point(0, 0);
            _hold.Name = "netStartUserControl1";
            //_hold.Size = new System.Drawing.Size(347, 327);
            _hold.TabIndex = 0;
            
            //this.Size = this.ClientSize;
            this.Controls.Add(_hold);
            this.Name = "FormContainer" +  (string.IsNullOrEmpty(_hold.Name)? _hold.GetType().ToString() : _hold.Name );
            this.Text = (string.IsNullOrEmpty(_hold.Text) ? _hold.GetType().ToString() : _hold.Text);

        }
        private T _hold;
        public T Hold
        {
            get
            {
                return _hold;
            }
        }

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
            this.components = new System.ComponentModel.Container();
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Text = "FormContainer";
        }

        #endregion
    }

}
