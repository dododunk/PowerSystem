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
    public partial class FormAmmDel : FormOpeAmmBase
    {
        public FormAmmDel()
        {           
            foreach (var item in this.Controls[0].Controls[0].Controls)
            {
                if (item is ComboField || item is EditField)
                    (item as Control).Enabled = false;
            }
            this.Text = "删除数据";
            this.button_OK.Text = "删除";
            this.button_OK.Click += button_OK_Click;
        }

        void button_OK_Click(object sender, EventArgs e)
        {

            try
            {
                string sql = string.Format("DELETE from AMMETERINFO where RowID = {0}", this.CurrentData.ROWID);
                AmmeterDB.ExcuteSql(sql);
                this.DialogResult = System.Windows.Forms.DialogResult.OK;
                this.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }
    }
}
