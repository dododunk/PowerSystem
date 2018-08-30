using System;
using System.ComponentModel;
using System.Data;
using System.Reflection;
namespace System.Windows.Forms
{
	public class ObjectSelectionWrapper<T> : INotifyPropertyChanged
	{
		protected int _Count = 0;
		protected bool _Selected = false;
		protected T _Item;
		protected ListSelectionWrapper<T> _Container;
		public event PropertyChangedEventHandler PropertyChanged;
		public int Count
		{
			get
			{
				return this._Count;
			}
			set
			{
				this._Count = value;
			}
		}
		public T Item
		{
			get
			{
				return this._Item;
			}
			set
			{
				this._Item = value;
			}
		}
		public string Name
		{
			get
			{
				string text = null;
				if (string.IsNullOrEmpty(this._Container.DisplayNameProperty))
				{
					T item = this.Item;
					text = item.ToString();
				}
				else
				{
					if (this.Item is DataRow)
					{
						text = (this.Item as DataRow)[this._Container.DisplayNameProperty].ToString();
					}
					else
					{
						PropertyDescriptorCollection properties = TypeDescriptor.GetProperties(this.Item);
						foreach (PropertyDescriptor propertyDescriptor in properties)
						{
							if (propertyDescriptor.Name.CompareTo(this._Container.DisplayNameProperty) == 0)
							{
								text = propertyDescriptor.GetValue(this.Item).ToString();
								break;
							}
						}
						if (string.IsNullOrEmpty(text))
						{
							T item = this.Item;
							PropertyInfo property = item.GetType().GetProperty(this._Container.DisplayNameProperty);
							if (property == null)
							{
								string arg_17F_0 = "Property {0} cannot be found on {1}.";
								object arg_17F_1 = this._Container.DisplayNameProperty;
								item = this.Item;
								throw new Exception(string.Format(arg_17F_0, arg_17F_1, item.GetType()));
							}
							text = property.GetValue(this.Item, null).ToString();
						}
					}
				}
				return this._Container.ShowCounts ? string.Format("{0} [{1}]", text, this.Count) : text;
			}
		}
		public string NameConcatenated
		{
			get
			{
				return this._Container.SelectedNames;
			}
		}
		public bool Selected
		{
			get
			{
				return this._Selected;
			}
			set
			{
				if (this._Selected != value)
				{
					this._Selected = value;
					this.OnPropertyChanged("Selected");
					this.OnPropertyChanged("NameConcatenated");
				}
			}
		}
		public ObjectSelectionWrapper(T item, ListSelectionWrapper<T> container)
		{
			this._Container = container;
			this._Item = item;
		}
		protected virtual void OnPropertyChanged(string propertyName)
		{
			PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
			if (propertyChanged != null)
			{
				propertyChanged(this, new PropertyChangedEventArgs(propertyName));
			}
		}
	}
}
