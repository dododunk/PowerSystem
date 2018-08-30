using System;
using System.Drawing;
namespace System.Windows.Forms
{
	public class CheckBoxComboBoxListControl : ScrollableControl
	{
		private CheckBoxComboBox _CheckBoxComboBox;
		private CheckBoxComboBoxItemList _Items;
		public CheckBoxComboBoxItemList Items
		{
			get
			{
				return this._Items;
			}
		}
		public CheckBoxComboBoxListControl(CheckBoxComboBox owner)
		{
			this.DoubleBuffered = true;
			this._CheckBoxComboBox = owner;
			this._Items = new CheckBoxComboBoxItemList(this._CheckBoxComboBox);
			this.BackColor = SystemColors.Window;
			this.AutoScroll = true;
			base.ResizeRedraw = true;
			this.MinimumSize = new Size(1, 1);
			this.MaximumSize = new Size(500, 500);
		}
		protected override void WndProc(ref Message m)
		{
			if (!(base.Parent.Parent as Popup).ProcessResizing(ref m))
			{
				base.WndProc(ref m);
			}
		}
		protected override void OnVisibleChanged(EventArgs e)
		{
			this.SynchroniseControlsWithComboBoxItems();
			base.OnVisibleChanged(e);
		}
		public void SynchroniseControlsWithComboBoxItems()
		{
			base.SuspendLayout();
			if (this._CheckBoxComboBox._MustAddHiddenItem)
			{
				this._CheckBoxComboBox.Items.Insert(0, this._CheckBoxComboBox.GetCSVText(false));
				this._CheckBoxComboBox.SelectedIndex = 0;
				this._CheckBoxComboBox._MustAddHiddenItem = false;
			}
			base.Controls.Clear();
			checked
			{
				for (int i = this._Items.Count - 1; i >= 0; i--)
				{
					CheckBoxComboBoxItem checkBoxComboBoxItem = this._Items[i];
					if (!this._CheckBoxComboBox.Items.Contains(checkBoxComboBoxItem.ComboBoxItem))
					{
						this._Items.Remove(checkBoxComboBoxItem);
						checkBoxComboBoxItem.Dispose();
					}
				}
				bool flag = this._CheckBoxComboBox.DropDownStyle == ComboBoxStyle.DropDownList && this._CheckBoxComboBox.DataSource == null && !base.DesignMode;
				CheckBoxComboBoxItemList checkBoxComboBoxItemList = new CheckBoxComboBoxItemList(this._CheckBoxComboBox);
				for (int j = 0; j <= this._CheckBoxComboBox.Items.Count - 1; j++)
				{
					object obj = this._CheckBoxComboBox.Items[j];
					CheckBoxComboBoxItem checkBoxComboBoxItem = null;
					if (j == 0 && flag && this._Items.Count > 0)
					{
						checkBoxComboBoxItem = this._Items[0];
					}
					else
					{
						int num = flag ? 1 : 0;
						for (int k = num; k <= this._Items.Count - 1; k++)
						{
							if (this._Items[k].ComboBoxItem == obj)
							{
								checkBoxComboBoxItem = this._Items[k];
								break;
							}
						}
					}
					if (checkBoxComboBoxItem == null)
					{
						checkBoxComboBoxItem = new CheckBoxComboBoxItem(this._CheckBoxComboBox, obj);
						checkBoxComboBoxItem.ApplyProperties(this._CheckBoxComboBox.CheckBoxProperties);
					}
					checkBoxComboBoxItemList.Add(checkBoxComboBoxItem);
					checkBoxComboBoxItem.Dock = DockStyle.Top;
				}
				this._Items.Clear();
				this._Items.AddRange(checkBoxComboBoxItemList);
				if (checkBoxComboBoxItemList.Count > 0)
				{
					checkBoxComboBoxItemList.Reverse();
					base.Controls.AddRange(checkBoxComboBoxItemList.ToArray());
				}
				if (this._CheckBoxComboBox.DropDownStyle == ComboBoxStyle.DropDownList && this._CheckBoxComboBox.DataSource == null && !base.DesignMode)
				{
					this._CheckBoxComboBox.CheckBoxItems[0].Visible = false;
				}
				base.ResumeLayout();
			}
		}
	}
}
