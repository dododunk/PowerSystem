using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.Design;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Globalization;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using System.Windows.Forms.Design;
using System.Xml;
using WinFormsUI.Docking.Win32;
namespace WinFormsUI.Docking
{
	[DefaultEvent("ActiveContentChanged"), DefaultProperty("DocumentStyle"), /*Designer(typeof(ControlDesigner)), */ToolboxBitmap(typeof(resfinder), "WinFormsUI.Docking.DockPanel.bmp"), LocalizedDescription("DockPanel_Description")]
	public class DockPanel : Panel
	{
		private class AutoHideWindowControl : Panel, ISplitterDragSource, IDragSource
		{
			private class SplitterControl : SplitterBase
			{
				private DockPanel.AutoHideWindowControl m_autoHideWindow;
				private DockPanel.AutoHideWindowControl AutoHideWindow
				{
					get
					{
						return this.m_autoHideWindow;
					}
				}
				protected override int SplitterSize
				{
					get
					{
						return 4;
					}
				}
				public SplitterControl(DockPanel.AutoHideWindowControl autoHideWindow)
				{
					this.m_autoHideWindow = autoHideWindow;
				}
				protected override void StartDrag()
				{
					this.AutoHideWindow.DockPanel.BeginDrag(this.AutoHideWindow, this.AutoHideWindow.RectangleToScreen(base.Bounds));
				}
			}
			private const int ANIMATE_TIME = 100;
			private System.Windows.Forms.Timer m_timerMouseTrack;
			private DockPanel.AutoHideWindowControl.SplitterControl m_splitter;
			private DockPanel m_dockPanel = null;
			private DockPane m_activePane = null;
			private IDockContent m_activeContent = null;
			private bool m_flagAnimate = true;
			private bool m_flagDragging = false;
			public DockPanel DockPanel
			{
				get
				{
					return this.m_dockPanel;
				}
			}
			public DockPane ActivePane
			{
				get
				{
					return this.m_activePane;
				}
			}
			public IDockContent ActiveContent
			{
				get
				{
					return this.m_activeContent;
				}
				set
				{
					if (value != this.m_activeContent)
					{
						if (value != null)
						{
							if (!DockHelper.IsDockStateAutoHide(value.DockHandler.DockState) || value.DockHandler.DockPanel != this.DockPanel)
							{
								throw new InvalidOperationException(Strings.DockPanel_ActiveAutoHideContent_InvalidValue);
							}
						}
						this.DockPanel.SuspendLayout();
						if (this.m_activeContent != null)
						{
							if (this.m_activeContent.DockHandler.Form.ContainsFocus)
							{
								this.DockPanel.ContentFocusManager.GiveUpFocus(this.m_activeContent);
							}
							this.AnimateWindow(false);
						}
						this.m_activeContent = value;
						this.SetActivePane();
						if (this.ActivePane != null)
						{
							this.ActivePane.ActiveContent = this.m_activeContent;
						}
						if (this.m_activeContent != null)
						{
							this.AnimateWindow(true);
						}
						this.DockPanel.ResumeLayout();
						this.DockPanel.RefreshAutoHideStrip();
						this.SetTimerMouseTrack();
					}
				}
			}
			public DockState DockState
			{
				get
				{
					return (this.ActiveContent == null) ? DockState.Unknown : this.ActiveContent.DockHandler.DockState;
				}
			}
			private bool FlagAnimate
			{
				get
				{
					return this.m_flagAnimate;
				}
				set
				{
					this.m_flagAnimate = value;
				}
			}
			internal bool FlagDragging
			{
				get
				{
					return this.m_flagDragging;
				}
				set
				{
					if (this.m_flagDragging != value)
					{
						this.m_flagDragging = value;
						this.SetTimerMouseTrack();
					}
				}
			}
			protected virtual Rectangle DisplayingRectangle
			{
				get
				{
					Rectangle clientRectangle = base.ClientRectangle;
					checked
					{
						if (this.DockState == DockState.DockBottomAutoHide)
						{
							clientRectangle.Y += 6;
							clientRectangle.Height -= 6;
						}
						else
						{
							if (this.DockState == DockState.DockRightAutoHide)
							{
								clientRectangle.X += 6;
								clientRectangle.Width -= 6;
							}
							else
							{
								if (this.DockState == DockState.DockTopAutoHide)
								{
									clientRectangle.Height -= 6;
								}
								else
								{
									if (this.DockState == DockState.DockLeftAutoHide)
									{
										clientRectangle.Width -= 6;
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
					return this.DockState == DockState.DockLeftAutoHide || this.DockState == DockState.DockRightAutoHide;
				}
			}
			Rectangle ISplitterDragSource.DragLimitBounds
			{
				get
				{
					Rectangle dockArea = this.DockPanel.DockArea;
					checked
					{
						if (((ISplitterDragSource)this).IsVertical)
						{
							dockArea.X += 24;
							dockArea.Width -= 48;
						}
						else
						{
							dockArea.Y += 24;
							dockArea.Height -= 48;
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
			public AutoHideWindowControl(DockPanel dockPanel)
			{
				this.m_dockPanel = dockPanel;
				this.m_timerMouseTrack = new System.Windows.Forms.Timer();
				this.m_timerMouseTrack.Tick += new EventHandler(this.TimerMouseTrack_Tick);
				base.Visible = false;
				this.m_splitter = new DockPanel.AutoHideWindowControl.SplitterControl(this);
				base.Controls.Add(this.m_splitter);
			}
			protected override void Dispose(bool disposing)
			{
				if (disposing)
				{
					this.m_timerMouseTrack.Dispose();
				}
				base.Dispose(disposing);
			}
			private void SetActivePane()
			{
				DockPane dockPane = (this.ActiveContent == null) ? null : this.ActiveContent.DockHandler.Pane;
				if (dockPane != this.m_activePane)
				{
					this.m_activePane = dockPane;
				}
			}
			private void AnimateWindow(bool show)
			{
				checked
				{
					if (!this.FlagAnimate && base.Visible != show)
					{
						base.Visible = show;
					}
					else
					{
						base.Parent.SuspendLayout();
						Rectangle rectangle = this.GetRectangle(!show);
						Rectangle rectangle2 = this.GetRectangle(show);
						int num4;
						int num3;
						int num2;
						int num = num2 = (num3 = (num4 = 0));
						if (this.DockState == DockState.DockTopAutoHide)
						{
							num4 = (show ? 1 : -1);
						}
						else
						{
							if (this.DockState == DockState.DockLeftAutoHide)
							{
								num3 = (show ? 1 : -1);
							}
							else
							{
								if (this.DockState == DockState.DockRightAutoHide)
								{
									num2 = (show ? -1 : 1);
									num3 = (show ? 1 : -1);
								}
								else
								{
									if (this.DockState == DockState.DockBottomAutoHide)
									{
										num = (show ? -1 : 1);
										num4 = (show ? 1 : -1);
									}
								}
							}
						}
						if (show)
						{
							base.Bounds = this.DockPanel.GetAutoHideWindowBounds(new Rectangle(0 - rectangle2.Width, 0 - rectangle2.Height, rectangle2.Width, rectangle2.Height));
							if (!base.Visible)
							{
								base.Visible = true;
							}
							base.PerformLayout();
						}
						base.SuspendLayout();
						this.LayoutAnimateWindow(rectangle);
						if (!base.Visible)
						{
							base.Visible = true;
						}
						int num5 = 1;
						int num6 = (rectangle.Width != rectangle2.Width) ? Math.Abs(rectangle.Width - rectangle2.Width) : Math.Abs(rectangle.Height - rectangle2.Height);
						int num7 = num6;
						DateTime now = DateTime.Now;
						while (rectangle != rectangle2)
						{
							DateTime now2 = DateTime.Now;
							rectangle.X += num2 * num5;
							rectangle.Y += num * num5;
							rectangle.Width += num3 * num5;
							rectangle.Height += num4 * num5;
							if (Math.Sign(rectangle2.X - rectangle.X) != Math.Sign(num2))
							{
								rectangle.X = rectangle2.X;
							}
							if (Math.Sign(rectangle2.Y - rectangle.Y) != Math.Sign(num))
							{
								rectangle.Y = rectangle2.Y;
							}
							if (Math.Sign(rectangle2.Width - rectangle.Width) != Math.Sign(num3))
							{
								rectangle.Width = rectangle2.Width;
							}
							if (Math.Sign(rectangle2.Height - rectangle.Height) != Math.Sign(num4))
							{
								rectangle.Height = rectangle2.Height;
							}
							this.LayoutAnimateWindow(rectangle);
							if (base.Parent != null)
							{
								base.Parent.Update();
							}
							num7 -= num5;
							do
							{
								TimeSpan t = new TimeSpan(0, 0, 0, 0, 100);
								TimeSpan timeSpan = DateTime.Now - now2;
								TimeSpan t2 = DateTime.Now - now;
								if ((int)(t - t2).TotalMilliseconds <= 0)
								{
									goto Block_22;
								}
								num5 = num7 * (int)timeSpan.TotalMilliseconds / (int)(t - t2).TotalMilliseconds;
							}
							while (num5 < 1);
							continue;
							Block_22:
							num5 = num7;
						}
						base.ResumeLayout();
						base.Parent.ResumeLayout();
					}
				}
			}
			private void LayoutAnimateWindow(Rectangle rect)
			{
				base.Bounds = this.DockPanel.GetAutoHideWindowBounds(rect);
				Rectangle clientRectangle = base.ClientRectangle;
				checked
				{
					if (this.DockState == DockState.DockLeftAutoHide)
					{
						this.ActivePane.Location = new Point(clientRectangle.Right - 2 - 4 - this.ActivePane.Width, this.ActivePane.Location.Y);
					}
					else
					{
						if (this.DockState == DockState.DockTopAutoHide)
						{
							this.ActivePane.Location = new Point(this.ActivePane.Location.X, clientRectangle.Bottom - 2 - 4 - this.ActivePane.Height);
						}
					}
				}
			}
			private Rectangle GetRectangle(bool show)
			{
				checked
				{
					Rectangle result;
					if (this.DockState == DockState.Unknown)
					{
						result = Rectangle.Empty;
					}
					else
					{
						Rectangle autoHideWindowRectangle = this.DockPanel.AutoHideWindowRectangle;
						if (show)
						{
							result = autoHideWindowRectangle;
						}
						else
						{
							if (this.DockState == DockState.DockLeftAutoHide)
							{
								autoHideWindowRectangle.Width = 0;
							}
							else
							{
								if (this.DockState == DockState.DockRightAutoHide)
								{
									autoHideWindowRectangle.X += autoHideWindowRectangle.Width;
									autoHideWindowRectangle.Width = 0;
								}
								else
								{
									if (this.DockState == DockState.DockTopAutoHide)
									{
										autoHideWindowRectangle.Height = 0;
									}
									else
									{
										autoHideWindowRectangle.Y += autoHideWindowRectangle.Height;
										autoHideWindowRectangle.Height = 0;
									}
								}
							}
							result = autoHideWindowRectangle;
						}
					}
					return result;
				}
			}
			private void SetTimerMouseTrack()
			{
				if (this.ActivePane == null || this.ActivePane.IsActivated || this.FlagDragging)
				{
					this.m_timerMouseTrack.Enabled = false;
				}
				else
				{
					int num = SystemInformation.MouseHoverTime;
					if (num <= 0)
					{
						num = 400;
					}
					this.m_timerMouseTrack.Interval = checked(2 * num);
					this.m_timerMouseTrack.Enabled = true;
				}
			}
			protected override void OnLayout(LayoutEventArgs levent)
			{
				base.DockPadding.All = 0;
				if (this.DockState == DockState.DockLeftAutoHide)
				{
					base.DockPadding.Right = 2;
					this.m_splitter.Dock = DockStyle.Right;
				}
				else
				{
					if (this.DockState == DockState.DockRightAutoHide)
					{
						base.DockPadding.Left = 2;
						this.m_splitter.Dock = DockStyle.Left;
					}
					else
					{
						if (this.DockState == DockState.DockTopAutoHide)
						{
							base.DockPadding.Bottom = 2;
							this.m_splitter.Dock = DockStyle.Bottom;
						}
						else
						{
							if (this.DockState == DockState.DockBottomAutoHide)
							{
								base.DockPadding.Top = 2;
								this.m_splitter.Dock = DockStyle.Top;
							}
						}
					}
				}
				Rectangle displayingRectangle = this.DisplayingRectangle;
				Rectangle bounds = new Rectangle(checked(0 - displayingRectangle.Width), displayingRectangle.Y, displayingRectangle.Width, displayingRectangle.Height);
				foreach (Control control in base.Controls)
				{
					DockPane dockPane = control as DockPane;
					if (dockPane != null)
					{
						if (dockPane == this.ActivePane)
						{
							dockPane.Bounds = displayingRectangle;
						}
						else
						{
							dockPane.Bounds = bounds;
						}
					}
				}
				base.OnLayout(levent);
			}
			protected override void OnPaint(PaintEventArgs e)
			{
				Graphics graphics = e.Graphics;
				checked
				{
					if (this.DockState == DockState.DockBottomAutoHide)
					{
						graphics.DrawLine(SystemPens.ControlLightLight, 0, 1, base.ClientRectangle.Right, 1);
					}
					else
					{
						if (this.DockState == DockState.DockRightAutoHide)
						{
							graphics.DrawLine(SystemPens.ControlLightLight, 1, 0, 1, base.ClientRectangle.Bottom);
						}
						else
						{
							if (this.DockState == DockState.DockTopAutoHide)
							{
								graphics.DrawLine(SystemPens.ControlDark, 0, base.ClientRectangle.Height - 2, base.ClientRectangle.Right, base.ClientRectangle.Height - 2);
								graphics.DrawLine(SystemPens.ControlDarkDark, 0, base.ClientRectangle.Height - 1, base.ClientRectangle.Right, base.ClientRectangle.Height - 1);
							}
							else
							{
								if (this.DockState == DockState.DockLeftAutoHide)
								{
									graphics.DrawLine(SystemPens.ControlDark, base.ClientRectangle.Width - 2, 0, base.ClientRectangle.Width - 2, base.ClientRectangle.Bottom);
									graphics.DrawLine(SystemPens.ControlDarkDark, base.ClientRectangle.Width - 1, 0, base.ClientRectangle.Width - 1, base.ClientRectangle.Bottom);
								}
							}
						}
					}
					base.OnPaint(e);
				}
			}
			public void RefreshActiveContent()
			{
				if (this.ActiveContent != null)
				{
					if (!DockHelper.IsDockStateAutoHide(this.ActiveContent.DockHandler.DockState))
					{
						this.FlagAnimate = false;
						this.ActiveContent = null;
						this.FlagAnimate = true;
					}
				}
			}
			public void RefreshActivePane()
			{
				this.SetTimerMouseTrack();
			}
			private void TimerMouseTrack_Tick(object sender, EventArgs e)
			{
				if (!base.IsDisposed)
				{
					if (this.ActivePane == null || this.ActivePane.IsActivated)
					{
						this.m_timerMouseTrack.Enabled = false;
					}
					else
					{
						DockPane activePane = this.ActivePane;
						Point pt = base.PointToClient(Control.MousePosition);
						Point pt2 = this.DockPanel.PointToClient(Control.MousePosition);
						Rectangle tabStripRectangle = this.DockPanel.GetTabStripRectangle(activePane.DockState);
						if (!base.ClientRectangle.Contains(pt) && !tabStripRectangle.Contains(pt2))
						{
							this.ActiveContent = null;
							this.m_timerMouseTrack.Enabled = false;
						}
					}
				}
			}
			void ISplitterDragSource.BeginDrag(Rectangle rectSplitter)
			{
				this.FlagDragging = true;
			}
			void ISplitterDragSource.EndDrag()
			{
				this.FlagDragging = false;
			}
			void ISplitterDragSource.MoveSplitter(int offset)
			{
				Rectangle dockArea = this.DockPanel.DockArea;
				IDockContent activeContent = this.ActiveContent;
				if (this.DockState == DockState.DockLeftAutoHide && dockArea.Width > 0)
				{
					if (activeContent.DockHandler.AutoHidePortion < 1.0)
					{
						activeContent.DockHandler.AutoHidePortion += (double)offset / (double)dockArea.Width;
					}
					else
					{
						activeContent.DockHandler.AutoHidePortion = (double)checked(base.Width + offset);
					}
				}
				else
				{
					if (this.DockState == DockState.DockRightAutoHide && dockArea.Width > 0)
					{
						if (activeContent.DockHandler.AutoHidePortion < 1.0)
						{
							activeContent.DockHandler.AutoHidePortion -= (double)offset / (double)dockArea.Width;
						}
						else
						{
							activeContent.DockHandler.AutoHidePortion = (double)checked(base.Width - offset);
						}
					}
					else
					{
						if (this.DockState == DockState.DockBottomAutoHide && dockArea.Height > 0)
						{
							if (activeContent.DockHandler.AutoHidePortion < 1.0)
							{
								activeContent.DockHandler.AutoHidePortion -= (double)offset / (double)dockArea.Height;
							}
							else
							{
								activeContent.DockHandler.AutoHidePortion = (double)checked(base.Height - offset);
							}
						}
						else
						{
							if (this.DockState == DockState.DockTopAutoHide && dockArea.Height > 0)
							{
								if (activeContent.DockHandler.AutoHidePortion < 1.0)
								{
									activeContent.DockHandler.AutoHidePortion += (double)offset / (double)dockArea.Height;
								}
								else
								{
									activeContent.DockHandler.AutoHidePortion = (double)checked(base.Height + offset);
								}
							}
						}
					}
				}
			}
		}
		private abstract class DragHandlerBase : NativeWindow, IMessageFilter
		{
			private Point m_startMousePosition = Point.Empty;
			protected abstract Control DragControl
			{
				get;
			}
			protected Point StartMousePosition
			{
				get
				{
					return this.m_startMousePosition;
				}
				private set
				{
					this.m_startMousePosition = value;
				}
			}
			protected bool BeginDrag()
			{
				bool flag = false;
				bool result;
				try
				{
					Monitor.Enter(this, ref flag);
					if (this.DragControl == null)
					{
						result = false;
					}
					else
					{
						this.StartMousePosition = Control.MousePosition;
						if (!NativeMethods.DragDetect(this.DragControl.Handle, this.StartMousePosition))
						{
							result = false;
						}
						else
						{
							this.DragControl.FindForm().Capture = true;
							base.AssignHandle(this.DragControl.FindForm().Handle);
							Application.AddMessageFilter(this);
							result = true;
						}
					}
				}
				finally
				{
					if (flag)
					{
						Monitor.Exit(this);
					}
				}
				return result;
			}
			protected abstract void OnDragging();
			protected abstract void OnEndDrag(bool abort);
			private void EndDrag(bool abort)
			{
				this.ReleaseHandle();
				Application.RemoveMessageFilter(this);
				this.DragControl.FindForm().Capture = false;
				this.OnEndDrag(abort);
			}
			bool IMessageFilter.PreFilterMessage(ref Message m)
			{
				if (m.Msg == 512)
				{
					this.OnDragging();
				}
				else
				{
					if (m.Msg == 514)
					{
						this.EndDrag(false);
					}
					else
					{
						if (m.Msg == 533)
						{
							this.EndDrag(true);
						}
						else
						{
							if (m.Msg == 256 && (int)m.WParam == 27)
							{
								this.EndDrag(true);
							}
						}
					}
				}
				return this.OnPreFilterMessage(ref m);
			}
			protected virtual bool OnPreFilterMessage(ref Message m)
			{
				return false;
			}
			protected sealed override void WndProc(ref Message m)
			{
				if (m.Msg == 31 || m.Msg == 533)
				{
					this.EndDrag(true);
				}
				base.WndProc(ref m);
			}
		}
		private abstract class DragHandler : DockPanel.DragHandlerBase
		{
			private DockPanel m_dockPanel;
			private IDragSource m_dragSource;
			public DockPanel DockPanel
			{
				get
				{
					return this.m_dockPanel;
				}
			}
			protected IDragSource DragSource
			{
				get
				{
					return this.m_dragSource;
				}
				set
				{
					this.m_dragSource = value;
				}
			}
			protected sealed override Control DragControl
			{
				get
				{
					return (this.DragSource == null) ? null : this.DragSource.DragControl;
				}
			}
			protected DragHandler(DockPanel dockPanel)
			{
				this.m_dockPanel = dockPanel;
			}
			protected sealed override bool OnPreFilterMessage(ref Message m)
			{
				if ((m.Msg == 256 || m.Msg == 257) && ((int)m.WParam == 17 || (int)m.WParam == 16))
				{
					this.OnDragging();
				}
				return base.OnPreFilterMessage(ref m);
			}
		}
		private sealed class DockDragHandler : DockPanel.DragHandler
		{
			private class DockIndicator : DragForm
			{
				private interface IHitTest
				{
					DockStyle Status
					{
						get;
						set;
					}
					DockStyle HitTest(Point pt);
				}
				private class PanelIndicator : PictureBox, DockPanel.DockDragHandler.DockIndicator.IHitTest
				{
					private static Image _imagePanelLeft = Resources.DockIndicator_PanelLeft;
					private static Image _imagePanelRight = Resources.DockIndicator_PanelRight;
					private static Image _imagePanelTop = Resources.DockIndicator_PanelTop;
					private static Image _imagePanelBottom = Resources.DockIndicator_PanelBottom;
					private static Image _imagePanelFill = Resources.DockIndicator_PanelFill;
					private static Image _imagePanelLeftActive = Resources.DockIndicator_PanelLeft_Active;
					private static Image _imagePanelRightActive = Resources.DockIndicator_PanelRight_Active;
					private static Image _imagePanelTopActive = Resources.DockIndicator_PanelTop_Active;
					private static Image _imagePanelBottomActive = Resources.DockIndicator_PanelBottom_Active;
					private static Image _imagePanelFillActive = Resources.DockIndicator_PanelFill_Active;
					private DockStyle m_dockStyle;
					private DockStyle m_status;
					private bool m_isActivated = false;
					private DockStyle DockStyle
					{
						get
						{
							return this.m_dockStyle;
						}
					}
					public DockStyle Status
					{
						get
						{
							return this.m_status;
						}
						set
						{
							if (value != this.DockStyle && value != DockStyle.None)
							{
								throw new InvalidEnumArgumentException();
							}
							if (this.m_status != value)
							{
								this.m_status = value;
								this.IsActivated = (this.m_status != DockStyle.None);
							}
						}
					}
					private Image ImageInactive
					{
						get
						{
							Image result;
							if (this.DockStyle == DockStyle.Left)
							{
								result = DockPanel.DockDragHandler.DockIndicator.PanelIndicator._imagePanelLeft;
							}
							else
							{
								if (this.DockStyle == DockStyle.Right)
								{
									result = DockPanel.DockDragHandler.DockIndicator.PanelIndicator._imagePanelRight;
								}
								else
								{
									if (this.DockStyle == DockStyle.Top)
									{
										result = DockPanel.DockDragHandler.DockIndicator.PanelIndicator._imagePanelTop;
									}
									else
									{
										if (this.DockStyle == DockStyle.Bottom)
										{
											result = DockPanel.DockDragHandler.DockIndicator.PanelIndicator._imagePanelBottom;
										}
										else
										{
											if (this.DockStyle == DockStyle.Fill)
											{
												result = DockPanel.DockDragHandler.DockIndicator.PanelIndicator._imagePanelFill;
											}
											else
											{
												result = null;
											}
										}
									}
								}
							}
							return result;
						}
					}
					private Image ImageActive
					{
						get
						{
							Image result;
							if (this.DockStyle == DockStyle.Left)
							{
								result = DockPanel.DockDragHandler.DockIndicator.PanelIndicator._imagePanelLeftActive;
							}
							else
							{
								if (this.DockStyle == DockStyle.Right)
								{
									result = DockPanel.DockDragHandler.DockIndicator.PanelIndicator._imagePanelRightActive;
								}
								else
								{
									if (this.DockStyle == DockStyle.Top)
									{
										result = DockPanel.DockDragHandler.DockIndicator.PanelIndicator._imagePanelTopActive;
									}
									else
									{
										if (this.DockStyle == DockStyle.Bottom)
										{
											result = DockPanel.DockDragHandler.DockIndicator.PanelIndicator._imagePanelBottomActive;
										}
										else
										{
											if (this.DockStyle == DockStyle.Fill)
											{
												result = DockPanel.DockDragHandler.DockIndicator.PanelIndicator._imagePanelFillActive;
											}
											else
											{
												result = null;
											}
										}
									}
								}
							}
							return result;
						}
					}
					private bool IsActivated
					{
						get
						{
							return this.m_isActivated;
						}
						set
						{
							this.m_isActivated = value;
							base.Image = (this.IsActivated ? this.ImageActive : this.ImageInactive);
						}
					}
					public PanelIndicator(DockStyle dockStyle)
					{
						this.m_dockStyle = dockStyle;
						base.SizeMode = PictureBoxSizeMode.AutoSize;
						base.Image = this.ImageInactive;
					}
					public DockStyle HitTest(Point pt)
					{
						return (base.Visible && base.ClientRectangle.Contains(base.PointToClient(pt))) ? this.DockStyle : DockStyle.None;
					}
				}
				private class PaneIndicator : PictureBox, DockPanel.DockDragHandler.DockIndicator.IHitTest
				{
					private struct HotSpotIndex
					{
						private int m_x;
						private int m_y;
						private DockStyle m_dockStyle;
						public int X
						{
							get
							{
								return this.m_x;
							}
						}
						public int Y
						{
							get
							{
								return this.m_y;
							}
						}
						public DockStyle DockStyle
						{
							get
							{
								return this.m_dockStyle;
							}
						}
						public HotSpotIndex(int x, int y, DockStyle dockStyle)
						{
							this.m_x = x;
							this.m_y = y;
							this.m_dockStyle = dockStyle;
						}
					}
					private static Bitmap _bitmapPaneDiamond = Resources.DockIndicator_PaneDiamond;
					private static Bitmap _bitmapPaneDiamondLeft = Resources.DockIndicator_PaneDiamond_Left;
					private static Bitmap _bitmapPaneDiamondRight = Resources.DockIndicator_PaneDiamond_Right;
					private static Bitmap _bitmapPaneDiamondTop = Resources.DockIndicator_PaneDiamond_Top;
					private static Bitmap _bitmapPaneDiamondBottom = Resources.DockIndicator_PaneDiamond_Bottom;
					private static Bitmap _bitmapPaneDiamondFill = Resources.DockIndicator_PaneDiamond_Fill;
					private static Bitmap _bitmapPaneDiamondHotSpot = Resources.DockIndicator_PaneDiamond_HotSpot;
					private static Bitmap _bitmapPaneDiamondHotSpotIndex = Resources.DockIndicator_PaneDiamond_HotSpotIndex;
					private static DockPanel.DockDragHandler.DockIndicator.PaneIndicator.HotSpotIndex[] _hotSpots = new DockPanel.DockDragHandler.DockIndicator.PaneIndicator.HotSpotIndex[]
					{
						new DockPanel.DockDragHandler.DockIndicator.PaneIndicator.HotSpotIndex(1, 0, DockStyle.Top),
						new DockPanel.DockDragHandler.DockIndicator.PaneIndicator.HotSpotIndex(0, 1, DockStyle.Left),
						new DockPanel.DockDragHandler.DockIndicator.PaneIndicator.HotSpotIndex(1, 1, DockStyle.Fill),
						new DockPanel.DockDragHandler.DockIndicator.PaneIndicator.HotSpotIndex(2, 1, DockStyle.Right),
						new DockPanel.DockDragHandler.DockIndicator.PaneIndicator.HotSpotIndex(1, 2, DockStyle.Bottom)
					};
					private static GraphicsPath _displayingGraphicsPath = DrawHelper.CalculateGraphicsPathFromBitmap(DockPanel.DockDragHandler.DockIndicator.PaneIndicator._bitmapPaneDiamond);
					private DockStyle m_status = DockStyle.None;
					public static GraphicsPath DisplayingGraphicsPath
					{
						get
						{
							return DockPanel.DockDragHandler.DockIndicator.PaneIndicator._displayingGraphicsPath;
						}
					}
					public DockStyle Status
					{
						get
						{
							return this.m_status;
						}
						set
						{
							this.m_status = value;
							if (this.m_status == DockStyle.None)
							{
								base.Image = DockPanel.DockDragHandler.DockIndicator.PaneIndicator._bitmapPaneDiamond;
							}
							else
							{
								if (this.m_status == DockStyle.Left)
								{
									base.Image = DockPanel.DockDragHandler.DockIndicator.PaneIndicator._bitmapPaneDiamondLeft;
								}
								else
								{
									if (this.m_status == DockStyle.Right)
									{
										base.Image = DockPanel.DockDragHandler.DockIndicator.PaneIndicator._bitmapPaneDiamondRight;
									}
									else
									{
										if (this.m_status == DockStyle.Top)
										{
											base.Image = DockPanel.DockDragHandler.DockIndicator.PaneIndicator._bitmapPaneDiamondTop;
										}
										else
										{
											if (this.m_status == DockStyle.Bottom)
											{
												base.Image = DockPanel.DockDragHandler.DockIndicator.PaneIndicator._bitmapPaneDiamondBottom;
											}
											else
											{
												if (this.m_status == DockStyle.Fill)
												{
													base.Image = DockPanel.DockDragHandler.DockIndicator.PaneIndicator._bitmapPaneDiamondFill;
												}
											}
										}
									}
								}
							}
						}
					}
					public PaneIndicator()
					{
						base.SizeMode = PictureBoxSizeMode.AutoSize;
						base.Image = DockPanel.DockDragHandler.DockIndicator.PaneIndicator._bitmapPaneDiamond;
						base.Region = new Region(DockPanel.DockDragHandler.DockIndicator.PaneIndicator.DisplayingGraphicsPath);
					}
					public DockStyle HitTest(Point pt)
					{
						checked
						{
							DockStyle result;
							if (!base.Visible)
							{
								result = DockStyle.None;
							}
							else
							{
								pt = base.PointToClient(pt);
								if (!base.ClientRectangle.Contains(pt))
								{
									result = DockStyle.None;
								}
								else
								{
									for (int i = DockPanel.DockDragHandler.DockIndicator.PaneIndicator._hotSpots.GetLowerBound(0); i <= DockPanel.DockDragHandler.DockIndicator.PaneIndicator._hotSpots.GetUpperBound(0); i++)
									{
										if (DockPanel.DockDragHandler.DockIndicator.PaneIndicator._bitmapPaneDiamondHotSpot.GetPixel(pt.X, pt.Y) == DockPanel.DockDragHandler.DockIndicator.PaneIndicator._bitmapPaneDiamondHotSpotIndex.GetPixel(DockPanel.DockDragHandler.DockIndicator.PaneIndicator._hotSpots[i].X, DockPanel.DockDragHandler.DockIndicator.PaneIndicator._hotSpots[i].Y))
										{
											result = DockPanel.DockDragHandler.DockIndicator.PaneIndicator._hotSpots[i].DockStyle;
											return result;
										}
									}
									result = DockStyle.None;
								}
							}
							return result;
						}
					}
				}
				private int _PanelIndicatorMargin = 10;
				private DockPanel.DockDragHandler m_dragHandler;
				private DockPanel.DockDragHandler.DockIndicator.PaneIndicator m_paneDiamond = null;
				private DockPanel.DockDragHandler.DockIndicator.PanelIndicator m_panelLeft = null;
				private DockPanel.DockDragHandler.DockIndicator.PanelIndicator m_panelRight = null;
				private DockPanel.DockDragHandler.DockIndicator.PanelIndicator m_panelTop = null;
				private DockPanel.DockDragHandler.DockIndicator.PanelIndicator m_panelBottom = null;
				private DockPanel.DockDragHandler.DockIndicator.PanelIndicator m_panelFill = null;
				private bool m_fullPanelEdge = false;
				private DockPane m_dockPane = null;
				private DockPanel.DockDragHandler.DockIndicator.IHitTest m_hitTest = null;
				private DockPanel.DockDragHandler.DockIndicator.PaneIndicator PaneDiamond
				{
					get
					{
						if (this.m_paneDiamond == null)
						{
							this.m_paneDiamond = new DockPanel.DockDragHandler.DockIndicator.PaneIndicator();
						}
						return this.m_paneDiamond;
					}
				}
				private DockPanel.DockDragHandler.DockIndicator.PanelIndicator PanelLeft
				{
					get
					{
						if (this.m_panelLeft == null)
						{
							this.m_panelLeft = new DockPanel.DockDragHandler.DockIndicator.PanelIndicator(DockStyle.Left);
						}
						return this.m_panelLeft;
					}
				}
				private DockPanel.DockDragHandler.DockIndicator.PanelIndicator PanelRight
				{
					get
					{
						if (this.m_panelRight == null)
						{
							this.m_panelRight = new DockPanel.DockDragHandler.DockIndicator.PanelIndicator(DockStyle.Right);
						}
						return this.m_panelRight;
					}
				}
				private DockPanel.DockDragHandler.DockIndicator.PanelIndicator PanelTop
				{
					get
					{
						if (this.m_panelTop == null)
						{
							this.m_panelTop = new DockPanel.DockDragHandler.DockIndicator.PanelIndicator(DockStyle.Top);
						}
						return this.m_panelTop;
					}
				}
				private DockPanel.DockDragHandler.DockIndicator.PanelIndicator PanelBottom
				{
					get
					{
						if (this.m_panelBottom == null)
						{
							this.m_panelBottom = new DockPanel.DockDragHandler.DockIndicator.PanelIndicator(DockStyle.Bottom);
						}
						return this.m_panelBottom;
					}
				}
				private DockPanel.DockDragHandler.DockIndicator.PanelIndicator PanelFill
				{
					get
					{
						if (this.m_panelFill == null)
						{
							this.m_panelFill = new DockPanel.DockDragHandler.DockIndicator.PanelIndicator(DockStyle.Fill);
						}
						return this.m_panelFill;
					}
				}
				public bool FullPanelEdge
				{
					get
					{
						return this.m_fullPanelEdge;
					}
					set
					{
						if (this.m_fullPanelEdge != value)
						{
							this.m_fullPanelEdge = value;
							this.RefreshChanges();
						}
					}
				}
				public DockPanel.DockDragHandler DragHandler
				{
					get
					{
						return this.m_dragHandler;
					}
				}
				public DockPanel DockPanel
				{
					get
					{
						return this.DragHandler.DockPanel;
					}
				}
				public DockPane DockPane
				{
					get
					{
						return this.m_dockPane;
					}
					internal set
					{
						if (this.m_dockPane != value)
						{
							DockPane displayingPane = this.DisplayingPane;
							this.m_dockPane = value;
							if (displayingPane != this.DisplayingPane)
							{
								this.RefreshChanges();
							}
						}
					}
				}
				private DockPanel.DockDragHandler.DockIndicator.IHitTest HitTestResult
				{
					get
					{
						return this.m_hitTest;
					}
					set
					{
						if (this.m_hitTest != value)
						{
							if (this.m_hitTest != null)
							{
								this.m_hitTest.Status = DockStyle.None;
							}
							this.m_hitTest = value;
						}
					}
				}
				private DockPane DisplayingPane
				{
					get
					{
						return this.ShouldPaneDiamondVisible() ? this.DockPane : null;
					}
				}
				public DockIndicator(DockPanel.DockDragHandler dragHandler)
				{
					this.m_dragHandler = dragHandler;
					base.Controls.AddRange(new Control[]
					{
						this.PaneDiamond,
						this.PanelLeft,
						this.PanelRight,
						this.PanelTop,
						this.PanelBottom,
						this.PanelFill
					});
					base.Region = new Region(Rectangle.Empty);
				}
				private void RefreshChanges()
				{
					Region region = new Region(Rectangle.Empty);
					Rectangle r = this.FullPanelEdge ? this.DockPanel.DockArea : this.DockPanel.DocumentWindowBounds;
					r = base.RectangleToClient(this.DockPanel.RectangleToScreen(r));
					checked
					{
						if (this.ShouldPanelIndicatorVisible(DockState.DockLeft))
						{
							this.PanelLeft.Location = new Point(r.X + this._PanelIndicatorMargin, r.Y + (r.Height - this.PanelRight.Height) / 2);
							this.PanelLeft.Visible = true;
							region.Union(this.PanelLeft.Bounds);
						}
						else
						{
							this.PanelLeft.Visible = false;
						}
						if (this.ShouldPanelIndicatorVisible(DockState.DockRight))
						{
							this.PanelRight.Location = new Point(r.X + r.Width - this.PanelRight.Width - this._PanelIndicatorMargin, r.Y + (r.Height - this.PanelRight.Height) / 2);
							this.PanelRight.Visible = true;
							region.Union(this.PanelRight.Bounds);
						}
						else
						{
							this.PanelRight.Visible = false;
						}
						if (this.ShouldPanelIndicatorVisible(DockState.DockTop))
						{
							this.PanelTop.Location = new Point(r.X + (r.Width - this.PanelTop.Width) / 2, r.Y + this._PanelIndicatorMargin);
							this.PanelTop.Visible = true;
							region.Union(this.PanelTop.Bounds);
						}
						else
						{
							this.PanelTop.Visible = false;
						}
						if (this.ShouldPanelIndicatorVisible(DockState.DockBottom))
						{
							this.PanelBottom.Location = new Point(r.X + (r.Width - this.PanelBottom.Width) / 2, r.Y + r.Height - this.PanelBottom.Height - this._PanelIndicatorMargin);
							this.PanelBottom.Visible = true;
							region.Union(this.PanelBottom.Bounds);
						}
						else
						{
							this.PanelBottom.Visible = false;
						}
						if (this.ShouldPanelIndicatorVisible(DockState.Document))
						{
							Rectangle rectangle = base.RectangleToClient(this.DockPanel.RectangleToScreen(this.DockPanel.DocumentWindowBounds));
							this.PanelFill.Location = new Point(rectangle.X + (rectangle.Width - this.PanelFill.Width) / 2, rectangle.Y + (rectangle.Height - this.PanelFill.Height) / 2);
							this.PanelFill.Visible = true;
							region.Union(this.PanelFill.Bounds);
						}
						else
						{
							this.PanelFill.Visible = false;
						}
						if (this.ShouldPaneDiamondVisible())
						{
							Rectangle rectangle2 = base.RectangleToClient(this.DockPane.RectangleToScreen(this.DockPane.ClientRectangle));
							this.PaneDiamond.Location = new Point(rectangle2.Left + (rectangle2.Width - this.PaneDiamond.Width) / 2, rectangle2.Top + (rectangle2.Height - this.PaneDiamond.Height) / 2);
							this.PaneDiamond.Visible = true;
							using (GraphicsPath graphicsPath = DockPanel.DockDragHandler.DockIndicator.PaneIndicator.DisplayingGraphicsPath.Clone() as GraphicsPath)
							{
								Point[] plgpts = new Point[]
								{
									new Point(this.PaneDiamond.Left, this.PaneDiamond.Top),
									new Point(this.PaneDiamond.Right, this.PaneDiamond.Top),
									new Point(this.PaneDiamond.Left, this.PaneDiamond.Bottom)
								};
								using (Matrix matrix = new Matrix(this.PaneDiamond.ClientRectangle, plgpts))
								{
									graphicsPath.Transform(matrix);
								}
								region.Union(graphicsPath);
							}
						}
						else
						{
							this.PaneDiamond.Visible = false;
						}
						base.Region = region;
					}
				}
				private bool ShouldPanelIndicatorVisible(DockState dockState)
				{
					return base.Visible && !this.DockPanel.DockWindows[dockState].Visible && this.DragHandler.DragSource.IsDockStateValid(dockState);
				}
				private bool ShouldPaneDiamondVisible()
				{
					return this.DockPane != null && this.DockPanel.AllowEndUserNestedDocking && this.DragHandler.DragSource.CanDockTo(this.DockPane);
				}
				public override void Show(bool bActivate)
				{
					base.Show(bActivate);
					base.Bounds = SystemInformation.VirtualScreen;
					this.RefreshChanges();
				}
				public void TestDrop()
				{
					Point mousePosition = Control.MousePosition;
					this.DockPane = DockHelper.PaneAtPoint(mousePosition, this.DockPanel);
					if (DockPanel.DockDragHandler.DockIndicator.TestDrop(this.PanelLeft, mousePosition) != DockStyle.None)
					{
						this.HitTestResult = this.PanelLeft;
					}
					else
					{
						if (DockPanel.DockDragHandler.DockIndicator.TestDrop(this.PanelRight, mousePosition) != DockStyle.None)
						{
							this.HitTestResult = this.PanelRight;
						}
						else
						{
							if (DockPanel.DockDragHandler.DockIndicator.TestDrop(this.PanelTop, mousePosition) != DockStyle.None)
							{
								this.HitTestResult = this.PanelTop;
							}
							else
							{
								if (DockPanel.DockDragHandler.DockIndicator.TestDrop(this.PanelBottom, mousePosition) != DockStyle.None)
								{
									this.HitTestResult = this.PanelBottom;
								}
								else
								{
									if (DockPanel.DockDragHandler.DockIndicator.TestDrop(this.PanelFill, mousePosition) != DockStyle.None)
									{
										this.HitTestResult = this.PanelFill;
									}
									else
									{
										if (DockPanel.DockDragHandler.DockIndicator.TestDrop(this.PaneDiamond, mousePosition) != DockStyle.None)
										{
											this.HitTestResult = this.PaneDiamond;
										}
										else
										{
											this.HitTestResult = null;
										}
									}
								}
							}
						}
					}
					if (this.HitTestResult != null)
					{
						if (this.HitTestResult is DockPanel.DockDragHandler.DockIndicator.PaneIndicator)
						{
							this.DragHandler.Outline.Show(this.DockPane, this.HitTestResult.Status);
						}
						else
						{
							this.DragHandler.Outline.Show(this.DockPanel, this.HitTestResult.Status, this.FullPanelEdge);
						}
					}
				}
				private static DockStyle TestDrop(DockPanel.DockDragHandler.DockIndicator.IHitTest hitTest, Point pt)
				{
					return hitTest.Status = hitTest.HitTest(pt);
				}
			}
			private class DockOutline : DockOutlineBase
			{
				private DragForm m_dragForm;
				private DragForm DragForm
				{
					get
					{
						return this.m_dragForm;
					}
				}
				public DockOutline()
				{
					this.m_dragForm = new DragForm();
					this.SetDragForm(Rectangle.Empty);
					this.DragForm.BackColor = SystemColors.ActiveCaption;
					this.DragForm.Opacity = 0.5;
					this.DragForm.Show(false);
				}
				protected override void OnShow()
				{
					this.CalculateRegion();
				}
				protected override void OnClose()
				{
					this.DragForm.Close();
				}
				private void CalculateRegion()
				{
					if (!base.SameAsOldValue)
					{
						if (!base.FloatWindowBounds.IsEmpty)
						{
							this.SetOutline(base.FloatWindowBounds);
						}
						else
						{
							if (base.DockTo is DockPanel)
							{
								this.SetOutline(base.DockTo as DockPanel, base.Dock, base.ContentIndex != 0);
							}
							else
							{
								if (base.DockTo is DockPane)
								{
									this.SetOutline(base.DockTo as DockPane, base.Dock, base.ContentIndex);
								}
								else
								{
									this.SetOutline();
								}
							}
						}
					}
				}
				private void SetOutline()
				{
					this.SetDragForm(Rectangle.Empty);
				}
				private void SetOutline(Rectangle floatWindowBounds)
				{
					this.SetDragForm(floatWindowBounds);
				}
				private void SetOutline(DockPanel dockPanel, DockStyle dock, bool fullPanelEdge)
				{
					Rectangle dragForm = fullPanelEdge ? dockPanel.DockArea : dockPanel.DocumentWindowBounds;
					dragForm.Location = dockPanel.PointToScreen(dragForm.Location);
					checked
					{
						if (dock == DockStyle.Top)
						{
							int dockWindowSize = dockPanel.GetDockWindowSize(DockState.DockTop);
							dragForm = new Rectangle(dragForm.X, dragForm.Y, dragForm.Width, dockWindowSize);
						}
						else
						{
							if (dock == DockStyle.Bottom)
							{
								int dockWindowSize = dockPanel.GetDockWindowSize(DockState.DockBottom);
								dragForm = new Rectangle(dragForm.X, dragForm.Bottom - dockWindowSize, dragForm.Width, dockWindowSize);
							}
							else
							{
								if (dock == DockStyle.Left)
								{
									int dockWindowSize2 = dockPanel.GetDockWindowSize(DockState.DockLeft);
									dragForm = new Rectangle(dragForm.X, dragForm.Y, dockWindowSize2, dragForm.Height);
								}
								else
								{
									if (dock == DockStyle.Right)
									{
										int dockWindowSize2 = dockPanel.GetDockWindowSize(DockState.DockRight);
										dragForm = new Rectangle(dragForm.Right - dockWindowSize2, dragForm.Y, dockWindowSize2, dragForm.Height);
									}
									else
									{
										if (dock == DockStyle.Fill)
										{
											dragForm = dockPanel.DocumentWindowBounds;
											dragForm.Location = dockPanel.PointToScreen(dragForm.Location);
										}
									}
								}
							}
						}
						this.SetDragForm(dragForm);
					}
				}
				private void SetOutline(DockPane pane, DockStyle dock, int contentIndex)
				{
					checked
					{
						if (dock != DockStyle.Fill)
						{
							Rectangle displayingRectangle = pane.DisplayingRectangle;
							if (dock == DockStyle.Right)
							{
								displayingRectangle.X += displayingRectangle.Width / 2;
							}
							if (dock == DockStyle.Bottom)
							{
								displayingRectangle.Y += displayingRectangle.Height / 2;
							}
							if (dock == DockStyle.Left || dock == DockStyle.Right)
							{
								displayingRectangle.Width -= displayingRectangle.Width / 2;
							}
							if (dock == DockStyle.Top || dock == DockStyle.Bottom)
							{
								displayingRectangle.Height -= displayingRectangle.Height / 2;
							}
							displayingRectangle.Location = pane.PointToScreen(displayingRectangle.Location);
							this.SetDragForm(displayingRectangle);
						}
						else
						{
							if (contentIndex == -1)
							{
								Rectangle displayingRectangle = pane.DisplayingRectangle;
								displayingRectangle.Location = pane.PointToScreen(displayingRectangle.Location);
								this.SetDragForm(displayingRectangle);
							}
							else
							{
								using (GraphicsPath outline = pane.TabStripControl.GetOutline(contentIndex))
								{
									RectangleF bounds = outline.GetBounds();
									Rectangle displayingRectangle = new Rectangle((int)bounds.X, (int)bounds.Y, (int)bounds.Width, (int)bounds.Height);
									using (Matrix matrix = new Matrix(displayingRectangle, new Point[]
									{
										new Point(0, 0),
										new Point(displayingRectangle.Width, 0),
										new Point(0, displayingRectangle.Height)
									}))
									{
										outline.Transform(matrix);
									}
									Region region = new Region(outline);
									this.SetDragForm(displayingRectangle, region);
								}
							}
						}
					}
				}
				private void SetDragForm(Rectangle rect)
				{
					this.DragForm.Bounds = rect;
					if (rect == Rectangle.Empty)
					{
						this.DragForm.Region = new Region(Rectangle.Empty);
					}
					else
					{
						if (this.DragForm.Region != null)
						{
							this.DragForm.Region = null;
						}
					}
				}
				private void SetDragForm(Rectangle rect, Region region)
				{
					this.DragForm.Bounds = rect;
					this.DragForm.Region = region;
				}
			}
			private DockOutlineBase m_outline;
			private DockPanel.DockDragHandler.DockIndicator m_indicator;
			private Rectangle m_floatOutlineBounds;
			public new IDockDragSource DragSource
			{
				get
				{
					return base.DragSource as IDockDragSource;
				}
				set
				{
					base.DragSource = value;
				}
			}
			public DockOutlineBase Outline
			{
				get
				{
					return this.m_outline;
				}
				private set
				{
					this.m_outline = value;
				}
			}
			private DockPanel.DockDragHandler.DockIndicator Indicator
			{
				get
				{
					return this.m_indicator;
				}
				set
				{
					this.m_indicator = value;
				}
			}
			private Rectangle FloatOutlineBounds
			{
				get
				{
					return this.m_floatOutlineBounds;
				}
				set
				{
					this.m_floatOutlineBounds = value;
				}
			}
			public DockDragHandler(DockPanel panel) : base(panel)
			{
			}
			public void BeginDrag(IDockDragSource dragSource)
			{
				this.DragSource = dragSource;
				if (!base.BeginDrag())
				{
					this.DragSource = null;
				}
				else
				{
					this.Outline = new DockPanel.DockDragHandler.DockOutline();
					this.Indicator = new DockPanel.DockDragHandler.DockIndicator(this);
					this.Indicator.Show(false);
					this.FloatOutlineBounds = this.DragSource.BeginDrag(base.StartMousePosition);
				}
			}
			protected override void OnDragging()
			{
				this.TestDrop();
			}
			protected override void OnEndDrag(bool abort)
			{
				base.DockPanel.SuspendLayout(true);
				this.Outline.Close();
				this.Indicator.Close();
				this.EndDrag(abort);
				base.DockPanel.PerformMdiClientLayout();
				base.DockPanel.ResumeLayout(true, true);
				this.DragSource = null;
			}
			private void TestDrop()
			{
				this.Outline.FlagTestDrop = false;
				this.Indicator.FullPanelEdge = ((Control.ModifierKeys & Keys.Shift) != Keys.None);
				if ((Control.ModifierKeys & Keys.Control) == Keys.None)
				{
					this.Indicator.TestDrop();
					if (!this.Outline.FlagTestDrop)
					{
						DockPane dockPane = DockHelper.PaneAtPoint(Control.MousePosition, base.DockPanel);
						if (dockPane != null && this.DragSource.IsDockStateValid(dockPane.DockState))
						{
							dockPane.TestDrop(this.DragSource, this.Outline);
						}
					}
					if (!this.Outline.FlagTestDrop && this.DragSource.IsDockStateValid(DockState.Float))
					{
						FloatWindow floatWindow = DockHelper.FloatWindowAtPoint(Control.MousePosition, base.DockPanel);
						if (floatWindow != null)
						{
							floatWindow.TestDrop(this.DragSource, this.Outline);
						}
					}
				}
				else
				{
					this.Indicator.DockPane = DockHelper.PaneAtPoint(Control.MousePosition, base.DockPanel);
				}
				checked
				{
					if (!this.Outline.FlagTestDrop)
					{
						if (this.DragSource.IsDockStateValid(DockState.Float))
						{
							Rectangle floatOutlineBounds = this.FloatOutlineBounds;
							floatOutlineBounds.Offset(Control.MousePosition.X - base.StartMousePosition.X, Control.MousePosition.Y - base.StartMousePosition.Y);
							this.Outline.Show(floatOutlineBounds);
						}
					}
					if (!this.Outline.FlagTestDrop)
					{
						Cursor.Current = Cursors.No;
						this.Outline.Show();
					}
					else
					{
						Cursor.Current = this.DragControl.Cursor;
					}
				}
			}
			private void EndDrag(bool abort)
			{
				if (!abort)
				{
					if (!this.Outline.FloatWindowBounds.IsEmpty)
					{
						this.DragSource.FloatAt(this.Outline.FloatWindowBounds);
					}
					else
					{
						if (this.Outline.DockTo is DockPane)
						{
							DockPane pane = this.Outline.DockTo as DockPane;
							this.DragSource.DockTo(pane, this.Outline.Dock, this.Outline.ContentIndex);
						}
						else
						{
							if (this.Outline.DockTo is DockPanel)
							{
								DockPanel dockPanel = this.Outline.DockTo as DockPanel;
								dockPanel.UpdateDockWindowZOrder(this.Outline.Dock, this.Outline.FlagFullEdge);
								this.DragSource.DockTo(dockPanel, this.Outline.Dock);
							}
						}
					}
				}
			}
		}
		private interface IFocusManager
		{
			bool IsFocusTrackingSuspended
			{
				get;
			}
			IDockContent ActiveContent
			{
				get;
			}
			DockPane ActivePane
			{
				get;
			}
			IDockContent ActiveDocument
			{
				get;
			}
			DockPane ActiveDocumentPane
			{
				get;
			}
			void SuspendFocusTracking();
			void ResumeFocusTracking();
		}
		private class FocusManagerImpl : Component, IContentFocusManager, DockPanel.IFocusManager
		{
			private class HookEventArgs : EventArgs
			{
				public int HookCode;
				public IntPtr wParam;
				public IntPtr lParam;
			}
			private class LocalWindowsHook : IDisposable
			{
				public delegate void HookEventHandler(object sender, DockPanel.FocusManagerImpl.HookEventArgs e);
				private IntPtr m_hHook = IntPtr.Zero;
				private NativeMethods.HookProc m_filterFunc = null;
				private HookType m_hookType;
				public event DockPanel.FocusManagerImpl.LocalWindowsHook.HookEventHandler HookInvoked;
				protected void OnHookInvoked(DockPanel.FocusManagerImpl.HookEventArgs e)
				{
					if (this.HookInvoked != null)
					{
						this.HookInvoked(this, e);
					}
				}
				public LocalWindowsHook(HookType hook)
				{
					this.m_hookType = hook;
					this.m_filterFunc = new NativeMethods.HookProc(this.CoreHookProc);
				}
				public IntPtr CoreHookProc(int code, IntPtr wParam, IntPtr lParam)
				{
					IntPtr result;
					if (code < 0)
					{
						result = NativeMethods.CallNextHookEx(this.m_hHook, code, wParam, lParam);
					}
					else
					{
						this.OnHookInvoked(new DockPanel.FocusManagerImpl.HookEventArgs
						{
							HookCode = code,
							wParam = wParam,
							lParam = lParam
						});
						result = NativeMethods.CallNextHookEx(this.m_hHook, code, wParam, lParam);
					}
					return result;
				}
				public void Install()
				{
					if (this.m_hHook != IntPtr.Zero)
					{
						this.Uninstall();
					}
					int currentThreadId = NativeMethods.GetCurrentThreadId();
					this.m_hHook = NativeMethods.SetWindowsHookEx(this.m_hookType, this.m_filterFunc, IntPtr.Zero, currentThreadId);
				}
				public void Uninstall()
				{
					if (this.m_hHook != IntPtr.Zero)
					{
						NativeMethods.UnhookWindowsHookEx(this.m_hHook);
						this.m_hHook = IntPtr.Zero;
					}
				}
				~LocalWindowsHook()
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
					this.Uninstall();
				}
			}
			private DockPanel.FocusManagerImpl.LocalWindowsHook m_localWindowsHook;
			private DockPanel.FocusManagerImpl.LocalWindowsHook.HookEventHandler m_hookEventHandler;
			private DockPanel m_dockPanel;
			private bool m_disposed = false;
			private IDockContent m_contentActivating = null;
			private List<IDockContent> m_listContent = new List<IDockContent>();
			private IDockContent m_lastActiveContent = null;
			private int m_countSuspendFocusTracking = 0;
			private bool m_inRefreshActiveWindow = false;
			private DockPane m_activePane = null;
			private IDockContent m_activeContent = null;
			private DockPane m_activeDocumentPane = null;
			private IDockContent m_activeDocument = null;
			public DockPanel DockPanel
			{
				get
				{
					return this.m_dockPanel;
				}
			}
			private IDockContent ContentActivating
			{
				get
				{
					return this.m_contentActivating;
				}
				set
				{
					this.m_contentActivating = value;
				}
			}
			private List<IDockContent> ListContent
			{
				get
				{
					return this.m_listContent;
				}
			}
			private IDockContent LastActiveContent
			{
				get
				{
					return this.m_lastActiveContent;
				}
				set
				{
					this.m_lastActiveContent = value;
				}
			}
			public bool IsFocusTrackingSuspended
			{
				get
				{
					return this.m_countSuspendFocusTracking != 0;
				}
			}
			private bool InRefreshActiveWindow
			{
				get
				{
					return this.m_inRefreshActiveWindow;
				}
			}
			public DockPane ActivePane
			{
				get
				{
					return this.m_activePane;
				}
			}
			public IDockContent ActiveContent
			{
				get
				{
					return this.m_activeContent;
				}
			}
			public DockPane ActiveDocumentPane
			{
				get
				{
					return this.m_activeDocumentPane;
				}
			}
			public IDockContent ActiveDocument
			{
				get
				{
					return this.m_activeDocument;
				}
			}
			public FocusManagerImpl(DockPanel dockPanel)
			{
				this.m_dockPanel = dockPanel;
				this.m_localWindowsHook = new DockPanel.FocusManagerImpl.LocalWindowsHook(HookType.WH_CALLWNDPROCRET);
				this.m_hookEventHandler = new DockPanel.FocusManagerImpl.LocalWindowsHook.HookEventHandler(this.HookEventHandler);
				this.m_localWindowsHook.HookInvoked += this.m_hookEventHandler;
				this.m_localWindowsHook.Install();
			}
			protected override void Dispose(bool disposing)
			{
				bool flag = false;
				try
				{
					Monitor.Enter(this, ref flag);
					if (!this.m_disposed && disposing)
					{
						this.m_localWindowsHook.Dispose();
						this.m_disposed = true;
					}
					base.Dispose(disposing);
				}
				finally
				{
					if (flag)
					{
						Monitor.Exit(this);
					}
				}
			}
			public void Activate(IDockContent content)
			{
				if (this.IsFocusTrackingSuspended)
				{
					this.ContentActivating = content;
				}
				else
				{
					if (content != null)
					{
						DockContentHandler dockHandler = content.DockHandler;
						if (!dockHandler.Form.IsDisposed)
						{
							if (DockPanel.FocusManagerImpl.ContentContains(content, dockHandler.ActiveWindowHandle))
							{
								NativeMethods.SetFocus(dockHandler.ActiveWindowHandle);
							}
							if (!dockHandler.Form.ContainsFocus)
							{
								if (!dockHandler.Form.SelectNextControl(dockHandler.Form.ActiveControl, true, true, true, true))
								{
									NativeMethods.SetFocus(dockHandler.Form.Handle);
								}
							}
						}
					}
				}
			}
			public void AddToList(IDockContent content)
			{
				if (!this.ListContent.Contains(content) && !this.IsInActiveList(content))
				{
					this.ListContent.Add(content);
				}
			}
			public void RemoveFromList(IDockContent content)
			{
				if (this.IsInActiveList(content))
				{
					this.RemoveFromActiveList(content);
				}
				if (this.ListContent.Contains(content))
				{
					this.ListContent.Remove(content);
				}
			}
			private bool IsInActiveList(IDockContent content)
			{
				return content.DockHandler.NextActive != null || this.LastActiveContent == content;
			}
			private void AddLastToActiveList(IDockContent content)
			{
				IDockContent lastActiveContent = this.LastActiveContent;
				if (lastActiveContent != content)
				{
					DockContentHandler dockHandler = content.DockHandler;
					if (this.IsInActiveList(content))
					{
						this.RemoveFromActiveList(content);
					}
					dockHandler.PreviousActive = lastActiveContent;
					dockHandler.NextActive = null;
					this.LastActiveContent = content;
					if (lastActiveContent != null)
					{
						lastActiveContent.DockHandler.NextActive = this.LastActiveContent;
					}
				}
			}
			private void RemoveFromActiveList(IDockContent content)
			{
				if (this.LastActiveContent == content)
				{
					this.LastActiveContent = content.DockHandler.PreviousActive;
				}
				IDockContent previousActive = content.DockHandler.PreviousActive;
				IDockContent nextActive = content.DockHandler.NextActive;
				if (previousActive != null)
				{
					previousActive.DockHandler.NextActive = nextActive;
				}
				if (nextActive != null)
				{
					nextActive.DockHandler.PreviousActive = previousActive;
				}
				content.DockHandler.PreviousActive = null;
				content.DockHandler.NextActive = null;
			}
			public void GiveUpFocus(IDockContent content)
			{
				DockContentHandler dockHandler = content.DockHandler;
				checked
				{
					if (dockHandler.Form.ContainsFocus)
					{
						if (this.IsFocusTrackingSuspended)
						{
							this.DockPanel.DummyControl.Focus();
						}
						if (this.LastActiveContent == content)
						{
							IDockContent previousActive = dockHandler.PreviousActive;
							if (previousActive != null)
							{
								this.Activate(previousActive);
							}
							else
							{
								if (this.ListContent.Count > 0)
								{
									this.Activate(this.ListContent[this.ListContent.Count - 1]);
								}
							}
						}
						else
						{
							if (this.LastActiveContent != null)
							{
								this.Activate(this.LastActiveContent);
							}
							else
							{
								if (this.ListContent.Count > 0)
								{
									this.Activate(this.ListContent[this.ListContent.Count - 1]);
								}
							}
						}
					}
				}
			}
			private static bool ContentContains(IDockContent content, IntPtr hWnd)
			{
				Control control = Control.FromChildHandle(hWnd);
				bool result;
				for (Control control2 = control; control2 != null; control2 = control2.Parent)
				{
					if (control2 == content.DockHandler.Form)
					{
						result = true;
						return result;
					}
				}
				result = false;
				return result;
			}
			public void SuspendFocusTracking()
			{
				checked
				{
					this.m_countSuspendFocusTracking++;
					this.m_localWindowsHook.HookInvoked -= this.m_hookEventHandler;
				}
			}
			public void ResumeFocusTracking()
			{
				checked
				{
					if (this.m_countSuspendFocusTracking > 0)
					{
						this.m_countSuspendFocusTracking--;
					}
					if (this.m_countSuspendFocusTracking == 0)
					{
						if (this.ContentActivating != null)
						{
							this.Activate(this.ContentActivating);
							this.ContentActivating = null;
						}
						this.m_localWindowsHook.HookInvoked += this.m_hookEventHandler;
						if (!this.InRefreshActiveWindow)
						{
							this.RefreshActiveWindow();
						}
					}
				}
			}
			private void HookEventHandler(object sender, DockPanel.FocusManagerImpl.HookEventArgs e)
			{
				checked
				{
					Msgs msgs = (Msgs)Marshal.ReadInt32(e.lParam, IntPtr.Size * 3);
					if (msgs == Msgs.WM_KILLFOCUS)
					{
						IntPtr hWnd = Marshal.ReadIntPtr(e.lParam, IntPtr.Size * 2);
						DockPane paneFromHandle = this.GetPaneFromHandle(hWnd);
						if (paneFromHandle == null)
						{
							this.RefreshActiveWindow();
						}
					}
					else
					{
						if (msgs == Msgs.WM_SETFOCUS)
						{
							this.RefreshActiveWindow();
						}
						else
						{
							if (msgs == Msgs.WM_MDIACTIVATE)
							{
								this.RefreshActiveWindow();
							}
						}
					}
				}
			}
			private DockPane GetPaneFromHandle(IntPtr hWnd)
			{
				Control control = Control.FromChildHandle(hWnd);
				DockPane dockPane = null;
				DockPane result;
				while (control != null)
				{
					IDockContent dockContent = control as IDockContent;
					if (dockContent != null)
					{
						dockContent.DockHandler.ActiveWindowHandle = hWnd;
					}
					if (dockContent != null && dockContent.DockHandler.DockPanel == this.DockPanel)
					{
						result = dockContent.DockHandler.Pane;
						return result;
					}
					dockPane = (control as DockPane);
					if (dockPane != null && dockPane.DockPanel == this.DockPanel)
					{
						break;
					}
					control = control.Parent;
				}
				result = dockPane;
				return result;
			}
			private void RefreshActiveWindow()
			{
				this.SuspendFocusTracking();
				this.m_inRefreshActiveWindow = true;
				DockPane activePane = this.ActivePane;
				IDockContent activeContent = this.ActiveContent;
				IDockContent activeDocument = this.ActiveDocument;
				this.SetActivePane();
				this.SetActiveContent();
				this.SetActiveDocumentPane();
				this.SetActiveDocument();
				this.DockPanel.AutoHideWindow.RefreshActivePane();
				this.ResumeFocusTracking();
				this.m_inRefreshActiveWindow = false;
				if (activeContent != this.ActiveContent)
				{
					this.DockPanel.OnActiveContentChanged(EventArgs.Empty);
				}
				if (activeDocument != this.ActiveDocument)
				{
					this.DockPanel.OnActiveDocumentChanged(EventArgs.Empty);
				}
				if (activePane != this.ActivePane)
				{
					this.DockPanel.OnActivePaneChanged(EventArgs.Empty);
				}
			}
			private void SetActivePane()
			{
				DockPane paneFromHandle = this.GetPaneFromHandle(NativeMethods.GetFocus());
				if (this.m_activePane != paneFromHandle)
				{
					if (this.m_activePane != null)
					{
						this.m_activePane.SetIsActivated(false);
					}
					this.m_activePane = paneFromHandle;
					if (this.m_activePane != null)
					{
						this.m_activePane.SetIsActivated(true);
					}
				}
			}
			internal void SetActiveContent()
			{
				IDockContent dockContent = (this.ActivePane == null) ? null : this.ActivePane.ActiveContent;
				if (this.m_activeContent != dockContent)
				{
					if (this.m_activeContent != null)
					{
						this.m_activeContent.DockHandler.IsActivated = false;
					}
					this.m_activeContent = dockContent;
					if (this.m_activeContent != null)
					{
						this.m_activeContent.DockHandler.IsActivated = true;
						if (!DockHelper.IsDockStateAutoHide(this.m_activeContent.DockHandler.DockState))
						{
							this.AddLastToActiveList(this.m_activeContent);
						}
					}
				}
			}
			private void SetActiveDocumentPane()
			{
				DockPane dockPane = null;
				if (this.ActivePane != null && this.ActivePane.DockState == DockState.Document)
				{
					dockPane = this.ActivePane;
				}
				if (dockPane == null && this.DockPanel.DockWindows != null)
				{
					if (this.ActiveDocumentPane == null)
					{
						dockPane = this.DockPanel.DockWindows[DockState.Document].DefaultPane;
					}
					else
					{
						if (this.ActiveDocumentPane.DockPanel != this.DockPanel || this.ActiveDocumentPane.DockState != DockState.Document)
						{
							dockPane = this.DockPanel.DockWindows[DockState.Document].DefaultPane;
						}
						else
						{
							dockPane = this.ActiveDocumentPane;
						}
					}
				}
				if (this.m_activeDocumentPane != dockPane)
				{
					if (this.m_activeDocumentPane != null)
					{
						this.m_activeDocumentPane.SetIsActiveDocumentPane(false);
					}
					this.m_activeDocumentPane = dockPane;
					if (this.m_activeDocumentPane != null)
					{
						this.m_activeDocumentPane.SetIsActiveDocumentPane(true);
					}
				}
			}
			private void SetActiveDocument()
			{
				IDockContent dockContent = (this.ActiveDocumentPane == null) ? null : this.ActiveDocumentPane.ActiveContent;
				if (this.m_activeDocument != dockContent)
				{
					this.m_activeDocument = dockContent;
				}
			}
		}
		private class MdiClientController : NativeWindow, IComponent, IDisposable
		{
			private bool m_autoScroll = true;
			private BorderStyle m_borderStyle = BorderStyle.Fixed3D;
			private MdiClient m_mdiClient = null;
			private Form m_parentForm = null;
			private ISite m_site = null;
			public event EventHandler Disposed;
			public event EventHandler HandleAssigned;
			public event EventHandler MdiChildActivate;
			public event LayoutEventHandler Layout;
			public event PaintEventHandler Paint;
			public bool AutoScroll
			{
				get
				{
					return this.m_autoScroll;
				}
				set
				{
					this.m_autoScroll = value;
					if (this.MdiClient != null)
					{
						this.UpdateStyles();
					}
				}
			}
			public BorderStyle BorderStyle
			{
				set
				{
					if (!Enum.IsDefined(typeof(BorderStyle), value))
					{
						throw new InvalidEnumArgumentException();
					}
					this.m_borderStyle = value;
					if (this.MdiClient != null)
					{
						if (this.Site == null || !this.Site.DesignMode)
						{
							int num = NativeMethods.GetWindowLong(this.MdiClient.Handle, -16);
							int num2 = NativeMethods.GetWindowLong(this.MdiClient.Handle, -20);
							switch (this.m_borderStyle)
							{
							case BorderStyle.None:
								num &= -8388609;
								num2 &= -513;
								break;

							case BorderStyle.FixedSingle:
								num2 &= -513;
								num |= 8388608;
								break;

							case BorderStyle.Fixed3D:
								num2 |= 512;
								num &= -8388609;
								break;
							}
							NativeMethods.SetWindowLong(this.MdiClient.Handle, -16, num);
							NativeMethods.SetWindowLong(this.MdiClient.Handle, -20, num2);
							this.UpdateStyles();
						}
					}
				}
			}
			public MdiClient MdiClient
			{
				get
				{
					return this.m_mdiClient;
				}
			}
			[Browsable(false)]
			public Form ParentForm
			{
				get
				{
					return this.m_parentForm;
				}
				set
				{
					if (this.m_parentForm != null)
					{
						this.m_parentForm.HandleCreated -= new EventHandler(this.ParentFormHandleCreated);
						this.m_parentForm.MdiChildActivate -= new EventHandler(this.ParentFormMdiChildActivate);
					}
					this.m_parentForm = value;
					if (this.m_parentForm != null)
					{
						if (this.m_parentForm.IsHandleCreated)
						{
							this.InitializeMdiClient();
							this.RefreshProperties();
						}
						else
						{
							this.m_parentForm.HandleCreated += new EventHandler(this.ParentFormHandleCreated);
						}
						this.m_parentForm.MdiChildActivate += new EventHandler(this.ParentFormMdiChildActivate);
					}
				}
			}
			public ISite Site
			{
				get
				{
					return this.m_site;
				}
				set
				{
					this.m_site = value;
					if (this.m_site != null)
					{
						IDesignerHost designerHost = value.GetService(typeof(IDesignerHost)) as IDesignerHost;
						if (designerHost != null)
						{
							Form form = designerHost.RootComponent as Form;
							if (form != null)
							{
								this.ParentForm = form;
							}
						}
					}
				}
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
						if (this.Site != null && this.Site.Container != null)
						{
							this.Site.Container.Remove(this);
						}
						if (this.Disposed != null)
						{
							this.Disposed(this, EventArgs.Empty);
						}
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
			public void RenewMdiClient()
			{
				this.InitializeMdiClient();
				this.RefreshProperties();
			}
			protected virtual void OnHandleAssigned(EventArgs e)
			{
				if (this.HandleAssigned != null)
				{
					this.HandleAssigned(this, e);
				}
			}
			protected virtual void OnMdiChildActivate(EventArgs e)
			{
				if (this.MdiChildActivate != null)
				{
					this.MdiChildActivate(this, e);
				}
			}
			protected virtual void OnLayout(LayoutEventArgs e)
			{
				if (this.Layout != null)
				{
					this.Layout(this, e);
				}
			}
			protected virtual void OnPaint(PaintEventArgs e)
			{
				if (this.Paint != null)
				{
					this.Paint(this, e);
				}
			}
			protected override void WndProc(ref Message m)
			{
				int msg = m.Msg;
				if (msg == 131)
				{
					if (!this.AutoScroll)
					{
						NativeMethods.ShowScrollBar(m.HWnd, 3, 0);
					}
				}
				base.WndProc(ref m);
			}
			private void ParentFormHandleCreated(object sender, EventArgs e)
			{
				this.m_parentForm.HandleCreated -= new EventHandler(this.ParentFormHandleCreated);
				this.InitializeMdiClient();
				this.RefreshProperties();
			}
			private void ParentFormMdiChildActivate(object sender, EventArgs e)
			{
				this.OnMdiChildActivate(e);
			}
			private void MdiClientLayout(object sender, LayoutEventArgs e)
			{
				this.OnLayout(e);
			}
			private void MdiClientHandleDestroyed(object sender, EventArgs e)
			{
				if (this.m_mdiClient != null)
				{
					this.m_mdiClient.HandleDestroyed -= new EventHandler(this.MdiClientHandleDestroyed);
					this.m_mdiClient = null;
				}
				this.ReleaseHandle();
			}
			private void InitializeMdiClient()
			{
				if (this.MdiClient != null)
				{
					this.MdiClient.HandleDestroyed -= new EventHandler(this.MdiClientHandleDestroyed);
					this.MdiClient.Layout -= new LayoutEventHandler(this.MdiClientLayout);
				}
				if (this.ParentForm != null)
				{
					foreach (Control control in this.ParentForm.Controls)
					{
						this.m_mdiClient = (control as MdiClient);
						if (this.m_mdiClient != null)
						{
							this.ReleaseHandle();
							base.AssignHandle(this.MdiClient.Handle);
							this.OnHandleAssigned(EventArgs.Empty);
							this.MdiClient.HandleDestroyed += new EventHandler(this.MdiClientHandleDestroyed);
							this.MdiClient.Layout += new LayoutEventHandler(this.MdiClientLayout);
							break;
						}
					}
				}
			}
			private void RefreshProperties()
			{
				this.BorderStyle = this.m_borderStyle;
				this.AutoScroll = this.m_autoScroll;
			}
			private void UpdateStyles()
			{
				NativeMethods.SetWindowPos(this.MdiClient.Handle, IntPtr.Zero, 0, 0, 0, 0, FlagsSetWindowPos.SWP_NOSIZE | FlagsSetWindowPos.SWP_NOMOVE | FlagsSetWindowPos.SWP_NOZORDER | FlagsSetWindowPos.SWP_NOACTIVATE | FlagsSetWindowPos.SWP_FRAMECHANGED | FlagsSetWindowPos.SWP_NOOWNERZORDER);
			}
		}
		private static class Persistor
		{
			private class DummyContent : DockContent
			{
			}
			private struct DockPanelStruct
			{
				private double m_dockLeftPortion;
				private double m_dockRightPortion;
				private double m_dockTopPortion;
				private double m_dockBottomPortion;
				private int m_indexActiveDocumentPane;
				private int m_indexActivePane;
				public double DockLeftPortion
				{
					get
					{
						return this.m_dockLeftPortion;
					}
					set
					{
						this.m_dockLeftPortion = value;
					}
				}
				public double DockRightPortion
				{
					get
					{
						return this.m_dockRightPortion;
					}
					set
					{
						this.m_dockRightPortion = value;
					}
				}
				public double DockTopPortion
				{
					get
					{
						return this.m_dockTopPortion;
					}
					set
					{
						this.m_dockTopPortion = value;
					}
				}
				public double DockBottomPortion
				{
					get
					{
						return this.m_dockBottomPortion;
					}
					set
					{
						this.m_dockBottomPortion = value;
					}
				}
				public int IndexActiveDocumentPane
				{
					get
					{
						return this.m_indexActiveDocumentPane;
					}
					set
					{
						this.m_indexActiveDocumentPane = value;
					}
				}
				public int IndexActivePane
				{
					get
					{
						return this.m_indexActivePane;
					}
					set
					{
						this.m_indexActivePane = value;
					}
				}
			}
			private struct ContentStruct
			{
				private string m_persistString;
				private double m_autoHidePortion;
				private bool m_isHidden;
				private bool m_isFloat;
				public string PersistString
				{
					get
					{
						return this.m_persistString;
					}
					set
					{
						this.m_persistString = value;
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
						this.m_autoHidePortion = value;
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
						this.m_isHidden = value;
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
						this.m_isFloat = value;
					}
				}
			}
			private struct PaneStruct
			{
				private DockState m_dockState;
				private int m_indexActiveContent;
				private int[] m_indexContents;
				private int m_zOrderIndex;
				public DockState DockState
				{
					get
					{
						return this.m_dockState;
					}
					set
					{
						this.m_dockState = value;
					}
				}
				public int IndexActiveContent
				{
					get
					{
						return this.m_indexActiveContent;
					}
					set
					{
						this.m_indexActiveContent = value;
					}
				}
				public int[] IndexContents
				{
					get
					{
						return this.m_indexContents;
					}
					set
					{
						this.m_indexContents = value;
					}
				}
				public int ZOrderIndex
				{
					get
					{
						return this.m_zOrderIndex;
					}
					set
					{
						this.m_zOrderIndex = value;
					}
				}
			}
			private struct NestedPane
			{
				private int m_indexPane;
				private int m_indexPrevPane;
				private DockAlignment m_alignment;
				private double m_proportion;
				public int IndexPane
				{
					get
					{
						return this.m_indexPane;
					}
					set
					{
						this.m_indexPane = value;
					}
				}
				public int IndexPrevPane
				{
					get
					{
						return this.m_indexPrevPane;
					}
					set
					{
						this.m_indexPrevPane = value;
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
					}
				}
				public double Proportion
				{
					get
					{
						return this.m_proportion;
					}
					set
					{
						this.m_proportion = value;
					}
				}
			}
			private struct DockWindowStruct
			{
				private DockState m_dockState;
				private int m_zOrderIndex;
				private DockPanel.Persistor.NestedPane[] m_nestedPanes;
				public DockState DockState
				{
					get
					{
						return this.m_dockState;
					}
					set
					{
						this.m_dockState = value;
					}
				}
				public int ZOrderIndex
				{
					get
					{
						return this.m_zOrderIndex;
					}
					set
					{
						this.m_zOrderIndex = value;
					}
				}
				public DockPanel.Persistor.NestedPane[] NestedPanes
				{
					get
					{
						return this.m_nestedPanes;
					}
					set
					{
						this.m_nestedPanes = value;
					}
				}
			}
			private struct FloatWindowStruct
			{
				private Rectangle m_bounds;
				private int m_zOrderIndex;
				private DockPanel.Persistor.NestedPane[] m_nestedPanes;
				public Rectangle Bounds
				{
					get
					{
						return this.m_bounds;
					}
					set
					{
						this.m_bounds = value;
					}
				}
				public int ZOrderIndex
				{
					get
					{
						return this.m_zOrderIndex;
					}
					set
					{
						this.m_zOrderIndex = value;
					}
				}
				public DockPanel.Persistor.NestedPane[] NestedPanes
				{
					get
					{
						return this.m_nestedPanes;
					}
					set
					{
						this.m_nestedPanes = value;
					}
				}
			}
			private const string ConfigFileVersion = "1.0";
			private static string[] CompatibleConfigFileVersions = new string[0];
			public static void SaveAsXml(DockPanel dockPanel, string fileName)
			{
				DockPanel.Persistor.SaveAsXml(dockPanel, fileName, Encoding.Unicode);
			}
			public static void SaveAsXml(DockPanel dockPanel, string fileName, Encoding encoding)
			{
				FileStream fileStream = new FileStream(fileName, FileMode.Create);
				try
				{
					DockPanel.Persistor.SaveAsXml(dockPanel, fileStream, encoding);
				}
				finally
				{
					fileStream.Close();
				}
			}
			public static void SaveAsXml(DockPanel dockPanel, Stream stream, Encoding encoding)
			{
				DockPanel.Persistor.SaveAsXml(dockPanel, stream, encoding, false);
			}
			public static void SaveAsXml(DockPanel dockPanel, Stream stream, Encoding encoding, bool upstream)
			{
				XmlTextWriter xmlTextWriter = new XmlTextWriter(stream, encoding);
				xmlTextWriter.Formatting = Formatting.Indented;
				if (!upstream)
				{
					xmlTextWriter.WriteStartDocument();
				}
				xmlTextWriter.WriteComment(Strings.DockPanel_Persistor_XmlFileComment1);
				xmlTextWriter.WriteComment(Strings.DockPanel_Persistor_XmlFileComment2);
				xmlTextWriter.WriteStartElement("DockPanel");
				xmlTextWriter.WriteAttributeString("FormatVersion", "1.0");
				xmlTextWriter.WriteAttributeString("DockLeftPortion", dockPanel.DockLeftPortion.ToString(CultureInfo.InvariantCulture));
				xmlTextWriter.WriteAttributeString("DockRightPortion", dockPanel.DockRightPortion.ToString(CultureInfo.InvariantCulture));
				xmlTextWriter.WriteAttributeString("DockTopPortion", dockPanel.DockTopPortion.ToString(CultureInfo.InvariantCulture));
				xmlTextWriter.WriteAttributeString("DockBottomPortion", dockPanel.DockBottomPortion.ToString(CultureInfo.InvariantCulture));
				xmlTextWriter.WriteAttributeString("ActiveDocumentPane", dockPanel.Panes.IndexOf(dockPanel.ActiveDocumentPane).ToString(CultureInfo.InvariantCulture));
				xmlTextWriter.WriteAttributeString("ActivePane", dockPanel.Panes.IndexOf(dockPanel.ActivePane).ToString(CultureInfo.InvariantCulture));
				xmlTextWriter.WriteStartElement("Contents");
				xmlTextWriter.WriteAttributeString("Count", dockPanel.Contents.Count.ToString(CultureInfo.InvariantCulture));
				foreach (IDockContent current in dockPanel.Contents)
				{
					xmlTextWriter.WriteStartElement("Content");
					xmlTextWriter.WriteAttributeString("ID", dockPanel.Contents.IndexOf(current).ToString(CultureInfo.InvariantCulture));
					xmlTextWriter.WriteAttributeString("PersistString", current.DockHandler.PersistString);
					xmlTextWriter.WriteAttributeString("AutoHidePortion", current.DockHandler.AutoHidePortion.ToString(CultureInfo.InvariantCulture));
					xmlTextWriter.WriteAttributeString("IsHidden", current.DockHandler.IsHidden.ToString(CultureInfo.InvariantCulture));
					xmlTextWriter.WriteAttributeString("IsFloat", current.DockHandler.IsFloat.ToString(CultureInfo.InvariantCulture));
					xmlTextWriter.WriteEndElement();
				}
				xmlTextWriter.WriteEndElement();
				xmlTextWriter.WriteStartElement("Panes");
				xmlTextWriter.WriteAttributeString("Count", dockPanel.Panes.Count.ToString(CultureInfo.InvariantCulture));
				foreach (DockPane current2 in dockPanel.Panes)
				{
					xmlTextWriter.WriteStartElement("Pane");
					xmlTextWriter.WriteAttributeString("ID", dockPanel.Panes.IndexOf(current2).ToString(CultureInfo.InvariantCulture));
					xmlTextWriter.WriteAttributeString("DockState", current2.DockState.ToString());
					xmlTextWriter.WriteAttributeString("ActiveContent", dockPanel.Contents.IndexOf(current2.ActiveContent).ToString(CultureInfo.InvariantCulture));
					xmlTextWriter.WriteStartElement("Contents");
					xmlTextWriter.WriteAttributeString("Count", current2.Contents.Count.ToString(CultureInfo.InvariantCulture));
					foreach (IDockContent current in current2.Contents)
					{
						xmlTextWriter.WriteStartElement("Content");
						xmlTextWriter.WriteAttributeString("ID", current2.Contents.IndexOf(current).ToString(CultureInfo.InvariantCulture));
						xmlTextWriter.WriteAttributeString("RefID", dockPanel.Contents.IndexOf(current).ToString(CultureInfo.InvariantCulture));
						xmlTextWriter.WriteEndElement();
					}
					xmlTextWriter.WriteEndElement();
					xmlTextWriter.WriteEndElement();
				}
				xmlTextWriter.WriteEndElement();
				xmlTextWriter.WriteStartElement("DockWindows");
				int num = 0;
				checked
				{
					foreach (DockWindow current3 in dockPanel.DockWindows)
					{
						xmlTextWriter.WriteStartElement("DockWindow");
						xmlTextWriter.WriteAttributeString("ID", num.ToString(CultureInfo.InvariantCulture));
						num++;
						xmlTextWriter.WriteAttributeString("DockState", current3.DockState.ToString());
						xmlTextWriter.WriteAttributeString("ZOrderIndex", dockPanel.Controls.IndexOf(current3).ToString(CultureInfo.InvariantCulture));
						xmlTextWriter.WriteStartElement("NestedPanes");
						xmlTextWriter.WriteAttributeString("Count", current3.NestedPanes.Count.ToString(CultureInfo.InvariantCulture));
						foreach (DockPane current2 in current3.NestedPanes)
						{
							xmlTextWriter.WriteStartElement("Pane");
							xmlTextWriter.WriteAttributeString("ID", current3.NestedPanes.IndexOf(current2).ToString(CultureInfo.InvariantCulture));
							xmlTextWriter.WriteAttributeString("RefID", dockPanel.Panes.IndexOf(current2).ToString(CultureInfo.InvariantCulture));
							NestedDockingStatus nestedDockingStatus = current2.NestedDockingStatus;
							xmlTextWriter.WriteAttributeString("PrevPane", dockPanel.Panes.IndexOf(nestedDockingStatus.PreviousPane).ToString(CultureInfo.InvariantCulture));
							xmlTextWriter.WriteAttributeString("Alignment", nestedDockingStatus.Alignment.ToString());
							xmlTextWriter.WriteAttributeString("Proportion", nestedDockingStatus.Proportion.ToString(CultureInfo.InvariantCulture));
							xmlTextWriter.WriteEndElement();
						}
						xmlTextWriter.WriteEndElement();
						xmlTextWriter.WriteEndElement();
					}
					xmlTextWriter.WriteEndElement();
					RectangleConverter rectangleConverter = new RectangleConverter();
					xmlTextWriter.WriteStartElement("FloatWindows");
					xmlTextWriter.WriteAttributeString("Count", dockPanel.FloatWindows.Count.ToString(CultureInfo.InvariantCulture));
					foreach (FloatWindow current4 in dockPanel.FloatWindows)
					{
						xmlTextWriter.WriteStartElement("FloatWindow");
						xmlTextWriter.WriteAttributeString("ID", dockPanel.FloatWindows.IndexOf(current4).ToString(CultureInfo.InvariantCulture));
						xmlTextWriter.WriteAttributeString("Bounds", rectangleConverter.ConvertToInvariantString(current4.Bounds));
						xmlTextWriter.WriteAttributeString("ZOrderIndex", current4.DockPanel.FloatWindows.IndexOf(current4).ToString(CultureInfo.InvariantCulture));
						xmlTextWriter.WriteStartElement("NestedPanes");
						xmlTextWriter.WriteAttributeString("Count", current4.NestedPanes.Count.ToString(CultureInfo.InvariantCulture));
						foreach (DockPane current2 in current4.NestedPanes)
						{
							xmlTextWriter.WriteStartElement("Pane");
							xmlTextWriter.WriteAttributeString("ID", current4.NestedPanes.IndexOf(current2).ToString(CultureInfo.InvariantCulture));
							xmlTextWriter.WriteAttributeString("RefID", dockPanel.Panes.IndexOf(current2).ToString(CultureInfo.InvariantCulture));
							NestedDockingStatus nestedDockingStatus = current2.NestedDockingStatus;
							xmlTextWriter.WriteAttributeString("PrevPane", dockPanel.Panes.IndexOf(nestedDockingStatus.PreviousPane).ToString(CultureInfo.InvariantCulture));
							xmlTextWriter.WriteAttributeString("Alignment", nestedDockingStatus.Alignment.ToString());
							xmlTextWriter.WriteAttributeString("Proportion", nestedDockingStatus.Proportion.ToString(CultureInfo.InvariantCulture));
							xmlTextWriter.WriteEndElement();
						}
						xmlTextWriter.WriteEndElement();
						xmlTextWriter.WriteEndElement();
					}
					xmlTextWriter.WriteEndElement();
					xmlTextWriter.WriteEndElement();
					if (!upstream)
					{
						xmlTextWriter.WriteEndDocument();
						xmlTextWriter.Close();
					}
					else
					{
						xmlTextWriter.Flush();
					}
				}
			}
			public static void LoadFromXml(DockPanel dockPanel, string fileName, DeserializeDockContent deserializeContent)
			{
				FileStream fileStream = new FileStream(fileName, FileMode.Open, FileAccess.Read);
				try
				{
					DockPanel.Persistor.LoadFromXml(dockPanel, fileStream, deserializeContent);
				}
				finally
				{
					fileStream.Close();
				}
			}
			public static void LoadFromXml(DockPanel dockPanel, Stream stream, DeserializeDockContent deserializeContent)
			{
				DockPanel.Persistor.LoadFromXml(dockPanel, stream, deserializeContent, true);
			}
			private static DockPanel.Persistor.ContentStruct[] LoadContents(XmlTextReader xmlIn)
			{
				int num = Convert.ToInt32(xmlIn.GetAttribute("Count"), CultureInfo.InvariantCulture);
				DockPanel.Persistor.ContentStruct[] array = new DockPanel.Persistor.ContentStruct[num];
				DockPanel.Persistor.MoveToNextElement(xmlIn);
				checked
				{
					for (int i = 0; i < num; i++)
					{
						int num2 = Convert.ToInt32(xmlIn.GetAttribute("ID"), CultureInfo.InvariantCulture);
						if (xmlIn.Name != "Content" || num2 != i)
						{
							throw new ArgumentException(Strings.DockPanel_LoadFromXml_InvalidXmlFormat);
						}
						array[i].PersistString = xmlIn.GetAttribute("PersistString");
						array[i].AutoHidePortion = Convert.ToDouble(xmlIn.GetAttribute("AutoHidePortion"), CultureInfo.InvariantCulture);
						array[i].IsHidden = Convert.ToBoolean(xmlIn.GetAttribute("IsHidden"), CultureInfo.InvariantCulture);
						array[i].IsFloat = Convert.ToBoolean(xmlIn.GetAttribute("IsFloat"), CultureInfo.InvariantCulture);
						DockPanel.Persistor.MoveToNextElement(xmlIn);
					}
					return array;
				}
			}
			private static DockPanel.Persistor.PaneStruct[] LoadPanes(XmlTextReader xmlIn)
			{
				EnumConverter enumConverter = new EnumConverter(typeof(DockState));
				int num = Convert.ToInt32(xmlIn.GetAttribute("Count"), CultureInfo.InvariantCulture);
				DockPanel.Persistor.PaneStruct[] array = new DockPanel.Persistor.PaneStruct[num];
				DockPanel.Persistor.MoveToNextElement(xmlIn);
				checked
				{
					for (int i = 0; i < num; i++)
					{
						int num2 = Convert.ToInt32(xmlIn.GetAttribute("ID"), CultureInfo.InvariantCulture);
						if (xmlIn.Name != "Pane" || num2 != i)
						{
							throw new ArgumentException(Strings.DockPanel_LoadFromXml_InvalidXmlFormat);
						}
						array[i].DockState = (DockState)enumConverter.ConvertFrom(xmlIn.GetAttribute("DockState"));
						array[i].IndexActiveContent = Convert.ToInt32(xmlIn.GetAttribute("ActiveContent"), CultureInfo.InvariantCulture);
						array[i].ZOrderIndex = -1;
						DockPanel.Persistor.MoveToNextElement(xmlIn);
						if (xmlIn.Name != "Contents")
						{
							throw new ArgumentException(Strings.DockPanel_LoadFromXml_InvalidXmlFormat);
						}
						int num3 = Convert.ToInt32(xmlIn.GetAttribute("Count"), CultureInfo.InvariantCulture);
						array[i].IndexContents = new int[num3];
						DockPanel.Persistor.MoveToNextElement(xmlIn);
						for (int j = 0; j < num3; j++)
						{
							int num4 = Convert.ToInt32(xmlIn.GetAttribute("ID"), CultureInfo.InvariantCulture);
							if (xmlIn.Name != "Content" || num4 != j)
							{
								throw new ArgumentException(Strings.DockPanel_LoadFromXml_InvalidXmlFormat);
							}
							array[i].IndexContents[j] = Convert.ToInt32(xmlIn.GetAttribute("RefID"), CultureInfo.InvariantCulture);
							DockPanel.Persistor.MoveToNextElement(xmlIn);
						}
					}
					return array;
				}
			}
			private static DockPanel.Persistor.DockWindowStruct[] LoadDockWindows(XmlTextReader xmlIn, DockPanel dockPanel)
			{
				EnumConverter enumConverter = new EnumConverter(typeof(DockState));
				EnumConverter enumConverter2 = new EnumConverter(typeof(DockAlignment));
				int count = dockPanel.DockWindows.Count;
				DockPanel.Persistor.DockWindowStruct[] array = new DockPanel.Persistor.DockWindowStruct[count];
				DockPanel.Persistor.MoveToNextElement(xmlIn);
				checked
				{
					for (int i = 0; i < count; i++)
					{
						int num = Convert.ToInt32(xmlIn.GetAttribute("ID"), CultureInfo.InvariantCulture);
						if (xmlIn.Name != "DockWindow" || num != i)
						{
							throw new ArgumentException(Strings.DockPanel_LoadFromXml_InvalidXmlFormat);
						}
						array[i].DockState = (DockState)enumConverter.ConvertFrom(xmlIn.GetAttribute("DockState"));
						array[i].ZOrderIndex = Convert.ToInt32(xmlIn.GetAttribute("ZOrderIndex"), CultureInfo.InvariantCulture);
						DockPanel.Persistor.MoveToNextElement(xmlIn);
						if (xmlIn.Name != "DockList" && xmlIn.Name != "NestedPanes")
						{
							throw new ArgumentException(Strings.DockPanel_LoadFromXml_InvalidXmlFormat);
						}
						int num2 = Convert.ToInt32(xmlIn.GetAttribute("Count"), CultureInfo.InvariantCulture);
						array[i].NestedPanes = new DockPanel.Persistor.NestedPane[num2];
						DockPanel.Persistor.MoveToNextElement(xmlIn);
						for (int j = 0; j < num2; j++)
						{
							int num3 = Convert.ToInt32(xmlIn.GetAttribute("ID"), CultureInfo.InvariantCulture);
							if (xmlIn.Name != "Pane" || num3 != j)
							{
								throw new ArgumentException(Strings.DockPanel_LoadFromXml_InvalidXmlFormat);
							}
							array[i].NestedPanes[j].IndexPane = Convert.ToInt32(xmlIn.GetAttribute("RefID"), CultureInfo.InvariantCulture);
							array[i].NestedPanes[j].IndexPrevPane = Convert.ToInt32(xmlIn.GetAttribute("PrevPane"), CultureInfo.InvariantCulture);
							array[i].NestedPanes[j].Alignment = (DockAlignment)enumConverter2.ConvertFrom(xmlIn.GetAttribute("Alignment"));
							array[i].NestedPanes[j].Proportion = Convert.ToDouble(xmlIn.GetAttribute("Proportion"), CultureInfo.InvariantCulture);
							DockPanel.Persistor.MoveToNextElement(xmlIn);
						}
					}
					return array;
				}
			}
			private static DockPanel.Persistor.FloatWindowStruct[] LoadFloatWindows(XmlTextReader xmlIn)
			{
				EnumConverter enumConverter = new EnumConverter(typeof(DockAlignment));
				RectangleConverter rectangleConverter = new RectangleConverter();
				int num = Convert.ToInt32(xmlIn.GetAttribute("Count"), CultureInfo.InvariantCulture);
				DockPanel.Persistor.FloatWindowStruct[] array = new DockPanel.Persistor.FloatWindowStruct[num];
				DockPanel.Persistor.MoveToNextElement(xmlIn);
				checked
				{
					for (int i = 0; i < num; i++)
					{
						int num2 = Convert.ToInt32(xmlIn.GetAttribute("ID"), CultureInfo.InvariantCulture);
						if (xmlIn.Name != "FloatWindow" || num2 != i)
						{
							throw new ArgumentException(Strings.DockPanel_LoadFromXml_InvalidXmlFormat);
						}
						array[i].Bounds = (Rectangle)rectangleConverter.ConvertFromInvariantString(xmlIn.GetAttribute("Bounds"));
						array[i].ZOrderIndex = Convert.ToInt32(xmlIn.GetAttribute("ZOrderIndex"), CultureInfo.InvariantCulture);
						DockPanel.Persistor.MoveToNextElement(xmlIn);
						if (xmlIn.Name != "DockList" && xmlIn.Name != "NestedPanes")
						{
							throw new ArgumentException(Strings.DockPanel_LoadFromXml_InvalidXmlFormat);
						}
						int num3 = Convert.ToInt32(xmlIn.GetAttribute("Count"), CultureInfo.InvariantCulture);
						array[i].NestedPanes = new DockPanel.Persistor.NestedPane[num3];
						DockPanel.Persistor.MoveToNextElement(xmlIn);
						for (int j = 0; j < num3; j++)
						{
							int num4 = Convert.ToInt32(xmlIn.GetAttribute("ID"), CultureInfo.InvariantCulture);
							if (xmlIn.Name != "Pane" || num4 != j)
							{
								throw new ArgumentException(Strings.DockPanel_LoadFromXml_InvalidXmlFormat);
							}
							array[i].NestedPanes[j].IndexPane = Convert.ToInt32(xmlIn.GetAttribute("RefID"), CultureInfo.InvariantCulture);
							array[i].NestedPanes[j].IndexPrevPane = Convert.ToInt32(xmlIn.GetAttribute("PrevPane"), CultureInfo.InvariantCulture);
							array[i].NestedPanes[j].Alignment = (DockAlignment)enumConverter.ConvertFrom(xmlIn.GetAttribute("Alignment"));
							array[i].NestedPanes[j].Proportion = Convert.ToDouble(xmlIn.GetAttribute("Proportion"), CultureInfo.InvariantCulture);
							DockPanel.Persistor.MoveToNextElement(xmlIn);
						}
					}
					return array;
				}
			}
			public static void LoadFromXml(DockPanel dockPanel, Stream stream, DeserializeDockContent deserializeContent, bool closeStream)
			{
				if (dockPanel.Contents.Count != 0)
				{
					throw new InvalidOperationException(Strings.DockPanel_LoadFromXml_AlreadyInitialized);
				}
				XmlTextReader xmlTextReader = new XmlTextReader(stream);
				xmlTextReader.WhitespaceHandling = WhitespaceHandling.None;
				xmlTextReader.MoveToContent();
				while (!xmlTextReader.Name.Equals("DockPanel"))
				{
					if (!DockPanel.Persistor.MoveToNextElement(xmlTextReader))
					{
						throw new ArgumentException(Strings.DockPanel_LoadFromXml_InvalidXmlFormat);
					}
				}
				string attribute = xmlTextReader.GetAttribute("FormatVersion");
				if (!DockPanel.Persistor.IsFormatVersionValid(attribute))
				{
					throw new ArgumentException(Strings.DockPanel_LoadFromXml_InvalidFormatVersion);
				}
				DockPanel.Persistor.DockPanelStruct dockPanelStruct = default(DockPanel.Persistor.DockPanelStruct);
				dockPanelStruct.DockLeftPortion = Convert.ToDouble(xmlTextReader.GetAttribute("DockLeftPortion"), CultureInfo.InvariantCulture);
				dockPanelStruct.DockRightPortion = Convert.ToDouble(xmlTextReader.GetAttribute("DockRightPortion"), CultureInfo.InvariantCulture);
				dockPanelStruct.DockTopPortion = Convert.ToDouble(xmlTextReader.GetAttribute("DockTopPortion"), CultureInfo.InvariantCulture);
				dockPanelStruct.DockBottomPortion = Convert.ToDouble(xmlTextReader.GetAttribute("DockBottomPortion"), CultureInfo.InvariantCulture);
				dockPanelStruct.IndexActiveDocumentPane = Convert.ToInt32(xmlTextReader.GetAttribute("ActiveDocumentPane"), CultureInfo.InvariantCulture);
				dockPanelStruct.IndexActivePane = Convert.ToInt32(xmlTextReader.GetAttribute("ActivePane"), CultureInfo.InvariantCulture);
				DockPanel.Persistor.MoveToNextElement(xmlTextReader);
				if (xmlTextReader.Name != "Contents")
				{
					throw new ArgumentException(Strings.DockPanel_LoadFromXml_InvalidXmlFormat);
				}
				DockPanel.Persistor.ContentStruct[] array = DockPanel.Persistor.LoadContents(xmlTextReader);
				if (xmlTextReader.Name != "Panes")
				{
					throw new ArgumentException(Strings.DockPanel_LoadFromXml_InvalidXmlFormat);
				}
				DockPanel.Persistor.PaneStruct[] array2 = DockPanel.Persistor.LoadPanes(xmlTextReader);
				if (xmlTextReader.Name != "DockWindows")
				{
					throw new ArgumentException(Strings.DockPanel_LoadFromXml_InvalidXmlFormat);
				}
				DockPanel.Persistor.DockWindowStruct[] array3 = DockPanel.Persistor.LoadDockWindows(xmlTextReader, dockPanel);
				if (xmlTextReader.Name != "FloatWindows")
				{
					throw new ArgumentException(Strings.DockPanel_LoadFromXml_InvalidXmlFormat);
				}
				DockPanel.Persistor.FloatWindowStruct[] array4 = DockPanel.Persistor.LoadFloatWindows(xmlTextReader);
				if (closeStream)
				{
					xmlTextReader.Close();
				}
				dockPanel.SuspendLayout(true);
				dockPanel.DockLeftPortion = dockPanelStruct.DockLeftPortion;
				dockPanel.DockRightPortion = dockPanelStruct.DockRightPortion;
				dockPanel.DockTopPortion = dockPanelStruct.DockTopPortion;
				dockPanel.DockBottomPortion = dockPanelStruct.DockBottomPortion;
				int num = 2147483647;
				checked
				{
					for (int i = 0; i < array3.Length; i++)
					{
						int num2 = -1;
						int num3 = -1;
						for (int j = 0; j < array3.Length; j++)
						{
							if (array3[j].ZOrderIndex > num2 && array3[j].ZOrderIndex < num)
							{
								num2 = array3[j].ZOrderIndex;
								num3 = j;
							}
						}
						dockPanel.DockWindows[array3[num3].DockState].BringToFront();
						num = num2;
					}
					for (int i = 0; i < array.Length; i++)
					{
						IDockContent dockContent = deserializeContent(array[i].PersistString);
						if (dockContent == null)
						{
							dockContent = new DockPanel.Persistor.DummyContent();
						}
						dockContent.DockHandler.DockPanel = dockPanel;
						dockContent.DockHandler.AutoHidePortion = array[i].AutoHidePortion;
						dockContent.DockHandler.IsHidden = true;
						dockContent.DockHandler.IsFloat = array[i].IsFloat;
					}
					for (int i = 0; i < array2.Length; i++)
					{
						DockPane dockPane = null;
						for (int j = 0; j < array2[i].IndexContents.Length; j++)
						{
							IDockContent dockContent = dockPanel.Contents[array2[i].IndexContents[j]];
                            if (dockContent == null)
                                continue;
							if (j == 0)
							{
								dockPane = dockPanel.DockPaneFactory.CreateDockPane(dockContent, array2[i].DockState, false);
							}
							else
							{
								if (array2[i].DockState == DockState.Float)
								{
									dockContent.DockHandler.FloatPane = dockPane;
								}
								else
								{
									dockContent.DockHandler.PanelPane = dockPane;
								}
							}
						}
					}
					for (int i = 0; i < array3.Length; i++)
					{
						for (int j = 0; j < array3[i].NestedPanes.Length; j++)
						{
							DockWindow dockWindow = dockPanel.DockWindows[array3[i].DockState];
							int indexPane = array3[i].NestedPanes[j].IndexPane;
							DockPane dockPane = dockPanel.Panes[indexPane];
							int indexPrevPane = array3[i].NestedPanes[j].IndexPrevPane;
							DockPane previousPane = (indexPrevPane == -1) ? dockWindow.NestedPanes.GetDefaultPreviousPane(dockPane) : dockPanel.Panes[indexPrevPane];
							DockAlignment alignment = array3[i].NestedPanes[j].Alignment;
							double proportion = array3[i].NestedPanes[j].Proportion;
							dockPane.DockTo(dockWindow, previousPane, alignment, proportion);
							if (array2[indexPane].DockState == dockWindow.DockState)
							{
								array2[indexPane].ZOrderIndex = array3[i].ZOrderIndex;
							}
						}
					}
					for (int i = 0; i < array4.Length; i++)
					{
						FloatWindow floatWindow = null;
						for (int j = 0; j < array4[i].NestedPanes.Length; j++)
						{
							int indexPane = array4[i].NestedPanes[j].IndexPane;
							DockPane dockPane = dockPanel.Panes[indexPane];
							if (j == 0)
							{
								floatWindow = dockPanel.FloatWindowFactory.CreateFloatWindow(dockPanel, dockPane, array4[i].Bounds);
							}
							else
							{
								int indexPrevPane = array4[i].NestedPanes[j].IndexPrevPane;
								DockPane previousPane = (indexPrevPane == -1) ? null : dockPanel.Panes[indexPrevPane];
								DockAlignment alignment = array4[i].NestedPanes[j].Alignment;
								double proportion = array4[i].NestedPanes[j].Proportion;
								dockPane.DockTo(floatWindow, previousPane, alignment, proportion);
							}
							if (array2[indexPane].DockState == floatWindow.DockState)
							{
								array2[indexPane].ZOrderIndex = array4[i].ZOrderIndex;
							}
						}
					}
					int[] array5 = null;
					if (array.Length > 0)
					{
						array5 = new int[array.Length];
						for (int i = 0; i < array.Length; i++)
						{
							array5[i] = i;
						}
						int num4 = array.Length;
						for (int i = 0; i < array.Length - 1; i++)
						{
							for (int j = i + 1; j < array.Length; j++)
							{
								DockPane pane = dockPanel.Contents[array5[i]].DockHandler.Pane;
								int num5 = (pane == null) ? 0 : array2[dockPanel.Panes.IndexOf(pane)].ZOrderIndex;
								DockPane pane2 = dockPanel.Contents[array5[j]].DockHandler.Pane;
								int num6 = (pane2 == null) ? 0 : array2[dockPanel.Panes.IndexOf(pane2)].ZOrderIndex;
								if (num5 > num6)
								{
									int num7 = array5[i];
									array5[i] = array5[j];
									array5[j] = num7;
								}
							}
						}
					}
					for (int i = 0; i < array.Length; i++)
					{
						IDockContent dockContent = dockPanel.Contents[array5[i]];
						if (dockContent.DockHandler.Pane != null && dockContent.DockHandler.Pane.DockState != DockState.Document)
						{
							dockContent.DockHandler.IsHidden = array[array5[i]].IsHidden;
						}
					}
					for (int i = 0; i < array.Length; i++)
					{
						IDockContent dockContent = dockPanel.Contents[array5[i]];
						if (dockContent.DockHandler.Pane != null && dockContent.DockHandler.Pane.DockState == DockState.Document)
						{
							dockContent.DockHandler.IsHidden = array[array5[i]].IsHidden;
						}
					}
					for (int i = 0; i < array2.Length; i++)
					{
						dockPanel.Panes[i].ActiveContent = ((array2[i].IndexActiveContent == -1) ? null : dockPanel.Contents[array2[i].IndexActiveContent]);
					}
					if (dockPanelStruct.IndexActiveDocumentPane != -1)
					{
						dockPanel.Panes[dockPanelStruct.IndexActiveDocumentPane].Activate();
					}
					if (dockPanelStruct.IndexActivePane != -1)
					{
						dockPanel.Panes[dockPanelStruct.IndexActivePane].Activate();
					}
					for (int i = dockPanel.Contents.Count - 1; i >= 0; i--)
					{
						if (dockPanel.Contents[i] is DockPanel.Persistor.DummyContent)
						{
							dockPanel.Contents[i].DockHandler.Form.Close();
						}
					}
					dockPanel.ResumeLayout(true, true);
				}
			}
			private static bool MoveToNextElement(XmlTextReader xmlIn)
			{
				bool result;
				if (!xmlIn.Read())
				{
					result = false;
				}
				else
				{
					while (xmlIn.NodeType == XmlNodeType.EndElement)
					{
						if (!xmlIn.Read())
						{
							result = false;
							return result;
						}
					}
					result = true;
				}
				return result;
			}
			private static bool IsFormatVersionValid(string formatVersion)
			{
				bool result;
				if (formatVersion == "1.0")
				{
					result = true;
				}
				else
				{
					string[] compatibleConfigFileVersions = DockPanel.Persistor.CompatibleConfigFileVersions;
					for (int i = 0; i < compatibleConfigFileVersions.Length; i++)
					{
						string a = compatibleConfigFileVersions[i];
						if (a == formatVersion)
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
		private sealed class SplitterDragHandler : DockPanel.DragHandler
		{
			private class SplitterOutline
			{
				private DragForm m_dragForm;
				private DragForm DragForm
				{
					get
					{
						return this.m_dragForm;
					}
				}
				public SplitterOutline()
				{
					this.m_dragForm = new DragForm();
					this.SetDragForm(Rectangle.Empty);
					this.DragForm.BackColor = Color.Black;
					this.DragForm.Opacity = 0.7;
					this.DragForm.Show(false);
				}
				public void Show(Rectangle rect)
				{
					this.SetDragForm(rect);
				}
				public void Close()
				{
					this.DragForm.Close();
				}
				private void SetDragForm(Rectangle rect)
				{
					this.DragForm.Bounds = rect;
					if (rect == Rectangle.Empty)
					{
						this.DragForm.Region = new Region(Rectangle.Empty);
					}
					else
					{
						if (this.DragForm.Region != null)
						{
							this.DragForm.Region = null;
						}
					}
				}
			}
			private DockPanel.SplitterDragHandler.SplitterOutline m_outline;
			private Rectangle m_rectSplitter;
			public new ISplitterDragSource DragSource
			{
				get
				{
					return base.DragSource as ISplitterDragSource;
				}
				private set
				{
					base.DragSource = value;
				}
			}
			private DockPanel.SplitterDragHandler.SplitterOutline Outline
			{
				get
				{
					return this.m_outline;
				}
				set
				{
					this.m_outline = value;
				}
			}
			private Rectangle RectSplitter
			{
				get
				{
					return this.m_rectSplitter;
				}
				set
				{
					this.m_rectSplitter = value;
				}
			}
			public SplitterDragHandler(DockPanel dockPanel) : base(dockPanel)
			{
			}
			public void BeginDrag(ISplitterDragSource dragSource, Rectangle rectSplitter)
			{
				this.DragSource = dragSource;
				this.RectSplitter = rectSplitter;
				if (!base.BeginDrag())
				{
					this.DragSource = null;
				}
				else
				{
					this.Outline = new DockPanel.SplitterDragHandler.SplitterOutline();
					this.Outline.Show(rectSplitter);
					this.DragSource.BeginDrag(rectSplitter);
				}
			}
			protected override void OnDragging()
			{
				this.Outline.Show(this.GetSplitterOutlineBounds(Control.MousePosition));
			}
			protected override void OnEndDrag(bool abort)
			{
				base.DockPanel.SuspendLayout(true);
				this.Outline.Close();
				if (!abort)
				{
					this.DragSource.MoveSplitter(this.GetMovingOffset(Control.MousePosition));
				}
				this.DragSource.EndDrag();
				base.DockPanel.ResumeLayout(true, true);
			}
			private int GetMovingOffset(Point ptMouse)
			{
				Rectangle splitterOutlineBounds = this.GetSplitterOutlineBounds(ptMouse);
				checked
				{
					int result;
					if (this.DragSource.IsVertical)
					{
						result = splitterOutlineBounds.X - this.RectSplitter.X;
					}
					else
					{
						result = splitterOutlineBounds.Y - this.RectSplitter.Y;
					}
					return result;
				}
			}
			private Rectangle GetSplitterOutlineBounds(Point ptMouse)
			{
				Rectangle dragLimitBounds = this.DragSource.DragLimitBounds;
				Rectangle rectSplitter = this.RectSplitter;
				checked
				{
					Rectangle result;
					if (dragLimitBounds.Width <= 0 || dragLimitBounds.Height <= 0)
					{
						result = rectSplitter;
					}
					else
					{
						if (this.DragSource.IsVertical)
						{
							rectSplitter.X += ptMouse.X - base.StartMousePosition.X;
							rectSplitter.Height = dragLimitBounds.Height;
						}
						else
						{
							rectSplitter.Y += ptMouse.Y - base.StartMousePosition.Y;
							rectSplitter.Width = dragLimitBounds.Width;
						}
						if (rectSplitter.Left < dragLimitBounds.Left)
						{
							rectSplitter.X = dragLimitBounds.X;
						}
						if (rectSplitter.Top < dragLimitBounds.Top)
						{
							rectSplitter.Y = dragLimitBounds.Y;
						}
						if (rectSplitter.Right > dragLimitBounds.Right)
						{
							rectSplitter.X -= rectSplitter.Right - dragLimitBounds.Right;
						}
						if (rectSplitter.Bottom > dragLimitBounds.Bottom)
						{
							rectSplitter.Y -= rectSplitter.Bottom - dragLimitBounds.Bottom;
						}
						result = rectSplitter;
					}
					return result;
				}
			}
		}
		private DockPanel.FocusManagerImpl m_focusManager;
		private DockPanelExtender m_extender;
		private DockPaneCollection m_panes;
		private FloatWindowCollection m_floatWindows;
		private DockPanel.AutoHideWindowControl m_autoHideWindow;
		private DockWindowCollection m_dockWindows;
		private DockContent m_dummyContent;
		private Control m_dummyControl;
		private Color m_BackColor;
		private AutoHideStripBase m_autoHideStripControl = null;
		private bool m_disposed = false;
		private bool m_allowEndUserDocking = true;
		private bool m_allowEndUserNestedDocking = true;
		private DockContentCollection m_contents = new DockContentCollection();
		private bool m_rightToLeftLayout = false;
		private bool m_showDocumentIcon = false;
		private DockPanelSkin m_dockPanelSkin = new DockPanelSkin();
		private DocumentTabStripLocation m_documentTabStripLocation = DocumentTabStripLocation.Top;
		private double m_dockBottomPortion = 0.25;
		private double m_dockLeftPortion = 0.25;
		private double m_dockRightPortion = 0.25;
		private double m_dockTopPortion = 0.25;
		private Size m_defaultFloatWindowSize = new Size(300, 300);
		private DocumentStyle m_documentStyle = DocumentStyle.DockingMdi;
		private PaintEventHandler m_dummyControlPaintEventHandler = null;
		private Rectangle[] m_clipRects = null;
		private static readonly object ContentAddedEvent = new object();
		private static readonly object ContentRemovedEvent = new object();
		private DockPanel.DockDragHandler m_dockDragHandler = null;
		private static readonly object ActiveDocumentChangedEvent = new object();
		private static readonly object ActiveContentChangedEvent = new object();
		private static readonly object ActivePaneChangedEvent = new object();
		private DockPanel.MdiClientController m_mdiClientController = null;
		private DockPanel.SplitterDragHandler m_splitterDragHandler = null;
		[LocalizedCategory("Category_DockingNotification"), LocalizedDescription("DockPanel_ContentAdded_Description")]
		public event EventHandler<DockContentEventArgs> ContentAdded
		{
			add
			{
				base.Events.AddHandler(DockPanel.ContentAddedEvent, value);
			}
			remove
			{
				base.Events.RemoveHandler(DockPanel.ContentAddedEvent, value);
			}
		}
		[LocalizedCategory("Category_DockingNotification"), LocalizedDescription("DockPanel_ContentRemoved_Description")]
		public event EventHandler<DockContentEventArgs> ContentRemoved
		{
			add
			{
				base.Events.AddHandler(DockPanel.ContentRemovedEvent, value);
			}
			remove
			{
				base.Events.RemoveHandler(DockPanel.ContentRemovedEvent, value);
			}
		}
		[LocalizedCategory("Category_PropertyChanged"), LocalizedDescription("DockPanel_ActiveDocumentChanged_Description")]
		public event EventHandler ActiveDocumentChanged
		{
			add
			{
				base.Events.AddHandler(DockPanel.ActiveDocumentChangedEvent, value);
			}
			remove
			{
				base.Events.RemoveHandler(DockPanel.ActiveDocumentChangedEvent, value);
			}
		}
		[LocalizedCategory("Category_PropertyChanged"), LocalizedDescription("DockPanel_ActiveContentChanged_Description")]
		public event EventHandler ActiveContentChanged
		{
			add
			{
				base.Events.AddHandler(DockPanel.ActiveContentChangedEvent, value);
			}
			remove
			{
				base.Events.RemoveHandler(DockPanel.ActiveContentChangedEvent, value);
			}
		}
		[LocalizedCategory("Category_PropertyChanged"), LocalizedDescription("DockPanel_ActivePaneChanged_Description")]
		public event EventHandler ActivePaneChanged
		{
			add
			{
				base.Events.AddHandler(DockPanel.ActivePaneChangedEvent, value);
			}
			remove
			{
				base.Events.RemoveHandler(DockPanel.ActivePaneChangedEvent, value);
			}
		}
		private DockPanel.AutoHideWindowControl AutoHideWindow
		{
			get
			{
				return this.m_autoHideWindow;
			}
		}
		internal Control AutoHideControl
		{
			get
			{
				return this.m_autoHideWindow;
			}
		}
		internal Rectangle AutoHideWindowRectangle
		{
			get
			{
				DockState dockState = this.AutoHideWindow.DockState;
				Rectangle dockArea = this.DockArea;
				Rectangle result;
				if (this.ActiveAutoHideContent == null)
				{
					result = Rectangle.Empty;
				}
				else
				{
					if (base.Parent == null)
					{
						result = Rectangle.Empty;
					}
					else
					{
						Rectangle empty = Rectangle.Empty;
						double num = this.ActiveAutoHideContent.DockHandler.AutoHidePortion;
						if (dockState == DockState.DockLeftAutoHide)
						{
							if (num < 1.0)
							{
								num = (double)dockArea.Width * num;
							}
							checked
							{
								if (num > (double)(dockArea.Width - 24))
								{
									num = (double)(dockArea.Width - 24);
								}
								empty.X = dockArea.X;
								empty.Y = dockArea.Y;
								empty.Width = (int)num;
								empty.Height = dockArea.Height;
							}
						}
						else
						{
							if (dockState == DockState.DockRightAutoHide)
							{
								if (num < 1.0)
								{
									num = (double)dockArea.Width * num;
								}
								checked
								{
									if (num > (double)(dockArea.Width - 24))
									{
										num = (double)(dockArea.Width - 24);
									}
									empty.X = dockArea.X + dockArea.Width - (int)num;
									empty.Y = dockArea.Y;
									empty.Width = (int)num;
									empty.Height = dockArea.Height;
								}
							}
							else
							{
								if (dockState == DockState.DockTopAutoHide)
								{
									if (num < 1.0)
									{
										num = (double)dockArea.Height * num;
									}
									checked
									{
										if (num > (double)(dockArea.Height - 24))
										{
											num = (double)(dockArea.Height - 24);
										}
										empty.X = dockArea.X;
										empty.Y = dockArea.Y;
										empty.Width = dockArea.Width;
										empty.Height = (int)num;
									}
								}
								else
								{
									if (dockState == DockState.DockBottomAutoHide)
									{
										if (num < 1.0)
										{
											num = (double)dockArea.Height * num;
										}
										checked
										{
											if (num > (double)(dockArea.Height - 24))
											{
												num = (double)(dockArea.Height - 24);
											}
											empty.X = dockArea.X;
											empty.Y = dockArea.Y + dockArea.Height - (int)num;
											empty.Width = dockArea.Width;
											empty.Height = (int)num;
										}
									}
								}
							}
						}
						result = empty;
					}
				}
				return result;
			}
		}
		[Description("Determines the color with which the client rectangle will be drawn.\r\nIf this property is used instead of the BackColor it will not have any influence on the borders to the surrounding controls (DockPane).\r\nThe BackColor property changes the borders of surrounding controls (DockPane).\r\nAlternatively both properties may be used (BackColor to draw and define the color of the borders and DockBackColor to define the color of the client rectangle).\r\nFor Backgroundimages: Set your prefered Image, then set the DockBackColor and the BackColor to the same Color (Control).")]
		public Color DockBackColor
		{
			get
			{
				return (!this.m_BackColor.IsEmpty) ? this.m_BackColor : base.BackColor;
			}
			set
			{
				if (this.m_BackColor != value)
				{
					this.m_BackColor = value;
					this.Refresh();
				}
			}
		}
		internal AutoHideStripBase AutoHideStripControl
		{
			get
			{
				if (this.m_autoHideStripControl == null)
				{
					this.m_autoHideStripControl = this.AutoHideStripFactory.CreateAutoHideStrip(this);
					base.Controls.Add(this.m_autoHideStripControl);
				}
				return this.m_autoHideStripControl;
			}
		}
		[Browsable(false)]
		public IDockContent ActiveAutoHideContent
		{
			get
			{
				return this.AutoHideWindow.ActiveContent;
			}
			set
			{
				this.AutoHideWindow.ActiveContent = value;
			}
		}
		[DefaultValue(true), LocalizedCategory("Category_Docking"), LocalizedDescription("DockPanel_AllowEndUserDocking_Description")]
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
		[DefaultValue(true), LocalizedCategory("Category_Docking"), LocalizedDescription("DockPanel_AllowEndUserNestedDocking_Description")]
		public bool AllowEndUserNestedDocking
		{
			get
			{
				return this.m_allowEndUserNestedDocking;
			}
			set
			{
				this.m_allowEndUserNestedDocking = value;
			}
		}
		[Browsable(false)]
		public DockContentCollection Contents
		{
			get
			{
				return this.m_contents;
			}
		}
		internal DockContent DummyContent
		{
			get
			{
				return this.m_dummyContent;
			}
		}
		[DefaultValue(false), LocalizedCategory("Appearance"), LocalizedDescription("DockPanel_RightToLeftLayout_Description")]
		public bool RightToLeftLayout
		{
			get
			{
				return this.m_rightToLeftLayout;
			}
			set
			{
				if (this.m_rightToLeftLayout != value)
				{
					this.m_rightToLeftLayout = value;
					foreach (FloatWindow current in this.FloatWindows)
					{
						current.RightToLeftLayout = value;
					}
				}
			}
		}
		[DefaultValue(false), LocalizedCategory("Category_Docking"), LocalizedDescription("DockPanel_ShowDocumentIcon_Description")]
		public bool ShowDocumentIcon
		{
			get
			{
				return this.m_showDocumentIcon;
			}
			set
			{
				if (this.m_showDocumentIcon != value)
				{
					this.m_showDocumentIcon = value;
					this.Refresh();
				}
			}
		}
		[LocalizedCategory("Category_Docking"), LocalizedDescription("DockPanel_DockPanelSkin")]
		public DockPanelSkin Skin
		{
			get
			{
				return this.m_dockPanelSkin;
			}
			set
			{
				this.m_dockPanelSkin = value;
			}
		}
		[DefaultValue(DocumentTabStripLocation.Top), LocalizedCategory("Category_Docking"), LocalizedDescription("DockPanel_DocumentTabStripLocation")]
		public DocumentTabStripLocation DocumentTabStripLocation
		{
			get
			{
				return this.m_documentTabStripLocation;
			}
			set
			{
				this.m_documentTabStripLocation = value;
			}
		}
		[Browsable(false)]
		public DockPanelExtender Extender
		{
			get
			{
				return this.m_extender;
			}
		}
		[Browsable(false)]
		public DockPanelExtender.IDockPaneFactory DockPaneFactory
		{
			get
			{
				return this.Extender.DockPaneFactory;
			}
		}
		[Browsable(false)]
		public DockPanelExtender.IFloatWindowFactory FloatWindowFactory
		{
			get
			{
				return this.Extender.FloatWindowFactory;
			}
		}
		internal DockPanelExtender.IDockPaneCaptionFactory DockPaneCaptionFactory
		{
			get
			{
				return this.Extender.DockPaneCaptionFactory;
			}
		}
		internal DockPanelExtender.IDockPaneStripFactory DockPaneStripFactory
		{
			get
			{
				return this.Extender.DockPaneStripFactory;
			}
		}
		internal DockPanelExtender.IAutoHideStripFactory AutoHideStripFactory
		{
			get
			{
				return this.Extender.AutoHideStripFactory;
			}
		}
		[Browsable(false)]
		public DockPaneCollection Panes
		{
			get
			{
				return this.m_panes;
			}
		}
		internal Rectangle DockArea
		{
			get
			{
				return checked(new Rectangle(base.DockPadding.Left, base.DockPadding.Top, base.ClientRectangle.Width - base.DockPadding.Left - base.DockPadding.Right, base.ClientRectangle.Height - base.DockPadding.Top - base.DockPadding.Bottom));
			}
		}
		[DefaultValue(0.25), LocalizedCategory("Category_Docking"), LocalizedDescription("DockPanel_DockBottomPortion_Description")]
		public double DockBottomPortion
		{
			get
			{
				return this.m_dockBottomPortion;
			}
			set
			{
				if (value <= 0.0)
				{
					throw new ArgumentOutOfRangeException("value");
				}
				if (value != this.m_dockBottomPortion)
				{
					this.m_dockBottomPortion = value;
					if (this.m_dockBottomPortion < 1.0 && this.m_dockTopPortion < 1.0)
					{
						if (this.m_dockTopPortion + this.m_dockBottomPortion > 1.0)
						{
							this.m_dockTopPortion = 1.0 - this.m_dockBottomPortion;
						}
					}
					base.PerformLayout();
				}
			}
		}
		[DefaultValue(0.25), LocalizedCategory("Category_Docking"), LocalizedDescription("DockPanel_DockLeftPortion_Description")]
		public double DockLeftPortion
		{
			get
			{
				return this.m_dockLeftPortion;
			}
			set
			{
				if (value <= 0.0)
				{
					throw new ArgumentOutOfRangeException("value");
				}
				if (value != this.m_dockLeftPortion)
				{
					this.m_dockLeftPortion = value;
					if (this.m_dockLeftPortion < 1.0 && this.m_dockRightPortion < 1.0)
					{
						if (this.m_dockLeftPortion + this.m_dockRightPortion > 1.0)
						{
							this.m_dockRightPortion = 1.0 - this.m_dockLeftPortion;
						}
					}
					base.PerformLayout();
				}
			}
		}
		[DefaultValue(0.25), LocalizedCategory("Category_Docking"), LocalizedDescription("DockPanel_DockRightPortion_Description")]
		public double DockRightPortion
		{
			get
			{
				return this.m_dockRightPortion;
			}
			set
			{
				if (value <= 0.0)
				{
					throw new ArgumentOutOfRangeException("value");
				}
				if (value != this.m_dockRightPortion)
				{
					this.m_dockRightPortion = value;
					if (this.m_dockLeftPortion < 1.0 && this.m_dockRightPortion < 1.0)
					{
						if (this.m_dockLeftPortion + this.m_dockRightPortion > 1.0)
						{
							this.m_dockLeftPortion = 1.0 - this.m_dockRightPortion;
						}
					}
					base.PerformLayout();
				}
			}
		}
		[DefaultValue(0.25), LocalizedCategory("Category_Docking"), LocalizedDescription("DockPanel_DockTopPortion_Description")]
		public double DockTopPortion
		{
			get
			{
				return this.m_dockTopPortion;
			}
			set
			{
				if (value <= 0.0)
				{
					throw new ArgumentOutOfRangeException("value");
				}
				if (value != this.m_dockTopPortion)
				{
					this.m_dockTopPortion = value;
					if (this.m_dockTopPortion < 1.0 && this.m_dockBottomPortion < 1.0)
					{
						if (this.m_dockTopPortion + this.m_dockBottomPortion > 1.0)
						{
							this.m_dockBottomPortion = 1.0 - this.m_dockTopPortion;
						}
					}
					base.PerformLayout();
				}
			}
		}
		[Browsable(false)]
		public DockWindowCollection DockWindows
		{
			get
			{
				return this.m_dockWindows;
			}
		}
		[Browsable(false)]
		public int DocumentsCount
		{
			get
			{
				int num = 0;
				checked
				{
					foreach (IDockContent current in this.Documents)
					{
						num++;
					}
					return num;
				}
			}
		}
		[Browsable(false)]
		public IEnumerable<IDockContent> Documents
		{
			get
			{
				foreach (IDockContent current in this.Contents)
				{
					if (current.DockHandler.DockState == DockState.Document)
					{
						yield return current;
					}
				}
				yield break;
			}
		}
		private Rectangle DocumentRectangle
		{
			get
			{
				Rectangle dockArea = this.DockArea;
				checked
				{
					if (this.DockWindows[DockState.DockLeft].VisibleNestedPanes.Count != 0)
					{
						dockArea.X += (int)unchecked((double)this.DockArea.Width * this.DockLeftPortion);
						dockArea.Width -= (int)unchecked((double)this.DockArea.Width * this.DockLeftPortion);
					}
					if (this.DockWindows[DockState.DockRight].VisibleNestedPanes.Count != 0)
					{
						dockArea.Width -= (int)unchecked((double)this.DockArea.Width * this.DockRightPortion);
					}
					if (this.DockWindows[DockState.DockTop].VisibleNestedPanes.Count != 0)
					{
						dockArea.Y += (int)unchecked((double)this.DockArea.Height * this.DockTopPortion);
						dockArea.Height -= (int)unchecked((double)this.DockArea.Height * this.DockTopPortion);
					}
					if (this.DockWindows[DockState.DockBottom].VisibleNestedPanes.Count != 0)
					{
						dockArea.Height -= (int)unchecked((double)this.DockArea.Height * this.DockBottomPortion);
					}
					return dockArea;
				}
			}
		}
		private Control DummyControl
		{
			get
			{
				return this.m_dummyControl;
			}
		}
		[Browsable(false)]
		public FloatWindowCollection FloatWindows
		{
			get
			{
				return this.m_floatWindows;
			}
		}
		[Category("Layout"), LocalizedDescription("DockPanel_DefaultFloatWindowSize_Description")]
		public Size DefaultFloatWindowSize
		{
			get
			{
				return this.m_defaultFloatWindowSize;
			}
			set
			{
				this.m_defaultFloatWindowSize = value;
			}
		}
		[DefaultValue(DocumentStyle.DockingMdi), LocalizedCategory("Category_Docking"), LocalizedDescription("DockPanel_DocumentStyle_Description")]
		public DocumentStyle DocumentStyle
		{
			get
			{
				return this.m_documentStyle;
			}
			set
			{
				if (value != this.m_documentStyle)
				{
					if (!Enum.IsDefined(typeof(DocumentStyle), value))
					{
						throw new InvalidEnumArgumentException();
					}
					if (value == DocumentStyle.SystemMdi && this.DockWindows[DockState.Document].VisibleNestedPanes.Count > 0)
					{
						throw new InvalidEnumArgumentException();
					}
					this.m_documentStyle = value;
					this.SuspendLayout(true);
					this.SetAutoHideWindowParent();
					this.SetMdiClient();
					this.InvalidateWindowRegion();
					foreach (IDockContent current in this.Contents)
					{
						if (current.DockHandler.DockState == DockState.Document)
						{
							current.DockHandler.SetPaneAndVisible(current.DockHandler.Pane);
						}
					}
					this.PerformMdiClientLayout();
					this.ResumeLayout(true, true);
				}
			}
		}
		internal Form ParentForm
		{
			get
			{
				if (!this.IsParentFormValid())
				{
					throw new InvalidOperationException(Strings.DockPanel_ParentForm_Invalid);
				}
				return this.GetMdiClientController().ParentForm;
			}
		}
		private Rectangle SystemMdiClientBounds
		{
			get
			{
				Rectangle result;
				if (!this.IsParentFormValid() || !base.Visible)
				{
					result = Rectangle.Empty;
				}
				else
				{
					Rectangle rectangle = this.ParentForm.RectangleToClient(base.RectangleToScreen(this.DocumentWindowBounds));
					result = rectangle;
				}
				return result;
			}
		}
		internal Rectangle DocumentWindowBounds
		{
			get
			{
				Rectangle displayRectangle = this.DisplayRectangle;
				checked
				{
					if (this.DockWindows[DockState.DockLeft].Visible)
					{
						displayRectangle.X += this.DockWindows[DockState.DockLeft].Width;
						displayRectangle.Width -= this.DockWindows[DockState.DockLeft].Width;
					}
					if (this.DockWindows[DockState.DockRight].Visible)
					{
						displayRectangle.Width -= this.DockWindows[DockState.DockRight].Width;
					}
					if (this.DockWindows[DockState.DockTop].Visible)
					{
						displayRectangle.Y += this.DockWindows[DockState.DockTop].Height;
						displayRectangle.Height -= this.DockWindows[DockState.DockTop].Height;
					}
					if (this.DockWindows[DockState.DockBottom].Visible)
					{
						displayRectangle.Height -= this.DockWindows[DockState.DockBottom].Height;
					}
					return displayRectangle;
				}
			}
		}
		private DockPanel.IFocusManager FocusManager
		{
			get
			{
				return this.m_focusManager;
			}
		}
		internal IContentFocusManager ContentFocusManager
		{
			get
			{
				return this.m_focusManager;
			}
		}
		[Browsable(false)]
		public IDockContent ActiveContent
		{
			get
			{
				return this.FocusManager.ActiveContent;
			}
		}
		[Browsable(false)]
		public DockPane ActivePane
		{
			get
			{
				return this.FocusManager.ActivePane;
			}
		}
		[Browsable(false)]
		public IDockContent ActiveDocument
		{
			get
			{
				return this.FocusManager.ActiveDocument;
			}
		}
		[Browsable(false)]
		public DockPane ActiveDocumentPane
		{
			get
			{
				return this.FocusManager.ActiveDocumentPane;
			}
		}
		private bool MdiClientExists
		{
			get
			{
				return this.GetMdiClientController().MdiClient != null;
			}
		}
		internal void RefreshActiveAutoHideContent()
		{
			this.AutoHideWindow.RefreshActiveContent();
		}
		internal Rectangle GetAutoHideWindowBounds(Rectangle rectAutoHideWindow)
		{
			Rectangle result;
			if (this.DocumentStyle == DocumentStyle.SystemMdi || this.DocumentStyle == DocumentStyle.DockingMdi)
			{
				result = ((base.Parent == null) ? Rectangle.Empty : base.Parent.RectangleToClient(base.RectangleToScreen(rectAutoHideWindow)));
			}
			else
			{
				result = rectAutoHideWindow;
			}
			return result;
		}
		internal void RefreshAutoHideStrip()
		{
			this.AutoHideStripControl.RefreshChanges();
		}
		public DockPanel()
		{
			this.m_focusManager = new DockPanel.FocusManagerImpl(this);
			this.m_extender = new DockPanelExtender(this);
			this.m_panes = new DockPaneCollection();
			this.m_floatWindows = new FloatWindowCollection();
			base.SuspendLayout();
			this.m_autoHideWindow = new DockPanel.AutoHideWindowControl(this);
			this.m_autoHideWindow.Visible = false;
			this.SetAutoHideWindowParent();
			this.m_dummyControl = new DummyControl();
			this.m_dummyControl.Bounds = new Rectangle(0, 0, 1, 1);
			base.Controls.Add(this.m_dummyControl);
			this.m_dockWindows = new DockWindowCollection(this);
			base.Controls.AddRange(new Control[]
			{
				this.DockWindows[DockState.Document],
				this.DockWindows[DockState.DockLeft],
				this.DockWindows[DockState.DockRight],
				this.DockWindows[DockState.DockTop],
				this.DockWindows[DockState.DockBottom]
			});
			this.m_dummyContent = new DockContent();
			base.ResumeLayout();
		}
		public void ApplayTheme(string theme)
		{
			string text = theme.ToUpper();
			if (text != null)
			{
				if (text == "CUSTOM")
				{
					this.BackColor = Color.FromArgb(215, 223, 231);
					this.DockBackColor = Color.FromArgb(215, 223, 231);
					DockingHelper.ThemeDocumentTabActiveBorder = Color.FromArgb(172, 201, 237);
					DockingHelper.ThemeDocumentTabInactiveBorder = Color.FromArgb(215, 223, 231);
					DockingHelper.ThemeToolWindowTabBorder = Color.FromArgb(215, 223, 231);
					DockingHelper.HideDocumentWindowBorder = true;
					DockingHelper.UseLightDockStripImages = false;
					this.Skin.AutoHideStripSkin.DockStripGradient.StartColor = Color.FromArgb(215, 223, 231);
					this.Skin.AutoHideStripSkin.DockStripGradient.EndColor = Color.FromArgb(215, 223, 231);
					this.Skin.AutoHideStripSkin.DockStripGradient.LinearGradientMode = LinearGradientMode.Vertical;
					this.Skin.AutoHideStripSkin.TabGradient.EndColor = SystemColors.Control;
					this.Skin.AutoHideStripSkin.TabGradient.StartColor = SystemColors.Control;
					this.Skin.AutoHideStripSkin.TabGradient.TextColor = SystemColors.ControlDarkDark;
					this.Skin.DockPaneStripSkin.DocumentGradient.DockStripGradient.StartColor = Color.FromArgb(239, 237, 226);
					this.Skin.DockPaneStripSkin.DocumentGradient.DockStripGradient.EndColor = Color.FromArgb(239, 237, 226);
					this.Skin.DockPaneStripSkin.DocumentGradient.DockStripGradient.LinearGradientMode = LinearGradientMode.Vertical;
					this.Skin.DockPaneStripSkin.DocumentGradient.ActiveTabGradient.StartColor = Color.FromArgb(243, 246, 251);
					this.Skin.DockPaneStripSkin.DocumentGradient.ActiveTabGradient.EndColor = Color.FromArgb(193, 210, 238);
					this.Skin.DockPaneStripSkin.DocumentGradient.ActiveTabGradient.LinearGradientMode = LinearGradientMode.Vertical;
					this.Skin.DockPaneStripSkin.DocumentGradient.InactiveTabGradient.StartColor = Color.FromArgb(252, 252, 252);
					this.Skin.DockPaneStripSkin.DocumentGradient.InactiveTabGradient.EndColor = Color.FromArgb(232, 232, 232);
					this.Skin.DockPaneStripSkin.DocumentGradient.InactiveTabGradient.LinearGradientMode = LinearGradientMode.Vertical;
					this.Skin.DockPaneStripSkin.DocumentGradient.InactiveTabGradient.TextColor = Color.Black;
					this.Skin.DockPaneStripSkin.ToolWindowGradient.DockStripGradient.StartColor = Color.FromArgb(239, 237, 226);
					this.Skin.DockPaneStripSkin.ToolWindowGradient.DockStripGradient.EndColor = Color.FromArgb(239, 237, 226);
					this.Skin.DockPaneStripSkin.ToolWindowGradient.ActiveTabGradient.StartColor = Color.FromArgb(162, 191, 227);
					this.Skin.DockPaneStripSkin.ToolWindowGradient.ActiveTabGradient.EndColor = Color.FromArgb(193, 210, 238);
					this.Skin.DockPaneStripSkin.ToolWindowGradient.InactiveTabGradient.StartColor = Color.Transparent;
					this.Skin.DockPaneStripSkin.ToolWindowGradient.InactiveTabGradient.EndColor = Color.Transparent;
					this.Skin.DockPaneStripSkin.ToolWindowGradient.InactiveTabGradient.TextColor = SystemColors.ControlDarkDark;
					this.Skin.DockPaneStripSkin.ToolWindowGradient.ActiveCaptionGradient.StartColor = Color.FromArgb(162, 191, 227);
					this.Skin.DockPaneStripSkin.ToolWindowGradient.ActiveCaptionGradient.EndColor = Color.FromArgb(193, 210, 238);
					this.Skin.DockPaneStripSkin.ToolWindowGradient.ActiveCaptionGradient.LinearGradientMode = LinearGradientMode.Vertical;
					this.Skin.DockPaneStripSkin.ToolWindowGradient.ActiveCaptionGradient.TextColor = Color.Black;
					this.Skin.DockPaneStripSkin.ToolWindowGradient.InactiveCaptionGradient.StartColor = Color.FromArgb(193, 210, 238);
					this.Skin.DockPaneStripSkin.ToolWindowGradient.InactiveCaptionGradient.EndColor = Color.FromArgb(215, 223, 231);
					this.Skin.DockPaneStripSkin.ToolWindowGradient.InactiveCaptionGradient.LinearGradientMode = LinearGradientMode.Vertical;
					this.Skin.DockPaneStripSkin.ToolWindowGradient.InactiveCaptionGradient.TextColor = Color.FromArgb(43, 43, 43);
					return;
				}
				if (!(text == "VS2010"))
				{
				}
			}
			this.BackColor = Color.FromArgb(41, 57, 85);
			this.DockBackColor = Color.FromArgb(41, 57, 85);
			this.BackgroundImage = Resources.VS2010ThemeBackground;
			this.BackgroundImageLayout = ImageLayout.Tile;
			DockingHelper.ThemeDocumentTabActiveBorder = Color.FromArgb(255, 231, 165);
			DockingHelper.ThemeDocumentTabInactiveBorder = Color.FromArgb(41, 57, 85);
			DockingHelper.ThemeToolWindowTabBorder = Color.FromArgb(41, 57, 85);
			DockingHelper.HideDocumentWindowBorder = true;
			DockingHelper.UseLightDockStripImages = true;
			this.Skin.AutoHideStripSkin.DockStripGradient.StartColor = Color.FromArgb(41, 57, 85);
			this.Skin.AutoHideStripSkin.DockStripGradient.EndColor = Color.FromArgb(41, 57, 85);
			this.Skin.AutoHideStripSkin.TabGradient.StartColor = Color.FromArgb(61, 82, 119);
			this.Skin.AutoHideStripSkin.TabGradient.EndColor = Color.FromArgb(61, 82, 119);
			this.Skin.AutoHideStripSkin.TabGradient.TextColor = Color.White;
			this.Skin.DockPaneStripSkin.DocumentGradient.DockStripGradient.StartColor = Color.FromArgb(41, 57, 85);
			this.Skin.DockPaneStripSkin.DocumentGradient.DockStripGradient.EndColor = Color.FromArgb(41, 57, 85);
			this.Skin.DockPaneStripSkin.DocumentGradient.ActiveTabGradient.StartColor = Color.White;
			this.Skin.DockPaneStripSkin.DocumentGradient.ActiveTabGradient.EndColor = Color.FromArgb(255, 231, 165);
			this.Skin.DockPaneStripSkin.DocumentGradient.ActiveTabGradient.LinearGradientMode = LinearGradientMode.Vertical;
			this.Skin.DockPaneStripSkin.DocumentGradient.ActiveTabGradient.TextColor = Color.Black;
			this.Skin.DockPaneStripSkin.DocumentGradient.InactiveTabGradient.StartColor = Color.FromArgb(41, 57, 85);
			this.Skin.DockPaneStripSkin.DocumentGradient.InactiveTabGradient.EndColor = Color.FromArgb(41, 57, 85);
			this.Skin.DockPaneStripSkin.DocumentGradient.InactiveTabGradient.TextColor = Color.White;
			this.Skin.DockPaneStripSkin.DocumentGradient.InactiveTabGradient.LinearGradientMode = LinearGradientMode.Vertical;
			this.Skin.DockPaneStripSkin.ToolWindowGradient.DockStripGradient.StartColor = Color.FromArgb(41, 57, 85);
			this.Skin.DockPaneStripSkin.ToolWindowGradient.DockStripGradient.EndColor = Color.FromArgb(41, 57, 85);
			this.Skin.DockPaneStripSkin.ToolWindowGradient.ActiveCaptionGradient.StartColor = Color.White;
			this.Skin.DockPaneStripSkin.ToolWindowGradient.ActiveCaptionGradient.EndColor = Color.FromArgb(255, 231, 165);
			this.Skin.DockPaneStripSkin.ToolWindowGradient.ActiveCaptionGradient.LinearGradientMode = LinearGradientMode.Vertical;
			this.Skin.DockPaneStripSkin.ToolWindowGradient.InactiveCaptionGradient.StartColor = Color.FromArgb(75, 94, 129);
			this.Skin.DockPaneStripSkin.ToolWindowGradient.InactiveCaptionGradient.EndColor = Color.FromArgb(62, 83, 120);
			this.Skin.DockPaneStripSkin.ToolWindowGradient.InactiveCaptionGradient.LinearGradientMode = LinearGradientMode.Vertical;
			this.Skin.DockPaneStripSkin.ToolWindowGradient.InactiveCaptionGradient.TextColor = Color.White;
			this.Skin.DockPaneStripSkin.ToolWindowGradient.ActiveTabGradient.StartColor = Color.White;
			this.Skin.DockPaneStripSkin.ToolWindowGradient.ActiveTabGradient.EndColor = Color.FromArgb(255, 231, 165);
			this.Skin.DockPaneStripSkin.ToolWindowGradient.ActiveTabGradient.LinearGradientMode = LinearGradientMode.Vertical;
			this.Skin.DockPaneStripSkin.ToolWindowGradient.InactiveTabGradient.StartColor = Color.FromArgb(41, 57, 85);
			this.Skin.DockPaneStripSkin.ToolWindowGradient.InactiveTabGradient.EndColor = Color.FromArgb(41, 57, 85);
			this.Skin.DockPaneStripSkin.ToolWindowGradient.InactiveTabGradient.TextColor = Color.White;
		}
		internal void ResetAutoHideStripControl()
		{
			if (this.m_autoHideStripControl != null)
			{
				this.m_autoHideStripControl.Dispose();
			}
			this.m_autoHideStripControl = null;
		}
		private void MdiClientHandleAssigned(object sender, EventArgs e)
		{
			this.SetMdiClient();
			base.PerformLayout();
		}
		private void MdiClient_Layout(object sender, LayoutEventArgs e)
		{
			if (this.DocumentStyle == DocumentStyle.DockingMdi)
			{
				foreach (DockPane current in this.Panes)
				{
					if (current.DockState == DockState.Document)
					{
						current.SetContentBounds();
					}
				}
				this.InvalidateWindowRegion();
			}
		}
		protected override void Dispose(bool disposing)
		{
			bool flag = false;
			try
			{
				Monitor.Enter(this, ref flag);
				if (!this.m_disposed && disposing)
				{
					this.m_focusManager.Dispose();
					if (this.m_mdiClientController != null)
					{
						this.m_mdiClientController.HandleAssigned -= new EventHandler(this.MdiClientHandleAssigned);
						this.m_mdiClientController.MdiChildActivate -= new EventHandler(this.ParentFormMdiChildActivate);
						this.m_mdiClientController.Layout -= new LayoutEventHandler(this.MdiClient_Layout);
						this.m_mdiClientController.Dispose();
					}
					this.FloatWindows.Dispose();
					this.Panes.Dispose();
					this.DummyContent.Dispose();
					this.m_disposed = true;
				}
				base.Dispose(disposing);
			}
			finally
			{
				if (flag)
				{
					Monitor.Exit(this);
				}
			}
		}
		protected override void OnRightToLeftChanged(EventArgs e)
		{
			base.OnRightToLeftChanged(e);
			foreach (FloatWindow current in this.FloatWindows)
			{
				if (current.RightToLeft != this.RightToLeft)
				{
					current.RightToLeft = this.RightToLeft;
				}
			}
		}
		public void UpdateDockWindowZOrder(DockStyle dockStyle, bool fullPanelEdge)
		{
			if (dockStyle == DockStyle.Left)
			{
				if (fullPanelEdge)
				{
					this.DockWindows[DockState.DockLeft].SendToBack();
				}
				else
				{
					this.DockWindows[DockState.DockLeft].BringToFront();
				}
			}
			else
			{
				if (dockStyle == DockStyle.Right)
				{
					if (fullPanelEdge)
					{
						this.DockWindows[DockState.DockRight].SendToBack();
					}
					else
					{
						this.DockWindows[DockState.DockRight].BringToFront();
					}
				}
				else
				{
					if (dockStyle == DockStyle.Top)
					{
						if (fullPanelEdge)
						{
							this.DockWindows[DockState.DockTop].SendToBack();
						}
						else
						{
							this.DockWindows[DockState.DockTop].BringToFront();
						}
					}
					else
					{
						if (dockStyle == DockStyle.Bottom)
						{
							if (fullPanelEdge)
							{
								this.DockWindows[DockState.DockBottom].SendToBack();
							}
							else
							{
								this.DockWindows[DockState.DockBottom].BringToFront();
							}
						}
					}
				}
			}
		}
		public IDockContent[] DocumentsToArray()
		{
			int documentsCount = this.DocumentsCount;
			IDockContent[] array = new IDockContent[documentsCount];
			int num = 0;
			checked
			{
				foreach (IDockContent current in this.Documents)
				{
					array[num] = current;
					num++;
				}
				return array;
			}
		}
		private bool ShouldSerializeDefaultFloatWindowSize()
		{
			return this.DefaultFloatWindowSize != new Size(300, 300);
		}
		private int GetDockWindowSize(DockState dockState)
		{
			checked
			{
				int result;
				if (dockState == DockState.DockLeft || dockState == DockState.DockRight)
				{
					int num = base.ClientRectangle.Width - base.DockPadding.Left - base.DockPadding.Right;
					int num2 = (this.m_dockLeftPortion >= 1.0) ? ((int)this.m_dockLeftPortion) : ((int)unchecked((double)num * this.m_dockLeftPortion));
					int num3 = (this.m_dockRightPortion >= 1.0) ? ((int)this.m_dockRightPortion) : ((int)unchecked((double)num * this.m_dockRightPortion));
					if (num2 < 24)
					{
						num2 = 24;
					}
					if (num3 < 24)
					{
						num3 = 24;
					}
					if (num2 + num3 > num - 24)
					{
						int num4 = num2 + num3 - (num - 24);
						num2 -= num4 / 2;
						num3 -= num4 / 2;
					}
					result = ((dockState == DockState.DockLeft) ? num2 : num3);
				}
				else
				{
					if (dockState == DockState.DockTop || dockState == DockState.DockBottom)
					{
						int num5 = base.ClientRectangle.Height - base.DockPadding.Top - base.DockPadding.Bottom;
						int num6 = (this.m_dockTopPortion >= 1.0) ? ((int)this.m_dockTopPortion) : ((int)unchecked((double)num5 * this.m_dockTopPortion));
						int num7 = (this.m_dockBottomPortion >= 1.0) ? ((int)this.m_dockBottomPortion) : ((int)unchecked((double)num5 * this.m_dockBottomPortion));
						if (num6 < 24)
						{
							num6 = 24;
						}
						if (num7 < 24)
						{
							num7 = 24;
						}
						if (num6 + num7 > num5 - 24)
						{
							int num4 = num6 + num7 - (num5 - 24);
							num6 -= num4 / 2;
							num7 -= num4 / 2;
						}
						result = ((dockState == DockState.DockTop) ? num6 : num7);
					}
					else
					{
						result = 0;
					}
				}
				return result;
			}
		}
		protected override void OnLayout(LayoutEventArgs levent)
		{
			this.SuspendLayout(true);
			this.AutoHideStripControl.Bounds = base.ClientRectangle;
			this.CalculateDockPadding();
			this.DockWindows[DockState.DockLeft].Width = this.GetDockWindowSize(DockState.DockLeft);
			this.DockWindows[DockState.DockRight].Width = this.GetDockWindowSize(DockState.DockRight);
			this.DockWindows[DockState.DockTop].Height = this.GetDockWindowSize(DockState.DockTop);
			this.DockWindows[DockState.DockBottom].Height = this.GetDockWindowSize(DockState.DockBottom);
			this.AutoHideWindow.Bounds = this.GetAutoHideWindowBounds(this.AutoHideWindowRectangle);
			this.DockWindows[DockState.Document].BringToFront();
			this.AutoHideWindow.BringToFront();
			base.OnLayout(levent);
			if (this.DocumentStyle == DocumentStyle.SystemMdi && this.MdiClientExists)
			{
				this.SetMdiClientBounds(this.SystemMdiClientBounds);
				this.InvalidateWindowRegion();
			}
			else
			{
				if (this.DocumentStyle == DocumentStyle.DockingMdi)
				{
					this.InvalidateWindowRegion();
				}
			}
			this.ResumeLayout(true, true);
		}
		internal Rectangle GetTabStripRectangle(DockState dockState)
		{
			return this.AutoHideStripControl.GetTabStripRectangle(dockState);
		}
		protected override void OnPaint(PaintEventArgs e)
		{
			base.OnPaint(e);
			if (!(this.DockBackColor == this.BackColor))
			{
				Graphics graphics = e.Graphics;
				SolidBrush brush = new SolidBrush(this.DockBackColor);
				graphics.FillRectangle(brush, base.ClientRectangle);
			}
		}
		internal void AddContent(IDockContent content)
		{
			if (content == null)
			{
				throw new ArgumentNullException();
			}
			if (!this.Contents.Contains(content))
			{
				this.Contents.Add(content);
				this.OnContentAdded(new DockContentEventArgs(content));
			}
		}
		internal void AddPane(DockPane pane)
		{
			if (!this.Panes.Contains(pane))
			{
				this.Panes.Add(pane);
			}
		}
		internal void AddFloatWindow(FloatWindow floatWindow)
		{
			if (!this.FloatWindows.Contains(floatWindow))
			{
				this.FloatWindows.Add(floatWindow);
			}
		}
		private void CalculateDockPadding()
		{
			base.DockPadding.All = 0;
			int num = this.AutoHideStripControl.MeasureHeight();
			if (this.AutoHideStripControl.GetNumberOfPanes(DockState.DockLeftAutoHide) > 0)
			{
				base.DockPadding.Left = num;
			}
			if (this.AutoHideStripControl.GetNumberOfPanes(DockState.DockRightAutoHide) > 0)
			{
				base.DockPadding.Right = num;
			}
			if (this.AutoHideStripControl.GetNumberOfPanes(DockState.DockTopAutoHide) > 0)
			{
				base.DockPadding.Top = num;
			}
			if (this.AutoHideStripControl.GetNumberOfPanes(DockState.DockBottomAutoHide) > 0)
			{
				base.DockPadding.Bottom = num;
			}
		}
		internal void RemoveContent(IDockContent content)
		{
			if (content == null)
			{
				throw new ArgumentNullException();
			}
			if (this.Contents.Contains(content))
			{
				this.Contents.Remove(content);
				this.OnContentRemoved(new DockContentEventArgs(content));
			}
		}
		internal void RemovePane(DockPane pane)
		{
			if (this.Panes.Contains(pane))
			{
				this.Panes.Remove(pane);
			}
		}
		internal void RemoveFloatWindow(FloatWindow floatWindow)
		{
			if (this.FloatWindows.Contains(floatWindow))
			{
				this.FloatWindows.Remove(floatWindow);
			}
		}
		public void SetPaneIndex(DockPane pane, int index)
		{
			int num = this.Panes.IndexOf(pane);
			if (num == -1)
			{
				throw new ArgumentException(Strings.DockPanel_SetPaneIndex_InvalidPane);
			}
			checked
			{
				if ((index < 0 || index > this.Panes.Count - 1) && index != -1)
				{
					throw new ArgumentOutOfRangeException(Strings.DockPanel_SetPaneIndex_InvalidIndex);
				}
				if (num != index)
				{
					if (num != this.Panes.Count - 1 || index != -1)
					{
						this.Panes.Remove(pane);
						if (index == -1)
						{
							this.Panes.Add(pane);
						}
						else
						{
							if (num < index)
							{
								this.Panes.AddAt(pane, index - 1);
							}
							else
							{
								this.Panes.AddAt(pane, index);
							}
						}
					}
				}
			}
		}
		public void SuspendLayout(bool allWindows)
		{
			this.FocusManager.SuspendFocusTracking();
			base.SuspendLayout();
			if (allWindows)
			{
				this.SuspendMdiClientLayout();
			}
		}
		public void ResumeLayout(bool performLayout, bool allWindows)
		{
			this.FocusManager.ResumeFocusTracking();
			base.ResumeLayout(performLayout);
			if (allWindows)
			{
				this.ResumeMdiClientLayout(performLayout);
			}
		}
		private bool IsParentFormValid()
		{
			bool result;
			if (this.DocumentStyle == DocumentStyle.DockingSdi || this.DocumentStyle == DocumentStyle.DockingWindow)
			{
				result = true;
			}
			else
			{
				if (!this.MdiClientExists)
				{
					this.GetMdiClientController().RenewMdiClient();
				}
				result = this.MdiClientExists;
			}
			return result;
		}
		protected override void OnParentChanged(EventArgs e)
		{
			this.SetAutoHideWindowParent();
			this.GetMdiClientController().ParentForm = (base.Parent as Form);
			base.OnParentChanged(e);
		}
		private void SetAutoHideWindowParent()
		{
			Control control;
			if (this.DocumentStyle == DocumentStyle.DockingMdi || this.DocumentStyle == DocumentStyle.SystemMdi)
			{
				control = base.Parent;
			}
			else
			{
				control = this;
			}
			if (this.AutoHideWindow.Parent != control)
			{
				this.AutoHideWindow.Parent = control;
				this.AutoHideWindow.BringToFront();
			}
		}
		protected override void OnVisibleChanged(EventArgs e)
		{
			base.OnVisibleChanged(e);
			if (base.Visible)
			{
				this.SetMdiClient();
			}
		}
		private void InvalidateWindowRegion()
		{
			if (!base.DesignMode)
			{
				if (this.m_dummyControlPaintEventHandler == null)
				{
					this.m_dummyControlPaintEventHandler = new PaintEventHandler(this.DummyControl_Paint);
				}
				this.DummyControl.Paint += this.m_dummyControlPaintEventHandler;
				this.DummyControl.Invalidate();
			}
		}
		private void DummyControl_Paint(object sender, PaintEventArgs e)
		{
			this.DummyControl.Paint -= this.m_dummyControlPaintEventHandler;
			this.UpdateWindowRegion();
		}
		private void UpdateWindowRegion()
		{
			if (this.DocumentStyle == DocumentStyle.DockingMdi)
			{
				this.UpdateWindowRegion_ClipContent();
			}
			else
			{
				if (this.DocumentStyle == DocumentStyle.DockingSdi || this.DocumentStyle == DocumentStyle.DockingWindow)
				{
					this.UpdateWindowRegion_FullDocumentArea();
				}
				else
				{
					if (this.DocumentStyle == DocumentStyle.SystemMdi)
					{
						this.UpdateWindowRegion_EmptyDocumentArea();
					}
				}
			}
		}
		private void UpdateWindowRegion_FullDocumentArea()
		{
			this.SetRegion(null);
		}
		private void UpdateWindowRegion_EmptyDocumentArea()
		{
			Rectangle documentWindowBounds = this.DocumentWindowBounds;
			this.SetRegion(new Rectangle[]
			{
				documentWindowBounds
			});
		}
		private void UpdateWindowRegion_ClipContent()
		{
			int num = 0;
			checked
			{
				foreach (DockPane current in this.Panes)
				{
					if (current.Visible && current.DockState == DockState.Document)
					{
						num++;
					}
				}
				if (num == 0)
				{
					this.SetRegion(null);
				}
				else
				{
					Rectangle[] array = new Rectangle[num];
					int num2 = 0;
					foreach (DockPane current in this.Panes)
					{
						if (current.Visible && current.DockState == DockState.Document)
						{
							array[num2] = base.RectangleToClient(current.RectangleToScreen(current.ContentRectangle));
							num2++;
						}
					}
					this.SetRegion(array);
				}
			}
		}
		private void SetRegion(Rectangle[] clipRects)
		{
			if (this.IsClipRectsChanged(clipRects))
			{
				this.m_clipRects = clipRects;
				if (this.m_clipRects == null || this.m_clipRects.GetLength(0) == 0)
				{
					base.Region = null;
				}
				else
				{
					Region region = new Region(new Rectangle(0, 0, base.Width, base.Height));
					Rectangle[] clipRects2 = this.m_clipRects;
					for (int i = 0; i < clipRects2.Length; i++)
					{
						Rectangle rect = clipRects2[i];
						region.Exclude(rect);
					}
					base.Region = region;
				}
			}
		}
		private bool IsClipRectsChanged(Rectangle[] clipRects)
		{
			bool result;
			if (clipRects == null && this.m_clipRects == null)
			{
				result = false;
			}
			else
			{
				if (clipRects == null != (this.m_clipRects == null))
				{
					result = true;
				}
				else
				{
					for (int i = 0; i < clipRects.Length; i++)
					{
						Rectangle left = clipRects[i];
						bool flag = false;
						Rectangle[] clipRects2 = this.m_clipRects;
						for (int j = 0; j < clipRects2.Length; j++)
						{
							Rectangle right = clipRects2[j];
							if (left == right)
							{
								flag = true;
								break;
							}
						}
						if (!flag)
						{
							result = true;
							return result;
						}
					}
					Rectangle[] clipRects3 = this.m_clipRects;
					for (int i = 0; i < clipRects3.Length; i++)
					{
						Rectangle right = clipRects3[i];
						bool flag = false;
						for (int j = 0; j < clipRects.Length; j++)
						{
							Rectangle left = clipRects[j];
							if (left == right)
							{
								flag = true;
								break;
							}
						}
						if (!flag)
						{
							result = true;
							return result;
						}
					}
					result = false;
				}
			}
			return result;
		}
		protected virtual void OnContentAdded(DockContentEventArgs e)
		{
			EventHandler<DockContentEventArgs> eventHandler = (EventHandler<DockContentEventArgs>)base.Events[DockPanel.ContentAddedEvent];
			if (eventHandler != null)
			{
				eventHandler(this, e);
			}
		}
		protected virtual void OnContentRemoved(DockContentEventArgs e)
		{
			EventHandler<DockContentEventArgs> eventHandler = (EventHandler<DockContentEventArgs>)base.Events[DockPanel.ContentRemovedEvent];
			if (eventHandler != null)
			{
				eventHandler(this, e);
			}
		}
		private DockPanel.DockDragHandler GetDockDragHandler()
		{
			if (this.m_dockDragHandler == null)
			{
				this.m_dockDragHandler = new DockPanel.DockDragHandler(this);
			}
			return this.m_dockDragHandler;
		}
		internal void BeginDrag(IDockDragSource dragSource)
		{
			this.GetDockDragHandler().BeginDrag(dragSource);
		}
		internal void SaveFocus()
		{
			this.DummyControl.Focus();
		}
		protected virtual void OnActiveDocumentChanged(EventArgs e)
		{
			EventHandler eventHandler = (EventHandler)base.Events[DockPanel.ActiveDocumentChangedEvent];
			if (eventHandler != null)
			{
				eventHandler(this, e);
			}
		}
		protected void OnActiveContentChanged(EventArgs e)
		{
			EventHandler eventHandler = (EventHandler)base.Events[DockPanel.ActiveContentChangedEvent];
			if (eventHandler != null)
			{
				eventHandler(this, e);
			}
		}
		protected virtual void OnActivePaneChanged(EventArgs e)
		{
			EventHandler eventHandler = (EventHandler)base.Events[DockPanel.ActivePaneChangedEvent];
			if (eventHandler != null)
			{
				eventHandler(this, e);
			}
		}
		private DockPanel.MdiClientController GetMdiClientController()
		{
			if (this.m_mdiClientController == null)
			{
				this.m_mdiClientController = new DockPanel.MdiClientController();
				this.m_mdiClientController.HandleAssigned += new EventHandler(this.MdiClientHandleAssigned);
				this.m_mdiClientController.MdiChildActivate += new EventHandler(this.ParentFormMdiChildActivate);
				this.m_mdiClientController.Layout += new LayoutEventHandler(this.MdiClient_Layout);
			}
			return this.m_mdiClientController;
		}
		private void ParentFormMdiChildActivate(object sender, EventArgs e)
		{
			if (this.GetMdiClientController().ParentForm != null)
			{
				IDockContent dockContent = this.GetMdiClientController().ParentForm.ActiveMdiChild as IDockContent;
				if (dockContent != null)
				{
					if (dockContent.DockHandler.DockPanel == this && dockContent.DockHandler.Pane != null)
					{
						dockContent.DockHandler.Pane.ActiveContent = dockContent;
					}
				}
			}
		}
		private void SetMdiClientBounds(Rectangle bounds)
		{
			this.GetMdiClientController().MdiClient.Bounds = bounds;
		}
		private void SuspendMdiClientLayout()
		{
			if (this.GetMdiClientController().MdiClient != null)
			{
				this.GetMdiClientController().MdiClient.SuspendLayout();
			}
		}
		private void ResumeMdiClientLayout(bool perform)
		{
			if (this.GetMdiClientController().MdiClient != null)
			{
				this.GetMdiClientController().MdiClient.ResumeLayout(perform);
			}
		}
		private void PerformMdiClientLayout()
		{
			if (this.GetMdiClientController().MdiClient != null)
			{
				this.GetMdiClientController().MdiClient.PerformLayout();
			}
		}
		private void SetMdiClient()
		{
			DockPanel.MdiClientController mdiClientController = this.GetMdiClientController();
			if (this.DocumentStyle == DocumentStyle.DockingMdi)
			{
				mdiClientController.AutoScroll = false;
				mdiClientController.BorderStyle = BorderStyle.None;
				if (this.MdiClientExists)
				{
					mdiClientController.MdiClient.Dock = DockStyle.Fill;
				}
			}
			else
			{
				if (this.DocumentStyle == DocumentStyle.DockingSdi || this.DocumentStyle == DocumentStyle.DockingWindow)
				{
					mdiClientController.AutoScroll = true;
					mdiClientController.BorderStyle = BorderStyle.Fixed3D;
					if (this.MdiClientExists)
					{
						mdiClientController.MdiClient.Dock = DockStyle.Fill;
					}
				}
				else
				{
					if (this.DocumentStyle == DocumentStyle.SystemMdi)
					{
						mdiClientController.AutoScroll = true;
						mdiClientController.BorderStyle = BorderStyle.Fixed3D;
						if (mdiClientController.MdiClient != null)
						{
							mdiClientController.MdiClient.Dock = DockStyle.None;
							mdiClientController.MdiClient.Bounds = this.SystemMdiClientBounds;
						}
					}
				}
			}
		}
		internal Rectangle RectangleToMdiClient(Rectangle rect)
		{
			Rectangle result;
			if (this.MdiClientExists)
			{
				result = this.GetMdiClientController().MdiClient.RectangleToClient(rect);
			}
			else
			{
				result = Rectangle.Empty;
			}
			return result;
		}
		public void SaveAsXml(string fileName)
		{
			DockPanel.Persistor.SaveAsXml(this, fileName);
		}
		public void SaveAsXml(string fileName, Encoding encoding)
		{
			DockPanel.Persistor.SaveAsXml(this, fileName, encoding);
		}
		public void SaveAsXml(Stream stream, Encoding encoding)
		{
			DockPanel.Persistor.SaveAsXml(this, stream, encoding);
		}
		public void SaveAsXml(Stream stream, Encoding encoding, bool upstream)
		{
			DockPanel.Persistor.SaveAsXml(this, stream, encoding, upstream);
		}
		public void LoadFromXml(string fileName, DeserializeDockContent deserializeContent)
		{
			DockPanel.Persistor.LoadFromXml(this, fileName, deserializeContent);
		}
		public void LoadFromXml(Stream stream, DeserializeDockContent deserializeContent)
		{
			DockPanel.Persistor.LoadFromXml(this, stream, deserializeContent);
		}
		public void LoadFromXml(Stream stream, DeserializeDockContent deserializeContent, bool closeStream)
		{
			DockPanel.Persistor.LoadFromXml(this, stream, deserializeContent, closeStream);
		}
		private DockPanel.SplitterDragHandler GetSplitterDragHandler()
		{
			if (this.m_splitterDragHandler == null)
			{
				this.m_splitterDragHandler = new DockPanel.SplitterDragHandler(this);
			}
			return this.m_splitterDragHandler;
		}
		internal void BeginDrag(ISplitterDragSource dragSource, Rectangle rectSplitter)
		{
			this.GetSplitterDragHandler().BeginDrag(dragSource, rectSplitter);
		}
	}
}
