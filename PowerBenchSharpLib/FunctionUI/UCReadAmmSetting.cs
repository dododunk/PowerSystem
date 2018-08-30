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
    public partial class UCReadAmmSetting : UserControl
    {
        public UCReadAmmSetting()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            FormReCallData form = new FormReCallData();
            if (form.ShowDialog() == DialogResult.OK)
            {

           }
        }
    }
}
