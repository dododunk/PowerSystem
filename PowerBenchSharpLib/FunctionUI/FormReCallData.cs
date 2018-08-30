using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace PowerBenchSharpLib
{
    public partial class FormReCallData : Form
    {
        public FormReCallData()
        {
            InitializeComponent();
            List<int> data = new List<int>();
            for(int i=0; i<100; ++i)
                data.Add(i);

            this.domainUpDown2.Items.AddRange(data);
        }

        private void btn_Cancel_Click(object sender, EventArgs e)
        {
            this.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.Close();
        }

        private void btn_OK_Click(object sender, EventArgs e)
        {
            this.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.Close();
        }
        public int Round
        {
            get
            {
                return Int32.Parse(this.domainUpDown1.Text);
            }
        }
        public int TimeInterVal
        {
            get
            {
                return Int32.Parse(this.domainUpDown2.Text);
            }
        }
    }
}
