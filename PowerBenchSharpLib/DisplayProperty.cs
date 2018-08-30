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

    //class DisplayProperty
    //{
    //    IGrouping<string, P_AmmeterInfo> _info;
    //    public DisplayProperty(IGrouping<string,P_AmmeterInfo> info)
    //    {
    //        _info = info;
    //    }

    //    [DisplayNameAttribute("名称")]
    //    public string Name
    //    {
    //        get
    //        {
    //            return _info.Key;
    //        }
    //    }
    //    [DisplayNameAttribute("子项个数")]
    //    public int ChildCount
    //    {
    //        get
    //        {
    //            return _info.Count();
    //        }
    //    }

    //}
}
