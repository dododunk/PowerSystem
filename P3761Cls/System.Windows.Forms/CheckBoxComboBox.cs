using System;
using System.ComponentModel;
using System.Drawing;
namespace System.Windows.Forms
{
	public class CheckBoxComboBox : PopupComboBox
	{
		private IContainer components = null;
		internal CheckBoxComboBoxListControl _CheckBoxComboBoxListControl;
		private string _DisplayMemberSingleItem = null;
		internal bool _MustAddHiddenItem = false;
		private CheckBoxProperties _CheckBoxProperties;
		public event EventHandler CheckBoxCheckedChanged;
		[Browsable(false)]
		public CheckBoxComboBoxItemList CheckBoxItems
		{
			get
			{
				if (this._CheckBoxComboBoxListControl.Items.Count != this.Items.Count)
				{
					this._CheckBoxComboBoxListControl.SynchroniseControlsWithComboBoxItems();
				}
				return this._CheckBoxComboBoxListControl.Items;
			}
		}
		public new object DataSource
		{
			get
			{
				return base.DataSource;
			}
			set
			{
				base.DataSource = value;
				if (!string.IsNullOrEmpty(this.ValueMember))
				{
					this._CheckBoxComboBoxListControl.SynchroniseControlsWithComboBoxItems();
				}
			}
		}
		public new string ValueMember
		{
			get
			{
				return base.ValueMember;
			}
			set
			{
				base.ValueMember = value;
				if (!string.IsNullOrEmpty(this.ValueMember))
				{
					this._CheckBoxComboBoxListControl.SynchroniseControlsWithComboBoxItems();
				}
			}
		}
		public string DisplayMemberSingleItem
		{
			get
			{
				string result;
				if (string.IsNullOrEmpty(this._DisplayMemberSingleItem))
				{
					result = base.DisplayMember;
				}
				else
				{
					result = this._DisplayMemberSingleItem;
				}
				return result;
			}
			set
			{
				this._DisplayMemberSingleItem = value;
			}
		}
		[Browsable(true), DesignerSerializationVisibility(DesignerSerializationVisibility.Content)]
		public new ComboBox.ObjectCollection Items
		{
			get
			{
				return base.Items;
			}
		}
		[Browsable(true), Description("The properties that will be assigned to the checkboxes as default values.")]
		public CheckBoxProperties CheckBoxProperties
		{
			get
			{
				return this._CheckBoxProperties;
			}
			set
			{
				this._CheckBoxProperties = value;
				this._CheckBoxProperties_PropertyChanged(this, EventArgs.Empty);
			}
		}
		protected override void Dispose(bool disposing)
		{
			if (disposing && this.components != null)
			{
				this.components.Dispose();
			}
			base.Dispose(disposing);
		}
		private void InitializeComponent()
		{
			this.components = new Container();
		}
		public CheckBoxComboBox()
		{
			this.InitializeComponent();
			this._CheckBoxProperties = new CheckBoxProperties();
			this._CheckBoxProperties.PropertyChanged += new EventHandler(this._CheckBoxProperties_PropertyChanged);
			CheckBoxComboBoxListControlContainer checkBoxComboBoxListControlContainer = new CheckBoxComboBoxListControlContainer();
			this._CheckBoxComboBoxListControl = new CheckBoxComboBoxListControl(this);
			this._CheckBoxComboBoxListControl.Items.CheckBoxCheckedChanged += new EventHandler(this.Items_CheckBoxCheckedChanged);
			checkBoxComboBoxListControlContainer.Controls.Add(this._CheckBoxComboBoxListControl);
			checkBoxComboBoxListControlContainer.Padding = new Padding(4, 0, 0, 14);
			this._CheckBoxComboBoxListControl.Dock = DockStyle.Fill;
			base.DropDownControl = checkBoxComboBoxListControlContainer;
			this.dropDown.Resizable = true;
		}
		internal string GetCSVText(bool skipFirstItem)
		{
			string text = string.Empty;
			int num = (base.DropDownStyle == ComboBoxStyle.DropDownList && this.DataSource == null && skipFirstItem) ? 1 : 0;
			checked
			{
				for (int i = num; i <= this._CheckBoxComboBoxListControl.Items.Count - 1; i++)
				{
					CheckBoxComboBoxItem checkBoxComboBoxItem = this._CheckBoxComboBoxListControl.Items[i];
					if (checkBoxComboBoxItem.Checked)
					{
						text += (string.IsNullOrEmpty(text) ? checkBoxComboBoxItem.Text : string.Format(", {0}", checkBoxComboBoxItem.Text));
					}
				}
				return text;
			}
		}
		private void Items_CheckBoxCheckedChanged(object sender, EventArgs e)
		{
			this.OnCheckBoxCheckedChanged(sender, e);
		}
		protected void OnCheckBoxCheckedChanged(object sender, EventArgs e)
		{
			string cSVText = this.GetCSVText(true);
			if (base.DropDownStyle != ComboBoxStyle.DropDownList)
			{
				this.Text = cSVText;
			}
			else
			{
				if (this.DataSource == null)
				{
					this.Items[0] = cSVText;
					this.CheckBoxItems[0].ComboBoxItem = cSVText;
				}
			}
			EventHandler checkBoxCheckedChanged = this.CheckBoxCheckedChanged;
			if (checkBoxCheckedChanged != null)
			{
				checkBoxCheckedChanged(sender, e);
			}
		}
		protected override void OnDropDownStyleChanged(EventArgs e)
		{
			base.OnDropDownStyleChanged(e);
			if (base.DropDownStyle == ComboBoxStyle.DropDownList && this.DataSource == null && !base.DesignMode)
			{
				this._MustAddHiddenItem = true;
			}
		}
		protected override void OnResize(EventArgs e)
		{
			Size size = new Size(base.Width, base.DropDownControl.Height);
			this.dropDown.Size = size;
			base.OnResize(e);
		}
		public void Clear()
		{
			this.Items.Clear();
			if (base.DropDownStyle == ComboBoxStyle.DropDownList && this.DataSource == null)
			{
				this._MustAddHiddenItem = true;
			}
		}
		public void ClearSelection()
		{
			foreach (CheckBoxComboBoxItem current in this.CheckBoxItems)
			{
				if (current.Checked)
				{
					current.Checked = false;
				}
			}
		}
		private void _CheckBoxProperties_PropertyChanged(object sender, EventArgs e)
		{
			foreach (CheckBoxComboBoxItem current in this.CheckBoxItems)
			{
				current.ApplyProperties(this.CheckBoxProperties);
			}
		}
		protected override void WndProc(ref Message m)
		{
			if (m.Msg == 331 && base.DropDownStyle == ComboBoxStyle.DropDownList && this.DataSource == null)
			{
				this._MustAddHiddenItem = true;
			}
			base.WndProc(ref m);
		}
	}
}
