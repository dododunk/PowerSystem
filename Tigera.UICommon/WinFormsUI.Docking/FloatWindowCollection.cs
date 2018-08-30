using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
namespace WinFormsUI.Docking
{
	public class FloatWindowCollection : ReadOnlyCollection<FloatWindow>
	{
		internal FloatWindowCollection() : base(new List<FloatWindow>())
		{
		}
		internal int Add(FloatWindow fw)
		{
			int result;
			if (base.Items.Contains(fw))
			{
				result = base.Items.IndexOf(fw);
			}
			else
			{
				base.Items.Add(fw);
				result = checked(base.Count - 1);
			}
			return result;
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
		internal void Remove(FloatWindow fw)
		{
			base.Items.Remove(fw);
		}
		internal void BringWindowToFront(FloatWindow fw)
		{
			base.Items.Remove(fw);
			base.Items.Add(fw);
		}
	}
}
