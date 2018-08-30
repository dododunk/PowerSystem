using ActiveReportDLT698;
using GB698Cls;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;
using WinFormsUI.Docking;
namespace GB698Ctl
{
	public class ActiveReport : DockContent
	{
		private delegate void ShowMsgDelegate(object obj);
		public delegate void AddRowDelegate(string iA1, string iA2, string iAFN, string iFN, string iPN, string iData);
		private delegate void AddDataDelegate(CollapseDataGridViewRow ROW, string _items, string _values);
		private DLT698_Recv gAS = new DLT698_Recv();
		public CollapseDataGridView grid1 = new CollapseDataGridView();
		private IContainer components = null;
		private ContextMenuStrip contextMenuStrip1;
		private ToolStripMenuItem 清空数据ToolStripMenuItem;
		public ActiveReport()
		{
			this.InitializeComponent();
			this.grid1.Parent = this;
			this.grid1.Dock = DockStyle.Fill;
			this.InitGrid(this.grid1);
			Application.DoEvents();
			Program.CanShowText = true;
		}
		private void InitGrid(DataGridView Grid)
		{
			Grid.Columns.Clear();
			Grid.Rows.Clear();
			Grid.ContextMenuStrip = this.contextMenuStrip1;
			Grid.MultiSelect = false;
			Grid.BorderStyle = BorderStyle.None;
			Grid.BackgroundColor = Color.FromKnownColor(KnownColor.White);
			Grid.GridColor = Color.FromKnownColor(KnownColor.ActiveBorder);
			Grid.ColumnHeadersDefaultCellStyle.Alignment = DataGridViewContentAlignment.MiddleCenter;
			Grid.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.EnableResizing;
			Grid.ColumnHeadersHeight = 28;
			DataGridViewTextBoxColumn dataGridViewTextBoxColumn = new DataGridViewTextBoxColumn();
			dataGridViewTextBoxColumn.HeaderText = "项目分类";
			dataGridViewTextBoxColumn.Name = "zdmc";
			dataGridViewTextBoxColumn.Width = 80;
			dataGridViewTextBoxColumn.ReadOnly = true;
			dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewTextBoxColumn);
			dataGridViewTextBoxColumn = new DataGridViewTextBoxColumn();
			dataGridViewTextBoxColumn.HeaderText = "项目名称";
			dataGridViewTextBoxColumn.Name = "gybz";
			dataGridViewTextBoxColumn.Width = 200;
			dataGridViewTextBoxColumn.ReadOnly = true;
			dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewTextBoxColumn);
			dataGridViewTextBoxColumn = new DataGridViewTextBoxColumn();
			dataGridViewTextBoxColumn.HeaderText = "AFN";
			dataGridViewTextBoxColumn.Name = "gygs";
			dataGridViewTextBoxColumn.Width = 35;
			dataGridViewTextBoxColumn.ReadOnly = true;
			dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewTextBoxColumn);
			dataGridViewTextBoxColumn = new DataGridViewTextBoxColumn();
			dataGridViewTextBoxColumn.HeaderText = "FN";
			dataGridViewTextBoxColumn.Name = "xzjs";
			dataGridViewTextBoxColumn.Width = 35;
			dataGridViewTextBoxColumn.ReadOnly = true;
			dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewTextBoxColumn);
			dataGridViewTextBoxColumn = new DataGridViewTextBoxColumn();
			dataGridViewTextBoxColumn.HeaderText = "PN";
			dataGridViewTextBoxColumn.Name = "kzm";
			dataGridViewTextBoxColumn.Width = 35;
			dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewTextBoxColumn);
			dataGridViewTextBoxColumn = new DataGridViewTextBoxColumn();
			dataGridViewTextBoxColumn.HeaderText = "A1";
			dataGridViewTextBoxColumn.Name = "ckzA1";
			dataGridViewTextBoxColumn.Width = 35;
			dataGridViewTextBoxColumn.ReadOnly = true;
			dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewTextBoxColumn);
			dataGridViewTextBoxColumn = new DataGridViewTextBoxColumn();
			dataGridViewTextBoxColumn.HeaderText = "A2";
			dataGridViewTextBoxColumn.Name = "ckzA2";
			dataGridViewTextBoxColumn.Width = 40;
			dataGridViewTextBoxColumn.ReadOnly = true;
			dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewTextBoxColumn);
			dataGridViewTextBoxColumn = new DataGridViewTextBoxColumn();
			dataGridViewTextBoxColumn.HeaderText = "名称";
			dataGridViewTextBoxColumn.Name = "ckz";
			dataGridViewTextBoxColumn.Width = 250;
			dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewTextBoxColumn);
			dataGridViewTextBoxColumn = new DataGridViewTextBoxColumn();
			dataGridViewTextBoxColumn.HeaderText = "数值";
			dataGridViewTextBoxColumn.Name = "ckzsj";
			dataGridViewTextBoxColumn.ReadOnly = true;
			dataGridViewTextBoxColumn.Width = 150;
			dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewTextBoxColumn);
			dataGridViewTextBoxColumn = new DataGridViewTextBoxColumn();
			dataGridViewTextBoxColumn.HeaderText = "时间";
			dataGridViewTextBoxColumn.Name = "ckzsj";
			dataGridViewTextBoxColumn.ReadOnly = true;
			dataGridViewTextBoxColumn.Width = 60;
			dataGridViewTextBoxColumn.SortMode = DataGridViewColumnSortMode.NotSortable;
			Grid.Columns.Add(dataGridViewTextBoxColumn);
			Grid.AllowUserToAddRows = false;
		}
		private void 清空数据ToolStripMenuItem_Click(object sender, EventArgs e)
		{
			this.InitGrid(this.grid1);
		}
		private void ActiveReport_Shown(object sender, EventArgs e)
		{
			ThreadPool.QueueUserWorkItem(new WaitCallback(this.ShowMsg), null);
			ActiveReportMsg.gRECInfo.Clear();
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
					for (int i = ActiveReportMsg.gRECInfo.Count - 1; i >= 0; i--)
					{
						Application.DoEvents();
						ActiveReportDLT698.DLT698 dLT = new ActiveReportDLT698.DLT698();
						byte[] rec = ActiveReportMsg.gRECInfo[i].Rec;
						ActiveReportDLT698.DLT698.FrameInfo frameInfo = default(ActiveReportDLT698.DLT698.FrameInfo);
						if (dLT.Assert_Basic(rec))
						{
							dLT.ParseData(rec, rec.Length, ref frameInfo);
							if (!string.IsNullOrEmpty(frameInfo.Data))
							{
								string[] array = frameInfo.FN.Split(new char[]
								{
									','
								});
								string[] array2 = frameInfo.PN.Split(new char[]
								{
									','
								});
								string[] array3 = frameInfo.Data.Split(new char[]
								{
									','
								});
								for (int j = 0; j < array.Length; j++)
								{
									this.AddRow(frameInfo.A1, frameInfo.A2, frameInfo.AFN, array[j], array2[j], array3[j]);
								}
							}
						}
						ActiveReportMsg.gRECInfo.RemoveAt(i);
					}
				}
			}
		}
		private string[] ClassOne()
		{
			string text = string.Empty;
			text = "F1 终端版本信息|0001,F2 终端日历时钟|0002,F3 终端参数状态|0003,F4 终端上行通信状态|0004,F5 终端控制设置状态|0005,F6 终端当前控制状态|0006,F7 终端事件计数器当前值|0007,F8 终端事件标志状态|0008,F9 终端状态量及变位标志|0009,F10 终端与主站当日/月通信流量|0010,F11 终端集中抄表状态信息|0011,F12 终端网路信号品质|0012,F17 当前总加有功功率|0017,F18 当前总加无功功率|0018,F19 当日总加有功电能量|0019,F20 当日总加无功电能量|0020,F21 当月总加有功电能量|0021,F22 当月总加无功电能量|0022,F23 终端当前剩余电量|0023,F24 当前功率下浮控控后总加有功功率冻结值|0024,F25 当前三相及总有无功功率/功率因数/三相电压/电流/零序电流/视在功率|0025,F26 A/B/C三相断相统计数据及最近一次断相记录|0026,F27 电能表日历时钟/编程次数及其最近一次操作时间|0027,F28 电表运行状态字及其变位标志|0028,F29 当前铜损/铁损有功总电能示值|0029,F30 上一结算日铜损/铁损有功总电能示值|0030,F31 当前[A/B/C]三相正/反向有功电能示值/组合无功[1/2]电能示值|0031,F32 上一结算日[A/B/C]三相正/反向有功电能示值/组合无功[1/2]电能示值|0032,F33 当前正向有无功电能示值/一四象限无功电能示值|0033,F34 当前反向有无功电能示值/二三象限无功电能示值|0034,F35 当月正向有无功最大需量及发生时间|0035,F36 当月反向有无功最大需量及发生时间|0036,F37 上月(上一结算日)正向有无功电能示值/一四象限无功电能示值|0037,F38 上月(上一结算日)反向有无功电能示值/二三象限无功电能示值|0038,F39 上月(上一结算日)正向有无功最大需量及发生时间|0039,F40 上月(上一结算日)反向有无功最大需量及发生时间|0040,F41 当日正向有功电能量|0041,F42 当日正向无功电能量|0042,F43 当日反向有功电能量|0043,F44 当日反向无功电能量|0044,F45 当月正向有功电能量|0045,F46 当月正向无功电能量|0046,F47 当月反向有功电能量|0047,F48 当月反向无功电能量|0048,F49 当前电压/电流相位角|0049,F57 当前[A/B/C]三相电压/电流2-N次谐波有效值|0057,F58 当前[A/B/C]三相电压/电流2-N次谐波含有率|0058,F65 当前电容器投切状态|0065,F66 当前电容器累计补偿投入时间和次数|0066,F67 当日/当月电容器累计补偿的无功电能量|0067,F73 直流模拟量当前数据|0073,F81 小时冻结总加有功功率|0081,F82 小时冻结总加无功功率|0082,F83 小时冻结总加有功总电能量|0083,F84 小时冻结总加无功总电能量|0084,F89 小时冻结有功功率|0089,F90 小时冻结A相有功功率|0090,F91 小时冻结B相有功功率|0091,F92 小时冻结C相有功功率|0092,F93 小时冻结无功功率|0093,F94 小时冻结A相无功功率|0094,F95 小时冻结B相无功功率|0095,F96 小时冻结C相无功功率|0096,F97 小时冻结A相电压|0097,F98 小时冻结B相电压|0098,F99 小时冻结C相电压|0099,F100 小时冻结A相电流|0100,F101 小时冻结B相电流|0101,F102 小时冻结C相电流|0102,F103 小时冻结零序电流|0103,F105 小时冻结正向有功总电能量|0105,F106 小时冻结正向无功总电能量|0106,F107 小时冻结反向有功总电能量|0107,F108 小时冻结反向无功总电能量|0108,F109 小时冻结正向有功总电能示值|0109,F110 小时冻结正向无功总电能示值|0110,F111 小时冻结反向有功总电能示值|0111,F112 小时冻结反向无功总电能示值|0112,F113 小时冻结总功率因数|0113,F114 小时冻结A相功率因数|0114,F115 小时冻结B相功率因数|0115,F116 小时冻结C相功率因数|0116,F121 小时冻结直流模拟量|0121,F129 当前正向有功电能示值|0129,F130 当前正向无功(组合无功1)电能示值|0130,F131 当前反向有功电能示值|0131,F132 当前反向无功(组合无功1)电能示值|0132,F133 当前一象限无功电能示值|0133,F134 当前二象限无功电能示值|0134,F135 当前三象限无功电能示值|0135,F136 当前四象限无功电能示值|0136,F137 上月(上一结算日)正向有功电能示值|0137,F138 上月(上一结算日)正向无功(组合无功1)电能示值|0138,F139 上月(上一结算日)反向有功电能示值|0139,F140 上月(上一结算日)反向无功(组合无功1)电能示值|0140,F141 上月(上一结算日)一象限无功电能示值|0141,F142 上月(上一结算日)二象限无功电能示值|0142,F143 上月(上一结算日)三象限无功电能示值|0143,F144 上月(上一结算日)四象限无功电能示值|0144,F145 当月正向有功最大需量及发生时间|0145,F146 当月正向无功最大需量及发生时间|0146,F147 当月反向有功最大需量及发生时间|0147,F148 当月反向无功最大需量及发生时间|0148,F149 上月(上一结算日)正向有功最大需量及发生时间|0149,F150 上月(上一结算日)正向无功最大需量及发生时间|0150,F151 上月(上一结算日)反向有功最大需量及发生时间|0151,F152 上月(上一结算日)反向无功最大需量及发生时间|0152,F153 第一时区冻结正向有功电能示值|0153,F154 第二时区冻结正向有功电能示值|0154,F155 第三时区冻结正向有功电能示值|0155,F156 第四时区冻结正向有功电能示值|0156,F157 第五时区冻结正向有功电能示值|0157,F158 第六时区冻结正向有功电能示值|0158,F159 第七时区冻结正向有功电能示值|0159,F160 第八时区冻结正向有功电能示值|0160,F161 电能表远程控制通断电状态及记录|0161,F165 电能表开关操作次数及时间|0165,F166 电能表参数修改次数及时间|0166,F167 电能表购/用电信息|0167,F168 电能表结算信息|0168,F169 集中抄表中继路由信息|0169,F170 集中抄表电表抄读信息|0170";
			return text.Split(new char[]
			{
				','
			});
		}
		private string[] ClassTwo()
		{
			string text = string.Empty;
			text = "F1 日冻结正向有无功电能示值/一四象限无功电能示值|0001,F2 日冻结反向有无功电能示值/二三象限无功电能示值|0002,F3 日冻结正向有无功最大需量及发生时间|0003,F4 日冻结反向有无功最大需量及发生时间|0004,F5 日冻结正向有功电能量|0005,F6 日冻结正向无功电能量|0006,F7 日冻结反向有功电能量|0007,F8 日冻结反向无功电能量|0008,F9 抄表日冻结正向有无功电能示值/一四象限无功电能示值|0009,F10 抄表日冻结反向有无功电能示值/二三象限无功电能示值|0010,F11 抄表日冻结电能表正向有无功最大需量及发生时间|0011,F12 抄表日冻结电能表反向有无功最大需量及发生时间|0012,F17 月冻结正向有无功电能示值/一四象限无功电能示值|0017,F18 月冻结反向有无功电能示值/二三象限无功电能示值|0018,F19 月冻结电能表正向有无功最大需量及发生时间|0019,F20 月冻结电能表反向有无功最大需量及发生时间|0020,F21 月冻结正向有功电能量|0021,F22 月冻结正向无功电能量|0022,F23 月冻结反向有功电能量|0023,F24 月冻结反向无功电能量|0024,F25 日冻结日总及分相最大有功功率及发生时间/有功功率为零时间|0025,F26 日冻结日总及分相最大需量及发生时间|0026,F27 日冻结日电压统计数据|0027,F28 日冻结日不平衡度越限累计时间|0028,F29 日冻结日电流越限数据|0029,F30 日冻结日视在功率越限累计时间|0030,F31 日负载率统计|0031,F32 日冻结电能表断相数据|0032,F33 月冻结月总及分相最大有功功率及发生时间/有功功率为零时间|0033,F34 月冻结月总及分相有功最大需量及发生时间|0034,F35 月冻结月电压统计数据|0035,F36 月冻结月不平衡度越限累计时间|0036,F37 月冻结月电流越限数据|0037,F38 月冻结月视在功率越限累计时间|0038,F39 月负载率统计|0039,F41 日冻结电容器累计投入时间和次数|0041,F42 日冻结日/月电容器累计补偿的无功电能量|0042,F43 日冻结日功率因数区段累计时间|0043,F44 月冻结月功率因数区段累计时间|0044,F45 日冻结铜损/铁损有功电能示值|0045,F46 月冻结铜损/铁损有功电能示值|0046,F49 日冻结终端日供电时间/日复位累计次数|0049,F50 日冻结终端日控制统计数据|0050,F51 月冻结终端月供电时间/月复位累计次数|0051,F52 月冻结终端月控制统计数据|0052,F53 终端与主站日通信流量|0053,F54 终端与主站月通信流量|0054,F57 日冻结总加组日最大最小有功功率及其发生时间/有功功率为零日累计时间|0057,F58 日冻结总加组日累计有功电能量|0058,F59 日冻结总加组日累计无功电能量|0059,F60 月冻结总加组月最大最小有功功率及其发生时间/有功功率为零累计时间|0060,F61 月冻结总加组月有功电能量|0061,F62 月冻结总加组月无功电能量|0062,F65 月冻结总加组超功率定值的月累计时间及月累计电能量|0065,F66 月冻结总加组超月电能量定值的月累计时间及月累计电能量|0066,F73 总加组有功功率曲线|0073,F74 总加组无功功率曲线|0074,F75 总加组有功电能量曲线|0075,F76 总加组无功电能量曲线|0076,F81 测量点有功功率曲线|0081,F82 测量点A相有功功率曲线|0082,F83 测量点B相有功功率曲线|0083,F84 测量点C相有功功率曲线|0084,F85 测量点无功功率曲线|0085,F86 测量点A相无功功率曲线|0086,F87 测量点B相无功功率曲线|0087,F88 测量点C相无功功率曲线|0088,F89 测量点A相电压曲线|0089,F90 测量点B相电压曲线|0090,F91 测量点C相电压曲线|0091,F92 测量点A相电流曲线|0092,F93 测量点B相电流曲线|0093,F94 测量点C相电流曲线|0094,F95 测量点零序电流曲线|0095,F97 测量点正向有功总电能量曲线|0097,F98 测量点正向无功总电能量曲线|0098,F99 测量点反向有功总电能量曲线|0099,F100 测量点反向无功总电能量曲线|0100,F101 测量点正向有功总电能示值曲线|0101,F102 测量点正向无功总电能示值曲线|0102,F103 测量点反向有功总电能示值曲线|0103,F104 测量点反向无功总电能示值曲线|0104,F105 测量点功率因数曲线|0105,F106 测量点A相功率因数曲线|0106,F107 测量点B相功率因数曲线|0107,F108 测量点C相功率因数曲线|0108,F109 测量点电压相位角曲线|0109,F110 测量点电流相位角曲线|0110,F113 日冻结测量点A相2-19次谐波电流日最大值及发生时间|0113,F114 日冻结测量点B相2-19次谐波电流日最大值及发生时间|0114,F115 日冻结测量点C相2-19次谐波电流日最大值及发生时间|0115,F116 日冻结测量点A相2-19次谐波电压含有率及总畸变率日最大值及发生时间|0116,F117 日冻结测量点B相2-19次谐波电压含有率及总畸变率日最大值及发生时间|0117,F118 日冻结测量点C相2-19次谐波电压含有率及总畸变率日最大值及发生时间|0118,F121 日冻结测量点A相谐波越限日统计数据|0121,F122 日冻结测量点B相谐波越限日统计数据|0122,F123 日冻结测量点C相谐波越限日统计数据|0123,F129 日冻结直流模拟量越限日累计时间/最大最小值及发生时间|0129,F130 月冻结直流模拟量月越限累计时间/最大最小值及发生时间|0130,F138 直流模拟量数据曲线|0138,F145 测量点一象限无功总电能示值曲线|0145,F146 测量点四象限无功总电能示值曲线|0146,F147 测量点二象限无功总电能示值曲线|0147,F148 测量点三象限无功总电能示值曲线|0148,F153 日冻结测量点分相正向有功电能示值|0153,F154 日冻结测量点分相正向无功电能示值|0154,F155 日冻结测量点分相反向有功电能示值|0155,F156 日冻结测量点分相反向无功电能示值|0156,F157 月冻结测量点分相正向有功电能示值|0157,F158 月冻结测量点分相正向无功电能示值|0158,F159 月冻结测量点分相反向有功电能示值|0159,F160 月冻结测量点分相反向无功电能示值|0160,F161 日冻结正向有功电能示值|0161,F162 日冻结正向无功(组合无功1)电能示值|0162,F163 日冻结反向有功电能示值|0163,F164 日冻结反向无功(组合无功1)电能示值|0164,F165 日冻结一象限无功电能示值|0165,F166 日冻结二象限无功电能示值|0166,F167 日冻结三象限无功电能示值|0167,F168 日冻结四象限无功电能示值|0168,F169 抄表日冻结正向有功电能示值|0169,F170 抄表日冻结正向无功(组合无功1)电能示值|0170,F171 抄表日冻结反向有功电能示值|0171,F172 抄表日冻结反向无功(组合无功1)电能示值|0172,F173 抄表日冻结一象限无功电能示值|0173,F174 抄表日冻结二象限无功电能示值|0174,F175 抄表日冻结三象限无功电能示值|0175,F176 抄表日冻结四象限无功电能示值|0176,F177 月冻结正向有功电能示值|0177,F178 月冻结正向无功(组合无功1)电能示值|0178,F179 月冻结反向有功电能示值|0179,F180 月冻结反向无功(组合无功1)电能示值|0180,F181 月冻结一象限无功电能示值|0181,F182 月冻结二象限无功电能示值|0182,F183 月冻结三象限无功电能示值|0183,F184 月冻结四象限无功电能示值|0184,F185 日冻结正向有功最大需量及发生时间|0185,F186 日冻结正向无功最大需量及发生时间|0186,F187 日冻结反向有功最大需量及发生时间|0187,F188 日冻结反向无功最大需量及发生时间|0188,F189 抄表日冻结正向有功最大需量及发生时间|0189,F190 抄表日冻结正向无功最大需量及发生时间|0190,F191 抄表日冻结反向有功最大需量及发生时间|0191,F192 抄表日冻结反向无功最大需量及发生时间|0192,F193 月冻结正向有功最大需量及发生时间|0193,F194 月冻结正向无功最大需量及发生时间|0194,F195 月冻结反向有功最大需量及发生时间|0195,F196 月冻结反向无功最大需量及发生时间|0196,F201 月冻结第一时区冻结正向有功电能示值|0201,F202 月冻结第二时区冻结正向有功电能示值|0202,F203 月冻结第三时区冻结正向有功电能示值|0203,F204 月冻结第四时区冻结正向有功电能示值|0204,F205 月冻结第五时区冻结正向有功电能示值|0205,F206 月冻结第六时区冻结正向有功电能示值|0206,F207 月冻结第七时区冻结正向有功电能示值|0207,F208 月冻结第八时区冻结正向有功电能示值|0208,F209 日冻结电能表远程控制状态及信息|0209,F213 月冻结电能表开关操作次数及时间|0213,F214 月冻结电能表参数修改次数及时间|0214,F215 月冻结电能表购/用电信息|0215,F216 月冻结电能表结算信息|0216,F217 台区集中抄表载波主节点白噪声曲线|0217,F218 台区集中抄表载波主节点色噪声曲线|0218";
			return text.Split(new char[]
			{
				','
			});
		}
		private string[] ClassThree()
		{
			string text = string.Empty;
			text = "F1 请求重要事件|0001,F2 请求一般事件|0E|0002";
			return text.Split(new char[]
			{
				','
			});
		}
		private string GetItemAllStr(string pText, string[] allitem)
		{
			checked
			{
				string result;
				for (int i = 0; i < allitem.Length; i++)
				{
					if (allitem[i].IndexOf(pText) >= 0)
					{
						result = allitem[i];
						return result;
					}
				}
				result = "";
				return result;
			}
		}
		private string GetItemSubStr(string pText)
		{
			return pText.Split(new char[]
			{
				'|'
			})[1];
		}
		private void Get_Categories_Name(string afn, string fn, ref string _Categories, ref string _Name)
		{
			if (afn.ToUpper() == "0C")
			{
				_Categories = "请求1类数据";
				_Name = this.GetItemAllStr(fn, this.ClassOne());
			}
			else
			{
				if (afn.ToUpper() == "0D")
				{
					_Categories = "请求2类数据";
					_Name = this.GetItemAllStr(fn, this.ClassTwo());
				}
				else
				{
					if (afn.ToUpper() == "0E")
					{
						_Categories = "请求3类数据";
						_Name = this.GetItemAllStr(fn, this.ClassThree());
					}
				}
			}
		}
		public void AddRow(string iA1, string iA2, string iAFN, string iFN, string iPN, string iData)
		{
			Thread.Sleep(0);
			checked
			{
				if (base.InvokeRequired)
				{
					base.Invoke(new ActiveReport.AddRowDelegate(this.AddRow), new object[]
					{
						iA1,
						iA2,
						iAFN,
						iFN,
						iPN,
						iData
					});
				}
				else
				{
					Color backColor = Color.FromArgb(240, 240, 240);
					string empty = string.Empty;
					string empty2 = string.Empty;
					this.Get_Categories_Name(iAFN, iFN, ref empty, ref empty2);
					CollapseDataGridViewRow collapseDataGridViewRow = new CollapseDataGridViewRow();
					foreach (DataGridViewColumn dataGridViewColumn in this.grid1.Columns)
					{
						collapseDataGridViewRow.Cells.Add(dataGridViewColumn.CellTemplate.Clone() as DataGridViewCell);
					}
					collapseDataGridViewRow.IsCollapse = false;
					collapseDataGridViewRow.Cells[0].Value = empty.Trim();
					collapseDataGridViewRow.Cells[0].Style.BackColor = backColor;
					collapseDataGridViewRow.Cells[1].Value = empty2;
					collapseDataGridViewRow.Cells[1].Style.BackColor = backColor;
					collapseDataGridViewRow.Cells[2].Value = iAFN;
					collapseDataGridViewRow.Cells[2].Style.BackColor = backColor;
					collapseDataGridViewRow.Cells[3].Value = iFN.PadLeft(4, '0');
					collapseDataGridViewRow.Cells[3].Style.BackColor = backColor;
					collapseDataGridViewRow.Cells[4].Value = iPN;
					collapseDataGridViewRow.Cells[4].Style.BackColor = backColor;
					collapseDataGridViewRow.Cells[5].Value = iA1;
					collapseDataGridViewRow.Cells[5].Style.BackColor = backColor;
					collapseDataGridViewRow.Cells[6].Value = iA2;
					collapseDataGridViewRow.Cells[6].Style.BackColor = backColor;
					collapseDataGridViewRow.Cells[7].Value = "";
					collapseDataGridViewRow.Cells[7].Style.BackColor = backColor;
					collapseDataGridViewRow.Cells[8].Value = "";
					collapseDataGridViewRow.Cells[8].Style.BackColor = backColor;
					collapseDataGridViewRow.Cells[9].Value = DateTime.Now.ToLongTimeString();
					collapseDataGridViewRow.Cells[9].Style.BackColor = backColor;
					this.grid1.Rows.Add(collapseDataGridViewRow);
					DLT698_Recv dLT698_Recv = new DLT698_Recv();
					dLT698_Recv.DoInfo(iAFN, iFN, iData, false, "");
					for (int i = 0; i < dLT698_Recv.ItemData.Count; i++)
					{
						if (!string.IsNullOrEmpty(dLT698_Recv.ItemData[i].Items))
						{
							this.AddData(collapseDataGridViewRow, dLT698_Recv.ItemData[i].Items, dLT698_Recv.ItemData[i].Values);
						}
					}
				}
			}
		}
		private void AddData(CollapseDataGridViewRow ROW, string _items, string _values)
		{
			Thread.Sleep(0);
			if (base.InvokeRequired)
			{
				base.Invoke(new ActiveReport.AddDataDelegate(this.AddData), new object[]
				{
					ROW,
					_items,
					_values
				});
			}
			else
			{
				DataGridViewRow dataGridViewRow = new DataGridViewRow();
				foreach (DataGridViewColumn dataGridViewColumn in this.grid1.Columns)
				{
					dataGridViewRow.Cells.Add(dataGridViewColumn.CellTemplate.Clone() as DataGridViewCell);
				}
				dataGridViewRow.Cells[0].Value = "";
				dataGridViewRow.Cells[1].Value = "";
				dataGridViewRow.Cells[2].Value = "";
				dataGridViewRow.Cells[3].Value = "";
				dataGridViewRow.Cells[4].Value = "";
				dataGridViewRow.Cells[5].Value = "";
				dataGridViewRow.Cells[6].Value = "";
				dataGridViewRow.Cells[7].Value = _items;
				dataGridViewRow.Cells[8].Value = _values;
				ROW.Rows.Add(dataGridViewRow);
			}
		}
		protected override void Dispose(bool disposing)
		{
			if (disposing && this.components != null)
			{
				this.components.Dispose();
			}
			base.Dispose(disposing);
		}
		private void InitializeComponent()
		{
			this.components = new Container();
			this.contextMenuStrip1 = new ContextMenuStrip(this.components);
			this.清空数据ToolStripMenuItem = new ToolStripMenuItem();
			this.contextMenuStrip1.SuspendLayout();
			base.SuspendLayout();
			this.contextMenuStrip1.Items.AddRange(new ToolStripItem[]
			{
				this.清空数据ToolStripMenuItem
			});
			this.contextMenuStrip1.Name = "contextMenuStrip1";
			this.contextMenuStrip1.Size = new Size(153, 48);
			this.清空数据ToolStripMenuItem.Name = "清空数据ToolStripMenuItem";
			this.清空数据ToolStripMenuItem.Size = new Size(152, 22);
			this.清空数据ToolStripMenuItem.Text = "清空数据";
			this.清空数据ToolStripMenuItem.Click += new EventHandler(this.清空数据ToolStripMenuItem_Click);
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(657, 433);
			this.Font = new Font("宋体", 9f, FontStyle.Regular, GraphicsUnit.Point, 134);
			base.Name = "ActiveReport";
			this.Text = "主动上报";
			base.Shown += new EventHandler(this.ActiveReport_Shown);
			this.contextMenuStrip1.ResumeLayout(false);
			base.ResumeLayout(false);
		}
	}
}
