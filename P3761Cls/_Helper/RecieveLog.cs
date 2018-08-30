using System;
using System.Collections.Generic;
namespace GB698Cls
{
    ///接收数据日志
	public class RecieveLog
	{
		public struct Log
		{
			public string Data;
		}
		public static List<RecieveLog.Log> gRECInfo = new List<RecieveLog.Log>();
		public static void AddInfo(string info)
		{
			RecieveLog.Log item = default(RecieveLog.Log);
			item.Data = info;
			RecieveLog.gRECInfo.Add(item);
		}
	}
}
