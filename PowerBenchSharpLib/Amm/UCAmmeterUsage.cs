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
    public partial class UCAmmeterUsage : UserControl
    {
        public UCAmmeterUsage()
        {
            InitializeComponent();

            InitUI();
            
            //
        }
        private BindingSource bindingSource1 = new BindingSource();

        private void InitUI()
        {
            this.ucFilterCombo_TimeRage.Title = "时间段";
            //this.ucFilterCombo_TimeRage.Items = new List<ShowItem>() { new ShowItem("所有", "所有") };


            this.ucFilterCombo_Station.Title = "局";
        }

        private void RunQuery(string filter)
        {       
            
            var usages = AmmeterDB.LoadAmmeterUsage( filter);
            this.dataGridView1.AutoGenerateColumns = true;
            //this.dataGridView1.
            bindingSource1.DataSource = (usages as DataSet).Tables[0];
            
            this.dataGridView1.DataSource = bindingSource1;
            
        }

        private void button_query_Click(object sender, EventArgs e)
        {
            RunQuery(string.Empty);
        }

    }
}
