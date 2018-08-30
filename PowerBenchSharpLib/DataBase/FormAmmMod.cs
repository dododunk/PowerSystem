using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;

namespace PowerBenchSharpLib
{
    public partial class FormAmmMod : FormOpeAmmBase
    {
        public FormAmmMod()
        {
            InitializeComponent();
            this.Text = "修改数据";
            //this.button_OK.Text = "修改";
        }


        string CreateUpdateSql()
        {

            string sql = string.Format(
@"update  AMMETERINFO set 
 USER_COMPANY ='{0}', 
USER_STATIONNAME ='{1}',
USER_STATIONNO ='{2}',
USER_BUS ='{3}',
USER_LINENAME ='{4}', 
USER_LINE ='{5}',
USER_TRANSFORMER ='{6}', 
USER_NAME ='{7}',
USER_VIRTUALADDR ='{8}',
USER_MODULE ='{9}',
USER_KIND={10},
USER_A1='{11}', 
USER_A2='{12}',
USER_CDMA ={13}"

,
this.editField_Company.Result,
this.editField_Station.Result,
this.editField_UserNO.Result,
this.comboField_Bus.Result,
this.comboField_Line.Result,
this.editField_LineNO.Result,
this.editField_Transformer.Result,
this.editField_UserName.Result,
this.editField_VirtualAddr.Result,
this.editField_Module.Result,
this.comboField_UserKind.Result,
this.editField1_A1.Result,
this.editField1_A2.Result,
this.comboField1_CDMA.Result



);


            string sqlfilter = string.Format(@"
            where
USER_COMPANY ='{0}'  and  
USER_STATION ='{1}'  and 
USER_BUS ='{2}'  and 
USER_LINENAME ='{3}'  and  
USER_LINE ='{4}'  and
USER_TRANSFORMER ='{5}'  and
USER_NAME ='{6}'  and
USER_VIRTUALADDR ='{7}'  and
USER_MODULE ='{8}'  and 
USER_KIND={9} and
USER_A1='{10}'  and
USER_A2='{11}'  and
USER_CDMA ={12}
",
                          _info.USER_COMPANY,
                          _info.USER_STATION,
                          
                          _info.USER_BUS,
                          _info.USER_LINENAME,
                          _info.USER_LINE,
                          _info.USER_TRANSFORMER,
                          _info.USER_NAME,
                          _info.USER_VIRTUALADDR,
                          _info.USER_MODULE,
                         (int)_info.USER_KIND,
                          _info.USER_A1,
                          _info.USER_A2,
                          (int)_info.USER_CDMA);


            var cmd = sql + sqlfilter;
            cmd = cmd.Replace("\r\n", " ");
            Debug.Write(cmd);
            return cmd;
        }



        private void button_OK_Click(object sender, EventArgs e)
        {
            try
            {
                var cmd = CreateUpdateSql();
                AmmeterDB.ExcuteSql(cmd);
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }

        }
    }
}
