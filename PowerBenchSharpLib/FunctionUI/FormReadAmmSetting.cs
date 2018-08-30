using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using exportapi;

namespace PowerBenchSharpLib
{
    public partial class FormReadAmmSetting : Form
    {
        public FormReadAmmSetting()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            FormReCallData form = new FormReCallData();
            if (form.ShowDialog() == DialogResult.OK)
            {

           }
        }


        CMD MakeCMD(CMD_TYPE id)
        {
            CMD cmd = new CMD();
            cmd.CMDID = rdb_ShiShi.Checked ? id : id + 0x80;
            //TODO
            cmd.DataMode = 1;

            cmd.Readtype = rdb_Single.Checked ? ReadType.Single :
                (rdb_Sync.Checked ? ReadType.Sync : ReadType.Seq);

            cmd.AddressMode = rdb_ShiDiZhi.Checked ? ADDRESSMODE.ReadlAddress : ADDRESSMODE.VirtualAdress;

            cmd.NeedReadNoRepied = checkBox15.Checked;

            


            return cmd;
        }
        private void btn_OK_Click(object sender, EventArgs e)
        {
           
            //有供电度
           if (chk_YouGongDianDu.Checked)
           {             
               _cmds.Add(MakeCMD(CMD_TYPE.S_YOUGONGDIANDU));
           }
            //无功电度
           if (chk_WuGongDianDu.Checked)
           {
               _cmds.Add(MakeCMD(CMD_TYPE.S_WUGONGDIANDU));              
           }
            //见点亮
           if (chk_JianDianLiang.Checked)
           {
               _cmds.Add(MakeCMD(CMD_TYPE.S_JIANDIANLIANG));
           }
            //风电两
           if (chk_FengDianLiang.Checked)
           {
               _cmds.Add(MakeCMD(CMD_TYPE.S_FENGDIANLIANG));
           }
            //古典两
           if (chk_GuDianLiang.Checked)
           {
               _cmds.Add(MakeCMD(CMD_TYPE.S_GUDIANLIANG));
           }
            //品点亮
           if (chk_PingDianLiang.Checked)
           {
               _cmds.Add(MakeCMD(CMD_TYPE.S_PINGDIANLIANG));
           }

           this.DialogResult = DialogResult.OK;
           this.Close();

        }

        List<CMD> _cmds = new List<CMD>();

        public List<CMD> Cmds
        {
            get { return _cmds; }
            
        }
    }
   
}
