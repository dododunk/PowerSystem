using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Tigera.LibCommon;

namespace PowerBenchSharpLib
{
    //public interface ILog
    //{
    //    public static void Log(string msg)
    //}
    public class LogEventArgs : EventArgs
    {
        public string Data
        {
            get
            {
                return _data;
            }
        }
        string _data;
        public LogEventArgs(string msg)
        {
            _data = msg;
        }
    }

    public class ForwardLogger
    {
        public static void Log(params string[] msgs)
        {
            StringBuilder sb = new StringBuilder();
            foreach (var item in msgs)
            {
                sb.Append(item);
            }
            if (OnMsg != null)
            {
                OnMsg(null,new LogEventArgs(sb.ToString()));
            } 
        }
        public static event EventHandler<LogEventArgs> OnMsg;
        private ForwardLogger()
        { 
        }
    }
}
