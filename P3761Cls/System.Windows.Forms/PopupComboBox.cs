using System;
using System.ComponentModel;
using System.Security.Permissions;
namespace System.Windows.Forms
{
	public class PopupComboBox : ComboBox
	{
		private IContainer components = null;
		protected Popup dropDown;
		private Control dropDownControl;
		public Control DropDownControl
		{
			get
			{
				return this.dropDownControl;
			}
			set
			{
				if (this.dropDownControl != value)
				{
					this.dropDownControl = value;
					this.dropDown = new Popup(value);
				}
			}
		}
		[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden), EditorBrowsable(EditorBrowsableState.Never)]
		public new int DropDownWidth
		{
			get
			{
				return base.DropDownWidth;
			}
			set
			{
				base.DropDownWidth = value;
			}
		}
		[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden), EditorBrowsable(EditorBrowsableState.Never)]
		public new int DropDownHeight
		{
			get
			{
				return base.DropDownHeight;
			}
			set
			{
				this.dropDown.Height = value;
				base.DropDownHeight = value;
			}
		}
		[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden), EditorBrowsable(EditorBrowsableState.Never)]
		public new bool IntegralHeight
		{
			get
			{
				return base.IntegralHeight;
			}
			set
			{
				base.IntegralHeight = value;
			}
		}
		[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden), EditorBrowsable(EditorBrowsableState.Never)]
		public new ComboBox.ObjectCollection Items
		{
			get
			{
				return base.Items;
			}
		}
		[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden), EditorBrowsable(EditorBrowsableState.Never)]
		public new int ItemHeight
		{
			get
			{
				return base.ItemHeight;
			}
			set
			{
				base.ItemHeight = value;
			}
		}
		public PopupComboBox()
		{
			this.InitializeComponent();
			base.DropDownHeight = (base.DropDownWidth = 1);
			base.IntegralHeight = false;
		}
		protected override void Dispose(bool disposing)
		{
			if (disposing)
			{
				if (this.components != null)
				{
					this.components.Dispose();
				}
				if (this.dropDown != null)
				{
					this.dropDown.Dispose();
				}
			}
			base.Dispose(disposing);
		}
		private void InitializeComponent()
		{
			base.SuspendLayout();
			base.ResumeLayout(false);
		}
		public void ShowDropDown()
		{
			if (this.dropDown != null)
			{
				this.dropDown.Show(this);
			}
		}
		public void HideDropDown()
		{
			if (this.dropDown != null)
			{
				this.dropDown.Hide();
			}
		}
		[SecurityPermission(SecurityAction.LinkDemand, Flags = SecurityPermissionFlag.UnmanagedCode)]
		protected override void WndProc(ref Message m)
		{
			if (m.Msg == 8465)
			{
				if (NativeMethods.HIWORD(m.WParam) == 7)
				{
					if (DateTime.Now.Subtract(this.dropDown.LastClosedTimeStamp).TotalMilliseconds > 500.0)
					{
						this.ShowDropDown();
					}
					return;
				}
			}
			base.WndProc(ref m);
		}
	}
}
