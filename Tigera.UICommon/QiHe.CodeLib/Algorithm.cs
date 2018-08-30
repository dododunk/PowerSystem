using System;
using System.Collections;
using System.Collections.Generic;
namespace QiHe.CodeLib
{
	public class Algorithm
	{
		public static byte[] ArraySection(byte[] data, int index, int count)
		{
			byte[] array = new byte[count];
			Array.Copy(data, index, array, 0, count);
			return array;
		}
		public static bool ArrayEqual(byte[] bytes, byte[] data)
		{
			return bytes.Length == data.Length && Algorithm.ArrayEqual(bytes, data, bytes.Length);
		}
		public static bool ArrayEqual(byte[] a, byte[] b, int count)
		{
			checked
			{
				bool result;
				for (int i = 0; i < count; i++)
				{
					if (a[i] != b[i])
					{
						result = false;
						return result;
					}
				}
				result = true;
				return result;
			}
		}
		public static int[] ArrayIndice(int length)
		{
			int[] array = new int[length];
			checked
			{
				for (int i = 0; i < length; i++)
				{
					array[i] = i;
				}
				return array;
			}
		}
		public static int Maximum(ArrayList list)
		{
			int num = 0;
			foreach (ICollection collection in list)
			{
				if (num < collection.Count)
				{
					num = collection.Count;
				}
			}
			return num;
		}
		public static int Sum(IList<int> list)
		{
			int num = 0;
			checked
			{
				foreach (int current in list)
				{
					num += current;
				}
				return num;
			}
		}
		public static void CopyArray(byte[] src, byte[] dest, int start)
		{
			int num = 0;
			checked
			{
				for (int i = start; i < start + dest.Length; i++)
				{
					dest[num++] = src[i];
				}
			}
		}
		public static int Maximum(IEnumerable<int> list)
		{
			int num = -2147483648;
			foreach (int current in list)
			{
				if (num < current)
				{
					num = current;
				}
			}
			return num;
		}
		public static int Minimum(IEnumerable<int> list)
		{
			int num = 2147483647;
			foreach (int current in list)
			{
				if (num > current)
				{
					num = current;
				}
			}
			return num;
		}
		public static uint Minimum(IEnumerable<uint> list)
		{
			uint num = 4294967295u;
			foreach (uint current in list)
			{
				if (num > current)
				{
					num = current;
				}
			}
			return num;
		}
		public static int PosofMaximum(IList<int> list)
		{
			int result = 0;
			int num = list[0];
			checked
			{
				for (int i = 1; i < list.Count; i++)
				{
					if (list[i] > num)
					{
						num = list[i];
						result = i;
					}
				}
				return result;
			}
		}
		public static int PosofMinimum(IList<int> list)
		{
			int result = 0;
			int num = list[0];
			checked
			{
				for (int i = 1; i < list.Count; i++)
				{
					if (list[i] < num)
					{
						num = list[i];
						result = i;
					}
				}
				return result;
			}
		}
		public static int PosofMinimum(int[] list)
		{
			int result = 0;
			int num = list[0];
			checked
			{
				for (int i = 1; i < list.Length; i++)
				{
					if (list[i] < num)
					{
						num = list[i];
						result = i;
					}
				}
				return result;
			}
		}
		public static List<int> PosofMaximums(IList<int> list)
		{
			int num = -2147483648;
			List<int> list2 = new List<int>();
			checked
			{
				for (int i = 0; i < list.Count; i++)
				{
					int num2 = list[i];
					if (num2 > num)
					{
						num = num2;
						list2.Clear();
					}
					if (num2 == num)
					{
						list2.Add(i);
					}
				}
				return list2;
			}
		}
		public static List<int> PosofMinimums(IList<int> list)
		{
			int num = 2147483647;
			List<int> list2 = new List<int>();
			checked
			{
				for (int i = 0; i < list.Count; i++)
				{
					int num2 = list[i];
					if (num2 < num)
					{
						num = num2;
						list2.Clear();
					}
					if (num2 == num)
					{
						list2.Add(i);
					}
				}
				return list2;
			}
		}
		public static List<T> Flat<T>(List<List<T>> groups)
		{
			List<T> list = new List<T>();
			foreach (List<T> current in groups)
			{
				list.AddRange(current);
			}
			return list;
		}
	}
}
