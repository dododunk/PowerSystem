using System;
using System.Collections.Generic;
using System.Reflection;
namespace System.Windows.Forms
{
	public class CheckBoxComboBoxItemList : List<CheckBoxComboBoxItem>
	{
		private CheckBoxComboBox _CheckBoxComboBox;
		public event EventHandler CheckBoxCheckedChanged;
		public CheckBoxComboBoxItem this[string displayName]
		{
			get
			{
				int num = (this._CheckBoxComboBox.DropDownStyle == ComboBoxStyle.DropDownList && this._CheckBoxComboBox.DataSource == null) ? 1 : 0;
				checked
				{
					for (int i = num; i <= base.Count - 1; i++)
					{
						CheckBoxComboBoxItem checkBoxComboBoxItem = base[i];
						string text;
						if (string.IsNullOrEmpty(checkBoxComboBoxItem.Text) && checkBoxComboBoxItem.DataBindings != null && checkBoxComboBoxItem.DataBindings["Text"] != null)
						{
							PropertyInfo property = checkBoxComboBoxItem.ComboBoxItem.GetType().GetProperty(checkBoxComboBoxItem.DataBindings["Text"].BindingMemberInfo.BindingMember);
							text = (string)property.GetValue(checkBoxComboBoxItem.ComboBoxItem, null);
						}
						else
						{
							text = checkBoxComboBoxItem.Text;
						}
						if (text.CompareTo(displayName) == 0)
						{
							return checkBoxComboBoxItem;
						}
					}
					throw new ArgumentOutOfRangeException(string.Format("\"{0}\" does not exist in this combo box.", displayName));
				}
			}
		}
		public CheckBoxComboBoxItemList(CheckBoxComboBox checkBoxComboBox)
		{
			this._CheckBoxComboBox = checkBoxComboBox;
		}
		protected void OnCheckBoxCheckedChanged(object sender, EventArgs e)
		{
			EventHandler checkBoxCheckedChanged = this.CheckBoxCheckedChanged;
			if (checkBoxCheckedChanged != null)
			{
				checkBoxCheckedChanged(sender, e);
			}
		}
		private void item_CheckedChanged(object sender, EventArgs e)
		{
			this.OnCheckBoxCheckedChanged(sender, e);
		}
		[Obsolete("Do not add items to this list directly. Use the ComboBox items instead.", false)]
		public new void Add(CheckBoxComboBoxItem item)
		{
			item.CheckedChanged += new EventHandler(this.item_CheckedChanged);
			base.Add(item);
		}
		public new void AddRange(IEnumerable<CheckBoxComboBoxItem> collection)
		{
			foreach (CheckBoxComboBoxItem current in collection)
			{
				current.CheckedChanged += new EventHandler(this.item_CheckedChanged);
			}
			base.AddRange(collection);
		}
		public new void Clear()
		{
			foreach (CheckBoxComboBoxItem current in this)
			{
				current.CheckedChanged -= new EventHandler(this.item_CheckedChanged);
			}
			base.Clear();
		}
		[Obsolete("Do not remove items from this list directly. Use the ComboBox items instead.", false)]
		public new bool Remove(CheckBoxComboBoxItem item)
		{
			item.CheckedChanged -= new EventHandler(this.item_CheckedChanged);
			return base.Remove(item);
		}
	}
}
