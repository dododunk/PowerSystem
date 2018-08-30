using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;

namespace PowerBenchSharpLib
{
    public class AmmeterUsage
    {
        [DisplayName("用户")]
        public string USER_NO
        {
            get;
            set;
        }

        [DisplayName("时间")]
        public DateTime CHECK_TIME
        {
            get;
            set;
        }
        [DisplayName("值")]
        public double CHECK_VALUE
        {
            get;
            set;
        }
    }
}
