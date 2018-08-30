using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace GB698Cls
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
        public Control Hold
        {
            get
            {
                return _hold;
            }
        }
    }
}
