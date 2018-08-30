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
    public partial class FormOuterSetting : Form
    {
        public FormOuterSetting()
        {
            InitializeComponent();
            var datas = new List<string>();
            for(int i=1; i<=40; i++)
            {
                datas.Add(i.ToString());
            }
            this.domainUpDown2.Items.AddRange(datas);
            this.domainUpDown3.Items.AddRange(datas);
            this.domainUpDown4.Items.AddRange(datas);

            this.domainUpDown1.SelectedIndex = 0;
            this.domainUpDown2.SelectedIndex = 9;
            this.domainUpDown3.SelectedIndex = 9;
            this.domainUpDown4.SelectedIndex = 9;
        }

        private void button1_Click(object sender, EventArgs e)
        {

        }

        private void button7_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button4_Click(object sender, EventArgs e)
        {

        }

        private void button6_Click(object sender, EventArgs e)
        {

        }

        private void button_ReadA_Click(object sender, EventArgs e)
        {

        }
    }
}
