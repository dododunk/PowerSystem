using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace PowerBenchSharpLib
{
    public partial class UCControlHold : UserControl
    {
        public UCControlHold(Type controlType)
        {
            InitializeComponent();
            if (controlType != null)
            {
                _control = Activator.CreateInstance(controlType) as Control;
                _control.Name = controlType.Name;
                _control.Dock = DockStyle.Fill;
                this.Controls.Add(_control);
                

                this.SizeChanged += UCControlHold_SizeChanged;
            }
        }
        Control _control;

        public Control Hold
        {
            get { return _control; }
           // set { _control = value; }
        }


        void UCControlHold_SizeChanged(object sender, EventArgs e)
        {

            //throw new NotImplementedException();
        }
    }
}
