using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Tigera.T_Definition;

namespace PowerBenchSharpLib
{
    public partial class FormOpeAmmBase : Form
    {

        public FormOpeAmmBase()
        {
            InitializeComponent();
            ShowInfo();
            
        }
        protected void ShowInfo()
        {
            this.editField_Company.SetData("公司", _info.USER_COMPANY,16);
            this.editField_Station.SetData("站", _info.USER_STATION,16);

            this.comboField_Bus.SetData("段", _info.USER_BUS, new List<int> { 1,2});
            this.editField_Transformer.SetData("变压器", _info.USER_TRANSFORMER);
            this.comboField_Line.SetData("线编号", _info.USER_LINE,new List<int>{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15});
            this.editField_LineNO.SetData("线名称", _info.USER_LINENAME.ToString(),16);            
            this.editField_UserNO.SetData("用户编号", _info.USER_NO,16);            
            this.editField_UserName.SetData("用户名称", _info.USER_NAME,16);
            this.editField_Module.SetData("模块", _info.USER_MODULE);
            this.editField_VirtualAddr.SetData("虚拟地址", _info.USER_VIRTUALADDR);
            
            this.editField1_A1.SetData("A1", _info.USER_A1);
            this.editField1_A2.SetData("A2", _info.USER_A2);
            this.comboField1_CDMA.SetData("CDMA", (int)_info.USER_CDMA, typeof(P_AmmeterInfo.CDMA_TYPE));
            this.comboField_UserKind.SetData("用户类别", (int)_info.USER_KIND, typeof(P_AmmeterInfo.USER_KINDTYPE));
        }
        protected P_AmmeterInfo _info = new P_AmmeterInfo();

        public P_AmmeterInfo CurrentData
        {
            get
            {
                return _info;
            }
            set
            {
                _info = value;
                ShowInfo();
            }
        }


       

        protected void button_Cancel_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
            this.Close();
        }

       


       

        

    }
}
