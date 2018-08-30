using System;
using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Security.Permissions;
using System.Windows.Forms;
namespace WinFormsUI.Docking
{
	public abstract class DockPaneStripBase : Control
	{
		protected internal class Tab : IDisposable
		{
			private IDockContent m_content;
			public IDockContent Content
			{
				get
				{
					return this.m_content;
				}
			}
			public Form ContentForm
			{
				get
				{
					return this.m_content as Form;
				}
			}
			public Tab(IDockContent content)
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
		protected sealed class TabCollection : IEnumerable<DockPaneStripBase.Tab>, IEnumerable
		{
			private DockPane m_dockPane;
			public DockPane DockPane
			{
				get
				{
					return this.m_dockPane;
				}
			}
			public int Count
			{
				get
				{
					return this.DockPane.DisplayingContents.Count;
				}
			}
			public DockPaneStripBase.Tab this[int index]
			{
				get
				{
					IDockContent dockContent = this.DockPane.DisplayingContents[index];
					if (dockContent == null)
					{
						throw new ArgumentOutOfRangeException("index");
					}
					return dockContent.DockHandler.GetTab(this.DockPane.TabStripControl);
				}
			}
			IEnumerator<DockPaneStripBase.Tab> IEnumerable<DockPaneStripBase.Tab>.GetEnumerator()
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
			public bool Contains(DockPaneStripBase.Tab tab)
			{
				return this.IndexOf(tab) != -1;
			}
			public bool Contains(IDockContent content)
			{
				return this.IndexOf(content) != -1;
			}
			public int IndexOf(DockPaneStripBase.Tab tab)
			{
				int result;
				if (tab == null)
				{
					result = -1;
				}
				else
				{
					result = this.DockPane.DisplayingContents.IndexOf(tab.Content);
				}
				return result;
			}
			public int IndexOf(IDockContent content)
			{
				return this.DockPane.DisplayingContents.IndexOf(content);
			}
		}
		private DockPane m_dockPane;
		private DockPaneStripBase.TabCollection m_tabs = null;
		protected DockPane DockPane
		{
			get
			{
				return this.m_dockPane;
			}
		}
		protected DockPane.AppearanceStyle Appearance
		{
			get
			{
				return this.DockPane.Appearance;
			}
		}
		protected DockPaneStripBase.TabCollection Tabs
		{
			get
			{
				if (this.m_tabs == null)
				{
					this.m_tabs = new DockPaneStripBase.TabCollection(this.DockPane);
				}
				return this.m_tabs;
			}
		}
		protected bool HasTabPageContextMenu
		{
			get
			{
				return this.DockPane.HasTabPageContextMenu;
			}
		}
		protected DockPaneStripBase(DockPane pane)
		{
			this.m_dockPane = pane;
			base.SetStyle(ControlStyles.OptimizedDoubleBuffer, true);
			base.SetStyle(ControlStyles.Selectable, false);
			this.AllowDrop = true;
		}
		internal void RefreshChanges()
		{
			if (!base.IsDisposed)
			{
				this.OnRefreshChanges();
			}
		}
		protected virtual void OnRefreshChanges()
		{
		}
		protected internal abstract int MeasureHeight();
		protected internal abstract void EnsureTabVisible(IDockContent content);
		protected int HitTest()
		{
			return this.HitTest(base.PointToClient(Control.MousePosition));
		}
		protected internal abstract int HitTest(Point point);
		protected internal abstract GraphicsPath GetOutline(int index);
		protected internal virtual DockPaneStripBase.Tab CreateTab(IDockContent content)
		{
			return new DockPaneStripBase.Tab(content);
		}
		protected override void OnMouseDown(MouseEventArgs e)
		{
			base.OnMouseDown(e);
			int num = this.HitTest();
			if (num != -1)
			{
				IDockContent content = this.Tabs[num].Content;
				if (this.DockPane.ActiveContent != content)
				{
					this.DockPane.ActiveContent = content;
				}
			}
			if (e.Button == MouseButtons.Left)
			{
				if (this.DockPane.DockPanel.AllowEndUserDocking && this.DockPane.AllowDockDragAndDrop && this.DockPane.ActiveContent.DockHandler.AllowEndUserDocking)
				{
					this.DockPane.DockPanel.BeginDrag(this.DockPane.ActiveContent.DockHandler);
				}
			}
		}
		protected void ShowTabPageContextMenu(Point position)
		{
			this.DockPane.ShowTabPageContextMenu(this, position);
		}
		protected override void OnMouseUp(MouseEventArgs e)
		{
			base.OnMouseUp(e);
			if (e.Button == MouseButtons.Right)
			{
				this.ShowTabPageContextMenu(new Point(e.X, e.Y));
			}
			else
			{
				if (e.Button == MouseButtons.Middle && this.DockPane.Appearance == DockPane.AppearanceStyle.Document)
				{
					int num = this.HitTest();
					if (num != -1)
					{
						IDockContent content = this.Tabs[num].Content;
						this.DockPane.CloseContent(content);
					}
				}
			}
		}
		[SecurityPermission(SecurityAction.LinkDemand, Flags = SecurityPermissionFlag.UnmanagedCode)]
		protected override void WndProc(ref Message m)
		{
			if (m.Msg == 515)
			{
				base.WndProc(ref m);
				int num = this.HitTest();
				if (this.DockPane.DockPanel.AllowEndUserDocking && this.DockPane.AllowDockDragAndDrop && this.DockPane.ActiveContent.DockHandler.AllowEndUserDocking && num != -1)
				{
					IDockContent content = this.Tabs[num].Content;
					if (content.DockHandler.CheckDockState(!content.DockHandler.IsFloat) != DockState.Unknown)
					{
						content.DockHandler.IsFloat = !content.DockHandler.IsFloat;
					}
				}
			}
			else
			{
				base.WndProc(ref m);
			}
		}
		protected override void OnDragOver(DragEventArgs drgevent)
		{
			base.OnDragOver(drgevent);
			int num = this.HitTest();
			if (num != -1)
			{
				IDockContent content = this.Tabs[num].Content;
				if (this.DockPane.ActiveContent != content)
				{
					this.DockPane.ActiveContent = content;
				}
			}
		}
	}
}
