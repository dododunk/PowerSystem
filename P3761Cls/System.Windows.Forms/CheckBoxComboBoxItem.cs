using System;
using System.ComponentModel;
using System.Reflection;
namespace System.Windows.Forms
{
	public class CheckBoxComboBoxItem : CheckBox
	{
		private CheckBoxComboBox _CheckBoxComboBox;
		private object _ComboBoxItem;
		public object ComboBoxItem
		{
			get
			{
				return this._ComboBoxItem;
			}
			internal set
			{
				this._ComboBoxItem = value;
			}
		}
		public CheckBoxComboBoxItem(CheckBoxComboBox owner, object comboBoxItem)
		{
			this.DoubleBuffered = true;
			this._CheckBoxComboBox = owner;
			this._ComboBoxItem = comboBoxItem;
			if (this._CheckBoxComboBox.DataSource != null)
			{
				this.AddBindings();
			}
			else
			{
				this.Text = comboBoxItem.ToString();
			}
		}
		public void AddBindings()
		{
			base.DataBindings.Add("Text", this._ComboBoxItem, this._CheckBoxComboBox.DisplayMemberSingleItem);
			base.DataBindings.Add("Checked", this._ComboBoxItem, this._CheckBoxComboBox.ValueMember, false, DataSourceUpdateMode.OnPropertyChanged, false, null, null);
			if (this._ComboBoxItem is INotifyPropertyChanged)
			{
				((INotifyPropertyChanged)this._ComboBoxItem).PropertyChanged += new PropertyChangedEventHandler(this.CheckBoxComboBoxItem_PropertyChanged);
			}
		}
		protected override void OnCheckedChanged(EventArgs e)
		{
			if (this._CheckBoxComboBox.DataSource != null)
			{
				PropertyInfo property = this.ComboBoxItem.GetType().GetProperty(this._CheckBoxComboBox.ValueMember);
				property.SetValue(this.ComboBoxItem, base.Checked, null);
			}
			base.OnCheckedChanged(e);
			if (this._CheckBoxComboBox.DataSource != null)
			{
				string displayMember = this._CheckBoxComboBox.DisplayMember;
				this._CheckBoxComboBox.DisplayMember = null;
				this._CheckBoxComboBox.DisplayMember = displayMember;
			}
		}
		internal void ApplyProperties(CheckBoxProperties properties)
		{
			base.Appearance = properties.Appearance;
			base.AutoCheck = properties.AutoCheck;
			base.AutoEllipsis = properties.AutoEllipsis;
			this.AutoSize = properties.AutoSize;
			base.CheckAlign = properties.CheckAlign;
			base.FlatAppearance.BorderColor = properties.FlatAppearanceBorderColor;
			base.FlatAppearance.BorderSize = properties.FlatAppearanceBorderSize;
			base.FlatAppearance.CheckedBackColor = properties.FlatAppearanceCheckedBackColor;
			base.FlatAppearance.MouseDownBackColor = properties.FlatAppearanceMouseDownBackColor;
			base.FlatAppearance.MouseOverBackColor = properties.FlatAppearanceMouseOverBackColor;
			base.FlatStyle = properties.FlatStyle;
			this.ForeColor = properties.ForeColor;
			this.RightToLeft = properties.RightToLeft;
			this.TextAlign = properties.TextAlign;
			base.ThreeState = properties.ThreeState;
		}
		private void CheckBoxComboBoxItem_PropertyChanged(object sender, PropertyChangedEventArgs e)
		{
			if (e.PropertyName == this._CheckBoxComboBox.ValueMember)
			{
				base.Checked = (bool)this._ComboBoxItem.GetType().GetProperty(this._CheckBoxComboBox.ValueMember).GetValue(this._ComboBoxItem, null);
			}
		}
	}
}
