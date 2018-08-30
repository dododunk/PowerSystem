using System;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Globalization;
using System.Text;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
	public class iForm : Form
	{
		public MenuContext menu = new MenuContext();
		public string TimePeriods = "0:00-0:30~0:30-1:00~1:00-1:30~1:30-2:00~2:00-2:30~2:30-3:00~3:00-3:30~3:30-4:00~4:00-4:30~4:30-5:00~5:00-5:30~5:30-6:00~6:00-6:30~6:30-7:00~7:00-7:30~7:30-8:00~8:00-8:30~8:30-9:00~9:00-9:30~9:30-10:00~10:00-10:30~10:30-11:00~11:00-11:30~11:30-12:00~12:00-12:30~12:30-13:00~13:00-13:30~13:30-14:00~14:00-14:30~14:30-15:00~15:00-15:30~15:30-16:00~16:00-16:30~16:30-17:00~17:00-18:30~17:30-18:00~18:00-18:30~18:30-19:00~19:00-19:30~19:30-20:00~20:00-20:30~20:30-21:00~21:00-22:30~21:30-22:00~22:00-22:30~22:30-23:00~23:00-23:30~23:30-0:30";
		public string TimePeriods2 = "0:00-1:00~1:00-2:00~2:00-3:00~3:00-4:00~4:00-5:00~5:00-6:00~6:00-7:00~7:00-8:00~8:00-9:00~9:00-10:00~10:00-11:00~11:00-12:00~12:00-13:00~13:00-14:00~14:00-15:00~15:00-16:00~16:00-17:00~17:00-18:00~18:00-19:00~19:00-20:00~20:00-21:00~21:00-22:00~22:00-23:00~23:00-0:00";
		public string ALLERC = "数据初始化和版本变更~参数丢失~参数变更~状态量位变~遥控跳闸~功控跳闸~电控跳闸~电能表参数变更~电流回路异常~电压回路异常~相序异常~电能表时间超差~电表故障信息~终端停/上电事件~谐波越限告警~直流模拟量越限告警~电压/电流不平衡越限~电容器投切自锁~购电参数设置~消息认证错误~终端故障~有功总电能量差动越限事件~电控告警事~电压越限~电流越限~视在功率越限~电能表示度下降~电能量超差~电能表走飞~电能表停走~终端485抄表失败~终端与主站通信流量超门限~电能表运行状态字变位~CT异常~发现未知电表~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
		//public PubFuncHelper gfunc = new PubFuncHelper();
		public string AFN;
		public string FN;
		public bool NeedSave;
		public bool IsCustomize;
		public string CustomizeItems = string.Empty;
		public string Data;
		public int Len;
		private IContainer components = null;
		public iForm()
		{
			this.InitializeComponent();
			this.NeedSave = false;
			this.IsCustomize = false;
		}
		public void OnRowPostPaint(object sender, DataGridViewRowPostPaintEventArgs e)
		{
			try
			{
				Rectangle bounds = new Rectangle(e.RowBounds.Location.X, Convert.ToInt32((float)e.RowBounds.Location.Y + ((float)e.RowBounds.Height - this.Font.Size) / 2f), 35, e.RowBounds.Height);
				TextRenderer.DrawText(e.Graphics, checked(e.RowIndex + 1).ToString(), this.Font, bounds, Color.Black, TextFormatFlags.Right);
			}
			catch (Exception)
			{
			}
		}
		public void OnCellPainting(object sender, DataGridViewCellPaintingEventArgs e)
		{
			try
			{
				Color color = Color.FromKnownColor(KnownColor.Control);
				Color color2 = Color.FromKnownColor(KnownColor.Control);
				Rectangle rect = checked(new Rectangle(e.CellBounds.X - 1, e.CellBounds.Y - 1, e.CellBounds.Width, e.CellBounds.Height));
				if (e.ColumnIndex == -1)
				{
					Color color3 = Color.FromArgb(241, 244, 248);
					Color color4 = color2;
					using (Brush brush = new LinearGradientBrush(e.CellBounds, color3, color4, LinearGradientMode.Vertical))
					{
						e.Graphics.FillRectangle(brush, e.CellBounds);
						e.Graphics.DrawRectangle(Pens.Silver, rect);
					}
					DataGridViewPaintParts paintParts = DataGridViewPaintParts.Border | DataGridViewPaintParts.ContentBackground | DataGridViewPaintParts.ContentForeground | DataGridViewPaintParts.ErrorIcon | DataGridViewPaintParts.Focus | DataGridViewPaintParts.SelectionBackground;
					e.Paint(e.ClipBounds, paintParts);
					e.Handled = true;
				}
				if (e.RowIndex == -1)
				{
					Color color3 = Color.FromArgb(241, 244, 248);
					Color color4 = color;
					using (Brush brush = new LinearGradientBrush(e.CellBounds, color3, color4, LinearGradientMode.Vertical))
					{
						e.Graphics.FillRectangle(brush, e.CellBounds);
						e.Graphics.DrawRectangle(Pens.Silver, rect);
					}
					DataGridViewPaintParts paintParts = DataGridViewPaintParts.Border | DataGridViewPaintParts.ContentBackground | DataGridViewPaintParts.ContentForeground | DataGridViewPaintParts.ErrorIcon | DataGridViewPaintParts.Focus | DataGridViewPaintParts.SelectionBackground;
					e.Paint(e.ClipBounds, paintParts);
					e.Handled = true;
				}
				if (e.ColumnIndex == -1 && e.RowIndex == -1)
				{
					e.Graphics.DrawRectangle(Pens.Silver, rect);
				}
			}
			catch
			{
			}
		}
		protected virtual void GetText()
		{
		}
		public virtual void SetText()
		{
		}
		
		public void SetCheck(bool ck)
		{
			foreach (Control control in base.Controls)
			{
				if (control is CheckBox)
				{
					((CheckBox)control).Checked = ck;
				}
			}
		}
		public  string OperaSend(string Value, int Num, string type)
		{
			checked
			{
				string result;
				if (string.IsNullOrEmpty(Value) & type.Trim().ToUpper() != "ASCII")
				{
					result = "";
				}
				else
				{
					string text = string.Empty;
					Value = Value.Trim();
					string text2 = type.ToUpper();
					switch (text2)
					{
					case "BIN":
						{
							long num2 = long.Parse(Value);
							string arg_323_0 = "X";
							int num = Num * 2;
							string val = num2.ToString(arg_323_0 + num.ToString());
							text = DataConvert.ReverseStr(val);
							break;
						}

					case "":
					case "BCD":
                        text = DataConvert.ReverseStr(Value.PadLeft(Num * 2, '0'));
						break;

					case "HEX":
						text = Value.PadRight(Num * 2, '0');
						break;

					case "BS":
					case "BS8":
					case "BS16":
					case "BS24":
					case "BS32":
					case "BS64":
						{
							string text3 = DataConvert.ReverseStr(Value, 1);
							string text4 = string.Empty;
							for (int i = 0; i < text3.Length; i += 8)
							{
								text4 += PubFuncHelper.BinToHex(text3.Substring(i, 8)).ToString("X2");
							}
							text += DataConvert.ReverseStr(text4);
							break;
						}

					case "ASCII":
                        text = DataConvert.ASCIIToHexStr(Value).PadRight(Num * 2, '0');
						break;

					case "A2":
					case "A3":
					case "A4":
					case "A5":
					case "A6":
					case "A9":
					case "A25":
						text = Value;
						break;

					case "A1":
						{
							Value = Value.Replace("年", "-");
							Value = Value.Replace("月", "-");
							Value = Value.Replace("日", " ");
							Value = Value.Replace("时", "：");
							Value = Value.Replace("分", "：");
							Value = Value.Replace("秒", "");
							string text5 = string.Empty;
							DateTime dateTime = DateTime.Parse(Value);
							int num = dateTime.Second;
							text5 = num.ToString("00");
							string arg_49C_0 = text5;
							num = dateTime.Minute;
							text5 = arg_49C_0 + num.ToString("00");
							string arg_4BA_0 = text5;
							num = dateTime.Hour;
							text5 = arg_4BA_0 + num.ToString("00");
							string arg_4D8_0 = text5;
							num = dateTime.Day;
							text5 = arg_4D8_0 + num.ToString("00");
							int num3 = (int)dateTime.DayOfWeek;
							if (num3 == 0)
							{
								num3 = 7;
							}
							num = dateTime.Month;
							text5 += (int.Parse(num.ToString(), NumberStyles.HexNumber) | num3 << 5).ToString("X2");
							string arg_54D_0 = text5;
							num = dateTime.Year;
							text5 = arg_54D_0 + num.ToString("0000").Substring(2, 2);
							text = text5;
							break;
						}

					case "A7":
						{
							string text5 = string.Empty;
							text5 = string.Format("{0:000.0}", decimal.Parse(Value));
							text5 = text5.Replace(".", "");
							text5 = DataConvert.ReverseStr(text5);
							text = text5;
							break;
						}

					case "A8":
						{
							string text5 = string.Empty;
							text5 = string.Format("{0:0000}", decimal.Parse(Value));
							text5 = text5.Replace(".", "");
							text5 = DataConvert.ReverseStr(text5);
							text = text5;
							break;
						}

					case "A10":
						text = DataConvert.ReverseStr(Value.PadLeft(6, '0'));
						break;

					case "A11":
						text = DataConvert.ReverseStr(Value.PadLeft(8, '0'));
						break;

					case "A12":
						text = DataConvert.ReverseStr(Value.PadLeft(12, '0'));
						break;

					case "A13":
						{
							string text5 = string.Empty;
							text5 = string.Format("{0:0000.0000}", decimal.Parse(Value));
							text5 = text5.Replace(".", "");
							text5 = DataConvert.ReverseStr(text5);
							text = text5;
							break;
						}

					case "A14":
						{
							string text5 = string.Empty;
							text5 = string.Format("{0:000000.0000}", decimal.Parse(Value));
							text5 = text5.Replace(".", "");
                            text5 = DataConvert.ReverseStr(text5);
							text = text5;
							break;
						}

					case "A15":
						Value = Value.Replace("年", "-");
						Value = Value.Replace("月", "-");
						Value = Value.Replace("日", " ");
						Value = Value.Replace("时", "：");
						Value = Value.Replace("分", "：");
						Value = Value.Replace("秒", "");
                        text = DataConvert.ReverseStr(Convert.ToDateTime(Value).ToString("yyMMddHHmm"));
						break;

					case "A16":
					case "A17":
					case "A18":
					case "A19":
						Value = Value.Replace("年", "-");
						Value = Value.Replace("月", "-");
						Value = Value.Replace("日", " ");
						Value = Value.Replace("时", "：");
						Value = Value.Replace("分", "：");
						Value = Value.Replace("秒", "");
						Value = Value.Replace(" ", "");
						Value = Value.Replace(":", "");
						Value = Value.Replace("-", "");
						Value = Value.Replace(".", "");
                        text = DataConvert.ReverseStr(Value);
						break;

					case "A20":
						Value = Value.Replace("年", "-");
						Value = Value.Replace("月", "-");
						Value = Value.Replace("日", " ");
						Value = Value.Replace("时", "：");
						Value = Value.Replace("分", "：");
						Value = Value.Replace("秒", "");
						text = DataConvert.ReverseStr(Convert.ToDateTime(Value).ToString("yyMMdd"));
						break;

					case "A21":
						Value = Value.Replace("年", "-");
						Value = Value.Replace("月", "-");
						Value = Value.Replace("日", " ");
						Value = Value.Replace("时", "：");
						Value = Value.Replace("分", "：");
						Value = Value.Replace("秒", "");
						Value = Convert.ToDateTime(Value).ToString("yy-MM");
						Value = Value.Replace(" ", "");
						Value = Value.Replace(":", "");
						Value = Value.Replace("-", "");
						Value = Value.Replace(".", "");
						text = DataConvert.ReverseStr(Value);
						break;

					case "A22":
						{
							string text5 = string.Empty;
							text5 = string.Format("{0:0.0}", float.Parse(Value));
							text = text5.Replace(".", "");
							break;
						}

					case "A23":
						{
							string text5 = string.Empty;
							text5 = string.Format("{0:00.0000}", float.Parse(Value));
							text5 = text5.Replace(".", "");
							text = DataConvert.ReverseStr(text5);
							break;
						}

					case "A24":
						Value = Value.Replace("年", "-");
						Value = Value.Replace("月", "-");
						Value = Value.Replace("日", " ");
						Value = Value.Replace("时", "：");
						Value = Value.Replace("分", "：");
						Value = Value.Replace("秒", "");
						Value = Value.Replace(" ", "");
						Value = Value.Replace(":", "");
						Value = Value.Replace("-", "");
						Value = Value.Replace(".", "");
						text = DataConvert.ReverseStr(Value);
						break;

					case "A26":
						{
							string text5 = string.Empty;
							text5 = string.Format("{0:0.000}", float.Parse(Value));
							text5 = text5.Replace(".", "");
							text = DataConvert.ReverseStr(text5);
							break;
						}

					case "A27":
						Value = Value.Replace(" ", "");
						Value = Value.Replace(":", "");
						Value = Value.Replace("-", "");
						Value = Value.Replace(".", "");
						text = DataConvert.ReverseStr(Value.PadLeft(8, '0'));
						break;
					}
					result = text;
				}
				return result;
			}
		}
		public string OperaRec(string Value, string type)
		{
			checked
			{
				string result;
				if (string.IsNullOrEmpty(Value))
				{
					result = "";
				}
				else
				{
					string text = string.Empty;
					string text2 = DataConvert.ReverseStr(Value);
					string text3 = type.ToUpper();
					switch (text3)
					{
					case "BIN":
						{
							int num = DataConvert.HexToInt(text2);
							text = num.ToString();
							break;
						}

					case "":
					case "BCD":
						text = text2;
						break;

					case "HEX":
						text = Value;
						break;

					case "BS":
					case "BS8":
					case "BS16":
					case "BS24":
					case "BS32":
					case "BS64":
						{
							string text4 = string.Empty;
							for (int i = 0; i < text2.Length; i += 2)
							{
								text4 += PubFuncHelper.HexToBin(text2.Substring(i, 2));
							}
							text = DataConvert.ReverseStr(text4, 1);
							break;
						}

					case "ASCII":
						text = DataConvert.HexStrToASCII(Value);
						break;

					case "A1":
						{
							string text5 = DataConvert.ReverseStr(Value);
							string text6 = string.Empty;
							text6 = text6 + text5.Substring(0, 2) + "年";
							int num2 = int.Parse(text5.Substring(2, 1), NumberStyles.HexNumber);
							string arg_354_0 = text6;
							int num = num2 & 1;
							text6 = arg_354_0 + num.ToString() + text5.Substring(3, 1) + "月";
							text6 = text6 + text5.Substring(4, 2) + "日";
							text6 = text6 + text5.Substring(6, 2) + "时";
							text6 = text6 + text5.Substring(8, 2) + "分";
							text6 = text6 + text5.Substring(10, 2) + "秒";
							text = text6;
							break;
						}

					case "A7":
						text = text2.Substring(0, 3) + "." + text2.Substring(3, 1);
						break;

					case "A8":
					case "A10":
					case "A12":
					case "A27":
						text = text2;
						break;

					case "A11":
						text = text2.Substring(0, 6) + "." + text2.Substring(6, 2);
						break;

					case "A13":
						text = text2.Substring(0, 4) + "." + text2.Substring(4, 4);
						break;

					case "A14":
						text = text2.Substring(0, 6) + "." + text2.Substring(6, 4);
						break;

					case "A15":
						text = string.Concat(new string[]
						{
							text2.Substring(0, 2),
							"年",
							text2.Substring(2, 2),
							"月",
							text2.Substring(4, 2),
							"日",
							text2.Substring(6, 2),
							"时",
							text2.Substring(8, 2),
							"分",
							text2.Substring(10, 2),
							"秒"
						});
						break;

					case "A16":
						text = string.Concat(new string[]
						{
							text2.Substring(0, 2),
							"日",
							text2.Substring(2, 2),
							"时",
							text2.Substring(4, 2),
							"分",
							text2.Substring(6, 2),
							"秒"
						});
						break;

					case "A17":
						text = string.Concat(new string[]
						{
							text2.Substring(0, 2),
							"月",
							text2.Substring(2, 2),
							"日",
							text2.Substring(4, 2),
							"时",
							text2.Substring(6, 2),
							"分"
						});
						break;

					case "A18":
						text = string.Concat(new string[]
						{
							text2.Substring(0, 2),
							"日",
							text2.Substring(2, 2),
							"时",
							text2.Substring(4, 2),
							"分"
						});
						break;

					case "A19":
						text = text2.Substring(0, 2) + "时" + text2.Substring(2, 2) + "分";
						break;

					case "A20":
						text = string.Concat(new string[]
						{
							text2.Substring(0, 2),
							"年",
							text2.Substring(2, 2),
							"月",
							text2.Substring(4, 2),
							"日"
						});
						break;

					case "A21":
						text = text2.Substring(0, 2) + "年" + text2.Substring(2, 2) + "月";
						break;

					case "A22":
						text = text2.Substring(0, 1) + "." + text2.Substring(1, 1);
						break;

					case "A23":
						text = text2.Substring(0, 2) + "." + text2.Substring(2, 4);
						break;

					case "A24":
						text = text2.Substring(0, 2) + "日" + text2.Substring(2, 2) + "时";
						break;

					case "A26":
						text = text2.Substring(0, 1) + "." + text2.Substring(1, 3);
						break;
					}
					if (text.ToUpper().IndexOf("EE") >= 0)
					{
						text = "";
					}
					result = text;
				}
				return result;
			}
		}
		private void IFormFormClosing(object sender, FormClosingEventArgs e)
		{
			if (this.NeedSave)
			{
				this.GetText();
			}
		}
		
		public string[] ClassOne()
		{
			string text = string.Empty;
			text = "F1 终端版本信息|0001,F2 终端日历时钟|0002,F3 终端参数状态|0003,F4 终端上行通信状态|0004,F5 终端控制设置状态|0005,F6 终端当前控制状态|0006,F7 终端事件计数器当前值|0007,F8 终端事件标志状态|0008,F9 终端状态量及变位标志|0009,F10 终端与主站当日/月通信流量|0010,F11 终端集中抄表状态信息|0011,F12 终端网路信号品质|0012,F17 当前总加有功功率|0017,F18 当前总加无功功率|0018,F19 当日总加有功电能量|0019,F20 当日总加无功电能量|0020,F21 当月总加有功电能量|0021,F22 当月总加无功电能量|0022,F23 终端当前剩余电量|0023,F24 当前功率下浮控控后总加有功功率冻结值|0024,F25 当前三相及总有无功功率/功率因数/三相电压/电流/零序电流/视在功率|0025,F26 A/B/C三相断相统计数据及最近一次断相记录|0026,F27 电能表日历时钟/编程次数及其最近一次操作时间|0027,F28 电表运行状态字及其变位标志|0028,F29 当前铜损/铁损有功总电能示值|0029,F30 上一结算日铜损/铁损有功总电能示值|0030,F31 当前[A/B/C]三相正/反向有功电能示值/组合无功[1/2]电能示值|0031,F32 上一结算日[A/B/C]三相正/反向有功电能示值/组合无功[1/2]电能示值|0032,F33 当前正向有无功电能示值/一四象限无功电能示值|0033,F34 当前反向有无功电能示值/二三象限无功电能示值|0034,F35 当月正向有无功最大需量及发生时间|0035,F36 当月反向有无功最大需量及发生时间|0036,F37 上月(上一结算日)正向有无功电能示值/一四象限无功电能示值|0037,F38 上月(上一结算日)反向有无功电能示值/二三象限无功电能示值|0038,F39 上月(上一结算日)正向有无功最大需量及发生时间|0039,F40 上月(上一结算日)反向有无功最大需量及发生时间|0040,F41 当日正向有功电能量|0041,F42 当日正向无功电能量|0042,F43 当日反向有功电能量|0043,F44 当日反向无功电能量|0044,F45 当月正向有功电能量|0045,F46 当月正向无功电能量|0046,F47 当月反向有功电能量|0047,F48 当月反向无功电能量|0048,F49 当前电压/电流相位角|0049,F57 当前[A/B/C]三相电压/电流2-N次谐波有效值|0057,F58 当前[A/B/C]三相电压/电流2-N次谐波含有率|0058,F65 当前电容器投切状态|0065,F66 当前电容器累计补偿投入时间和次数|0066,F67 当日/当月电容器累计补偿的无功电能量|0067,F73 直流模拟量当前数据|0073,F81 小时冻结总加有功功率|0081,F82 小时冻结总加无功功率|0082,F83 小时冻结总加有功总电能量|0083,F84 小时冻结总加无功总电能量|0084,F89 小时冻结有功功率|0089,F90 小时冻结A相有功功率|0090,F91 小时冻结B相有功功率|0091,F92 小时冻结C相有功功率|0092,F93 小时冻结无功功率|0093,F94 小时冻结A相无功功率|0094,F95 小时冻结B相无功功率|0095,F96 小时冻结C相无功功率|0096,F97 小时冻结A相电压|0097,F98 小时冻结B相电压|0098,F99 小时冻结C相电压|0099,F100 小时冻结A相电流|0100,F101 小时冻结B相电流|0101,F102 小时冻结C相电流|0102,F103 小时冻结零序电流|0103,F105 小时冻结正向有功总电能量|0105,F106 小时冻结正向无功总电能量|0106,F107 小时冻结反向有功总电能量|0107,F108 小时冻结反向无功总电能量|0108,F109 小时冻结正向有功总电能示值|0109,F110 小时冻结正向无功总电能示值|0110,F111 小时冻结反向有功总电能示值|0111,F112 小时冻结反向无功总电能示值|0112,F113 小时冻结总功率因数|0113,F114 小时冻结A相功率因数|0114,F115 小时冻结B相功率因数|0115,F116 小时冻结C相功率因数|0116,F121 小时冻结直流模拟量|0121,F129 当前正向有功电能示值|0129,F130 当前正向无功(组合无功1)电能示值|0130,F131 当前反向有功电能示值|0131,F132 当前反向无功(组合无功1)电能示值|0132,F133 当前一象限无功电能示值|0133,F134 当前二象限无功电能示值|0134,F135 当前三象限无功电能示值|0135,F136 当前四象限无功电能示值|0136,F137 上月(上一结算日)正向有功电能示值|0137,F138 上月(上一结算日)正向无功(组合无功1)电能示值|0138,F139 上月(上一结算日)反向有功电能示值|0139,F140 上月(上一结算日)反向无功(组合无功1)电能示值|0140,F141 上月(上一结算日)一象限无功电能示值|0141,F142 上月(上一结算日)二象限无功电能示值|0142,F143 上月(上一结算日)三象限无功电能示值|0143,F144 上月(上一结算日)四象限无功电能示值|0144,F145 当月正向有功最大需量及发生时间|0145,F146 当月正向无功最大需量及发生时间|0146,F147 当月反向有功最大需量及发生时间|0147,F148 当月反向无功最大需量及发生时间|0148,F149 上月(上一结算日)正向有功最大需量及发生时间|0149,F150 上月(上一结算日)正向无功最大需量及发生时间|0150,F151 上月(上一结算日)反向有功最大需量及发生时间|0151,F152 上月(上一结算日)反向无功最大需量及发生时间|0152,F153 第一时区冻结正向有功电能示值|0153,F154 第二时区冻结正向有功电能示值|0154,F155 第三时区冻结正向有功电能示值|0155,F156 第四时区冻结正向有功电能示值|0156,F157 第五时区冻结正向有功电能示值|0157,F158 第六时区冻结正向有功电能示值|0158,F159 第七时区冻结正向有功电能示值|0159,F160 第八时区冻结正向有功电能示值|0160,F161 电能表远程控制通断电状态及记录|0161,F165 电能表开关操作次数及时间|0165,F166 电能表参数修改次数及时间|0166,F167 电能表购/用电信息|0167,F168 电能表结算信息|0168,F169 集中抄表中继路由信息|0169,F170 集中抄表电表抄读信息|0170";
			return text.Split(new char[]
			{
				','
			});
		}
		public string[] ClassTwo()
		{
			string text = string.Empty;
			text = "F1 日冻结正向有无功电能示值/一四象限无功电能示值|0001,F2 日冻结反向有无功电能示值/二三象限无功电能示值|0002,F3 日冻结正向有无功最大需量及发生时间|0003,F4 日冻结反向有无功最大需量及发生时间|0004,F5 日冻结正向有功电能量|0005,F6 日冻结正向无功电能量|0006,F7 日冻结反向有功电能量|0007,F8 日冻结反向无功电能量|0008,F9 抄表日冻结正向有无功电能示值/一四象限无功电能示值|0009,F10 抄表日冻结反向有无功电能示值/二三象限无功电能示值|0010,F11 抄表日冻结电能表正向有无功最大需量及发生时间|0011,F12 抄表日冻结电能表反向有无功最大需量及发生时间|0012,F17 月冻结正向有无功电能示值/一四象限无功电能示值|0017,F18 月冻结反向有无功电能示值/二三象限无功电能示值|0018,F19 月冻结电能表正向有无功最大需量及发生时间|0019,F20 月冻结电能表反向有无功最大需量及发生时间|0020,F21 月冻结正向有功电能量|0021,F22 月冻结正向无功电能量|0022,F23 月冻结反向有功电能量|0023,F24 月冻结反向无功电能量|0024,F25 日冻结日总及分相最大有功功率及发生时间/有功功率为零时间|0025,F26 日冻结日总及分相最大需量及发生时间|0026,F27 日冻结日电压统计数据|0027,F28 日冻结日不平衡度越限累计时间|0028,F29 日冻结日电流越限数据|0029,F30 日冻结日视在功率越限累计时间|0030,F31 日负载率统计|0031,F32 日冻结电能表断相数据|0032,F33 月冻结月总及分相最大有功功率及发生时间/有功功率为零时间|0033,F34 月冻结月总及分相有功最大需量及发生时间|0034,F35 月冻结月电压统计数据|0035,F36 月冻结月不平衡度越限累计时间|0036,F37 月冻结月电流越限数据|0037,F38 月冻结月视在功率越限累计时间|0038,F39 月负载率统计|0039,F41 日冻结电容器累计投入时间和次数|0041,F42 日冻结日/月电容器累计补偿的无功电能量|0042,F43 日冻结日功率因数区段累计时间|0043,F44 月冻结月功率因数区段累计时间|0044,F45 日冻结铜损/铁损有功电能示值|0045,F46 月冻结铜损/铁损有功电能示值|0046,F49 日冻结终端日供电时间/日复位累计次数|0049,F50 日冻结终端日控制统计数据|0050,F51 月冻结终端月供电时间/月复位累计次数|0051,F52 月冻结终端月控制统计数据|0052,F53 终端与主站日通信流量|0053,F54 终端与主站月通信流量|0054,F57 日冻结总加组日最大最小有功功率及其发生时间/有功功率为零日累计时间|0057,F58 日冻结总加组日累计有功电能量|0058,F59 日冻结总加组日累计无功电能量|0059,F60 月冻结总加组月最大最小有功功率及其发生时间/有功功率为零累计时间|0060,F61 月冻结总加组月有功电能量|0061,F62 月冻结总加组月无功电能量|0062,F65 月冻结总加组超功率定值的月累计时间及月累计电能量|0065,F66 月冻结总加组超月电能量定值的月累计时间及月累计电能量|0066,F73 总加组有功功率曲线|0073,F74 总加组无功功率曲线|0074,F75 总加组有功电能量曲线|0075,F76 总加组无功电能量曲线|0076,F81 测量点有功功率曲线|0081,F82 测量点A相有功功率曲线|0082,F83 测量点B相有功功率曲线|0083,F84 测量点C相有功功率曲线|0084,F85 测量点无功功率曲线|0085,F86 测量点A相无功功率曲线|0086,F87 测量点B相无功功率曲线|0087,F88 测量点C相无功功率曲线|0088,F89 测量点A相电压曲线|0089,F90 测量点B相电压曲线|0090,F91 测量点C相电压曲线|0091,F92 测量点A相电流曲线|0092,F93 测量点B相电流曲线|0093,F94 测量点C相电流曲线|0094,F95 测量点零序电流曲线|0095,F97 测量点正向有功总电能量曲线|0097,F98 测量点正向无功总电能量曲线|0098,F99 测量点反向有功总电能量曲线|0099,F100 测量点反向无功总电能量曲线|0100,F101 测量点正向有功总电能示值曲线|0101,F102 测量点正向无功总电能示值曲线|0102,F103 测量点反向有功总电能示值曲线|0103,F104 测量点反向无功总电能示值曲线|0104,F105 测量点功率因数曲线|0105,F106 测量点A相功率因数曲线|0106,F107 测量点B相功率因数曲线|0107,F108 测量点C相功率因数曲线|0108,F109 测量点电压相位角曲线|0109,F110 测量点电流相位角曲线|0110,F113 日冻结测量点A相2-19次谐波电流日最大值及发生时间|0113,F114 日冻结测量点B相2-19次谐波电流日最大值及发生时间|0114,F115 日冻结测量点C相2-19次谐波电流日最大值及发生时间|0115,F116 日冻结测量点A相2-19次谐波电压含有率及总畸变率日最大值及发生时间|0116,F117 日冻结测量点B相2-19次谐波电压含有率及总畸变率日最大值及发生时间|0117,F118 日冻结测量点C相2-19次谐波电压含有率及总畸变率日最大值及发生时间|0118,F121 日冻结测量点A相谐波越限日统计数据|0121,F122 日冻结测量点B相谐波越限日统计数据|0122,F123 日冻结测量点C相谐波越限日统计数据|0123,F129 日冻结直流模拟量越限日累计时间/最大最小值及发生时间|0129,F130 月冻结直流模拟量月越限累计时间/最大最小值及发生时间|0130,F138 直流模拟量数据曲线|0138,F145 测量点一象限无功总电能示值曲线|0145,F146 测量点四象限无功总电能示值曲线|0146,F147 测量点二象限无功总电能示值曲线|0147,F148 测量点三象限无功总电能示值曲线|0148,F153 日冻结测量点分相正向有功电能示值|0153,F154 日冻结测量点分相正向无功电能示值|0154,F155 日冻结测量点分相反向有功电能示值|0155,F156 日冻结测量点分相反向无功电能示值|0156,F157 月冻结测量点分相正向有功电能示值|0157,F158 月冻结测量点分相正向无功电能示值|0158,F159 月冻结测量点分相反向有功电能示值|0159,F160 月冻结测量点分相反向无功电能示值|0160,F161 日冻结正向有功电能示值|0161,F162 日冻结正向无功(组合无功1)电能示值|0162,F163 日冻结反向有功电能示值|0163,F164 日冻结反向无功(组合无功1)电能示值|0164,F165 日冻结一象限无功电能示值|0165,F166 日冻结二象限无功电能示值|0166,F167 日冻结三象限无功电能示值|0167,F168 日冻结四象限无功电能示值|0168,F169 抄表日冻结正向有功电能示值|0169,F170 抄表日冻结正向无功(组合无功1)电能示值|0170,F171 抄表日冻结反向有功电能示值|0171,F172 抄表日冻结反向无功(组合无功1)电能示值|0172,F173 抄表日冻结一象限无功电能示值|0173,F174 抄表日冻结二象限无功电能示值|0174,F175 抄表日冻结三象限无功电能示值|0175,F176 抄表日冻结四象限无功电能示值|0176,F177 月冻结正向有功电能示值|0177,F178 月冻结正向无功(组合无功1)电能示值|0178,F179 月冻结反向有功电能示值|0179,F180 月冻结反向无功(组合无功1)电能示值|0180,F181 月冻结一象限无功电能示值|0181,F182 月冻结二象限无功电能示值|0182,F183 月冻结三象限无功电能示值|0183,F184 月冻结四象限无功电能示值|0184,F185 日冻结正向有功最大需量及发生时间|0185,F186 日冻结正向无功最大需量及发生时间|0186,F187 日冻结反向有功最大需量及发生时间|0187,F188 日冻结反向无功最大需量及发生时间|0188,F189 抄表日冻结正向有功最大需量及发生时间|0189,F190 抄表日冻结正向无功最大需量及发生时间|0190,F191 抄表日冻结反向有功最大需量及发生时间|0191,F192 抄表日冻结反向无功最大需量及发生时间|0192,F193 月冻结正向有功最大需量及发生时间|0193,F194 月冻结正向无功最大需量及发生时间|0194,F195 月冻结反向有功最大需量及发生时间|0195,F196 月冻结反向无功最大需量及发生时间|0196,F201 月冻结第一时区冻结正向有功电能示值|0201,F202 月冻结第二时区冻结正向有功电能示值|0202,F203 月冻结第三时区冻结正向有功电能示值|0203,F204 月冻结第四时区冻结正向有功电能示值|0204,F205 月冻结第五时区冻结正向有功电能示值|0205,F206 月冻结第六时区冻结正向有功电能示值|0206,F207 月冻结第七时区冻结正向有功电能示值|0207,F208 月冻结第八时区冻结正向有功电能示值|0208,F209 日冻结电能表远程控制状态及信息|0209,F213 月冻结电能表开关操作次数及时间|0213,F214 月冻结电能表参数修改次数及时间|0214,F215 月冻结电能表购/用电信息|0215,F216 月冻结电能表结算信息|0216,F217 台区集中抄表载波主节点白噪声曲线|0217,F218 台区集中抄表载波主节点色噪声曲线|0218";
			return text.Split(new char[]
			{
				','
			});
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
			base.SuspendLayout();
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(363, 234);
			
			base.MaximizeBox = false;
			base.MinimizeBox = false;
			base.Name = "iForm";
			base.ShowInTaskbar = false;
			base.StartPosition = FormStartPosition.CenterScreen;
			
			base.FormClosing += new FormClosingEventHandler(this.IFormFormClosing);
			base.ResumeLayout(false);
		}
	}
}
