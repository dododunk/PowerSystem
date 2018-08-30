using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
namespace WinFormsUI.Docking
{
	public class DockPaneCollection : ReadOnlyCollection<DockPane>
	{
		internal DockPaneCollection() : base(new List<DockPane>())
		{
		}
		internal int Add(DockPane pane)
		{
			int result;
			if (base.Items.Contains(pane))
			{
				result = base.Items.IndexOf(pane);
			}
			else
			{
				base.Items.Add(pane);
				result = checked(base.Count - 1);
			}
			return result;
		}
		internal void AddAt(DockPane pane, int index)
		{
			if (index >= 0 && index <= checked(base.Items.Count - 1))
			{
				if (!base.Contains(pane))
				{
					base.Items.Insert(index, pane);
				}
			}
		}
		internal void Dispose()
		{
			checked
			{
				for (int i = base.Count - 1; i >= 0; i--)
				{
					base[i].Close();
				}
			}
		}
		internal void Remove(DockPane pane)
		{
			base.Items.Remove(pane);
		}
	}
}
