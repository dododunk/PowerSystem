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
    public partial class FormAmmAdd : FormOpeAmmBase
    {
        public FormAmmAdd()
        {
            this.Text = "添加数据";
            this.button_OK.Text = "添加";
            this.button_OK.Click += new System.EventHandler(this.button_OK_Click);

            //this.editField_Company.Input.AutoCompleteSource
        }


        protected string CreateInsertSql()
        {
            string sql = string.Format(

@"INSERT INTO AMMETERINFO ( 
 USER_COMPANY, 
USER_STATION,
USER_NO,
USER_BUS,
USER_LINENAME, 
USER_LINE,
USER_TRANSFORMER,
USER_NAME,
USER_VIRTUALADDR,
USER_MODULE,
USER_KIND,
USER_A1, 
USER_A2,
USER_CDMA ,
USER_SUBAMM,
USER_SUBAMMMAC,
USER_CHANNEL,
USER_PHASE) 
VALUES (
'{0}', '{1}','{2}','{3}','{4}','{5}','{6}','{7}',{8},{9},{10},'{11}','{12}',{13},{14},{15},{16}, {17})
",
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
 this.comboField_Phase.Result
 );
            sql = sql.Replace(Environment.NewLine, " ");
            return sql;
        }



        private void button_OK_Click(object sender, EventArgs e)
        {
            try
            {
                var cmd = CreateInsertSql();
                ForwardLogger.Log("run sql:" + cmd);
                Debug.Write(cmd);
                AmmeterDB.ExcuteSql(cmd);
                //this.DialogResult = DialogResult.OK;
                MessageBox.Show("添加成功");
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
