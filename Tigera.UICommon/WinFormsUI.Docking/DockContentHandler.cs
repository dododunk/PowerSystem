using System;
using System.ComponentModel;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;
using WinFormsUI.Docking.Win32;
namespace WinFormsUI.Docking
{
	public class DockContentHandler : IDisposable, IDockDragSource, IDragSource
	{
		private Form m_form;
		private IDockContent m_previousActive = null;
		private IDockContent m_nextActive = null;
		private EventHandlerList m_events;
		private bool m_allowEndUserDocking = true;
		private double m_autoHidePortion = 0.25;
		private bool m_closeButton = true;
		private bool m_closeButtonVisible = true;
		private DockAreas m_allowedAreas = DockAreas.Float | DockAreas.DockLeft | DockAreas.DockRight | DockAreas.DockTop | DockAreas.DockBottom | DockAreas.Document;
		private DockState m_dockState = DockState.Unknown;
		private DockPanel m_dockPanel = null;
		private bool m_isHidden = true;
		private string m_tabText = null;
		private DockState m_visibleState = DockState.Unknown;
		private bool m_isFloat = false;
		private DockPane m_panelPane = null;
		private DockPane m_floatPane = null;
		private int m_countSetDockState = 0;
		private GetPersistStringCallback m_getPersistStringCallback = null;
		private bool m_hideOnClose = false;
		private DockState m_showHint = DockState.Unknown;
		private bool m_isActivated = false;
		private ContextMenu m_tabPageContextMenu = null;
		private string m_toolTipText = null;
		private IntPtr m_activeWindowHandle = IntPtr.Zero;
		private DockPaneStripBase.Tab m_tab = null;
		private IDisposable m_autoHideTab = null;
		private static readonly object DockStateChangedEvent = new object();
		private bool m_flagClipWindow = false;
		private ContextMenuStrip m_tabPageContextMenuStrip = null;
		public event EventHandler DockStateChanged
		{
			add
			{
				this.Events.AddHandler(DockContentHandler.DockStateChangedEvent, value);
			}
			remove
			{
				this.Events.RemoveHandler(DockContentHandler.DockStateChangedEvent, value);
			}
		}
		public Form Form
		{
			get
			{
				return this.m_form;
			}
		}
		public IDockContent Content
		{
			get
			{
				return this.Form as IDockContent;
			}
		}
		public IDockContent PreviousActive
		{
			get
			{
				return this.m_previousActive;
			}
			internal set
			{
				this.m_previousActive = value;
			}
		}
		public IDockContent NextActive
		{
			get
			{
				return this.m_nextActive;
			}
			internal set
			{
				this.m_nextActive = value;
			}
		}
		private EventHandlerList Events
		{
			get
			{
				return this.m_events;
			}
		}
		public bool AllowEndUserDocking
		{
			get
			{
				return this.m_allowEndUserDocking;
			}
			set
			{
				this.m_allowEndUserDocking = value;
			}
		}
		public double AutoHidePortion
		{
			get
			{
				return this.m_autoHidePortion;
			}
			set
			{
				if (value <= 0.0)
				{
					throw new ArgumentOutOfRangeException(Strings.DockContentHandler_AutoHidePortion_OutOfRange);
				}
				if (this.m_autoHidePortion != value)
				{
					this.m_autoHidePortion = value;
					if (this.DockPanel != null)
					{
						if (this.DockPanel.ActiveAutoHideContent == this.Content)
						{
							this.DockPanel.PerformLayout();
						}
					}
				}
			}
		}
		public bool CloseButton
		{
			get
			{
				return this.m_closeButton;
			}
			set
			{
				if (this.m_closeButton != value)
				{
					this.m_closeButton = value;
					if (this.Pane != null && this.Pane.ActiveContent.DockHandler == this)
					{
						this.Pane.RefreshChanges();
					}
				}
			}
		}
		public bool CloseButtonVisible
		{
			get
			{
				return this.m_closeButtonVisible;
			}
			set
			{
				this.m_closeButtonVisible = value;
			}
		}
		private DockState DefaultDockState
		{
			get
			{
				DockState result;
				if (this.ShowHint != DockState.Unknown && this.ShowHint != DockState.Hidden)
				{
					result = this.ShowHint;
				}
				else
				{
					if ((this.DockAreas & DockAreas.Document) != (DockAreas)0)
					{
						result = DockState.Document;
					}
					else
					{
						if ((this.DockAreas & DockAreas.DockRight) != (DockAreas)0)
						{
							result = DockState.DockRight;
						}
						else
						{
							if ((this.DockAreas & DockAreas.DockLeft) != (DockAreas)0)
							{
								result = DockState.DockLeft;
							}
							else
							{
								if ((this.DockAreas & DockAreas.DockBottom) != (DockAreas)0)
								{
									result = DockState.DockBottom;
								}
								else
								{
									if ((this.DockAreas & DockAreas.DockTop) != (DockAreas)0)
									{
										result = DockState.DockTop;
									}
									else
									{
										result = DockState.Unknown;
									}
								}
							}
						}
					}
				}
				return result;
			}
		}
		private DockState DefaultShowState
		{
			get
			{
				DockState result;
				if (this.ShowHint != DockState.Unknown)
				{
					result = this.ShowHint;
				}
				else
				{
					if ((this.DockAreas & DockAreas.Document) != (DockAreas)0)
					{
						result = DockState.Document;
					}
					else
					{
						if ((this.DockAreas & DockAreas.DockRight) != (DockAreas)0)
						{
							result = DockState.DockRight;
						}
						else
						{
							if ((this.DockAreas & DockAreas.DockLeft) != (DockAreas)0)
							{
								result = DockState.DockLeft;
							}
							else
							{
								if ((this.DockAreas & DockAreas.DockBottom) != (DockAreas)0)
								{
									result = DockState.DockBottom;
								}
								else
								{
									if ((this.DockAreas & DockAreas.DockTop) != (DockAreas)0)
									{
										result = DockState.DockTop;
									}
									else
									{
										if ((this.DockAreas & DockAreas.Float) != (DockAreas)0)
										{
											result = DockState.Float;
										}
										else
										{
											result = DockState.Unknown;
										}
									}
								}
							}
						}
					}
				}
				return result;
			}
		}
		public DockAreas DockAreas
		{
			get
			{
				return this.m_allowedAreas;
			}
			set
			{
				if (this.m_allowedAreas != value)
				{
					if (!DockHelper.IsDockStateValid(this.DockState, value))
					{
						throw new InvalidOperationException(Strings.DockContentHandler_DockAreas_InvalidValue);
					}
					this.m_allowedAreas = value;
					if (!DockHelper.IsDockStateValid(this.ShowHint, this.m_allowedAreas))
					{
						this.ShowHint = DockState.Unknown;
					}
				}
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
				if (this.m_dockState != value)
				{
					this.DockPanel.SuspendLayout(true);
					if (value == DockState.Hidden)
					{
						this.IsHidden = true;
					}
					else
					{
						this.SetDockState(false, value, this.Pane);
					}
					this.DockPanel.ResumeLayout(true, true);
				}
			}
		}
		public DockPanel DockPanel
		{
			get
			{
				return this.m_dockPanel;
			}
			set
			{
				if (this.m_dockPanel != value)
				{
					this.Pane = null;
					if (this.m_dockPanel != null)
					{
						this.m_dockPanel.RemoveContent(this.Content);
					}
					if (this.m_tab != null)
					{
						this.m_tab.Dispose();
						this.m_tab = null;
					}
					if (this.m_autoHideTab != null)
					{
						this.m_autoHideTab.Dispose();
						this.m_autoHideTab = null;
					}
					this.m_dockPanel = value;
					if (this.m_dockPanel != null)
					{
						this.m_dockPanel.AddContent(this.Content);
						this.Form.TopLevel = false;
						this.Form.FormBorderStyle = FormBorderStyle.None;
						this.Form.ShowInTaskbar = false;
						this.Form.WindowState = FormWindowState.Normal;
						NativeMethods.SetWindowPos(this.Form.Handle, IntPtr.Zero, 0, 0, 0, 0, FlagsSetWindowPos.SWP_NOSIZE | FlagsSetWindowPos.SWP_NOMOVE | FlagsSetWindowPos.SWP_NOZORDER | FlagsSetWindowPos.SWP_NOACTIVATE | FlagsSetWindowPos.SWP_FRAMECHANGED | FlagsSetWindowPos.SWP_NOOWNERZORDER);
					}
				}
			}
		}
		public Icon Icon
		{
			get
			{
				return this.Form.Icon;
			}
		}
		public DockPane Pane
		{
			get
			{
				return this.IsFloat ? this.FloatPane : this.PanelPane;
			}
			set
			{
				if (this.Pane != value)
				{
					this.DockPanel.SuspendLayout(true);
					DockPane pane = this.Pane;
					this.SuspendSetDockState();
					this.FloatPane = ((value == null) ? null : (value.IsFloat ? value : this.FloatPane));
					this.PanelPane = ((value == null) ? null : (value.IsFloat ? this.PanelPane : value));
					this.ResumeSetDockState(this.IsHidden, (value != null) ? value.DockState : DockState.Unknown, pane);
					this.DockPanel.ResumeLayout(true, true);
				}
			}
		}
		public bool IsHidden
		{
			get
			{
				return this.m_isHidden;
			}
			set
			{
				if (this.m_isHidden != value)
				{
					this.SetDockState(value, this.VisibleState, this.Pane);
				}
			}
		}
		public string TabText
		{
			get
			{
				return (this.m_tabText == null || this.m_tabText == "") ? this.Form.Text : this.m_tabText;
			}
			set
			{
				if (!(this.m_tabText == value))
				{
					this.m_tabText = value;
					if (this.Pane != null)
					{
						this.Pane.RefreshChanges();
					}
				}
			}
		}
		public DockState VisibleState
		{
			get
			{
				return this.m_visibleState;
			}
			set
			{
				if (this.m_visibleState != value)
				{
					this.SetDockState(this.IsHidden, value, this.Pane);
				}
			}
		}
		public bool IsFloat
		{
			get
			{
				return this.m_isFloat;
			}
			set
			{
				if (this.m_isFloat != value)
				{
					DockState dockState = this.CheckDockState(value);
					if (dockState == DockState.Unknown)
					{
						throw new InvalidOperationException(Strings.DockContentHandler_IsFloat_InvalidValue);
					}
					this.SetDockState(this.IsHidden, dockState, this.Pane);
				}
			}
		}
		public DockPane PanelPane
		{
			get
			{
				return this.m_panelPane;
			}
			set
			{
				if (this.m_panelPane != value)
				{
					if (value != null)
					{
						if (value.IsFloat || value.DockPanel != this.DockPanel)
						{
							throw new InvalidOperationException(Strings.DockContentHandler_DockPane_InvalidValue);
						}
					}
					DockPane pane = this.Pane;
					if (this.m_panelPane != null)
					{
						this.RemoveFromPane(this.m_panelPane);
					}
					this.m_panelPane = value;
					if (this.m_panelPane != null)
					{
						this.m_panelPane.AddContent(this.Content);
						this.SetDockState(this.IsHidden, this.IsFloat ? DockState.Float : this.m_panelPane.DockState, pane);
					}
					else
					{
						this.SetDockState(this.IsHidden, DockState.Unknown, pane);
					}
				}
			}
		}
		public DockPane FloatPane
		{
			get
			{
				return this.m_floatPane;
			}
			set
			{
				if (this.m_floatPane != value)
				{
					if (value != null)
					{
						if (!value.IsFloat || value.DockPanel != this.DockPanel)
						{
							throw new InvalidOperationException(Strings.DockContentHandler_FloatPane_InvalidValue);
						}
					}
					DockPane pane = this.Pane;
					if (this.m_floatPane != null)
					{
						this.RemoveFromPane(this.m_floatPane);
					}
					this.m_floatPane = value;
					if (this.m_floatPane != null)
					{
						this.m_floatPane.AddContent(this.Content);
						this.SetDockState(this.IsHidden, this.IsFloat ? DockState.Float : this.VisibleState, pane);
					}
					else
					{
						this.SetDockState(this.IsHidden, DockState.Unknown, pane);
					}
				}
			}
		}
		internal bool IsSuspendSetDockState
		{
			get
			{
				return this.m_countSetDockState != 0;
			}
		}
		internal string PersistString
		{
			get
			{
				return (this.GetPersistStringCallback == null) ? this.Form.GetType().ToString() : this.GetPersistStringCallback();
			}
		}
		public GetPersistStringCallback GetPersistStringCallback
		{
			get
			{
				return this.m_getPersistStringCallback;
			}
			set
			{
				this.m_getPersistStringCallback = value;
			}
		}
		public bool HideOnClose
		{
			get
			{
				return this.m_hideOnClose;
			}
			set
			{
				this.m_hideOnClose = value;
			}
		}
		public DockState ShowHint
		{
			get
			{
				return this.m_showHint;
			}
			set
			{
				if (!DockHelper.IsDockStateValid(value, this.DockAreas))
				{
					throw new InvalidOperationException(Strings.DockContentHandler_ShowHint_InvalidValue);
				}
				if (this.m_showHint != value)
				{
					this.m_showHint = value;
				}
			}
		}
		public bool IsActivated
		{
			get
			{
				return this.m_isActivated;
			}
			internal set
			{
				if (this.m_isActivated != value)
				{
					this.m_isActivated = value;
				}
			}
		}
		public ContextMenu TabPageContextMenu
		{
			get
			{
				return this.m_tabPageContextMenu;
			}
			set
			{
				this.m_tabPageContextMenu = value;
			}
		}
		public string ToolTipText
		{
			get
			{
				return this.m_toolTipText;
			}
			set
			{
				this.m_toolTipText = value;
			}
		}
		internal IntPtr ActiveWindowHandle
		{
			get
			{
				return this.m_activeWindowHandle;
			}
			set
			{
				this.m_activeWindowHandle = value;
			}
		}
		internal IDisposable AutoHideTab
		{
			get
			{
				return this.m_autoHideTab;
			}
			set
			{
				this.m_autoHideTab = value;
			}
		}
		internal bool FlagClipWindow
		{
			get
			{
				return this.m_flagClipWindow;
			}
			set
			{
				if (this.m_flagClipWindow != value)
				{
					this.m_flagClipWindow = value;
					if (this.m_flagClipWindow)
					{
						this.Form.Region = new Region(Rectangle.Empty);
					}
					else
					{
						this.Form.Region = null;
					}
				}
			}
		}
		public ContextMenuStrip TabPageContextMenuStrip
		{
			get
			{
				return this.m_tabPageContextMenuStrip;
			}
			set
			{
				this.m_tabPageContextMenuStrip = value;
			}
		}
		Control IDragSource.DragControl
		{
			get
			{
				return this.Form;
			}
		}
		public DockContentHandler(Form form) : this(form, null)
		{
		}
		public DockContentHandler(Form form, GetPersistStringCallback getPersistStringCallback)
		{
			if (!(form is IDockContent))
			{
				throw new ArgumentException(Strings.DockContent_Constructor_InvalidForm, "form");
			}
			this.m_form = form;
			this.m_getPersistStringCallback = getPersistStringCallback;
			this.m_events = new EventHandlerList();
			this.Form.Disposed += new EventHandler(this.Form_Disposed);
			this.Form.TextChanged += new EventHandler(this.Form_TextChanged);
		}
		public void Dispose()
		{
			this.Dispose(true);
			GC.SuppressFinalize(this);
		}
		protected virtual void Dispose(bool disposing)
		{
			if (disposing)
			{
				bool flag = false;
				try
				{
					Monitor.Enter(this, ref flag);
					this.DockPanel = null;
					if (this.m_autoHideTab != null)
					{
						this.m_autoHideTab.Dispose();
					}
					if (this.m_tab != null)
					{
						this.m_tab.Dispose();
					}
					this.Form.Disposed -= new EventHandler(this.Form_Disposed);
					this.Form.TextChanged -= new EventHandler(this.Form_TextChanged);
					this.m_events.Dispose();
				}
				finally
				{
					if (flag)
					{
						Monitor.Exit(this);
					}
				}
			}
		}
		public DockState CheckDockState(bool isFloat)
		{
			DockState dockState;
			if (isFloat)
			{
				if (!this.IsDockStateValid(DockState.Float))
				{
					dockState = DockState.Unknown;
				}
				else
				{
					dockState = DockState.Float;
				}
			}
			else
			{
				dockState = ((this.PanelPane != null) ? this.PanelPane.DockState : this.DefaultDockState);
				if (dockState != DockState.Unknown && !this.IsDockStateValid(dockState))
				{
					dockState = DockState.Unknown;
				}
			}
			return dockState;
		}
		private void RemoveFromPane(DockPane pane)
		{
			pane.RemoveContent(this.Content);
			this.SetPane(null);
			if (pane.Contents.Count == 0)
			{
				pane.Dispose();
			}
		}
		private void SuspendSetDockState()
		{
			checked
			{
				this.m_countSetDockState++;
			}
		}
		private void ResumeSetDockState()
		{
			checked
			{
				this.m_countSetDockState--;
				if (this.m_countSetDockState < 0)
				{
					this.m_countSetDockState = 0;
				}
			}
		}
		private void ResumeSetDockState(bool isHidden, DockState visibleState, DockPane oldPane)
		{
			this.ResumeSetDockState();
			this.SetDockState(isHidden, visibleState, oldPane);
		}
		internal void SetDockState(bool isHidden, DockState visibleState, DockPane oldPane)
		{
			if (!this.IsSuspendSetDockState)
			{
				if (this.DockPanel == null && visibleState != DockState.Unknown)
				{
					throw new InvalidOperationException(Strings.DockContentHandler_SetDockState_NullPanel);
				}
				if (visibleState == DockState.Hidden || (visibleState != DockState.Unknown && !this.IsDockStateValid(visibleState)))
				{
					throw new InvalidOperationException(Strings.DockContentHandler_SetDockState_InvalidState);
				}
				DockPanel dockPanel = this.DockPanel;
				if (dockPanel != null)
				{
					dockPanel.SuspendLayout(true);
				}
				this.SuspendSetDockState();
				DockState dockState = this.DockState;
				if (this.m_isHidden != isHidden || dockState == DockState.Unknown)
				{
					this.m_isHidden = isHidden;
				}
				this.m_visibleState = visibleState;
				this.m_dockState = (isHidden ? DockState.Hidden : visibleState);
				if (visibleState == DockState.Unknown)
				{
					this.Pane = null;
				}
				else
				{
					this.m_isFloat = (this.m_visibleState == DockState.Float);
					if (this.Pane == null)
					{
						this.Pane = this.DockPanel.DockPaneFactory.CreateDockPane(this.Content, visibleState, true);
					}
					else
					{
						if (this.Pane.DockState != visibleState)
						{
							if (this.Pane.Contents.Count == 1)
							{
								this.Pane.SetDockState(visibleState);
							}
							else
							{
								this.Pane = this.DockPanel.DockPaneFactory.CreateDockPane(this.Content, visibleState, true);
							}
						}
					}
				}
				if (this.Form.ContainsFocus && (this.DockState == DockState.Hidden || this.DockState == DockState.Unknown))
				{
					this.DockPanel.ContentFocusManager.GiveUpFocus(this.Content);
				}
				this.SetPaneAndVisible(this.Pane);
				if (oldPane != null && !oldPane.IsDisposed && dockState == oldPane.DockState)
				{
					DockContentHandler.RefreshDockPane(oldPane);
				}
				if (this.Pane != null && this.DockState == this.Pane.DockState)
				{
					if ((this.Pane != oldPane || (this.Pane == oldPane && dockState != oldPane.DockState)) && (this.Pane.DockWindow == null || this.Pane.DockWindow.Visible || this.Pane.IsHidden) && !this.Pane.IsAutoHide)
					{
						DockContentHandler.RefreshDockPane(this.Pane);
					}
				}
				if (dockState != this.DockState)
				{
					if (this.DockState == DockState.Hidden || this.DockState == DockState.Unknown || DockHelper.IsDockStateAutoHide(this.DockState))
					{
						this.DockPanel.ContentFocusManager.RemoveFromList(this.Content);
					}
					else
					{
						this.DockPanel.ContentFocusManager.AddToList(this.Content);
					}
					this.OnDockStateChanged(EventArgs.Empty);
				}
				this.ResumeSetDockState();
				if (dockPanel != null)
				{
					dockPanel.ResumeLayout(true, true);
				}
			}
		}
		private static void RefreshDockPane(DockPane pane)
		{
			pane.RefreshChanges();
			pane.ValidateActiveContent();
		}
		public bool IsDockStateValid(DockState dockState)
		{
			return (this.DockPanel == null || dockState != DockState.Document || this.DockPanel.DocumentStyle != DocumentStyle.SystemMdi) && DockHelper.IsDockStateValid(dockState, this.DockAreas);
		}
		public void Activate()
		{
			if (this.DockPanel == null)
			{
				this.Form.Activate();
			}
			else
			{
				if (this.Pane == null)
				{
					this.Show(this.DockPanel);
				}
				else
				{
					this.IsHidden = false;
					this.Pane.ActiveContent = this.Content;
					if (this.DockState == DockState.Document && this.DockPanel.DocumentStyle == DocumentStyle.SystemMdi)
					{
						this.Form.Activate();
					}
					else
					{
						if (DockHelper.IsDockStateAutoHide(this.DockState))
						{
							this.DockPanel.ActiveAutoHideContent = this.Content;
						}
						if (!this.Form.ContainsFocus)
						{
							this.DockPanel.ContentFocusManager.Activate(this.Content);
						}
					}
				}
			}
		}
		public void GiveUpFocus()
		{
			this.DockPanel.ContentFocusManager.GiveUpFocus(this.Content);
		}
		public void Hide()
		{
			this.IsHidden = true;
		}
		internal void SetPaneAndVisible(DockPane pane)
		{
			this.SetPane(pane);
			this.SetVisible();
		}
		private void SetPane(DockPane pane)
		{
			if (pane != null && pane.DockState == DockState.Document && this.DockPanel.DocumentStyle == DocumentStyle.DockingMdi)
			{
				if (this.Form.Parent is DockPane)
				{
					this.SetParent(null);
				}
				if (this.Form.MdiParent != this.DockPanel.ParentForm)
				{
					this.FlagClipWindow = true;
					this.Form.MdiParent = this.DockPanel.ParentForm;
				}
			}
			else
			{
				this.FlagClipWindow = true;
				if (this.Form.MdiParent != null)
				{
					this.Form.MdiParent = null;
				}
				if (this.Form.TopLevel)
				{
					this.Form.TopLevel = false;
				}
				this.SetParent(pane);
			}
		}
		internal void SetVisible()
		{
			bool flag = !this.IsHidden && ((this.Pane != null && this.Pane.DockState == DockState.Document && this.DockPanel.DocumentStyle == DocumentStyle.DockingMdi) || (this.Pane != null && this.Pane.ActiveContent == this.Content) || ((this.Pane == null || this.Pane.ActiveContent == this.Content) && this.Form.Visible));
			if (this.Form.Visible != flag)
			{
				this.Form.Visible = flag;
			}
		}
		private void SetParent(Control value)
		{
			if (this.Form.Parent != value)
			{
				bool flag = false;
				if (this.Form.ContainsFocus)
				{
					if (value == null && !this.IsFloat)
					{
						this.DockPanel.ContentFocusManager.GiveUpFocus(this.Content);
					}
					else
					{
						this.DockPanel.SaveFocus();
						flag = true;
					}
				}
				this.Form.Parent = value;
				if (flag)
				{
					this.Activate();
				}
			}
		}
		public void Show()
		{
			if (this.DockPanel == null)
			{
				this.Form.Show();
			}
			else
			{
				this.Show(this.DockPanel);
			}
		}
		public void Show(DockPanel dockPanel)
		{
			if (dockPanel == null)
			{
				throw new ArgumentNullException(Strings.DockContentHandler_Show_NullDockPanel);
			}
			if (this.DockState == DockState.Unknown)
			{
				this.Show(dockPanel, this.DefaultShowState);
			}
			else
			{
				this.Activate();
			}
		}
		public void Show(DockPanel dockPanel, DockState dockState)
		{
			if (dockPanel == null)
			{
				throw new ArgumentNullException(Strings.DockContentHandler_Show_NullDockPanel);
			}
			if (dockState == DockState.Unknown || dockState == DockState.Hidden)
			{
				throw new ArgumentException(Strings.DockContentHandler_Show_InvalidDockState);
			}
			dockPanel.SuspendLayout(true);
			this.DockPanel = dockPanel;
			if (dockState == DockState.Float && this.FloatPane == null)
			{
				this.Pane = this.DockPanel.DockPaneFactory.CreateDockPane(this.Content, DockState.Float, true);
			}
			else
			{
				if (this.PanelPane == null)
				{
					DockPane dockPane = null;
					foreach (DockPane current in this.DockPanel.Panes)
					{
						if (current.DockState == dockState)
						{
							dockPane = current;
							break;
						}
					}
					if (dockPane == null)
					{
						this.Pane = this.DockPanel.DockPaneFactory.CreateDockPane(this.Content, dockState, true);
					}
					else
					{
						this.Pane = dockPane;
					}
				}
			}
			this.DockState = dockState;
			dockPanel.ResumeLayout(true, true);
			this.Activate();
		}
		public void Show(DockPanel dockPanel, Rectangle floatWindowBounds)
		{
			if (dockPanel == null)
			{
				throw new ArgumentNullException(Strings.DockContentHandler_Show_NullDockPanel);
			}
			dockPanel.SuspendLayout(true);
			this.DockPanel = dockPanel;
			if (this.FloatPane == null)
			{
				this.IsHidden = true;
				this.FloatPane = this.DockPanel.DockPaneFactory.CreateDockPane(this.Content, DockState.Float, false);
				this.FloatPane.FloatWindow.StartPosition = FormStartPosition.Manual;
			}
			this.FloatPane.FloatWindow.Bounds = floatWindowBounds;
			this.Show(dockPanel, DockState.Float);
			this.Activate();
			dockPanel.ResumeLayout(true, true);
		}
		public void Show(DockPane pane, IDockContent beforeContent)
		{
			if (pane == null)
			{
				throw new ArgumentNullException(Strings.DockContentHandler_Show_NullPane);
			}
			if (beforeContent != null && pane.Contents.IndexOf(beforeContent) == -1)
			{
				throw new ArgumentException(Strings.DockContentHandler_Show_InvalidBeforeContent);
			}
			pane.DockPanel.SuspendLayout(true);
			this.DockPanel = pane.DockPanel;
			this.Pane = pane;
			pane.SetContentIndex(this.Content, pane.Contents.IndexOf(beforeContent));
			this.Show();
			pane.DockPanel.ResumeLayout(true, true);
		}
		public void Show(DockPane previousPane, DockAlignment alignment, double proportion)
		{
			if (previousPane == null)
			{
				throw new ArgumentException(Strings.DockContentHandler_Show_InvalidPrevPane);
			}
			if (DockHelper.IsDockStateAutoHide(previousPane.DockState))
			{
				throw new ArgumentException(Strings.DockContentHandler_Show_InvalidPrevPane);
			}
			previousPane.DockPanel.SuspendLayout(true);
			this.DockPanel = previousPane.DockPanel;
			this.DockPanel.DockPaneFactory.CreateDockPane(this.Content, previousPane, alignment, proportion, true);
			this.Show();
			previousPane.DockPanel.ResumeLayout(true, true);
		}
		public void Close()
		{
			DockPanel dockPanel = this.DockPanel;
			if (dockPanel != null)
			{
				dockPanel.SuspendLayout(true);
			}
			this.Form.Close();
			if (dockPanel != null)
			{
				dockPanel.ResumeLayout(true, true);
			}
		}
		internal DockPaneStripBase.Tab GetTab(DockPaneStripBase dockPaneStrip)
		{
			if (this.m_tab == null)
			{
				this.m_tab = dockPaneStrip.CreateTab(this.Content);
			}
			return this.m_tab;
		}
		protected virtual void OnDockStateChanged(EventArgs e)
		{
			EventHandler eventHandler = (EventHandler)this.Events[DockContentHandler.DockStateChangedEvent];
			if (eventHandler != null)
			{
				eventHandler(this, e);
			}
		}
		private void Form_Disposed(object sender, EventArgs e)
		{
			this.Dispose();
		}
		private void Form_TextChanged(object sender, EventArgs e)
		{
			if (DockHelper.IsDockStateAutoHide(this.DockState))
			{
				this.DockPanel.RefreshAutoHideStrip();
			}
			else
			{
				if (this.Pane != null)
				{
					if (this.Pane.FloatWindow != null)
					{
						this.Pane.FloatWindow.SetText();
					}
					this.Pane.RefreshChanges();
				}
			}
		}
		bool IDockDragSource.CanDockTo(DockPane pane)
		{
			return this.IsDockStateValid(pane.DockState) && (this.Pane != pane || pane.DisplayingContents.Count != 1);
		}
		Rectangle IDockDragSource.BeginDrag(Point ptMouse)
		{
			DockPane floatPane = this.FloatPane;
			Size size;
			if (this.DockState == DockState.Float || floatPane == null || floatPane.FloatWindow.NestedPanes.Count != 1)
			{
				size = this.DockPanel.DefaultFloatWindowSize;
			}
			else
			{
				size = floatPane.FloatWindow.Size;
			}
			Rectangle clientRectangle = this.Pane.ClientRectangle;
			checked
			{
				Point point;
				if (this.DockState == DockState.Document)
				{
					if (this.Pane.DockPanel.DocumentTabStripLocation == DocumentTabStripLocation.Bottom)
					{
						point = new Point(clientRectangle.Left, clientRectangle.Bottom - size.Height);
					}
					else
					{
						point = new Point(clientRectangle.Left, clientRectangle.Top);
					}
				}
				else
				{
					point = new Point(clientRectangle.Left, clientRectangle.Bottom);
					point.Y -= size.Height;
				}
				point = this.Pane.PointToScreen(point);
				if (ptMouse.X > point.X + size.Width)
				{
					point.X += ptMouse.X - (point.X + size.Width) + 4;
				}
				return new Rectangle(point, size);
			}
		}
		public void FloatAt(Rectangle floatWindowBounds)
		{
			DockPane dockPane = this.DockPanel.DockPaneFactory.CreateDockPane(this.Content, floatWindowBounds, true);
		}
		public void DockTo(DockPane pane, DockStyle dockStyle, int contentIndex)
		{
			checked
			{
				if (dockStyle == DockStyle.Fill)
				{
					bool flag = this.Pane == pane;
					if (!flag)
					{
						this.Pane = pane;
					}
					if (contentIndex == -1 || !flag)
					{
						pane.SetContentIndex(this.Content, contentIndex);
					}
					else
					{
						DockContentCollection contents = pane.Contents;
						int num = contents.IndexOf(this.Content);
						int num2 = contentIndex;
						if (num < num2)
						{
							num2++;
							if (num2 > contents.Count - 1)
							{
								num2 = -1;
							}
						}
						pane.SetContentIndex(this.Content, num2);
					}
				}
				else
				{
					DockPane dockPane = this.DockPanel.DockPaneFactory.CreateDockPane(this.Content, pane.DockState, true);
					INestedPanesContainer nestedPanesContainer = pane.NestedPanesContainer;
					if (dockStyle == DockStyle.Left)
					{
						dockPane.DockTo(nestedPanesContainer, pane, DockAlignment.Left, 0.5);
					}
					else
					{
						if (dockStyle == DockStyle.Right)
						{
							dockPane.DockTo(nestedPanesContainer, pane, DockAlignment.Right, 0.5);
						}
						else
						{
							if (dockStyle == DockStyle.Top)
							{
								dockPane.DockTo(nestedPanesContainer, pane, DockAlignment.Top, 0.5);
							}
							else
							{
								if (dockStyle == DockStyle.Bottom)
								{
									dockPane.DockTo(nestedPanesContainer, pane, DockAlignment.Bottom, 0.5);
								}
							}
						}
					}
					dockPane.DockState = pane.DockState;
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
				DockPane dockPane = this.DockPanel.DockPaneFactory.CreateDockPane(this.Content, DockState.DockTop, true);
			}
			else
			{
				if (dockStyle == DockStyle.Bottom)
				{
					DockPane dockPane = this.DockPanel.DockPaneFactory.CreateDockPane(this.Content, DockState.DockBottom, true);
				}
				else
				{
					if (dockStyle == DockStyle.Left)
					{
						DockPane dockPane = this.DockPanel.DockPaneFactory.CreateDockPane(this.Content, DockState.DockLeft, true);
					}
					else
					{
						if (dockStyle == DockStyle.Right)
						{
							DockPane dockPane = this.DockPanel.DockPaneFactory.CreateDockPane(this.Content, DockState.DockRight, true);
						}
						else
						{
							if (dockStyle == DockStyle.Fill)
							{
								DockPane dockPane = this.DockPanel.DockPaneFactory.CreateDockPane(this.Content, DockState.Document, true);
							}
						}
					}
				}
			}
		}
	}
}
