using System;
using System.Collections.Generic;
namespace GB698Cls
{
	public class ActiveReportMsg
	{
		public struct RECInfo
		{
			public byte[] Rec;
		}
		public static List<ActiveReportMsg.RECInfo> gRECInfo = new List<ActiveReportMsg.RECInfo>();
		public static void AddInfo(byte[] info)
		{
			ActiveReportMsg.RECInfo item = default(ActiveReportMsg.RECInfo);
			item.Rec = info;
			ActiveReportMsg.gRECInfo.Add(item);
		}
	}
}
