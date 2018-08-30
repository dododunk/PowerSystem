using System;
using System.Drawing;
using System.Windows.Forms;
namespace WinFormsUI.Docking
{
	internal static class DockHelper
	{
		public static bool IsDockStateAutoHide(DockState dockState)
		{
			return dockState == DockState.DockLeftAutoHide || dockState == DockState.DockRightAutoHide || dockState == DockState.DockTopAutoHide || dockState == DockState.DockBottomAutoHide;
		}
		public static bool IsDockStateValid(DockState dockState, DockAreas dockableAreas)
		{
			return ((dockableAreas & DockAreas.Float) != (DockAreas)0 || dockState != DockState.Float) && ((dockableAreas & DockAreas.Document) != (DockAreas)0 || dockState != DockState.Document) && ((dockableAreas & DockAreas.DockLeft) != (DockAreas)0 || (dockState != DockState.DockLeft && dockState != DockState.DockLeftAutoHide)) && ((dockableAreas & DockAreas.DockRight) != (DockAreas)0 || (dockState != DockState.DockRight && dockState != DockState.DockRightAutoHide)) && ((dockableAreas & DockAreas.DockTop) != (DockAreas)0 || (dockState != DockState.DockTop && dockState != DockState.DockTopAutoHide)) && ((dockableAreas & DockAreas.DockBottom) != (DockAreas)0 || (dockState != DockState.DockBottom && dockState != DockState.DockBottomAutoHide));
		}
		public static bool IsDockWindowState(DockState state)
		{
			return state == DockState.DockTop || state == DockState.DockBottom || state == DockState.DockLeft || state == DockState.DockRight || state == DockState.Document;
		}
		public static DockState ToggleAutoHideState(DockState state)
		{
			DockState result;
			if (state == DockState.DockLeft)
			{
				result = DockState.DockLeftAutoHide;
			}
			else
			{
				if (state == DockState.DockRight)
				{
					result = DockState.DockRightAutoHide;
				}
				else
				{
					if (state == DockState.DockTop)
					{
						result = DockState.DockTopAutoHide;
					}
					else
					{
						if (state == DockState.DockBottom)
						{
							result = DockState.DockBottomAutoHide;
						}
						else
						{
							if (state == DockState.DockLeftAutoHide)
							{
								result = DockState.DockLeft;
							}
							else
							{
								if (state == DockState.DockRightAutoHide)
								{
									result = DockState.DockRight;
								}
								else
								{
									if (state == DockState.DockTopAutoHide)
									{
										result = DockState.DockTop;
									}
									else
									{
										if (state == DockState.DockBottomAutoHide)
										{
											result = DockState.DockBottom;
										}
										else
										{
											result = state;
										}
									}
								}
							}
						}
					}
				}
			}
			return result;
		}
		public static DockPane PaneAtPoint(Point pt, DockPanel dockPanel)
		{
			Control control = Win32Helper.ControlAtPoint(pt);
			DockPane result;
			while (control != null)
			{
				IDockContent dockContent = control as IDockContent;
				if (dockContent != null && dockContent.DockHandler.DockPanel == dockPanel)
				{
					result = dockContent.DockHandler.Pane;
				}
				else
				{
					DockPane dockPane = control as DockPane;
					if (dockPane == null || dockPane.DockPanel != dockPanel)
					{
						control = control.Parent;
						continue;
					}
					result = dockPane;
				}
				return result;
			}
			result = null;
			return result;
		}
		public static FloatWindow FloatWindowAtPoint(Point pt, DockPanel dockPanel)
		{
			FloatWindow result;
			for (Control control = Win32Helper.ControlAtPoint(pt); control != null; control = control.Parent)
			{
				FloatWindow floatWindow = control as FloatWindow;
				if (floatWindow != null && floatWindow.DockPanel == dockPanel)
				{
					result = floatWindow;
					return result;
				}
			}
			result = null;
			return result;
		}
	}
}
