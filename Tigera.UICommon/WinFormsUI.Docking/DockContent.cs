using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace WinFormsUI.Docking
{
	public class DockContent : Form, IDockContent
	{
		private DockContentHandler m_dockHandler = null;
		[DefaultValue(null), Localizable(true), LocalizedCategory("Category_Docking"), LocalizedDescription("DockContent_TabText_Description")]
		private string m_tabText = null;
		private static readonly object DockStateChangedEvent = new object();
		[LocalizedCategory("Category_PropertyChanged"), LocalizedDescription("Pane_DockStateChanged_Description")]
		public event EventHandler DockStateChanged
		{
			add
			{
				base.Events.AddHandler(DockContent.DockStateChangedEvent, value);
			}
			remove
			{
				base.Events.RemoveHandler(DockContent.DockStateChangedEvent, value);
			}
		}
		[Browsable(false)]
		public DockContentHandler DockHandler
		{
			get
			{
				return this.m_dockHandler;
			}
		}
		[DefaultValue(true), LocalizedCategory("Category_Docking"), LocalizedDescription("DockContent_AllowEndUserDocking_Description")]
		public bool AllowEndUserDocking
		{
			get
			{
				return this.DockHandler.AllowEndUserDocking;
			}
			set
			{
				this.DockHandler.AllowEndUserDocking = value;
			}
		}
		[DefaultValue(DockAreas.Float | DockAreas.DockLeft | DockAreas.DockRight | DockAreas.DockTop | DockAreas.DockBottom | DockAreas.Document), LocalizedCategory("Category_Docking"), LocalizedDescription("DockContent_DockAreas_Description")]
		public DockAreas DockAreas
		{
			get
			{
				return this.DockHandler.DockAreas;
			}
			set
			{
				this.DockHandler.DockAreas = value;
			}
		}
		[DefaultValue(0.25), LocalizedCategory("Category_Docking"), LocalizedDescription("DockContent_AutoHidePortion_Description")]
		public double AutoHidePortion
		{
			get
			{
				return this.DockHandler.AutoHidePortion;
			}
			set
			{
				this.DockHandler.AutoHidePortion = value;
			}
		}
		public string TabText
		{
			get
			{
				return this.m_tabText;
			}
			set
			{
				DockContentHandler arg_11_0 = this.DockHandler;
				this.m_tabText = value;
				arg_11_0.TabText = value;
			}
		}
		[DefaultValue(true), LocalizedCategory("Category_Docking"), LocalizedDescription("DockContent_CloseButton_Description")]
		public bool CloseButton
		{
			get
			{
				return this.DockHandler.CloseButton;
			}
			set
			{
				this.DockHandler.CloseButton = value;
			}
		}
		[DefaultValue(true), LocalizedCategory("Category_Docking"), LocalizedDescription("DockContent_CloseButtonVisible_Description")]
		public bool CloseButtonVisible
		{
			get
			{
				return this.DockHandler.CloseButtonVisible;
			}
			set
			{
				this.DockHandler.CloseButtonVisible = value;
			}
		}
		[Browsable(false)]
		public DockPanel DockPanel
		{
			get
			{
				return this.DockHandler.DockPanel;
			}
			set
			{
				this.DockHandler.DockPanel = value;
			}
		}
		[Browsable(false)]
		public DockState DockState
		{
			get
			{
				return this.DockHandler.DockState;
			}
			set
			{
				this.DockHandler.DockState = value;
			}
		}
		[Browsable(false)]
		public DockPane Pane
		{
			get
			{
				return this.DockHandler.Pane;
			}
			set
			{
				this.DockHandler.Pane = value;
			}
		}
		[Browsable(false)]
		public bool IsHidden
		{
			get
			{
				return this.DockHandler.IsHidden;
			}
			set
			{
				this.DockHandler.IsHidden = value;
			}
		}
		[Browsable(false)]
		public DockState VisibleState
		{
			get
			{
				return this.DockHandler.VisibleState;
			}
			set
			{
				this.DockHandler.VisibleState = value;
			}
		}
		[Browsable(false)]
		public bool IsFloat
		{
			get
			{
				return this.DockHandler.IsFloat;
			}
			set
			{
				this.DockHandler.IsFloat = value;
			}
		}
		[Browsable(false)]
		public DockPane PanelPane
		{
			get
			{
				return this.DockHandler.PanelPane;
			}
			set
			{
				this.DockHandler.PanelPane = value;
			}
		}
		[Browsable(false)]
		public DockPane FloatPane
		{
			get
			{
				return this.DockHandler.FloatPane;
			}
			set
			{
				this.DockHandler.FloatPane = value;
			}
		}
		[DefaultValue(false), LocalizedCategory("Category_Docking"), LocalizedDescription("DockContent_HideOnClose_Description")]
		public bool HideOnClose
		{
			get
			{
				return this.DockHandler.HideOnClose;
			}
			set
			{
				this.DockHandler.HideOnClose = value;
			}
		}
		[DefaultValue(DockState.Unknown), LocalizedCategory("Category_Docking"), LocalizedDescription("DockContent_ShowHint_Description")]
		public DockState ShowHint
		{
			get
			{
				return this.DockHandler.ShowHint;
			}
			set
			{
				this.DockHandler.ShowHint = value;
			}
		}
		[Browsable(false)]
		public bool IsActivated
		{
			get
			{
				return this.DockHandler.IsActivated;
			}
		}
		[DefaultValue(null), LocalizedCategory("Category_Docking"), LocalizedDescription("DockContent_TabPageContextMenu_Description")]
		public ContextMenu TabPageContextMenu
		{
			get
			{
				return this.DockHandler.TabPageContextMenu;
			}
			set
			{
				this.DockHandler.TabPageContextMenu = value;
			}
		}
		[DefaultValue(null), LocalizedCategory("Category_Docking"), LocalizedDescription("DockContent_TabPageContextMenuStrip_Description")]
		public ContextMenuStrip TabPageContextMenuStrip
		{
			get
			{
				return this.DockHandler.TabPageContextMenuStrip;
			}
			set
			{
				this.DockHandler.TabPageContextMenuStrip = value;
			}
		}
		[Category("Appearance"), DefaultValue(null), Localizable(true), LocalizedDescription("DockContent_ToolTipText_Description")]
		public string ToolTipText
		{
			get
			{
				return this.DockHandler.ToolTipText;
			}
			set
			{
				this.DockHandler.ToolTipText = value;
			}
		}
		public DockContent()
		{
			this.m_dockHandler = new DockContentHandler(this, new GetPersistStringCallback(this.GetPersistString));
			this.m_dockHandler.DockStateChanged += new EventHandler(this.DockHandler_DockStateChanged);
			base.ParentChanged += new EventHandler(this.DockContent_ParentChanged);
		}
		private void DockContent_ParentChanged(object Sender, EventArgs e)
		{
			if (base.Parent != null)
			{
				this.Font = base.Parent.Font;
			}
		}
		private bool ShouldSerializeTabText()
		{
			return this.m_tabText != null;
		}
		protected virtual string GetPersistString()
		{
			return base.GetType().ToString();
		}
		public bool IsDockStateValid(DockState dockState)
		{
			return this.DockHandler.IsDockStateValid(dockState);
		}
		public new void Activate()
		{
			this.DockHandler.Activate();
		}
		public new void Hide()
		{
			this.DockHandler.Hide();
		}
		public new void Show()
		{
			this.DockHandler.Show();
		}
		public void Show(DockPanel dockPanel)
		{
			this.DockHandler.Show(dockPanel);
		}
		public void Show(DockPanel dockPanel, DockState dockState)
		{
			this.DockHandler.Show(dockPanel, dockState);
		}
		public void Show(DockPanel dockPanel, Rectangle floatWindowBounds)
		{
			this.DockHandler.Show(dockPanel, floatWindowBounds);
		}
		public void Show(DockPane pane, IDockContent beforeContent)
		{
			this.DockHandler.Show(pane, beforeContent);
		}
		public void Show(DockPane previousPane, DockAlignment alignment, double proportion)
		{
			this.DockHandler.Show(previousPane, alignment, proportion);
		}
		public void FloatAt(Rectangle floatWindowBounds)
		{
			this.DockHandler.FloatAt(floatWindowBounds);
		}
		public void DockTo(DockPane paneTo, DockStyle dockStyle, int contentIndex)
		{
			this.DockHandler.DockTo(paneTo, dockStyle, contentIndex);
		}
		public void DockTo(DockPanel panel, DockStyle dockStyle)
		{
			this.DockHandler.DockTo(panel, dockStyle);
		}
		void IDockContent.OnActivated(EventArgs e)
		{
			this.OnActivated(e);
		}
		void IDockContent.OnDeactivate(EventArgs e)
		{
			this.OnDeactivate(e);
		}
		private void DockHandler_DockStateChanged(object sender, EventArgs e)
		{
			this.OnDockStateChanged(e);
		}
		protected virtual void OnDockStateChanged(EventArgs e)
		{
			EventHandler eventHandler = (EventHandler)base.Events[DockContent.DockStateChangedEvent];
			if (eventHandler != null)
			{
				eventHandler(this, e);
			}
		}
	}
}
