using System;
using System.Collections;
using System.Collections.Generic;
namespace QiHe.CodeLib
{
	public class UniqueList<T> : IList<T>, ICollection<T>, IEnumerable<T>, IEnumerable
	{
		private IList<T> internalList;
		private IDictionary<T, int> internalLookup;
		public T this[int index]
		{
			get
			{
				return this.internalList[index];
			}
			set
			{
				this.internalList[index] = value;
			}
		}
		public int Count
		{
			get
			{
				return this.internalList.Count;
			}
		}
		public bool IsReadOnly
		{
			get
			{
				return this.internalList.IsReadOnly;
			}
		}
		public UniqueList()
		{
			this.internalList = new List<T>();
			this.internalLookup = new Dictionary<T, int>();
		}
		public UniqueList(int capacity)
		{
			this.internalList = new List<T>(capacity);
			this.internalLookup = new Dictionary<T, int>(capacity);
		}
		public int IndexOf(T item)
		{
			int result;
			if (this.internalLookup.ContainsKey(item))
			{
				result = this.internalLookup[item];
			}
			else
			{
				result = -1;
			}
			return result;
		}
		public void Insert(int index, T item)
		{
			if (this.internalLookup.ContainsKey(item))
			{
				throw new ArgumentException("Duplicate item already exist in the list");
			}
			this.internalList.Insert(index, item);
			this.internalLookup.Add(item, index);
			checked
			{
				for (int i = index; i < this.internalList.Count; i++)
				{
					T key = this.internalList[i];
					this.internalLookup[key] = i;
				}
			}
		}
		public void RemoveAt(int index)
		{
			T key = this.internalList[index];
			this.internalList.RemoveAt(index);
			this.internalLookup.Remove(key);
			checked
			{
				for (int i = index; i < this.internalList.Count; i++)
				{
					T key2 = this.internalList[i];
					this.internalLookup[key2] = i;
				}
			}
		}
		public void Add(T item)
		{
			this.internalList.Add(item);
			if (!this.internalLookup.ContainsKey(item))
			{
				this.internalLookup.Add(item, checked(this.internalList.Count - 1));
			}
		}
		public void Clear()
		{
			this.internalList.Clear();
			this.internalLookup.Clear();
		}
		public bool Contains(T item)
		{
			return this.internalLookup.ContainsKey(item);
		}
		public void CopyTo(T[] array, int arrayIndex)
		{
			this.internalList.CopyTo(array, arrayIndex);
		}
		public bool Remove(T item)
		{
			bool result;
			if (this.internalLookup.ContainsKey(item))
			{
				int index = this.internalLookup[item];
				this.RemoveAt(index);
				result = true;
			}
			else
			{
				result = false;
			}
			return result;
		}
		IEnumerator<T> IEnumerable<T>.GetEnumerator()
		{
			return this.internalList.GetEnumerator();
		}
		public IEnumerator GetEnumerator()
		{
			return this.internalList.GetEnumerator();
		}
	}
}
