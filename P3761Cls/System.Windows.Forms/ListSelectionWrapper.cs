using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Reflection;
namespace System.Windows.Forms
{
	public class ListSelectionWrapper<T> : List<ObjectSelectionWrapper<T>>
	{
		private bool _ShowCounts;
		private IEnumerable _Source;
		private string _DisplayNameProperty = null;
		public string DisplayNameProperty
		{
			get
			{
				return this._DisplayNameProperty;
			}
			set
			{
				this._DisplayNameProperty = value;
			}
		}
		public string SelectedNames
		{
			get
			{
				string text = "";
				foreach (ObjectSelectionWrapper<T> current in this)
				{
					if (current.Selected)
					{
						text += (string.IsNullOrEmpty(text) ? string.Format("\"{0}\"", current.Name) : string.Format(" & \"{0}\"", current.Name));
					}
				}
				return text;
			}
		}
		public bool ShowCounts
		{
			get
			{
				return this._ShowCounts;
			}
			set
			{
				this._ShowCounts = value;
			}
		}
		public ListSelectionWrapper(IEnumerable source) : this(source, false)
		{
		}
		public ListSelectionWrapper(IEnumerable source, bool showCounts)
		{
			this._Source = source;
			this._ShowCounts = showCounts;
			if (this._Source is IBindingList)
			{
				((IBindingList)this._Source).ListChanged += new ListChangedEventHandler(this.ListSelectionWrapper_ListChanged);
			}
			this.Populate();
		}
		public ListSelectionWrapper(IEnumerable source, string usePropertyAsDisplayName) : this(source, false, usePropertyAsDisplayName)
		{
		}
		public ListSelectionWrapper(IEnumerable source, bool showCounts, string usePropertyAsDisplayName) : this(source, showCounts)
		{
			this._DisplayNameProperty = usePropertyAsDisplayName;
		}
		public void ClearCounts()
		{
			foreach (ObjectSelectionWrapper<T> current in this)
			{
				current.Count = 0;
			}
		}
		private ObjectSelectionWrapper<T> CreateSelectionWrapper(IEnumerator Object)
		{
			Type[] types = new Type[]
			{
				typeof(T),
				base.GetType()
			};
			ConstructorInfo constructor = typeof(ObjectSelectionWrapper<T>).GetConstructor(types);
			if (constructor == null)
			{
				throw new Exception(string.Format("The selection wrapper class {0} must have a constructor with ({1} Item, {2} Container) parameters.", typeof(ObjectSelectionWrapper<T>), typeof(T), base.GetType()));
			}
			object[] parameters = new object[]
			{
				Object.Current,
				this
			};
			object obj = constructor.Invoke(parameters);
			return (ObjectSelectionWrapper<T>)obj;
		}
		public ObjectSelectionWrapper<T> FindObjectWithItem(T Object)
		{
			return base.Find(delegate(ObjectSelectionWrapper<T> target)
			{
				T item = target.Item;
				return item.Equals(Object);
			}
			);
		}
		private void Populate()
		{
			base.Clear();
			IEnumerator enumerator = this._Source.GetEnumerator();
			if (enumerator != null)
			{
				while (enumerator.MoveNext())
				{
					base.Add(this.CreateSelectionWrapper(enumerator));
				}
			}
		}
		private void ListSelectionWrapper_ListChanged(object sender, ListChangedEventArgs e)
		{
			switch (e.ListChangedType)
			{
			case ListChangedType.Reset:
				this.Populate();
				break;

			case ListChangedType.ItemAdded:
				base.Add(this.CreateSelectionWrapper((IEnumerator)((IBindingList)this._Source)[e.NewIndex]));
				break;

			case ListChangedType.ItemDeleted:
				base.Remove(this.FindObjectWithItem((T)((IBindingList)this._Source)[e.OldIndex]));
				break;
			}
		}
	}
}
