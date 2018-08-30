using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;

namespace GB698Ctl.GB698Ctl
{
    public partial class UCNetStart : UserControl
    {
        public UCNetStart()
        {
            InitializeComponent();
        }

        private void button_start_Click(object sender, EventArgs e)
        {
            var data = this.textBox1.Text.Trim();
            try
            {
                Program.gPort = int.Parse(this.textBox1.Text);
            }
            catch (System.Exception ex)
            {
                return;
            }

            new Thread(new ParameterizedThreadStart(Program.StartTcpNet)).Start(Program.gPort);
            this.label2.Text = "启动监听线程";
            
        }

      
    }
}
