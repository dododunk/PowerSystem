using System;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.Security.Permissions;
using System.Threading;
using System.Windows.Forms;
namespace WinFormsUI.Docking
{
	[ToolboxItem(false)]
	public class DockPane : UserControl, IDockDragSource, IDragSource
	{
		public enum AppearanceStyle
		{
			ToolWindow,
			Document
		}
		private enum HitTestArea
		{
			Caption,
			TabStrip,
			Content,
			None
		}
		private struct HitTestResult
		{
			public DockPane.HitTestArea HitArea;
			public int Index;
			public HitTestResult(DockPane.HitTestArea hitTestArea, int index)
			{
				this.HitArea = hitTestArea;
				this.Index = index;
			}
		}
		private class SplitterControl : Control, ISplitterDragSource, IDragSource
		{
			private DockPane m_pane;
			private DockAlignment m_alignment;
			public DockPane DockPane
			{
				get
				{
					return this.m_pane;
				}
			}
			public DockAlignment Alignment
			{
				get
				{
					return this.m_alignment;
				}
				set
				{
					this.m_alignment = value;
					if (this.m_alignment == DockAlignment.Left || this.m_alignment == DockAlignment.Right)
					{
						this.Cursor = Cursors.VSplit;
					}
					else
					{
						if (this.m_alignment == DockAlignment.Top || this.m_alignment == DockAlignment.Bottom)
						{
							this.Cursor = Cursors.HSplit;
						}
						else
						{
							this.Cursor = Cursors.Default;
						}
					}
					if (this.DockPane.DockState == DockState.Document)
					{
						base.Invalidate();
					}
				}
			}
			bool ISplitterDragSource.IsVertical
			{
				get
				{
					NestedDockingStatus nestedDockingStatus = this.DockPane.NestedDockingStatus;
					return nestedDockingStatus.DisplayingAlignment == DockAlignment.Left || nestedDockingStatus.DisplayingAlignment == DockAlignment.Right;
				}
			}
			Rectangle ISplitterDragSource.DragLimitBounds
			{
				get
				{
					NestedDockingStatus nestedDockingStatus = this.DockPane.NestedDockingStatus;
					Rectangle result = base.Parent.RectangleToScreen(nestedDockingStatus.LogicalBounds);
					checked
					{
						if (((ISplitterDragSource)this).IsVertical)
						{
							result.X += 24;
							result.Width -= 48;
						}
						else
						{
							result.Y += 24;
							result.Height -= 48;
						}
						return result;
					}
				}
			}
			Control IDragSource.DragControl
			{
				get
				{
					return this;
				}
			}
			public SplitterControl(DockPane pane)
			{
				base.SetStyle(ControlStyles.Selectable, false);
				this.m_pane = pane;
			}
			protected override void OnPaint(PaintEventArgs e)
			{
				base.OnPaint(e);
				checked
				{
					if (this.DockPane.DockState == DockState.Document)
					{
						Graphics graphics = e.Graphics;
						Rectangle clientRectangle = base.ClientRectangle;
						if (this.Alignment == DockAlignment.Top || this.Alignment == DockAlignment.Bottom)
						{
							graphics.DrawLine(SystemPens.ControlDark, clientRectangle.Left, clientRectangle.Bottom - 1, clientRectangle.Right, clientRectangle.Bottom - 1);
						}
						else
						{
							if (this.Alignment == DockAlignment.Left || this.Alignment == DockAlignment.Right)
							{
								graphics.DrawLine(SystemPens.ControlDarkDark, clientRectangle.Right - 1, clientRectangle.Top, clientRectangle.Right - 1, clientRectangle.Bottom);
							}
						}
					}
				}
			}
			protected override void OnMouseDown(MouseEventArgs e)
			{
				base.OnMouseDown(e);
				if (e.Button == MouseButtons.Left)
				{
					this.DockPane.DockPanel.BeginDrag(this, base.Parent.RectangleToScreen(base.Bounds));
				}
			}
			void ISplitterDragSource.BeginDrag(Rectangle rectSplitter)
			{
			}
			void ISplitterDragSource.EndDrag()
			{
			}
			void ISplitterDragSource.MoveSplitter(int offset)
			{
				NestedDockingStatus nestedDockingStatus = this.DockPane.NestedDockingStatus;
				double num = nestedDockingStatus.Proportion;
				if (nestedDockingStatus.LogicalBounds.Width > 0 && nestedDockingStatus.LogicalBounds.Height > 0)
				{
					if (nestedDockingStatus.DisplayingAlignment == DockAlignment.Left)
					{
						num += (double)offset / (double)nestedDockingStatus.LogicalBounds.Width;
					}
					else
					{
						if (nestedDockingStatus.DisplayingAlignment == DockAlignment.Right)
						{
							num -= (double)offset / (double)nestedDockingStatus.LogicalBounds.Width;
						}
						else
						{
							if (nestedDockingStatus.DisplayingAlignment == DockAlignment.Top)
							{
								num += (double)offset / (double)nestedDockingStatus.LogicalBounds.Height;
							}
							else
							{
								num -= (double)offset / (double)nestedDockingStatus.LogicalBounds.Height;
							}
						}
					}
					this.DockPane.SetNestedDockingProportion(num);
				}
			}
		}
		private DockPaneCaptionBase m_captionControl;
		private DockPaneStripBase m_tabStripControl;
		private IDockContent m_activeContent = null;
		private bool m_allowDockDragAndDrop = true;
		private IDisposable m_autoHidePane = null;
		private object m_autoHideTabs = null;
		private DockContentCollection m_contents;
		private DockContentCollection m_displayingContents;
		private DockPanel m_dockPanel;
		private bool m_isActivated = false;
		private bool m_isActiveDocumentPane = false;
		private bool m_isHidden = true;
		private static readonly object DockStateChangedEvent = new object();
		private static readonly object IsActivatedChangedEvent = new object();
		private static readonly object IsActiveDocumentPaneChangedEvent = new object();
		private NestedDockingStatus m_nestedDockingStatus;
		private bool m_isFloat;
		private DockState m_dockState = DockState.Unknown;
		private int m_countRefreshStateChange = 0;
		private DockPane.SplitterControl m_splitter;
		public event EventHandler DockStateChanged
		{
			add
			{
				base.Events.AddHandler(DockPane.DockStateChangedEvent, value);
			}
			remove
			{
				base.Events.RemoveHandler(DockPane.DockStateChangedEvent, value);
			}
		}
		public event EventHandler IsActivatedChanged
		{
			add
			{
				base.Events.AddHandler(DockPane.IsActivatedChangedEvent, value);
			}
			remove
			{
				base.Events.RemoveHandler(DockPane.IsActivatedChangedEvent, value);
			}
		}
		public event EventHandler IsActiveDocumentPaneChanged
		{
			add
			{
				base.Events.AddHandler(DockPane.IsActiveDocumentPaneChangedEvent, value);
			}
			remove
			{
				base.Events.RemoveHandler(DockPane.IsActiveDocumentPaneChangedEvent, value);
			}
		}
		private DockPaneCaptionBase CaptionControl
		{
			get
			{
				return this.m_captionControl;
			}
		}
		internal DockPaneStripBase TabStripControl
		{
			get
			{
				return this.m_tabStripControl;
			}
		}
		public virtual IDockContent ActiveContent
		{
			get
			{
				return this.m_activeContent;
			}
			set
			{
				if (this.ActiveContent != value)
				{
					if (value != null)
					{
						if (!this.DisplayingContents.Contains(value))
						{
							throw new InvalidOperationException(Strings.DockPane_ActiveContent_InvalidValue);
						}
					}
					else
					{
						if (this.DisplayingContents.Count != 0)
						{
							throw new InvalidOperationException(Strings.DockPane_ActiveContent_InvalidValue);
						}
					}
					IDockContent activeContent = this.m_activeContent;
					if (this.DockPanel.ActiveAutoHideContent == activeContent)
					{
						this.DockPanel.ActiveAutoHideContent = null;
					}
					this.m_activeContent = value;
					if (this.DockPanel.DocumentStyle == DocumentStyle.DockingMdi && this.DockState == DockState.Document)
					{
						if (this.m_activeContent != null)
						{
							this.m_activeContent.DockHandler.Form.BringToFront();
						}
					}
					else
					{
						if (this.m_activeContent != null)
						{
							this.m_activeContent.DockHandler.SetVisible();
						}
						if (activeContent != null && this.DisplayingContents.Contains(activeContent))
						{
							activeContent.DockHandler.SetVisible();
						}
						if (this.IsActivated && this.m_activeContent != null)
						{
							this.m_activeContent.DockHandler.Activate();
						}
					}
					if (this.FloatWindow != null)
					{
						this.FloatWindow.SetText();
					}
					if (this.DockPanel.DocumentStyle == DocumentStyle.DockingMdi && this.DockState == DockState.Document)
					{
						this.RefreshChanges(false);
					}
					else
					{
						this.RefreshChanges();
					}
					if (this.m_activeContent != null)
					{
						this.TabStripControl.EnsureTabVisible(this.m_activeContent);
					}
				}
			}
		}
		public virtual bool AllowDockDragAndDrop
		{
			get
			{
				return this.m_allowDockDragAndDrop;
			}
			set
			{
				this.m_allowDockDragAndDrop = value;
			}
		}
		internal IDisposable AutoHidePane
		{
			get
			{
				return this.m_autoHidePane;
			}
			set
			{
				this.m_autoHidePane = value;
			}
		}
		internal object AutoHideTabs
		{
			get
			{
				return this.m_autoHideTabs;
			}
			set
			{
				this.m_autoHideTabs = value;
			}
		}
		private object TabPageContextMenu
		{
			get
			{
				IDockContent activeContent = this.ActiveContent;
				object result;
				if (activeContent == null)
				{
					result = null;
				}
				else
				{
					if (activeContent.DockHandler.TabPageContextMenuStrip != null)
					{
						result = activeContent.DockHandler.TabPageContextMenuStrip;
					}
					else
					{
						if (activeContent.DockHandler.TabPageContextMenu != null)
						{
							result = activeContent.DockHandler.TabPageContextMenu;
						}
						else
						{
							result = null;
						}
					}
				}
				return result;
			}
		}
		internal bool HasTabPageContextMenu
		{
			get
			{
				return this.TabPageContextMenu != null;
			}
		}
		private Rectangle CaptionRectangle
		{
			get
			{
				Rectangle result;
				if (!this.HasCaption)
				{
					result = Rectangle.Empty;
				}
				else
				{
					Rectangle displayingRectangle = this.DisplayingRectangle;
					int x = displayingRectangle.X;
					int y = displayingRectangle.Y;
					int width = displayingRectangle.Width;
					int height = this.CaptionControl.MeasureHeight();
					result = new Rectangle(x, y, width, height);
				}
				return result;
			}
		}
		internal Rectangle ContentRectangle
		{
			get
			{
				Rectangle displayingRectangle = this.DisplayingRectangle;
				Rectangle captionRectangle = this.CaptionRectangle;
				Rectangle tabStripRectangle = this.TabStripRectangle;
				int x = displayingRectangle.X;
				checked
				{
					int num = displayingRectangle.Y + (captionRectangle.IsEmpty ? 0 : captionRectangle.Height);
					if (this.DockState == DockState.Document && this.DockPanel.DocumentTabStripLocation == DocumentTabStripLocation.Top)
					{
						num += tabStripRectangle.Height;
					}
					int width = displayingRectangle.Width;
					int height = displayingRectangle.Height - captionRectangle.Height - tabStripRectangle.Height;
					return new Rectangle(x, num, width, height);
				}
			}
		}
		internal Rectangle TabStripRectangle
		{
			get
			{
				Rectangle result;
				if (this.Appearance == DockPane.AppearanceStyle.ToolWindow)
				{
					result = this.TabStripRectangle_ToolWindow;
				}
				else
				{
					result = this.TabStripRectangle_Document;
				}
				return result;
			}
		}
		private Rectangle TabStripRectangle_ToolWindow
		{
			get
			{
				checked
				{
					Rectangle result;
					if (this.DisplayingContents.Count <= 1 || this.IsAutoHide)
					{
						result = Rectangle.Empty;
					}
					else
					{
						Rectangle displayingRectangle = this.DisplayingRectangle;
						int width = displayingRectangle.Width;
						int num = this.TabStripControl.MeasureHeight();
						int x = displayingRectangle.X;
						int y = displayingRectangle.Bottom - num;
						Rectangle captionRectangle = this.CaptionRectangle;
						if (captionRectangle.Contains(x, y))
						{
							y = captionRectangle.Y + captionRectangle.Height;
						}
						result = new Rectangle(x, y, width, num);
					}
					return result;
				}
			}
		}
		private Rectangle TabStripRectangle_Document
		{
			get
			{
				Rectangle result;
				if (this.DisplayingContents.Count == 0)
				{
					result = Rectangle.Empty;
				}
				else
				{
					if (this.DisplayingContents.Count == 1 && this.DockPanel.DocumentStyle == DocumentStyle.DockingSdi)
					{
						result = Rectangle.Empty;
					}
					else
					{
						Rectangle displayingRectangle = this.DisplayingRectangle;
						int x = displayingRectangle.X;
						int width = displayingRectangle.Width;
						int num = this.TabStripControl.MeasureHeight();
						int y;
						if (this.DockPanel.DocumentTabStripLocation == DocumentTabStripLocation.Bottom)
						{
							y = checked(displayingRectangle.Height - num);
						}
						else
						{
							y = displayingRectangle.Y;
						}
						result = new Rectangle(x, y, width, num);
					}
				}
				return result;
			}
		}
		public virtual string CaptionText
		{
			get
			{
				return (this.ActiveContent == null) ? string.Empty : this.ActiveContent.DockHandler.TabText;
			}
		}
		public DockContentCollection Contents
		{
			get
			{
				return this.m_contents;
			}
		}
		public DockContentCollection DisplayingContents
		{
			get
			{
				return this.m_displayingContents;
			}
		}
		public DockPanel DockPanel
		{
			get
			{
				return this.m_dockPanel;
			}
		}
		private bool HasCaption
		{
			get
			{
				return this.DockState != DockState.Document && this.DockState != DockState.Hidden && this.DockState != DockState.Unknown && (this.DockState != DockState.Float || this.FloatWindow.VisibleNestedPanes.Count > 1);
			}
		}
		public bool IsActivated
		{
			get
			{
				return this.m_isActivated;
			}
		}
		public bool IsActiveDocumentPane
		{
			get
			{
				return this.m_isActiveDocumentPane;
			}
		}
		public bool IsAutoHide
		{
			get
			{
				return DockHelper.IsDockStateAutoHide(this.DockState);
			}
		}
		public DockPane.AppearanceStyle Appearance
		{
			get
			{
				return (this.DockState == DockState.Document) ? DockPane.AppearanceStyle.Document : DockPane.AppearanceStyle.ToolWindow;
			}
		}
		internal Rectangle DisplayingRectangle
		{
			get
			{
				return base.ClientRectangle;
			}
		}
		public bool IsHidden
		{
			get
			{
				return this.m_isHidden;
			}
		}
		public DockWindow DockWindow
		{
			get
			{
				return (this.m_nestedDockingStatus.NestedPanes == null) ? null : (this.m_nestedDockingStatus.NestedPanes.Container as DockWindow);
			}
			set
			{
				DockWindow dockWindow = this.DockWindow;
				if (dockWindow != value)
				{
					this.DockTo(value);
				}
			}
		}
		public FloatWindow FloatWindow
		{
			get
			{
				return (this.m_nestedDockingStatus.NestedPanes == null) ? null : (this.m_nestedDockingStatus.NestedPanes.Container as FloatWindow);
			}
			set
			{
				FloatWindow floatWindow = this.FloatWindow;
				if (floatWindow != value)
				{
					this.DockTo(value);
				}
			}
		}
		public NestedDockingStatus NestedDockingStatus
		{
			get
			{
				return this.m_nestedDockingStatus;
			}
		}
		public bool IsFloat
		{
			get
			{
				return this.m_isFloat;
			}
		}
		public INestedPanesContainer NestedPanesContainer
		{
			get
			{
				INestedPanesContainer result;
				if (this.NestedDockingStatus.NestedPanes == null)
				{
					result = null;
				}
				else
				{
					result = this.NestedDockingStatus.NestedPanes.Container;
				}
				return result;
			}
		}
		public DockState DockState
		{
			get
			{
				return this.m_dockState;
			}
			set
			{
				this.SetDockState(value);
			}
		}
		private bool IsRefreshStateChangeSuspended
		{
			get
			{
				return this.m_countRefreshStateChange != 0;
			}
		}
		Control IDragSource.DragControl
		{
			get
			{
				return this;
			}
		}
		private DockPane.SplitterControl Splitter
		{
			get
			{
				return this.m_splitter;
			}
		}
		internal Rectangle SplitterBounds
		{
			set
			{
				this.Splitter.Bounds = value;
			}
		}
		internal DockAlignment SplitterAlignment
		{
			set
			{
				this.Splitter.Alignment = value;
			}
		}
		protected internal DockPane(IDockContent content, DockState visibleState, bool show)
		{
			this.InternalConstruct(content, visibleState, false, Rectangle.Empty, null, DockAlignment.Right, 0.5, show);
		}
		protected internal DockPane(IDockContent content, FloatWindow floatWindow, bool show)
		{
			if (floatWindow == null)
			{
				throw new ArgumentNullException("floatWindow");
			}
			this.InternalConstruct(content, DockState.Float, false, Rectangle.Empty, floatWindow.NestedPanes.GetDefaultPreviousPane(this), DockAlignment.Right, 0.5, show);
		}
		protected internal DockPane(IDockContent content, DockPane previousPane, DockAlignment alignment, double proportion, bool show)
		{
			if (previousPane == null)
			{
				throw new ArgumentNullException("previousPane");
			}
			this.InternalConstruct(content, previousPane.DockState, false, Rectangle.Empty, previousPane, alignment, proportion, show);
		}
		protected internal DockPane(IDockContent content, Rectangle floatWindowBounds, bool show)
		{
			this.InternalConstruct(content, DockState.Float, true, floatWindowBounds, null, DockAlignment.Right, 0.5, show);
		}
		private void InternalConstruct(IDockContent content, DockState dockState, bool flagBounds, Rectangle floatWindowBounds, DockPane prevPane, DockAlignment alignment, double proportion, bool show)
		{
			if (dockState == DockState.Hidden || dockState == DockState.Unknown)
			{
				throw new ArgumentException(Strings.DockPane_SetDockState_InvalidState);
			}
			if (content == null)
			{
				throw new ArgumentNullException(Strings.DockPane_Constructor_NullContent);
			}
			if (content.DockHandler.DockPanel == null)
			{
				throw new ArgumentException(Strings.DockPane_Constructor_NullDockPanel);
			}
			base.SuspendLayout();
			base.SetStyle(ControlStyles.Selectable, false);
			this.m_isFloat = (dockState == DockState.Float);
			this.m_contents = new DockContentCollection();
			this.m_displayingContents = new DockContentCollection(this);
			this.m_dockPanel = content.DockHandler.DockPanel;
			this.m_dockPanel.AddPane(this);
			this.m_splitter = new DockPane.SplitterControl(this);
			this.m_nestedDockingStatus = new NestedDockingStatus(this);
			this.m_captionControl = this.DockPanel.DockPaneCaptionFactory.CreateDockPaneCaption(this);
			this.m_tabStripControl = this.DockPanel.DockPaneStripFactory.CreateDockPaneStrip(this);
			base.Controls.AddRange(new Control[]
			{
				this.m_captionControl,
				this.m_tabStripControl
			});
			this.DockPanel.SuspendLayout(true);
			if (flagBounds)
			{
				this.FloatWindow = this.DockPanel.FloatWindowFactory.CreateFloatWindow(this.DockPanel, this, floatWindowBounds);
			}
			else
			{
				if (prevPane != null)
				{
					this.DockTo(prevPane.NestedPanesContainer, prevPane, alignment, proportion);
				}
			}
			this.SetDockState(dockState);
			if (show)
			{
				content.DockHandler.Pane = this;
			}
			else
			{
				if (this.IsFloat)
				{
					content.DockHandler.FloatPane = this;
				}
				else
				{
					content.DockHandler.PanelPane = this;
				}
			}
			base.ResumeLayout();
			this.DockPanel.ResumeLayout(true, true);
		}
		protected override void Dispose(bool disposing)
		{
			if (disposing)
			{
				this.m_dockState = DockState.Unknown;
				if (this.NestedPanesContainer != null)
				{
					this.NestedPanesContainer.NestedPanes.Remove(this);
				}
				if (this.DockPanel != null)
				{
					this.DockPanel.RemovePane(this);
					this.m_dockPanel = null;
				}
				this.Splitter.Dispose();
				if (this.m_autoHidePane != null)
				{
					this.m_autoHidePane.Dispose();
				}
			}
			base.Dispose(disposing);
		}
		internal void ShowTabPageContextMenu(Control control, Point position)
		{
			object tabPageContextMenu = this.TabPageContextMenu;
			if (tabPageContextMenu != null)
			{
				ContextMenuStrip contextMenuStrip = tabPageContextMenu as ContextMenuStrip;
				if (contextMenuStrip != null)
				{
					contextMenuStrip.Show(control, position);
				}
				else
				{
					ContextMenu contextMenu = tabPageContextMenu as ContextMenu;
					if (contextMenu != null)
					{
						contextMenu.Show(this, position);
					}
				}
			}
		}
		internal void SetIsActivated(bool value)
		{
			if (this.m_isActivated != value)
			{
				this.m_isActivated = value;
				if (this.DockState != DockState.Document)
				{
					this.RefreshChanges(false);
				}
				this.OnIsActivatedChanged(EventArgs.Empty);
			}
		}
		internal void SetIsActiveDocumentPane(bool value)
		{
			if (this.m_isActiveDocumentPane != value)
			{
				this.m_isActiveDocumentPane = value;
				if (this.DockState == DockState.Document)
				{
					this.RefreshChanges();
				}
				this.OnIsActiveDocumentPaneChanged(EventArgs.Empty);
			}
		}
		public bool IsDockStateValid(DockState dockState)
		{
			bool result;
			foreach (IDockContent current in this.Contents)
			{
				if (!current.DockHandler.IsDockStateValid(dockState))
				{
					result = false;
					return result;
				}
			}
			result = true;
			return result;
		}
		public void Activate()
		{
			if (DockHelper.IsDockStateAutoHide(this.DockState) && this.DockPanel.ActiveAutoHideContent != this.ActiveContent)
			{
				this.DockPanel.ActiveAutoHideContent = this.ActiveContent;
			}
			else
			{
				if (!this.IsActivated && this.ActiveContent != null)
				{
					this.ActiveContent.DockHandler.Activate();
				}
			}
		}
		internal void AddContent(IDockContent content)
		{
			if (!this.Contents.Contains(content))
			{
				this.Contents.Add(content);
			}
		}
		internal void Close()
		{
			base.Dispose();
		}
		public void CloseActiveContent()
		{
			this.CloseContent(this.ActiveContent);
		}
		internal void CloseContent(IDockContent content)
		{
			DockPanel dockPanel = this.DockPanel;
			if (content != null)
			{
				if (content.DockHandler.CloseButton)
				{
					dockPanel.SuspendLayout(true);
					try
					{
						if (content.DockHandler.HideOnClose)
						{
							content.DockHandler.Hide();
							this.NestedDockingStatus.NestedPanes.SwitchPaneWithFirstChild(this);
						}
						else
						{
							content.DockHandler.Close();
						}
					}
					finally
					{
						dockPanel.ResumeLayout(true, true);
					}
				}
			}
		}
		private DockPane.HitTestResult GetHitTest(Point ptMouse)
		{
			Point pt = base.PointToClient(ptMouse);
			DockPane.HitTestResult result;
			if (this.CaptionRectangle.Contains(pt))
			{
				result = new DockPane.HitTestResult(DockPane.HitTestArea.Caption, -1);
			}
			else
			{
				if (this.ContentRectangle.Contains(pt))
				{
					result = new DockPane.HitTestResult(DockPane.HitTestArea.Content, -1);
				}
				else
				{
					if (this.TabStripRectangle.Contains(pt))
					{
						result = new DockPane.HitTestResult(DockPane.HitTestArea.TabStrip, this.TabStripControl.HitTest(this.TabStripControl.PointToClient(ptMouse)));
					}
					else
					{
						result = new DockPane.HitTestResult(DockPane.HitTestArea.None, -1);
					}
				}
			}
			return result;
		}
		private void SetIsHidden(bool value)
		{
			if (this.m_isHidden != value)
			{
				this.m_isHidden = value;
				if (DockHelper.IsDockStateAutoHide(this.DockState))
				{
					this.DockPanel.RefreshAutoHideStrip();
					this.DockPanel.PerformLayout();
				}
				else
				{
					if (this.NestedPanesContainer != null)
					{
						((Control)this.NestedPanesContainer).PerformLayout();
					}
				}
			}
		}
		protected override void OnLayout(LayoutEventArgs levent)
		{
			this.SetIsHidden(this.DisplayingContents.Count == 0);
			if (!this.IsHidden)
			{
				this.CaptionControl.Bounds = this.CaptionRectangle;
				this.TabStripControl.Bounds = this.TabStripRectangle;
				this.SetContentBounds();
				foreach (IDockContent current in this.Contents)
				{
					if (this.DisplayingContents.Contains(current) && current.DockHandler.FlagClipWindow && current.DockHandler.Form.Visible)
					{
						current.DockHandler.FlagClipWindow = false;
					}
				}
			}
			base.OnLayout(levent);
		}
		internal void SetContentBounds()
		{
			Rectangle rectangle = this.ContentRectangle;
			if (this.DockState == DockState.Document && this.DockPanel.DocumentStyle == DocumentStyle.DockingMdi)
			{
				rectangle = this.DockPanel.RectangleToMdiClient(base.RectangleToScreen(rectangle));
			}
			Rectangle bounds = new Rectangle(checked(0 - rectangle.Width), rectangle.Y, rectangle.Width, rectangle.Height);
			foreach (IDockContent current in this.Contents)
			{
				if (current.DockHandler.Pane == this)
				{
					if (current == this.ActiveContent)
					{
						current.DockHandler.Form.Bounds = rectangle;
					}
					else
					{
						current.DockHandler.Form.Bounds = bounds;
					}
				}
			}
		}
		internal void RefreshChanges()
		{
			this.RefreshChanges(true);
		}
		private void RefreshChanges(bool performLayout)
		{
			if (!base.IsDisposed)
			{
				this.CaptionControl.RefreshChanges();
				this.TabStripControl.RefreshChanges();
				if (this.DockState == DockState.Float && this.FloatWindow != null)
				{
					this.FloatWindow.RefreshChanges();
				}
				if (DockHelper.IsDockStateAutoHide(this.DockState) && this.DockPanel != null)
				{
					this.DockPanel.RefreshAutoHideStrip();
					this.DockPanel.PerformLayout();
				}
				if (performLayout)
				{
					base.PerformLayout();
				}
			}
		}
		internal void RemoveContent(IDockContent content)
		{
			if (this.Contents.Contains(content))
			{
				this.Contents.Remove(content);
			}
		}
		public void SetContentIndex(IDockContent content, int index)
		{
			int num = this.Contents.IndexOf(content);
			if (num == -1)
			{
				throw new ArgumentException(Strings.DockPane_SetContentIndex_InvalidContent);
			}
			checked
			{
				if ((index < 0 || index > this.Contents.Count - 1) && index != -1)
				{
					throw new ArgumentOutOfRangeException(Strings.DockPane_SetContentIndex_InvalidIndex);
				}
				if (num != index)
				{
					if (num != this.Contents.Count - 1 || index != -1)
					{
						this.Contents.Remove(content);
						if (index == -1)
						{
							this.Contents.Add(content);
						}
						else
						{
							if (num < index)
							{
								this.Contents.AddAt(content, index - 1);
							}
							else
							{
								this.Contents.AddAt(content, index);
							}
						}
						this.RefreshChanges();
					}
				}
			}
		}
		private void SetParent()
		{
			if (this.DockState == DockState.Unknown || this.DockState == DockState.Hidden)
			{
				this.SetParent(null);
				this.Splitter.Parent = null;
			}
			else
			{
				if (this.DockState == DockState.Float)
				{
					this.SetParent(this.FloatWindow);
					this.Splitter.Parent = this.FloatWindow;
				}
				else
				{
					if (DockHelper.IsDockStateAutoHide(this.DockState))
					{
						this.SetParent(this.DockPanel.AutoHideControl);
						this.Splitter.Parent = null;
					}
					else
					{
						this.SetParent(this.DockPanel.DockWindows[this.DockState]);
						this.Splitter.Parent = base.Parent;
					}
				}
			}
		}
		private void SetParent(Control value)
		{
			if (base.Parent != value)
			{
				IDockContent focusedContent = this.GetFocusedContent();
				if (focusedContent != null)
				{
					this.DockPanel.SaveFocus();
				}
				base.Parent = value;
				if (focusedContent != null)
				{
					focusedContent.DockHandler.Activate();
				}
			}
		}
		public new void Show()
		{
			this.Activate();
		}
		internal void TestDrop(IDockDragSource dragSource, DockOutlineBase dockOutline)
		{
			if (dragSource.CanDockTo(this))
			{
				Point mousePosition = Control.MousePosition;
				DockPane.HitTestResult hitTest = this.GetHitTest(mousePosition);
				if (hitTest.HitArea == DockPane.HitTestArea.Caption)
				{
					dockOutline.Show(this, -1);
				}
				else
				{
					if (hitTest.HitArea == DockPane.HitTestArea.TabStrip && hitTest.Index != -1)
					{
						dockOutline.Show(this, hitTest.Index);
					}
				}
			}
		}
		internal void ValidateActiveContent()
		{
			checked
			{
				if (this.ActiveContent == null)
				{
					if (this.DisplayingContents.Count != 0)
					{
						this.ActiveContent = this.DisplayingContents[0];
					}
				}
				else
				{
					if (this.DisplayingContents.IndexOf(this.ActiveContent) < 0)
					{
						IDockContent dockContent = null;
						for (int i = this.Contents.IndexOf(this.ActiveContent) - 1; i >= 0; i--)
						{
							if (this.Contents[i].DockHandler.DockState == this.DockState)
							{
								dockContent = this.Contents[i];
								break;
							}
						}
						IDockContent dockContent2 = null;
						for (int i = this.Contents.IndexOf(this.ActiveContent) + 1; i < this.Contents.Count; i++)
						{
							if (this.Contents[i].DockHandler.DockState == this.DockState)
							{
								dockContent2 = this.Contents[i];
								break;
							}
						}
						if (dockContent != null)
						{
							this.ActiveContent = dockContent;
						}
						else
						{
							if (dockContent2 != null)
							{
								this.ActiveContent = dockContent2;
							}
							else
							{
								this.ActiveContent = null;
							}
						}
					}
				}
			}
		}
		protected virtual void OnDockStateChanged(EventArgs e)
		{
			EventHandler eventHandler = (EventHandler)base.Events[DockPane.DockStateChangedEvent];
			if (eventHandler != null)
			{
				eventHandler(this, e);
			}
		}
		protected virtual void OnIsActivatedChanged(EventArgs e)
		{
			EventHandler eventHandler = (EventHandler)base.Events[DockPane.IsActivatedChangedEvent];
			if (eventHandler != null)
			{
				eventHandler(this, e);
			}
		}
		protected virtual void OnIsActiveDocumentPaneChanged(EventArgs e)
		{
			EventHandler eventHandler = (EventHandler)base.Events[DockPane.IsActiveDocumentPaneChangedEvent];
			if (eventHandler != null)
			{
				eventHandler(this, e);
			}
		}
		public DockPane SetDockState(DockState value)
		{
			if (value == DockState.Unknown || value == DockState.Hidden)
			{
				throw new InvalidOperationException(Strings.DockPane_SetDockState_InvalidState);
			}
			checked
			{
				DockPane result;
				if (value == DockState.Float == this.IsFloat)
				{
					this.InternalSetDockState(value);
					result = this;
				}
				else
				{
					if (this.DisplayingContents.Count == 0)
					{
						result = null;
					}
					else
					{
						IDockContent dockContent = null;
						for (int i = 0; i < this.DisplayingContents.Count; i++)
						{
							IDockContent dockContent2 = this.DisplayingContents[i];
							if (dockContent2.DockHandler.IsDockStateValid(value))
							{
								dockContent = dockContent2;
								break;
							}
						}
						if (dockContent == null)
						{
							result = null;
						}
						else
						{
							dockContent.DockHandler.DockState = value;
							DockPane pane = dockContent.DockHandler.Pane;
							this.DockPanel.SuspendLayout(true);
							for (int i = 0; i < this.DisplayingContents.Count; i++)
							{
								IDockContent dockContent2 = this.DisplayingContents[i];
								if (dockContent2.DockHandler.IsDockStateValid(value))
								{
									dockContent2.DockHandler.Pane = pane;
								}
							}
							this.DockPanel.ResumeLayout(true, true);
							result = pane;
						}
					}
				}
				return result;
			}
		}
		private void InternalSetDockState(DockState value)
		{
			if (this.m_dockState != value)
			{
				DockState dockState = this.m_dockState;
				INestedPanesContainer nestedPanesContainer = this.NestedPanesContainer;
				this.m_dockState = value;
				this.SuspendRefreshStateChange();
				IDockContent focusedContent = this.GetFocusedContent();
				if (focusedContent != null)
				{
					this.DockPanel.SaveFocus();
				}
				if (!this.IsFloat)
				{
					this.DockWindow = this.DockPanel.DockWindows[this.DockState];
				}
				else
				{
					if (this.FloatWindow == null)
					{
						this.FloatWindow = this.DockPanel.FloatWindowFactory.CreateFloatWindow(this.DockPanel, this);
					}
				}
				if (focusedContent != null)
				{
					this.DockPanel.ContentFocusManager.Activate(focusedContent);
				}
				this.ResumeRefreshStateChange(nestedPanesContainer, dockState);
			}
		}
		private void SuspendRefreshStateChange()
		{
			checked
			{
				this.m_countRefreshStateChange++;
				this.DockPanel.SuspendLayout(true);
			}
		}
		private void ResumeRefreshStateChange()
		{
			checked
			{
				this.m_countRefreshStateChange--;
				Debug.Assert(this.m_countRefreshStateChange >= 0);
				this.DockPanel.ResumeLayout(true, true);
			}
		}
		private void ResumeRefreshStateChange(INestedPanesContainer oldContainer, DockState oldDockState)
		{
			this.ResumeRefreshStateChange();
			this.RefreshStateChange(oldContainer, oldDockState);
		}
		private void RefreshStateChange(INestedPanesContainer oldContainer, DockState oldDockState)
		{
			bool flag = false;
			try
			{
				Monitor.Enter(this, ref flag);
				if (this.IsRefreshStateChangeSuspended)
				{
					return;
				}
				this.SuspendRefreshStateChange();
			}
			finally
			{
				if (flag)
				{
					Monitor.Exit(this);
				}
			}
			this.DockPanel.SuspendLayout(true);
			IDockContent focusedContent = this.GetFocusedContent();
			if (focusedContent != null)
			{
				this.DockPanel.SaveFocus();
			}
			this.SetParent();
			if (this.ActiveContent != null)
			{
				this.ActiveContent.DockHandler.SetDockState(this.ActiveContent.DockHandler.IsHidden, this.DockState, this.ActiveContent.DockHandler.Pane);
			}
			foreach (IDockContent current in this.Contents)
			{
				if (current.DockHandler.Pane == this)
				{
					current.DockHandler.SetDockState(current.DockHandler.IsHidden, this.DockState, current.DockHandler.Pane);
				}
			}
			if (oldContainer != null)
			{
				Control control = (Control)oldContainer;
				if (oldContainer.DockState == oldDockState && !control.IsDisposed)
				{
					control.PerformLayout();
				}
			}
			if (DockHelper.IsDockStateAutoHide(oldDockState))
			{
				this.DockPanel.RefreshActiveAutoHideContent();
			}
			if (this.NestedPanesContainer.DockState == this.DockState)
			{
				((Control)this.NestedPanesContainer).PerformLayout();
			}
			if (DockHelper.IsDockStateAutoHide(this.DockState))
			{
				this.DockPanel.RefreshActiveAutoHideContent();
			}
			if (DockHelper.IsDockStateAutoHide(oldDockState) || DockHelper.IsDockStateAutoHide(this.DockState))
			{
				this.DockPanel.RefreshAutoHideStrip();
				this.DockPanel.PerformLayout();
			}
			this.ResumeRefreshStateChange();
			if (focusedContent != null)
			{
				focusedContent.DockHandler.Activate();
			}
			this.DockPanel.ResumeLayout(true, true);
			if (oldDockState != this.DockState)
			{
				this.OnDockStateChanged(EventArgs.Empty);
				return;
			}
		}
		private IDockContent GetFocusedContent()
		{
			IDockContent result = null;
			foreach (IDockContent current in this.Contents)
			{
				if (current.DockHandler.Form.ContainsFocus)
				{
					result = current;
					break;
				}
			}
			return result;
		}
		public DockPane DockTo(INestedPanesContainer container)
		{
			if (container == null)
			{
				throw new InvalidOperationException(Strings.DockPane_DockTo_NullContainer);
			}
			DockAlignment alignment;
			if (container.DockState == DockState.DockLeft || container.DockState == DockState.DockRight)
			{
				alignment = DockAlignment.Bottom;
			}
			else
			{
				alignment = DockAlignment.Right;
			}
			return this.DockTo(container, container.NestedPanes.GetDefaultPreviousPane(this), alignment, 0.5);
		}
		public DockPane DockTo(INestedPanesContainer container, DockPane previousPane, DockAlignment alignment, double proportion)
		{
			if (container == null)
			{
				throw new InvalidOperationException(Strings.DockPane_DockTo_NullContainer);
			}
			DockPane result;
			if (container.IsFloat == this.IsFloat)
			{
				this.InternalAddToDockList(container, previousPane, alignment, proportion);
				result = this;
			}
			else
			{
				IDockContent firstContent = this.GetFirstContent(container.DockState);
				if (firstContent == null)
				{
					result = null;
				}
				else
				{
					this.DockPanel.DummyContent.DockPanel = this.DockPanel;
					DockPane dockPane;
					if (container.IsFloat)
					{
						dockPane = this.DockPanel.DockPaneFactory.CreateDockPane(this.DockPanel.DummyContent, (FloatWindow)container, true);
					}
					else
					{
						dockPane = this.DockPanel.DockPaneFactory.CreateDockPane(this.DockPanel.DummyContent, container.DockState, true);
					}
					dockPane.DockTo(container, previousPane, alignment, proportion);
					this.SetVisibleContentsToPane(dockPane);
					this.DockPanel.DummyContent.DockPanel = null;
					result = dockPane;
				}
			}
			return result;
		}
		private void SetVisibleContentsToPane(DockPane pane)
		{
			this.SetVisibleContentsToPane(pane, this.ActiveContent);
		}
		private void SetVisibleContentsToPane(DockPane pane, IDockContent activeContent)
		{
			checked
			{
				for (int i = 0; i < this.DisplayingContents.Count; i++)
				{
					IDockContent dockContent = this.DisplayingContents[i];
					if (dockContent.DockHandler.IsDockStateValid(pane.DockState))
					{
						dockContent.DockHandler.Pane = pane;
						i--;
					}
				}
				if (activeContent.DockHandler.Pane == pane)
				{
					pane.ActiveContent = activeContent;
				}
			}
		}
		private void InternalAddToDockList(INestedPanesContainer container, DockPane prevPane, DockAlignment alignment, double proportion)
		{
			if (container.DockState == DockState.Float != this.IsFloat)
			{
				throw new InvalidOperationException(Strings.DockPane_DockTo_InvalidContainer);
			}
			int num = container.NestedPanes.Count;
			checked
			{
				if (container.NestedPanes.Contains(this))
				{
					num--;
				}
				if (prevPane == null && num > 0)
				{
					throw new InvalidOperationException(Strings.DockPane_DockTo_NullPrevPane);
				}
				if (prevPane != null && !container.NestedPanes.Contains(prevPane))
				{
					throw new InvalidOperationException(Strings.DockPane_DockTo_NoPrevPane);
				}
				if (prevPane == this)
				{
					throw new InvalidOperationException(Strings.DockPane_DockTo_SelfPrevPane);
				}
				INestedPanesContainer nestedPanesContainer = this.NestedPanesContainer;
				DockState dockState = this.DockState;
				container.NestedPanes.Add(this);
				this.NestedDockingStatus.SetStatus(container.NestedPanes, prevPane, alignment, proportion);
				if (DockHelper.IsDockWindowState(this.DockState))
				{
					this.m_dockState = container.DockState;
				}
				this.RefreshStateChange(nestedPanesContainer, dockState);
			}
		}
		public void SetNestedDockingProportion(double proportion)
		{
			this.NestedDockingStatus.SetStatus(this.NestedDockingStatus.NestedPanes, this.NestedDockingStatus.PreviousPane, this.NestedDockingStatus.Alignment, proportion);
			if (this.NestedPanesContainer != null)
			{
				((Control)this.NestedPanesContainer).PerformLayout();
			}
		}
		public DockPane Float()
		{
			this.DockPanel.SuspendLayout(true);
			IDockContent activeContent = this.ActiveContent;
			DockPane dockPane = this.GetFloatPaneFromContents();
			DockPane result;
			if (dockPane == null)
			{
				IDockContent firstContent = this.GetFirstContent(DockState.Float);
				if (firstContent == null)
				{
					this.DockPanel.ResumeLayout(true, true);
					result = null;
					return result;
				}
				dockPane = this.DockPanel.DockPaneFactory.CreateDockPane(firstContent, DockState.Float, true);
			}
			this.SetVisibleContentsToPane(dockPane, activeContent);
			this.DockPanel.ResumeLayout(true, true);
			result = dockPane;
			return result;
		}
		private DockPane GetFloatPaneFromContents()
		{
			DockPane dockPane = null;
			checked
			{
				DockPane result;
				for (int i = 0; i < this.DisplayingContents.Count; i++)
				{
					IDockContent dockContent = this.DisplayingContents[i];
					if (dockContent.DockHandler.IsDockStateValid(DockState.Float))
					{
						if (dockPane != null && dockContent.DockHandler.FloatPane != dockPane)
						{
							result = null;
							return result;
						}
						dockPane = dockContent.DockHandler.FloatPane;
					}
				}
				result = dockPane;
				return result;
			}
		}
		private IDockContent GetFirstContent(DockState dockState)
		{
			checked
			{
				IDockContent result;
				for (int i = 0; i < this.DisplayingContents.Count; i++)
				{
					IDockContent dockContent = this.DisplayingContents[i];
					if (dockContent.DockHandler.IsDockStateValid(dockState))
					{
						result = dockContent;
						return result;
					}
				}
				result = null;
				return result;
			}
		}
		public void RestoreToPanel()
		{
			this.DockPanel.SuspendLayout(true);
			IDockContent activeContent = this.DockPanel.ActiveContent;
			checked
			{
				for (int i = this.DisplayingContents.Count - 1; i >= 0; i--)
				{
					IDockContent dockContent = this.DisplayingContents[i];
					if (dockContent.DockHandler.CheckDockState(false) != DockState.Unknown)
					{
						dockContent.DockHandler.IsFloat = false;
					}
				}
				this.DockPanel.ResumeLayout(true, true);
			}
		}
		[SecurityPermission(SecurityAction.LinkDemand, Flags = SecurityPermissionFlag.UnmanagedCode)]
		protected override void WndProc(ref Message m)
		{
			if (m.Msg == 33)
			{
				this.Activate();
			}
			base.WndProc(ref m);
		}
		bool IDockDragSource.IsDockStateValid(DockState dockState)
		{
			return this.IsDockStateValid(dockState);
		}
		bool IDockDragSource.CanDockTo(DockPane pane)
		{
			return this.IsDockStateValid(pane.DockState) && pane != this;
		}
		Rectangle IDockDragSource.BeginDrag(Point ptMouse)
		{
			Point location = base.PointToScreen(new Point(0, 0));
			DockPane floatPane = this.ActiveContent.DockHandler.FloatPane;
			Size size;
			if (this.DockState == DockState.Float || floatPane == null || floatPane.FloatWindow.NestedPanes.Count != 1)
			{
				size = this.DockPanel.DefaultFloatWindowSize;
			}
			else
			{
				size = floatPane.FloatWindow.Size;
			}
			checked
			{
				if (ptMouse.X > location.X + size.Width)
				{
					location.X += ptMouse.X - (location.X + size.Width) + 4;
				}
				return new Rectangle(location, size);
			}
		}
		public void FloatAt(Rectangle floatWindowBounds)
		{
			if (this.FloatWindow == null || this.FloatWindow.NestedPanes.Count != 1)
			{
				this.FloatWindow = this.DockPanel.FloatWindowFactory.CreateFloatWindow(this.DockPanel, this, floatWindowBounds);
			}
			else
			{
				this.FloatWindow.Bounds = floatWindowBounds;
			}
			this.DockState = DockState.Float;
			this.NestedDockingStatus.NestedPanes.Remove(this);
		}
		public void DockTo(DockPane pane, DockStyle dockStyle, int contentIndex)
		{
			checked
			{
				if (dockStyle == DockStyle.Fill)
				{
					IDockContent activeContent = this.ActiveContent;
					for (int i = this.Contents.Count - 1; i >= 0; i--)
					{
						IDockContent dockContent = this.Contents[i];
						if (dockContent.DockHandler.DockState == this.DockState)
						{
							dockContent.DockHandler.Pane = pane;
							if (contentIndex != -1)
							{
								pane.SetContentIndex(dockContent, contentIndex);
							}
						}
					}
					pane.ActiveContent = activeContent;
				}
				else
				{
					if (dockStyle == DockStyle.Left)
					{
						this.DockTo(pane.NestedPanesContainer, pane, DockAlignment.Left, 0.5);
					}
					else
					{
						if (dockStyle == DockStyle.Right)
						{
							this.DockTo(pane.NestedPanesContainer, pane, DockAlignment.Right, 0.5);
						}
						else
						{
							if (dockStyle == DockStyle.Top)
							{
								this.DockTo(pane.NestedPanesContainer, pane, DockAlignment.Top, 0.5);
							}
							else
							{
								if (dockStyle == DockStyle.Bottom)
								{
									this.DockTo(pane.NestedPanesContainer, pane, DockAlignment.Bottom, 0.5);
								}
							}
						}
					}
					this.DockState = pane.DockState;
				}
			}
		}
		public void DockTo(DockPanel panel, DockStyle dockStyle)
		{
			if (panel != this.DockPanel)
			{
				throw new ArgumentException(Strings.IDockDragSource_DockTo_InvalidPanel, "panel");
			}
			if (dockStyle == DockStyle.Top)
			{
				this.DockState = DockState.DockTop;
			}
			else
			{
				if (dockStyle == DockStyle.Bottom)
				{
					this.DockState = DockState.DockBottom;
				}
				else
				{
					if (dockStyle == DockStyle.Left)
					{
						this.DockState = DockState.DockLeft;
					}
					else
					{
						if (dockStyle == DockStyle.Right)
						{
							this.DockState = DockState.DockRight;
						}
						else
						{
							if (dockStyle == DockStyle.Fill)
							{
								this.DockState = DockState.Document;
							}
						}
					}
				}
			}
		}
	}
}
