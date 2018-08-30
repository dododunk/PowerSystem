using System;
using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;
namespace WinFormsUI.Docking
{
	public abstract class AutoHideStripBase : Control
	{
		protected class Tab : IDisposable
		{
			private IDockContent m_content;
			public IDockContent Content
			{
				get
				{
					return this.m_content;
				}
			}
			protected internal Tab(IDockContent content)
			{
				this.m_content = content;
			}
			~Tab()
			{
				this.Dispose(false);
			}
			public void Dispose()
			{
				this.Dispose(true);
				GC.SuppressFinalize(this);
			}
			protected virtual void Dispose(bool disposing)
			{
			}
		}
		protected sealed class TabCollection : IEnumerable<AutoHideStripBase.Tab>, IEnumerable
		{
			private DockPane m_dockPane = null;
			public DockPane DockPane
			{
				get
				{
					return this.m_dockPane;
				}
			}
			public DockPanel DockPanel
			{
				get
				{
					return this.DockPane.DockPanel;
				}
			}
			public int Count
			{
				get
				{
					return this.DockPane.DisplayingContents.Count;
				}
			}
			public AutoHideStripBase.Tab this[int index]
			{
				get
				{
					IDockContent dockContent = this.DockPane.DisplayingContents[index];
					if (dockContent == null)
					{
						throw new ArgumentOutOfRangeException("index");
					}
					if (dockContent.DockHandler.AutoHideTab == null)
					{
						dockContent.DockHandler.AutoHideTab = this.DockPanel.AutoHideStripControl.CreateTab(dockContent);
					}
					return dockContent.DockHandler.AutoHideTab as AutoHideStripBase.Tab;
				}
			}
			IEnumerator<AutoHideStripBase.Tab> IEnumerable<AutoHideStripBase.Tab>.GetEnumerator()
			{
				checked
				{
					for (int i = 0; i < this.Count; i++)
					{
						yield return this[i];
					}
					yield break;
				}
			}
			IEnumerator IEnumerable.GetEnumerator()
			{
				checked
				{
					for (int i = 0; i < this.Count; i++)
					{
						yield return this[i];
					}
					yield break;
				}
			}
			internal TabCollection(DockPane pane)
			{
				this.m_dockPane = pane;
			}
			public bool Contains(AutoHideStripBase.Tab tab)
			{
				return this.IndexOf(tab) != -1;
			}
			public bool Contains(IDockContent content)
			{
				return this.IndexOf(content) != -1;
			}
			public int IndexOf(AutoHideStripBase.Tab tab)
			{
				int result;
				if (tab == null)
				{
					result = -1;
				}
				else
				{
					result = this.IndexOf(tab.Content);
				}
				return result;
			}
			public int IndexOf(IDockContent content)
			{
				return this.DockPane.DisplayingContents.IndexOf(content);
			}
		}
		protected class Pane : IDisposable
		{
			private DockPane m_dockPane;
			public DockPane DockPane
			{
				get
				{
					return this.m_dockPane;
				}
			}
			public AutoHideStripBase.TabCollection AutoHideTabs
			{
				get
				{
					if (this.DockPane.AutoHideTabs == null)
					{
						this.DockPane.AutoHideTabs = new AutoHideStripBase.TabCollection(this.DockPane);
					}
					return this.DockPane.AutoHideTabs as AutoHideStripBase.TabCollection;
				}
			}
			protected internal Pane(DockPane dockPane)
			{
				this.m_dockPane = dockPane;
			}
			~Pane()
			{
				this.Dispose(false);
			}
			public void Dispose()
			{
				this.Dispose(true);
				GC.SuppressFinalize(this);
			}
			protected virtual void Dispose(bool disposing)
			{
			}
		}
		protected sealed class PaneCollection : IEnumerable<AutoHideStripBase.Pane>, IEnumerable
		{
			private class AutoHideState
			{
				public DockState m_dockState;
				public bool m_selected = false;
				public DockState DockState
				{
					get
					{
						return this.m_dockState;
					}
				}
				public bool Selected
				{
					get
					{
						return this.m_selected;
					}
					set
					{
						this.m_selected = value;
					}
				}
				public AutoHideState(DockState dockState)
				{
					this.m_dockState = dockState;
				}
			}
			private class AutoHideStateCollection
			{
				private AutoHideStripBase.PaneCollection.AutoHideState[] m_states;
				public AutoHideStripBase.PaneCollection.AutoHideState this[DockState dockState]
				{
					get
					{
						checked
						{
							for (int i = 0; i < this.m_states.Length; i++)
							{
								if (this.m_states[i].DockState == dockState)
								{
									return this.m_states[i];
								}
							}
							throw new ArgumentOutOfRangeException("dockState");
						}
					}
				}
				public AutoHideStateCollection()
				{
					this.m_states = new AutoHideStripBase.PaneCollection.AutoHideState[]
					{
						new AutoHideStripBase.PaneCollection.AutoHideState(DockState.DockTopAutoHide),
						new AutoHideStripBase.PaneCollection.AutoHideState(DockState.DockBottomAutoHide),
						new AutoHideStripBase.PaneCollection.AutoHideState(DockState.DockLeftAutoHide),
						new AutoHideStripBase.PaneCollection.AutoHideState(DockState.DockRightAutoHide)
					};
				}
				public bool ContainsPane(DockPane pane)
				{
					checked
					{
						bool result;
						if (pane.IsHidden)
						{
							result = false;
						}
						else
						{
							for (int i = 0; i < this.m_states.Length; i++)
							{
								if (this.m_states[i].DockState == pane.DockState && this.m_states[i].Selected)
								{
									result = true;
									return result;
								}
							}
							result = false;
						}
						return result;
					}
				}
			}
			private DockPanel m_dockPanel;
			private AutoHideStripBase.PaneCollection.AutoHideStateCollection m_states;
			public DockPanel DockPanel
			{
				get
				{
					return this.m_dockPanel;
				}
			}
			private AutoHideStripBase.PaneCollection.AutoHideStateCollection States
			{
				get
				{
					return this.m_states;
				}
			}
			public int Count
			{
				get
				{
					int num = 0;
					checked
					{
						foreach (DockPane current in this.DockPanel.Panes)
						{
							if (this.States.ContainsPane(current))
							{
								num++;
							}
						}
						return num;
					}
				}
			}
			public AutoHideStripBase.Pane this[int index]
			{
				get
				{
					int num = 0;
					checked
					{
						foreach (DockPane current in this.DockPanel.Panes)
						{
							if (this.States.ContainsPane(current))
							{
								if (num == index)
								{
									if (current.AutoHidePane == null)
									{
										current.AutoHidePane = this.DockPanel.AutoHideStripControl.CreatePane(current);
									}
									return current.AutoHidePane as AutoHideStripBase.Pane;
								}
								num++;
							}
						}
						throw new ArgumentOutOfRangeException("index");
					}
				}
			}
			internal PaneCollection(DockPanel panel, DockState dockState)
			{
				this.m_dockPanel = panel;
				this.m_states = new AutoHideStripBase.PaneCollection.AutoHideStateCollection();
				this.States[DockState.DockTopAutoHide].Selected = (dockState == DockState.DockTopAutoHide);
				this.States[DockState.DockBottomAutoHide].Selected = (dockState == DockState.DockBottomAutoHide);
				this.States[DockState.DockLeftAutoHide].Selected = (dockState == DockState.DockLeftAutoHide);
				this.States[DockState.DockRightAutoHide].Selected = (dockState == DockState.DockRightAutoHide);
			}
			public bool Contains(AutoHideStripBase.Pane pane)
			{
				return this.IndexOf(pane) != -1;
			}
			public int IndexOf(AutoHideStripBase.Pane pane)
			{
				checked
				{
					int result;
					if (pane == null)
					{
						result = -1;
					}
					else
					{
						int num = 0;
						foreach (DockPane current in this.DockPanel.Panes)
						{
							if (this.States.ContainsPane(pane.DockPane))
							{
								if (pane == current.AutoHidePane)
								{
									result = num;
									return result;
								}
								num++;
							}
						}
						result = -1;
					}
					return result;
				}
			}
			IEnumerator<AutoHideStripBase.Pane> IEnumerable<AutoHideStripBase.Pane>.GetEnumerator()
			{
				checked
				{
					for (int i = 0; i < this.Count; i++)
					{
						yield return this[i];
					}
					yield break;
				}
			}
			IEnumerator IEnumerable.GetEnumerator()
			{
				checked
				{
					for (int i = 0; i < this.Count; i++)
					{
						yield return this[i];
					}
					yield break;
				}
			}
		}
		private DockPanel m_dockPanel;
		private AutoHideStripBase.PaneCollection m_panesTop;
		private AutoHideStripBase.PaneCollection m_panesBottom;
		private AutoHideStripBase.PaneCollection m_panesLeft;
		private AutoHideStripBase.PaneCollection m_panesRight;
		private GraphicsPath m_displayingArea = null;
		protected DockPanel DockPanel
		{
			get
			{
				return this.m_dockPanel;
			}
		}
		protected AutoHideStripBase.PaneCollection PanesTop
		{
			get
			{
				return this.m_panesTop;
			}
		}
		protected AutoHideStripBase.PaneCollection PanesBottom
		{
			get
			{
				return this.m_panesBottom;
			}
		}
		protected AutoHideStripBase.PaneCollection PanesLeft
		{
			get
			{
				return this.m_panesLeft;
			}
		}
		protected AutoHideStripBase.PaneCollection PanesRight
		{
			get
			{
				return this.m_panesRight;
			}
		}
		protected Rectangle RectangleTopLeft
		{
			get
			{
				int num = this.MeasureHeight();
				return (this.PanesTop.Count > 0 && this.PanesLeft.Count > 0) ? new Rectangle(0, 0, num, num) : Rectangle.Empty;
			}
		}
		protected Rectangle RectangleTopRight
		{
			get
			{
				int num = this.MeasureHeight();
				return (this.PanesTop.Count > 0 && this.PanesRight.Count > 0) ? new Rectangle(checked(base.Width - num), 0, num, num) : Rectangle.Empty;
			}
		}
		protected Rectangle RectangleBottomLeft
		{
			get
			{
				int num = this.MeasureHeight();
				return (this.PanesBottom.Count > 0 && this.PanesLeft.Count > 0) ? new Rectangle(0, checked(base.Height - num), num, num) : Rectangle.Empty;
			}
		}
		protected Rectangle RectangleBottomRight
		{
			get
			{
				int num = this.MeasureHeight();
				return (this.PanesBottom.Count > 0 && this.PanesRight.Count > 0) ? checked(new Rectangle(base.Width - num, base.Height - num, num, num)) : Rectangle.Empty;
			}
		}
		private GraphicsPath DisplayingArea
		{
			get
			{
				if (this.m_displayingArea == null)
				{
					this.m_displayingArea = new GraphicsPath();
				}
				return this.m_displayingArea;
			}
		}
		protected AutoHideStripBase(DockPanel panel)
		{
			this.m_dockPanel = panel;
			this.m_panesTop = new AutoHideStripBase.PaneCollection(panel, DockState.DockTopAutoHide);
			this.m_panesBottom = new AutoHideStripBase.PaneCollection(panel, DockState.DockBottomAutoHide);
			this.m_panesLeft = new AutoHideStripBase.PaneCollection(panel, DockState.DockLeftAutoHide);
			this.m_panesRight = new AutoHideStripBase.PaneCollection(panel, DockState.DockRightAutoHide);
			base.SetStyle(ControlStyles.OptimizedDoubleBuffer, true);
			base.SetStyle(ControlStyles.Selectable, false);
		}
		protected AutoHideStripBase.PaneCollection GetPanes(DockState dockState)
		{
			AutoHideStripBase.PaneCollection result;
			if (dockState == DockState.DockTopAutoHide)
			{
				result = this.PanesTop;
			}
			else
			{
				if (dockState == DockState.DockBottomAutoHide)
				{
					result = this.PanesBottom;
				}
				else
				{
					if (dockState == DockState.DockLeftAutoHide)
					{
						result = this.PanesLeft;
					}
					else
					{
						if (dockState != DockState.DockRightAutoHide)
						{
							throw new ArgumentOutOfRangeException("dockState");
						}
						result = this.PanesRight;
					}
				}
			}
			return result;
		}
		internal int GetNumberOfPanes(DockState dockState)
		{
			return this.GetPanes(dockState).Count;
		}
		protected internal Rectangle GetTabStripRectangle(DockState dockState)
		{
			int num = this.MeasureHeight();
			checked
			{
				Rectangle result;
				if (dockState == DockState.DockTopAutoHide && this.PanesTop.Count > 0)
				{
					result = new Rectangle(this.RectangleTopLeft.Width, 0, base.Width - this.RectangleTopLeft.Width - this.RectangleTopRight.Width, num);
				}
				else
				{
					if (dockState == DockState.DockBottomAutoHide && this.PanesBottom.Count > 0)
					{
						result = new Rectangle(this.RectangleBottomLeft.Width, base.Height - num, base.Width - this.RectangleBottomLeft.Width - this.RectangleBottomRight.Width, num);
					}
					else
					{
						if (dockState == DockState.DockLeftAutoHide && this.PanesLeft.Count > 0)
						{
							result = new Rectangle(0, this.RectangleTopLeft.Width, num, base.Height - this.RectangleTopLeft.Height - this.RectangleBottomLeft.Height);
						}
						else
						{
							if (dockState == DockState.DockRightAutoHide && this.PanesRight.Count > 0)
							{
								result = new Rectangle(base.Width - num, this.RectangleTopRight.Width, num, base.Height - this.RectangleTopRight.Height - this.RectangleBottomRight.Height);
							}
							else
							{
								result = Rectangle.Empty;
							}
						}
					}
				}
				return result;
			}
		}
		private void SetRegion()
		{
			this.DisplayingArea.Reset();
			this.DisplayingArea.AddRectangle(this.RectangleTopLeft);
			this.DisplayingArea.AddRectangle(this.RectangleTopRight);
			this.DisplayingArea.AddRectangle(this.RectangleBottomLeft);
			this.DisplayingArea.AddRectangle(this.RectangleBottomRight);
			this.DisplayingArea.AddRectangle(this.GetTabStripRectangle(DockState.DockTopAutoHide));
			this.DisplayingArea.AddRectangle(this.GetTabStripRectangle(DockState.DockBottomAutoHide));
			this.DisplayingArea.AddRectangle(this.GetTabStripRectangle(DockState.DockLeftAutoHide));
			this.DisplayingArea.AddRectangle(this.GetTabStripRectangle(DockState.DockRightAutoHide));
			base.Region = new Region(this.DisplayingArea);
		}
		protected override void OnMouseDown(MouseEventArgs e)
		{
			base.OnMouseDown(e);
			if (e.Button == MouseButtons.Left)
			{
				IDockContent dockContent = this.HitTest();
				if (dockContent != null)
				{
					dockContent.DockHandler.Activate();
				}
			}
		}
		protected override void OnMouseHover(EventArgs e)
		{
			base.OnMouseHover(e);
			IDockContent dockContent = this.HitTest();
			if (dockContent != null && this.DockPanel.ActiveAutoHideContent != dockContent)
			{
				this.DockPanel.ActiveAutoHideContent = dockContent;
			}
			base.ResetMouseEventArgs();
		}
		protected override void OnLayout(LayoutEventArgs levent)
		{
			this.RefreshChanges();
			base.OnLayout(levent);
		}
		internal void RefreshChanges()
		{
			if (!base.IsDisposed)
			{
				this.SetRegion();
				this.OnRefreshChanges();
			}
		}
		protected virtual void OnRefreshChanges()
		{
		}
		protected internal abstract int MeasureHeight();
		private IDockContent HitTest()
		{
			Point point = base.PointToClient(Control.MousePosition);
			return this.HitTest(point);
		}
		protected virtual AutoHideStripBase.Tab CreateTab(IDockContent content)
		{
			return new AutoHideStripBase.Tab(content);
		}
		protected virtual AutoHideStripBase.Pane CreatePane(DockPane dockPane)
		{
			return new AutoHideStripBase.Pane(dockPane);
		}
		protected abstract IDockContent HitTest(Point point);
	}
}
