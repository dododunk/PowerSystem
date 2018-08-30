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
    public partial class UCAmmetersOpe : UserControl
    {
        public UCAmmetersOpe()
        {
            InitializeComponent();
            SetupDataGridView();

        }
        private void SetupDataGridView()
        {
            this.dataGridView1.Columns.Add("公司", "公司");
            this.dataGridView1.Columns.Add("公司编号", "公司编号");
            this.dataGridView1.Columns.Add("站名","站名");
            this.dataGridView1.Columns.Add("线", "线");
            this.dataGridView1.Columns.Add("变压器", "变压器");
        }

        private void button_SendAmmDatas_Click(object sender, EventArgs e)
        {
            if (ONbutton_SendAmmDatasClick != null)
            {
                ONbutton_SendAmmDatasClick(this, EventArgs.Empty);
            }
        }
        public event EventHandler ONbutton_SendAmmDatasClick;
        public void LoadData(List<P_AmmeterInfo> datas)
        {
            _datas = datas;
            foreach(var item in _datas)
            {
                string[] therow = new string[]{item.USER_COMPANY,item.USER_STATION,item.USER_LINENAME,item.USER_TRANSFORMER};
                this.dataGridView1.Rows.Add(therow);
            }
            
        }
        private List<P_AmmeterInfo> _datas;

        public List<P_AmmeterInfo> Datas
        {
            get { return _datas; }
         
        }

        public void OnSelected(object sender, SelectItemEventArgs args)
        {
            var items = args.Datas;
            foreach(var item in items)
            {
                this.dataGridView1.Rows.Add("");
            }
        }

        private void button_ReadAmm_Click(object sender, EventArgs e)
        {
            FormContainer<UCReadAmmSetting> form = new FormContainer<UCReadAmmSetting>();
            if (form.ShowDialog() == DialogResult.OK)
            {

            }
        }

    }
}
