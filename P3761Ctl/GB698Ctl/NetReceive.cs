using GB698Cls;
using System;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Threading;
using System.Windows.Forms;
using WinFormsUI.Docking;
namespace GB698Ctl
{
	public class NetReceive : ToolWindow
	{
		private delegate void ShowMsgDelegate(object obj);
		private delegate void AddMsgDelegate(string txt, Color color);
		public RichTextBoxEx textbox = new RichTextBoxEx();
		private IContainer components = null;
		private Panel panel1;
		private ToolStripMenuItem 保存ToolStripMenuItem;
		private ToolStripSeparator toolStripMenuItem1;
		private ToolStripMenuItem 刷新ToolStripMenuItem;
        private ToolStripMenuItem 选中帧解析ToolStripMenuItem;
		internal ContextMenuStrip ContextMenuDock;
		private SaveFileDialog saveFileDialog1;
		public NetReceive()
		{
			this.InitializeComponent();
			this.textbox.Parent = this.panel1;
			this.textbox.Multiline = true;
			this.textbox.ScrollBars = RichTextBoxScrollBars.Both;
			this.textbox.Dock = DockStyle.Fill;
			this.textbox.ContextMenuStrip = this.ContextMenuDock;
			Application.DoEvents();
			Program.CanShowText = true;
		}
		private void NetReceiveShown(object sender, EventArgs e)
		{
			ThreadPool.QueueUserWorkItem(new WaitCallback(this.ShowMsg), null);
		}
		private void ShowMsg(object obj)
		{
			Thread.CurrentThread.IsBackground = true;
			checked
			{
				while (Program.CanShowText)
				{
					Application.DoEvents();
					Thread.Sleep(1);
					for (int i = RecieveLog.gRECInfo.Count - 1; i >= 0; i--)
					{
						Application.DoEvents();
						this.AddMsg(RecieveLog.gRECInfo[i].Data, Color.FromArgb(23, 23, 23));
						RecieveLog.gRECInfo.RemoveAt(i);
					}
				}
			}
		}
		private void AddMsg(string txt, Color color)
		{
			Thread.Sleep(0);
			if (base.InvokeRequired)
			{
				base.Invoke(new NetReceive.AddMsgDelegate(this.AddMsg), new object[]
				{
					txt,
					color
				});
			}
			else
			{
				try
				{
					if (Program.SaveLog == 1)
					{
						LogWritter.WriteLine(txt);
					}
				}
				catch
				{
				}
				try
				{
					this.textbox.Select(this.textbox.Text.Length, 0);
					this.textbox.SelectionColor = color;
					this.textbox.AppendText(txt);
					this.textbox.Select(this.textbox.Text.Length, 0);
					this.textbox.ScrollToCaret();
				}
				catch
				{
				}
				Application.DoEvents();
			}
		}
		private void 刷新ToolStripMenuItemClick(object sender, EventArgs e)
		{
			this.textbox.Text = "";
		}
		private void 保存ToolStripMenuItemClick(object sender, EventArgs e)
		{
			this.saveFileDialog1.Filter = "文本|*.txt";
			this.saveFileDialog1.InitialDirectory = Program.SysPath;
			if (this.saveFileDialog1.ShowDialog() == DialogResult.OK)
			{
				string text = this.textbox.Text;
				using (StreamWriter streamWriter = new StreamWriter(this.saveFileDialog1.FileName))
				{
					streamWriter.WriteLine(text);
				}
			}
		}
		private void NetReceiveFormClosing(object sender, FormClosingEventArgs e)
		{
			Program.CanShowText = false;
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
        private void 选中帧解析ToolStripMenuItemClick(object sender, EventArgs e)
        {
            FrmParse frmParse = new FrmParse();
            frmParse.DoParse(this.textbox.SelectedText);
            frmParse.Show();
        }
		private void InitializeComponent()
		{
            base.SuspendLayout();
			this.components = new Container();
			this.saveFileDialog1 = new SaveFileDialog();
			this.ContextMenuDock = new ContextMenuStrip(this.components);
			this.刷新ToolStripMenuItem = new ToolStripMenuItem();
			this.toolStripMenuItem1 = new ToolStripSeparator();
			this.保存ToolStripMenuItem = new ToolStripMenuItem();
            this.选中帧解析ToolStripMenuItem = new ToolStripMenuItem();
			this.panel1 = new Panel();
			this.ContextMenuDock.SuspendLayout();
			
			this.ContextMenuDock.Items.AddRange(new ToolStripItem[]
			{
                this.选中帧解析ToolStripMenuItem,
				this.刷新ToolStripMenuItem,
				this.toolStripMenuItem1,
				this.保存ToolStripMenuItem
			});
			this.ContextMenuDock.Name = "ContextMenuStrip1";
			this.ContextMenuDock.Size = new Size(95, 54);
			this.ContextMenuDock.Text = "Window Position";
			this.刷新ToolStripMenuItem.Name = "刷新ToolStripMenuItem";
			this.刷新ToolStripMenuItem.Size = new Size(94, 22);
			this.刷新ToolStripMenuItem.Text = "清空";
			this.刷新ToolStripMenuItem.Click += new EventHandler(this.刷新ToolStripMenuItemClick);
			this.toolStripMenuItem1.Name = "toolStripMenuItem1";
			this.toolStripMenuItem1.Size = new Size(91, 6);
			this.保存ToolStripMenuItem.Name = "保存ToolStripMenuItem";
			this.保存ToolStripMenuItem.Size = new Size(94, 22);
			this.保存ToolStripMenuItem.Text = "保存";
			this.保存ToolStripMenuItem.Click += new EventHandler(this.保存ToolStripMenuItemClick);
            this.选中帧解析ToolStripMenuItem.Name = "选中帧解析ToolStripMenuItem";
			this.选中帧解析ToolStripMenuItem.Size = new Size(142, 22);
			this.选中帧解析ToolStripMenuItem.Text = "选中文本解析";
			this.选中帧解析ToolStripMenuItem.Click += new EventHandler(this.选中帧解析ToolStripMenuItemClick);
			this.panel1.BackColor = Color.FromArgb(239, 237, 226);
			this.panel1.Dock = DockStyle.Fill;
			this.panel1.Location = new Point(0, 0);
			this.panel1.Name = "panel1";
			this.panel1.Size = new Size(620, 215);
			this.panel1.TabIndex = 5;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(620, 215);
			base.CloseButton = false;
			base.CloseButtonVisible = false;
			base.Controls.Add(this.panel1);
			
			base.Name = "NetReceive";
			base.TabPageContextMenuStrip = this.ContextMenuDock;
			this.Text = "网络接收报文";
			base.FormClosing += new FormClosingEventHandler(this.NetReceiveFormClosing);
			base.Shown += new EventHandler(this.NetReceiveShown);
			this.ContextMenuDock.ResumeLayout(false);
			base.ResumeLayout(false);
		}
	}
}
