using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PowerBenchSharpLib
{
    public static class DbDataConvert
    {
        public static string ToString(object val)
        {
            var res = val.ToString().Trim();
            return res;
        }
        public static int ToInt32(object val)
        {
            var res = ToString(val);
            return string.IsNullOrEmpty(res) ? 0 : int.Parse(res);
        }
        public static Int16 ToInt16(object val)
        {
            var res = ToString(val);
            return string.IsNullOrEmpty(res) ? (Int16)0 : Int16.Parse(res);
        }
        public static DateTime ToDateTime(object val)
        {
            var res = ToString(val);
            return string.IsNullOrEmpty(res) ? DateTime.MinValue : DateTime.Parse(res);
        }
        public static Single ToSingle(object val)
        {
            var res = ToString(val);
            return string.IsNullOrEmpty(res) ? Single.NaN : Single.Parse(res);
        }
    }
}
