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
            this.Text = "修改数据";
            this.button_OK.Text = "修改";
            this.button_OK.Click +=button_OK_Click;
        }


        string CreateUpdateSql()
        {
            string sql = string.Format(
@"update  AMMETERINFO set 
 USER_COMPANY ='{0}', 
USER_STATION ='{1}',
USER_NO = '{2}',
USER_BUS ='{3}',
USER_LINENAME ='{4}', 
USER_LINE ='{5}',
USER_TRANSFORMER ='{6}', 
USER_NAME ='{7}',
USER_VIRTUALADDR ={8},
USER_MODULE ={9},
USER_KIND={10},
USER_A1='{11}', 
USER_A2='{12}',
USER_CDMA ={13},
USER_SUBAMM = {14},
USER_SUBAMMMAC = {15},
USER_CHANNEL = {16},
USER_PHASE = {17},
USER_DEC_CNL = {18}
"
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
this.comboField1_CDMA.Result,
this.comboField_SUBAMM.Result,
this.editField_SUBAMMMAC.Result,
this.comboFieldChannel.Result,
this.comboField_Phase.Result,
this.comboField_DecCnl.Result
);


            string sqlfilter = string.Format(@" where rowid ={0}",this.CurrentData.ROWID);
            var cmd = sql + sqlfilter;
            cmd = cmd.Replace(Environment.NewLine, " ");
            
            return cmd;
        }



        private void button_OK_Click(object sender, EventArgs e)
        {
            try
            {
                var cmd = CreateUpdateSql();
                Debug.Write(cmd);
                AmmeterDB.ExcuteSql(cmd);
                MessageBox.Show("修改成功");
                //
                if (this.chkKeepWWindow.Checked != true)
                {
                    this.DialogResult = System.Windows.Forms.DialogResult.OK;
                    this.Close();
                }
                
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }
    }
}
