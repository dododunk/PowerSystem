using GB698Cls;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Ctl
{
	public class GB698Items : ToolWindow
	{
		public TreeView treeView1 = new TreeView();
		private string _Categories = string.Empty;
		private string _Name = string.Empty;
		private string _AFN = string.Empty;
		private string _FN = string.Empty;
		private FormCustomizeAdd gCustomizeAdd;
		private IContainer components = null;
		private ToolStripMenuItem 查询项目ToolStripMenuItem;
		private ToolStripSeparator toolStripMenuItem2;
		private ToolStripMenuItem 自定义添加ToolStripMenuItem;
		private ToolStripSeparator toolStripMenuItem1;
		private ToolStripMenuItem 刷新ToolStripMenuItem;
		internal ContextMenuStrip ContextMenuDock;
		private ImageList imageList1;
		public GB698Items()
		{
			this.InitializeComponent();
			this.treeView1.BorderStyle = BorderStyle.Fixed3D;
			this.treeView1.Dock = DockStyle.Fill;
			this.treeView1.Parent = this;
			this.treeView1.ContextMenuStrip = this.ContextMenuDock;
			this.treeView1.NodeMouseDoubleClick += new TreeNodeMouseClickEventHandler(this.TreeView1NodeMouseDoubleClick);
			this.treeView1.AfterSelect += new TreeViewEventHandler(this.TreeView1AfterSelect);
		}
		private void GB698ItemsShown(object sender, EventArgs e)
		{
			Application.DoEvents();
			this.LoadSysTree(this.treeView1, this.imageList1);
			Application.DoEvents();
		}
		private void LoadSysTree(TreeView _tree, ImageList _img)
		{
			_tree.Nodes.Clear();
			_tree.ImageList = _img;
			_tree.BeginUpdate();
			ProtocolTree protocolTree = new ProtocolTree();
			protocolTree.InitTree(_tree);
			_tree.EndUpdate();
		}
		private void LoadCustomize(TreeView _tree)
		{
			TreeNode iroot = this.AddRoot(_tree, "自定义规约", 0);
			string[] aLLCustomizeItems = Program.gFaDataBase.GetALLCustomizeItems();
			checked
			{
				for (int i = 0; i < aLLCustomizeItems.Length; i++)
				{
					string[] array = aLLCustomizeItems[i].Split(new char[]
					{
						','
					});
					if (array.Length > 1)
					{
						string text = string.Empty;
						text = text + Convert.ToString(array[0]) + "|";
						text = text + Convert.ToString(array[1]) + "|";
						text += Convert.ToString(array[2]);
						TreeNode treeNode = this.AddChild(iroot, text, 1, 2);
					}
				}
			}
		}
		private TreeNode AddRoot(TreeView _tree, string nodetest, int imageindex)
		{
			TreeNode treeNode = new TreeNode(nodetest, imageindex, imageindex);
			_tree.Nodes.Add(treeNode);
			return treeNode;
		}
		private TreeNode AddChild(TreeNode iroot, string nodetest, int imageindex1, int imageindex2)
		{
			TreeNode treeNode = new TreeNode(nodetest, imageindex1, imageindex2);
			iroot.Nodes.Add(treeNode);
			return treeNode;
		}
		private void TreeView1AfterSelect(object sender, TreeViewEventArgs e)
		{
			this._Categories = "";
			int nodeCount = e.Node.GetNodeCount(true);
			if (nodeCount == 0 & e.Node.Parent != null)
			{
				string[] array = e.Node.Text.Split(new char[]
				{
					'|'
				});
				this._Categories = e.Node.Parent.Text;
				this._Name = array[0];
				this._AFN = array[1];
				this._FN = array[2];
			}
		}
		private void TreeView1NodeMouseDoubleClick(object sender, TreeNodeMouseClickEventArgs e)
		{
			if (!string.IsNullOrEmpty(this._Categories))
			{
				MainForm.gMainForm.gb698Opera.AddRow(this._Categories, this._Name, "", "", this._AFN, this._FN.PadLeft(4, '0'), "", "");
			}
		}
		private void 刷新ToolStripMenuItemClick(object sender, EventArgs e)
		{
			this.LoadSysTree(this.treeView1, this.imageList1);
		}
		private void 自定义添加ToolStripMenuItemClick(object sender, EventArgs e)
		{
			this.gCustomizeAdd = new FormCustomizeAdd();
			this.gCustomizeAdd.ShowDialog();
			this.LoadSysTree(this.treeView1, this.imageList1);
		}
		private void 查询项目ToolStripMenuItemClick(object sender, EventArgs e)
		{
			string text = InputPN.InputBox("模糊查询", "项目名称", "");
			if (!string.IsNullOrEmpty(text))
			{
				TreeNodeCollection nodes = this.treeView1.Nodes;
				this.GetNode(nodes, text);
			}
		}
		private void GetNode(TreeNodeCollection tc, string jhd)
		{
			bool flag = false;
			foreach (TreeNode treeNode in tc)
			{
				int nodeCount = treeNode.GetNodeCount(true);
				if (nodeCount == 0)
				{
					if (treeNode.Text.IndexOf(jhd) >= 0)
					{
						this.treeView1.SelectedNode = treeNode;
						treeNode.EnsureVisible();
						flag = true;
						break;
					}
				}
				this.GetNode(treeNode.Nodes, jhd);
			}
			if (!flag)
			{
				MessageBox.Show("未查到相关记录");
			}
		}
		protected override void Dispose(bool disposing)
		{
			if (disposing)
			{
				if (this.components != null)
				{
					this.components.Dispose();
				}
			}
			base.Dispose(disposing);
		}
		private void InitializeComponent()
		{
			this.components = new Container();
			ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof(GB698Items));
			this.imageList1 = new ImageList(this.components);
			this.ContextMenuDock = new ContextMenuStrip(this.components);
			this.刷新ToolStripMenuItem = new ToolStripMenuItem();
			this.toolStripMenuItem1 = new ToolStripSeparator();
			this.自定义添加ToolStripMenuItem = new ToolStripMenuItem();
			this.toolStripMenuItem2 = new ToolStripSeparator();
			this.查询项目ToolStripMenuItem = new ToolStripMenuItem();
			this.ContextMenuDock.SuspendLayout();
			base.SuspendLayout();
			this.imageList1.ImageStream = (ImageListStreamer)componentResourceManager.GetObject("imageList1.ImageStream");
			this.imageList1.TransparentColor = Color.Transparent;
			this.imageList1.Images.SetKeyName(0, "cabinet.ico");
			this.imageList1.Images.SetKeyName(1, "copy.ico");
			this.imageList1.Images.SetKeyName(2, "copy plus.ico");
			this.imageList1.Images.SetKeyName(3, "http_www.snshelp.com_80_fav.ico");
			this.imageList1.Images.SetKeyName(4, "build.ico");
			this.ContextMenuDock.Items.AddRange(new ToolStripItem[]
			{
				this.刷新ToolStripMenuItem,
				this.toolStripMenuItem1,
				this.自定义添加ToolStripMenuItem,
				this.toolStripMenuItem2,
				this.查询项目ToolStripMenuItem
			});
			this.ContextMenuDock.Name = "ContextMenuStrip1";
			this.ContextMenuDock.Size = new Size(119, 82);
			this.ContextMenuDock.Text = "Window Position";
			this.刷新ToolStripMenuItem.Name = "刷新ToolStripMenuItem";
			this.刷新ToolStripMenuItem.Size = new Size(118, 22);
			this.刷新ToolStripMenuItem.Text = "刷新项目";
			this.刷新ToolStripMenuItem.Click += new EventHandler(this.刷新ToolStripMenuItemClick);
			this.toolStripMenuItem1.Name = "toolStripMenuItem1";
			this.toolStripMenuItem1.Size = new Size(115, 6);
			this.自定义添加ToolStripMenuItem.Name = "自定义添加ToolStripMenuItem";
			this.自定义添加ToolStripMenuItem.Size = new Size(118, 22);
			this.自定义添加ToolStripMenuItem.Text = "规约添加";
			this.自定义添加ToolStripMenuItem.Click += new EventHandler(this.自定义添加ToolStripMenuItemClick);
			this.toolStripMenuItem2.Name = "toolStripMenuItem2";
			this.toolStripMenuItem2.Size = new Size(115, 6);
			this.查询项目ToolStripMenuItem.Name = "查询项目ToolStripMenuItem";
			this.查询项目ToolStripMenuItem.Size = new Size(118, 22);
			this.查询项目ToolStripMenuItem.Text = "查询项目";
			this.查询项目ToolStripMenuItem.Click += new EventHandler(this.查询项目ToolStripMenuItemClick);
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			this.BackColor = Color.FromArgb(239, 237, 226);
			base.ClientSize = new Size(196, 387);
			base.CloseButton = false;
			base.CloseButtonVisible = false;
			base.Name = "GB698Items";
			base.TabPageContextMenuStrip = this.ContextMenuDock;
			this.Text = "主站协议";
			base.Shown += new EventHandler(this.GB698ItemsShown);
			this.ContextMenuDock.ResumeLayout(false);
			base.ResumeLayout(false);
		}
	}
}
