using System;
using System.Collections.Generic;
namespace GB698Cls
{
	public class BufferManager
	{
		private struct DataItem
		{
			public string A1;
			public string A2;
			public byte[] Buff;
		}
		private static List<BufferManager.DataItem> Buff = new List<DataItem>();
		public static void AddDataItem(string A1, string A2, byte[] data)
		{
			if (data.Length > 0)
			{
				BufferManager.DataItem item;
				item.A1 = A1;
				item.A2 = A2;
				item.Buff = data;
				BufferManager.Buff.Add(item);
			}
		}
		public static void AllClear()
		{
			BufferManager.Buff.Clear();
		}
		public static void ClrBuff(string A1, string A2)
		{
			List<BufferManager.DataItem> list = BufferManager.Buff.FindAll((BufferManager.DataItem bBuff) => bBuff.A1 != A1 || bBuff.A2 != A2);
            BufferManager.Buff = list ?? new List<DataItem>();
		}
		public static byte[] PopFirstMatchBuff(string A1, string A2)
		{
			byte[] result = new byte[0];
			List<BufferManager.DataItem> list = BufferManager.Buff.FindAll((BufferManager.DataItem bBuff) => bBuff.A1 == A1 && bBuff.A2 == A2);
			if (list != null)
			{
				if (list.Count > 0)
				{
					result = BufferManager.Buff[0].Buff;
					BufferManager.Buff.Remove(BufferManager.Buff[0]);
				}
			}
			return result;
		}
	}
}
