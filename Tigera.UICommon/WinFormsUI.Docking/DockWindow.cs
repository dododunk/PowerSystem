using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace WinFormsUI.Docking
{
	[ToolboxItem(false)]
	public class DockWindow : Panel, INestedPanesContainer, ISplitterDragSource, IDragSource
	{
		private class SplitterControl : SplitterBase
		{
			protected override int SplitterSize
			{
				get
				{
					return 4;
				}
			}
			protected override void StartDrag()
			{
				DockWindow dockWindow = base.Parent as DockWindow;
				if (dockWindow != null)
				{
					dockWindow.DockPanel.BeginDrag(dockWindow, dockWindow.RectangleToScreen(base.Bounds));
				}
			}
		}
		private DockPanel m_dockPanel;
		private DockState m_dockState;
		private DockWindow.SplitterControl m_splitter;
		private NestedPaneCollection m_nestedPanes;
		public VisibleNestedPaneCollection VisibleNestedPanes
		{
			get
			{
				return this.NestedPanes.VisibleNestedPanes;
			}
		}
		public NestedPaneCollection NestedPanes
		{
			get
			{
				return this.m_nestedPanes;
			}
		}
		public DockPanel DockPanel
		{
			get
			{
				return this.m_dockPanel;
			}
		}
		public DockState DockState
		{
			get
			{
				return this.m_dockState;
			}
		}
		public bool IsFloat
		{
			get
			{
				return this.DockState == DockState.Float;
			}
		}
		internal DockPane DefaultPane
		{
			get
			{
				return (this.VisibleNestedPanes.Count == 0) ? null : this.VisibleNestedPanes[0];
			}
		}
		public virtual Rectangle DisplayingRectangle
		{
			get
			{
				Rectangle clientRectangle = base.ClientRectangle;
				checked
				{
					if (!DockingHelper.HideDocumentWindowBorder && this.DockState == DockState.Document)
					{
						clientRectangle.X++;
						clientRectangle.Y++;
						clientRectangle.Width -= 2;
						clientRectangle.Height -= 2;
					}
					else
					{
						if (this.DockState == DockState.DockLeft)
						{
							clientRectangle.Width -= 4;
						}
						else
						{
							if (this.DockState == DockState.DockRight)
							{
								clientRectangle.X += 4;
								clientRectangle.Width -= 4;
							}
							else
							{
								if (this.DockState == DockState.DockTop)
								{
									clientRectangle.Height -= 4;
								}
								else
								{
									if (this.DockState == DockState.DockBottom)
									{
										clientRectangle.Y += 4;
										clientRectangle.Height -= 4;
									}
								}
							}
						}
					}
					return clientRectangle;
				}
			}
		}
		bool ISplitterDragSource.IsVertical
		{
			get
			{
				return this.DockState == DockState.DockLeft || this.DockState == DockState.DockRight;
			}
		}
		Rectangle ISplitterDragSource.DragLimitBounds
		{
			get
			{
				Rectangle dockArea = this.DockPanel.DockArea;
				Point location;
				if ((Control.ModifierKeys & Keys.Shift) == Keys.None)
				{
					location = base.Location;
				}
				else
				{
					location = this.DockPanel.DockArea.Location;
				}
				checked
				{
					if (((ISplitterDragSource)this).IsVertical)
					{
						dockArea.X += 24;
						dockArea.Width -= 48;
						dockArea.Y = location.Y;
						if ((Control.ModifierKeys & Keys.Shift) == Keys.None)
						{
							dockArea.Height = base.Height;
						}
					}
					else
					{
						dockArea.Y += 24;
						dockArea.Height -= 48;
						dockArea.X = location.X;
						if ((Control.ModifierKeys & Keys.Shift) == Keys.None)
						{
							dockArea.Width = base.Width;
						}
					}
					return this.DockPanel.RectangleToScreen(dockArea);
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
		internal DockWindow(DockPanel dockPanel, DockState dockState)
		{
			this.m_nestedPanes = new NestedPaneCollection(this);
			this.m_dockPanel = dockPanel;
			this.m_dockState = dockState;
			base.Visible = false;
			base.SuspendLayout();
			if (this.DockState == DockState.DockLeft || this.DockState == DockState.DockRight || this.DockState == DockState.DockTop || this.DockState == DockState.DockBottom)
			{
				this.m_splitter = new DockWindow.SplitterControl();
				base.Controls.Add(this.m_splitter);
			}
			if (this.DockState == DockState.DockLeft)
			{
				this.Dock = DockStyle.Left;
				this.m_splitter.Dock = DockStyle.Right;
			}
			else
			{
				if (this.DockState == DockState.DockRight)
				{
					this.Dock = DockStyle.Right;
					this.m_splitter.Dock = DockStyle.Left;
				}
				else
				{
					if (this.DockState == DockState.DockTop)
					{
						this.Dock = DockStyle.Top;
						this.m_splitter.Dock = DockStyle.Bottom;
					}
					else
					{
						if (this.DockState == DockState.DockBottom)
						{
							this.Dock = DockStyle.Bottom;
							this.m_splitter.Dock = DockStyle.Top;
						}
						else
						{
							if (this.DockState == DockState.Document)
							{
								this.Dock = DockStyle.Fill;
							}
						}
					}
				}
			}
			base.ResumeLayout();
		}
		protected override void OnPaint(PaintEventArgs e)
		{
			checked
			{
				if (!DockingHelper.HideDocumentWindowBorder && this.DockState == DockState.Document)
				{
					e.Graphics.DrawRectangle(SystemPens.ControlDark, base.ClientRectangle.X, base.ClientRectangle.Y, base.ClientRectangle.Width - 1, base.ClientRectangle.Height - 1);
				}
				base.OnPaint(e);
			}
		}
		protected override void OnLayout(LayoutEventArgs levent)
		{
			this.VisibleNestedPanes.Refresh();
			if (this.VisibleNestedPanes.Count == 0)
			{
				if (base.Visible)
				{
					base.Visible = false;
				}
			}
			else
			{
				if (!base.Visible)
				{
					base.Visible = true;
					this.VisibleNestedPanes.Refresh();
				}
			}
			base.OnLayout(levent);
		}
		void ISplitterDragSource.BeginDrag(Rectangle rectSplitter)
		{
		}
		void ISplitterDragSource.EndDrag()
		{
		}
		void ISplitterDragSource.MoveSplitter(int offset)
		{
			if ((Control.ModifierKeys & Keys.Shift) != Keys.None)
			{
				base.SendToBack();
			}
			Rectangle dockArea = this.DockPanel.DockArea;
			if (this.DockState == DockState.DockLeft && dockArea.Width > 0)
			{
				if (this.DockPanel.DockLeftPortion > 1.0)
				{
					this.DockPanel.DockLeftPortion = (double)checked(base.Width + offset);
				}
				else
				{
					this.DockPanel.DockLeftPortion += (double)offset / (double)dockArea.Width;
				}
			}
			else
			{
				if (this.DockState == DockState.DockRight && dockArea.Width > 0)
				{
					if (this.DockPanel.DockRightPortion > 1.0)
					{
						this.DockPanel.DockRightPortion = (double)checked(base.Width - offset);
					}
					else
					{
						this.DockPanel.DockRightPortion -= (double)offset / (double)dockArea.Width;
					}
				}
				else
				{
					if (this.DockState == DockState.DockBottom && dockArea.Height > 0)
					{
						if (this.DockPanel.DockBottomPortion > 1.0)
						{
							this.DockPanel.DockBottomPortion = (double)checked(base.Height - offset);
						}
						else
						{
							this.DockPanel.DockBottomPortion -= (double)offset / (double)dockArea.Height;
						}
					}
					else
					{
						if (this.DockState == DockState.DockTop && dockArea.Height > 0)
						{
							if (this.DockPanel.DockTopPortion > 1.0)
							{
								this.DockPanel.DockTopPortion = (double)checked(base.Height + offset);
							}
							else
							{
								this.DockPanel.DockTopPortion += (double)offset / (double)dockArea.Height;
							}
						}
					}
				}
			}
		}
	}
}
