using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Tigera.T_Definition;

namespace PowerBenchSharpLib
{
    public partial class AmmeterInfoControl : UserControl
    {
        public AmmeterInfoControl()
        {
            InitializeComponent();

            this.toolStripButton_LoadData.Click += toolStripLoadData;
            this.toolStripButtonAddItem.Click += toolStripMenuItem_AddData_Click;
            this.toolStripButton_Select.Click += toolStripMenuItem_SelectDatas_Ope;
            /*
            this.autoToolStrip1.AddMenuItem("加载数据", toolStripLoadData);
            this.autoToolStrip1.AddMenuItem("添加数据", toolStripMenuItem_AddData_Click);
            this.autoToolStrip1.AddMenuItem("选择操作", toolStripMenuItem_SelectDatas_Ope);
             * */
        }

        void toolStripLoadData(object sender, EventArgs e)
        {
            this.autoToolStrip1.Enabled = false;
            try
            {
                var results = AmmeterDB.LoadAmmInfoFromDatabase();
                treeView_Ammeter.ClearData();
                this.treeView_Ammeter.AddData(results);
                this.treeView_Ammeter.BuildTree();
            }
           
            finally
            {
                this.autoToolStrip1.Enabled = true;
            }
        }

        

        public AmmeterTree Tree
        {
            get
            {
                return this.treeView_Ammeter;
            }
        }


        
        

      

        private void toolStripMenuItem_AddData_Click(object sender, EventArgs e)
        {
            FormAmmAdd form = new FormAmmAdd();
            if (form.ShowDialog(this) == DialogResult.OK)
            {
                toolStripLoadData(this, EventArgs.Empty);
            }
            
        }

        public event EventHandler<SelectItemEventArgs> OnSelect;
        private void toolStripMenuItem_SelectDatas_Ope(object sender, EventArgs e)
        {
            var result = this.treeView_Ammeter.GetSelected();
            if (result.Count != 0)
            {
                if (OnSelect != null)
                {
                    OnSelect(this, new SelectItemEventArgs(result));
                }
            }      

        }

        

    }

    public class SelectItemEventArgs : EventArgs
    {
        List<P_AmmeterInfo> _datas;

        public List<P_AmmeterInfo> Datas
        {
            get { return _datas; }
        }
        public SelectItemEventArgs(List<P_AmmeterInfo> items)
        {
            _datas = items;
        }

    }
}
