using System;
namespace System.Windows.Forms
{
	public class CollapseDataGridViewRow : DataGridViewRow
	{
		private CollapseDataGridViewRowCollection m_rowCollection = new CollapseDataGridViewRowCollection();
		private bool m_isCollapse = false;
		public bool IsCollapse
		{
			get
			{
				return this.m_isCollapse;
			}
			set
			{
				this.m_isCollapse = value;
			}
		}
		public CollapseDataGridViewRowCollection Rows
		{
			get
			{
				return this.m_rowCollection;
			}
			set
			{
				this.m_rowCollection = value;
			}
		}
	}
}
