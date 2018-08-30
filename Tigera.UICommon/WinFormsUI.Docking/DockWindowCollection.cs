using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
namespace WinFormsUI.Docking
{
	public class DockWindowCollection : ReadOnlyCollection<DockWindow>
	{
		public DockWindow this[DockState dockState]
		{
			get
			{
				DockWindow result;
				if (dockState == DockState.Document)
				{
					result = base.Items[0];
				}
				else
				{
					if (dockState == DockState.DockLeft || dockState == DockState.DockLeftAutoHide)
					{
						result = base.Items[1];
					}
					else
					{
						if (dockState == DockState.DockRight || dockState == DockState.DockRightAutoHide)
						{
							result = base.Items[2];
						}
						else
						{
							if (dockState == DockState.DockTop || dockState == DockState.DockTopAutoHide)
							{
								result = base.Items[3];
							}
							else
							{
								if (dockState != DockState.DockBottom && dockState != DockState.DockBottomAutoHide)
								{
									throw new ArgumentOutOfRangeException();
								}
								result = base.Items[4];
							}
						}
					}
				}
				return result;
			}
		}
		internal DockWindowCollection(DockPanel dockPanel) : base(new List<DockWindow>())
		{
			base.Items.Add(new DockWindow(dockPanel, DockState.Document));
			base.Items.Add(new DockWindow(dockPanel, DockState.DockLeft));
			base.Items.Add(new DockWindow(dockPanel, DockState.DockRight));
			base.Items.Add(new DockWindow(dockPanel, DockState.DockTop));
			base.Items.Add(new DockWindow(dockPanel, DockState.DockBottom));
		}
	}
}
