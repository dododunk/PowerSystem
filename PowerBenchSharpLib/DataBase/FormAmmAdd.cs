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
            InitializeComponent();
            this.Text = "添加数据";
            //this.button_OK.Text = "添加";
        }


        protected string CreateInsertSql()
        {
            string sql = string.Format(

@"INSERT INTO AMMETERINFO ( 
 USER_COMPANY, 
USER_STATIONNAME,
USER_STATIONNO,
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

USER_CDMA ) 
VALUES (
'{0}', '{1}','{2}','{3}','{4}','{5}','{6}','{7}','{8}','{9}',{10},'{11}','{12}',{13})
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
 this.comboField1_CDMA.Result
 
 
 
 );
            sql = sql.Replace("\r\n", " ");
            return sql;
        }

        

        private void button_OK_Click(object sender, EventArgs e)
        {
            var cmd = CreateInsertSql();
            try
            {

                Debug.Write(cmd);
                AmmeterDB.ExcuteSql(cmd);
                this.DialogResult = DialogResult.OK;
                MessageBox.Show("添加成功");
                
               // this.Close();
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

    }
}
