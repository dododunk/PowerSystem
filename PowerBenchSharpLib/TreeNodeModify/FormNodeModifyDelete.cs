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
    public partial class FormNodeModifyDelete : Form
    {
        public FormNodeModifyDelete()
        {
            InitializeComponent();
            this.comboField_phase.Visible = false;

        }

        private LevelBase _Info;

        Level5Module L5moduleinfo;
        Level4Trans L4transinfo;
        Level3Line L3linenode;
        Level2Bus L2busnode;
        Level1station L1stationnode;
        Level0Company L0companynode;

        DataOpeMode _ope;



        public DataOpeMode Ope
        {
            // get { return _ope; }
            set
            {
                _ope = value;
                if (_ope == DataOpeMode.Del)
                {
                    this.Text = "删除节点";
                    this.button_OK.Text = "删除";
                    this.editField1.Enabled = false;
                }
            }
        }
        public LevelBase Info
        {
            get { return _Info; }
            set
            {
                _Info = value;
                L5moduleinfo = _Info as Level5Module;

                if (L5moduleinfo != null)
                {
                    this.propertyGrid1.SelectedObject = L5moduleinfo as Level4Trans;
                    this.editField1.SetData("模块", L5moduleinfo.Module);
                    this.comboField_phase.Visible = true;
                    this.comboField_phase.SetData("相别", (int)L5moduleinfo.Phase, typeof(Tigera.T_Definition.P_AmmeterInfo.Phase));
                    return;
                }

                L4transinfo = _Info as Level4Trans;
                if (L4transinfo != null)
                {
                    this.propertyGrid1.SelectedObject = L4transinfo as Level3Line;
                    this.editField1.SetData("变压器", L4transinfo.Tranformer);
                    return;
                }
                L3linenode = _Info as Level3Line;
                if (L3linenode != null)
                {
                    this.propertyGrid1.SelectedObject = L3linenode as Level2Bus;
                    this.editField1.SetData("线", L3linenode.Line);
                    return;
                }
                L2busnode = _Info as Level2Bus;
                if (L2busnode != null)
                {
                    this.propertyGrid1.SelectedObject = L2busnode as Level1station;
                    this.editField1.SetData("段", L2busnode.Bus.ToString());
                    return;
                }

                L1stationnode = _Info as Level1station;
                if (L1stationnode != null)
                {
                    this.propertyGrid1.SelectedObject = L1stationnode as Level0Company;
                    this.editField1.SetData("站", L1stationnode.Station);
                    return;
                }
                L0companynode = _Info as Level0Company;
                if (L0companynode != null)
                {
                    this.editField1.SetData("局", L0companynode.Company);
                    return;

                }

            }
        }




        private void button_Cancel_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
            this.Close();
        }

        private void button_OK_Click(object sender, EventArgs e)
        {
            string sql = string.Empty;
            if (this.editField1.Changed || this._ope == DataOpeMode.Del || this.comboField_phase.Changed )
            {
                if (MessageBox.Show(null, "确定修改?\r\n(修改完数据请最好重新启动应用程序重新加载数据)", "warning", MessageBoxButtons.YesNo, MessageBoxIcon.Warning) == DialogResult.Yes)
                {                    
                    if (L0companynode != null)
                    {
                        var cur = L0companynode;
                        sql = string.Format("update AMMETERINFO set USER_COMPANY = '{0}' where user_company= '{1}'",
                            this.editField1.Result,
                            cur.Company);
                    }
                    if (L1stationnode != null)
                    {
                        var cur = L1stationnode;
                        sql = string.Format("update AMMETERINFO set USER_STATION = '{0}' where user_company= '{1}' and USER_STATION = '{2}'",
                            this.editField1.Result,
                            cur.Company, cur.Station);
                    }
                    if (L2busnode != null)
                    {
                        var cur = L2busnode;
                        sql = string.Format("update AMMETERINFO set USER_BUS = '{0}' where user_company= '{1}' and USER_STATION = '{2}' and USER_BUS = '{3}'",
                            this.editField1.Result,
                            cur.Company, cur.Station, cur.Bus);
                    }
                    if (L3linenode != null)
                    {
                        var cur = L3linenode;
                        sql = string.Format("update AMMETERINFO set USER_LINENAME = '{0}' where user_company= '{1}' and USER_STATION = '{2}' and USER_BUS='{3}' and USER_LINENAME='{4}'",
                            this.editField1.Result,
                            cur.Company, cur.Station, cur.Bus, cur.Line);
                    }
                    if (L4transinfo != null)
                    {
                        var cur = L4transinfo;
                        sql = string.Format("update AMMETERINFO set USER_TRANSFORMER = '{0}' where user_company= '{1}' and USER_STATION = '{2}' and USER_BUS='{3}' and USER_LINENAME = '{4}' and USER_TRANSFORMER = '{5}' ",
                            this.editField1.Result,
                            cur.Company, cur.Station, cur.Bus, cur.Line, cur.Tranformer);
                    }
                    if (L5moduleinfo != null)
                    {
                        var cur = L5moduleinfo;
                        sql = string.Format("update AMMETERINFO set USER_MODULE = '{0}', user_phase = {7} where user_company= '{1}' and USER_STATION = '{2}' and USER_BUS='{3}' and USER_LINENAME = '{4}' and USER_TRANSFORMER = '{5}'and USER_MODULE = '{6}' ",
                            this.editField1.Result,
                            cur.Company, cur.Station, cur.Bus, cur.Line, cur.Tranformer, cur.Module,this.comboField_phase.Result);
                    }

                    try
                    {
                        if (this._ope == DataOpeMode.Del)
                        {
                            sql = "delete from AMMETERINFO " + sql.Substring(sql.IndexOf("where"));
                        }
                        AmmeterDB.ExcuteSql(sql);
                        this.DialogResult = DialogResult.OK;
                        this.Close();
                    }
                    catch (System.Exception ex)
                    {
                        MessageBox.Show(ex.ToString(),"错误");
                    }

                    
                }
            }

            
        }
    }
}
