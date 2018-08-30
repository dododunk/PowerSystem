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
            exportapi.CLogger.OnMsg += CLogger_OnMsg;

        }

        void CLogger_OnMsg(object sender, exportapi.LogEventArgs e)
        {
            Console.WriteLine(e._data);
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
            Rebind();
        }
        void Rebind()
        {
         
            this.dataGridView1.DataSource = new BindingList<P_AmmeterInfo> (_datas);           
        }
        private List<P_AmmeterInfo> _datas;

        public List<P_AmmeterInfo> Datas
        {
            get { return _datas; }         
        }


        List<exportapi.InputParam> GetInputParams()
        {
            List<exportapi.InputParam> list = new List<exportapi.InputParam>();
            if (Datas == null)
                return null;
            foreach (var item in Datas)
            {
                exportapi.InputParam input = new exportapi.InputParam();
                input.un_module_addr = (uint)uint.Parse(item.USER_MODULE);
                
                input.uc_sub_meter_addr = (byte)item.USER_SUBAMMMAC;

                input.uc_phase_number = (byte) item.USER_PHASE;

                //input.uc_station_number = (byte)item.USER_BUS;
                //TODO
                input.uc_section = (byte)item.USER_BUS;

                input.uc_line_number = (byte)item.USER_LINE;
                
                
                input.uc_module_encode_flag =(byte) item.USER_CDMA;

                input.VirAddress =  item.USER_VIRTUALADDR;

                input.Channel =  item.USER_CHANNEL;
                input.Dec_CNL = item.USER_DEC_CNL;
                input.Key = item.ROWID;
                input.Dump();



                list.Add(input);
            }
            return list;

        }


        private void button_ReadAmm_Click(object sender, EventArgs e)
        {
            var form = new FormReadAmmSetting();
            if (form.ShowDialog() == DialogResult.OK)
            {
                var list = GetInputParams();

                exportapi.CRunTask task = new exportapi.CRunTask();
                task.Init();
                task.OnResult += new EventHandler<exportapi.ResultEventArgs>(task_OnResult);
                foreach (var cmd in form.Cmds)
                {
                    task.ReadAmmeters(list, cmd);
                }
            }
        }

        int GetRowIndex(int rowid)
        {
            int i=0;
            foreach (var item in this.Datas)
            {
                if (item.ROWID == rowid)
                {
                    return i;
                }
                i++;
            }
            return -1;
        }
            
        void task_OnResult(object sender, exportapi.ResultEventArgs e)
        {
            var row = GetRowIndex(e.Key);
            var x = this._datas[row];
            x.CHECK_VALUE = e.Result;
            x.CHECK_TIME = DateTime.Now;
            this.Datas[row] = x;
            Rebind();


            //this.dataGridView1[row, 1].Value = e.Result.ToString();
            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Test();
        }
        void Test()
        {
            var x = _datas[3];
            x.CHECK_VALUE = 1112.3;
            x.CHECK_TIME = DateTime.Now;
            _datas[3] = x;
            Rebind();
            
            //this.dataGridView1[1, 2].Value = 112.3;
            //this.dataGridView1[1, 3].Value = 112.3;
        }

    }
}
