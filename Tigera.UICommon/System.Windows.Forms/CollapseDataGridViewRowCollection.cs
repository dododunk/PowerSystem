using System;
using System.Collections;
using System.Collections.Generic;
namespace System.Windows.Forms
{
	public class CollapseDataGridViewRowCollection : ICollection<DataGridViewRow>, IEnumerable<DataGridViewRow>, IEnumerable
	{
		private List<DataGridViewRow> m_list = new List<DataGridViewRow>();
		public DataGridViewRow this[int index]
		{
			get
			{
				if (index >= this.m_list.Count)
				{
					throw new ArgumentOutOfRangeException("index");
				}
				return this.m_list[index];
			}
		}
		public int Count
		{
			get
			{
				return this.m_list.Count;
			}
		}
		public bool IsReadOnly
		{
			get
			{
				return false;
			}
		}
		public IEnumerator<DataGridViewRow> GetEnumerator()
		{
			if (this.m_list.Count == 0)
			{
				throw new ArgumentOutOfRangeException("collection is null");
			}
			checked
			{
				for (int i = 0; i < this.m_list.Count; i++)
				{
					yield return this.m_list[i];
				}
				yield break;
			}
		}
		IEnumerator IEnumerable.GetEnumerator()
		{
			if (this.m_list.Count == 0)
			{
				throw new ArgumentOutOfRangeException("collection is null");
			}
			checked
			{
				for (int i = 0; i < this.m_list.Count; i++)
				{
					yield return this.m_list[i];
				}
				yield break;
			}
		}
		public void Add(DataGridViewRow item)
		{
			this.m_list.Add(item);
		}
		public void Clear()
		{
			this.m_list.Clear();
		}
		public bool Contains(DataGridViewRow item)
		{
			return this.m_list.Contains(item);
		}
		public void CopyTo(DataGridViewRow[] array, int arrayIndex)
		{
			this.m_list.CopyTo(array, arrayIndex);
		}
		public bool Remove(DataGridViewRow item)
		{
			return this.m_list.Remove(item);
		}
	}
}
