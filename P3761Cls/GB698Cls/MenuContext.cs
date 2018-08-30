using System;
using System.Windows.Forms;
namespace GB698Cls
{
	public class MenuContext
	{
		private ToolStripMenuItem ToolStripMenuItem1;
		private ToolStripMenuItem ToolStripMenuItem2;
		private ToolStripSeparator ToolStripMenuItem3;
		public ContextMenuStrip contextMenuStrip = null;
		public DataGridView Grid = null;
		public MenuContext()
		{
			this.ToolStripMenuItem1 = new ToolStripMenuItem();
			this.ToolStripMenuItem1.Name = "ToolStripMenuItem1";
			this.ToolStripMenuItem1.Text = "添加行";
			this.ToolStripMenuItem3 = new ToolStripSeparator();
			this.ToolStripMenuItem3.Name = "ToolStripMenuItem3";
			this.ToolStripMenuItem3.Text = "-";
			this.ToolStripMenuItem2 = new ToolStripMenuItem();
			this.ToolStripMenuItem2.Name = "ToolStripMenuItem2";
			this.ToolStripMenuItem2.Text = "删除行";
			this.contextMenuStrip = new ContextMenuStrip();
			this.contextMenuStrip.Items.Add(this.ToolStripMenuItem1);
			this.contextMenuStrip.Items.Add(this.ToolStripMenuItem3);
			this.contextMenuStrip.Items.Add(this.ToolStripMenuItem2);
			this.ToolStripMenuItem1.Click += new EventHandler(this.AddMenuItemClick);
			this.ToolStripMenuItem2.Click += new EventHandler(this.DelMenuItemClick);
		}
		private void AddMenuItemClick(object sender, EventArgs e)
		{
			try
			{
				this.Grid.Rows.Add();
			}
			catch (Exception)
			{
			}
		}
		private void DelMenuItemClick(object sender, EventArgs e)
		{
			try
			{
				this.Grid.Rows.Remove(this.Grid.CurrentRow);
			}
			catch (Exception)
			{
			}
		}
	}
}
