using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Drawing;
namespace WinFormsUI.Docking
{
	public sealed class NestedPaneCollection : ReadOnlyCollection<DockPane>
	{
		private INestedPanesContainer m_container;
		private VisibleNestedPaneCollection m_visibleNestedPanes;
		public INestedPanesContainer Container
		{
			get
			{
				return this.m_container;
			}
		}
		public VisibleNestedPaneCollection VisibleNestedPanes
		{
			get
			{
				return this.m_visibleNestedPanes;
			}
		}
		public DockState DockState
		{
			get
			{
				return this.Container.DockState;
			}
		}
		public bool IsFloat
		{
			get
			{
				return this.DockState == DockState.Float;
			}
		}
		internal NestedPaneCollection(INestedPanesContainer container) : base(new List<DockPane>())
		{
			this.m_container = container;
			this.m_visibleNestedPanes = new VisibleNestedPaneCollection(this);
		}
		internal void Add(DockPane pane)
		{
			if (pane != null)
			{
				NestedPaneCollection nestedPaneCollection = (pane.NestedPanesContainer == null) ? null : pane.NestedPanesContainer.NestedPanes;
				if (nestedPaneCollection != null)
				{
					nestedPaneCollection.InternalRemove(pane);
				}
				base.Items.Add(pane);
				if (nestedPaneCollection != null)
				{
					nestedPaneCollection.CheckFloatWindowDispose();
				}
			}
		}
		private void CheckFloatWindowDispose()
		{
			if (base.Count == 0 && this.Container.DockState == DockState.Float)
			{
				FloatWindow floatWindow = (FloatWindow)this.Container;
				if (!floatWindow.Disposing && !floatWindow.IsDisposed)
				{
					NativeMethods.PostMessage(((FloatWindow)this.Container).Handle, 1025, 0u, 0u);
				}
			}
		}
		internal void SwitchPaneWithFirstChild(DockPane pane)
		{
			checked
			{
				if (base.Contains(pane))
				{
					NestedDockingStatus nestedDockingStatus = pane.NestedDockingStatus;
					DockPane dockPane = null;
					for (int i = base.Count - 1; i > base.IndexOf(pane); i--)
					{
						if (base[i].NestedDockingStatus.PreviousPane == pane)
						{
							dockPane = base[i];
							break;
						}
					}
					if (dockPane != null)
					{
						int num = base.IndexOf(dockPane);
						base.Items[base.IndexOf(pane)] = dockPane;
						base.Items[num] = pane;
						NestedDockingStatus nestedDockingStatus2 = dockPane.NestedDockingStatus;
						DockAlignment alignment;
						if (nestedDockingStatus2.Alignment == DockAlignment.Left)
						{
							alignment = DockAlignment.Right;
						}
						else
						{
							if (nestedDockingStatus2.Alignment == DockAlignment.Right)
							{
								alignment = DockAlignment.Left;
							}
							else
							{
								if (nestedDockingStatus2.Alignment == DockAlignment.Top)
								{
									alignment = DockAlignment.Bottom;
								}
								else
								{
									alignment = DockAlignment.Top;
								}
							}
						}
						double proportion = unchecked(1.0 - nestedDockingStatus2.Proportion);
						nestedDockingStatus2.SetStatus(this, nestedDockingStatus.PreviousPane, nestedDockingStatus.Alignment, nestedDockingStatus.Proportion);
						for (int i = num - 1; i > base.IndexOf(dockPane); i--)
						{
							NestedDockingStatus nestedDockingStatus3 = base[i].NestedDockingStatus;
							if (nestedDockingStatus3.PreviousPane == pane)
							{
								nestedDockingStatus3.SetStatus(this, dockPane, nestedDockingStatus3.Alignment, nestedDockingStatus3.Proportion);
							}
						}
						nestedDockingStatus.SetStatus(this, dockPane, alignment, proportion);
					}
				}
			}
		}
		internal void Remove(DockPane pane)
		{
			this.InternalRemove(pane);
			this.CheckFloatWindowDispose();
		}
		private void InternalRemove(DockPane pane)
		{
			checked
			{
				if (base.Contains(pane))
				{
					NestedDockingStatus nestedDockingStatus = pane.NestedDockingStatus;
					DockPane dockPane = null;
					for (int i = base.Count - 1; i > base.IndexOf(pane); i--)
					{
						if (base[i].NestedDockingStatus.PreviousPane == pane)
						{
							dockPane = base[i];
							break;
						}
					}
					if (dockPane != null)
					{
						int num = base.IndexOf(dockPane);
						base.Items.Remove(dockPane);
						base.Items[base.IndexOf(pane)] = dockPane;
						NestedDockingStatus nestedDockingStatus2 = dockPane.NestedDockingStatus;
						nestedDockingStatus2.SetStatus(this, nestedDockingStatus.PreviousPane, nestedDockingStatus.Alignment, nestedDockingStatus.Proportion);
						for (int i = num - 1; i > base.IndexOf(dockPane); i--)
						{
							NestedDockingStatus nestedDockingStatus3 = base[i].NestedDockingStatus;
							if (nestedDockingStatus3.PreviousPane == pane)
							{
								nestedDockingStatus3.SetStatus(this, dockPane, nestedDockingStatus3.Alignment, nestedDockingStatus3.Proportion);
							}
						}
					}
					else
					{
						base.Items.Remove(pane);
					}
					nestedDockingStatus.SetStatus(null, null, DockAlignment.Left, 0.5);
					nestedDockingStatus.SetDisplayingStatus(false, null, DockAlignment.Left, 0.5);
					nestedDockingStatus.SetDisplayingBounds(Rectangle.Empty, Rectangle.Empty, Rectangle.Empty);
				}
			}
		}
		public DockPane GetDefaultPreviousPane(DockPane pane)
		{
			checked
			{
				DockPane result;
				for (int i = base.Count - 1; i >= 0; i--)
				{
					if (base[i] != pane)
					{
						result = base[i];
						return result;
					}
				}
				result = null;
				return result;
			}
		}
	}
}
