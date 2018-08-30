using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Tigera.T_Definition;
using System.ComponentModel;

namespace PowerBenchSharpLib
{
    public class NodeEventArgs : EventArgs
    {
        object _obj;
        public NodeEventArgs(Object obj)
        {
            _obj = obj;
        }
        public Object Obj
        {
            get
            {
                return _obj;
            }
        }
    }

}
