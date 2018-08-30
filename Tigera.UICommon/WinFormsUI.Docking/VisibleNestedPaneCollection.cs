using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Drawing;
namespace WinFormsUI.Docking
{
	public sealed class VisibleNestedPaneCollection : ReadOnlyCollection<DockPane>
	{
		private NestedPaneCollection m_nestedPanes;
		public NestedPaneCollection NestedPanes
		{
			get
			{
				return this.m_nestedPanes;
			}
		}
		public INestedPanesContainer Container
		{
			get
			{
				return this.NestedPanes.Container;
			}
		}
		public DockState DockState
		{
			get
			{
				return this.NestedPanes.DockState;
			}
		}
		public bool IsFloat
		{
			get
			{
				return this.NestedPanes.IsFloat;
			}
		}
		internal VisibleNestedPaneCollection(NestedPaneCollection nestedPanes) : base(new List<DockPane>())
		{
			this.m_nestedPanes = nestedPanes;
		}
		internal void Refresh()
		{
			base.Items.Clear();
			checked
			{
				for (int i = 0; i < this.NestedPanes.Count; i++)
				{
					DockPane dockPane = this.NestedPanes[i];
					NestedDockingStatus nestedDockingStatus = dockPane.NestedDockingStatus;
					nestedDockingStatus.SetDisplayingStatus(true, nestedDockingStatus.PreviousPane, nestedDockingStatus.Alignment, nestedDockingStatus.Proportion);
					base.Items.Add(dockPane);
				}
				foreach (DockPane dockPane in this.NestedPanes)
				{
					
					if (dockPane.DockState != this.DockState || dockPane.IsHidden)
					{
						dockPane.Bounds = Rectangle.Empty;
						dockPane.SplitterBounds = Rectangle.Empty;
						this.Remove(dockPane);
					}
				}
				this.CalculateBounds();
				foreach (DockPane dockPane in this)
				{
					
					NestedDockingStatus nestedDockingStatus = dockPane.NestedDockingStatus;
					dockPane.Bounds = nestedDockingStatus.PaneBounds;
					dockPane.SplitterBounds = nestedDockingStatus.SplitterBounds;
					dockPane.SplitterAlignment = nestedDockingStatus.Alignment;
				}
			}
		}
		private void Remove(DockPane pane)
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
						nestedDockingStatus2.SetDisplayingStatus(true, nestedDockingStatus.DisplayingPreviousPane, nestedDockingStatus.DisplayingAlignment, nestedDockingStatus.DisplayingProportion);
						for (int i = num - 1; i > base.IndexOf(dockPane); i--)
						{
							NestedDockingStatus nestedDockingStatus3 = base[i].NestedDockingStatus;
							if (nestedDockingStatus3.PreviousPane == pane)
							{
								nestedDockingStatus3.SetDisplayingStatus(true, dockPane, nestedDockingStatus3.DisplayingAlignment, nestedDockingStatus3.DisplayingProportion);
							}
						}
					}
					else
					{
						base.Items.Remove(pane);
					}
					nestedDockingStatus.SetDisplayingStatus(false, null, DockAlignment.Left, 0.5);
				}
			}
		}
		private void CalculateBounds()
		{
			checked
			{
				if (base.Count != 0)
				{
					base[0].NestedDockingStatus.SetDisplayingBounds(this.Container.DisplayingRectangle, this.Container.DisplayingRectangle, Rectangle.Empty);
					for (int i = 1; i < base.Count; i++)
					{
						DockPane dockPane = base[i];
						NestedDockingStatus nestedDockingStatus = dockPane.NestedDockingStatus;
						DockPane displayingPreviousPane = nestedDockingStatus.DisplayingPreviousPane;
						NestedDockingStatus nestedDockingStatus2 = displayingPreviousPane.NestedDockingStatus;
						Rectangle paneBounds = nestedDockingStatus2.PaneBounds;
						bool arg_88_0 = nestedDockingStatus.DisplayingAlignment == DockAlignment.Left || nestedDockingStatus.DisplayingAlignment == DockAlignment.Right;
						Rectangle paneBounds2 = paneBounds;
						Rectangle paneBounds3 = paneBounds;
						Rectangle splitterBounds = paneBounds;
						if (nestedDockingStatus.DisplayingAlignment == DockAlignment.Left)
						{
							paneBounds2.Width = (int)unchecked((double)paneBounds.Width * nestedDockingStatus.DisplayingProportion) - 2;
							splitterBounds.X = paneBounds2.X + paneBounds2.Width;
							splitterBounds.Width = 4;
							paneBounds3.X = splitterBounds.X + splitterBounds.Width;
							paneBounds3.Width = paneBounds.Width - paneBounds2.Width - splitterBounds.Width;
						}
						else
						{
							if (nestedDockingStatus.DisplayingAlignment == DockAlignment.Right)
							{
								paneBounds3.Width = paneBounds.Width - (int)unchecked((double)paneBounds.Width * nestedDockingStatus.DisplayingProportion) - 2;
								splitterBounds.X = paneBounds3.X + paneBounds3.Width;
								splitterBounds.Width = 4;
								paneBounds2.X = splitterBounds.X + splitterBounds.Width;
								paneBounds2.Width = paneBounds.Width - paneBounds3.Width - splitterBounds.Width;
							}
							else
							{
								if (nestedDockingStatus.DisplayingAlignment == DockAlignment.Top)
								{
									paneBounds2.Height = (int)unchecked((double)paneBounds.Height * nestedDockingStatus.DisplayingProportion) - 2;
									splitterBounds.Y = paneBounds2.Y + paneBounds2.Height;
									splitterBounds.Height = 4;
									paneBounds3.Y = splitterBounds.Y + splitterBounds.Height;
									paneBounds3.Height = paneBounds.Height - paneBounds2.Height - splitterBounds.Height;
								}
								else
								{
									if (nestedDockingStatus.DisplayingAlignment == DockAlignment.Bottom)
									{
										paneBounds3.Height = paneBounds.Height - (int)unchecked((double)paneBounds.Height * nestedDockingStatus.DisplayingProportion) - 2;
										splitterBounds.Y = paneBounds3.Y + paneBounds3.Height;
										splitterBounds.Height = 4;
										paneBounds2.Y = splitterBounds.Y + splitterBounds.Height;
										paneBounds2.Height = paneBounds.Height - paneBounds3.Height - splitterBounds.Height;
									}
									else
									{
										paneBounds2 = Rectangle.Empty;
									}
								}
							}
						}
						splitterBounds.Intersect(paneBounds);
						paneBounds2.Intersect(paneBounds);
						paneBounds3.Intersect(paneBounds);
						nestedDockingStatus.SetDisplayingBounds(paneBounds, paneBounds2, splitterBounds);
						nestedDockingStatus2.SetDisplayingBounds(nestedDockingStatus2.LogicalBounds, paneBounds3, nestedDockingStatus2.SplitterBounds);
					}
				}
			}
		}
	}
}
