using System;
using System.Drawing;
using System.Security.Permissions;
using System.Windows.Forms;
namespace WinFormsUI.Docking
{
	public class FloatWindow : Form, INestedPanesContainer, IDockDragSource, IDragSource
	{
		internal const int WM_CHECKDISPOSE = 1025;
		private NestedPaneCollection m_nestedPanes;
		private bool m_allowEndUserDocking = true;
		private DockPanel m_dockPanel;
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
		public NestedPaneCollection NestedPanes
		{
			get
			{
				return this.m_nestedPanes;
			}
		}
		public VisibleNestedPaneCollection VisibleNestedPanes
		{
			get
			{
				return this.NestedPanes.VisibleNestedPanes;
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
				return DockState.Float;
			}
		}
		public bool IsFloat
		{
			get
			{
				return this.DockState == DockState.Float;
			}
		}
		public virtual Rectangle DisplayingRectangle
		{
			get
			{
				return base.ClientRectangle;
			}
		}
		Control IDragSource.DragControl
		{
			get
			{
				return this;
			}
		}
		protected internal FloatWindow(DockPanel dockPanel, DockPane pane)
		{
			this.InternalConstruct(dockPanel, pane, false, Rectangle.Empty);
		}
		protected internal FloatWindow(DockPanel dockPanel, DockPane pane, Rectangle bounds)
		{
			this.InternalConstruct(dockPanel, pane, true, bounds);
		}
		private void InternalConstruct(DockPanel dockPanel, DockPane pane, bool boundsSpecified, Rectangle bounds)
		{
			if (dockPanel == null)
			{
				throw new ArgumentNullException(Strings.FloatWindow_Constructor_NullDockPanel);
			}
			this.m_nestedPanes = new NestedPaneCollection(this);
			base.FormBorderStyle = FormBorderStyle.SizableToolWindow;
			base.ShowInTaskbar = false;
			if (dockPanel.RightToLeft != this.RightToLeft)
			{
				this.RightToLeft = dockPanel.RightToLeft;
			}
			if (this.RightToLeftLayout != dockPanel.RightToLeftLayout)
			{
				this.RightToLeftLayout = dockPanel.RightToLeftLayout;
			}
			base.SuspendLayout();
			if (boundsSpecified)
			{
				base.Bounds = bounds;
				base.StartPosition = FormStartPosition.Manual;
			}
			else
			{
				base.StartPosition = FormStartPosition.WindowsDefaultLocation;
				base.Size = dockPanel.DefaultFloatWindowSize;
			}
			this.m_dockPanel = dockPanel;
			base.Owner = this.DockPanel.FindForm();
			this.DockPanel.AddFloatWindow(this);
			if (pane != null)
			{
				pane.FloatWindow = this;
			}
			base.ResumeLayout();
		}
		protected override void Dispose(bool disposing)
		{
			if (disposing)
			{
				if (this.DockPanel != null)
				{
					this.DockPanel.RemoveFloatWindow(this);
				}
				this.m_dockPanel = null;
			}
			base.Dispose(disposing);
		}
		internal bool IsDockStateValid(DockState dockState)
		{
			bool result;
			foreach (DockPane current in this.NestedPanes)
			{
				foreach (IDockContent current2 in current.Contents)
				{
					if (!DockHelper.IsDockStateValid(dockState, current2.DockHandler.DockAreas))
					{
						result = false;
						return result;
					}
				}
			}
			result = true;
			return result;
		}
		protected override void OnActivated(EventArgs e)
		{
			this.DockPanel.FloatWindows.BringWindowToFront(this);
			base.OnActivated(e);
			foreach (DockPane current in this.VisibleNestedPanes)
			{
				foreach (IDockContent current2 in current.Contents)
				{
					current2.OnActivated(e);
				}
			}
		}
		protected override void OnDeactivate(EventArgs e)
		{
			base.OnDeactivate(e);
			foreach (DockPane current in this.VisibleNestedPanes)
			{
				foreach (IDockContent current2 in current.Contents)
				{
					current2.OnDeactivate(e);
				}
			}
		}
		protected override void OnLayout(LayoutEventArgs levent)
		{
			this.VisibleNestedPanes.Refresh();
			this.RefreshChanges();
			base.Visible = (this.VisibleNestedPanes.Count > 0);
			this.SetText();
			base.OnLayout(levent);
		}
		internal void SetText()
		{
			DockPane dockPane = (this.VisibleNestedPanes.Count == 1) ? this.VisibleNestedPanes[0] : null;
			if (dockPane == null)
			{
				this.Text = " ";
			}
			else
			{
				if (dockPane.ActiveContent == null)
				{
					this.Text = " ";
				}
				else
				{
					this.Text = dockPane.ActiveContent.DockHandler.TabText;
				}
			}
		}
		protected override void SetBoundsCore(int x, int y, int width, int height, BoundsSpecified specified)
		{
			Rectangle virtualScreen = SystemInformation.VirtualScreen;
			checked
			{
				if (y + height > virtualScreen.Bottom)
				{
					y -= y + height - virtualScreen.Bottom;
				}
				if (y < virtualScreen.Top)
				{
					y += virtualScreen.Top - y;
				}
				base.SetBoundsCore(x, y, width, height, specified);
			}
		}
		[SecurityPermission(SecurityAction.LinkDemand, Flags = SecurityPermissionFlag.UnmanagedCode)]
		protected override void WndProc(ref Message m)
		{
			checked
			{
				if (m.Msg == 161)
				{
					if (!base.IsDisposed)
					{
						uint num = NativeMethods.SendMessage(base.Handle, 132, 0u, (uint)((int)m.LParam));
						if (num == 2u && this.DockPanel.AllowEndUserDocking && this.AllowEndUserDocking)
						{
							base.Activate();
							this.m_dockPanel.BeginDrag(this);
						}
						else
						{
							base.WndProc(ref m);
						}
					}
				}
				else
				{
					if (m.Msg == 164)
					{
						uint num = NativeMethods.SendMessage(base.Handle, 132, 0u, (uint)((int)m.LParam));
						if (num == 2u)
						{
							DockPane dockPane = (this.VisibleNestedPanes.Count == 1) ? this.VisibleNestedPanes[0] : null;
							if (dockPane != null && dockPane.ActiveContent != null)
							{
								dockPane.ShowTabPageContextMenu(this, base.PointToClient(Control.MousePosition));
								return;
							}
						}
						base.WndProc(ref m);
					}
					else
					{
						if (m.Msg == 16)
						{
							if (this.NestedPanes.Count == 0)
							{
								base.WndProc(ref m);
							}
							else
							{
								for (int i = this.NestedPanes.Count - 1; i >= 0; i--)
								{
									DockContentCollection contents = this.NestedPanes[i].Contents;
									for (int j = contents.Count - 1; j >= 0; j--)
									{
										IDockContent dockContent = contents[j];
										if (dockContent.DockHandler.DockState == DockState.Float)
										{
											if (dockContent.DockHandler.CloseButton)
											{
												if (dockContent.DockHandler.HideOnClose)
												{
													dockContent.DockHandler.Hide();
												}
												else
												{
													dockContent.DockHandler.Close();
												}
											}
										}
									}
								}
							}
						}
						else
						{
							if (m.Msg == 163)
							{
								uint num = NativeMethods.SendMessage(base.Handle, 132, 0u, (uint)((int)m.LParam));
								if (num != 2u)
								{
									base.WndProc(ref m);
								}
								else
								{
									this.DockPanel.SuspendLayout(true);
									foreach (DockPane current in this.NestedPanes)
									{
										if (current.DockState == DockState.Float)
										{
											current.RestoreToPanel();
										}
									}
									this.DockPanel.ResumeLayout(true, true);
								}
							}
							else
							{
								if (m.Msg == 1025)
								{
									if (this.NestedPanes.Count == 0)
									{
										base.Dispose();
									}
								}
								else
								{
									base.WndProc(ref m);
								}
							}
						}
					}
				}
			}
		}
		internal void RefreshChanges()
		{
			checked
			{
				if (!base.IsDisposed)
				{
					if (this.VisibleNestedPanes.Count == 0)
					{
						base.ControlBox = true;
					}
					else
					{
						for (int i = this.VisibleNestedPanes.Count - 1; i >= 0; i--)
						{
							DockContentCollection contents = this.VisibleNestedPanes[i].Contents;
							for (int j = contents.Count - 1; j >= 0; j--)
							{
								IDockContent dockContent = contents[j];
								if (dockContent.DockHandler.DockState == DockState.Float)
								{
									if (dockContent.DockHandler.CloseButton && dockContent.DockHandler.CloseButtonVisible)
									{
										base.ControlBox = true;
										return;
									}
								}
							}
						}
						if (base.ControlBox)
						{
							base.ControlBox = false;
						}
					}
				}
			}
		}
		internal void TestDrop(IDockDragSource dragSource, DockOutlineBase dockOutline)
		{
			if (this.VisibleNestedPanes.Count == 1)
			{
				DockPane pane = this.VisibleNestedPanes[0];
				if (dragSource.CanDockTo(pane))
				{
					Point mousePosition = Control.MousePosition;
					uint lParam = Win32Helper.MakeLong(mousePosition.X, mousePosition.Y);
					if (NativeMethods.SendMessage(base.Handle, 132, 0u, lParam) == 2u)
					{
						dockOutline.Show(this.VisibleNestedPanes[0], -1);
					}
				}
			}
		}
		bool IDockDragSource.IsDockStateValid(DockState dockState)
		{
			return this.IsDockStateValid(dockState);
		}
		bool IDockDragSource.CanDockTo(DockPane pane)
		{
			return this.IsDockStateValid(pane.DockState) && pane.FloatWindow != this;
		}
		Rectangle IDockDragSource.BeginDrag(Point ptMouse)
		{
			return base.Bounds;
		}
		public void FloatAt(Rectangle floatWindowBounds)
		{
			base.Bounds = floatWindowBounds;
		}
		public void DockTo(DockPane pane, DockStyle dockStyle, int contentIndex)
		{
			checked
			{
				if (dockStyle == DockStyle.Fill)
				{
					for (int i = this.NestedPanes.Count - 1; i >= 0; i--)
					{
						DockPane dockPane = this.NestedPanes[i];
						for (int j = dockPane.Contents.Count - 1; j >= 0; j--)
						{
							IDockContent dockContent = dockPane.Contents[j];
							dockContent.DockHandler.Pane = pane;
							if (contentIndex != -1)
							{
								pane.SetContentIndex(dockContent, contentIndex);
							}
							dockContent.DockHandler.Activate();
						}
					}
				}
				else
				{
					DockAlignment alignment = DockAlignment.Left;
					if (dockStyle == DockStyle.Left)
					{
						alignment = DockAlignment.Left;
					}
					else
					{
						if (dockStyle == DockStyle.Right)
						{
							alignment = DockAlignment.Right;
						}
						else
						{
							if (dockStyle == DockStyle.Top)
							{
								alignment = DockAlignment.Top;
							}
							else
							{
								if (dockStyle == DockStyle.Bottom)
								{
									alignment = DockAlignment.Bottom;
								}
							}
						}
					}
					FloatWindow.MergeNestedPanes(this.VisibleNestedPanes, pane.NestedPanesContainer.NestedPanes, pane, alignment, 0.5);
				}
			}
		}
		public void DockTo(DockPanel panel, DockStyle dockStyle)
		{
			if (panel != this.DockPanel)
			{
				throw new ArgumentException(Strings.IDockDragSource_DockTo_InvalidPanel, "panel");
			}
			NestedPaneCollection nestedPaneCollection = null;
			if (dockStyle == DockStyle.Top)
			{
				nestedPaneCollection = this.DockPanel.DockWindows[DockState.DockTop].NestedPanes;
			}
			else
			{
				if (dockStyle == DockStyle.Bottom)
				{
					nestedPaneCollection = this.DockPanel.DockWindows[DockState.DockBottom].NestedPanes;
				}
				else
				{
					if (dockStyle == DockStyle.Left)
					{
						nestedPaneCollection = this.DockPanel.DockWindows[DockState.DockLeft].NestedPanes;
					}
					else
					{
						if (dockStyle == DockStyle.Right)
						{
							nestedPaneCollection = this.DockPanel.DockWindows[DockState.DockRight].NestedPanes;
						}
						else
						{
							if (dockStyle == DockStyle.Fill)
							{
								nestedPaneCollection = this.DockPanel.DockWindows[DockState.Document].NestedPanes;
							}
						}
					}
				}
			}
			DockPane prevPane = null;
			checked
			{
				for (int i = nestedPaneCollection.Count - 1; i >= 0; i--)
				{
					if (nestedPaneCollection[i] != this.VisibleNestedPanes[0])
					{
						prevPane = nestedPaneCollection[i];
					}
				}
				FloatWindow.MergeNestedPanes(this.VisibleNestedPanes, nestedPaneCollection, prevPane, DockAlignment.Left, 0.5);
			}
		}
		private static void MergeNestedPanes(VisibleNestedPaneCollection nestedPanesFrom, NestedPaneCollection nestedPanesTo, DockPane prevPane, DockAlignment alignment, double proportion)
		{
			checked
			{
				if (nestedPanesFrom.Count != 0)
				{
					int count = nestedPanesFrom.Count;
					DockPane[] array = new DockPane[count];
					DockPane[] array2 = new DockPane[count];
					DockAlignment[] array3 = new DockAlignment[count];
					double[] array4 = new double[count];
					for (int i = 0; i < count; i++)
					{
						array[i] = nestedPanesFrom[i];
						array2[i] = nestedPanesFrom[i].NestedDockingStatus.PreviousPane;
						array3[i] = nestedPanesFrom[i].NestedDockingStatus.Alignment;
						array4[i] = nestedPanesFrom[i].NestedDockingStatus.Proportion;
					}
					DockPane dockPane = array[0].DockTo(nestedPanesTo.Container, prevPane, alignment, proportion);
					array[0].DockState = nestedPanesTo.DockState;
					for (int i = 1; i < count; i++)
					{
						for (int j = i; j < count; j++)
						{
							if (array2[j] == array[i - 1])
							{
								array2[j] = dockPane;
							}
						}
						dockPane = array[i].DockTo(nestedPanesTo.Container, array2[i], array3[i], array4[i]);
						array[i].DockState = nestedPanesTo.DockState;
					}
				}
			}
		}
	}
}
