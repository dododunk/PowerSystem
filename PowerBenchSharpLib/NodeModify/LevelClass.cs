using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Tigera.T_Definition;
using System.Data.SqlClient;
using System.Data.OleDb;
using System.Data.Common;
using System.IO;
using System.Windows.Forms;
using System.ComponentModel;

namespace PowerBenchSharpLib
{
    public class LevelBase
    {
        protected IGrouping<string, P_AmmeterInfo> _group;
        protected LevelBase(IGrouping<string, P_AmmeterInfo> group)
        {
            _group = group;
        }

        public IGrouping<string, P_AmmeterInfo> Group
        {
            get
            {

                return _group;
            }


        }
        [DisplayNameAttribute("子项个数")]
        public int Count
        {
            get
            {
                return _group.Count();
            }
        }
        [DisplayNameAttribute("名称")]
        public string Name
        {
            get
            {
                return _group.Key;
            }
        }
    }
    public class Level0Company : LevelBase
    {
        public Level0Company(IGrouping<string, P_AmmeterInfo> group)
            : base(group)
        {


        }
        [DisplayName("局")]
        public string Company
        {
            get
            {
                return _group.First().USER_COMPANY;
            }
         }

    }

    public class Level1station : Level0Company
    {
        public Level1station(IGrouping<string, P_AmmeterInfo> group)
            : base(group)
        {


        }
        [DisplayName("站")]
        public string Station
        {
            get
            {
                return _group.First().USER_STATION;
            }
        }


    }
    public class Level2Bus : Level1station
    {
        public Level2Bus(IGrouping<string, P_AmmeterInfo> group)
            : base(group)
        {


        }
        [DisplayName("段")]
        public int Bus
        {
            get
            {
                return _group.First().USER_BUS;
            }

        }

    }

    public class Level3Line : Level2Bus
    {
        public Level3Line(IGrouping<string, P_AmmeterInfo> group)
            : base(group)
        {


        }
        [DisplayName("线")]
        public string Line
        {
            get
            {
                return _group.First().USER_LINENAME;
            }
        }

    }
    public class Level4Trans : Level3Line
    {
        public Level4Trans(IGrouping<string, P_AmmeterInfo> group)
            : base(group)
        {
        }
        [DisplayName("变压器")]
        public string Tranformer
        {
            get
            {
                return _group.First().USER_TRANSFORMER;
            }
        }

    }
    public class Level5Module : Level4Trans
    {
        public Level5Module(IGrouping<string, P_AmmeterInfo> group)
            : base(group)
        {


        }
        [DisplayName("模块")]
        public string Module
        {
            get
            {
                return _group.First().USER_MODULE;
            }
        }

    }
    public class Level6SubAmm : Level5Module
    {
        public Level6SubAmm(IGrouping<string, P_AmmeterInfo> group)
            : base(group)
        {


        }
        [DisplayName("子表")]
        public string Amm
        {
            get
            {
                return _group.First().USER_NO;
            }
        }

    }
}