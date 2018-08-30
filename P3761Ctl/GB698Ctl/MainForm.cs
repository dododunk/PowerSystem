using GB698Cls;
using GB698Ctl.Properties;
//using HelpRes;
using System;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.IO;
using System.Windows.Forms;
using WinFormsUI.Docking;
using GB698Ctl.GB698Ctl;
namespace GB698Ctl
{
	public class MainForm : Form
	{
		public bool m_bSaveLayout = true;
		public static MainForm gMainForm;
		private IniFile ini = new IniFile(Program.SysPath + "Sys.ini");
		private DeserializeDockContent m_deserializeDockContent;
		private FrameParse gFrameParse = new FrameParse();
		private FormDataOpera gDataOpera = new FormDataOpera();
		public AddressList gAddressList = new AddressList();
		public FrameDisplay gFrameDisplay = new FrameDisplay();
		public NetReceive gNetReceive = new NetReceive();
		public FormDataParse gDataParse = new FormDataParse();
		public GB698Items gb698Items = new GB698Items();
		public GB698Opera gb698Opera = new GB698Opera();
		public FormCustomize gFormCustomize = new FormCustomize();
		public TimingTask gTimingTask = new TimingTask();
		public ActiveReport gActiveReport = new ActiveReport();
		public AF10F1 gAF10F1 = new AF10F1();
		public AF10F9 gAF10F9 = new AF10F9();
		private FormFactory gFrmOut = new FormFactory();
		private IContainer components = null;
		private ToolStripStatusLabel toolStripStatusLabel3;
		private ToolStripStatusLabel toolStripStatusLabel2;
		private ToolStripStatusLabel toolStripStatusLabel1;
		private StatusStrip statusStrip1;
		private ToolStripContentPanel ContentPanel;
		private ToolStripPanel LeftToolStripPanel;
		private ToolStripPanel RightToolStripPanel;
		private ToolStripPanel TopToolStripPanel;
		private ToolStripPanel BottomToolStripPanel;
		private ToolStripMenuItem f9转发主站直接对电表的抄读数据命令ToolStripMenuItem;
		private ToolStripSeparator toolStripMenuItem18;
		private ToolStripMenuItem f1透明转发ToolStripMenuItem1;
		private ToolStripSeparator toolStripSeparator5;
		private ToolStripSplitButton toolStripSplitButton1;
		private ToolStripMenuItem f9ToolStripMenuItem;
		private ToolStripMenuItem f68定时上报2类数据任务启动停止设置ToolStripMenuItem;
		private ToolStripMenuItem f67定时上报1类数据任务启动停止设置ToolStripMenuItem;
		private ToolStripMenuItem f66定时上报2类数据任务设置ToolStripMenuItem;
		private ToolStripMenuItem f65定时上报1类数据任务设置ToolStripMenuItem;
		private ToolStripSeparator toolStripMenuItem17;
		private ToolStripMenuItem f3主站IP地址和端口ToolStripMenuItem;
		private ToolStripSeparator toolStripMenuItem16;
		private ToolStripMenuItem f1终端上行通信口通信参数设置ToolStripMenuItem;
		private ToolStripSeparator toolStripMenuItem14;
		private ToolStripMenuItem f25当前三相及总有无功功率功率因数三相电压电流零序电流视在功率ToolStripMenuItem;
		private ToolStripMenuItem f1透明转发ToolStripMenuItem;
		private ToolStripMenuItem toolStripMenuItem15;
		private ToolStripSeparator toolStripMenuItem13;
		private ToolStripMenuItem 界面布局还原ToolStripMenuItem;
		private ToolStripSeparator toolStripMenuItem4;
		private ToolStripSeparator toolStripMenuItem12;
		private ToolStripMenuItem 有效性判断ToolStripMenuItem;
		private ToolStripSeparator toolStripMenuItem11;
		private ToolStripMenuItem eRC格式查询ToolStripMenuItem;
		private ToolStripMenuItem 格式查询ToolStripMenuItem;
		private ToolStripSeparator toolStripMenuItem10;
		private ToolStripMenuItem 帧结构ToolStripMenuItem;
		private ToolStripMenuItem hToolStripMenuItem;
		private ToolStripMenuItem f33终端抄表运行参数设置ToolStripMenuItem;
		private ToolStripSeparator toolStripMenuItem9;
		private ToolStripMenuItem f10终端电能表交流采样装置配置参数ToolStripMenuItem;
		private ToolStripSeparator toolStripMenuItem8;
		private ToolStripMenuItem 设置参数ToolStripMenuItem;
		private ToolStripMenuItem f136当前四象限无功电能示值ToolStripMenuItem;
		private ToolStripMenuItem f135当前三象限无功电能示值ToolStripMenuItem;
		private ToolStripMenuItem f134当前二象限无功电能示值ToolStripMenuItem;
		private ToolStripMenuItem f133当前一象限无功电能示值ToolStripMenuItem;
		private ToolStripMenuItem f132当前反向无功组合无功1电能示值ToolStripMenuItem;
		private ToolStripMenuItem f131当前反向有功电能示值ToolStripMenuItem;
		private ToolStripMenuItem f130当前正向无功组合无功1电能示值ToolStripMenuItem;
		private ToolStripMenuItem f129当前正向有功电能示值ToolStripMenuItem;
		private ToolStripMenuItem c请求1类数据117ToolStripMenuItem;
		private ToolStripSeparator toolStripMenuItem19;
		private ToolStripMenuItem f31对时命令ToolStripMenuItem;
		private ToolStripMenuItem 控制命令ToolStripMenuItem;
		private ToolStripSeparator toolStripMenuItem7;
		private ToolStripMenuItem f4参数除与系统主站通信有关的及全体数据区初始化ToolStripMenuItem;
		private ToolStripMenuItem f3参数及全体数据区初始化ToolStripMenuItem;
		private ToolStripMenuItem f2数据区初始化ToolStripMenuItem;
		private ToolStripMenuItem f1硬件初始化ToolStripMenuItem;
		private ToolStripMenuItem 复位命令ToolStripMenuItem;
		private ToolStripMenuItem 规约操作ToolStripMenuItem;
		private ToolStripSeparator toolStripMenuItem6;
		private ToolStripMenuItem 自定义规约删除ToolStripMenuItem;
		private ToolStripMenuItem 自定义规约添加ToolStripMenuItem;
		private ToolStripSeparator toolStripSeparator6;
		private ToolStripButton toolStripButton5;
		private ToolStripMenuItem 系统定时任务ToolStripMenuItem;
		private ToolStripSeparator toolStripMenuItem5;
		private ToolStripMenuItem 自定义规约测试ToolStripMenuItem;
		private ToolStripSeparator toolStripMenuItem1;
		private ToolStripMenuItem 系统帮助ToolStripMenuItem;
		private ToolStripSeparator toolStripSeparator4;
		private ToolStripButton toolStripButton4;
		private ToolStripSeparator toolStripSeparator3;
		private ToolStripButton toolStripButton2;
		private ToolStripSeparator toolStripSeparator2;
		private ToolStripButton toolStripButton1;
		private ToolStrip toolStrip1;
		private ToolStripSeparator toolStripSeparator1;
		private ToolStripButton toolStripButton3;
		private ToolStripMenuItem 数据查询ToolStripMenuItem;
		private ToolStripSeparator toolStripMenuItem3;
		
