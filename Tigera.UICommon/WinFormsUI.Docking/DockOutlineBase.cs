using System;
using System.Drawing;
using System.Windows.Forms;
namespace WinFormsUI.Docking
{
	internal abstract class DockOutlineBase
	{
		private Rectangle m_oldFloatWindowBounds;
		private Control m_oldDockTo;
		private DockStyle m_oldDock;
		private int m_oldContentIndex;
		private Rectangle m_floatWindowBounds;
		private Control m_dockTo;
		private DockStyle m_dock;
		private int m_contentIndex;
		private bool m_flagTestDrop = false;
		protected Rectangle OldFloatWindowBounds
		{
			get
			{
				return this.m_oldFloatWindowBounds;
			}
		}
		protected Control OldDockTo
		{
			get
			{
				return this.m_oldDockTo;
			}
		}
		protected DockStyle OldDock
		{
			get
			{
				return this.m_oldDock;
			}
		}
		protected int OldContentIndex
		{
			get
			{
				return this.m_oldContentIndex;
			}
		}
		protected bool SameAsOldValue
		{
			get
			{
				return this.FloatWindowBounds == this.OldFloatWindowBounds && this.DockTo == this.OldDockTo && this.Dock == this.OldDock && this.ContentIndex == this.OldContentIndex;
			}
		}
		public Rectangle FloatWindowBounds
		{
			get
			{
				return this.m_floatWindowBounds;
			}
		}
		public Control DockTo
		{
			get
			{
				return this.m_dockTo;
			}
		}
		public DockStyle Dock
		{
			get
			{
				return this.m_dock;
			}
		}
		public int ContentIndex
		{
			get
			{
				return this.m_contentIndex;
			}
		}
		public bool FlagFullEdge
		{
			get
			{
				return this.m_contentIndex != 0;
			}
		}
		public bool FlagTestDrop
		{
			get
			{
				return this.m_flagTestDrop;
			}
			set
			{
				this.m_flagTestDrop = value;
			}
		}
		public DockOutlineBase()
		{
			this.Init();
		}
		private void Init()
		{
			this.SetValues(Rectangle.Empty, null, DockStyle.None, -1);
			this.SaveOldValues();
		}
		private void SaveOldValues()
		{
			this.m_oldDockTo = this.m_dockTo;
			this.m_oldDock = this.m_dock;
			this.m_oldContentIndex = this.m_contentIndex;
			this.m_oldFloatWindowBounds = this.m_floatWindowBounds;
		}
		protected abstract void OnShow();
		protected abstract void OnClose();
		private void SetValues(Rectangle floatWindowBounds, Control dockTo, DockStyle dock, int contentIndex)
		{
			this.m_floatWindowBounds = floatWindowBounds;
			this.m_dockTo = dockTo;
			this.m_dock = dock;
			this.m_contentIndex = contentIndex;
			this.FlagTestDrop = true;
		}
		private void TestChange()
		{
			if (this.m_floatWindowBounds != this.m_oldFloatWindowBounds || this.m_dockTo != this.m_oldDockTo || this.m_dock != this.m_oldDock || this.m_contentIndex != this.m_oldContentIndex)
			{
				this.OnShow();
			}
		}
		public void Show()
		{
			this.SaveOldValues();
			this.SetValues(Rectangle.Empty, null, DockStyle.None, -1);
			this.TestChange();
		}
		public void Show(DockPane pane, DockStyle dock)
		{
			this.SaveOldValues();
			this.SetValues(Rectangle.Empty, pane, dock, -1);
			this.TestChange();
		}
		public void Show(DockPane pane, int contentIndex)
		{
			this.SaveOldValues();
			this.SetValues(Rectangle.Empty, pane, DockStyle.Fill, contentIndex);
			this.TestChange();
		}
		public void Show(DockPanel dockPanel, DockStyle dock, bool fullPanelEdge)
		{
			this.SaveOldValues();
			this.SetValues(Rectangle.Empty, dockPanel, dock, fullPanelEdge ? -1 : 0);
			this.TestChange();
		}
		public void Show(Rectangle floatWindowBounds)
		{
			this.SaveOldValues();
			this.SetValues(floatWindowBounds, null, DockStyle.None, -1);
			this.TestChange();
		}
		public void Close()
		{
			this.OnClose();
		}
	}
}
