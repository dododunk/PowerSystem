using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Ctl
{
	public class CustomizeDel : Form
	{
		public TreeView treeView1 = new TreeView();
		private string _Categories = string.Empty;
		private string _Name = string.Empty;
		private string _AFN = string.Empty;
		private string _FN = string.Empty;
		private IContainer components = null;
		private ImageList imageList1;
		private Button button1;
		private Panel panel1;
		private SplitContainer splitContainer1;
		private DataGridViewEx grid1;
		private DataGridViewTextBoxColumn Column3;
		private DataGridViewTextBoxColumn Column2;
		private DataGridViewTextBoxColumn Column1;
		private TextBox textBox1;
		private Label label1;
		private Label label2;
		private ComboBox AFN;
		private Label label3;
		private ComboBox FN;
		public CustomizeDel()
		{
			this.InitializeComponent();
			this.grid1.AllowUserToAddRows = false;
			checked
			{
				for (int i = 1; i < 235; i++)
				{
					this.FN.Items.Add(i.ToString().PadLeft(4, '0'));
				}
				this.treeView1.BorderStyle = BorderStyle.Fixed3D;
				this.treeView1.Dock = DockStyle.Fill;
				this.treeView1.Parent = this.splitContainer1.Panel1;
				this.treeView1.AfterSelect += new TreeViewEventHandler(this.TreeView1AfterSelect);
				Application.DoEvents();
				this.LoadSysTree(this.treeView1, this.imageList1);
				Application.DoEvents();
			}
		}
		private void LoadSysTree(TreeView _tree, ImageList _img)
		{
			_tree.Nodes.Clear();
			_tree.ImageList = _img;
			_tree.BeginUpdate();
			this.LoadCustomize(_tree);
			_tree.EndUpdate();
		}
		private void Button1Click(object sender, EventArgs e)
		{
			if (MessageBox.Show("确定删除?", "警告", MessageBoxButtons.YesNo) == DialogResult.Yes)
			{
				Program.gFaDataBase.DeleteCustomize(this.AFN.Text, this.FN.Text);
				Application.DoEvents();
				this.LoadSysTree(this.treeView1, this.imageList1);
				Application.DoEvents();
			}
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
			checked
			{
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
					if (!string.IsNullOrEmpty(this._Name))
					{
						this.AFN.Text = this._AFN;
						this.FN.Text = this._FN;
						this.textBox1.Text = this._Name;
						string[] array2 = Program.gFaDataBase.GetCustomizeItems(this._AFN, this._FN).Split(new char[]
						{
							'|'
						});
						for (int i = 0; i < array2.Length; i++)
						{
							string[] array3 = array2[i].Split(new char[]
							{
								','
							});
							if (array3.Length > 1)
							{
								this.grid1.Rows.Add();
								this.grid1.Rows[i].Cells[0].Value = array3[0];
								this.grid1.Rows[i].Cells[1].Value = array3[1];
								this.grid1.Rows[i].Cells[2].Value = array3[2];
							}
						}
					}
				}
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
			DataGridViewCellStyle dataGridViewCellStyle = new DataGridViewCellStyle();
			DataGridViewCellStyle dataGridViewCellStyle2 = new DataGridViewCellStyle();
			ComponentResourceManager componentResourceManager = new ComponentResourceManager(this.GetType());
			this.splitContainer1 = new SplitContainer();
			this.panel1 = new Panel();
			this.button1 = new Button();
			this.grid1 = new DataGridViewEx();
			this.Column1 = new DataGridViewTextBoxColumn();
			this.Column2 = new DataGridViewTextBoxColumn();
			this.Column3 = new DataGridViewTextBoxColumn();
			this.textBox1 = new TextBox();
			this.label1 = new Label();
			this.FN = new ComboBox();
			this.label3 = new Label();
			this.AFN = new ComboBox();
			this.label2 = new Label();
			this.imageList1 = new ImageList(this.components);
			this.splitContainer1.Panel2.SuspendLayout();
			this.splitContainer1.SuspendLayout();
			this.panel1.SuspendLayout();
			((ISupportInitialize)this.grid1).BeginInit();
			base.SuspendLayout();
			this.splitContainer1.BackColor = Color.FromArgb(239, 237, 226);
			this.splitContainer1.Dock = DockStyle.Fill;
			this.splitContainer1.FixedPanel = FixedPanel.Panel1;
			this.splitContainer1.IsSplitterFixed = true;
			this.splitContainer1.Location = new Point(3, 24);
			this.splitContainer1.Name = "splitContainer1";
			this.splitContainer1.Panel2.Controls.Add(this.panel1);
			this.splitContainer1.Size = new Size(607, 390);
			this.splitContainer1.SplitterDistance = 185;
			this.splitContainer1.TabIndex = 0;
			this.panel1.BackColor = Color.FromArgb(239, 237, 226);
			this.panel1.Controls.Add(this.button1);
			this.panel1.Controls.Add(this.grid1);
			this.panel1.Controls.Add(this.textBox1);
			this.panel1.Controls.Add(this.label1);
			this.panel1.Controls.Add(this.FN);
			this.panel1.Controls.Add(this.label3);
			this.panel1.Controls.Add(this.AFN);
			this.panel1.Controls.Add(this.label2);
			this.panel1.Dock = DockStyle.Fill;
			this.panel1.Location = new Point(0, 0);
			this.panel1.Name = "panel1";
			this.panel1.Size = new Size(418, 390);
			this.panel1.TabIndex = 0;
			this.button1.Location = new Point(363, 359);
			this.button1.Name = "button1";
			this.button1.Size = new Size(46, 23);
			this.button1.TabIndex = 22;
			this.button1.Text = "删除";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new EventHandler(this.Button1Click);
			dataGridViewCellStyle.BackColor = Color.FromArgb(240, 240, 240);
			this.grid1.AlternatingRowsDefaultCellStyle = dataGridViewCellStyle;
			this.grid1.BackgroundColor = Color.White;
			this.grid1.BorderStyle = BorderStyle.Fixed3D;
			this.grid1.ColumnHeaderColor = SystemColors.Control;
			dataGridViewCellStyle2.Alignment = DataGridViewContentAlignment.MiddleCenter;
			dataGridViewCellStyle2.BackColor = SystemColors.Control;
			dataGridViewCellStyle2.Font = new Font("宋体", 9f, FontStyle.Regular, GraphicsUnit.Point, 134);
			dataGridViewCellStyle2.ForeColor = SystemColors.WindowText;
			dataGridViewCellStyle2.SelectionBackColor = SystemColors.Highlight;
			dataGridViewCellStyle2.SelectionForeColor = SystemColors.HighlightText;
			dataGridViewCellStyle2.WrapMode = DataGridViewTriState.True;
			this.grid1.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle2;
			this.grid1.ColumnHeadersHeight = 28;
			this.grid1.Columns.AddRange(new DataGridViewColumn[]
			{
				this.Column1,
				this.Column2,
				this.Column3
			});
			this.grid1.GridColor = SystemColors.ActiveBorder;
			this.grid1.Location = new Point(6, 63);
			this.grid1.MultiSelect = false;
			this.grid1.Name = "grid1";
			this.grid1.RowHeaderColor = SystemColors.Control;
			this.grid1.RowTemplate.Height = 23;
			this.grid1.SelectionMode = DataGridViewSelectionMode.CellSelect;
			this.grid1.Size = new Size(404, 291);
			this.grid1.TabIndex = 21;
			this.Column1.HeaderText = "数据内容";
			this.Column1.Name = "Column1";
			this.Column1.ReadOnly = true;
			this.Column1.SortMode = DataGridViewColumnSortMode.NotSortable;
			this.Column1.Width = 200;
			this.Column2.HeaderText = "数据格式";
			this.Column2.Name = "Column2";
			this.Column2.ReadOnly = true;
			this.Column2.Resizable = DataGridViewTriState.True;
			this.Column2.SortMode = DataGridViewColumnSortMode.NotSortable;
			this.Column2.Width = 80;
			this.Column3.HeaderText = "字节数";
			this.Column3.Name = "Column3";
			this.Column3.ReadOnly = true;
			this.Column3.SortMode = DataGridViewColumnSortMode.NotSortable;
			this.Column3.Width = 60;
			this.textBox1.Location = new Point(45, 36);
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new Size(278, 21);
			this.textBox1.TabIndex = 20;
			this.label1.AutoSize = true;
			this.label1.Location = new Point(10, 39);
			this.label1.Name = "label1";
			this.label1.Size = new Size(29, 12);
			this.label1.TabIndex = 19;
			this.label1.Text = "名称";
			this.FN.FormattingEnabled = true;
			this.FN.Location = new Point(132, 10);
			this.FN.Name = "FN";
			this.FN.Size = new Size(61, 20);
			this.FN.TabIndex = 18;
			this.FN.Text = "0001";
			this.label3.AutoSize = true;
			this.label3.Location = new Point(109, 13);
			this.label3.Name = "label3";
			this.label3.Size = new Size(17, 12);
			this.label3.TabIndex = 17;
			this.label3.Text = "FN";
			this.AFN.FormattingEnabled = true;
			this.AFN.Items.AddRange(new object[]
			{
				"01",
				"02",
				"03",
				"04",
				"05",
				"06 ",
				"08",
				"09",
				"0A",
				"0B",
				"0C",
				"0D",
				"0E",
				"0F",
				"10"
			});
			this.AFN.Location = new Point(45, 10);
			this.AFN.Name = "AFN";
			this.AFN.Size = new Size(50, 20);
			this.AFN.TabIndex = 16;
			this.AFN.Text = "0A";
			this.label2.AutoSize = true;
			this.label2.Location = new Point(10, 13);
			this.label2.Name = "label2";
			this.label2.Size = new Size(23, 12);
			this.label2.TabIndex = 15;
			this.label2.Text = "AFN";
			this.imageList1.ImageStream = (ImageListStreamer)componentResourceManager.GetObject("imageList1.ImageStream");
			this.imageList1.TransparentColor = Color.Transparent;
			this.imageList1.Images.SetKeyName(0, "cabinet.ico");
			this.imageList1.Images.SetKeyName(1, "copy.ico");
			this.imageList1.Images.SetKeyName(2, "copy plus.ico");
			this.imageList1.Images.SetKeyName(3, "http_www.snshelp.com_80_fav.ico");
			this.imageList1.Images.SetKeyName(4, "build.ico");
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			this.BackColor = Color.FromArgb(239, 237, 226);
			base.ClientSize = new Size(613, 417);
			base.Controls.Add(this.splitContainer1);
			base.MaximizeBox = false;
			base.MinimizeBox = false;
			base.Name = "CustomizeDel";
			base.StartPosition = FormStartPosition.CenterScreen;
			this.Text = "自定义规约删除";
			this.splitContainer1.Panel2.ResumeLayout(false);
			this.splitContainer1.ResumeLayout(false);
			this.panel1.ResumeLayout(false);
			this.panel1.PerformLayout();
			((ISupportInitialize)this.grid1).EndInit();
			base.ResumeLayout(false);
		}
	}
}
