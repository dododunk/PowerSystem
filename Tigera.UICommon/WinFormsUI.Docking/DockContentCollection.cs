using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
namespace WinFormsUI.Docking
{
	public class DockContentCollection : ReadOnlyCollection<IDockContent>
	{
		private static List<IDockContent> _emptyList = new List<IDockContent>(0);
		private DockPane m_dockPane = null;
		private DockPane DockPane
		{
			get
			{
				return this.m_dockPane;
			}
		}
		public new IDockContent this[int index]
		{
			get
			{
				IDockContent result;
				if (this.DockPane == null)
				{
                    try
                    {
                        result = base.Items[index];
                    }
                    catch (System.Exception ex)
                    {
                        return null;
                    }
					
				}
				else
				{
					result = this.GetVisibleContent(index);
				}
				return result;
			}
		}
		public new int Count
		{
			get
			{
				int result;
				if (this.DockPane == null)
				{
					result = base.Count;
				}
				else
				{
					result = this.CountOfVisibleContents;
				}
				return result;
			}
		}
		private int CountOfVisibleContents
		{
			get
			{
				if (this.DockPane == null)
				{
					throw new InvalidOperationException();
				}
				int num = 0;
				checked
				{
					foreach (IDockContent current in this.DockPane.Contents)
					{
						if (current.DockHandler.DockState == this.DockPane.DockState)
						{
							num++;
						}
					}
					return num;
				}
			}
		}
		internal DockContentCollection() : base(new List<IDockContent>())
		{
		}
		internal DockContentCollection(DockPane pane) : base(DockContentCollection._emptyList)
		{
			this.m_dockPane = pane;
		}
		internal int Add(IDockContent content)
		{
			if (this.DockPane != null)
			{
				throw new InvalidOperationException();
			}
			int result;
			if (this.Contains(content))
			{
				result = this.IndexOf(content);
			}
			else
			{
				base.Items.Add(content);
				result = checked(this.Count - 1);
			}
			return result;
		}
		internal void AddAt(IDockContent content, int index)
		{
			if (this.DockPane != null)
			{
				throw new InvalidOperationException();
			}
			if (index >= 0 && index <= checked(base.Items.Count - 1))
			{
				if (!this.Contains(content))
				{
					base.Items.Insert(index, content);
				}
			}
		}
		public new bool Contains(IDockContent content)
		{
			bool result;
			if (this.DockPane == null)
			{
				result = base.Items.Contains(content);
			}
			else
			{
				result = (this.GetIndexOfVisibleContents(content) != -1);
			}
			return result;
		}
		public new int IndexOf(IDockContent content)
		{
			int result;
			if (this.DockPane == null)
			{
				if (!this.Contains(content))
				{
					result = -1;
				}
				else
				{
					result = base.Items.IndexOf(content);
				}
			}
			else
			{
				result = this.GetIndexOfVisibleContents(content);
			}
			return result;
		}
		internal void Remove(IDockContent content)
		{
			if (this.DockPane != null)
			{
				throw new InvalidOperationException();
			}
			if (this.Contains(content))
			{
				base.Items.Remove(content);
			}
		}
		private IDockContent GetVisibleContent(int index)
		{
			if (this.DockPane == null)
			{
				throw new InvalidOperationException();
			}
			int num = -1;
			checked
			{
				foreach (IDockContent current in this.DockPane.Contents)
				{
					if (current.DockHandler.DockState == this.DockPane.DockState)
					{
						num++;
					}
					if (num == index)
					{
						return current;
					}
				}
				throw new ArgumentOutOfRangeException();
			}
		}
		private int GetIndexOfVisibleContents(IDockContent content)
		{
			if (this.DockPane == null)
			{
				throw new InvalidOperationException();
			}
			checked
			{
				int result;
				if (content == null)
				{
					result = -1;
				}
				else
				{
					int num = -1;
					foreach (IDockContent current in this.DockPane.Contents)
					{
						if (current.DockHandler.DockState == this.DockPane.DockState)
						{
							num++;
							if (current == content)
							{
								result = num;
								return result;
							}
						}
					}
					result = -1;
				}
				return result;
			}
		}
	}
}
