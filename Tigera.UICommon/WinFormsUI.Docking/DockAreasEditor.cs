using System;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Design;
using System.Windows.Forms;
using System.Windows.Forms.Design;
namespace WinFormsUI.Docking
{
	internal class DockAreasEditor : UITypeEditor
	{
		private class DockAreasEditorControl : UserControl
		{
			private CheckBox checkBoxFloat;
			private CheckBox checkBoxDockLeft;
			private CheckBox checkBoxDockRight;
			private CheckBox checkBoxDockTop;
			private CheckBox checkBoxDockBottom;
			private CheckBox checkBoxDockFill;
			private DockAreas m_oldDockAreas;
			public DockAreas DockAreas
			{
				get
				{
					DockAreas dockAreas = (DockAreas)0;
					if (this.checkBoxFloat.Checked)
					{
						dockAreas |= DockAreas.Float;
					}
					if (this.checkBoxDockLeft.Checked)
					{
						dockAreas |= DockAreas.DockLeft;
					}
					if (this.checkBoxDockRight.Checked)
					{
						dockAreas |= DockAreas.DockRight;
					}
					if (this.checkBoxDockTop.Checked)
					{
						dockAreas |= DockAreas.DockTop;
					}
					if (this.checkBoxDockBottom.Checked)
					{
						dockAreas |= DockAreas.DockBottom;
					}
					if (this.checkBoxDockFill.Checked)
					{
						dockAreas |= DockAreas.Document;
					}
					DockAreas result;
					if (dockAreas == (DockAreas)0)
					{
						result = this.m_oldDockAreas;
					}
					else
					{
						result = dockAreas;
					}
					return result;
				}
			}
			public DockAreasEditorControl()
			{
				this.checkBoxFloat = new CheckBox();
				this.checkBoxDockLeft = new CheckBox();
				this.checkBoxDockRight = new CheckBox();
				this.checkBoxDockTop = new CheckBox();
				this.checkBoxDockBottom = new CheckBox();
				this.checkBoxDockFill = new CheckBox();
				base.SuspendLayout();
				this.checkBoxFloat.Appearance = Appearance.Button;
				this.checkBoxFloat.Dock = DockStyle.Top;
				this.checkBoxFloat.Height = 24;
				this.checkBoxFloat.Text = Strings.DockAreaEditor_FloatCheckBoxText;
				this.checkBoxFloat.TextAlign = ContentAlignment.MiddleCenter;
				this.checkBoxFloat.FlatStyle = FlatStyle.System;
				this.checkBoxDockLeft.Appearance = Appearance.Button;
				this.checkBoxDockLeft.Dock = DockStyle.Left;
				this.checkBoxDockLeft.Width = 24;
				this.checkBoxDockLeft.FlatStyle = FlatStyle.System;
				this.checkBoxDockRight.Appearance = Appearance.Button;
				this.checkBoxDockRight.Dock = DockStyle.Right;
				this.checkBoxDockRight.Width = 24;
				this.checkBoxDockRight.FlatStyle = FlatStyle.System;
				this.checkBoxDockTop.Appearance = Appearance.Button;
				this.checkBoxDockTop.Dock = DockStyle.Top;
				this.checkBoxDockTop.Height = 24;
				this.checkBoxDockTop.FlatStyle = FlatStyle.System;
				this.checkBoxDockBottom.Appearance = Appearance.Button;
				this.checkBoxDockBottom.Dock = DockStyle.Bottom;
				this.checkBoxDockBottom.Height = 24;
				this.checkBoxDockBottom.FlatStyle = FlatStyle.System;
				this.checkBoxDockFill.Appearance = Appearance.Button;
				this.checkBoxDockFill.Dock = DockStyle.Fill;
				this.checkBoxDockFill.FlatStyle = FlatStyle.System;
				base.Controls.AddRange(new Control[]
				{
					this.checkBoxDockFill,
					this.checkBoxDockBottom,
					this.checkBoxDockTop,
					this.checkBoxDockRight,
					this.checkBoxDockLeft,
					this.checkBoxFloat
				});
				base.Size = new Size(160, 144);
				this.BackColor = SystemColors.Control;
				base.ResumeLayout();
			}
			public void SetStates(DockAreas dockAreas)
			{
				this.m_oldDockAreas = dockAreas;
				if ((dockAreas & DockAreas.DockLeft) != (DockAreas)0)
				{
					this.checkBoxDockLeft.Checked = true;
				}
				if ((dockAreas & DockAreas.DockRight) != (DockAreas)0)
				{
					this.checkBoxDockRight.Checked = true;
				}
				if ((dockAreas & DockAreas.DockTop) != (DockAreas)0)
				{
					this.checkBoxDockTop.Checked = true;
				}
				if ((dockAreas & DockAreas.DockTop) != (DockAreas)0)
				{
					this.checkBoxDockTop.Checked = true;
				}
				if ((dockAreas & DockAreas.DockBottom) != (DockAreas)0)
				{
					this.checkBoxDockBottom.Checked = true;
				}
				if ((dockAreas & DockAreas.Document) != (DockAreas)0)
				{
					this.checkBoxDockFill.Checked = true;
				}
				if ((dockAreas & DockAreas.Float) != (DockAreas)0)
				{
					this.checkBoxFloat.Checked = true;
				}
			}
		}
		private DockAreasEditor.DockAreasEditorControl m_ui = null;
		public override UITypeEditorEditStyle GetEditStyle(ITypeDescriptorContext context)
		{
			return UITypeEditorEditStyle.DropDown;
		}
		public override object EditValue(ITypeDescriptorContext context, IServiceProvider sp, object value)
		{
			if (this.m_ui == null)
			{
				this.m_ui = new DockAreasEditor.DockAreasEditorControl();
			}
			this.m_ui.SetStates((DockAreas)value);
			IWindowsFormsEditorService windowsFormsEditorService = (IWindowsFormsEditorService)sp.GetService(typeof(IWindowsFormsEditorService));
			windowsFormsEditorService.DropDownControl(this.m_ui);
			return this.m_ui.DockAreas;
		}
	}
}
