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
	public class FrameDisplay : ToolWindow
	{
		private delegate void ShowMsgDelegate(object obj);
		private delegate void AddMsgDelegate(string txt, Color color);
		public RichTextBoxEx textbox = new RichTextBoxEx();
		private IContainer components = null;
		private Panel panel1;
		private ToolStripSeparator toolStripMenuItem2;
		private ToolStripMenuItem 选中帧解析ToolStripMenuItem;
		private SaveFileDialog saveFileDialog1;
		private ToolStripMenuItem 保存ToolStripMenuItem;
		private ToolStripSeparator toolStripMenuItem1;
		private ToolStripMenuItem 刷新ToolStripMenuItem;
		internal ContextMenuStrip ContextMenuDock;
		public FrameDisplay()
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
		private void FrameDisplayShown(object sender, EventArgs e)
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
					
					
					int num = 0;
					if (num < LogMSG.gMSGInfo.Count)
					{
					
						this.AddMsg(LogMSG.gMSGInfo[num].Msg, LogMSG.gMSGInfo[num].cor);
						LogMSG.gMSGInfo.RemoveAt(num);
						num++;
					}
				}
			}
		}
		private void AddMsg(string txt, Color color)
		{
			Thread.Sleep(0);
			if (base.InvokeRequired)
			{
				base.Invoke(new FrameDisplay.AddMsgDelegate(this.AddMsg), new object[]
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
					if (txt.Length > 0)
					{
						this.textbox.Select(this.textbox.Text.Length, 0);
						this.textbox.SelectionColor = color;
						this.textbox.AppendText(txt);
						this.textbox.Select(this.textbox.Text.Length, 0);
						this.textbox.ScrollToCaret();
					}
				}
				catch
				{
				}
				Application.DoEvents();
			}
		}
		private void FrameDisplayFormClosing(object sender, FormClosingEventArgs e)
		{
			Program.CanShowText = false;
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
		private void 选中帧解析ToolStripMenuItemClick(object sender, EventArgs e)
		{
			FrmParse frmParse = new FrmParse();
			frmParse.DoParse(this.textbox.SelectedText);
			frmParse.Show();
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
			this.ContextMenuDock = new ContextMenuStrip(this.components);
			this.选中帧解析ToolStripMenuItem = new ToolStripMenuItem();
			this.toolStripMenuItem2 = new ToolStripSeparator();
			this.刷新ToolStripMenuItem = new ToolStripMenuItem();
			this.toolStripMenuItem1 = new ToolStripSeparator();
			this.保存ToolStripMenuItem = new ToolStripMenuItem();
			this.saveFileDialog1 = new SaveFileDialog();
			this.panel1 = new Panel();
			this.ContextMenuDock.SuspendLayout();
			base.SuspendLayout();
			this.ContextMenuDock.Items.AddRange(new ToolStripItem[]
			{
				this.选中帧解析ToolStripMenuItem,
				this.toolStripMenuItem2,
				this.刷新ToolStripMenuItem,
				this.toolStripMenuItem1,
				this.保存ToolStripMenuItem
			});
			this.ContextMenuDock.Name = "ContextMenuStrip1";
			this.ContextMenuDock.Size = new Size(143, 82);
			this.ContextMenuDock.Text = "Window Position";
			this.选中帧解析ToolStripMenuItem.Name = "选中帧解析ToolStripMenuItem";
			this.选中帧解析ToolStripMenuItem.Size = new Size(142, 22);
			this.选中帧解析ToolStripMenuItem.Text = "选中文本解析";
			this.选中帧解析ToolStripMenuItem.Click += new EventHandler(this.选中帧解析ToolStripMenuItemClick);
			this.toolStripMenuItem2.Name = "toolStripMenuItem2";
			this.toolStripMenuItem2.Size = new Size(139, 6);
			this.刷新ToolStripMenuItem.Name = "刷新ToolStripMenuItem";
			this.刷新ToolStripMenuItem.Size = new Size(142, 22);
			this.刷新ToolStripMenuItem.Text = "清空信息";
			this.刷新ToolStripMenuItem.Click += new EventHandler(this.刷新ToolStripMenuItemClick);
			this.toolStripMenuItem1.Name = "toolStripMenuItem1";
			this.toolStripMenuItem1.Size = new Size(139, 6);
			this.保存ToolStripMenuItem.Name = "保存ToolStripMenuItem";
			this.保存ToolStripMenuItem.Size = new Size(142, 22);
			this.保存ToolStripMenuItem.Text = "保存信息";
			this.保存ToolStripMenuItem.Click += new EventHandler(this.保存ToolStripMenuItemClick);
			this.panel1.Dock = DockStyle.Fill;
			this.panel1.Location = new Point(0, 0);
			this.panel1.Name = "panel1";
			this.panel1.Size = new Size(595, 244);
			this.panel1.TabIndex = 6;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			this.BackColor = Color.FromArgb(239, 237, 226);
			base.ClientSize = new Size(595, 244);
			base.CloseButton = false;
			base.CloseButtonVisible = false;
			base.Controls.Add(this.panel1);
			//base.DockAreas = (DockAreas.Float | DockAreas.DockLeft | DockAreas.DockRight | DockAreas.DockTop | DockAreas.DockBottom | DockAreas.Document);
			base.Name = "FrameDisplay";
			base.TabPageContextMenuStrip = this.ContextMenuDock;
			this.Text = "操作记录";
			base.FormClosing += new FormClosingEventHandler(this.FrameDisplayFormClosing);
			base.Shown += new EventHandler(this.FrameDisplayShown);
			this.ContextMenuDock.ResumeLayout(false);
			base.ResumeLayout(false);
		}
	}
}