		private ToolStripMenuItem 帧解析ToolStripMenuItem;
		private ToolStripMenuItem 数据操作ToolStripMenuItem;
		private ToolStripMenuItem 系统帮组ToolStripMenuItem;
		private ToolStripMenuItem 抄读参数配置ToolStripMenuItem;
		private ToolStripSeparator toolStripMenuItem2;
		private ToolStripMenuItem 系统参数配置ToolStripMenuItem;
		private ToolStripMenuItem 系统配置ToolStripMenuItem;
		private MenuStrip menuStrip1;
		private ToolStripMenuItem 系统操作ToolStripMenuItem;
		private ToolStripSeparator toolStripMenuItem20;
		private ToolStripMenuItem 主动上报监控ToolStripMenuItem;
        private ToolStripMenuItem 网络服务ToolStripMenuItem;
		private DockPanel dockPanel;
		public MainForm()
		{
			MainForm.gMainForm = this;
			this.InitializeComponent();
			this.m_deserializeDockContent = new DeserializeDockContent(this.GetContentFromPersistString);
			
			
			Application.DoEvents();
			
			this.toolStripStatusLabel3.Text = Strings.Description + " ‖ Build:2012.2.23";
			Application.DoEvents();
		}
		private void InitUI()
		{
			this.gb698Items.Show(this.dockPanel, DockState.DockLeft);
			this.gAddressList.Show(this.gb698Items.Pane, DockAlignment.Bottom, 0.35);
			this.gFrameDisplay.Show(this.dockPanel, DockState.DockBottomAutoHide);
			this.gNetReceive.Show(this.dockPanel, DockState.DockBottomAutoHide);
			this.gDataParse.Show(this.dockPanel, DockState.DockBottomAutoHide);
			this.ShowGB698Opera();
		}
		private IDockContent GetContentFromPersistString(string persistString)
		{
			IDockContent result;
			if (persistString == typeof(AddressList).ToString())
			{
				result = this.gAddressList;
			}
			else
			{
				if (persistString == typeof(FrameDisplay).ToString())
				{
					result = this.gFrameDisplay;
				}
				else
				{
					if (persistString == typeof(NetReceive).ToString())
					{
						result = this.gNetReceive;
					}
					else
					{
						if (persistString == typeof(GB698Items).ToString())
						{
							result = this.gb698Items;
						}
						else
						{
							if (persistString == typeof(GB698Opera).ToString())
							{
								result = this.gb698Opera;
							}
							else
							{
								if (persistString == typeof(FormDataParse).ToString())
								{
									result = this.gDataParse;
								}
								else
								{
									if (persistString == typeof(FrameParse).ToString())
									{
										result = this.gFrameParse;
									}
									else
									{
										if (persistString == typeof(FormDataOpera).ToString())
										{
											result = this.gDataOpera;
										}
										else
										{
											if (persistString == typeof(TimingTask).ToString())
											{
												result = this.gTimingTask;
											}
											else
											{
												if (persistString == typeof(FormCustomize).ToString())
												{
													result = this.gFormCustomize;
												}
												else
												{
													if (persistString == typeof(AF10F1).ToString())
													{
														result = this.gAF10F1;
													}
													else
													{
														if (persistString == typeof(AF10F9).ToString())
														{
															result = this.gAF10F9;
														}
														else
														{
															if (persistString == typeof(ActiveReport).ToString())
															{
																result = this.gActiveReport;
															}
															else
															{
																GB698Opera gB698Opera = new GB698Opera();
																result = gB698Opera;
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			return result;
		}
		private void ShowActiveReport()
		{
			this.gActiveReport = new ActiveReport();
			if (this.dockPanel.DocumentStyle == DocumentStyle.SystemMdi)
			{
				this.gActiveReport.MdiParent = this;
				this.gActiveReport.Show();
			}
			else
			{
				this.gActiveReport.Show(this.dockPanel);
			}
			Application.DoEvents();
		}
		private void ShowGB698Opera()
		{
			if (this.dockPanel.DocumentStyle == DocumentStyle.SystemMdi)
			{
				this.gb698Opera.MdiParent = this;
				this.gb698Opera.Show();
			}
			else
			{
				this.gb698Opera.Show(this.dockPanel);
			}
			Application.DoEvents();
		}
		private void ShowAF10F1()
		{
			this.gAF10F1 = new AF10F1();
			if (this.dockPanel.DocumentStyle == DocumentStyle.SystemMdi)
			{
				this.gAF10F1.MdiParent = this;
				this.gAF10F1.Show();
			}
			else
			{
				this.gAF10F1.Show(this.dockPanel);
			}
			Application.DoEvents();
		}
		private void ShowAF10F9()
		{
			this.gAF10F9 = new AF10F9();
			if (this.dockPanel.DocumentStyle == DocumentStyle.SystemMdi)
			{
				this.gAF10F9.MdiParent = this;
				this.gAF10F9.Show();
			}
			else
			{
				this.gAF10F9.Show(this.dockPanel);
			}
			Application.DoEvents();
		}
		private void ShowTimingTask()
		{
			this.gTimingTask = new TimingTask();
			if (this.dockPanel.DocumentStyle == DocumentStyle.SystemMdi)
			{
				this.gTimingTask.MdiParent = this;
				this.gTimingTask.Show();
			}
			else
			{
				this.gTimingTask.Show(this.dockPanel);
			}
			Application.DoEvents();
		}
		private void ShowFrameParse()
		{
			this.gFrameParse = new FrameParse();
			if (this.dockPanel.DocumentStyle == DocumentStyle.SystemMdi)
			{
				this.gFrameParse.MdiParent = this;
				this.gFrameParse.Show();
			}
			else
			{
				this.gFrameParse.Show(this.dockPanel);
			}
			Application.DoEvents();
		}
		private void ShowDataOpera()
		{
			this.gDataOpera = new FormDataOpera();
			if (this.dockPanel.DocumentStyle == DocumentStyle.SystemMdi)
			{
				this.gDataOpera.MdiParent = this;
				this.gDataOpera.Show();
			}
			else
			{
				this.gDataOpera.Show(this.dockPanel);
			}
			Application.DoEvents();
		}
		private void ShowCustomize()
		{
			this.gFormCustomize = new FormCustomize();
			if (this.dockPanel.DocumentStyle == DocumentStyle.SystemMdi)
			{
				this.gFormCustomize.MdiParent = this;
				this.gFormCustomize.Show();
			}
			else
			{
				this.gFormCustomize.Show(this.dockPanel);
			}
			Application.DoEvents();
		}
		private void 系统参数配置ToolStripMenuItemClick(object sender, EventArgs e)
		{
			UCNetSysConfig sysConfig = new UCNetSysConfig();
			sysConfig.Show();
		}
		private void 抄读参数配置ToolStripMenuItemClick(object sender, EventArgs e)
		{
			FormSysConst sysConst = new FormSysConst();
			sysConst.Show();
		}
		private void 有效性判断ToolStripMenuItemClick(object sender, EventArgs e)
		{
			FormSysAssert sysAssert = new FormSysAssert();
			sysAssert.Show();
		}
		private void 文件传输ToolStripMenuItemClick(object sender, EventArgs e)
		{
			new AFN0F_01
			{
				gDelay = Program.gDelay,
				gComPort = Program.gComPort,
				gCommSetting = Program.gCommSetting,
                gType = ComunicationType.Serial,
				CID = Program.CID,
				Tp = Program.Tp,
				PW = Program.PW,
				Flag = Program.Flag
			}.Show();
		}
		private void 帧解析ToolStripMenuItemClick(object sender, EventArgs e)
		{
			this.ShowFrameParse();
		}
		private void 数据查询ToolStripMenuItemClick(object sender, EventArgs e)
		{
			this.ShowDataOpera();
		}
		private void 主动上报监控ToolStripMenuItem_Click(object sender, EventArgs e)
		{
			this.ShowActiveReport();
		}
		private void 系统定时任务ToolStripMenuItemClick(object sender, EventArgs e)
		{
			this.ShowTimingTask();
		}
		private void ToolStripButton5Click(object sender, EventArgs e)
		{
			this.ShowTimingTask();
		}
		
		private void 系统帮助ToolStripMenuItemClick(object sender, EventArgs e)
		{
			string text = Program.SysPath + "help.doc";
			if (File.Exists(text))
			{
				Process.Start(text);
			}
			else
			{
				MessageBox.Show("目录下缺少帮助文件 help.doc", "提示", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
			}
		}
		private void HToolStripMenuItemClick(object sender, EventArgs e)
		{
			this.系统帮助ToolStripMenuItemClick(sender, e);
		}
		private void ToolStripButton4Click(object sender, EventArgs e)
		{
			this.ShowDataOpera();
		}
		private void ToolStripButton2Click(object sender, EventArgs e)
		{
			this.ShowFrameParse();
		}
		private void 自定义规约测试ToolStripMenuItemClick(object sender, EventArgs e)
		{
			this.ShowCustomize();
		}
		private void ToolStripButton1Click(object sender, EventArgs e)
		{
			FormSysConst sysConst = new FormSysConst();
			sysConst.Show();
		}
		private void 界面布局还原ToolStripMenuItemClick(object sender, EventArgs e)
		{
			this.m_bSaveLayout = false;
			if (MessageBox.Show("系统将会在下次登录时还原默认布局,是否现在重启?", "警告", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes)
			{
				Application.Restart();
			}
		}
		private void 自定义规约添加ToolStripMenuItemClick(object sender, EventArgs e)
		{
			FormCustomizeAdd customizeAdd = new FormCustomizeAdd();
			customizeAdd.ShowDialog();
		}
		private void 自定义规约删除ToolStripMenuItemClick(object sender, EventArgs e)
		{
			CustomizeDel customizeDel = new CustomizeDel();
			customizeDel.ShowDialog();
		}
		private void ToolStripButton3Click(object sender, EventArgs e)
		{
			UCNetSysConfig sysConfig = new UCNetSysConfig();
			sysConfig.Show();
		}
		private void ERC格式查询ToolStripMenuItemClick(object sender, EventArgs e)
		{
			//HelpFrm helpFrm = new HelpFrm();
			//byte[] mbyte = RelaseRes.Release("ERC");
			//helpFrm.ShowHelp(mbyte);
			//helpFrm.Show();
		}
		private void 格式查询ToolStripMenuItemClick(object sender, EventArgs e)
		{
			//HelpFrm helpFrm = new HelpFrm();
			//byte[] mbyte = RelaseRes.Release("Appendix");
			//helpFrm.ShowHelp(mbyte);
			//helpFrm.Show();
		}
		private void 帧结构ToolStripMenuItemClick(object sender, EventArgs e)
		{
			//byte[] mbyte = RelaseRes.Release("Frame");
			//HelpFrm helpFrm = new HelpFrm();
			//helpFrm.ShowHelp(mbyte);
			//helpFrm.Show();
		}
		private void MainFormLoad(object sender, EventArgs e)
		{
			string text = Path.Combine(Path.GetDirectoryName(Application.ExecutablePath), "Config.xml");
			this.dockPanel.SuspendLayout(true);
			if (File.Exists(text))
			{
				this.dockPanel.LoadFromXml(text, this.m_deserializeDockContent);
			}
			this.dockPanel.ResumeLayout(true, true);
		}
		private void MainFormFormClosing(object sender, FormClosingEventArgs e)
		{
			Program.CheckClients = false;
			Program.CanShowText = false;
			string text = Path.Combine(Path.GetDirectoryName(Application.ExecutablePath), "Config.xml");
			if (this.m_bSaveLayout)
			{
				this.dockPanel.SaveAsXml(text);
			}
			else
			{
				if (File.Exists(text))
				{
					File.Delete(text);
				}
			}
			Application.DoEvents();
			try
			{
			}
			catch
			{
			}
		}
		private void F1硬件初始化ToolStripMenuItemClick(object sender, EventArgs e)
		{
			OtherOpera.ReadAndWrite("01", "0001", "");
		}
		private void F2数据区初始化ToolStripMenuItemClick(object sender, EventArgs e)
		{
			OtherOpera.ReadAndWrite("01", "0002", "");
		}
		private void F3参数及全体数据区初始化ToolStripMenuItemClick(object sender, EventArgs e)
		{
			OtherOpera.ReadAndWrite("01", "0003", "");
		}
		private void F4参数除与系统主站通信有关的及全体数据区初始化ToolStripMenuItemClick(object sender, EventArgs e)
		{
			OtherOpera.ReadAndWrite("01", "0004", "");
		}
		private void F1终端上行通信口通信参数设置ToolStripMenuItemClick(object sender, EventArgs e)
		{
			OtherOpera.ReadAndWrite("04", "0001", this.gFrmOut.CreateForm("04", "0001", ""));
		}
		private void F3主站IP地址和端口ToolStripMenuItemClick(object sender, EventArgs e)
		{
			OtherOpera.ReadAndWrite("04", "0003", this.gFrmOut.CreateForm("04", "0003", ""));
		}
		private void F10终端电能表交流采样装置配置参数ToolStripMenuItemClick(object sender, EventArgs e)
		{
			OtherOpera.ReadAndWrite("04", "0010", this.gFrmOut.CreateForm("04", "0010", ""));
		}
		private void F33终端抄表运行参数设置ToolStripMenuItemClick(object sender, EventArgs e)
		{
			OtherOpera.ReadAndWrite("04", "0033", this.gFrmOut.CreateForm("04", "0033", ""));
		}
		private void F65定时上报1类数据任务设置ToolStripMenuItemClick(object sender, EventArgs e)
		{
			OtherOpera.ReadAndWrite("04", "0065", this.gFrmOut.CreateForm("04", "0065", ""));
		}
		private void F66定时上报2类数据任务设置ToolStripMenuItemClick(object sender, EventArgs e)
		{
			OtherOpera.ReadAndWrite("04", "0066", this.gFrmOut.CreateForm("04", "0066", ""));
		}
		private void F67定时上报1类数据任务启动停止设置ToolStripMenuItemClick(object sender, EventArgs e)
		{
			OtherOpera.ReadAndWrite("04", "0067", this.gFrmOut.CreateForm("04", "0067", ""));
		}
		private void F68定时上报2类数据任务启动停止设置ToolStripMenuItemClick(object sender, EventArgs e)
		{
			OtherOpera.ReadAndWrite("04", "0068", this.gFrmOut.CreateForm("04", "0068", ""));
		}
		private void F31对时命令ToolStripMenuItemClick(object sender, EventArgs e)
		{
			OtherOpera.ReadAndWrite("05", "0031", "");
		}
		private void F25当前三相及总有无功功率功率因数三相电压电流零序电流视在功率ToolStripMenuItemClick(object sender, EventArgs e)
		{
			OtherOpera.ReadAndWrite("0C", "0025", "");
		}
		private void F129当前正向有功电能示值ToolStripMenuItemClick(object sender, EventArgs e)
		{
			OtherOpera.ReadAndWrite("0C", "0129", "");
		}
		private void F130当前正向无功组合无功1电能示值ToolStripMenuItemClick(object sender, EventArgs e)
		{
			OtherOpera.ReadAndWrite("0C", "0130", "");
		}
		private void F131当前反向有功电能示值ToolStripMenuItemClick(object sender, EventArgs e)
		{
			OtherOpera.ReadAndWrite("0C", "0131", "");
		}
		private void F132当前反向无功组合无功1电能示值ToolStripMenuItemClick(object sender, EventArgs e)
		{
			OtherOpera.ReadAndWrite("0C", "0132", "");
		}
		private void F133当前一象限无功电能示值ToolStripMenuItemClick(object sender, EventArgs e)
		{
			OtherOpera.ReadAndWrite("0C", "0133", "");
		}
		private void F134当前二象限无功电能示值ToolStripMenuItemClick(object sender, EventArgs e)
		{
			OtherOpera.ReadAndWrite("0C", "0134", "");
		}
		private void F135当前三象限无功电能示值ToolStripMenuItemClick(object sender, EventArgs e)
		{
			OtherOpera.ReadAndWrite("0C", "0135", "");
		}
		private void F136当前四象限无功电能示值ToolStripMenuItemClick(object sender, EventArgs e)
		{
			OtherOpera.ReadAndWrite("0C", "0136", "");
		}
		private void F1透明转发ToolStripMenuItemClick(object sender, EventArgs e)
		{
			this.ShowAF10F1();
		}
		private void F9ToolStripMenuItemClick(object sender, EventArgs e)
		{
			this.ShowAF10F9();
		}
		private void F1透明转发ToolStripMenuItem1Click(object sender, EventArgs e)
		{
			this.ShowAF10F1();
		}
		private void F9转发主站直接对电表的抄读数据命令ToolStripMenuItemClick(object sender, EventArgs e)
		{
			this.ShowAF10F9();
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
            WinFormsUI.Docking.DockPanelSkin dockPanelSkin1 = new WinFormsUI.Docking.DockPanelSkin();
            WinFormsUI.Docking.AutoHideStripSkin autoHideStripSkin1 = new WinFormsUI.Docking.AutoHideStripSkin();
            WinFormsUI.Docking.DockPanelGradient dockPanelGradient1 = new WinFormsUI.Docking.DockPanelGradient();
            WinFormsUI.Docking.TabGradient tabGradient1 = new WinFormsUI.Docking.TabGradient();
            WinFormsUI.Docking.DockPaneStripSkin dockPaneStripSkin1 = new WinFormsUI.Docking.DockPaneStripSkin();
            WinFormsUI.Docking.DockPaneStripGradient dockPaneStripGradient1 = new WinFormsUI.Docking.DockPaneStripGradient();
            WinFormsUI.Docking.TabGradient tabGradient2 = new WinFormsUI.Docking.TabGradient();
            WinFormsUI.Docking.DockPanelGradient dockPanelGradient2 = new WinFormsUI.Docking.DockPanelGradient();
            WinFormsUI.Docking.TabGradient tabGradient3 = new WinFormsUI.Docking.TabGradient();
            WinFormsUI.Docking.DockPaneStripToolWindowGradient dockPaneStripToolWindowGradient1 = new WinFormsUI.Docking.DockPaneStripToolWindowGradient();
            WinFormsUI.Docking.TabGradient tabGradient4 = new WinFormsUI.Docking.TabGradient();
            WinFormsUI.Docking.TabGradient tabGradient5 = new WinFormsUI.Docking.TabGradient();
            WinFormsUI.Docking.DockPanelGradient dockPanelGradient3 = new WinFormsUI.Docking.DockPanelGradient();
            WinFormsUI.Docking.TabGradient tabGradient6 = new WinFormsUI.Docking.TabGradient();
            WinFormsUI.Docking.TabGradient tabGradient7 = new WinFormsUI.Docking.TabGradient();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.系统配置ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.系统参数配置ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripSeparator();
            this.抄读参数配置ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem12 = new System.Windows.Forms.ToolStripSeparator();
            this.有效性判断ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem4 = new System.Windows.Forms.ToolStripSeparator();
            this.界面布局还原ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.系统操作ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.自定义规约测试ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem6 = new System.Windows.Forms.ToolStripSeparator();
            this.自定义规约添加ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.自定义规约删除ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem5 = new System.Windows.Forms.ToolStripSeparator();
            this.系统定时任务ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem20 = new System.Windows.Forms.ToolStripSeparator();
            this.主动上报监控ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.规约操作ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.复位命令ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.f1硬件初始化ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.f2数据区初始化ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.f3参数及全体数据区初始化ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.f4参数除与系统主站通信有关的及全体数据区初始化ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem7 = new System.Windows.Forms.ToolStripSeparator();
            this.设置参数ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.f1终端上行通信口通信参数设置ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.f3主站IP地址和端口ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem16 = new System.Windows.Forms.ToolStripSeparator();
            this.f10终端电能表交流采样装置配置参数ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem9 = new System.Windows.Forms.ToolStripSeparator();
            this.f33终端抄表运行参数设置ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem17 = new System.Windows.Forms.ToolStripSeparator();
            this.f65定时上报1类数据任务设置ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.f66定时上报2类数据任务设置ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.f67定时上报1类数据任务启动停止设置ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.f68定时上报2类数据任务启动停止设置ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem8 = new System.Windows.Forms.ToolStripSeparator();
            this.控制命令ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.f31对时命令ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem19 = new System.Windows.Forms.ToolStripSeparator();
            this.c请求1类数据117ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.f25当前三相及总有无功功率功率因数三相电压电流零序电流视在功率ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem14 = new System.Windows.Forms.ToolStripSeparator();
            this.f129当前正向有功电能示值ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.f130当前正向无功组合无功1电能示值ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.f131当前反向有功电能示值ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.f132当前反向无功组合无功1电能示值ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.f133当前一象限无功电能示值ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.f134当前二象限无功电能示值ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.f135当前三象限无功电能示值ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.f136当前四象限无功电能示值ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem13 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripMenuItem15 = new System.Windows.Forms.ToolStripMenuItem();
            this.f1透明转发ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.f9ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.数据操作ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.帧解析ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem3 = new System.Windows.Forms.ToolStripSeparator();
            this.数据查询ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem10 = new System.Windows.Forms.ToolStripSeparator();
            this.帧结构ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem11 = new System.Windows.Forms.ToolStripSeparator();
            this.格式查询ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.eRC格式查询ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.系统帮组ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.系统帮助ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            
            this.hToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripButton3 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.toolStripButton1 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton2 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton4 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton5 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator6 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripSplitButton1 = new System.Windows.Forms.ToolStripSplitButton();
            this.f1透明转发ToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem18 = new System.Windows.Forms.ToolStripSeparator();
            this.f9转发主站直接对电表的抄读数据命令ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator5 = new System.Windows.Forms.ToolStripSeparator();
            this.BottomToolStripPanel = new System.Windows.Forms.ToolStripPanel();
            this.TopToolStripPanel = new System.Windows.Forms.ToolStripPanel();
            this.RightToolStripPanel = new System.Windows.Forms.ToolStripPanel();
            this.LeftToolStripPanel = new System.Windows.Forms.ToolStripPanel();
            this.ContentPanel = new System.Windows.Forms.ToolStripContentPanel();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel2 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel3 = new System.Windows.Forms.ToolStripStatusLabel();
            this.dockPanel = new WinFormsUI.Docking.DockPanel();
            this.网络服务ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.toolStrip1.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.系统配置ToolStripMenuItem,
            this.系统操作ToolStripMenuItem,
            this.规约操作ToolStripMenuItem,
            this.数据操作ToolStripMenuItem,
            this.系统帮组ToolStripMenuItem,
            this.hToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(516, 24);
            this.menuStrip1.TabIndex = 3;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // 系统配置ToolStripMenuItem
            // 
            this.系统配置ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.系统参数配置ToolStripMenuItem,
            this.toolStripMenuItem2,
            this.抄读参数配置ToolStripMenuItem,
            this.toolStripMenuItem12,
            this.有效性判断ToolStripMenuItem,
            this.toolStripMenuItem4,
            this.界面布局还原ToolStripMenuItem,
            this.网络服务ToolStripMenuItem});
            this.系统配置ToolStripMenuItem.Name = "系统配置ToolStripMenuItem";
            this.系统配置ToolStripMenuItem.Size = new System.Drawing.Size(67, 20);
            this.系统配置ToolStripMenuItem.Text = "系统配置";
            // 
            // 系统参数配置ToolStripMenuItem
            // 
            this.系统参数配置ToolStripMenuItem.Name = "系统参数配置ToolStripMenuItem";
            this.系统参数配置ToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.系统参数配置ToolStripMenuItem.Text = "系统参数设置";
            this.系统参数配置ToolStripMenuItem.Click += new System.EventHandler(this.系统参数配置ToolStripMenuItemClick);
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(149, 6);
            // 
            // 抄读参数配置ToolStripMenuItem
            // 
            this.抄读参数配置ToolStripMenuItem.Name = "抄读参数配置ToolStripMenuItem";
            this.抄读参数配置ToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.抄读参数配置ToolStripMenuItem.Text = "抄读参数设置";
            this.抄读参数配置ToolStripMenuItem.Click += new System.EventHandler(this.抄读参数配置ToolStripMenuItemClick);
            // 
            // toolStripMenuItem12
            // 
            this.toolStripMenuItem12.Name = "toolStripMenuItem12";
            this.toolStripMenuItem12.Size = new System.Drawing.Size(149, 6);
            // 
            // 有效性判断ToolStripMenuItem
            // 
            this.有效性判断ToolStripMenuItem.Name = "有效性判断ToolStripMenuItem";
            this.有效性判断ToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.有效性判断ToolStripMenuItem.Text = "帧有效性判断";
            this.有效性判断ToolStripMenuItem.Click += new System.EventHandler(this.有效性判断ToolStripMenuItemClick);
            // 
            // toolStripMenuItem4
            // 
            this.toolStripMenuItem4.Name = "toolStripMenuItem4";
            this.toolStripMenuItem4.Size = new System.Drawing.Size(149, 6);
            // 
            // 界面布局还原ToolStripMenuItem
            // 
            this.界面布局还原ToolStripMenuItem.Name = "界面布局还原ToolStripMenuItem";
            this.界面布局还原ToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.界面布局还原ToolStripMenuItem.Text = "界面布局还原";
            this.界面布局还原ToolStripMenuItem.Click += new System.EventHandler(this.界面布局还原ToolStripMenuItemClick);
            // 
            // 系统操作ToolStripMenuItem
            // 
            this.系统操作ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.自定义规约测试ToolStripMenuItem,
            this.toolStripMenuItem6,
            this.自定义规约添加ToolStripMenuItem,
            this.自定义规约删除ToolStripMenuItem,
            this.toolStripMenuItem5,
            this.系统定时任务ToolStripMenuItem,
            this.toolStripMenuItem20,
            this.主动上报监控ToolStripMenuItem});
            this.系统操作ToolStripMenuItem.Name = "系统操作ToolStripMenuItem";
            this.系统操作ToolStripMenuItem.Size = new System.Drawing.Size(67, 20);
            this.系统操作ToolStripMenuItem.Text = "系统操作";
            // 
            // 自定义规约测试ToolStripMenuItem
            // 
            this.自定义规约测试ToolStripMenuItem.Name = "自定义规约测试ToolStripMenuItem";
            this.自定义规约测试ToolStripMenuItem.Size = new System.Drawing.Size(158, 22);
            this.自定义规约测试ToolStripMenuItem.Text = "自定义规约测试";
            this.自定义规约测试ToolStripMenuItem.Click += new System.EventHandler(this.自定义规约测试ToolStripMenuItemClick);
            // 
            // toolStripMenuItem6
            // 
            this.toolStripMenuItem6.Name = "toolStripMenuItem6";
            this.toolStripMenuItem6.Size = new System.Drawing.Size(155, 6);
            // 
            // 自定义规约添加ToolStripMenuItem
            // 
            this.自定义规约添加ToolStripMenuItem.Name = "自定义规约添加ToolStripMenuItem";
            this.自定义规约添加ToolStripMenuItem.Size = new System.Drawing.Size(158, 22);
            this.自定义规约添加ToolStripMenuItem.Text = "自定义规约添加";
            this.自定义规约添加ToolStripMenuItem.Click += new System.EventHandler(this.自定义规约添加ToolStripMenuItemClick);
            // 
            // 自定义规约删除ToolStripMenuItem
            // 
            this.自定义规约删除ToolStripMenuItem.Name = "自定义规约删除ToolStripMenuItem";
            this.自定义规约删除ToolStripMenuItem.Size = new System.Drawing.Size(158, 22);
            this.自定义规约删除ToolStripMenuItem.Text = "自定义规约删除";
            this.自定义规约删除ToolStripMenuItem.Click += new System.EventHandler(this.自定义规约删除ToolStripMenuItemClick);
            // 
            // toolStripMenuItem5
            // 
            this.toolStripMenuItem5.Name = "toolStripMenuItem5";
            this.toolStripMenuItem5.Size = new System.Drawing.Size(155, 6);
            // 
            // 系统定时任务ToolStripMenuItem
            // 
            this.系统定时任务ToolStripMenuItem.Name = "系统定时任务ToolStripMenuItem";
            this.系统定时任务ToolStripMenuItem.Size = new System.Drawing.Size(158, 22);
            this.系统定时任务ToolStripMenuItem.Text = "系统定时任务";
            this.系统定时任务ToolStripMenuItem.Click += new System.EventHandler(this.系统定时任务ToolStripMenuItemClick);
            // 
            // toolStripMenuItem20
            // 
            this.toolStripMenuItem20.Name = "toolStripMenuItem20";
            this.toolStripMenuItem20.Size = new System.Drawing.Size(155, 6);
            // 
            // 主动上报监控ToolStripMenuItem
            // 
            this.主动上报监控ToolStripMenuItem.Name = "主动上报监控ToolStripMenuItem";
            this.主动上报监控ToolStripMenuItem.Size = new System.Drawing.Size(158, 22);
            this.主动上报监控ToolStripMenuItem.Text = "主动上报监控";
            this.主动上报监控ToolStripMenuItem.Click += new System.EventHandler(this.主动上报监控ToolStripMenuItem_Click);
            // 
            // 规约操作ToolStripMenuItem
            // 
            this.规约操作ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.复位命令ToolStripMenuItem,
            this.toolStripMenuItem7,
            this.设置参数ToolStripMenuItem,
            this.toolStripMenuItem8,
            this.控制命令ToolStripMenuItem,
            this.toolStripMenuItem19,
            this.c请求1类数据117ToolStripMenuItem,
            this.toolStripMenuItem13,
            this.toolStripMenuItem15});
            this.规约操作ToolStripMenuItem.Name = "规约操作ToolStripMenuItem";
            this.规约操作ToolStripMenuItem.Size = new System.Drawing.Size(67, 20);
            this.规约操作ToolStripMenuItem.Text = "规约操作";
            // 
            // 复位命令ToolStripMenuItem
            // 
            this.复位命令ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.f1硬件初始化ToolStripMenuItem,
            this.f2数据区初始化ToolStripMenuItem,
            this.f3参数及全体数据区初始化ToolStripMenuItem,
            this.f4参数除与系统主站通信有关的及全体数据区初始化ToolStripMenuItem});
            this.复位命令ToolStripMenuItem.Name = "复位命令ToolStripMenuItem";
            this.复位命令ToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
            this.复位命令ToolStripMenuItem.Text = "[01]复位命令";
            // 
            // f1硬件初始化ToolStripMenuItem
            // 
            this.f1硬件初始化ToolStripMenuItem.Name = "f1硬件初始化ToolStripMenuItem";
            this.f1硬件初始化ToolStripMenuItem.Size = new System.Drawing.Size(361, 22);
            this.f1硬件初始化ToolStripMenuItem.Text = "F1 硬件初始化";
            this.f1硬件初始化ToolStripMenuItem.Click += new System.EventHandler(this.F1硬件初始化ToolStripMenuItemClick);
            // 
            // f2数据区初始化ToolStripMenuItem
            // 
            this.f2数据区初始化ToolStripMenuItem.Name = "f2数据区初始化ToolStripMenuItem";
            this.f2数据区初始化ToolStripMenuItem.Size = new System.Drawing.Size(361, 22);
            this.f2数据区初始化ToolStripMenuItem.Text = "F2 数据区初始化";
            this.f2数据区初始化ToolStripMenuItem.Click += new System.EventHandler(this.F2数据区初始化ToolStripMenuItemClick);
            // 
            // f3参数及全体数据区初始化ToolStripMenuItem
            // 
            this.f3参数及全体数据区初始化ToolStripMenuItem.Name = "f3参数及全体数据区初始化ToolStripMenuItem";
            this.f3参数及全体数据区初始化ToolStripMenuItem.Size = new System.Drawing.Size(361, 22);
            this.f3参数及全体数据区初始化ToolStripMenuItem.Text = "F3 参数及全体数据区初始化";
            this.f3参数及全体数据区初始化ToolStripMenuItem.Click += new System.EventHandler(this.F3参数及全体数据区初始化ToolStripMenuItemClick);
            // 
            // f4参数除与系统主站通信有关的及全体数据区初始化ToolStripMenuItem
            // 
            this.f4参数除与系统主站通信有关的及全体数据区初始化ToolStripMenuItem.Name = "f4参数除与系统主站通信有关的及全体数据区初始化ToolStripMenuItem";
            this.f4参数除与系统主站通信有关的及全体数据区初始化ToolStripMenuItem.Size = new System.Drawing.Size(361, 22);
            this.f4参数除与系统主站通信有关的及全体数据区初始化ToolStripMenuItem.Text = "F4 参数(除与系统主站通信有关的)及全体数据区初始化";
            this.f4参数除与系统主站通信有关的及全体数据区初始化ToolStripMenuItem.Click += new System.EventHandler(this.F4参数除与系统主站通信有关的及全体数据区初始化ToolStripMenuItemClick);
            // 
            // toolStripMenuItem7
            // 
            this.toolStripMenuItem7.Name = "toolStripMenuItem7";
            this.toolStripMenuItem7.Size = new System.Drawing.Size(159, 6);
            // 
            // 设置参数ToolStripMenuItem
            // 
            this.设置参数ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.f1终端上行通信口通信参数设置ToolStripMenuItem,
            this.f3主站IP地址和端口ToolStripMenuItem,
            this.toolStripMenuItem16,
            this.f10终端电能表交流采样装置配置参数ToolStripMenuItem,
            this.toolStripMenuItem9,
            this.f33终端抄表运行参数设置ToolStripMenuItem,
            this.toolStripMenuItem17,
            this.f65定时上报1类数据任务设置ToolStripMenuItem,
            this.f66定时上报2类数据任务设置ToolStripMenuItem,
            this.f67定时上报1类数据任务启动停止设置ToolStripMenuItem,
            this.f68定时上报2类数据任务启动停止设置ToolStripMenuItem});
            this.设置参数ToolStripMenuItem.Name = "设置参数ToolStripMenuItem";
            this.设置参数ToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
            this.设置参数ToolStripMenuItem.Text = "[04]设置参数";
            // 
            // f1终端上行通信口通信参数设置ToolStripMenuItem
            // 
            this.f1终端上行通信口通信参数设置ToolStripMenuItem.Name = "f1终端上行通信口通信参数设置ToolStripMenuItem";
            this.f1终端上行通信口通信参数设置ToolStripMenuItem.Size = new System.Drawing.Size(286, 22);
            this.f1终端上行通信口通信参数设置ToolStripMenuItem.Text = "F1 终端上行通信口通信参数设置";
            this.f1终端上行通信口通信参数设置ToolStripMenuItem.Click += new System.EventHandler(this.F1终端上行通信口通信参数设置ToolStripMenuItemClick);
            // 
            // f3主站IP地址和端口ToolStripMenuItem
            // 
            this.f3主站IP地址和端口ToolStripMenuItem.Name = "f3主站IP地址和端口ToolStripMenuItem";
            this.f3主站IP地址和端口ToolStripMenuItem.Size = new System.Drawing.Size(286, 22);
            this.f3主站IP地址和端口ToolStripMenuItem.Text = "F3 主站IP地址和端口";
            this.f3主站IP地址和端口ToolStripMenuItem.Click += new System.EventHandler(this.F3主站IP地址和端口ToolStripMenuItemClick);
            // 
            // toolStripMenuItem16
            // 
            this.toolStripMenuItem16.Name = "toolStripMenuItem16";
            this.toolStripMenuItem16.Size = new System.Drawing.Size(283, 6);
            // 
            // f10终端电能表交流采样装置配置参数ToolStripMenuItem
            // 
            this.f10终端电能表交流采样装置配置参数ToolStripMenuItem.Name = "f10终端电能表交流采样装置配置参数ToolStripMenuItem";
            this.f10终端电能表交流采样装置配置参数ToolStripMenuItem.Size = new System.Drawing.Size(286, 22);
            this.f10终端电能表交流采样装置配置参数ToolStripMenuItem.Text = "F10 终端电能表/交流采样装置配置参数";
            this.f10终端电能表交流采样装置配置参数ToolStripMenuItem.Click += new System.EventHandler(this.F10终端电能表交流采样装置配置参数ToolStripMenuItemClick);
            // 
            // toolStripMenuItem9
            // 
            this.toolStripMenuItem9.Name = "toolStripMenuItem9";
            this.toolStripMenuItem9.Size = new System.Drawing.Size(283, 6);
            // 
            // f33终端抄表运行参数设置ToolStripMenuItem
            // 
            this.f33终端抄表运行参数设置ToolStripMenuItem.Name = "f33终端抄表运行参数设置ToolStripMenuItem";
            this.f33终端抄表运行参数设置ToolStripMenuItem.Size = new System.Drawing.Size(286, 22);
            this.f33终端抄表运行参数设置ToolStripMenuItem.Text = "F33 终端抄表运行参数设置";
            this.f33终端抄表运行参数设置ToolStripMenuItem.Click += new System.EventHandler(this.F33终端抄表运行参数设置ToolStripMenuItemClick);
            // 
            // toolStripMenuItem17
            // 
            this.toolStripMenuItem17.Name = "toolStripMenuItem17";
            this.toolStripMenuItem17.Size = new System.Drawing.Size(283, 6);
            // 
            // f65定时上报1类数据任务设置ToolStripMenuItem
            // 
            this.f65定时上报1类数据任务设置ToolStripMenuItem.Name = "f65定时上报1类数据任务设置ToolStripMenuItem";
            this.f65定时上报1类数据任务设置ToolStripMenuItem.Size = new System.Drawing.Size(286, 22);
            this.f65定时上报1类数据任务设置ToolStripMenuItem.Text = "F65 定时上报1类数据任务设置";
            this.f65定时上报1类数据任务设置ToolStripMenuItem.Click += new System.EventHandler(this.F65定时上报1类数据任务设置ToolStripMenuItemClick);
            // 
            // f66定时上报2类数据任务设置ToolStripMenuItem
            // 
            this.f66定时上报2类数据任务设置ToolStripMenuItem.Name = "f66定时上报2类数据任务设置ToolStripMenuItem";
            this.f66定时上报2类数据任务设置ToolStripMenuItem.Size = new System.Drawing.Size(286, 22);
            this.f66定时上报2类数据任务设置ToolStripMenuItem.Text = "F66 定时上报2类数据任务设置";
            this.f66定时上报2类数据任务设置ToolStripMenuItem.Click += new System.EventHandler(this.F66定时上报2类数据任务设置ToolStripMenuItemClick);
            // 
            // f67定时上报1类数据任务启动停止设置ToolStripMenuItem
            // 
            this.f67定时上报1类数据任务启动停止设置ToolStripMenuItem.Name = "f67定时上报1类数据任务启动停止设置ToolStripMenuItem";
            this.f67定时上报1类数据任务启动停止设置ToolStripMenuItem.Size = new System.Drawing.Size(286, 22);
            this.f67定时上报1类数据任务启动停止设置ToolStripMenuItem.Text = "F67 定时上报1类数据任务启动/停止设置";
            this.f67定时上报1类数据任务启动停止设置ToolStripMenuItem.Click += new System.EventHandler(this.F67定时上报1类数据任务启动停止设置ToolStripMenuItemClick);
            // 
            // f68定时上报2类数据任务启动停止设置ToolStripMenuItem
            // 
            this.f68定时上报2类数据任务启动停止设置ToolStripMenuItem.Name = "f68定时上报2类数据任务启动停止设置ToolStripMenuItem";
            this.f68定时上报2类数据任务启动停止设置ToolStripMenuItem.Size = new System.Drawing.Size(286, 22);
            this.f68定时上报2类数据任务启动停止设置ToolStripMenuItem.Text = "F68 定时上报2类数据任务启动/停止设置";
            this.f68定时上报2类数据任务启动停止设置ToolStripMenuItem.Click += new System.EventHandler(this.F68定时上报2类数据任务启动停止设置ToolStripMenuItemClick);
            // 
            // toolStripMenuItem8
            // 
            this.toolStripMenuItem8.Name = "toolStripMenuItem8";
            this.toolStripMenuItem8.Size = new System.Drawing.Size(159, 6);
            // 
            // 控制命令ToolStripMenuItem
            // 
            this.控制命令ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.f31对时命令ToolStripMenuItem});
            this.控制命令ToolStripMenuItem.Name = "控制命令ToolStripMenuItem";
            this.控制命令ToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
            this.控制命令ToolStripMenuItem.Text = "[05]控制命令";
            // 
            // f31对时命令ToolStripMenuItem
            // 
            this.f31对时命令ToolStripMenuItem.Name = "f31对时命令ToolStripMenuItem";
            this.f31对时命令ToolStripMenuItem.Size = new System.Drawing.Size(143, 22);
            this.f31对时命令ToolStripMenuItem.Text = "F31 对时命令";
            this.f31对时命令ToolStripMenuItem.Click += new System.EventHandler(this.F31对时命令ToolStripMenuItemClick);
            // 
            // toolStripMenuItem19
            // 
            this.toolStripMenuItem19.Name = "toolStripMenuItem19";
            this.toolStripMenuItem19.Size = new System.Drawing.Size(159, 6);
            // 
            // c请求1类数据117ToolStripMenuItem
            // 
            this.c请求1类数据117ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.f25当前三相及总有无功功率功率因数三相电压电流零序电流视在功率ToolStripMenuItem,
            this.toolStripMenuItem14,
            this.f129当前正向有功电能示值ToolStripMenuItem,
            this.f130当前正向无功组合无功1电能示值ToolStripMenuItem,
            this.f131当前反向有功电能示值ToolStripMenuItem,
            this.f132当前反向无功组合无功1电能示值ToolStripMenuItem,
            this.f133当前一象限无功电能示值ToolStripMenuItem,
            this.f134当前二象限无功电能示值ToolStripMenuItem,
            this.f135当前三象限无功电能示值ToolStripMenuItem,
            this.f136当前四象限无功电能示值ToolStripMenuItem});
            this.c请求1类数据117ToolStripMenuItem.Name = "c请求1类数据117ToolStripMenuItem";
            this.c请求1类数据117ToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
            this.c请求1类数据117ToolStripMenuItem.Text = "[0C]请求1类数据";
            // 
            // f25当前三相及总有无功功率功率因数三相电压电流零序电流视在功率ToolStripMenuItem
            // 
            this.f25当前三相及总有无功功率功率因数三相电压电流零序电流视在功率ToolStripMenuItem.Name = "f25当前三相及总有无功功率功率因数三相电压电流零序电流视在功率ToolStripMenuItem";
            this.f25当前三相及总有无功功率功率因数三相电压电流零序电流视在功率ToolStripMenuItem.Size = new System.Drawing.Size(499, 22);
            this.f25当前三相及总有无功功率功率因数三相电压电流零序电流视在功率ToolStripMenuItem.Text = "F25 当前三相及总有/无功功率、功率因数,三相电压、电流、零序电流、视在功率";
            this.f25当前三相及总有无功功率功率因数三相电压电流零序电流视在功率ToolStripMenuItem.Click += new System.EventHandler(this.F25当前三相及总有无功功率功率因数三相电压电流零序电流视在功率ToolStripMenuItemClick);
            // 
            // toolStripMenuItem14
            // 
            this.toolStripMenuItem14.Name = "toolStripMenuItem14";
            this.toolStripMenuItem14.Size = new System.Drawing.Size(496, 6);
            // 
            // f129当前正向有功电能示值ToolStripMenuItem
            // 
            this.f129当前正向有功电能示值ToolStripMenuItem.Name = "f129当前正向有功电能示值ToolStripMenuItem";
            this.f129当前正向有功电能示值ToolStripMenuItem.Size = new System.Drawing.Size(499, 22);
            this.f129当前正向有功电能示值ToolStripMenuItem.Text = "F129 当前正向有功电能示值";
            this.f129当前正向有功电能示值ToolStripMenuItem.Click += new System.EventHandler(this.F129当前正向有功电能示值ToolStripMenuItemClick);
            // 
            // f130当前正向无功组合无功1电能示值ToolStripMenuItem
            // 
            this.f130当前正向无功组合无功1电能示值ToolStripMenuItem.Name = "f130当前正向无功组合无功1电能示值ToolStripMenuItem";
            this.f130当前正向无功组合无功1电能示值ToolStripMenuItem.Size = new System.Drawing.Size(499, 22);
            this.f130当前正向无功组合无功1电能示值ToolStripMenuItem.Text = "F130 当前正向无功(组合无功1)电能示值";
            this.f130当前正向无功组合无功1电能示值ToolStripMenuItem.Click += new System.EventHandler(this.F130当前正向无功组合无功1电能示值ToolStripMenuItemClick);
            // 
            // f131当前反向有功电能示值ToolStripMenuItem
            // 
            this.f131当前反向有功电能示值ToolStripMenuItem.Name = "f131当前反向有功电能示值ToolStripMenuItem";
            this.f131当前反向有功电能示值ToolStripMenuItem.Size = new System.Drawing.Size(499, 22);
            this.f131当前反向有功电能示值ToolStripMenuItem.Text = "F131 当前反向有功电能示值";
            this.f131当前反向有功电能示值ToolStripMenuItem.Click += new System.EventHandler(this.F131当前反向有功电能示值ToolStripMenuItemClick);
            // 
            // f132当前反向无功组合无功1电能示值ToolStripMenuItem
            // 
            this.f132当前反向无功组合无功1电能示值ToolStripMenuItem.Name = "f132当前反向无功组合无功1电能示值ToolStripMenuItem";
            this.f132当前反向无功组合无功1电能示值ToolStripMenuItem.Size = new System.Drawing.Size(499, 22);
            this.f132当前反向无功组合无功1电能示值ToolStripMenuItem.Text = "F132 当前反向无功(组合无功1)电能示值";
            this.f132当前反向无功组合无功1电能示值ToolStripMenuItem.Click += new System.EventHandler(this.F132当前反向无功组合无功1电能示值ToolStripMenuItemClick);
            // 
            // f133当前一象限无功电能示值ToolStripMenuItem
            // 
            this.f133当前一象限无功电能示值ToolStripMenuItem.Name = "f133当前一象限无功电能示值ToolStripMenuItem";
            this.f133当前一象限无功电能示值ToolStripMenuItem.Size = new System.Drawing.Size(499, 22);
            this.f133当前一象限无功电能示值ToolStripMenuItem.Text = "F133 当前一象限无功电能示值";
            this.f133当前一象限无功电能示值ToolStripMenuItem.Click += new System.EventHandler(this.F133当前一象限无功电能示值ToolStripMenuItemClick);
            // 
            // f134当前二象限无功电能示值ToolStripMenuItem
            // 
            this.f134当前二象限无功电能示值ToolStripMenuItem.Name = "f134当前二象限无功电能示值ToolStripMenuItem";
            this.f134当前二象限无功电能示值ToolStripMenuItem.Size = new System.Drawing.Size(499, 22);
            this.f134当前二象限无功电能示值ToolStripMenuItem.Text = "F134 当前二象限无功电能示值";
            this.f134当前二象限无功电能示值ToolStripMenuItem.Click += new System.EventHandler(this.F134当前二象限无功电能示值ToolStripMenuItemClick);
            // 
            // f135当前三象限无功电能示值ToolStripMenuItem
            // 
            this.f135当前三象限无功电能示值ToolStripMenuItem.Name = "f135当前三象限无功电能示值ToolStripMenuItem";
            this.f135当前三象限无功电能示值ToolStripMenuItem.Size = new System.Drawing.Size(499, 22);
            this.f135当前三象限无功电能示值ToolStripMenuItem.Text = "F135 当前三象限无功电能示值";
            this.f135当前三象限无功电能示值ToolStripMenuItem.Click += new System.EventHandler(this.F135当前三象限无功电能示值ToolStripMenuItemClick);
            // 
            // f136当前四象限无功电能示值ToolStripMenuItem
            // 
            this.f136当前四象限无功电能示值ToolStripMenuItem.Name = "f136当前四象限无功电能示值ToolStripMenuItem";
            this.f136当前四象限无功电能示值ToolStripMenuItem.Size = new System.Drawing.Size(499, 22);
            this.f136当前四象限无功电能示值ToolStripMenuItem.Text = "F136 当前四象限无功电能示值";
            this.f136当前四象限无功电能示值ToolStripMenuItem.Click += new System.EventHandler(this.F136当前四象限无功电能示值ToolStripMenuItemClick);
            // 
            // toolStripMenuItem13
            // 
            this.toolStripMenuItem13.Name = "toolStripMenuItem13";
            this.toolStripMenuItem13.Size = new System.Drawing.Size(159, 6);
            // 
            // toolStripMenuItem15
            // 
            this.toolStripMenuItem15.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.f1透明转发ToolStripMenuItem,
            this.f9ToolStripMenuItem});
            this.toolStripMenuItem15.Name = "toolStripMenuItem15";
            this.toolStripMenuItem15.Size = new System.Drawing.Size(162, 22);
            this.toolStripMenuItem15.Text = "[10]数据转发";
            // 
            // f1透明转发ToolStripMenuItem
            // 
            this.f1透明转发ToolStripMenuItem.Name = "f1透明转发ToolStripMenuItem";
            this.f1透明转发ToolStripMenuItem.Size = new System.Drawing.Size(281, 22);
            this.f1透明转发ToolStripMenuItem.Text = "F1 透明转发";
            this.f1透明转发ToolStripMenuItem.Click += new System.EventHandler(this.F1透明转发ToolStripMenuItemClick);
            // 
            // f9ToolStripMenuItem
            // 
            this.f9ToolStripMenuItem.Name = "f9ToolStripMenuItem";
            this.f9ToolStripMenuItem.Size = new System.Drawing.Size(281, 22);
            this.f9ToolStripMenuItem.Text = "F9 转发主站直接对电表的抄读数据命令";
            this.f9ToolStripMenuItem.Click += new System.EventHandler(this.F9ToolStripMenuItemClick);
            // 
            // 数据操作ToolStripMenuItem
            // 
            this.数据操作ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.帧解析ToolStripMenuItem,
            this.toolStripMenuItem3,
            this.数据查询ToolStripMenuItem,
            this.toolStripMenuItem10,
            this.帧结构ToolStripMenuItem,
            this.toolStripMenuItem11,
            this.格式查询ToolStripMenuItem,
            this.eRC格式查询ToolStripMenuItem});
            this.数据操作ToolStripMenuItem.Name = "数据操作ToolStripMenuItem";
            this.数据操作ToolStripMenuItem.Size = new System.Drawing.Size(67, 20);
            this.数据操作ToolStripMenuItem.Text = "数据操作";
            // 
            // 帧解析ToolStripMenuItem
            // 
            this.帧解析ToolStripMenuItem.Name = "帧解析ToolStripMenuItem";
            this.帧解析ToolStripMenuItem.Size = new System.Drawing.Size(191, 22);
            this.帧解析ToolStripMenuItem.Text = "系统报文解析";
            this.帧解析ToolStripMenuItem.Click += new System.EventHandler(this.帧解析ToolStripMenuItemClick);
            // 
            // toolStripMenuItem3
            // 
            this.toolStripMenuItem3.Name = "toolStripMenuItem3";
            this.toolStripMenuItem3.Size = new System.Drawing.Size(188, 6);
            // 
            // 数据查询ToolStripMenuItem
            // 
            this.数据查询ToolStripMenuItem.Name = "数据查询ToolStripMenuItem";
            this.数据查询ToolStripMenuItem.Size = new System.Drawing.Size(191, 22);
            this.数据查询ToolStripMenuItem.Text = "用户召测数据查询";
            this.数据查询ToolStripMenuItem.Click += new System.EventHandler(this.数据查询ToolStripMenuItemClick);
            // 
            // toolStripMenuItem10
            // 
            this.toolStripMenuItem10.Name = "toolStripMenuItem10";
            this.toolStripMenuItem10.Size = new System.Drawing.Size(188, 6);
            // 
            // 帧结构ToolStripMenuItem
            // 
            this.帧结构ToolStripMenuItem.Name = "帧结构ToolStripMenuItem";
            this.帧结构ToolStripMenuItem.Size = new System.Drawing.Size(191, 22);
            this.帧结构ToolStripMenuItem.Text = "376.1帧结构说明";
            this.帧结构ToolStripMenuItem.Click += new System.EventHandler(this.帧结构ToolStripMenuItemClick);
            // 
            // toolStripMenuItem11
            // 
            this.toolStripMenuItem11.Name = "toolStripMenuItem11";
            this.toolStripMenuItem11.Size = new System.Drawing.Size(188, 6);
            // 
            // 格式查询ToolStripMenuItem
            // 
            this.格式查询ToolStripMenuItem.Name = "格式查询ToolStripMenuItem";
            this.格式查询ToolStripMenuItem.Size = new System.Drawing.Size(191, 22);
            this.格式查询ToolStripMenuItem.Text = "A1-A27数据格式说明";
            this.格式查询ToolStripMenuItem.Click += new System.EventHandler(this.格式查询ToolStripMenuItemClick);
            // 
            // eRC格式查询ToolStripMenuItem
            // 
            this.eRC格式查询ToolStripMenuItem.Name = "eRC格式查询ToolStripMenuItem";
            this.eRC格式查询ToolStripMenuItem.Size = new System.Drawing.Size(191, 22);
            this.eRC格式查询ToolStripMenuItem.Text = "ERC事件记录数据格式";
            this.eRC格式查询ToolStripMenuItem.Click += new System.EventHandler(this.ERC格式查询ToolStripMenuItemClick);
            // 
            // 系统帮组ToolStripMenuItem
            // 
            this.系统帮组ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.系统帮助ToolStripMenuItem,
            this.toolStripMenuItem1
            });

            
            this.系统帮组ToolStripMenuItem.Name = "系统帮组ToolStripMenuItem";
            this.系统帮组ToolStripMenuItem.Size = new System.Drawing.Size(67, 20);
            this.系统帮组ToolStripMenuItem.Text = "系统帮助";
            // 
            // 系统帮助ToolStripMenuItem
            // 
            this.系统帮助ToolStripMenuItem.Name = "系统帮助ToolStripMenuItem";
            this.系统帮助ToolStripMenuItem.Size = new System.Drawing.Size(122, 22);
            this.系统帮助ToolStripMenuItem.Text = "系统帮助";
            this.系统帮助ToolStripMenuItem.Click += new System.EventHandler(this.系统帮助ToolStripMenuItemClick);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(119, 6);
            // 
            // 关于ToolStripMenuItem
            // 
            
            
            
            
            // 
            // hToolStripMenuItem
            // 
            this.hToolStripMenuItem.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.hToolStripMenuItem.Name = "hToolStripMenuItem";
            this.hToolStripMenuItem.Size = new System.Drawing.Size(12, 20);
            this.hToolStripMenuItem.Click += new System.EventHandler(this.HToolStripMenuItemClick);
            // 
            // toolStripButton3
            // 
            this.toolStripButton3.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton3.Name = "toolStripButton3";
            this.toolStripButton3.Size = new System.Drawing.Size(59, 22);
            this.toolStripButton3.Text = "系统参数";
            this.toolStripButton3.Click += new System.EventHandler(this.ToolStripButton3Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStrip1
            // 
            this.toolStrip1.BackColor = System.Drawing.Color.Transparent;
            this.toolStrip1.CanOverflow = false;
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton3,
            this.toolStripSeparator1,
            this.toolStripButton1,
            this.toolStripSeparator2,
            this.toolStripButton2,
            this.toolStripSeparator3,
            this.toolStripButton4,
            this.toolStripSeparator4,
            this.toolStripButton5,
            this.toolStripSeparator6,
            this.toolStripSplitButton1,
            this.toolStripSeparator5});
            this.toolStrip1.LayoutStyle = System.Windows.Forms.ToolStripLayoutStyle.HorizontalStackWithOverflow;
            this.toolStrip1.Location = new System.Drawing.Point(0, 24);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(516, 25);
            this.toolStrip1.TabIndex = 7;
            // 
            // toolStripButton1
            // 
            this.toolStripButton1.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton1.Name = "toolStripButton1";
            this.toolStripButton1.Size = new System.Drawing.Size(59, 22);
            this.toolStripButton1.Text = "抄读参数";
            this.toolStripButton1.Click += new System.EventHandler(this.ToolStripButton1Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton2
            // 
            this.toolStripButton2.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton2.Name = "toolStripButton2";
            this.toolStripButton2.Size = new System.Drawing.Size(59, 22);
            this.toolStripButton2.Text = "报文解析";
            this.toolStripButton2.Click += new System.EventHandler(this.ToolStripButton2Click);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton4
            // 
            this.toolStripButton4.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton4.Name = "toolStripButton4";
            this.toolStripButton4.Size = new System.Drawing.Size(59, 22);
            this.toolStripButton4.Text = "数据查询";
            this.toolStripButton4.Click += new System.EventHandler(this.ToolStripButton4Click);
            // 
            // toolStripSeparator4
            // 
            this.toolStripSeparator4.Name = "toolStripSeparator4";
            this.toolStripSeparator4.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton5
            // 
            this.toolStripButton5.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton5.Name = "toolStripButton5";
            this.toolStripButton5.Size = new System.Drawing.Size(59, 22);
            this.toolStripButton5.Text = "定时任务";
            this.toolStripButton5.Click += new System.EventHandler(this.ToolStripButton5Click);
            // 
            // toolStripSeparator6
            // 
            this.toolStripSeparator6.Name = "toolStripSeparator6";
            this.toolStripSeparator6.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripSplitButton1
            // 
            this.toolStripSplitButton1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.f1透明转发ToolStripMenuItem1,
            this.toolStripMenuItem18,
            this.f9转发主站直接对电表的抄读数据命令ToolStripMenuItem});
            this.toolStripSplitButton1.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripSplitButton1.Name = "toolStripSplitButton1";
            this.toolStripSplitButton1.Size = new System.Drawing.Size(71, 22);
            this.toolStripSplitButton1.Text = "数据转发";
            // 
            // f1透明转发ToolStripMenuItem1
            // 
            this.f1透明转发ToolStripMenuItem1.Name = "f1透明转发ToolStripMenuItem1";
            this.f1透明转发ToolStripMenuItem1.Size = new System.Drawing.Size(137, 22);
            this.f1透明转发ToolStripMenuItem1.Text = "F1 透明转发";
            this.f1透明转发ToolStripMenuItem1.Click += new System.EventHandler(this.F1透明转发ToolStripMenuItem1Click);
            // 
            // toolStripMenuItem18
            // 
            this.toolStripMenuItem18.Name = "toolStripMenuItem18";
            this.toolStripMenuItem18.Size = new System.Drawing.Size(134, 6);
            // 
            // f9转发主站直接对电表的抄读数据命令ToolStripMenuItem
            // 
            this.f9转发主站直接对电表的抄读数据命令ToolStripMenuItem.Name = "f9转发主站直接对电表的抄读数据命令ToolStripMenuItem";
            this.f9转发主站直接对电表的抄读数据命令ToolStripMenuItem.Size = new System.Drawing.Size(137, 22);
            this.f9转发主站直接对电表的抄读数据命令ToolStripMenuItem.Text = "F9 数据直抄";
            this.f9转发主站直接对电表的抄读数据命令ToolStripMenuItem.Click += new System.EventHandler(this.F9转发主站直接对电表的抄读数据命令ToolStripMenuItemClick);
            // 
            // toolStripSeparator5
            // 
            this.toolStripSeparator5.Name = "toolStripSeparator5";
            this.toolStripSeparator5.Size = new System.Drawing.Size(6, 25);
            // 
            // BottomToolStripPanel
            // 
            this.BottomToolStripPanel.Location = new System.Drawing.Point(0, 0);
            this.BottomToolStripPanel.Name = "BottomToolStripPanel";
            this.BottomToolStripPanel.Orientation = System.Windows.Forms.Orientation.Horizontal;
            this.BottomToolStripPanel.RowMargin = new System.Windows.Forms.Padding(3, 0, 0, 0);
            this.BottomToolStripPanel.Size = new System.Drawing.Size(0, 0);
            // 
            // TopToolStripPanel
            // 
            this.TopToolStripPanel.Location = new System.Drawing.Point(0, 0);
            this.TopToolStripPanel.Name = "TopToolStripPanel";
            this.TopToolStripPanel.Orientation = System.Windows.Forms.Orientation.Horizontal;
            this.TopToolStripPanel.RowMargin = new System.Windows.Forms.Padding(3, 0, 0, 0);
            this.TopToolStripPanel.Size = new System.Drawing.Size(0, 0);
            // 
            // RightToolStripPanel
            // 
            this.RightToolStripPanel.Location = new System.Drawing.Point(0, 0);
            this.RightToolStripPanel.Name = "RightToolStripPanel";
            this.RightToolStripPanel.Orientation = System.Windows.Forms.Orientation.Horizontal;
            this.RightToolStripPanel.RowMargin = new System.Windows.Forms.Padding(3, 0, 0, 0);
            this.RightToolStripPanel.Size = new System.Drawing.Size(0, 0);
            // 
            // LeftToolStripPanel
            // 
            this.LeftToolStripPanel.Location = new System.Drawing.Point(0, 0);
            this.LeftToolStripPanel.Name = "LeftToolStripPanel";
            this.LeftToolStripPanel.Orientation = System.Windows.Forms.Orientation.Horizontal;
            this.LeftToolStripPanel.RowMargin = new System.Windows.Forms.Padding(3, 0, 0, 0);
            this.LeftToolStripPanel.Size = new System.Drawing.Size(0, 0);
            // 
            // ContentPanel
            // 
            this.ContentPanel.Size = new System.Drawing.Size(339, 177);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1,
            this.toolStripStatusLabel2,
            this.toolStripStatusLabel3});
            this.statusStrip1.Location = new System.Drawing.Point(0, 375);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.RenderMode = System.Windows.Forms.ToolStripRenderMode.ManagerRenderMode;
            this.statusStrip1.Size = new System.Drawing.Size(516, 22);
            this.statusStrip1.TabIndex = 24;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Font = new System.Drawing.Font("Times New Roman", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(55, 17);
            this.toolStripStatusLabel1.Text = "侦听端口";
            // 
            // toolStripStatusLabel2
            // 
            this.toolStripStatusLabel2.Name = "toolStripStatusLabel2";
            this.toolStripStatusLabel2.Size = new System.Drawing.Size(0, 17);
            // 
            // toolStripStatusLabel3
            // 
            this.toolStripStatusLabel3.Font = new System.Drawing.Font("Times New Roman", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.toolStripStatusLabel3.Name = "toolStripStatusLabel3";
            this.toolStripStatusLabel3.Size = new System.Drawing.Size(446, 17);
            this.toolStripStatusLabel3.Spring = true;
            this.toolStripStatusLabel3.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // dockPanel
            // 
            this.dockPanel.ActiveAutoHideContent = null;
            this.dockPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dockPanel.DockBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(239)))), ((int)(((byte)(237)))), ((int)(((byte)(226)))));
            this.dockPanel.Location = new System.Drawing.Point(0, 49);
            this.dockPanel.Name = "dockPanel";
            this.dockPanel.ShowDocumentIcon = true;
            this.dockPanel.Size = new System.Drawing.Size(516, 326);
            dockPanelGradient1.EndColor = System.Drawing.Color.FromArgb(((int)(((byte)(41)))), ((int)(((byte)(57)))), ((int)(((byte)(85)))));
            dockPanelGradient1.StartColor = System.Drawing.Color.FromArgb(((int)(((byte)(41)))), ((int)(((byte)(57)))), ((int)(((byte)(85)))));
            autoHideStripSkin1.DockStripGradient = dockPanelGradient1;
            tabGradient1.EndColor = System.Drawing.Color.FromArgb(((int)(((byte)(61)))), ((int)(((byte)(82)))), ((int)(((byte)(119)))));
            tabGradient1.StartColor = System.Drawing.Color.FromArgb(((int)(((byte)(61)))), ((int)(((byte)(82)))), ((int)(((byte)(119)))));
            tabGradient1.TextColor = System.Drawing.Color.White;
            autoHideStripSkin1.TabGradient = tabGradient1;
            autoHideStripSkin1.TextFont = new System.Drawing.Font("SimSun", 9F);
            dockPanelSkin1.AutoHideStripSkin = autoHideStripSkin1;
            tabGradient2.EndColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(231)))), ((int)(((byte)(165)))));
            tabGradient2.LinearGradientMode = System.Drawing.Drawing2D.LinearGradientMode.Vertical;
            tabGradient2.StartColor = System.Drawing.Color.White;
            tabGradient2.TextColor = System.Drawing.Color.Black;
            dockPaneStripGradient1.ActiveTabGradient = tabGradient2;
            dockPanelGradient2.EndColor = System.Drawing.Color.FromArgb(((int)(((byte)(41)))), ((int)(((byte)(57)))), ((int)(((byte)(85)))));
            dockPanelGradient2.StartColor = System.Drawing.Color.FromArgb(((int)(((byte)(41)))), ((int)(((byte)(57)))), ((int)(((byte)(85)))));
            dockPaneStripGradient1.DockStripGradient = dockPanelGradient2;
            tabGradient3.EndColor = System.Drawing.Color.FromArgb(((int)(((byte)(41)))), ((int)(((byte)(57)))), ((int)(((byte)(85)))));
            tabGradient3.LinearGradientMode = System.Drawing.Drawing2D.LinearGradientMode.Vertical;
            tabGradient3.StartColor = System.Drawing.Color.FromArgb(((int)(((byte)(41)))), ((int)(((byte)(57)))), ((int)(((byte)(85)))));
            tabGradient3.TextColor = System.Drawing.Color.White;
            dockPaneStripGradient1.InactiveTabGradient = tabGradient3;
            dockPaneStripSkin1.DocumentGradient = dockPaneStripGradient1;
            dockPaneStripSkin1.TextFont = new System.Drawing.Font("SimSun", 9F);
            tabGradient4.EndColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(231)))), ((int)(((byte)(165)))));
            tabGradient4.LinearGradientMode = System.Drawing.Drawing2D.LinearGradientMode.Vertical;
            tabGradient4.StartColor = System.Drawing.Color.White;
            tabGradient4.TextColor = System.Drawing.SystemColors.ControlText;
            dockPaneStripToolWindowGradient1.ActiveCaptionGradient = tabGradient4;
            tabGradient5.EndColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(231)))), ((int)(((byte)(165)))));
            tabGradient5.LinearGradientMode = System.Drawing.Drawing2D.LinearGradientMode.Vertical;
            tabGradient5.StartColor = System.Drawing.Color.White;
            tabGradient5.TextColor = System.Drawing.SystemColors.ControlText;
            dockPaneStripToolWindowGradient1.ActiveTabGradient = tabGradient5;
            dockPanelGradient3.EndColor = System.Drawing.Color.FromArgb(((int)(((byte)(41)))), ((int)(((byte)(57)))), ((int)(((byte)(85)))));
            dockPanelGradient3.StartColor = System.Drawing.Color.FromArgb(((int)(((byte)(41)))), ((int)(((byte)(57)))), ((int)(((byte)(85)))));
            dockPaneStripToolWindowGradient1.DockStripGradient = dockPanelGradient3;
            tabGradient6.EndColor = System.Drawing.Color.FromArgb(((int)(((byte)(62)))), ((int)(((byte)(83)))), ((int)(((byte)(120)))));
            tabGradient6.LinearGradientMode = System.Drawing.Drawing2D.LinearGradientMode.Vertical;
            tabGradient6.StartColor = System.Drawing.Color.FromArgb(((int)(((byte)(75)))), ((int)(((byte)(94)))), ((int)(((byte)(129)))));
            tabGradient6.TextColor = System.Drawing.Color.White;
            dockPaneStripToolWindowGradient1.InactiveCaptionGradient = tabGradient6;
            tabGradient7.EndColor = System.Drawing.Color.FromArgb(((int)(((byte)(41)))), ((int)(((byte)(57)))), ((int)(((byte)(85)))));
            tabGradient7.StartColor = System.Drawing.Color.FromArgb(((int)(((byte)(41)))), ((int)(((byte)(57)))), ((int)(((byte)(85)))));
            tabGradient7.TextColor = System.Drawing.Color.White;
            dockPaneStripToolWindowGradient1.InactiveTabGradient = tabGradient7;
            dockPaneStripSkin1.ToolWindowGradient = dockPaneStripToolWindowGradient1;
            dockPanelSkin1.DockPaneStripSkin = dockPaneStripSkin1;
            this.dockPanel.Skin = dockPanelSkin1;
            this.dockPanel.TabIndex = 31;
            // 
            // 网络服务ToolStripMenuItem
            // 
            this.网络服务ToolStripMenuItem.Name = "网络服务ToolStripMenuItem";
            this.网络服务ToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.网络服务ToolStripMenuItem.Text = "网络服务";
            this.网络服务ToolStripMenuItem.Click += new System.EventHandler(this.网络服务ToolStripMenuItem_Click);
            // 
            // MainForm
            // 
            this.ClientSize = new System.Drawing.Size(516, 397);
            this.Controls.Add(this.dockPanel);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.toolStrip1);
            this.Controls.Add(this.menuStrip1);
            this.Font = new System.Drawing.Font("SimSun", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.IsMdiContainer = true;
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "采集终端通信协议测试V3  (Q/GDW 376.1-2009)";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainFormFormClosing);
            this.Load += new System.EventHandler(this.MainFormLoad);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

		}

        private void 网络服务ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FormContainer<UCNetStart> form = new FormContainer<UCNetStart>();
            form.Show(this);
        }
	}
}
