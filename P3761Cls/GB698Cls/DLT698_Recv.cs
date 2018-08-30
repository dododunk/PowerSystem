using System;
using System.Collections.Generic;
using System.Globalization;
using System.Text;
using Helper;
namespace GB698Cls
{
	public class DLT698_Recv
	{
		public struct ItemsInfo
		{
			public string Items;
			public string Values;
			public void Clear()
			{
				this.Items = string.Empty;
				this.Values = string.Empty;
			}
		}
		//private PubFuncHelper gfunc = new PubFuncHelper();
		private DLT698Message gDLT698 = new DLT698Message();
		private string ALLERC = "数据初始化和版本变更~参数丢失~参数变更~状态量位变~遥控跳闸~功控跳闸~电控跳闸~电能表参数变更~电流回路异常~电压回路异常~相序异常~电能表时间超差~电表故障信息~终端停/上电事件~谐波越限告警~直流模拟量越限告警~电压/电流不平衡越限~电容器投切自锁~购电参数设置~消息认证错误~终端故障~有功总电能量差动越限事件~电控告警事~电压越限~电流越限~视在功率越限~电能表示度下降~电能量超差~电能表走飞~电能表停走~终端485抄表失败~终端与主站通信流量超门限~电能表运行状态字变位~CT异常~发现未知电表~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
		private string TimePeriods = "0:00-0:30~0:30-1:00~1:00-1:30~1:30-2:00~2:00-2:30~2:30-3:00~3:00-3:30~3:30-4:00~4:00-4:30~4:30-5:00~5:00-5:30~5:30-6:00~6:00-6:30~6:30-7:00~7:00-7:30~7:30-8:00~8:00-8:30~8:30-9:00~9:00-9:30~9:30-10:00~10:00-10:30~10:30-11:00~11:00-11:30~11:30-12:00~12:00-12:30~12:30-13:00~13:00-13:30~13:30-14:00~14:00-14:30~14:30-15:00~15:00-15:30~15:30-16:00~16:00-16:30~16:30-17:00~17:00-18:30~17:30-18:00~18:00-18:30~18:30-19:00~19:00-19:30~19:30-20:00~20:00-20:30~20:30-21:00~21:00-22:30~21:30-22:00~22:00-22:30~22:30-23:00~23:00-23:30~23:30-0:30";
		private string TimePeriods2 = "0:00-1:00~1:00-2:00~2:00-3:00~3:00-4:00~4:00-5:00~5:00-6:00~6:00-7:00~7:00-8:00~8:00-9:00~9:00-10:00~10:00-11:00~11:00-12:00~12:00-13:00~13:00-14:00~14:00-15:00~15:00-16:00~16:00-17:00~17:00-18:00~18:00-19:00~19:00-20:00~20:00-21:00~21:00-22:00~22:00-23:00~23:00-0:00";
		public int DataLength = 0;
		public List<DLT698_Recv.ItemsInfo> ItemData = new List<DLT698_Recv.ItemsInfo>();
		public string AF10_F9_Val = string.Empty;
		private string DoERC(string Value, ref int datalen, ref string sjname)
		{
			int num = DataConvert.HexToInt(Value.Substring(0, 2));
			datalen = DataConvert.HexToInt(Value.Substring(2, 2));
			string[] array = this.ALLERC.Split(new char[]
			{
				'~'
			});
			sjname = array[checked(num - 1)];
			string text = string.Empty;
			string text2 = text;
			text = string.Concat(new string[]
			{
				text2,
				"ERC",
				num.ToString(),
				":",
				sjname,
				",\r\n"
			});
			text = text + "长度Le=" + datalen.ToString() + ",\r\n";
			string value = Value.Substring(4);
			switch (num)
			{
			case 1:
				text += this.ERC1(value);
				break;

			case 2:
				text += this.ERC2(value);
				break;

			case 3:
				text += this.ERC3(value);
				break;

			case 4:
				text += this.ERC4(value);
				break;

			case 5:
				text += this.ERC5(value);
				break;

			case 6:
				text += this.ERC6(value);
				break;

			case 7:
				text += this.ERC7(value);
				break;

			case 8:
				text += this.ERC8(value);
				break;

			case 9:
				text += this.ERC9(value);
				break;

			case 10:
				text += this.ERC10(value);
				break;

			case 11:
				text += this.ERC11(value);
				break;

			case 12:
				text += this.ERC12(value);
				break;

			case 13:
				text += this.ERC13(value);
				break;

			case 14:
				text += this.ERC14(value);
				break;

			case 15:
				text += this.ERC15(value);
				break;

			case 16:
				text += this.ERC16(value);
				break;

			case 17:
				text += this.ERC17(value);
				break;

			case 18:
				text += this.ERC18(value);
				break;

			case 19:
				text += this.ERC19(value);
				break;

			case 20:
				text += this.ERC20(value);
				break;

			case 21:
				text += this.ERC21(value);
				break;

			case 22:
				text += this.ERC22(value);
				break;

			case 23:
				text += this.ERC23(value);
				break;

			case 24:
				text += this.ERC24(value);
				break;

			case 25:
				text += this.ERC25(value);
				break;

			case 26:
				text += this.ERC26(value);
				break;

			case 27:
				text += this.ERC27(value);
				break;

			case 28:
				text += this.ERC28(value);
				break;

			case 29:
				text += this.ERC29(value);
				break;

			case 30:
				text += this.ERC30(value);
				break;

			case 31:
				text += this.ERC31(value);
				break;

			case 32:
				text += this.ERC32(value);
				break;

			case 33:
				text += this.ERC33(value);
				break;

			case 34:
				text += this.ERC34(value);
				break;

			case 35:
				text += this.ERC35(value);
				break;
			}
			return text;
		}
		private string ERC1(string Value)
		{
			string text = string.Empty;
			int num = 0;
			text = text + "初始化/版本变更时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
				string text2 = ((num2 & 1) == 1) ? "终端进行参数及数据区初始化并记录初始化时间" : "无初始化发生";
				text2 += (((num2 >> 1 & 1) == 1) ? "终端版本变更并记录变更时间和变更前后版本号," : "版本未变更,");
				text = text + "事件标志:" + text2 + ",\r\n";
				num += 2;
				text = text + "变更前软件版本号:" + this.OperaRec(Value.Substring(num, 8), "ASCII") + ",\r\n";
				num += 8;
				text = text + "变更后软件版本号:" + this.OperaRec(Value.Substring(num, 8), "ASCII") + ",\r\n";
				num += 8;
				return text;
			}
		}
		private string ERC2(string Value)
		{
			string text = string.Empty;
			int num = 0;
			text = text + "发生时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
				string text2 = ((num2 & 1) == 1) ? "终端参数丢失," : "参数未丢失,";
				text2 += (((num2 >> 1 & 1) == 1) ? "测量点参数丢失," : "参数未丢失,");
				text = text + "事件标志:" + text2 + ",\r\n";
				num += 2;
				return text;
			}
		}
		private string ERC3(string Value)
		{
			string text = string.Empty;
			int num = 0;
			text = text + "参数更新时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				text = text + "启动站地址:" + this.OperaRec(Value.Substring(num, 2), "BIN") + ",\r\n";
				num += 2;
				int num2 = 1;
				while (true)
				{
					string text2 = string.Empty;
					string text3 = string.Empty;
					if (num + 8 >= Value.Length - 1)
					{
						break;
					}
					string text4 = Value.Substring(num, 8);
					num += 8;
					if (text4.IndexOf("EE") >= 0)
					{
						text3 = (text2 = "无效");
					}
					else
					{
						this.gDLT698.GetDataCellMark(text4, ref text2, ref text3);
					}
					string text5 = text;
					text = string.Concat(new string[]
					{
						text5,
						"变更参数数据单元标识",
						num2.ToString(),
						":FN=",
						text2,
						",PN=",
						text3,
						",\r\n"
					});
					num2++;
				}
				return text;
			}
		}
		private string ERC4(string Value)
		{
			string text = string.Empty;
			int num = 0;
			text = text + "变位时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				text = text + "状态变位D0-D7:" + this.OperaRec(Value.Substring(num, 2), "BS") + ",\r\n";
				num += 2;
				text = text + "变位后状态D0-D7:" + this.OperaRec(Value.Substring(num, 2), "BS") + ",\r\n";
				num += 2;
				return text;
			}
		}
		private string ERC5(string Value)
		{
			string text = string.Empty;
			int num = 0;
			text = text + "跳闸时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
				num += 2;
				string text2 = string.Empty;
				for (int i = 0; i < 8; i++)
				{
					if ((num2 >> i & 1) == 1)
					{
						text2 = text2 + "第" + (i + 1).ToString() + "控制轮次跳闸,";
					}
					else
					{
						text2 = text2 + "第" + (i + 1).ToString() + "控制轮次未跳闸,";
					}
				}
				text = text + "跳闸轮次:" + text2 + ",\r\n";
				text = text + "跳闸时功率:" + this.OperaRec(Value.Substring(num, 4), "A2") + ",\r\n";
				num += 4;
				text = text + "跳闸后2分钟的功率:" + this.OperaRec(Value.Substring(num, 4), "A2") + ",\r\n";
				num += 4;
				return text;
			}
		}
		private string ERC6(string Value)
		{
			string text = string.Empty;
			int num = 0;
			text = text + "跳闸时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
				num += 2;
				text = text + "总加组号:" + (num2 & 31).ToString() + ",\r\n";
				num2 = DataConvert.HexToInt(Value.Substring(num, 2));
				num += 2;
				string text2 = string.Empty;
				for (int i = 0; i < 8; i++)
				{
					if ((num2 >> i & 1) == 1)
					{
						text2 = text2 + "第" + (i + 1).ToString() + "控制轮次跳闸,";
					}
					else
					{
						text2 = text2 + "第" + (i + 1).ToString() + "控制轮次未跳闸,";
					}
				}
				text = text + "跳闸轮次:" + text2 + ",\r\n";
				num2 = DataConvert.HexToInt(Value.Substring(num, 2));
				num += 2;
				text2 = string.Empty;
				text2 = text2 + "时段控" + (((num2 & 1) == 1) ? "有效," : "无效,");
				text2 = text2 + "厂休控" + (((num2 >> 1 & 1) == 1) ? "有效," : "无效,");
				text2 = text2 + "营业报停控" + (((num2 >> 2 & 1) == 1) ? "有效," : "无效,");
				text2 = text2 + "当前功率下浮控" + (((num2 >> 3 & 1) == 1) ? "有效," : "无效,");
				text = text + "功控类别:" + text2 + ",\r\n";
				text = text + "跳闸前功率:" + this.OperaRec(Value.Substring(num, 4), "A2") + ",\r\n";
				num += 4;
				text = text + "跳闸后2分钟的功率:" + this.OperaRec(Value.Substring(num, 4), "A2") + ",\r\n";
				num += 4;
				text = text + "跳闸时功率定值:" + this.OperaRec(Value.Substring(num, 4), "A2") + ",\r\n";
				num += 4;
				return text;
			}
		}
		private string ERC7(string Value)
		{
			string text = string.Empty;
			int num = 0;
			text = text + "跳闸时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
				num += 2;
				text = text + "总加组号:" + (num2 & 31).ToString() + ",\r\n";
				num2 = DataConvert.HexToInt(Value.Substring(num, 2));
				num += 2;
				string text2 = string.Empty;
				for (int i = 0; i < 8; i++)
				{
					if ((num2 >> i & 1) == 1)
					{
						text2 = text2 + "第" + (i + 1).ToString() + "控制轮次跳闸,";
					}
					else
					{
						text2 = text2 + "第" + (i + 1).ToString() + "控制轮次未跳闸,";
					}
				}
				text = text + "跳闸轮次:" + text2 + ",\r\n";
				num2 = DataConvert.HexToInt(Value.Substring(num, 2));
				num += 2;
				text2 = string.Empty;
				text2 = text2 + "月电控" + (((num2 & 1) == 1) ? "有效," : "无效,");
				text2 = text2 + "购电控" + (((num2 >> 1 & 1) == 1) ? "有效," : "无效,");
				text = text + "电控类别:" + text2 + ",\r\n";
				text = text + "跳闸时电能量:" + this.OperaRec(Value.Substring(num, 8), "A3") + ",\r\n";
				num += 8;
				text = text + "跳闸时电能量定值:" + this.OperaRec(Value.Substring(num, 8), "A3") + ",\r\n";
				num += 8;
				return text;
			}
		}
		private string ERC8(string Value)
		{
			string str = string.Empty;
			int num = 0;
			str = str + "跳闸时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				int num2 = DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(num, 4)));
				num += 4;
				str = str + "测量点号:" + (num2 & 4095).ToString() + ",\r\n";
				num2 = DataConvert.HexToInt(Value.Substring(num, 2));
				num += 2;
				string text = string.Empty;
				text = text + "电能表费率时段" + (((num2 & 1) == 1) ? "变化," : "无变更,");
				text = text + "电能表编程时间" + (((num2 >> 1 & 1) == 1) ? "更改," : "未更改,");
				text = text + "电能表抄表日" + (((num2 >> 2 & 1) == 1) ? "更改," : "未更改,");
				text = text + "电能表脉冲常数" + (((num2 >> 3 & 1) == 1) ? "更改," : "未更改,");
				text = text + "电能表的互感器倍率" + (((num2 >> 4 & 1) == 1) ? "更改," : "未更改,");
				text = text + "电能表最大需量" + (((num2 >> 5 & 1) == 1) ? "清零," : "未被清零,");
				return str + "变更标志:" + text + ",\r\n";
			}
		}
		private string ERC9(string Value)
		{
			string text = string.Empty;
			int num = 0;
			text = text + "发生时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				int num2 = DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(num, 4)));
				num += 4;
				text += ((num2 >> 15 == 1) ? "起/止标志发生," : "起/止标志恢复,,\r\n");
				text = text + "测量点号:" + (num2 & 4095).ToString() + ",\r\n";
				num2 = DataConvert.HexToInt(Value.Substring(num, 2));
				num += 2;
				string text2 = string.Empty;
				text2 += (((num2 & 1) == 1) ? "A相发生异常," : "");
				text2 += (((num2 >> 1 & 1) == 1) ? "B相发生异常," : "");
				text2 += (((num2 >> 2 & 1) == 1) ? "C相发生异常," : "");
				text2 = text2 + "电流回路-" + "备用,短路,开路,反向".Split(new char[]
				{
					','
				})[num2 >> 6 & 3];
				text = text + "异常标志:" + text2 + ",\r\n";
				text = text + "发生时的Ua/Uab:" + this.OperaRec(Value.Substring(num, 4), "A7") + ",\r\n";
				num += 4;
				text = text + "发生时的Ub:" + this.OperaRec(Value.Substring(num, 4), "A7") + ",\r\n";
				num += 4;
				text = text + "发生时的Uc/Ucb:" + this.OperaRec(Value.Substring(num, 4), "A7") + ",\r\n";
				num += 4;
				text = text + "发生时的Ia:" + this.OperaRec(Value.Substring(num, 6), "A25") + ",\r\n";
				num += 6;
				text = text + "发生时的Ib:" + this.OperaRec(Value.Substring(num, 6), "A25") + ",\r\n";
				num += 6;
				text = text + "发生时的Ic:" + this.OperaRec(Value.Substring(num, 6), "A25") + ",\r\n";
				num += 6;
				text = text + "发生时电能表正向有功总电能示值:" + this.OperaRec(Value.Substring(num, 10), "A14") + ",\r\n";
				num += 10;
				return text;
			}
		}
		private string ERC10(string Value)
		{
			string text = string.Empty;
			int num = 0;
			text = text + "发生时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				int num2 = DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(num, 4)));
				num += 4;
				text += ((num2 >> 15 == 1) ? "起/止标志发生," : "起/止标志恢复,,\r\n");
				text = text + "测量点号:" + (num2 & 4095).ToString() + ",\r\n";
				num2 = DataConvert.HexToInt(Value.Substring(num, 2));
				num += 2;
				string text2 = string.Empty;
				text2 += (((num2 & 1) == 1) ? "A相发生异常," : "");
				text2 += (((num2 >> 1 & 1) == 1) ? "B相发生异常," : "");
				text2 += (((num2 >> 2 & 1) == 1) ? "C相发生异常," : "");
				text2 = text2 + "电流回路-" + "备用,断相,失压,备用".Split(new char[]
				{
					','
				})[num2 >> 6 & 3];
				text = text + "异常标志:" + text2 + ",\r\n";
				text = text + "发生时的Ua/Uab:" + this.OperaRec(Value.Substring(num, 4), "A7") + ",\r\n";
				num += 4;
				text = text + "发生时的Ub:" + this.OperaRec(Value.Substring(num, 4), "A7") + ",\r\n";
				num += 4;
				text = text + "发生时的Uc/Ucb:" + this.OperaRec(Value.Substring(num, 4), "A7") + ",\r\n";
				num += 4;
				text = text + "发生时的Ia:" + this.OperaRec(Value.Substring(num, 6), "A25") + ",\r\n";
				num += 6;
				text = text + "发生时的Ib:" + this.OperaRec(Value.Substring(num, 6), "A25") + ",\r\n";
				num += 6;
				text = text + "发生时的Ic:" + this.OperaRec(Value.Substring(num, 6), "A25") + ",\r\n";
				num += 6;
				text = text + "发生时电能表正向有功总电能示值:" + this.OperaRec(Value.Substring(num, 10), "A14") + ",\r\n";
				num += 10;
				return text;
			}
		}
		private string ERC11(string Value)
		{
			string text = string.Empty;
			int num = 0;
			text = text + "发生时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				int num2 = DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(num, 4)));
				num += 4;
				text += ((num2 >> 15 == 1) ? "起/止标志发生," : "起/止标志恢复,,\r\n");
				text = text + "测量点号:" + (num2 & 4095).ToString() + ",\r\n";
				text = text + "∠Ua/Uab:" + this.OperaRec(Value.Substring(num, 4), "A5") + ",\r\n";
				num += 4;
				text = text + "∠Ub:" + this.OperaRec(Value.Substring(num, 4), "A5") + ",\r\n";
				num += 4;
				text = text + "∠Uc/Ucb:" + this.OperaRec(Value.Substring(num, 4), "A5") + ",\r\n";
				num += 4;
				text = text + "∠Ia:" + this.OperaRec(Value.Substring(num, 4), "A5") + ",\r\n";
				num += 4;
				text = text + "∠Ib:" + this.OperaRec(Value.Substring(num, 4), "A5") + ",\r\n";
				num += 4;
				text = text + "∠Ic:" + this.OperaRec(Value.Substring(num, 4), "A5") + ",\r\n";
				num += 4;
				text = text + "发生时电能表正向有功总电能示值:" + this.OperaRec(Value.Substring(num, 10), "A14") + ",\r\n";
				num += 10;
				return text;
			}
		}
		private string ERC12(string Value)
		{
			string str = string.Empty;
			int num = 0;
			str = str + "发生时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				int num2 = DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(num, 4)));
				num += 4;
				str += ((num2 >> 15 == 1) ? "起/止标志发生," : "起/止标志恢复,,\r\n");
				return str + "测量点号:" + (num2 & 4095).ToString() + ",\r\n";
			}
		}
		private string ERC13(string Value)
		{
			string str = string.Empty;
			int num = 0;
			str = str + "发生时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				int num2 = DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(num, 4)));
				num += 4;
				str += ((num2 >> 15 == 1) ? "起/止标志发生," : "起/止标志恢复,,\r\n");
				str = str + "测量点号:" + (num2 & 4095).ToString() + ",\r\n";
				num2 = DataConvert.HexToInt(Value.Substring(num, 2));
				num += 2;
				string text = string.Empty;
				text += (((num2 & 1) == 1) ? "电能表编程次数或最大需量清零次数发生变化," : "");
				text += (((num2 >> 1 & 1) == 1) ? "电能表断相次数变化," : "");
				text += (((num2 >> 2 & 1) == 1) ? "电能表失压次数变化," : "");
				text += (((num2 >> 3 & 1) == 1) ? "电能表停电次数变化," : "");
				text += (((num2 >> 4 & 1) == 1) ? "电能表电池欠压," : "");
				return str + "异常标志:" + text + ",\r\n";
			}
		}
		private string ERC14(string Value)
		{
			string text = string.Empty;
			int num = 0;
			text = text + "停电发生时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				text = text + "上电时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
				num += 10;
				return text;
			}
		}
		private string ERC15(string Value)
		{
			string text = string.Empty;
			int num = 0;
			text = text + "发生时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				int num2 = DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(num, 4)));
				num += 4;
				string text2 = text;
				text = string.Concat(new string[]
				{
					text2,
					(num2 >> 15 == 1) ? "起/止标志发生," : "起/止标志恢复,",
					"测量点号:",
					(num2 & 4095).ToString(),
					",\r\n"
				});
				num2 = DataConvert.HexToInt(Value.Substring(num, 2));
				num += 2;
				string text3 = string.Empty;
				text3 += (((num2 >> 7 & 1) == 1) ? "电流越限事件," : "电压越限事件,");
				if ((num2 >> 7 & 1) == 1)
				{
					text3 += (((num2 & 1) == 1) ? "Iab/Ia有效," : "Iab/Ia异常,");
					text3 += (((num2 >> 1 & 1) == 1) ? "Ib有效," : "Ib异常,");
					text3 += (((num2 >> 2 & 1) == 1) ? "Icb/Ic有效," : "Icb/Ic异常,");
				}
				else
				{
					text3 += (((num2 & 1) == 1) ? "Uab/Ua有效," : "Uab/Ua异常,");
					text3 += (((num2 >> 1 & 1) == 1) ? "Ub有效," : "Ub异常,");
					text3 += (((num2 >> 2 & 1) == 1) ? "Ucb/Uc有效," : "Ucb/Uc异常,");
				}
				text = text + "异常标志:" + text3 + ",\r\n";
				long num3 = DataConvert.HexToLong(DataConvert.ReverseStr(Value.Substring(num, 6)));
				num += 6;
				text3 = string.Empty;
				for (int i = 0; i < 24; i++)
				{
					if ((num3 >> i & 1L) == 1L)
					{
						if (i == 0)
						{
							text3 += "总畸变越限,";
						}
						else
						{
							text3 = text3 + (i + 1).ToString() + "次越限,";
						}
					}
				}
				text = text + "谐波越限标志:" + text3 + ",\r\n";
				for (int i = 0; i < 20; i++)
				{
					if ((num2 >> 7 & 1) == 1)
					{
						if (i == 0)
						{
							text = text + "越限时总畸变电流有效值:" + this.OperaRec(Value.Substring(num, 4), "A6") + ",\r\n";
						}
						else
						{
							text2 = text;
							text = string.Concat(new string[]
							{
								text2,
								"越限时该相",
								(i + 1).ToString(),
								"次电流有效值:",
								this.OperaRec(Value.Substring(num, 4), "A6"),
								",\r\n"
							});
						}
					}
					else
					{
						if (i == 0)
						{
							text = text + "越限时总畸变电压含有率:" + this.OperaRec(Value.Substring(num, 4), "A5") + ",\r\n";
						}
						else
						{
							text2 = text;
							text = string.Concat(new string[]
							{
								text2,
								"越限时该相",
								(i + 1).ToString(),
								"次电压含有率:",
								this.OperaRec(Value.Substring(num, 4), "A5"),
								",\r\n"
							});
						}
					}
					num += 4;
				}
				return text;
			}
		}
		private string ERC16(string Value)
		{
			string str = string.Empty;
			int num = 0;
			str = str + "发生时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				int num2 = DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(num, 2)));
				num += 2;
				str += ((num2 >> 7 == 1) ? "起/止标志发生," : "起/止标志恢复,,\r\n");
				str = str + "测量点号:" + (num2 & 63).ToString() + ",\r\n";
				num2 = DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(num, 2)));
				num += 2;
				string text = string.Empty;
				text += (((num2 & 1) == 1) ? "越上限," : "");
				text += (((num2 >> 1 & 1) == 1) ? "越下限," : "");
				return str + "异常标志:" + text + ",\r\n";
			}
		}
		private string ERC17(string Value)
		{
			string text = string.Empty;
			int num = 0;
			text = text + "发生时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				int num2 = DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(num, 4)));
				num += 4;
				text += ((num2 >> 15 == 1) ? "起/止标志发生," : "起/止标志恢复,,\r\n");
				text = text + "测量点号:" + (num2 & 4095).ToString() + ",\r\n";
				num2 = DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(num, 2)));
				num += 2;
				string text2 = string.Empty;
				text2 += (((num2 & 1) == 1) ? "电压不平衡度越限有效," : "电压不平衡度越限无效,");
				text2 += (((num2 >> 1 & 1) == 1) ? "电流不平衡度越限有效," : "电流不平衡度越限无效,");
				text = text + "异常标志:" + text2 + ",\r\n";
				text = text + "发生时的电压不平衡度:" + this.OperaRec(Value.Substring(num, 4), "A5") + ",\r\n";
				num += 4;
				text = text + "发生时的电流不平衡度:" + this.OperaRec(Value.Substring(num, 4), "A5") + ",\r\n";
				num += 4;
				text = text + "发生时的Ua/Uab:" + this.OperaRec(Value.Substring(num, 4), "A7") + ",\r\n";
				num += 4;
				text = text + "发生时的Ub:" + this.OperaRec(Value.Substring(num, 4), "A7") + ",\r\n";
				num += 4;
				text = text + "发生时的Uc/Ucb:" + this.OperaRec(Value.Substring(num, 4), "A7") + ",\r\n";
				num += 4;
				text = text + "发生时的Ia:" + this.OperaRec(Value.Substring(num, 6), "A25") + ",\r\n";
				num += 6;
				text = text + "发生时的Ib:" + this.OperaRec(Value.Substring(num, 6), "A25") + ",\r\n";
				num += 6;
				text = text + "发生时的Ic:" + this.OperaRec(Value.Substring(num, 6), "A25") + ",\r\n";
				num += 6;
				return text;
			}
		}
		private string ERC18(string Value)
		{
			string text = string.Empty;
			int num = 0;
			text = text + "发生时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				int num2 = DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(num, 4)));
				num += 4;
				text += ((num2 >> 15 == 1) ? "起/止标志发生," : "起/止标志恢复,,\r\n");
				text = text + "测量点号:" + (num2 & 4095).ToString() + ",\r\n";
				num2 = DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(num, 2)));
				num += 2;
				string text2 = string.Empty;
				text2 += "过压,装置故障,执行回路故障".Split(new char[]
				{
					','
				})[num2 & 3];
				text = text + "异常标志:" + text2 + ",\r\n";
				num2 = DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(num, 4)));
				num += 4;
				text2 = string.Empty;
				for (int i = 0; i < 16; i++)
				{
					if ((num2 >> i & 1) == 1)
					{
						text2 = text2 + (i + 1).ToString() + "组电容器组自锁,";
					}
					else
					{
						text2 = text2 + (i + 1).ToString() + "组电容器组未自锁,";
					}
				}
				text = text + "电容器组标志:" + text2 + ",\r\n";
				text = text + "越限发生时功率因数:" + this.OperaRec(Value.Substring(num, 4), "A5") + ",\r\n";
				num += 4;
				text = text + "越限发生时无功功率:" + this.OperaRec(Value.Substring(num, 4), "A23") + ",\r\n";
				num += 4;
				text = text + "越限发生时电压:" + this.OperaRec(Value.Substring(num, 4), "A7") + ",\r\n";
				num += 4;
				return text;
			}
		}
		private string ERC19(string Value)
		{
			string text = string.Empty;
			int num = 0;
			text = text + "购电能量设置时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				int num2 = DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(num, 2)));
				num += 2;
				text = text + "总加组号:" + (num2 & 63).ToString() + ",\r\n";
				text = text + "购电单号:" + this.OperaRec(Value.Substring(num, 8), "BIN") + ",\r\n";
				num += 8;
				text = text + "追加/刷新标志:" + ((Value.Substring(num, 2) == "55") ? "追加," : "刷新,") + ",\r\n";
				num += 2;
				text = text + "购电量值:" + this.OperaRec(Value.Substring(num, 8), "A3") + ",\r\n";
				num += 8;
				text = text + "报警门限:" + this.OperaRec(Value.Substring(num, 8), "A3") + ",\r\n";
				num += 8;
				text = text + "跳闸门限:" + this.OperaRec(Value.Substring(num, 8), "A3") + ",\r\n";
				num += 8;
				text = text + "本次购电前剩余电能量:" + this.OperaRec(Value.Substring(num, 8), "A3") + ",\r\n";
				num += 8;
				text = text + "本次购电后剩余电能量:" + this.OperaRec(Value.Substring(num, 8), "A3") + ",\r\n";
				num += 8;
				return text;
			}
		}
		private string ERC20(string Value)
		{
			string text = string.Empty;
			int num = 0;
			text = text + "发生时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				text = text + "消息认证码PW:" + this.OperaRec(Value.Substring(num, 32), "BIN") + ",\r\n";
				num += 32;
				text = text + "启动站地址MSA:" + this.OperaRec(Value.Substring(num, 2), "BIN") + ",\r\n";
				num += 2;
				return text;
			}
		}
		private string ERC21(string Value)
		{
			string str = string.Empty;
			int num = 0;
			str = str + "发生时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
				num += 2;
				string str2 = string.Empty;
				switch (num2)
				{
				case 1:
					str2 = "终端主板内存故障,";
					break;

				case 2:
					str2 = "时钟故障,";
					break;

				case 3:
					str2 = "主板通信故障,";
					break;

				case 4:
					str2 = "485抄表故障,";
					break;

				case 5:
					str2 = "显示板故障,";
					break;

				case 6:
					str2 = "载波通道异常,";
					break;

				default:
					str2 = "备用,";
					break;
				}
				return str + "终端故障编码:" + str2 + ",\r\n";
			}
		}
		private string ERC22(string Value)
		{
			string text = string.Empty;
			int num = 0;
			text = text + "发生时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				int num2 = DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(num, 2)));
				num += 2;
				text += ((num2 >> 7 == 1) ? "起/止标志发生," : "起/止标志恢复,,\r\n");
				text = text + "电能量差动组号:" + (num2 & 63).ToString() + ",\r\n";
				text = text + "越限时对比总加组有功总电能量:" + this.OperaRec(Value.Substring(num, 8), "A3") + ",\r\n";
				num += 8;
				text = text + "越限时参照总加组有功总电能量:" + this.OperaRec(Value.Substring(num, 8), "A3") + ",\r\n";
				num += 8;
				text = text + "越限时差动越限相对偏差值:" + this.OperaRec(Value.Substring(num, 2), "BIN") + ",\r\n";
				num += 2;
				text = text + "越限时差动越限绝对偏差值:" + this.OperaRec(Value.Substring(num, 8), "A3") + ",\r\n";
				num += 8;
				int num3 = DataConvert.HexToInt(Value.Substring(num, 2));
				num += 2;
				text = text + "对比的总加组测量点数量:" + num3.ToString() + ",\r\n";
				for (int i = 0; i < num3; i++)
				{
					string text2 = text;
					text = string.Concat(new string[]
					{
						text2,
						"越限时对比总加组第",
						(i + 1).ToString(),
						"测量点有功总电能示值:",
						this.OperaRec(Value.Substring(num, 10), "A14"),
						",\r\n"
					});
					num += 10;
				}
				num3 = DataConvert.HexToInt(Value.Substring(num, 2));
				num += 2;
				text = text + "参照的总加组测量点数量:" + num3.ToString() + ",\r\n";
				for (int i = 0; i < num3; i++)
				{
					string text2 = text;
					text = string.Concat(new string[]
					{
						text2,
						"越限时参照总加组第",
						(i + 1).ToString(),
						"测量点有功总电能示值:",
						this.OperaRec(Value.Substring(num, 10), "A14"),
						",\r\n"
					});
					num += 10;
				}
				return text;
			}
		}
		private string ERC23(string Value)
		{
			string text = string.Empty;
			int num = 0;
			text = text + "告警时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				int num2 = DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(num, 2)));
				num += 2;
				text = text + "总加组号:" + (num2 & 63).ToString() + ",\r\n";
				num2 = DataConvert.HexToInt(Value.Substring(num, 2));
				num += 2;
				string text2 = string.Empty;
				for (int i = 0; i < 8; i++)
				{
					if ((num2 >> i & 1) == 1)
					{
						text2 = text2 + "第" + (i + 1).ToString() + "轮次投入,";
					}
					else
					{
						text2 = text2 + "第" + (i + 1).ToString() + "轮次未投入,";
					}
				}
				text = text + "投入轮次:" + text2 + ",\r\n";
				num2 = DataConvert.HexToInt(Value.Substring(num, 2));
				text = text + "电控类别:" + "月电控,购电控".Split(new char[]
				{
					','
				})[num2 - 1] + ",\r\n";
				text = text + "告警时电能量:" + this.OperaRec(Value.Substring(num, 8), "A3") + ",\r\n";
				num += 8;
				text = text + "告警时电控定值:" + this.OperaRec(Value.Substring(num, 8), "A3") + ",\r\n";
				num += 8;
				return text;
			}
		}
		private string ERC24(string Value)
		{
			string text = string.Empty;
			int num = 0;
			text = text + "发生时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				int num2 = DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(num, 4)));
				num += 4;
				text = text + ((num2 >> 15 == 1) ? "起/止标志发生," : "起/止标志恢复,") + ",\r\n";
				text = text + "测量点号:" + (num2 & 4095).ToString() + ",\r\n";
				num2 = DataConvert.HexToInt(Value.Substring(num, 2));
				num += 2;
				string text2 = string.Empty;
				text2 += (((num2 & 1) == 1) ? "A相越限," : "");
				text2 += (((num2 >> 1 & 1) == 1) ? "B相越限," : "");
				text2 += (((num2 >> 2 & 1) == 1) ? "C相越限," : "");
				text2 = text2 + "电压越限类型-" + "备用,越上上限,越下下限,备用".Split(new char[]
				{
					','
				})[num2 >> 6 & 3];
				text = text + "越限标志:" + text2 + ",\r\n";
				text = text + "发生时的Ua/Uab:" + this.OperaRec(Value.Substring(num, 4), "A7") + ",\r\n";
				num += 4;
				text = text + "发生时的Ub:" + this.OperaRec(Value.Substring(num, 4), "A7") + ",\r\n";
				num += 4;
				text = text + "发生时的Uc/Ucb:" + this.OperaRec(Value.Substring(num, 4), "A7") + ",\r\n";
				num += 4;
				return text;
			}
		}
		private string ERC25(string Value)
		{
			string text = string.Empty;
			int num = 0;
			text = text + "发生时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				int num2 = DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(num, 4)));
				num += 4;
				text += ((num2 >> 15 == 1) ? "起/止标志发生," : "起/止标志恢复,,\r\n");
				text = text + "测量点号:" + (num2 & 4095).ToString() + ",\r\n";
				num2 = DataConvert.HexToInt(Value.Substring(num, 2));
				num += 2;
				string text2 = string.Empty;
				text2 += (((num2 & 1) == 1) ? "A相越限," : "");
				text2 += (((num2 >> 1 & 1) == 1) ? "B相越限," : "");
				text2 += (((num2 >> 2 & 1) == 1) ? "C相越限," : "");
				text2 = text2 + "电压越限类型-" + "备用,越上上限,越下下限,备用".Split(new char[]
				{
					','
				})[num2 >> 6 & 3];
				text = text + "越限标志:" + text2 + ",\r\n";
				text = text + "发生时的Ia:" + this.OperaRec(Value.Substring(num, 6), "A25") + ",\r\n";
				num += 6;
				text = text + "发生时的Ib:" + this.OperaRec(Value.Substring(num, 6), "A25") + ",\r\n";
				num += 6;
				text = text + "发生时的Ic:" + this.OperaRec(Value.Substring(num, 6), "A25") + ",\r\n";
				num += 6;
				return text;
			}
		}
		private string ERC26(string Value)
		{
			string text = string.Empty;
			int num = 0;
			text = text + "发生时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				int num2 = DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(num, 4)));
				num += 4;
				text += ((num2 >> 15 == 1) ? "起/止标志发生," : "起/止标志恢复,,\r\n");
				text = text + "测量点号:" + (num2 & 4095).ToString() + ",\r\n";
				num2 = DataConvert.HexToInt(Value.Substring(num, 2));
				num += 2;
				string text2 = string.Empty;
				text2 += (((num2 & 1) == 1) ? "A相越限," : "");
				text2 += (((num2 >> 1 & 1) == 1) ? "B相越限," : "");
				text2 += (((num2 >> 2 & 1) == 1) ? "C相越限," : "");
				text2 = text2 + "电压越限类型-" + "备用,越上上限,越下下限,备用".Split(new char[]
				{
					','
				})[num2 >> 6 & 3];
				text = text + "越限标志:" + text2 + ",\r\n";
				text = text + "发生时的视在功率:" + this.OperaRec(Value.Substring(num, 6), "A23") + ",\r\n";
				num += 6;
				text = text + "发生时的视在功率限值:" + this.OperaRec(Value.Substring(num, 6), "A23") + ",\r\n";
				num += 6;
				return text;
			}
		}
		private string ERC27(string Value)
		{
			string text = string.Empty;
			int num = 0;
			text = text + "发生时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				int num2 = DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(num, 4)));
				num += 4;
				string text2 = text;
				text = string.Concat(new string[]
				{
					text2,
					(num2 >> 15 == 1) ? "起/止标志发生," : "起/止标志恢复,",
					"测量点号:",
					(num2 & 4095).ToString(),
					",\r\n"
				});
				text = text + "下降前电能表正向有功总电能示值:" + this.OperaRec(Value.Substring(num, 10), "A14") + ",\r\n";
				num += 10;
				text = text + "下降后电能表正向有功总电能示值:" + this.OperaRec(Value.Substring(num, 10), "A14") + ",\r\n";
				num += 10;
				return text;
			}
		}
		private string ERC28(string Value)
		{
			string text = string.Empty;
			int num = 0;
			text = text + "发生时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				int num2 = DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(num, 4)));
				num += 4;
				text += ((num2 >> 15 == 1) ? "起/止标志发生," : "起/止标志恢复,,\r\n");
				text = text + "测量点号:" + (num2 & 4095).ToString() + ",\r\n";
				text = text + "下降前电能表正向有功总电能示值:" + this.OperaRec(Value.Substring(num, 10), "A14") + ",\r\n";
				num += 10;
				text = text + "下降后电能表正向有功总电能示值:" + this.OperaRec(Value.Substring(num, 10), "A14") + ",\r\n";
				num += 10;
				text = text + "电能量超差阈值:" + this.OperaRec(Value.Substring(num, 2), "A22") + ",\r\n";
				num += 2;
				return text;
			}
		}
		private string ERC29(string Value)
		{
			string text = string.Empty;
			int num = 0;
			text = text + "发生时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				int num2 = DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(num, 4)));
				num += 4;
				text += ((num2 >> 15 == 1) ? "起/止标志发生," : "起/止标志恢复,,\r\n");
				text = text + "测量点号:" + (num2 & 4095).ToString() + ",\r\n";
				text = text + "电能表飞走发生前正向有功总电能示值:" + this.OperaRec(Value.Substring(num, 10), "A14") + ",\r\n";
				num += 10;
				text = text + "电能表飞走发生后正向有功总电能示值:" + this.OperaRec(Value.Substring(num, 10), "A14") + ",\r\n";
				num += 10;
				text = text + "电能表飞走阈值:" + this.OperaRec(Value.Substring(num, 2), "A22") + ",\r\n";
				num += 2;
				return text;
			}
		}
		private string ERC30(string Value)
		{
			string text = string.Empty;
			int num = 0;
			text = text + "发生时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				int num2 = DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(num, 4)));
				num += 4;
				text += ((num2 >> 15 == 1) ? "起/止标志发生," : "起/止标志恢复,,\r\n");
				text = text + "测量点号:" + (num2 & 4095).ToString() + ",\r\n";
				text = text + "电能表停走发生时正向有功总电能示值:" + this.OperaRec(Value.Substring(num, 10), "A14") + ",\r\n";
				num += 10;
				text = text + "电能表停走阈值:" + this.OperaRec(Value.Substring(num, 2), "A22") + ",\r\n";
				num += 2;
				return text;
			}
		}
		private string ERC31(string Value)
		{
			string text = string.Empty;
			int num = 0;
			text = text + "发生时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				int num2 = DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(num, 4)));
				num += 4;
				text += ((num2 >> 15 == 1) ? "起/止标志发生," : "起/止标志恢复,,\r\n");
				text = text + "测量点号:" + (num2 & 4095).ToString() + ",\r\n";
				text = text + "最近一次抄表成功时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
				num += 10;
				text = text + "最近一次抄表成功正向有功总电能示值:" + this.OperaRec(Value.Substring(num, 10), "A14") + ",\r\n";
				num += 10;
				text = text + "最近一次抄表成功正向无功总电能示值:" + this.OperaRec(Value.Substring(num, 8), "A11") + ",\r\n";
				num += 8;
				return text;
			}
		}
		private string ERC32(string Value)
		{
			string text = string.Empty;
			int num = 0;
			text = text + "发生时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				text = text + "当月已发生的通信流量:" + this.OperaRec(Value.Substring(num, 8), "BIN") + ",\r\n";
				num += 8;
				text = text + "月通信流量门限:" + this.OperaRec(Value.Substring(num, 8), "BIN") + ",\r\n";
				num += 8;
				return text;
			}
		}
		private string ERC33(string Value)
		{
			string text = string.Empty;
			int num = 0;
			text = text + "发生时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				int num2 = DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(num, 4)));
				num += 4;
				text = text + "测量点号:" + (num2 & 4095).ToString() + ",\r\n";
				text = text + "电表运行状态字变位标志1(D0-D15):" + this.OperaRec(Value.Substring(num, 4), "BS") + ",\r\n";
				num += 4;
				text = text + "电表运行状态字变位标志2(D0-D15):" + this.OperaRec(Value.Substring(num, 4), "BS") + ",\r\n";
				num += 4;
				text = text + "电表运行状态字变位标志3(D0-D15):" + this.OperaRec(Value.Substring(num, 4), "BS") + ",\r\n";
				num += 4;
				text = text + "电表运行状态字变位标志4(D0-D15):" + this.OperaRec(Value.Substring(num, 4), "BS") + ",\r\n";
				num += 4;
				text = text + "电表运行状态字变位标志5(D0-D15):" + this.OperaRec(Value.Substring(num, 4), "BS") + ",\r\n";
				num += 4;
				text = text + "电表运行状态字变位标志6(D0-D15):" + this.OperaRec(Value.Substring(num, 4), "BS") + ",\r\n";
				num += 4;
				text = text + "电表运行状态字变位标志7(D0-D15):" + this.OperaRec(Value.Substring(num, 4), "BS") + ",\r\n";
				num += 4;
				text += ",\r\n";
				text = text + "电表运行状态字1:" + this.ZhuangTaiZi(this.OperaRec(Value.Substring(num, 4), "BCD"), 1) + ",\r\n";
				num += 4;
				text = text + "电表运行状态字2:" + this.ZhuangTaiZi(this.OperaRec(Value.Substring(num, 4), "BCD"), 2) + ",\r\n";
				num += 4;
				text = text + "电表运行状态字3:" + this.ZhuangTaiZi(this.OperaRec(Value.Substring(num, 4), "BCD"), 3) + ",\r\n";
				num += 4;
				text = text + "电表运行状态字4:" + this.ZhuangTaiZi(this.OperaRec(Value.Substring(num, 4), "BCD"), 4) + ",\r\n";
				num += 4;
				text = text + "电表运行状态字5:" + this.ZhuangTaiZi(this.OperaRec(Value.Substring(num, 4), "BCD"), 5) + ",\r\n";
				num += 4;
				text = text + "电表运行状态字6:" + this.ZhuangTaiZi(this.OperaRec(Value.Substring(num, 4), "BCD"), 6) + ",\r\n";
				num += 4;
				text = text + "电表运行状态字7:" + this.ZhuangTaiZi(this.OperaRec(Value.Substring(num, 4), "BCD"), 7) + ",\r\n";
				num += 4;
				return text;
			}
		}
		private string ERC34(string Value)
		{
			string text = string.Empty;
			int num = 0;
			text = text + "发生时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				int num2 = DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(num, 4)));
				num += 4;
				string text2 = text;
				text = string.Concat(new string[]
				{
					text2,
					(num2 >> 15 == 1) ? "起/止标志发生," : "起/止标志恢复,",
					"测量点号:",
					(num2 & 4095).ToString(),
					",\r\n"
				});
				num2 = DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(num, 2)));
				num += 2;
				string text3 = string.Empty;
				text3 += (((num2 & 1) == 1) ? "A相有事件," : "");
				text3 += (((num2 >> 1 & 1) == 1) ? "B相有事件," : "");
				text3 += (((num2 >> 2 & 1) == 1) ? "C相有事件," : "");
				text3 += "一次侧短路,二次侧短路,二次侧开路".Split(new char[]
				{
					','
				})[1 + (num2 >> 6) & 3];
				return text + "异常标志:" + text3 + ",\r\n";
			}
		}
		private string ERC35(string Value)
		{
			string text = string.Empty;
			int num = 0;
			text = text + "发生时间:" + this.OperaRec(Value.Substring(num, 10), "A15") + ",\r\n";
			checked
			{
				num += 10;
				int num2 = DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(num, 2)));
				num += 2;
				text = text + "终端通信端口号:" + (num2 & 63).ToString() + ",\r\n";
				num2 = DataConvert.HexToInt(Value.Substring(num, 2));
				num += 2;
				text = text + "发现块数:" + num2.ToString() + ",\r\n";
				for (int i = 0; i < num2; i++)
				{
					string text2 = text;
					text = string.Concat(new string[]
					{
						text2,
						"第",
						(i + 1).ToString(),
						"块未知电表通信地址:",
						this.OperaRec(Value.Substring(num, 12), "A12"),
						",\r\n"
					});
					num += 12;
					int num3 = DataConvert.HexToInt(Value.Substring(num, 2));
					num += 2;
					string text3 = ((num2 >> 7 & 1) == 1) ? "C相有效," : "";
					text3 += (((num2 >> 6 & 1) == 1) ? "B相有效," : "");
					text3 += (((num2 >> 5 & 1) == 1) ? "A相有效," : "");
					text3 = text3 + "载波信号品质:" + (num2 & 15).ToString();
					text2 = text;
					text = string.Concat(new string[]
					{
						text2,
						"第",
						(i + 1).ToString(),
						"块未知电表所在相别及发现者接收到的信号品质:",
						text3,
						",\r\n"
					});
					num3 = DataConvert.HexToInt(Value.Substring(num, 2));
					num += 2;
					text3 = "DL/T645-1997,DL/T645-2007,备用,备用".Split(new char[]
					{
						','
					})[num2 & 3];
					text2 = text;
					text = string.Concat(new string[]
					{
						text2,
						"第",
						(i + 1).ToString(),
						"块未知电表通信协议:",
						text3,
						",\r\n"
					});
				}
				return text;
			}
		}
		private void ItemAdd(string Items, string Values)
		{
			DLT698_Recv.ItemsInfo item = default(DLT698_Recv.ItemsInfo);
			item.Items = Items;
			item.Values = Values;
			this.ItemData.Add(item);
		}
		private string HexStrToIp(string hexip)
		{
			return string.Concat(new object[]
			{
				DataConvert.HexToInt(hexip.Substring(0, 2)),
				".",
				DataConvert.HexToInt(hexip.Substring(2, 2)),
				".",
				DataConvert.HexToInt(hexip.Substring(4, 2)),
				".",
				DataConvert.HexToInt(hexip.Substring(6, 2))
			});
		}
		public string ASCIIToHexStr(string strValue)
		{
			byte[] bytes = Encoding.ASCII.GetBytes(strValue);
			string text = string.Empty;
			checked
			{
				for (int i = 0; i < bytes.Length; i++)
				{
					text += bytes[i].ToString("X2");
				}
				return text;
			}
		}
		public string HexStrToASCII(string strValue)
		{
			byte[] array = new byte[strValue.Length / 2];
			int num = 0;
			checked
			{
				for (int i = 0; i < strValue.Length / 2; i++)
				{
					if ((byte)int.Parse(strValue.Substring(i * 2, 2), NumberStyles.HexNumber) != 0)
					{
						array[num] = (byte)int.Parse(strValue.Substring(i * 2, 2), NumberStyles.HexNumber);
						num++;
					}
				}
				return Encoding.Default.GetString(array, 0, num);
			}
		}
		private int GetIndex(string pText, string[] allitem)
		{
			checked
			{
				int result;
				for (int i = 0; i < allitem.Length; i++)
				{
					if (allitem[i].IndexOf(pText) >= 0)
					{
						result = i;
						return result;
					}
				}
				result = 0;
				return result;
			}
		}
		public int HexToInt(string HexChar)
		{
			int result = 0;
			bool flag = int.TryParse(HexChar, NumberStyles.HexNumber, null, out result);
			return result;
		}
		public long HexToLong(string HexChar)
		{
			long result = 0L;
			bool flag = long.TryParse(HexChar, NumberStyles.HexNumber, null, out result);
			return result;
		}
		public string ReverseStr(string val)
		{
			string text = string.Empty;
			checked
			{
				if (val.Length > 0)
				{
					for (int i = 0; i < val.Length; i += 2)
					{
						text = val.Substring(i, 2) + text;
					}
				}
				return text;
			}
		}
		public string ReverseStr(string val, int Step)
		{
			string text = val.Replace(" ", "");
			string text2 = string.Empty;
			checked
			{
				for (int i = 0; i < text.Length; i += Step)
				{
					text2 = text.Substring(i, Step) + text2;
				}
				string text3 = string.Empty;
				if (text.Length != val.Length)
				{
					for (int i = 0; i < text2.Length; i += Step)
					{
						text3 = text3 + text2.Substring(i, Step) + " ";
					}
				}
				else
				{
					text3 = text2;
				}
				return text3;
			}
		}
		private string OperaRec(string Value, string type, string danwei)
		{
			string text = string.Empty;
			string text2 = DataConvert.ReverseStr(Value);
			string text3 = type.ToUpper().Trim();
			checked
			{
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
						string text5 = text2;
						text = text5.Substring(0, 2) + "年";
						int num2 = int.Parse(text5.Substring(2, 1), NumberStyles.HexNumber);
						string arg_378_0 = text;
						int num = num2 & 1;
						text = arg_378_0 + num.ToString() + text5.Substring(3, 1) + "月";
						text = text + text5.Substring(4, 2) + "日 ";
						num2 >>= 1;
						text += " ";
						text = text + text5.Substring(6, 2) + "时";
						text = text + text5.Substring(8, 2) + "分";
						text = text + text5.Substring(10, 2) + "秒";
						if (num2 > 0)
						{
							string text6 = "星期一,星期二,星期三,星期四,星期五,星期六,星期日";
							text = text + " [" + text6.Split(new char[]
							{
								','
							})[num2 - 1] + "]";
						}
						break;
					}

				case "A2":
					{
						int num3 = int.Parse(text2.Substring(0, 1));
						text2 = text2.Substring(1, 3);
						text = (((num3 & 1) == 0) ? "+" : "-");
						text += text2;
						string arg_478_0 = text;
						string arg_478_1 = "*10^";
						int num = 4 - (num3 >> 1);
						text = arg_478_0 + arg_478_1 + num.ToString();
						break;
					}

				case "A3":
					{
						int num2 = int.Parse(text2.Substring(0, 1));
						text2 = text2.Substring(1, 7);
						text = (((num2 & 1) == 0) ? "+" : "-");
						text += text2;
						if (!string.IsNullOrEmpty(danwei))
						{
							text += danwei;
						}
						else
						{
							text += (((num2 & 4) == 0) ? "kWh、厘" : "MWh、元");
						}
						break;
					}

				case "A4":
					{
						int num2 = int.Parse(text2, NumberStyles.HexNumber);
						text = (((num2 & 128) == 0) ? "上浮" : "下浮");
						string arg_526_0 = text;
						int num = num2 & 127;
						text = arg_526_0 + num.ToString("X2");
						break;
					}

				case "A5":
					{
						int num2 = DataConvert.HexToInt(text2.Substring(0, 2));
						text = (((num2 & 128) == 0) ? "" : "-");
						string text7 = text;
						string[] array = new string[5];
						array[0] = text7;
						string[] arg_581_0 = array;
						int arg_581_1 = 1;
						int num = num2 & 127;
						arg_581_0[arg_581_1] = num.ToString("X2");
						array[2] = text2.Substring(2, 1);
						array[3] = ".";
						array[4] = text2.Substring(3, 1);
						text = string.Concat(array);
						break;
					}

				case "A6":
					{
						int num2 = DataConvert.HexToInt(text2.Substring(0, 2));
						text = (((num2 & 128) == 0) ? "" : "-");
						string arg_5FA_0 = text;
						int num = num2 & 127;
						text = arg_5FA_0 + num.ToString("X2") + "." + text2.Substring(2, 2);
						break;
					}

				case "A7":
					text = text2.Substring(0, 3) + "." + text2.Substring(3, 1);
					break;

				case "A9":
					{
						int num2 = DataConvert.HexToInt(text2.Substring(0, 2));
						text = (((num2 & 128) == 0) ? "" : "-");
						string arg_66F_0 = text;
						int num = num2 & 127;
						text = arg_66F_0 + num.ToString("X2") + "." + text2.Substring(2, 4);
						break;
					}

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
						"日 ",
						text2.Substring(6, 2),
						"时",
						text2.Substring(8, 2),
						"分"
					});
					break;

				case "A16":
					text = string.Concat(new string[]
					{
						text2.Substring(0, 2),
						"日 ",
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
						"日 ",
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
						"日 ",
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
				case "TD_D":
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
				case "TD_M":
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

				case "A25":
					{
						long num4 = DataConvert.HexToLong(text2);
						string str = ((num4 & 8388608L) == 0L) ? "+" : "-";
						text = (num4 & 8388607L).ToString("X6");
						text = str + text2.Substring(0, 3) + "." + text2.Substring(3, 3);
						break;
					}

				case "A26":
					text = text2.Substring(0, 1) + "." + text2.Substring(1, 3);
					break;

				case "D1":
					switch (int.Parse(Value))
					{
					case 0:
						text = "正确";
						break;

					case 1:
						text = "出错";
						break;

					default:
						text = "备用";
						break;
					}
					break;
				}
				if (text.ToUpper().IndexOf("EE") >= 0)
				{
					text = "";
				}
				return text;
			}
		}
		private string OperaRec(string Value, string type)
		{
			return this.OperaRec(Value, type, "");
		}
		private string C1(string midu, ref int Num)
		{
			string result = string.Empty;
			int num = int.Parse(midu);
			switch (num)
			{
			case 0:
				Num = 0;
				result = "不冻结: 无";
				break;

			case 1:
				Num = 4;
				result = "15min: 15分、30分、45分、0分";
				break;

			case 2:
				Num = 2;
				result = "30min: 30分、0分";
				break;

			case 3:
				Num = 1;
				result = "60min: 0分";
				break;

			default:
				switch (num)
				{
				case 254:
					Num = 14;
					result = "5min: 5分、10分、15分...、0分";
					break;

				case 255:
					Num = 60;
					result = "1min: 1分、2分、3分、...、0分";
					break;

				default:
					Num = 0;
					result = "备用";
					break;
				}
				break;
			}
			return result;
		}
		private string Td_c(string Value, ref int Num)
		{
			string text = "起始时间:" + this.OperaRec(Value.Substring(0, 10), "A15") + ",";
			text = text + "数据冻结密度:" + this.OperaRec(Value.Substring(10, 2), "BIN");
			int num = int.Parse(this.OperaRec(Value.Substring(12, 2), "BIN"));
			text = text + "数据点数:" + num.ToString() + "\r\n";
			Num = num;
			return text;
		}
		private string Td_h(string Value, ref int Num)
		{
			int num = DataConvert.HexToInt(Value.Substring(0, 2));
			string text = (num >> 4 & 3).ToString() + (num & 15).ToString();
			string text2 = this.C1(Value.Substring(2, 2), ref Num);
			return string.Concat(new string[]
			{
				"上一整点的小时时间:",
				text,
				"时,密度:",
				text2,
				","
			});
		}
		public void DoInfo(string AFN, string FN, string Data, string Format)
		{
			this.DoInfo(AFN, FN, Data, false, "", Format);
		}
		public void DoInfo(string AFN, string FN, string Data)
		{
			this.DoInfo(AFN, FN, Data, false, "");
		}
		public void DoInfo(string AFN, string FN, string Data, bool IsCustomize, string CustomizeItems)
		{
			this.DoInfo(AFN, FN, Data, IsCustomize, CustomizeItems, "");
		}
		public void DoInfo(string AFN, string FN, string Data, bool IsCustomize, string CustomizeItems, string Format)
		{
			this.ItemData.Clear();
			this.DataLength = 0;
			if (!string.IsNullOrEmpty(FN) & FN.ToUpper() != "INVALID")
			{
				int num = int.Parse(FN);
				if (!IsCustomize)
				{
					if (AFN == "00")
					{
						if (num == 3)
						{
							this.DataLength = this.AF00_F3(Data);
						}
					}
					if (AFN == "03")
					{
						if (num == 1)
						{
							this.DataLength = this.AF03_F1(Data);
						}
						else
						{
							if (num == 2)
							{
								this.DataLength = this.AF03_F2(Data);
							}
							else
							{
								if (num == 3)
								{
									this.DataLength = this.AF03_F3(Data);
								}
								else
								{
									if (num == 4)
									{
										this.DataLength = this.AF03_F4(Data);
									}
								}
							}
						}
					}
					if (AFN == "06")
					{
						if (num == 1)
						{
							this.DataLength = this.AF06_F1(Data);
						}
						else
						{
							if (num == 2)
							{
								this.DataLength = this.AF06_F1(Data);
							}
							else
							{
								if (num == 3)
								{
									this.DataLength = this.AF06_F1(Data);
								}
								else
								{
									if (num == 4)
									{
										this.DataLength = this.AF06_F1(Data);
									}
								}
							}
						}
					}
					if (AFN == "09")
					{
						if (num == 1)
						{
							this.DataLength = this.AF09_F1(Data);
						}
						else
						{
							if (num == 2)
							{
								this.DataLength = this.AF09_F2(Data);
							}
							else
							{
								if (num == 3)
								{
									this.DataLength = this.AF09_F3(Data);
								}
								else
								{
									if (num == 4)
									{
										this.DataLength = this.AF09_F4(Data);
									}
									else
									{
										if (num == 5)
										{
											this.DataLength = this.AF09_F5(Data);
										}
										else
										{
											if (num == 6)
											{
												this.DataLength = this.AF09_F6(Data);
											}
											else
											{
												if (num == 7)
												{
													this.DataLength = this.AF09_F7(Data);
												}
												else
												{
													if (num == 8)
													{
														this.DataLength = this.AF09_F8(Data);
													}
												}
											}
										}
									}
								}
							}
						}
					}
					if (AFN == "0A")
					{
						if (num == 1)
						{
							this.DataLength = this.AF0A_F1(Data);
						}
						else
						{
							if (num == 2)
							{
								this.DataLength = this.AF0A_F2(Data);
							}
							else
							{
								if (num == 3)
								{
									this.DataLength = this.AF0A_F3(Data);
								}
								else
								{
									if (num == 4)
									{
										this.DataLength = this.AF0A_F4(Data);
									}
									else
									{
										if (num == 5)
										{
											this.DataLength = this.AF0A_F5(Data);
										}
										else
										{
											if (num == 6)
											{
												this.DataLength = this.AF0A_F6(Data);
											}
											else
											{
												if (num == 7)
												{
													this.DataLength = this.AF0A_F7(Data);
												}
												else
												{
													if (num == 8)
													{
														this.DataLength = this.AF0A_F8(Data);
													}
													else
													{
														if (num == 9)
														{
															this.DataLength = this.AF0A_F9(Data);
														}
														else
														{
															if (num == 10)
															{
																this.DataLength = this.AF0A_F10(Data);
															}
															else
															{
																if (num == 11)
																{
																	this.DataLength = this.AF0A_F11(Data);
																}
																else
																{
																	if (num == 12)
																	{
																		this.DataLength = this.AF0A_F12(Data);
																	}
																	else
																	{
																		if (num == 13)
																		{
																			this.DataLength = this.AF0A_F13(Data);
																		}
																		else
																		{
																			if (num == 14)
																			{
																				this.DataLength = this.AF0A_F14(Data);
																			}
																			else
																			{
																				if (num == 15)
																				{
																					this.DataLength = this.AF0A_F15(Data);
																				}
																				else
																				{
																					if (num == 16)
																					{
																						this.DataLength = this.AF0A_F16(Data);
																					}
																					else
																					{
																						if (num == 17)
																						{
																							this.DataLength = this.AF0A_F17(Data);
																						}
																						else
																						{
																							if (num == 18)
																							{
																								this.DataLength = this.AF0A_F18(Data);
																							}
																							else
																							{
																								if (num == 19)
																								{
																									this.DataLength = this.AF0A_F19(Data);
																								}
																								else
																								{
																									if (num == 20)
																									{
																										this.DataLength = this.AF0A_F20(Data);
																									}
																									else
																									{
																										if (num == 21)
																										{
																											this.DataLength = this.AF0A_F21(Data);
																										}
																										else
																										{
																											if (num == 22)
																											{
																												this.DataLength = this.AF0A_F22(Data);
																											}
																											else
																											{
																												if (num == 23)
																												{
																													this.DataLength = this.AF0A_F23(Data);
																												}
																												else
																												{
																													if (num == 25)
																													{
																														this.DataLength = this.AF0A_F25(Data);
																													}
																													else
																													{
																														if (num == 26)
																														{
																															this.DataLength = this.AF0A_F26(Data);
																														}
																														else
																														{
																															if (num == 27)
																															{
																																this.DataLength = this.AF0A_F27(Data);
																															}
																															else
																															{
																																if (num == 28)
																																{
																																	this.DataLength = this.AF0A_F28(Data);
																																}
																																else
																																{
																																	if (num == 29)
																																	{
																																		this.DataLength = this.AF0A_F29(Data);
																																	}
																																	else
																																	{
																																		if (num == 30)
																																		{
																																			this.DataLength = this.AF0A_F30(Data);
																																		}
																																		else
																																		{
																																			if (num == 31)
																																			{
																																				this.DataLength = this.AF0A_F31(Data);
																																			}
																																			else
																																			{
																																				if (num == 33)
																																				{
																																					this.DataLength = this.AF0A_F33(Data);
																																				}
																																				else
																																				{
																																					if (num == 34)
																																					{
																																						this.DataLength = this.AF0A_F34(Data);
																																					}
																																					else
																																					{
																																						if (num == 35)
																																						{
																																							this.DataLength = this.AF0A_F35(Data);
																																						}
																																						else
																																						{
																																							if (num == 36)
																																							{
																																								this.DataLength = this.AF0A_F36(Data);
																																							}
																																							else
																																							{
																																								if (num == 37)
																																								{
																																									this.DataLength = this.AF0A_F37(Data);
																																								}
																																								else
																																								{
																																									if (num == 38 | num == 39)
																																									{
																																										this.DataLength = this.AF0A_F38(Data);
																																									}
																																									else
																																									{
																																										if (num == 41)
																																										{
																																											this.DataLength = this.AF0A_F41(Data);
																																										}
																																										else
																																										{
																																											if (num == 42)
																																											{
																																												this.DataLength = this.AF0A_F42(Data);
																																											}
																																											else
																																											{
																																												if (num == 43)
																																												{
																																													this.DataLength = this.AF0A_F43(Data);
																																												}
																																												else
																																												{
																																													if (num == 44)
																																													{
																																														this.DataLength = this.AF0A_F44(Data);
																																													}
																																													else
																																													{
																																														if (num == 45)
																																														{
																																															this.DataLength = this.AF0A_F45(Data);
																																														}
																																														else
																																														{
																																															if (num == 46)
																																															{
																																																this.DataLength = this.AF0A_F46(Data);
																																															}
																																															else
																																															{
																																																if (num == 47)
																																																{
																																																	this.DataLength = this.AF0A_F47(Data);
																																																}
																																																else
																																																{
																																																	if (num == 48)
																																																	{
																																																		this.DataLength = this.AF0A_F48(Data);
																																																	}
																																																	else
																																																	{
																																																		if (num == 49)
																																																		{
																																																			this.DataLength = this.AF0A_F49(Data);
																																																		}
																																																		else
																																																		{
																																																			if (num == 57)
																																																			{
																																																				this.DataLength = this.AF0A_F57(Data);
																																																			}
																																																			else
																																																			{
																																																				if (num == 58)
																																																				{
																																																					this.DataLength = this.AF0A_F58(Data);
																																																				}
																																																				else
																																																				{
																																																					if (num == 59)
																																																					{
																																																						this.DataLength = this.AF0A_F59(Data);
																																																					}
																																																					else
																																																					{
																																																						if (num == 60)
																																																						{
																																																							this.DataLength = this.AF0A_F60(Data);
																																																						}
																																																						else
																																																						{
																																																							if (num == 61)
																																																							{
																																																								this.DataLength = this.AF0A_F61(Data);
																																																							}
																																																							else
																																																							{
																																																								if (num == 65 | num == 66)
																																																								{
																																																									this.DataLength = this.AF0A_F65(Data);
																																																								}
																																																								else
																																																								{
																																																									if (num == 67 | num == 68)
																																																									{
																																																										this.DataLength = this.AF0A_F67(Data);
																																																									}
																																																									else
																																																									{
																																																										if (num == 73)
																																																										{
																																																											this.DataLength = this.AF0A_F73(Data);
																																																										}
																																																										else
																																																										{
																																																											if (num == 74)
																																																											{
																																																												this.DataLength = this.AF0A_F74(Data);
																																																											}
																																																											else
																																																											{
																																																												if (num == 75)
																																																												{
																																																													this.DataLength = this.AF0A_F75(Data);
																																																												}
																																																												else
																																																												{
																																																													if (num == 76)
																																																													{
																																																														this.DataLength = this.AF0A_F76(Data);
																																																													}
																																																													else
																																																													{
																																																														if (num == 81)
																																																														{
																																																															this.DataLength = this.AF0A_F81(Data);
																																																														}
																																																														else
																																																														{
																																																															if (num == 82)
																																																															{
																																																																this.DataLength = this.AF0A_F82(Data);
																																																															}
																																																															else
																																																															{
																																																																if (num == 83)
																																																																{
																																																																	this.DataLength = this.AF0A_F83(Data);
																																																																}
																																																																else
																																																																{
																																																																	if (num == 85)
																																																																	{
																																																																		this.DataLength = this.AF0A_F85(Data);
																																																																	}
																																																																	else
																																																																	{
																																																																		if (num == 89)
																																																																		{
																																																																			this.DataLength = this.AF0A_F89(Data);
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
					if (AFN == "0B")
					{
						if (num == 2)
						{
							this.DataLength = this.AF0B_F2(Data);
						}
					}
					if (AFN == "0C")
					{
						if (num == 2)
						{
							this.DataLength = this.AF0C_F2(Data);
						}
						else
						{
							if (num == 3)
							{
								this.DataLength = this.AF0C_F3(Data);
							}
							else
							{
								if (num == 4)
								{
									this.DataLength = this.AF0C_F4(Data);
								}
								else
								{
									if (num == 5)
									{
										this.DataLength = this.AF0C_F5(Data);
									}
									else
									{
										if (num == 6)
										{
											this.DataLength = this.AF0C_F6(Data);
										}
										else
										{
											if (num == 7)
											{
												this.DataLength = this.AF0C_F7(Data);
											}
											else
											{
												if (num == 8)
												{
													this.DataLength = this.AF0C_F8(Data);
												}
												else
												{
													if (num == 9)
													{
														this.DataLength = this.AF0C_F9(Data);
													}
													else
													{
														if (num == 10)
														{
															this.DataLength = this.AF0C_F10(Data);
														}
														else
														{
															if (num == 11)
															{
																this.DataLength = this.AF0C_F11(Data);
															}
															else
															{
																if (num == 12)
																{
																	this.DataLength = this.AF0C_F12(Data);
																}
																else
																{
																	if (num == 17)
																	{
																		this.DataLength = this.AF0C_F17(Data);
																	}
																	else
																	{
																		if (num == 18)
																		{
																			this.DataLength = this.AF0C_F18(Data);
																		}
																		else
																		{
																			if (num == 19)
																			{
																				this.DataLength = this.AF0C_F19(Data);
																			}
																			else
																			{
																				if (num == 20)
																				{
																					this.DataLength = this.AF0C_F20(Data);
																				}
																				else
																				{
																					if (num == 21)
																					{
																						this.DataLength = this.AF0C_F21(Data);
																					}
																					else
																					{
																						if (num == 22)
																						{
																							this.DataLength = this.AF0C_F22(Data);
																						}
																						else
																						{
																							if (num == 23)
																							{
																								this.DataLength = this.AF0C_F23(Data);
																							}
																							else
																							{
																								if (num == 24)
																								{
																									this.DataLength = this.AF0C_F24(Data);
																								}
																								else
																								{
																									if (num == 25)
																									{
																										this.DataLength = this.AF0C_F25(Data);
																									}
																									else
																									{
																										if (num == 26)
																										{
																											this.DataLength = this.AF0C_F26(Data);
																										}
																										else
																										{
																											if (num == 27)
																											{
																												this.DataLength = this.AF0C_F27(Data);
																											}
																											else
																											{
																												if (num == 28)
																												{
																													this.DataLength = this.AF0C_F28(Data);
																												}
																												else
																												{
																													if (num == 29)
																													{
																														this.DataLength = this.AF0C_F29(Data);
																													}
																													else
																													{
																														if (num == 30)
																														{
																															this.DataLength = this.AF0C_F30(Data);
																														}
																														else
																														{
																															if (num == 31)
																															{
																																this.DataLength = this.AF0C_F31(Data);
																															}
																															else
																															{
																																if (num == 32)
																																{
																																	this.DataLength = this.AF0C_F32(Data);
																																}
																																else
																																{
																																	if (num == 33)
																																	{
																																		this.DataLength = this.AF0C_F33(Data);
																																	}
																																	else
																																	{
																																		if (num == 34)
																																		{
																																			this.DataLength = this.AF0C_F34(Data);
																																		}
																																		else
																																		{
																																			if (num == 35)
																																			{
																																				this.DataLength = this.AF0C_F35(Data);
																																			}
																																			else
																																			{
																																				if (num == 36)
																																				{
																																					this.DataLength = this.AF0C_F36(Data);
																																				}
																																				else
																																				{
																																					if (num == 37)
																																					{
																																						this.DataLength = this.AF0C_F37(Data);
																																					}
																																					else
																																					{
																																						if (num == 38)
																																						{
																																							this.DataLength = this.AF0C_F38(Data);
																																						}
																																						else
																																						{
																																							if (num == 39)
																																							{
																																								this.DataLength = this.AF0C_F39(Data);
																																							}
																																							else
																																							{
																																								if (num == 40)
																																								{
																																									this.DataLength = this.AF0C_F40(Data);
																																								}
																																								else
																																								{
																																									if (num == 41)
																																									{
																																										this.DataLength = this.AF0C_F41(Data);
																																									}
																																									else
																																									{
																																										if (num == 42)
																																										{
																																											this.DataLength = this.AF0C_F42(Data);
																																										}
																																										else
																																										{
																																											if (num == 43)
																																											{
																																												this.DataLength = this.AF0C_F43(Data);
																																											}
																																											else
																																											{
																																												if (num == 44)
																																												{
																																													this.DataLength = this.AF0C_F44(Data);
																																												}
																																												else
																																												{
																																													if (num == 45)
																																													{
																																														this.DataLength = this.AF0C_F45(Data);
																																													}
																																													else
																																													{
																																														if (num == 46)
																																														{
																																															this.DataLength = this.AF0C_F46(Data);
																																														}
																																														else
																																														{
																																															if (num == 47)
																																															{
																																																this.DataLength = this.AF0C_F47(Data);
																																															}
																																															else
																																															{
																																																if (num == 48)
																																																{
																																																	this.DataLength = this.AF0C_F48(Data);
																																																}
																																																else
																																																{
																																																	if (num == 49)
																																																	{
																																																		this.DataLength = this.AF0C_F49(Data);
																																																	}
																																																	else
																																																	{
																																																		if (num == 57)
																																																		{
																																																			this.DataLength = this.AF0C_F57(Data);
																																																		}
																																																		else
																																																		{
																																																			if (num == 58)
																																																			{
																																																				this.DataLength = this.AF0C_F58(Data);
																																																			}
																																																			else
																																																			{
																																																				if (num == 65)
																																																				{
																																																					this.DataLength = this.AF0C_F65(Data);
																																																				}
																																																				else
																																																				{
																																																					if (num == 66)
																																																					{
																																																						this.DataLength = this.AF0C_F66(Data);
																																																					}
																																																					else
																																																					{
																																																						if (num == 67)
																																																						{
																																																							this.DataLength = this.AF0C_F67(Data);
																																																						}
																																																						else
																																																						{
																																																							if (num == 73)
																																																							{
																																																								this.DataLength = this.AF0C_F73(Data);
																																																							}
																																																							else
																																																							{
																																																								if (num == 81)
																																																								{
																																																									this.DataLength = this.AF0C_F81(Data);
																																																								}
																																																								else
																																																								{
																																																									if (num == 82)
																																																									{
																																																										this.DataLength = this.AF0C_F82(Data);
																																																									}
																																																									else
																																																									{
																																																										if (num == 83)
																																																										{
																																																											this.DataLength = this.AF0C_F83(Data);
																																																										}
																																																										else
																																																										{
																																																											if (num == 84)
																																																											{
																																																												this.DataLength = this.AF0C_F84(Data);
																																																											}
																																																											else
																																																											{
																																																												if (num == 89 | num == 90 | num == 91 | num == 92)
																																																												{
																																																													this.DataLength = this.AF0C_F89(Data);
																																																												}
																																																												else
																																																												{
																																																													if (num == 93 | num == 94 | num == 95 | num == 96)
																																																													{
																																																														this.DataLength = this.AF0C_F93(Data);
																																																													}
																																																													else
																																																													{
																																																														if (num == 97 | num == 98 | num == 99)
																																																														{
																																																															this.DataLength = this.AF0C_F97(Data);
																																																														}
																																																														else
																																																														{
																																																															if (num == 100 | num == 101 | num == 102 | num == 103)
																																																															{
																																																																this.DataLength = this.AF0C_F100(Data);
																																																															}
																																																															else
																																																															{
																																																																if (num == 105)
																																																																{
																																																																	this.DataLength = this.AF0C_F105(Data);
																																																																}
																																																																else
																																																																{
																																																																	if (num == 106)
																																																																	{
																																																																		this.DataLength = this.AF0C_F106(Data);
																																																																	}
																																																																	else
																																																																	{
																																																																		if (num == 107)
																																																																		{
																																																																			this.DataLength = this.AF0C_F107(Data);
																																																																		}
																																																																		else
																																																																		{
																																																																			if (num == 108)
																																																																			{
																																																																				this.DataLength = this.AF0C_F108(Data);
																																																																			}
																																																																			else
																																																																			{
																																																																				if (num == 109)
																																																																				{
																																																																					this.DataLength = this.AF0C_F109(Data);
																																																																				}
																																																																				else
																																																																				{
																																																																					if (num == 110)
																																																																					{
																																																																						this.DataLength = this.AF0C_F110(Data);
																																																																					}
																																																																					else
																																																																					{
																																																																						if (num == 111)
																																																																						{
																																																																							this.DataLength = this.AF0C_F111(Data);
																																																																						}
																																																																						else
																																																																						{
																																																																							if (num == 112)
																																																																							{
																																																																								this.DataLength = this.AF0C_F112(Data);
																																																																							}
																																																																							else
																																																																							{
																																																																								if (num == 113 | num == 114 | num == 115 | num == 116)
																																																																								{
																																																																									this.DataLength = this.AF0C_F113(Data);
																																																																								}
																																																																								else
																																																																								{
																																																																									if (num == 121)
																																																																									{
																																																																										this.DataLength = this.AF0C_F121(Data);
																																																																									}
																																																																									else
																																																																									{
																																																																										if (num == 129)
																																																																										{
																																																																											this.DataLength = this.AF0C_F129(Data);
																																																																										}
																																																																										else
																																																																										{
																																																																											if (num == 130)
																																																																											{
																																																																												this.DataLength = this.AF0C_F130(Data);
																																																																											}
																																																																											else
																																																																											{
																																																																												if (num == 131)
																																																																												{
																																																																													this.DataLength = this.AF0C_F131(Data);
																																																																												}
																																																																												else
																																																																												{
																																																																													if (num == 132)
																																																																													{
																																																																														this.DataLength = this.AF0C_F132(Data);
																																																																													}
																																																																													else
																																																																													{
																																																																														if (num == 133)
																																																																														{
																																																																															this.DataLength = this.AF0C_F133(Data);
																																																																														}
																																																																														else
																																																																														{
																																																																															if (num == 134)
																																																																															{
																																																																																this.DataLength = this.AF0C_F134(Data);
																																																																															}
																																																																															else
																																																																															{
																																																																																if (num == 135)
																																																																																{
																																																																																	this.DataLength = this.AF0C_F135(Data);
																																																																																}
																																																																																else
																																																																																{
																																																																																	if (num == 136)
																																																																																	{
																																																																																		this.DataLength = this.AF0C_F136(Data);
																																																																																	}
																																																																																	else
																																																																																	{
																																																																																		if (num == 137)
																																																																																		{
																																																																																			this.DataLength = this.AF0C_F137(Data);
																																																																																		}
																																																																																		else
																																																																																		{
																																																																																			if (num == 138)
																																																																																			{
																																																																																				this.DataLength = this.AF0C_F138(Data);
																																																																																			}
																																																																																			else
																																																																																			{
																																																																																				if (num == 139)
																																																																																				{
																																																																																					this.DataLength = this.AF0C_F139(Data);
																																																																																				}
																																																																																				else
																																																																																				{
																																																																																					if (num == 140)
																																																																																					{
																																																																																						this.DataLength = this.AF0C_F140(Data);
																																																																																					}
																																																																																					else
																																																																																					{
																																																																																						if (num == 141)
																																																																																						{
																																																																																							this.DataLength = this.AF0C_F141(Data);
																																																																																						}
																																																																																						else
																																																																																						{
																																																																																							if (num == 142)
																																																																																							{
																																																																																								this.DataLength = this.AF0C_F142(Data);
																																																																																							}
																																																																																							else
																																																																																							{
																																																																																								if (num == 143)
																																																																																								{
																																																																																									this.DataLength = this.AF0C_F143(Data);
																																																																																								}
																																																																																								else
																																																																																								{
																																																																																									if (num == 144)
																																																																																									{
																																																																																										this.DataLength = this.AF0C_F144(Data);
																																																																																									}
																																																																																									else
																																																																																									{
																																																																																										if (num == 145)
																																																																																										{
																																																																																											this.DataLength = this.AF0C_F145(Data);
																																																																																										}
																																																																																										else
																																																																																										{
																																																																																											if (num == 146)
																																																																																											{
																																																																																												this.DataLength = this.AF0C_F146(Data);
																																																																																											}
																																																																																											else
																																																																																											{
																																																																																												if (num == 147)
																																																																																												{
																																																																																													this.DataLength = this.AF0C_F147(Data);
																																																																																												}
																																																																																												else
																																																																																												{
																																																																																													if (num == 148)
																																																																																													{
																																																																																														this.DataLength = this.AF0C_F148(Data);
																																																																																													}
																																																																																													else
																																																																																													{
																																																																																														if (num == 149)
																																																																																														{
																																																																																															this.DataLength = this.AF0C_F149(Data);
																																																																																														}
																																																																																														else
																																																																																														{
																																																																																															if (num == 150)
																																																																																															{
																																																																																																this.DataLength = this.AF0C_F150(Data);
																																																																																															}
																																																																																															else
																																																																																															{
																																																																																																if (num == 151)
																																																																																																{
																																																																																																	this.DataLength = this.AF0C_F151(Data);
																																																																																																}
																																																																																																else
																																																																																																{
																																																																																																	if (num == 152)
																																																																																																	{
																																																																																																		this.DataLength = this.AF0C_F152(Data);
																																																																																																	}
																																																																																																	else
																																																																																																	{
																																																																																																		if (num == 153)
																																																																																																		{
																																																																																																			this.DataLength = this.AF0C_F153(Data);
																																																																																																		}
																																																																																																		else
																																																																																																		{
																																																																																																			if (num == 154)
																																																																																																			{
																																																																																																				this.DataLength = this.AF0C_F154(Data);
																																																																																																			}
																																																																																																			else
																																																																																																			{
																																																																																																				if (num == 155)
																																																																																																				{
																																																																																																					this.DataLength = this.AF0C_F155(Data);
																																																																																																				}
																																																																																																				else
																																																																																																				{
																																																																																																					if (num == 156)
																																																																																																					{
																																																																																																						this.DataLength = this.AF0C_F156(Data);
																																																																																																					}
																																																																																																					else
																																																																																																					{
																																																																																																						if (num == 157)
																																																																																																						{
																																																																																																							this.DataLength = this.AF0C_F157(Data);
																																																																																																						}
																																																																																																						else
																																																																																																						{
																																																																																																							if (num == 158)
																																																																																																							{
																																																																																																								this.DataLength = this.AF0C_F158(Data);
																																																																																																							}
																																																																																																							else
																																																																																																							{
																																																																																																								if (num == 159)
																																																																																																								{
																																																																																																									this.DataLength = this.AF0C_F159(Data);
																																																																																																								}
																																																																																																								else
																																																																																																								{
																																																																																																									if (num == 160)
																																																																																																									{
																																																																																																										this.DataLength = this.AF0C_F160(Data);
																																																																																																									}
																																																																																																									else
																																																																																																									{
																																																																																																										if (num == 161)
																																																																																																										{
																																																																																																											this.DataLength = this.AF0C_F161(Data);
																																																																																																										}
																																																																																																										else
																																																																																																										{
																																																																																																											if (num == 165)
																																																																																																											{
																																																																																																												this.DataLength = this.AF0C_F165(Data);
																																																																																																											}
																																																																																																											else
																																																																																																											{
																																																																																																												if (num == 166)
																																																																																																												{
																																																																																																													this.DataLength = this.AF0C_F166(Data);
																																																																																																												}
																																																																																																												else
																																																																																																												{
																																																																																																													if (num == 167)
																																																																																																													{
																																																																																																														this.DataLength = this.AF0C_F167(Data);
																																																																																																													}
																																																																																																													else
																																																																																																													{
																																																																																																														if (num == 168)
																																																																																																														{
																																																																																																															this.DataLength = this.AF0C_F168(Data);
																																																																																																														}
																																																																																																														else
																																																																																																														{
																																																																																																															if (num == 169)
																																																																																																															{
																																																																																																																this.DataLength = this.AF0C_F169(Data);
																																																																																																															}
																																																																																																															else
																																																																																																															{
																																																																																																																if (num == 170)
																																																																																																																{
																																																																																																																	this.DataLength = this.AF0C_F170(Data);
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
								}
							}
						}
					}
					if (AFN == "0D")
					{
						if (num == 1)
						{
							this.DataLength = this.AF0D_F1(Data);
						}
						else
						{
							if (num == 2)
							{
								this.DataLength = this.AF0D_F2(Data);
							}
							else
							{
								if (num == 3)
								{
									this.DataLength = this.AF0D_F3(Data);
								}
								else
								{
									if (num == 4)
									{
										this.DataLength = this.AF0D_F4(Data);
									}
									else
									{
										if (num == 5)
										{
											this.DataLength = this.AF0D_F5(Data);
										}
										else
										{
											if (num == 6)
											{
												this.DataLength = this.AF0D_F6(Data);
											}
											else
											{
												if (num == 7)
												{
													this.DataLength = this.AF0D_F7(Data);
												}
												else
												{
													if (num == 8)
													{
														this.DataLength = this.AF0D_F8(Data);
													}
													else
													{
														if (num == 9)
														{
															this.DataLength = this.AF0D_F9(Data);
														}
														else
														{
															if (num == 10)
															{
																this.DataLength = this.AF0D_F10(Data);
															}
															else
															{
																if (num == 11)
																{
																	this.DataLength = this.AF0D_F11(Data);
																}
																else
																{
																	if (num == 12)
																	{
																		this.DataLength = this.AF0D_F12(Data);
																	}
																	else
																	{
																		if (num == 17)
																		{
																			this.DataLength = this.AF0D_F17(Data);
																		}
																		else
																		{
																			if (num == 18)
																			{
																				this.DataLength = this.AF0D_F18(Data);
																			}
																			else
																			{
																				if (num == 19)
																				{
																					this.DataLength = this.AF0D_F19(Data);
																				}
																				else
																				{
																					if (num == 20)
																					{
																						this.DataLength = this.AF0D_F20(Data);
																					}
																					else
																					{
																						if (num == 21)
																						{
																							this.DataLength = this.AF0D_F21(Data);
																						}
																						else
																						{
																							if (num == 22)
																							{
																								this.DataLength = this.AF0D_F22(Data);
																							}
																							else
																							{
																								if (num == 23)
																								{
																									this.DataLength = this.AF0D_F23(Data);
																								}
																								else
																								{
																									if (num == 24)
																									{
																										this.DataLength = this.AF0D_F24(Data);
																									}
																									else
																									{
																										if (num == 25)
																										{
																											this.DataLength = this.AF0D_F25(Data);
																										}
																										else
																										{
																											if (num == 26)
																											{
																												this.DataLength = this.AF0D_F26(Data);
																											}
																											else
																											{
																												if (num == 27)
																												{
																													this.DataLength = this.AF0D_F27(Data);
																												}
																												else
																												{
																													if (num == 28)
																													{
																														this.DataLength = this.AF0D_F28(Data);
																													}
																													else
																													{
																														if (num == 29)
																														{
																															this.DataLength = this.AF0D_F29(Data);
																														}
																														else
																														{
																															if (num == 30)
																															{
																																this.DataLength = this.AF0D_F30(Data);
																															}
																															else
																															{
																																if (num == 31)
																																{
																																	this.DataLength = this.AF0D_F31(Data);
																																}
																																else
																																{
																																	if (num == 32)
																																	{
																																		this.DataLength = this.AF0D_F32(Data);
																																	}
																																	else
																																	{
																																		if (num == 33)
																																		{
																																			this.DataLength = this.AF0D_F33(Data);
																																		}
																																		else
																																		{
																																			if (num == 34)
																																			{
																																				this.DataLength = this.AF0D_F34(Data);
																																			}
																																			else
																																			{
																																				if (num == 35)
																																				{
																																					this.DataLength = this.AF0D_F35(Data);
																																				}
																																				else
																																				{
																																					if (num == 36)
																																					{
																																						this.DataLength = this.AF0D_F36(Data);
																																					}
																																					else
																																					{
																																						if (num == 37)
																																						{
																																							this.DataLength = this.AF0D_F37(Data);
																																						}
																																						else
																																						{
																																							if (num == 38)
																																							{
																																								this.DataLength = this.AF0D_F38(Data);
																																							}
																																							else
																																							{
																																								if (num == 39)
																																								{
																																									this.DataLength = this.AF0D_F39(Data);
																																								}
																																								else
																																								{
																																									if (num == 41)
																																									{
																																										this.DataLength = this.AF0D_F41(Data);
																																									}
																																									else
																																									{
																																										if (num == 42)
																																										{
																																											this.DataLength = this.AF0D_F42(Data);
																																										}
																																										else
																																										{
																																											if (num == 43)
																																											{
																																												this.DataLength = this.AF0D_F43(Data);
																																											}
																																											else
																																											{
																																												if (num == 44)
																																												{
																																													this.DataLength = this.AF0D_F44(Data);
																																												}
																																												else
																																												{
																																													if (num == 45)
																																													{
																																														this.DataLength = this.AF0D_F45(Data);
																																													}
																																													else
																																													{
																																														if (num == 46)
																																														{
																																															this.DataLength = this.AF0D_F46(Data);
																																														}
																																														else
																																														{
																																															if (num == 49)
																																															{
																																																this.DataLength = this.AF0D_F49(Data);
																																															}
																																															else
																																															{
																																																if (num == 50)
																																																{
																																																	this.DataLength = this.AF0D_F50(Data);
																																																}
																																																else
																																																{
																																																	if (num == 51)
																																																	{
																																																		this.DataLength = this.AF0D_F51(Data);
																																																	}
																																																	else
																																																	{
																																																		if (num == 52)
																																																		{
																																																			this.DataLength = this.AF0D_F52(Data);
																																																		}
																																																		else
																																																		{
																																																			if (num == 53)
																																																			{
																																																				this.DataLength = this.AF0D_F53(Data);
																																																			}
																																																			else
																																																			{
																																																				if (num == 54)
																																																				{
																																																					this.DataLength = this.AF0D_F54(Data);
																																																				}
																																																				else
																																																				{
																																																					if (num == 57)
																																																					{
																																																						this.DataLength = this.AF0D_F57(Data);
																																																					}
																																																					else
																																																					{
																																																						if (num == 58)
																																																						{
																																																							this.DataLength = this.AF0D_F58(Data);
																																																						}
																																																						else
																																																						{
																																																							if (num == 59)
																																																							{
																																																								this.DataLength = this.AF0D_F59(Data);
																																																							}
																																																							else
																																																							{
																																																								if (num == 60)
																																																								{
																																																									this.DataLength = this.AF0D_F60(Data);
																																																								}
																																																								else
																																																								{
																																																									if (num == 61)
																																																									{
																																																										this.DataLength = this.AF0D_F61(Data);
																																																									}
																																																									else
																																																									{
																																																										if (num == 62)
																																																										{
																																																											this.DataLength = this.AF0D_F62(Data);
																																																										}
																																																										else
																																																										{
																																																											if (num == 65)
																																																											{
																																																												this.DataLength = this.AF0D_F65(Data);
																																																											}
																																																											else
																																																											{
																																																												if (num == 66)
																																																												{
																																																													this.DataLength = this.AF0D_F66(Data);
																																																												}
																																																												else
																																																												{
																																																													if (num == 73)
																																																													{
																																																														this.DataLength = this.AF0D_F73(Data);
																																																													}
																																																													else
																																																													{
																																																														if (num == 74)
																																																														{
																																																															this.DataLength = this.AF0D_F74(Data);
																																																														}
																																																														else
																																																														{
																																																															if (num == 75)
																																																															{
																																																																this.DataLength = this.AF0D_F75(Data);
																																																															}
																																																															else
																																																															{
																																																																if (num == 76)
																																																																{
																																																																	this.DataLength = this.AF0D_F76(Data);
																																																																}
																																																																else
																																																																{
																																																																	if (num == 81)
																																																																	{
																																																																		this.DataLength = this.AF0D_F81(Data);
																																																																	}
																																																																	else
																																																																	{
																																																																		if (num == 82)
																																																																		{
																																																																			this.DataLength = this.AF0D_F82(Data);
																																																																		}
																																																																		else
																																																																		{
																																																																			if (num == 83)
																																																																			{
																																																																				this.DataLength = this.AF0D_F83(Data);
																																																																			}
																																																																			else
																																																																			{
																																																																				if (num == 84)
																																																																				{
																																																																					this.DataLength = this.AF0D_F84(Data);
																																																																				}
																																																																				else
																																																																				{
																																																																					if (num == 85)
																																																																					{
																																																																						this.DataLength = this.AF0D_F85(Data);
																																																																					}
																																																																					else
																																																																					{
																																																																						if (num == 86)
																																																																						{
																																																																							this.DataLength = this.AF0D_F86(Data);
																																																																						}
																																																																						else
																																																																						{
																																																																							if (num == 87)
																																																																							{
																																																																								this.DataLength = this.AF0D_F87(Data);
																																																																							}
																																																																							else
																																																																							{
																																																																								if (num == 88)
																																																																								{
																																																																									this.DataLength = this.AF0D_F88(Data);
																																																																								}
																																																																								else
																																																																								{
																																																																									if (num == 89)
																																																																									{
																																																																										this.DataLength = this.AF0D_F89(Data);
																																																																									}
																																																																									else
																																																																									{
																																																																										if (num == 90)
																																																																										{
																																																																											this.DataLength = this.AF0D_F90(Data);
																																																																										}
																																																																										else
																																																																										{
																																																																											if (num == 91)
																																																																											{
																																																																												this.DataLength = this.AF0D_F91(Data);
																																																																											}
																																																																											else
																																																																											{
																																																																												if (num == 92)
																																																																												{
																																																																													this.DataLength = this.AF0D_F92(Data);
																																																																												}
																																																																												else
																																																																												{
																																																																													if (num == 93)
																																																																													{
																																																																														this.DataLength = this.AF0D_F93(Data);
																																																																													}
																																																																													else
																																																																													{
																																																																														if (num == 94)
																																																																														{
																																																																															this.DataLength = this.AF0D_F94(Data);
																																																																														}
																																																																														else
																																																																														{
																																																																															if (num == 95)
																																																																															{
																																																																																this.DataLength = this.AF0D_F95(Data);
																																																																															}
																																																																															else
																																																																															{
																																																																																if (num == 97)
																																																																																{
																																																																																	this.DataLength = this.AF0D_F97(Data);
																																																																																}
																																																																																else
																																																																																{
																																																																																	if (num == 98)
																																																																																	{
																																																																																		this.DataLength = this.AF0D_F98(Data);
																																																																																	}
																																																																																	else
																																																																																	{
																																																																																		if (num == 99)
																																																																																		{
																																																																																			this.DataLength = this.AF0D_F99(Data);
																																																																																		}
																																																																																		else
																																																																																		{
																																																																																			if (num == 100)
																																																																																			{
																																																																																				this.DataLength = this.AF0D_F100(Data);
																																																																																			}
																																																																																			else
																																																																																			{
																																																																																				if (num == 101)
																																																																																				{
																																																																																					this.DataLength = this.AF0D_F101(Data);
																																																																																				}
																																																																																				else
																																																																																				{
																																																																																					if (num == 102)
																																																																																					{
																																																																																						this.DataLength = this.AF0D_F102(Data);
																																																																																					}
																																																																																					else
																																																																																					{
																																																																																						if (num == 103)
																																																																																						{
																																																																																							this.DataLength = this.AF0D_F103(Data);
																																																																																						}
																																																																																						else
																																																																																						{
																																																																																							if (num == 104)
																																																																																							{
																																																																																								this.DataLength = this.AF0D_F104(Data);
																																																																																							}
																																																																																							else
																																																																																							{
																																																																																								if (num == 105)
																																																																																								{
																																																																																									this.DataLength = this.AF0D_F105(Data);
																																																																																								}
																																																																																								else
																																																																																								{
																																																																																									if (num == 106)
																																																																																									{
																																																																																										this.DataLength = this.AF0D_F106(Data);
																																																																																									}
																																																																																									else
																																																																																									{
																																																																																										if (num == 107)
																																																																																										{
																																																																																											this.DataLength = this.AF0D_F107(Data);
																																																																																										}
																																																																																										else
																																																																																										{
																																																																																											if (num == 108)
																																																																																											{
																																																																																												this.DataLength = this.AF0D_F108(Data);
																																																																																											}
																																																																																											else
																																																																																											{
																																																																																												if (num == 109)
																																																																																												{
																																																																																													this.DataLength = this.AF0D_F109(Data);
																																																																																												}
																																																																																												else
																																																																																												{
																																																																																													if (num == 110)
																																																																																													{
																																																																																														this.DataLength = this.AF0D_F110(Data);
																																																																																													}
																																																																																													else
																																																																																													{
																																																																																														if (num == 113)
																																																																																														{
																																																																																															this.DataLength = this.AF0D_F113(Data);
																																																																																														}
																																																																																														else
																																																																																														{
																																																																																															if (num == 114)
																																																																																															{
																																																																																																this.DataLength = this.AF0D_F114(Data);
																																																																																															}
																																																																																															else
																																																																																															{
																																																																																																if (num == 115)
																																																																																																{
																																																																																																	this.DataLength = this.AF0D_F115(Data);
																																																																																																}
																																																																																																else
																																																																																																{
																																																																																																	if (num == 116)
																																																																																																	{
																																																																																																		this.DataLength = this.AF0D_F116(Data);
																																																																																																	}
																																																																																																	else
																																																																																																	{
																																																																																																		if (num == 117)
																																																																																																		{
																																																																																																			this.DataLength = this.AF0D_F117(Data);
																																																																																																		}
																																																																																																		else
																																																																																																		{
																																																																																																			if (num == 118)
																																																																																																			{
																																																																																																				this.DataLength = this.AF0D_F118(Data);
																																																																																																			}
																																																																																																			else
																																																																																																			{
																																																																																																				if (num == 121)
																																																																																																				{
																																																																																																					this.DataLength = this.AF0D_F121(Data);
																																																																																																				}
																																																																																																				else
																																																																																																				{
																																																																																																					if (num == 122)
																																																																																																					{
																																																																																																						this.DataLength = this.AF0D_F122(Data);
																																																																																																					}
																																																																																																					else
																																																																																																					{
																																																																																																						if (num == 123)
																																																																																																						{
																																																																																																							this.DataLength = this.AF0D_F123(Data);
																																																																																																						}
																																																																																																						else
																																																																																																						{
																																																																																																							if (num == 129)
																																																																																																							{
																																																																																																								this.DataLength = this.AF0D_F129(Data);
																																																																																																							}
																																																																																																							else
																																																																																																							{
																																																																																																								if (num == 130)
																																																																																																								{
																																																																																																									this.DataLength = this.AF0D_F130(Data);
																																																																																																								}
																																																																																																								else
																																																																																																								{
																																																																																																									if (num == 138)
																																																																																																									{
																																																																																																										this.DataLength = this.AF0D_F138(Data);
																																																																																																									}
																																																																																																									else
																																																																																																									{
																																																																																																										if (num == 145)
																																																																																																										{
																																																																																																											this.DataLength = this.AF0D_F145(Data);
																																																																																																										}
																																																																																																										else
																																																																																																										{
																																																																																																											if (num == 146)
																																																																																																											{
																																																																																																												this.DataLength = this.AF0D_F146(Data);
																																																																																																											}
																																																																																																											else
																																																																																																											{
																																																																																																												if (num == 147)
																																																																																																												{
																																																																																																													this.DataLength = this.AF0D_F147(Data);
																																																																																																												}
																																																																																																												else
																																																																																																												{
																																																																																																													if (num == 148)
																																																																																																													{
																																																																																																														this.DataLength = this.AF0D_F148(Data);
																																																																																																													}
																																																																																																													else
																																																																																																													{
																																																																																																														if (num == 152)
																																																																																																														{
																																																																																																															this.DataLength = this.AF0D_F152(Data);
																																																																																																														}
																																																																																																														else
																																																																																																														{
																																																																																																															if (num == 153)
																																																																																																															{
																																																																																																																this.DataLength = this.AF0D_F153(Data);
																																																																																																															}
																																																																																																															else
																																																																																																															{
																																																																																																																if (num == 154)
																																																																																																																{
																																																																																																																	this.DataLength = this.AF0D_F154(Data);
																																																																																																																}
																																																																																																																else
																																																																																																																{
																																																																																																																	if (num == 155)
																																																																																																																	{
																																																																																																																		this.DataLength = this.AF0D_F155(Data);
																																																																																																																	}
																																																																																																																	else
																																																																																																																	{
																																																																																																																		if (num == 156)
																																																																																																																		{
																																																																																																																			this.DataLength = this.AF0D_F156(Data);
																																																																																																																		}
																																																																																																																		else
																																																																																																																		{
																																																																																																																			if (num == 157)
																																																																																																																			{
																																																																																																																				this.DataLength = this.AF0D_F157(Data);
																																																																																																																			}
																																																																																																																			else
																																																																																																																			{
																																																																																																																				if (num == 158)
																																																																																																																				{
																																																																																																																					this.DataLength = this.AF0D_F158(Data);
																																																																																																																				}
																																																																																																																				else
																																																																																																																				{
																																																																																																																					if (num == 159)
																																																																																																																					{
																																																																																																																						this.DataLength = this.AF0D_F159(Data);
																																																																																																																					}
																																																																																																																					else
																																																																																																																					{
																																																																																																																						if (num == 160)
																																																																																																																						{
																																																																																																																							this.DataLength = this.AF0D_F160(Data);
																																																																																																																						}
																																																																																																																						else
																																																																																																																						{
																																																																																																																							if (num == 161)
																																																																																																																							{
																																																																																																																								this.DataLength = this.AF0D_F161(Data);
																																																																																																																							}
																																																																																																																							else
																																																																																																																							{
																																																																																																																								if (num == 162)
																																																																																																																								{
																																																																																																																									this.DataLength = this.AF0D_F162(Data);
																																																																																																																								}
																																																																																																																								else
																																																																																																																								{
																																																																																																																									if (num == 163)
																																																																																																																									{
																																																																																																																										this.DataLength = this.AF0D_F163(Data);
																																																																																																																									}
																																																																																																																									else
																																																																																																																									{
																																																																																																																										if (num == 164)
																																																																																																																										{
																																																																																																																											this.DataLength = this.AF0D_F164(Data);
																																																																																																																										}
																																																																																																																										else
																																																																																																																										{
																																																																																																																											if (num == 165)
																																																																																																																											{
																																																																																																																												this.DataLength = this.AF0D_F165(Data);
																																																																																																																											}
																																																																																																																											else
																																																																																																																											{
																																																																																																																												if (num == 166)
																																																																																																																												{
																																																																																																																													this.DataLength = this.AF0D_F166(Data);
																																																																																																																												}
																																																																																																																												else
																																																																																																																												{
																																																																																																																													if (num == 167)
																																																																																																																													{
																																																																																																																														this.DataLength = this.AF0D_F167(Data);
																																																																																																																													}
																																																																																																																													else
																																																																																																																													{
																																																																																																																														if (num == 168)
																																																																																																																														{
																																																																																																																															this.DataLength = this.AF0D_F168(Data);
																																																																																																																														}
																																																																																																																														else
																																																																																																																														{
																																																																																																																															if (num == 169)
																																																																																																																															{
																																																																																																																																this.DataLength = this.AF0D_F169(Data);
																																																																																																																															}
																																																																																																																															else
																																																																																																																															{
																																																																																																																																if (num == 170)
																																																																																																																																{
																																																																																																																																	this.DataLength = this.AF0D_F170(Data);
																																																																																																																																}
																																																																																																																																else
																																																																																																																																{
																																																																																																																																	if (num == 171)
																																																																																																																																	{
																																																																																																																																		this.DataLength = this.AF0D_F171(Data);
																																																																																																																																	}
																																																																																																																																	else
																																																																																																																																	{
																																																																																																																																		if (num == 172)
																																																																																																																																		{
																																																																																																																																			this.DataLength = this.AF0D_F172(Data);
																																																																																																																																		}
																																																																																																																																		else
																																																																																																																																		{
																																																																																																																																			if (num == 173)
																																																																																																																																			{
																																																																																																																																				this.DataLength = this.AF0D_F173(Data);
																																																																																																																																			}
																																																																																																																																			else
																																																																																																																																			{
																																																																																																																																				if (num == 174)
																																																																																																																																				{
																																																																																																																																					this.DataLength = this.AF0D_F174(Data);
																																																																																																																																				}
																																																																																																																																				else
																																																																																																																																				{
																																																																																																																																					if (num == 175)
																																																																																																																																					{
																																																																																																																																						this.DataLength = this.AF0D_F175(Data);
																																																																																																																																					}
																																																																																																																																					else
																																																																																																																																					{
																																																																																																																																						if (num == 176)
																																																																																																																																						{
																																																																																																																																							this.DataLength = this.AF0D_F176(Data);
																																																																																																																																						}
																																																																																																																																						else
																																																																																																																																						{
																																																																																																																																							if (num == 177)
																																																																																																																																							{
																																																																																																																																								this.DataLength = this.AF0D_F177(Data);
																																																																																																																																							}
																																																																																																																																							else
																																																																																																																																							{
																																																																																																																																								if (num == 178)
																																																																																																																																								{
																																																																																																																																									this.DataLength = this.AF0D_F178(Data);
																																																																																																																																								}
																																																																																																																																								else
																																																																																																																																								{
																																																																																																																																									if (num == 179)
																																																																																																																																									{
																																																																																																																																										this.DataLength = this.AF0D_F179(Data);
																																																																																																																																									}
																																																																																																																																									else
																																																																																																																																									{
																																																																																																																																										if (num == 180)
																																																																																																																																										{
																																																																																																																																											this.DataLength = this.AF0D_F180(Data);
																																																																																																																																										}
																																																																																																																																										else
																																																																																																																																										{
																																																																																																																																											if (num == 181)
																																																																																																																																											{
																																																																																																																																												this.DataLength = this.AF0D_F181(Data);
																																																																																																																																											}
																																																																																																																																											else
																																																																																																																																											{
																																																																																																																																												if (num == 182)
																																																																																																																																												{
																																																																																																																																													this.DataLength = this.AF0D_F182(Data);
																																																																																																																																												}
																																																																																																																																												else
																																																																																																																																												{
																																																																																																																																													if (num == 183)
																																																																																																																																													{
																																																																																																																																														this.DataLength = this.AF0D_F183(Data);
																																																																																																																																													}
																																																																																																																																													else
																																																																																																																																													{
																																																																																																																																														if (num == 184)
																																																																																																																																														{
																																																																																																																																															this.DataLength = this.AF0D_F184(Data);
																																																																																																																																														}
																																																																																																																																														else
																																																																																																																																														{
																																																																																																																																															if (num == 185)
																																																																																																																																															{
																																																																																																																																																this.DataLength = this.AF0D_F185(Data);
																																																																																																																																															}
																																																																																																																																															else
																																																																																																																																															{
																																																																																																																																																if (num == 186)
																																																																																																																																																{
																																																																																																																																																	this.DataLength = this.AF0D_F186(Data);
																																																																																																																																																}
																																																																																																																																																else
																																																																																																																																																{
																																																																																																																																																	if (num == 187)
																																																																																																																																																	{
																																																																																																																																																		this.DataLength = this.AF0D_F187(Data);
																																																																																																																																																	}
																																																																																																																																																	else
																																																																																																																																																	{
																																																																																																																																																		if (num == 188)
																																																																																																																																																		{
																																																																																																																																																			this.DataLength = this.AF0D_F188(Data);
																																																																																																																																																		}
																																																																																																																																																		else
																																																																																																																																																		{
																																																																																																																																																			if (num == 189)
																																																																																																																																																			{
																																																																																																																																																				this.DataLength = this.AF0D_F189(Data);
																																																																																																																																																			}
																																																																																																																																																			else
																																																																																																																																																			{
																																																																																																																																																				if (num == 190)
																																																																																																																																																				{
																																																																																																																																																					this.DataLength = this.AF0D_F190(Data);
																																																																																																																																																				}
																																																																																																																																																				else
																																																																																																																																																				{
																																																																																																																																																					if (num == 191)
																																																																																																																																																					{
																																																																																																																																																						this.DataLength = this.AF0D_F191(Data);
																																																																																																																																																					}
																																																																																																																																																					else
																																																																																																																																																					{
																																																																																																																																																						if (num == 192)
																																																																																																																																																						{
																																																																																																																																																							this.DataLength = this.AF0D_F192(Data);
																																																																																																																																																						}
																																																																																																																																																						else
																																																																																																																																																						{
																																																																																																																																																							if (num == 193)
																																																																																																																																																							{
																																																																																																																																																								this.DataLength = this.AF0D_F193(Data);
																																																																																																																																																							}
																																																																																																																																																							else
																																																																																																																																																							{
																																																																																																																																																								if (num == 194)
																																																																																																																																																								{
																																																																																																																																																									this.DataLength = this.AF0D_F194(Data);
																																																																																																																																																								}
																																																																																																																																																								else
																																																																																																																																																								{
																																																																																																																																																									if (num == 195)
																																																																																																																																																									{
																																																																																																																																																										this.DataLength = this.AF0D_F195(Data);
																																																																																																																																																									}
																																																																																																																																																									else
																																																																																																																																																									{
																																																																																																																																																										if (num == 196)
																																																																																																																																																										{
																																																																																																																																																											this.DataLength = this.AF0D_F196(Data);
																																																																																																																																																										}
																																																																																																																																																										else
																																																																																																																																																										{
																																																																																																																																																											if (num == 201)
																																																																																																																																																											{
																																																																																																																																																												this.DataLength = this.AF0D_F201(Data);
																																																																																																																																																											}
																																																																																																																																																											else
																																																																																																																																																											{
																																																																																																																																																												if (num == 202)
																																																																																																																																																												{
																																																																																																																																																													this.DataLength = this.AF0D_F202(Data);
																																																																																																																																																												}
																																																																																																																																																												else
																																																																																																																																																												{
																																																																																																																																																													if (num == 203)
																																																																																																																																																													{
																																																																																																																																																														this.DataLength = this.AF0D_F203(Data);
																																																																																																																																																													}
																																																																																																																																																													else
																																																																																																																																																													{
																																																																																																																																																														if (num == 204)
																																																																																																																																																														{
																																																																																																																																																															this.DataLength = this.AF0D_F204(Data);
																																																																																																																																																														}
																																																																																																																																																														else
																																																																																																																																																														{
																																																																																																																																																															if (num == 205)
																																																																																																																																																															{
																																																																																																																																																																this.DataLength = this.AF0D_F205(Data);
																																																																																																																																																															}
																																																																																																																																																															else
																																																																																																																																																															{
																																																																																																																																																																if (num == 206)
																																																																																																																																																																{
																																																																																																																																																																	this.DataLength = this.AF0D_F206(Data);
																																																																																																																																																																}
																																																																																																																																																																else
																																																																																																																																																																{
																																																																																																																																																																	if (num == 207)
																																																																																																																																																																	{
																																																																																																																																																																		this.DataLength = this.AF0D_F207(Data);
																																																																																																																																																																	}
																																																																																																																																																																	else
																																																																																																																																																																	{
																																																																																																																																																																		if (num == 208)
																																																																																																																																																																		{
																																																																																																																																																																			this.DataLength = this.AF0D_F208(Data);
																																																																																																																																																																		}
																																																																																																																																																																		else
																																																																																																																																																																		{
																																																																																																																																																																			if (num == 209)
																																																																																																																																																																			{
																																																																																																																																																																				this.DataLength = this.AF0D_F209(Data);
																																																																																																																																																																			}
																																																																																																																																																																			else
																																																																																																																																																																			{
																																																																																																																																																																				if (num == 213)
																																																																																																																																																																				{
																																																																																																																																																																					this.DataLength = this.AF0D_F213(Data);
																																																																																																																																																																				}
																																																																																																																																																																				else
																																																																																																																																																																				{
																																																																																																																																																																					if (num == 214)
																																																																																																																																																																					{
																																																																																																																																																																						this.DataLength = this.AF0D_F214(Data);
																																																																																																																																																																					}
																																																																																																																																																																					else
																																																																																																																																																																					{
																																																																																																																																																																						if (num == 215)
																																																																																																																																																																						{
																																																																																																																																																																							this.DataLength = this.AF0D_F215(Data);
																																																																																																																																																																						}
																																																																																																																																																																						else
																																																																																																																																																																						{
																																																																																																																																																																							if (num == 216)
																																																																																																																																																																							{
																																																																																																																																																																								this.DataLength = this.AF0D_F216(Data);
																																																																																																																																																																							}
																																																																																																																																																																							else
																																																																																																																																																																							{
																																																																																																																																																																								if (num == 217)
																																																																																																																																																																								{
																																																																																																																																																																									this.DataLength = this.AF0D_F217(Data);
																																																																																																																																																																								}
																																																																																																																																																																								else
																																																																																																																																																																								{
																																																																																																																																																																									if (num == 218)
																																																																																																																																																																									{
																																																																																																																																																																										this.DataLength = this.AF0D_F218(Data);
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
													}
												}
											}
										}
									}
								}
							}
						}
					}
					if (AFN == "0E")
					{
						if (num == 1 | num == 2)
						{
							this.DataLength = this.AF0E_F1(Data);
						}
					}
					if (AFN == "10")
					{
						if (num == 1)
						{
							this.DataLength = this.AF10_F1(Data, Format);
						}
						else
						{
							if (num == 9)
							{
								this.DataLength = this.AF10_F9(Data, Format);
							}
							else
							{
								if (num == 10)
								{
									this.DataLength = this.AF10_F10(Data);
								}
								else
								{
									if (num == 11)
									{
										this.DataLength = this.AF10_F11(Data);
									}
								}
							}
						}
					}
				}
				else
				{
					this.DataLength = this.CustomizeAnalysis(CustomizeItems, Data);
				}
			}
		}
		private int AF00_F3(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("AFN", this.OperaRec(Value.Substring(num, 2), "BCD"));
					num += 2;
					int num2 = 1;
					while (true)
					{
						string empty = string.Empty;
						string empty2 = string.Empty;
						string strValue = Value.Substring(num, 8);
						this.gDLT698.GetDataCellMark(strValue, ref empty, ref empty2);
						this.ItemAdd("数据单元标识" + num2.ToString(), "FN=" + empty + ",PN=" + empty2);
						num += 8;
						int num3 = int.Parse(this.OperaRec(Value.Substring(num, 2), "BIN"));
						string values = string.Empty;
						switch (num3)
						{
						case 0:
							values = "正确";
							break;

						case 1:
							values = "错误";
							break;

						default:
							values = "备用";
							break;
						}
						this.ItemAdd("ERR" + num2.ToString(), values);
						num += 2;
						if (num > Value.Length - 1)
						{
							break;
						}
						num2++;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF03_F1(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("中继站工作状态控制应答", this.AF03_F1_Ret(Value));
					num += Value.Length;
					result = num;
				}
				return result;
			}
		}
		private string AF03_F1_Ret(string Value)
		{
			string result;
			if (!string.IsNullOrEmpty(Value))
			{
				int num = 0;
				string text = string.Empty;
				long num2 = DataConvert.HexToLong(DataConvert.ReverseStr(Value));
				long num3;
				checked
				{
					num += Value.Length;
					num3 = (num2 & 3L);
				}
				if (num3 <= 3L)
				{
					if (num3 >= 0L)
					{
						switch ((int)num3)
						{
						case 0:
							text += "A机状态:不存在";
							break;

						case 1:
							text += "A机状态:正常";
							break;

						case 2:
							text += "A机状态:故障";
							break;

						case 3:
							text += "A机状态:备用";
							break;
						}
					}
				}
				text += (((num2 >> 2 & 1L) == 0L) ? "A机为备份机" : "A机为值班机");
				text += (((num2 >> 3 & 1L) == 0L) ? "A机禁止中继转发" : "A机允许中继转发");
				num3 = (num2 >> 4 & 3L);
				if (num3 <= 3L)
				{
					if (num3 >= 0L)
					{
						switch ((int)num3)
						{
						case 0:
							text += "B机状态:不存在";
							break;

						case 1:
							text += "B机状态:正常";
							break;

						case 2:
							text += "B机状态:故障";
							break;

						case 3:
							text += "B机状态:备用";
							break;
						}
					}
				}
				
				text += (((num2 >> 6 & 1L) == 0L) ? "B机为备份机" : "B机为值班机");
				text += (((num2 >> 7 & 1L) == 0L) ? "B机禁止中继转发" : "B机允许中继转发");
				result = text;
				return result;
				
			}
			result = "";
			return result;
		}
		private int AF03_F2(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("中继站工作状态应答", this.AF03_F1_Ret(Value));
					num += Value.Length;
					result = num;
				}
				return result;
			}
		}
		private int AF03_F3(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					for (int i = 0; i < 10; i++)
					{
						this.ItemAdd("最近" + (10 - i).ToString() + "次切换时间", this.OperaRec(Value.Substring(num, 10), "A15"));
						num += 10;
						this.ItemAdd("最近" + (10 - i).ToString() + "次切换前中继站工作状态", this.AF03_F1_Ret(Value.Substring(num, 2)));
						num += 2;
						this.ItemAdd("最近" + (10 - i).ToString() + "次切换后中继站工作状态", this.AF03_F1_Ret(Value.Substring(num, 2)));
						num += 2;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF03_F4(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("切换累计次数", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("A机值班累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("A机正常运行累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("B机值班累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("B机正常运行累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					result = num;
				}
				return result;
			}
		}
		private int AF06_F1(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("信息", this.OperaRec(Value, "BIN"));
					num += Value.Length;
					result = num;
				}
				return result;
			}
		}
		private int AF09_F1(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("厂商代号", this.OperaRec(Value.Substring(num, 8), "ASCII"));
					num += 8;
					this.ItemAdd("设备编号", this.OperaRec(Value.Substring(num, 16), "ASCII"));
					num += 16;
					this.ItemAdd("终端软件版本号", this.OperaRec(Value.Substring(num, 8), "ASCII"));
					num += 8;
					this.ItemAdd("终端软件发布日期", this.OperaRec(Value.Substring(num, 6), "A20"));
					num += 6;
					this.ItemAdd("终端配置容量信息码", this.OperaRec(Value.Substring(num, 22), "ASCII"));
					num += 22;
					this.ItemAdd("终端通信协议版本号", this.OperaRec(Value.Substring(num, 8), "ASCII"));
					num += 8;
					this.ItemAdd("终端硬件版本号", this.OperaRec(Value.Substring(num, 8), "ASCII"));
					num += 8;
					this.ItemAdd("终端硬件发布日期", this.OperaRec(Value.Substring(num, 6), "A20"));
					num += 6;
					result = num;
				}
				return result;
			}
		}
        private int AF09_F2(string Value)
        {
            if (string.IsNullOrEmpty(Value))
            {
                return 0;
            }
            int startIndex = 0;
            this.ItemAdd("脉冲量输入路数", this.OperaRec(Value.Substring(startIndex, 2), "BIN"));
            startIndex += 2;
            this.ItemAdd("开关量输入路数", this.OperaRec(Value.Substring(startIndex, 2), "BIN"));
            startIndex += 2;
            this.ItemAdd("直流模拟量输入路数", this.OperaRec(Value.Substring(startIndex, 2), "BIN"));
            startIndex += 2;
            this.ItemAdd("开关量输出路数(轮次)", this.OperaRec(Value.Substring(startIndex, 2), "BIN"));
            startIndex += 2;
            this.ItemAdd("支持的抄电能表/交流采样装置最多个数", this.OperaRec(Value.Substring(startIndex, 4), "BIN"));
            startIndex += 4;
            this.ItemAdd("支持的终端上行通信最大接收缓存区字节数", this.OperaRec(Value.Substring(startIndex, 4), "BIN"));
            startIndex += 4;
            this.ItemAdd("支持的终端上行通信最大发送缓存区字节数", this.OperaRec(Value.Substring(startIndex, 4), "BIN"));
            startIndex += 4;
            this.ItemAdd("终端MAC地址1段", this.OperaRec(Value.Substring(startIndex, 2), "BIN"));
            startIndex += 2;
            this.ItemAdd("终端MAC地址2段", this.OperaRec(Value.Substring(startIndex, 2), "BIN"));
            startIndex += 2;
            this.ItemAdd("终端MAC地址3段", this.OperaRec(Value.Substring(startIndex, 2), "BIN"));
            startIndex += 2;
            this.ItemAdd("终端MAC地址4段", this.OperaRec(Value.Substring(startIndex, 2), "BIN"));
            startIndex += 2;
            this.ItemAdd("终端MAC地址5段", this.OperaRec(Value.Substring(startIndex, 2), "BIN"));
            startIndex += 2;
            this.ItemAdd("终端MAC地址6段", this.OperaRec(Value.Substring(startIndex, 2), "BIN"));
            startIndex += 2;
            int num2 = DataConvert.HexToInt(Value.Substring(startIndex, 2));
            this.ItemAdd("通信端口数量", num2.ToString());
            startIndex += 2;
            for (int i = 0; i < num2; i++)
            {
                int num8;
                long num4 = DataConvert.HexToLong(DataConvert.ReverseStr(Value.Substring(startIndex, 4)));
                string values = string.Empty + "\r\n端口号:" + ((num4 & 0x1fL)).ToString() + ",";
                long num7 = (num4 >> 5) & 3L;
                if ((num7 <= 3L) && (num7 >= 0L))
                {
                    switch (((int)num7))
                    {
                        case 0:
                            values = values + "接口及通道类型:直接RS485接口,";
                            break;

                        case 1:
                            values = values + "接口及通道类型:直接RS232接口,";
                            break;

                        case 2:
                            values = values + "接口及通道类型:串行接口连接窄带低压载波通信模块,";
                            break;

                        case 3:
                            values = values + "接口及通道类型:保留,";
                            break;
                    }
                }
                values = values + ((((num4 >> 7) & 1L) == 0L) ? "标准异步串行口," : "非标准异步串行口,");
                num7 = (num4 >> 13) & 3L;
                if ((num7 <= 3L) && (num7 >= 0L))
                {
                    switch (((int)num7))
                    {
                        case 0:
                            values = values + "专变/公变抄表,";
                            goto Label_0358;

                        case 1:
                            values = values + "变电站抄表,";
                            goto Label_0358;

                        case 2:
                            values = values + "台区低压集抄,";
                            goto Label_0358;

                        case 3:
                            values = values + "当地用户侧数据共享,";
                            goto Label_0358;
                    }
                }
                values = values + "备用,";
            Label_0358:
                num8 = i + 1;
                this.ItemAdd("第" + num8.ToString() + "个通信端口的端口号及信息字", values);
                startIndex += 4;
                num8 = i + 1;
                this.ItemAdd("第" + num8.ToString() + "个通信端口支持的最高波特率", this.OperaRec(Value.Substring(startIndex, 8), "BIN"));
                startIndex += 8;
                num8 = i + 1;
                this.ItemAdd("第" + num8.ToString() + "个通信端口支持的设备个数", this.OperaRec(Value.Substring(startIndex, 4), "BIN"));
                startIndex += 4;
                num8 = i + 1;
                this.ItemAdd("第" + num8.ToString() + "个通信端口支持的最大接收缓存区字节数", this.OperaRec(Value.Substring(startIndex, 4), "BIN"));
                startIndex += 4;
                this.ItemAdd("第" + ((i + 1)).ToString() + "个通信端口支持的最大发送缓存区字节数", this.OperaRec(Value.Substring(startIndex, 4), "BIN"));
                startIndex += 4;
            }
            return startIndex;
        }
        private int AF09_F3(string Value)
        {
            int num4;
            if (string.IsNullOrEmpty(Value))
            {
                return 0;
            }
            int startIndex = 0;
            this.ItemAdd("支持的测量点最多点数", this.OperaRec(Value.Substring(startIndex, 4), "BIN"));
            startIndex += 4;
            this.ItemAdd("支持的总加组最多组数", this.OperaRec(Value.Substring(startIndex, 2), "BIN"));
            startIndex += 2;
            this.ItemAdd("支持的任务最多个数", this.OperaRec(Value.Substring(startIndex, 2), "BIN"));
            startIndex += 2;
            this.ItemAdd("支持的有功总电能量差动组最多组数", this.OperaRec(Value.Substring(startIndex, 2), "BIN"));
            startIndex += 2;
            this.ItemAdd("支持的最大费率数", this.OperaRec(Value.Substring(startIndex, 2), "BIN"));
            startIndex += 2;
            int num = 0;
            this.ItemAdd("支持的测量点数据最大冻结密度", this.C1(this.OperaRec(Value.Substring(startIndex, 2), "BIN"), ref num));
            startIndex += 2;
            this.ItemAdd("支持的总加组有功功率数据最大冻结密度", this.C1(this.OperaRec(Value.Substring(startIndex, 2), "BIN"), ref num));
            startIndex += 2;
            this.ItemAdd("支持的总加组无功功率数据最大冻结密度", this.C1(this.OperaRec(Value.Substring(startIndex, 2), "BIN"), ref num));
            startIndex += 2;
            this.ItemAdd("支持的总加组有功电能量数据最大冻结密度", this.C1(this.OperaRec(Value.Substring(startIndex, 2), "BIN"), ref num));
            startIndex += 2;
            this.ItemAdd("支持的总加组无功电能量数据最大冻结密度", this.C1(this.OperaRec(Value.Substring(startIndex, 2), "BIN"), ref num));
            startIndex += 2;
            this.ItemAdd("支持的日数据最多存放天数", this.OperaRec(Value.Substring(startIndex, 2), "BIN"));
            startIndex += 2;
            this.ItemAdd("支持的月数据最多存放月数", this.OperaRec(Value.Substring(startIndex, 2), "BIN"));
            startIndex += 2;
            this.ItemAdd("支持的时段功控定值方案最多个数", this.OperaRec(Value.Substring(startIndex, 2), "BIN"));
            startIndex += 2;
            this.ItemAdd("支持的谐波检测最高谐波次数", this.OperaRec(Value.Substring(startIndex, 2), "BIN"));
            startIndex += 2;
            this.ItemAdd("支持的无功补偿电容器组最多组数", this.OperaRec(Value.Substring(startIndex, 2), "BIN"));
            startIndex += 2;
            this.ItemAdd("支持的台区集中抄表重点户最多户数", this.OperaRec(Value.Substring(startIndex, 2), "BIN"));
            startIndex += 2;
            int num3 = DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(startIndex, 4)));
            this.ItemAdd("支持的用户大类号标志", num3.ToString());
            startIndex += 4;
            for (num4 = 0; num4 < 0x10; num4++)
            {
                this.ItemAdd(num4.ToString() + "号大类", (((num3 >> num4) & 1) == 1) ? "支持" : "不支持");
            }
            for (num4 = 0; num4 < 0x10; num4++)
            {
                this.ItemAdd("支持" + num4.ToString() + "号用户大类下的用户小类号个数", this.OperaRec(Value.Substring(startIndex, 2), "BIN"));
                startIndex += 2;
            }
            return startIndex;
        }
		private int AF09_F4(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = DataConvert.HexToInt(Value.Substring(0, 2));
					this.ItemAdd("支持的信息类组数", num.ToString());
					int num2 = 2;
					for (int i = 0; i < num; i++)
					{
						int num3 = DataConvert.HexToInt(Value.Substring(num2, 2));
						num2 += 2;
						string text = string.Empty;
						for (int j = 0; j < 8; j++)
						{
							if ((num3 >> j & 1) == 1)
							{
								text = text + "F" + (8 * i + 1 + j).ToString() + ",";
							}
						}
						this.ItemAdd("第" + (i + 1).ToString() + "组信息类组所对应的信息类元标志位", text);
					}
					result = num2;
				}
				return result;
			}
		}
		private int AF09_F5(string Value)
		{
			return this.AF09_F4(Value);
		}
		private int AF09_F6(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					long num2 = DataConvert.HexToLong(DataConvert.ReverseStr(Value.Substring(num, 4)));
					this.ItemAdd("支持的用户大类号标志", num2.ToString());
					num += 4;
					for (int i = 0; i < 16; i++)
					{
						if ((num2 >> i & 1L) == 1L)
						{
							int num3 = DataConvert.HexToInt(Value.Substring(num, 2));
							num += 2;
							this.ItemAdd((i + 1).ToString() + ".支持的信息类组数", num3.ToString());
							for (int j = 0; j < num3; j++)
							{
								int num4 = DataConvert.HexToInt(Value.Substring(num, 2));
								num += 2;
								string text = string.Empty;
								for (int k = 0; k < 8; k++)
								{
									if ((num4 >> k & 1) == 1)
									{
										text = text + "F" + (8 * j + 1 + k).ToString() + ",";
									}
								}
								this.ItemAdd((i + 1).ToString() + ".支持的第" + (j + 1).ToString() + "组信息类组所对应的信息类元标志位", text);
							}
						}
					}
					result = num;
				}
				return result;
			}
		}
		private int AF09_F7(string Value)
		{
			return this.AF09_F6(Value);
		}
		private int AF09_F8(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					string[] array = this.ALLERC.Split(new char[]
					{
						'~'
					});
					int num = 0;
					string text = this.OperaRec(Value.Substring(0, 16), "BS");
					num += 16;
					string text2 = string.Empty;
					for (int i = 0; i < 64; i++)
					{
						if (text.Substring(i, 1) == "1" & !string.IsNullOrEmpty(array[i]))
						{
							string text3 = text2;
							text2 = string.Concat(new string[]
							{
								text3,
								"\r\nERC[",
								(i + 1).ToString(),
								"] ",
								array[i],
								","
							});
						}
					}
					if (string.IsNullOrEmpty(text2))
					{
						text2 = Value;
					}
					this.ItemAdd("支持的事件记录", text2);
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F1(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端数传机延时时间RTS", DataConvert.HexToInt(Value.Substring(num, 2)).ToString());
					num += 2;
					this.ItemAdd("终端作为启动站允许发送传输延时时间", DataConvert.HexToInt(Value.Substring(num, 2)).ToString());
					num += 2;
					int num2 = DataConvert.HexToInt(Value.Substring(num + 2, 2) + Value.Substring(num, 2));
					this.ItemAdd("终端等待从动站响应的超时时间", (num2 & 4095).ToString());
					this.ItemAdd("重发次数", (num2 >> 12 & 3).ToString());
					num += 4;
					byte b = byte.Parse(Value.Substring(num, 2));
					string text = string.Empty;
					text += (((b & 1) == 1) ? "1类数据自动上报," : "");
					text += (((b & 2) == 2) ? "2类数据自动上报," : "");
					text += (((b & 4) == 4) ? "3类数据自动上报," : "");
					this.ItemAdd("需要主站确认的通信服务(CON=1)的标志", text);
					num += 2;
					this.ItemAdd("心跳周期", DataConvert.HexToInt(Value.Substring(num, 2)).ToString());
					num += 2;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F2(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("被转发的终端地址数", (num2 & 127).ToString());
					this.ItemAdd("被转发的终端地址状态", (num2 >> 7 == 0) ? ",禁止终端转发" : ",允许终端转发");
					num += 2;
					for (int i = 0; i < (num2 & 127); i++)
					{
						this.ItemAdd("被转发终端地址" + i.ToString(), DataConvert.ReverseStr(Value.Substring(num, 4)));
						num += 4;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F3(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("主站IP地址", DataConvert.HexStrToIp(Value.Substring(num, 8)));
					num += 8;
					this.ItemAdd("主站端口", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("备用IP地址", DataConvert.HexStrToIp(Value.Substring(num, 8)));
					num += 8;
					this.ItemAdd("备用端口", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("APN", this.OperaRec(Value.Substring(24), "ASCII"));
					num += 32;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F4(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					string text = Value.Substring(num, 16);
					num += 16;
					text = text.Replace("F", "");
					text = text.Replace('A', ',');
					text = text.Replace('B', '#');
					this.ItemAdd("主站电话号码", text);
					text = Value.Substring(num, 16);
					num += 16;
					text = text.Replace("F", "");
					text = text.Replace('A', ',');
					text = text.Replace('B', '#');
					this.ItemAdd("短信中心号码", text);
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F5(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					if (num2 != 0)
					{
						if (num2 != 255)
						{
							this.ItemAdd("消息认证方案号", "认证方案:" + DataConvert.HexToInt(Value.Substring(0, 2)).ToString());
						}
						else
						{
							this.ItemAdd("消息认证方案号", "专用硬件认证方案");
						}
					}
					else
					{
						this.ItemAdd("消息认证方案号", "不认证");
					}
					num += 2;
					this.ItemAdd("消息认证方案参数", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F6(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端组地址1", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("终端组地址2", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("终端组地址3", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("终端组地址4", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("终端组地址5", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("终端组地址6", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("终端组地址7", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("终端组地址8", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F7(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("IP地址", DataConvert.HexStrToIp(DataConvert.ReverseStr(Value.Substring(num, 8))));
					num += 8;
					this.ItemAdd("子网掩码", DataConvert.HexStrToIp(DataConvert.ReverseStr(Value.Substring(num, 8))));
					num += 8;
					this.ItemAdd("网关", DataConvert.HexStrToIp(DataConvert.ReverseStr(Value.Substring(num, 8))));
					num += 8;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					num += 2;
					switch (num2)
					{
					case 0:
						this.ItemAdd("代理类型", "0:不使用代理");
						break;

					case 1:
						this.ItemAdd("代理类型", "1:http connect代理");
						break;

					case 2:
						this.ItemAdd("代理类型", "2:socks4代理");
						break;

					case 3:
						this.ItemAdd("代理类型", "3:socks5代理");
						break;
					}
					this.ItemAdd("代理服务器地址", DataConvert.HexStrToIp(DataConvert.ReverseStr(Value.Substring(num, 8))));
					num += 8;
					this.ItemAdd("代理服务器端口", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					switch (DataConvert.HexToInt(Value.Substring(num, 2)))
					{
					case 0:
						this.ItemAdd("代理服务器连接方式", "无需验证");
						break;

					case 1:
						this.ItemAdd("代理服务器连接方式", "需要用户名及密码");
						break;
					}
					num += 2;
					int num3 = DataConvert.HexToInt(Value.Substring(num, 2));
					num += 2;
					this.ItemAdd("用户名长度", num3.ToString());
					this.ItemAdd("用户名", DataConvert.HexStrToASCII(DataConvert.ReverseStr(Value.Substring(num, 2 * num3))));
					num += 2 * num3;
					int num4 = DataConvert.HexToInt(Value.Substring(num, 2));
					num += 2;
					this.ItemAdd("密码长度", num4.ToString());
					this.ItemAdd("密码", DataConvert.HexStrToASCII(DataConvert.ReverseStr(Value.Substring(num, 2 * num4))));
					num += 2 * num4;
					this.ItemAdd("终端侦听端口", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F8(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					int num3 = num2 >> 7;
					string text = string.Empty;
					text += ((num3 == 0) ? "TCP," : "UDP,");
					num3 = (num2 >> 4 & 3);
					if (num3 == 0)
					{
						text += "混合模式,";
					}
					else
					{
						if (num3 == 1)
						{
							text += "客户机模式,";
						}
						else
						{
							if (num3 == 2)
							{
								text += "服务器模式,";
							}
						}
					}
					num3 = (num2 & 2);
					if (num3 == 0)
					{
						text += "永久在线模式";
					}
					else
					{
						if (num3 == 1)
						{
							text += "被动激活模式";
						}
						else
						{
							if (num3 == 2)
							{
								text += "时段在线模式";
							}
						}
					}
					this.ItemAdd("工作模式", text);
					num += 2;
					this.ItemAdd("时段在线模式重拨间隔", DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(num, 4))).ToString());
					num += 4;
					this.ItemAdd("被动激活模式重拨次数", DataConvert.HexToInt(Value.Substring(num, 2)).ToString());
					num += 2;
					this.ItemAdd("被动激活模式连续无通信自动断线时间", DataConvert.HexToInt(Value.Substring(num, 2)).ToString());
					num += 2;
					text = string.Empty;
					string[] array = this.TimePeriods2.Split(new char[]
					{
						'~'
					});
					long num4 = DataConvert.HexToLong(DataConvert.ReverseStr(Value.Substring(num, 6)));
					this.ItemAdd("时段在线模式允许在线时段标志", this.OperaRec(Value.Substring(10, 6), "BS"));
					for (int i = 0; i < 24; i++)
					{
						this.ItemAdd(array[i], ((num4 >> i & 1L) == 0L) ? "禁止" : "允许");
					}
					num += 6;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F9(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					string[] array = this.ALLERC.Split(new char[]
					{
						'~'
					});
					int num = 0;
					string text = this.OperaRec(Value.Substring(num, 16), "BS");
					num += 16;
					string text2 = string.Empty;
					for (int i = 0; i < 64; i++)
					{
						if (text.Substring(i, 1) == "1" & !string.IsNullOrEmpty(array[i]))
						{
							string text3 = text2;
							text2 = string.Concat(new string[]
							{
								text3,
								"\r\nERC",
								(i + 1).ToString(),
								":",
								array[i],
								","
							});
						}
					}
					this.ItemAdd("事件记录有效标志位", text2);
					text = this.OperaRec(Value.Substring(num, 16), "BS");
					num += 16;
					text2 = string.Empty;
					for (int i = 0; i < 64; i++)
					{
						if (text.Substring(i, 1) == "1" & !string.IsNullOrEmpty(array[i]))
						{
							string text3 = text2;
							text2 = string.Concat(new string[]
							{
								text3,
								"\r\nERC",
								(i + 1).ToString(),
								":",
								array[i],
								","
							});
						}
					}
					this.ItemAdd("事件重要性等级标志位", text2);
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F10(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					string pText = string.Empty;
					int num = 0;
					int num2 = DataConvert.HexToInt(DataConvert.ReverseStr(Value.Substring(num, 4)));
					this.ItemAdd("采样装置配置数量", num2.ToString());
					num += 4;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("第" + (i + 1).ToString() + "块表采样装置序号", this.OperaRec(Value.Substring(num, 4), "BIN"));
						num += 4;
						this.ItemAdd("第" + (i + 1).ToString() + "块表所属测量点号", this.OperaRec(Value.Substring(num, 4), "BIN"));
						num += 4;
						int num3 = DataConvert.HexToInt(Value.Substring(num, 2));
						num += 2;
						this.ItemAdd("第" + (i + 1).ToString() + "块表通信速率", "使用默认值,600,1200,2400,4800,7200,9600,19200".Split(new char[]
						{
							','
						})[num3 >> 5]);
						this.ItemAdd("第" + (i + 1).ToString() + "块表通信端口号", (num3 & 31).ToString());
						pText = DataConvert.HexToInt(Value.Substring(num, 2)).ToString();
						num += 2;
						string[] array = "00.无需抄表,01.645-1997,02.交流采样装置通信协议,30.645-2007,31.串行接口连接窄带低压载波通信".Split(new char[]
						{
							','
						});
						int index = this.GetIndex(pText, array);
						this.ItemAdd("第" + (i + 1).ToString() + "块表通信协议类型", array[index]);
						this.ItemAdd("第" + (i + 1).ToString() + "块表通信地址", this.OperaRec(Value.Substring(num, 12), "BCD"));
						num += 12;
						this.ItemAdd("第" + (i + 1).ToString() + "块表通信密码", this.OperaRec(Value.Substring(num, 12), "BCD"));
						num += 12;
						this.ItemAdd("第" + (i + 1).ToString() + "块表电能费率个数", this.OperaRec(Value.Substring(num, 2), "BIN"));
						num += 2;
						num3 = DataConvert.HexToInt(Value.Substring(num, 2));
						num += 2;
						this.ItemAdd("第" + (i + 1).ToString() + "块表有功电能示值的整数位个数", "4位,5位,6位,7位".Split(new char[]
						{
							','
						})[num3 >> 2]);
						this.ItemAdd("第" + (i + 1).ToString() + "块表有功电能示值的小数位个数", "1位,2位,3位,4位".Split(new char[]
						{
							','
						})[num3 & 3]);
						this.ItemAdd("第" + (i + 1).ToString() + "块表所属采集器通信地址", this.OperaRec(Value.Substring(num, 12), "BCD"));
						num += 12;
						num3 = DataConvert.HexToInt(Value.Substring(num, 2));
						num += 2;
						this.ItemAdd("第" + (i + 1).ToString() + "块表用户大类号", (num3 >> 4).ToString());
						this.ItemAdd("第" + (i + 1).ToString() + "块表用户小类号", (num3 & 15).ToString());
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F11(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("本次脉冲配置路数", num2.ToString());
					num += 2;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("第" + (i + 1).ToString() + "路脉冲输入端口号", this.OperaRec(Value.Substring(num, 2), "BIN"));
						num += 2;
						this.ItemAdd("第" + (i + 1).ToString() + "路所属测量点号", this.OperaRec(Value.Substring(num, 2), "BIN"));
						num += 2;
						int num3 = DataConvert.HexToInt(Value.Substring(num, 2));
						this.ItemAdd("第" + (i + 1).ToString() + "路脉冲属性", "正向有功,正向无功,反向有功,反向无功".Split(new char[]
						{
							','
						})[num3 & 3]);
						num += 2;
						this.ItemAdd("第" + (i + 1).ToString() + "路电表常数", this.OperaRec(Value.Substring(num, 4), "BIN"));
						num += 4;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F12(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					string empty = string.Empty;
					int num = 0;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					for (int i = 0; i < 8; i++)
					{
						this.ItemAdd("状态量接入第" + (i + 1).ToString() + "路", ((num2 >> i & 1) == 1) ? "接入" : "未接入");
					}
					num += 2;
					empty = string.Empty;
					num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					for (int i = 0; i < 8; i++)
					{
						this.ItemAdd("状态量属性第" + (i + 1).ToString() + "路触点", ((num2 >> i & 1) == 1) ? "常开" : "常闭");
					}
					num += 2;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F13(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("模拟量配置路数", num2.ToString());
					num += 2;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("第" + (i + 1).ToString() + "路输入端口号", this.OperaRec(Value.Substring(num, 2), "BIN"));
						num += 2;
						this.ItemAdd("第" + (i + 1).ToString() + "路所属测量点号", this.OperaRec(Value.Substring(num, 2), "BIN"));
						num += 2;
						int num3 = DataConvert.HexToInt(Value.Substring(num, 2));
						num += 2;
						switch (num3 & 31)
						{
						case 0:
							this.ItemAdd("第" + (i + 1).ToString() + "路模拟量属性", "A相电压");
							break;

						case 1:
							this.ItemAdd("第" + (i + 1).ToString() + "路模拟量属性", "B相电压");
							break;

						case 2:
							this.ItemAdd("第" + (i + 1).ToString() + "路模拟量属性", "C相电压");
							break;

						case 3:
							this.ItemAdd("第" + (i + 1).ToString() + "路模拟量属性", "A相电流");
							break;

						case 4:
							this.ItemAdd("第" + (i + 1).ToString() + "路模拟量属性", "B相电流");
							break;

						case 5:
							this.ItemAdd("第" + (i + 1).ToString() + "路模拟量属性", "C相电流");
							break;

						default:
							this.ItemAdd("第" + (i + 1).ToString() + "路模拟量属性", "无效");
							break;
						}
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F14(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("本次总加组配置数量", num2.ToString());
					num += 2;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("第" + (i + 1).ToString() + "总加组序号", this.OperaRec(Value.Substring(num, 2), "BIN"));
						num += 2;
						int num3 = DataConvert.HexToInt(Value.Substring(num, 2));
						this.ItemAdd("第" + (i + 1).ToString() + "总加组测量点数量", num3.ToString());
						num += 2;
						for (int j = 0; j < num3; j++)
						{
							int num4 = DataConvert.HexToInt(Value.Substring(num, 2));
							this.ItemAdd(string.Concat(new string[]
							{
								"第",
								(i + 1).ToString(),
								"总加组第",
								(j + 1).ToString(),
								"测量点号"
							}), (num4 & 63).ToString());
							this.ItemAdd(string.Concat(new string[]
							{
								"第",
								(i + 1).ToString(),
								"总加组第",
								(j + 1).ToString(),
								"总加标志"
							}), (((num4 >> 6 & 1) == 1) ? "反向," : "正向,") + (((num4 >> 7 & 1) == 1) ? "减运算," : "加运算,"));
							num += 2;
						}
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F15(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("本次有功总电能量差动组配置数量", num2.ToString());
					num += 2;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("第" + (i + 1).ToString() + "组有功总电能量差动组序号", this.OperaRec(Value.Substring(num, 2), "BIN"));
						num += 2;
						this.ItemAdd("第" + (i + 1).ToString() + "组对比的总加组序号", this.OperaRec(Value.Substring(num, 2), "BIN"));
						num += 2;
						this.ItemAdd("第" + (i + 1).ToString() + "组参照的总加组序号", this.OperaRec(Value.Substring(num, 2), "BIN"));
						num += 2;
						int num3 = DataConvert.HexToInt(Value.Substring(num, 2));
						num += 2;
						this.ItemAdd("第" + (i + 1).ToString() + "组参与差动的电能量的时间区间", "60分钟电量,30分钟电量,15分钟电量,无效".Split(new char[]
						{
							','
						})[num3 & 3]);
						this.ItemAdd("第" + (i + 1).ToString() + "组参与差动的电能量的对比方法标志", (num3 >> 6 == 1) ? "绝对对比" : "相对对比");
						this.ItemAdd("第" + (i + 1).ToString() + "组差动越限相对偏差值", this.OperaRec(Value.Substring(num, 2), "BIN"));
						num += 2;
						this.ItemAdd("第" + (i + 1).ToString() + "组差动越限相对偏差值", this.OperaRec(Value.Substring(num, 8), "A3", "kWh"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F16(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("虚拟专网用户名", this.OperaRec(Value.Substring(num, 64), "ASCII"));
					num += 64;
					this.ItemAdd("虚拟专网密码", this.OperaRec(Value.Substring(num, 64), "ASCII"));
					num += 64;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F17(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("保安定值", this.OperaRec(Value, "A2"));
					num += Value.Length;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F18(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					string[] array = this.TimePeriods.Split(new char[]
					{
						'~'
					});
					int num = 0;
					string text = string.Empty;
					for (int i = 0; i < 12; i++)
					{
						text += this.OperaRec(Value.Substring(num, 2), "BS");
						num += 2;
					}
					string text2 = DataConvert.ReverseStr(text, 1);
					for (int i = 0; i < 32; i += 2)
					{
						this.ItemAdd("终端功控时段:" + array[array.Length - i - 1], this.ZTChose(text2.Substring(i, 2)));
					}
					result = num;
				}
				return result;
			}
		}
		private string ZTChose(string Value)
		{
			int num = 0;
			int num2 = int.Parse(Value);
			string result = string.Empty;
			switch (num2)
			{
			case 0:
				result = "不控制";
				break;

			case 1:
				result = "控制1";
				break;

			case 2:
				result = "控制2";
				break;

			case 3:
				result = "保留";
				break;
			}
			checked
			{
				num += Value.Length;
				return result;
			}
		}
		private int AF0A_F19(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("时段功控定值浮动系数", this.OperaRec(Value, "A4"));
					num += Value.Length;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F20(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月电能量控定值浮动系数", this.OperaRec(Value, "A4"));
					num += Value.Length;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F21(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					string[] array = this.TimePeriods.Split(new char[]
					{
						'~'
					});
					int num = 0;
					for (int i = 0; i < 48; i++)
					{
						this.ItemAdd(array[i] + "时段费率号", DataConvert.HexToInt(Value.Substring(num, 2)).ToString());
						num += 2;
					}
					this.ItemAdd("费率数", DataConvert.HexToInt(Value.Substring(num, 2)).ToString());
					num += 2;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F22(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = DataConvert.HexToInt(Value.Substring(0, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("第" + (i + 1).ToString() + "费率", this.OperaRec(Value.Substring(num, 8), "A3", "厘/元"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F23(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					string[] array = this.TimePeriods2.Split(new char[]
					{
						'~'
					});
					long num2 = DataConvert.HexToLong(DataConvert.ReverseStr(Value));
					for (int i = 0; i < array.Length; i++)
					{
						this.ItemAdd(array[i], ((num2 >> i & 1L) == 1L) ? "告警" : "不告警");
					}
					num += Value.Length;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F25(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("电压互感器倍率", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("电流互感器倍率", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("额定电压", this.OperaRec(Value.Substring(num, 4), "A7"));
					num += 4;
					this.ItemAdd("额定电流", this.OperaRec(Value.Substring(num, 2), "A22"));
					num += 2;
					this.ItemAdd("额定负荷", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					num += 2;
					string text = string.Empty;
					switch (num2 & 3)
					{
					case 1:
						text += "三相三线,";
						break;

					case 2:
						text += "三相四线,";
						break;

					case 3:
						text += "单相表,";
						break;

					default:
						text += "备用,";
						break;
					}
					switch (num2 >> 2 & 3)
					{
					case 1:
						text += "单相表接线相:A相,";
						break;

					case 2:
						text += "单相表接线相:B相,";
						break;

					case 3:
						text += "单相表接线相:C相,";
						break;

					default:
						text += "单相表接线相:不确定,";
						break;
					}
					this.ItemAdd("电源接线方式", text);
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F26(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("电压合格率判别参数电压合格上限", this.OperaRec(Value.Substring(num, 4), "A7"));
					num += 4;
					this.ItemAdd("电压合格率判别参数电压合格下限", this.OperaRec(Value.Substring(num, 4), "A7"));
					num += 4;
					this.ItemAdd("电压合格率判别参数电压断相门限", this.OperaRec(Value.Substring(num, 4), "A7"));
					num += 4;
					this.ItemAdd("过压判别参数电压上上限", this.OperaRec(Value.Substring(num, 4), "A7"));
					num += 4;
					this.ItemAdd("过压判别参数越限持续时间", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					this.ItemAdd("过压判别参数越限恢复系数", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("欠压判别参数电压下下限", this.OperaRec(Value.Substring(num, 4), "A7"));
					num += 4;
					this.ItemAdd("欠压判别参数越限持续时间", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					this.ItemAdd("欠压判别参数越限恢复系数", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("过流判别参数相电流上上限", this.OperaRec(Value.Substring(num, 6), "A25"));
					num += 6;
					this.ItemAdd("过流判别参数越限持续时间", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					this.ItemAdd("过流判别参数越限恢复系数", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("超额定电流判别参数相电流上限", this.OperaRec(Value.Substring(num, 6), "A25"));
					num += 6;
					this.ItemAdd("超额定电流判别参数越限持续时间", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					this.ItemAdd("超额定电流判别参数越限恢复系数", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("零序电流超限判别零序电流上限", this.OperaRec(Value.Substring(num, 6), "A25"));
					num += 6;
					this.ItemAdd("零序电流超限判别越限持续时间", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					this.ItemAdd("零序电流超限判别越限恢复系数", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("视在功率超上上限判别参数视在功率上上限", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("视在功率超上上限判别参数越限持续时间", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					this.ItemAdd("视在功率超上上限判别参数越限恢复系数", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("视在功率超上限判别参数视在功率上限", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("视在功率超上限判别参数越限持续时间", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					this.ItemAdd("视在功率超上限判别参数越限恢复系数", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("三相电压不平衡超限判别参数三相电压不平衡限值", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("三相电压不平衡超限判别参数越限持续时间", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					this.ItemAdd("三相电压不平衡超限判别参数越限恢复系数", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("三相电流不平衡超限判别参数三相电流不平衡限值", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("三相电流不平衡超限判别参数越限持续时间", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					this.ItemAdd("三相电流不平衡超限判别参数越限恢复系数", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("连续失压时间限值", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F27(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("A相电阻RA", this.OperaRec(Value.Substring(num, 4), "A26"));
					num += 4;
					this.ItemAdd("A相电抗XA", this.OperaRec(Value.Substring(num, 4), "A26"));
					num += 4;
					this.ItemAdd("A相电导GA", this.OperaRec(Value.Substring(num, 4), "A26"));
					num += 4;
					this.ItemAdd("A相电纳BA", this.OperaRec(Value.Substring(num, 4), "A26"));
					num += 4;
					this.ItemAdd("B相电阻RB", this.OperaRec(Value.Substring(num, 4), "A26"));
					num += 4;
					this.ItemAdd("B相电抗XB", this.OperaRec(Value.Substring(num, 4), "A26"));
					num += 4;
					this.ItemAdd("B相电导GB", this.OperaRec(Value.Substring(num, 4), "A26"));
					num += 4;
					this.ItemAdd("B相电纳BB", this.OperaRec(Value.Substring(num, 4), "A26"));
					num += 4;
					this.ItemAdd("C相电阻RC", this.OperaRec(Value.Substring(num, 4), "A26"));
					num += 4;
					this.ItemAdd("C相电抗XC", this.OperaRec(Value.Substring(num, 4), "A26"));
					num += 4;
					this.ItemAdd("C相电导GC", this.OperaRec(Value.Substring(num, 4), "A26"));
					num += 4;
					this.ItemAdd("C相电纳BC", this.OperaRec(Value.Substring(num, 4), "A26"));
					num += 4;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F28(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("功率因数分段限值1", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("功率因数分段限值2", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F29(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端当地电能表显示号", this.OperaRec(Value.Substring(num), "ASCII"));
					num += Value.Length;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F30(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("台区集中抄表停抄/投抄设置", (DataConvert.HexToInt(Value.Substring(num, 2)) == 1) ? "停抄" : "投抄");
					num += Value.Length;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F31(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("本次设置的载波从节点附属节点地址个数", num2.ToString());
					num += 2;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("第" + (i + 1).ToString() + "个载波从节点附属节点地址", this.OperaRec(Value.Substring(num, 12), "A12"));
						num += 12;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F33(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("本次设置的参数块个数", num2.ToString());
					num += 2;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("第" + (i + 1).ToString() + "个参数块.终端通信端口号", this.OperaRec(Value.Substring(num, 2), "BIN"));
						num += 2;
						string text = string.Empty;
						long num3 = DataConvert.HexToLong(DataConvert.ReverseStr(Value.Substring(num, 4)));
						num += 4;
						text += (((num3 & 1L) == 1L) ? "不允许自动抄表," : "要求终端根据抄表时段自动抄表,");
						text += (((num3 >> 1 & 1L) == 1L) ? "终端只抄重点表," : "终端抄所有表,");
						text += (((num3 >> 2 & 1L) == 1L) ? "终端采用广播冻结抄表," : "不要求广播冻结抄表,");
						text += (((num3 >> 3 & 1L) == 1L) ? "定时对电表广播校时," : "不要求定时对电表广播校时,");
						text += (((num3 >> 4 & 1L) == 1L) ? "搜寻新增或更换的电表," : "不要求搜寻新增或更换的电表,");
						text += (((num3 >> 5 & 1L) == 1L) ? "抄读电表状态字," : "不要求抄读电表状态字,");
						text += (((num3 >> 6 & 1L) == 1L) ? "集中器每次启动抄表前发送<数据区初始化(节点侦听信息)>命令,master收到后将路由清除," : "正常抄表,");
						text += (((num3 >> 7 & 1L) == 1L) ? "抄购电信息," : "不抄购电信息,");
						text += (((num3 >> 8 & 7L) == 0L) ? "不重抄," : ("重抄" + (num3 >> 8 & 7L).ToString() + "轮,"));
						text = text + "自动启动一次抄所有表最长持续时间" + ((num3 >> 11 & 3L) + 1L).ToString() + "小时,";
						text = text + "抄表间隔" + "1,2,4,8,12,24".Split(new char[]
						{
							','
						})[(int)((IntPtr)(num3 >> 13 & 7L))] + "小时,";
						this.ItemAdd("第" + (i + 1).ToString() + "个参数块.台区集中抄表运行控制字", text);
						text = string.Empty;
						num3 = DataConvert.HexToLong(DataConvert.ReverseStr(Value.Substring(num, 8)));
						num += 8;
						int j;
						for (j = 0; j < 30; j++)
						{
							text += (((num3 >> j & 1L) == 1L) ? ((j + 1).ToString() + "日,") : "");
						}
						this.ItemAdd("第" + (i + 1).ToString() + "个参数块.抄表日(日期)", text);
						this.ItemAdd("第" + (i + 1).ToString() + "个参数块.抄表日(时间)", this.OperaRec(Value.Substring(num, 4), "A19"));
						num += 4;
						this.ItemAdd("第" + (i + 1).ToString() + "个参数块.抄表间隔时间", this.OperaRec(Value.Substring(num, 2), "BIN"));
						num += 2;
						this.ItemAdd("第" + (i + 1).ToString() + "个参数块.对电表广播校时定时时间", this.OperaRec(Value.Substring(num, 6), "A18"));
						num += 6;
						num3 = DataConvert.HexToLong(DataConvert.ReverseStr(Value.Substring(num, 2)));
						num += 2;
						this.ItemAdd("第" + (i + 1).ToString() + "个参数块.允许抄表时段数", num3.ToString());
						j = 0;
						while (unchecked((long)j) < num3)
						{
							this.ItemAdd(string.Concat(new string[]
							{
								"第",
								(i + 1).ToString(),
								"个参数块.第",
								(j + 1).ToString(),
								"个允许抄表时段开始时间"
							}), this.OperaRec(Value.Substring(num, 4), "A19"));
							num += 4;
							this.ItemAdd(string.Concat(new string[]
							{
								"第",
								(i + 1).ToString(),
								"个参数块.第",
								(j + 1).ToString(),
								"个允许抄表时段结束时间"
							}), this.OperaRec(Value.Substring(num, 4), "A19"));
							num += 4;
							j++;
						}
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F34(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("本次设置的参数块个数", num2.ToString());
					num += 2;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("本次设置的第" + (i + 1).ToString() + "个参数块终端通信端口号", this.OperaRec(Value.Substring(num, 2), "BIN"));
						num += 2;
						this.ItemAdd("本次设置的第" + (i + 1).ToString() + "个参数块与终端接口端的通信控制字", this.OperaRec(Value.Substring(num, 2), "BIN"));
						num += 2;
						this.ItemAdd("本次设置的第" + (i + 1).ToString() + "个参数块与终端接口对应端的通信速率", this.OperaRec(Value.Substring(num, 8), "BIN"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F35(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = DataConvert.HexToInt(Value.Substring(0, 2));
					this.ItemAdd("台区集中抄表重点户个数", num.ToString());
					int num2 = 2;
					for (int i = 0; i < num; i++)
					{
						this.ItemAdd("第" + (i + 1).ToString() + "个重点户的电能表/交流采样装置序号", this.OperaRec(Value.Substring(num2, 4), "BIN"));
						num2 += 4;
					}
					result = num2;
				}
				return result;
			}
		}
		private int AF0A_F36(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月通信流量门限", this.OperaRec(Value.Substring(num), "BIN"));
					num += Value.Length;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F37(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端级联通信端口号", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					string text = string.Empty;
					text = text + "300,600,1200,2400,4800,7200,9600,19200".Split(new char[]
					{
						','
					})[num2 >> 5] + ",";
					text = text + ((num2 >> 4 & 1) + 1).ToString() + "停止位,";
					text += (((num2 >> 3 & 1) == 0) ? "无校验," : "有校验,");
					text += (((num2 >> 2 & 1) == 0) ? "偶校验," : "奇校验,");
					text = text + "5位数,6位数,7位数,8位数".Split(new char[]
					{
						','
					})[num2 & 3] + ",";
					this.ItemAdd("终端级联通信控制字", text);
					num += 2;
					this.ItemAdd("接收等待报文超时时间", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					this.ItemAdd("接收等待字节超时时间", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					this.ItemAdd("级联方(主动站)接收失败重发次数", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					this.ItemAdd("级联巡测周期", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					int num3 = DataConvert.HexToInt(Value.Substring(num, 2));
					num2 = (num3 & 7);
					num += 2;
					this.ItemAdd("级联/被级联标志", (num3 >> 6 == 1) ? "被级联方," : "级联方,");
					this.ItemAdd("级联/被级联对应的被级联/级联的终端个数n", "终端个数:" + num2.ToString());
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("第" + (i + 1).ToString() + "个.[被级联/级联方]行政区划码", this.OperaRec(Value.Substring(num, 4), "BCD"));
						num += 4;
						this.ItemAdd("第" + (i + 1).ToString() + "个.[被级联/级联方]终端地址", this.OperaRec(Value.Substring(num, 4), "BIN"));
						num += 4;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F38(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("本次设置所对应的用户大类号", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("本次设置的组数", num2.ToString());
					num += 2;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("第" + (i + 1).ToString() + "组.用户小类号", this.OperaRec(Value.Substring(num, 2), "BIN"));
						num += 2;
						int num3 = DataConvert.HexToInt(Value.Substring(num, 2));
						this.ItemAdd("第" + (i + 1).ToString() + "组.信息类组数", num3.ToString());
						num += 2;
						for (int j = 0; j < num3; j++)
						{
							int num4 = DataConvert.HexToInt(Value.Substring(num, 2));
							num += 2;
							string text = string.Empty;
							for (int k = 0; k < 8; k++)
							{
								if ((num4 >> k & 1) == 1)
								{
									text = text + "F" + (8 * j + 1 + k).ToString() + ",";
								}
							}
							this.ItemAdd(string.Concat(new object[]
							{
								"第",
								(i + 1).ToString(),
								"组.第",
								j + 1,
								"个信息类组所对应的信息类元标志位"
							}), text);
						}
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F41(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					num += 2;
					string text = string.Empty;
					text += (((num2 & 1) == 1) ? "第1套功率定值方案," : "");
					text += (((num2 & 2) >> 1 == 1) ? "第2套功率定值方案," : "");
					text += (((num2 & 4) >> 2 == 1) ? "第3套功率定值方案," : "");
					this.ItemAdd("方案标志", text);
					for (int i = 0; i < 3; i++)
					{
						num2 = DataConvert.HexToInt(Value.Substring(num, 2));
						num += 2;
						for (int j = 0; j < num2; j++)
						{
							if ((num2 >> j & 1) == 1)
							{
								this.ItemAdd(string.Concat(new string[]
								{
									"第",
									(i + 1).ToString(),
									"套.定值时段",
									(j + 1).ToString(),
									"功控定值"
								}), this.OperaRec(Value.Substring(num, 4), "A2"));
								num += 4;
							}
						}
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F42(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("厂休控定值", this.OperaRec(Value.Substring(num, 4), "A2"));
					num += 4;
					this.ItemAdd("限电起始时间", this.OperaRec(Value.Substring(num, 4), "A19"));
					num += 4;
					this.ItemAdd("限电延续时间", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					num += 2;
					string values = string.Empty;
					for (int i = 1; i < 8; i++)
					{
						if ((num2 >> i & 1) == 1)
						{
							values = "星期一,星期二,星期三,星期四,星期五,星期六,星期日".Split(new char[]
							{
								','
							})[i - 1];
						}
					}
					this.ItemAdd("每周限电日", values);
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F43(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("功率控制的功率计算滑差时间", this.OperaRec(Value.Substring(0, 2), "BIN"));
					num += 2;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F44(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("报停起始时间", this.OperaRec(Value.Substring(num, 6), "A20"));
					num += 6;
					this.ItemAdd("报停结束时间", this.OperaRec(Value.Substring(num, 6), "A20"));
					num += 6;
					this.ItemAdd("报停控功率定值", this.OperaRec(Value.Substring(num, 4), "A2"));
					num += 4;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F45(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					num += 2;
					for (int i = 0; i < 8; i++)
					{
						this.ItemAdd("第" + (i + 1).ToString() + "轮次开关", ((num2 >> i & 1) == 1) ? "受控" : "不受控");
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F46(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月电量控定值", this.OperaRec(Value, "A3", "kWh/MWh"));
					num += Value.Length;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F47(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("购电单号", this.OperaRec(Value.Substring(num, 8), "BIN"));
					num += 8;
					this.ItemAdd("追加/刷新标志", (Value.Substring(num, 2) == "55") ? "追加" : "刷新");
					num += 2;
					this.ItemAdd("购电量(费)值", this.OperaRec(Value.Substring(num, 8), "A3", "kWh/厘"));
					num += 8;
					this.ItemAdd("报警门限值", this.OperaRec(Value.Substring(num, 8), "A3", "kWh/厘"));
					num += 8;
					this.ItemAdd("跳闸门限值", this.OperaRec(Value.Substring(num, 8), "A3", "kWh/厘"));
					num += 8;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F48(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					num += 2;
					for (int i = 0; i < 8; i++)
					{
						this.ItemAdd("第" + (i + 1).ToString() + "轮次开关", ((num2 >> i & 1) == 1) ? "受控" : "不受控");
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F49(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("功控告警时间", this.OperaRec(Value, "BIN"));
					num += Value.Length;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F57(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					string[] array = this.TimePeriods2.Split(new char[]
					{
						'~'
					});
					long num2 = DataConvert.HexToLong(DataConvert.ReverseStr(Value));
					for (int i = 0; i < array.Length; i++)
					{
						this.ItemAdd(array[i], ((num2 >> i & 1L) == 1L) ? "允许告警" : "不允许告警");
					}
					num += Value.Length;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F58(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("允许与主站连续无通信时间", this.OperaRec(Value, "BIN"));
					num += Value.Length;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F59(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("电能量超差阈值", this.OperaRec(Value.Substring(num, 2), "A22"));
					num += 2;
					this.ItemAdd("电能表飞走阈值", this.OperaRec(Value.Substring(num, 2), "A22"));
					num += 2;
					this.ItemAdd("电能表停走阈值", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					this.ItemAdd("电能表校时阈值", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F60(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("总畸变电压含有率上限", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("奇次谐波电压含有率上限", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("偶次谐波电压含有率上限", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					for (int i = 2; i <= 18; i += 2)
					{
						this.ItemAdd(i.ToString() + "次谐波电压含有率上限", this.OperaRec(Value.Substring(num, 4), "A5"));
						num += 4;
					}
					for (int i = 3; i <= 19; i += 2)
					{
						this.ItemAdd(i.ToString() + "次谐波电压含有率上限", this.OperaRec(Value.Substring(num, 4), "A5"));
						num += 4;
					}
					this.ItemAdd("总畸变电流有效值上限", this.OperaRec(Value.Substring(num, 4), "A6"));
					num += 4;
					for (int i = 2; i <= 18; i += 2)
					{
						this.ItemAdd(i.ToString() + "次谐波电压含有率上限", this.OperaRec(Value.Substring(num, 4), "A6"));
						num += 4;
					}
					for (int i = 3; i <= 19; i += 2)
					{
						this.ItemAdd(i.ToString() + "次谐波电压含有率上限", this.OperaRec(Value.Substring(num, 4), "A6"));
						num += 4;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F61(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					num += 2;
					for (int i = 0; i < 8; i++)
					{
						this.ItemAdd("第" + (i + 1).ToString() + "路", ((num2 >> i & 1) == 1) ? "接入" : "未接入");
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F65(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					num += 2;
					this.ItemAdd("定时上报周期单位", "分,时,日,月".Split(new char[]
					{
						','
					})[num2 >> 6]);
					this.ItemAdd("定时上报周期", (num2 & 63).ToString());
					this.ItemAdd("上报基准时间", this.OperaRec(Value.Substring(num, 12), "A1"));
					num += 12;
					this.ItemAdd("曲线数据抽取倍率", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("数据单元标识个数", num2.ToString());
					num += 2;
					for (int i = 0; i < num2; i++)
					{
						string empty = string.Empty;
						string empty2 = string.Empty;
						this.gDLT698.GetDataCellMark(Value.Substring(num, 8), ref empty, ref empty2);
						num += 8;
						this.ItemAdd("数据单元标识" + (i + 1).ToString(), "FN=" + empty + ",PN=" + empty2);
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F67(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					string text = Value.ToUpper();
					if (text != null)
					{
						if (text == "55")
						{
							this.ItemAdd("启动/停止标志", "启动");
							goto IL_73;
						}
						if (text == "AA")
						{
							this.ItemAdd("启动/停止标志", "停止");
							goto IL_73;
						}
					}
					this.ItemAdd("启动/停止标志", "无效");
					IL_73:
					num += Value.Length;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F73(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					for (int i = 0; i < 16; i++)
					{
						int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
						num += 2;
						string text = (num2 >> 6 == 1) ? "共补" : "分补";
						text += (((num2 & 1) == 1) ? "A相" : "");
						text += (((num2 & 2) >> 1 == 1) ? "B相" : "");
						text += (((num2 & 4) >> 2 == 1) ? "C相" : "");
						this.ItemAdd("补偿方式" + (i + 1).ToString(), text);
						this.ItemAdd("电容装见容量", Value.Substring(num, 4));
						num += 4;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F74(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("目标功率因数", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("投入无功功率门限", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 4;
					this.ItemAdd("切除无功功率门限", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("延时时间", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					this.ItemAdd("动作时间间隔", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F75(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("过电压", this.OperaRec(Value.Substring(num, 4), "A7"));
					num += 4;
					this.ItemAdd("过电压回差值", this.OperaRec(Value.Substring(num, 4), "A7"));
					num += 4;
					this.ItemAdd("欠电压", this.OperaRec(Value.Substring(num, 4), "A7"));
					num += 4;
					this.ItemAdd("欠电压回差值", this.OperaRec(Value.Substring(num, 4), "A7"));
					num += 4;
					this.ItemAdd("总畸变电流含有率上限", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("总畸变电流含有率越限回差值", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("总畸变电压含有率上限", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("总畸变电压含有率越限回差值", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F76(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					num += 2;
					switch (num2)
					{
					case 0:
						this.ItemAdd("控制方式", "当地控制");
						break;

					case 1:
						this.ItemAdd("控制方式", "远方遥控");
						break;

					case 2:
						this.ItemAdd("控制方式", "闭锁");
						break;

					case 3:
						this.ItemAdd("控制方式", "解锁");
						break;

					default:
						this.ItemAdd("控制方式", "备用值:" + Value);
						break;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F81(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("直流模拟量量程起始值", this.OperaRec(Value.Substring(num, 4), "A2"));
					num += 4;
					this.ItemAdd("直流模拟量量程终止值", this.OperaRec(Value.Substring(num, 4), "A2"));
					num += 4;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F82(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("直流模拟量上限", this.OperaRec(Value.Substring(num, 4), "A2"));
					num += 4;
					this.ItemAdd("直流模拟量下限", this.OperaRec(Value.Substring(num, 4), "A2"));
					num += 4;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F83(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("直流模拟量冻结密度", this.C1(this.OperaRec(Value, "BCD"), ref num2));
					num += Value.Length;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F85(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("行政区划码(A1)", this.OperaRec(Value.Substring(num, 4), "BCD"));
					num += 4;
					this.ItemAdd("终端地址(A2)", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					result = num;
				}
				return result;
			}
		}
		private int AF0A_F89(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("无线信道号", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					int num2 = int.Parse(this.OperaRec(Value.Substring(num, 2), "BIN"));
					string text = "最大发射功率,等级1发射功率,等级2发射功率,等级3发射功率,等级4发射功率,等级5发射功率,等级6发射功率,最小发射功率";
					this.ItemAdd("主无线模块发射功率", text.Split(new char[]
					{
						','
					})[num2]);
					num += 2;
					int num3 = int.Parse(this.OperaRec(Value.Substring(num, 2), "BIN"));
					string text2 = ",1200,2400,4800,7200,9600,19200,38400";
					this.ItemAdd("无线空中波特率", text2.Split(new char[]
					{
						','
					})[num3]);
					num += 2;
					this.ItemAdd("无线网络标识", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("路由方式", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					this.ItemAdd("保留", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					result = num;
				}
				return result;
			}
		}
		private int AF0B_F2(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("请求的任务中的数据的起始时间", this.OperaRec(Value, "A15"));
					num += Value.Length;
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F2(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端日历时钟", this.OperaRec(Value, "A1"));
					num += Value.Length;
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F3(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					string text = this.OperaRec(Value, "BS");
					num += Value.Length;
					string text2 = string.Empty;
					for (int i = 0; i < 248; i++)
					{
						if (int.Parse(text.Substring(i, 1)) == 1)
						{
							text2 = text2 + "\r\nF" + (i + 1).ToString() + ",";
						}
					}
					if (string.IsNullOrEmpty(text2))
					{
						text2 = this.OperaRec(Value, "BS");
					}
					this.ItemAdd("终端参数状态", text2);
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F4(string Value)
		{
			int result;
			if (!string.IsNullOrEmpty(Value))
			{
				int num = 0;
				long num2 = DataConvert.HexToLong(DataConvert.ReverseStr(Value));
				string text;
				long num3;
				checked
				{
					num += Value.Length;
					text = string.Empty;
					num3 = (num2 >> 2 & 3L);
				}
				if (num3 <= 3L)
				{
					if (num3 >= 0L)
					{
						switch ((int)num3)
						{
						case 0:
						case 3:
							text += "终端主动上报无效,";
							break;

						case 1:
							text += "禁止终端主动上报,";
							break;

						case 2:
							text += "允许终端主动上报,";
							break;
						}
					}
				}
				num3 = (num2 & 3L);
				if (num3 <= 3L)
				{
					if (num3 >= 0L)
					{
						switch ((int)num3)
						{
						case 0:
						case 3:
							text += "终端通话无效,";
							break;

						case 1:
							text += "禁止终端通话,";
							break;

						case 2:
							text += "允许终端通话,";
							break;
						}
					}
				}
				
				this.ItemAdd("终端上行通信状态", text);
				result = num;
				return result;
				
			}
			result = 0;
			return result;
		}
		private int AF0C_F5(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					num += 2;
					string text = string.Empty;
					text += (((num2 & 1) == 1) ? "保电状态投入," : "保电状态解除,");
					text += (((num2 >> 1 & 1) == 1) ? "剔除状态投入," : "剔除状态解除,");
					text += (((num2 >> 2 & 1) == 1) ? "催费告警状态投入," : "催费告警状态解除,");
					this.ItemAdd("保电、剔除和催费告警投入状态", text);
					this.ItemAdd("总加组有效标志位D0-D7", this.OperaRec(Value.Substring(num, 2), "BS"));
					num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					num += 2;
					for (int i = 0; i < 8; i++)
					{
						if ((num2 >> i & 1) == 1)
						{
							this.ItemAdd("总加组" + (i + 1).ToString() + ".功控定值方案号", this.OperaRec(Value.Substring(num, 2), "BIN"));
							num += 2;
							int num3 = DataConvert.HexToInt(Value.Substring(num, 2));
							num += 2;
							string text2 = string.Empty;
							for (int j = 0; j < 8; j++)
							{
								if ((num3 >> j & 1) == 1)
								{
									text2 = text2 + (j + 1).ToString() + "时段控投入,";
								}
							}
							this.ItemAdd("总加组" + (i + 1).ToString() + ".功控时段有效标志位", text2);
							int num4 = DataConvert.HexToInt(Value.Substring(num, 2));
							string text3 = ((num4 & 1) == 1) ? "时段控," : "";
							text3 += (((num4 >> 1 & 1) == 1) ? "厂休控," : "");
							text3 += (((num4 >> 2 & 1) == 1) ? "营业报停控," : "");
							text3 += (((num4 >> 3 & 1) == 1) ? "当前功率下浮控," : "");
							this.ItemAdd("总加组" + (i + 1).ToString() + ".功控状态", text3);
							num += 2;
							int num5 = DataConvert.HexToInt(Value.Substring(num, 2));
							string text4 = ((num5 & 1) == 1) ? "月电控," : "";
							text4 += (((num5 >> 1 & 1) == 1) ? "购电控," : "");
							this.ItemAdd("总加组" + (i + 1).ToString() + ".电控状态", text4);
							num += 2;
							int num6 = DataConvert.HexToInt(Value.Substring(num, 2));
							this.ItemAdd("总加组" + (i + 1).ToString() + ".功控轮次状态", num6.ToString());
							num += 2;
							string empty = string.Empty;
							for (int j = 0; j < 8; j++)
							{
								this.ItemAdd(string.Concat(new string[]
								{
									"总加组",
									(i + 1).ToString(),
									".功控轮次第",
									(j + 1).ToString(),
									"轮次开关"
								}), ((num6 >> j & 1) == 1) ? "受控" : "不受控");
							}
							num6 = DataConvert.HexToInt(Value.Substring(num, 2));
							this.ItemAdd("总加组" + (i + 1).ToString() + ".电控轮次状态", num6.ToString());
							num += 2;
							for (int j = 0; j < 8; j++)
							{
								this.ItemAdd(string.Concat(new string[]
								{
									"总加组",
									(i + 1).ToString(),
									".电控轮次第",
									(j + 1).ToString(),
									"轮次开关"
								}), ((num6 >> j & 1) == 1) ? "受控" : "不受控");
							}
						}
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F6(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					num += 2;
					for (int i = 0; i < 8; i++)
					{
						this.ItemAdd("遥控跳闸输出第" + (i + 1).ToString() + "轮", ((num2 >> i & 1) == 1) ? "跳闸" : "合闸");
					}
					num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					num += 2;
					this.ItemAdd("当前催费告警状态", ((num2 & 1) == 1) ? "终端处于催费告警状态" : "终端未处于催费告警状态");
					num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("总加组有效标志位", num2.ToString());
					num += 2;
					for (int i = 0; i < 8; i++)
					{
						this.ItemAdd("总加组有效标志位第" + (i + 1).ToString() + "组", ((num2 >> i & 1) == 1) ? "有相应总加组的当前控制状态" : "无相应总加组的当前控制状态");
					}
					for (int j = 0; j < 8; j++)
					{
						if ((num2 >> j & 1) == 1)
						{
							this.ItemAdd("总加组" + (j + 1).ToString() + ".当前功控定值", this.OperaRec(Value.Substring(num, 4), "A2"));
							num += 4;
							this.ItemAdd("总加组" + (j + 1).ToString() + ".当前功率下浮控浮动系数", this.OperaRec(Value.Substring(num, 2), "A4"));
							num += 2;
							num2 = DataConvert.HexToInt(Value.Substring(num, 2));
							num += 2;
							for (int i = 0; i < 8; i++)
							{
								this.ItemAdd(string.Concat(new string[]
								{
									"总加组",
									(j + 1).ToString(),
									".功控跳闸输出第",
									(i + 1).ToString(),
									"轮"
								}), ((num2 >> i & 1) == 1) ? "跳闸" : "合闸");
							}
							num2 = DataConvert.HexToInt(Value.Substring(num, 2));
							num += 2;
							for (int i = 0; i < 8; i++)
							{
								this.ItemAdd(string.Concat(new string[]
								{
									"总加组",
									(j + 1).ToString(),
									".月电控跳闸输出第",
									(i + 1).ToString(),
									"轮"
								}), ((num2 >> i & 1) == 1) ? "跳闸" : "合闸");
							}
							num2 = DataConvert.HexToInt(Value.Substring(num, 2));
							num += 2;
							for (int i = 0; i < 8; i++)
							{
								this.ItemAdd(string.Concat(new string[]
								{
									"总加组",
									(j + 1).ToString(),
									".购电控跳闸输出第",
									(i + 1).ToString(),
									"轮"
								}), ((num2 >> i & 1) == 1) ? "跳闸" : "合闸");
							}
							int num3 = DataConvert.HexToInt(Value.Substring(num, 2));
							string text = ((num3 & 1) == 1) ? "时段控," : "";
							text += (((num3 >> 1 & 1) == 1) ? "厂休控," : "");
							text += (((num3 >> 2 & 1) == 1) ? "营业报停控," : "");
							text += (((num3 >> 3 & 1) == 1) ? "当前功率下浮控," : "");
							this.ItemAdd("总加组" + (j + 1).ToString() + ".功控越限告警状态", text);
							num += 2;
							int num4 = DataConvert.HexToInt(Value.Substring(num, 2));
							string text2 = ((num4 & 1) == 1) ? "月电控," : "";
							text2 += (((num4 >> 1 & 1) == 1) ? "购电控," : "");
							this.ItemAdd("总加组" + (j + 1).ToString() + ".电控越限告警状态", text2);
							num += 2;
						}
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F7(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					string[] array = this.ALLERC.Split(new char[]
					{
						'~'
					});
					int num = 0;
					this.ItemAdd("重要事件计数器EC1值", DataConvert.HexToInt(Value.Substring(num, 2)).ToString());
					num += 2;
					this.ItemAdd("一般事件计数器EC2值", DataConvert.HexToInt(Value.Substring(num, 2)).ToString());
					num += 2;
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F8(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					string[] array = this.ALLERC.Split(new char[]
					{
						'~'
					});
					int num = 0;
					string text = this.OperaRec(Value.Substring(num, 16), "BS");
					num += 16;
					string text2 = string.Empty;
					for (int i = 0; i < 64; i++)
					{
						if (text.Substring(i, 1) == "1")
						{
							text2 = text2 + "\r\n" + array[i] + ",";
						}
					}
					if (string.IsNullOrEmpty(text2))
					{
						text2 = Value;
					}
					this.ItemAdd("事件状态标志", text2);
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F9(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					num += 2;
					for (int i = 0; i < 8; i++)
					{
						this.ItemAdd("状态量的状态ST:" + (i + 1).ToString() + "路", ((num2 >> i & 1) == 1) ? "状态[合]" : "状态[分]");
					}
					num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					num += 2;
					for (int i = 0; i < 8; i++)
					{
						this.ItemAdd("状态量的变位CD:" + (i + 1).ToString() + "路", ((num2 >> i & 1) == 1) ? "变化[有]" : "变化[无]");
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F10(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端与主站当日通信流量", this.OperaRec(Value.Substring(num, 8), "BIN"));
					num += 8;
					this.ItemAdd("终端与主站当月通信流量", this.OperaRec(Value.Substring(num, 8), "BIN"));
					num += 8;
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F11(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("本项数据块个数", num2.ToString());
					num += 2;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("第" + (i + 1).ToString() + "个数据块.终端通信端口号", this.OperaRec(Value.Substring(num, 2), "BIN"));
						num += 2;
						this.ItemAdd("第" + (i + 1).ToString() + "个数据块.要抄电表总数", this.OperaRec(Value.Substring(num, 4), "BIN"));
						num += 4;
						int num3 = DataConvert.HexToInt(Value.Substring(num, 2));
						string text = ((num3 & 1) == 1) ? "抄表," : "未抄表,";
						text += (((num3 >> 1 & 1) == 1) ? "时段内完成," : "时段内未完成,");
						this.ItemAdd("第" + (i + 1).ToString() + "个数据块.当前抄表工作状态标志", text);
						num += 2;
						this.ItemAdd("第" + (i + 1).ToString() + "个数据块.抄表成功块数", this.OperaRec(Value.Substring(num, 4), "BIN"));
						num += 4;
						this.ItemAdd("第" + (i + 1).ToString() + "个数据块.抄重点表成功块数", this.OperaRec(Value.Substring(num, 2), "BIN"));
						num += 2;
						this.ItemAdd("第" + (i + 1).ToString() + "个数据块.抄表开始时间", this.OperaRec(Value.Substring(num, 12), "A1"));
						num += 12;
						this.ItemAdd("第" + (i + 1).ToString() + "个数据块.抄表结束时间", this.OperaRec(Value.Substring(num, 12), "A1"));
						num += 12;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F12(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("网络信号品质", this.OperaRec(Value, "A5"));
					num += Value.Length;
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F17(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("当前总加有功功率", this.OperaRec(Value, "A2"));
					num += Value.Length;
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F18(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("当前总加无功功率", this.OperaRec(Value, "A2"));
					num += Value.Length;
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F19(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					num += 2;
					this.ItemAdd("费率数", num2.ToString());
					this.ItemAdd("当日总加有功总电能量", this.OperaRec(Value.Substring(num, 8), "A3"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "当日总加有功电能量", this.OperaRec(Value.Substring(num, 8), "A3", "kWh"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F20(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					num += 2;
					this.ItemAdd("费率数", num2.ToString());
					this.ItemAdd("当日总加无功总电能量", this.OperaRec(Value.Substring(num, 8), "A3"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "当日总加无功电能量", this.OperaRec(Value.Substring(num, 8), "A3", "kvarh"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F21(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					num += 2;
					this.ItemAdd("费率数", num2.ToString());
					this.ItemAdd("当月总加有功总电能量", this.OperaRec(Value.Substring(num, 8), "A3"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "当月总加有功电能量", this.OperaRec(Value.Substring(num, 8), "A3", "kWh"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F22(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					num += 2;
					this.ItemAdd("费率数", num2.ToString());
					this.ItemAdd("当月总加无功总电能量", this.OperaRec(Value.Substring(2, 8), "A3"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "当月总加无功电能量", this.OperaRec(Value.Substring(num, 8), "A3", "kvarh"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F23(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("当前剩余电量(费)", this.OperaRec(Value, "A3", "kWh/厘"));
					num += Value.Length;
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F24(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("控后总加有功功率冻结值", this.OperaRec(Value, "A2"));
					num += Value.Length;
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F25(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					this.ItemAdd("当前总有功功率", this.OperaRec(Value.Substring(num, 6), "A9"));
					num += 6;
					this.ItemAdd("当前A相有功功率", this.OperaRec(Value.Substring(num, 6), "A9"));
					num += 6;
					this.ItemAdd("当前B相有功功率", this.OperaRec(Value.Substring(num, 6), "A9"));
					num += 6;
					this.ItemAdd("当前C相有功功率", this.OperaRec(Value.Substring(num, 6), "A9"));
					num += 6;
					this.ItemAdd("当前总无功功率", this.OperaRec(Value.Substring(num, 6), "A9"));
					num += 6;
					this.ItemAdd("当前A相无功功率", this.OperaRec(Value.Substring(num, 6), "A9"));
					num += 6;
					this.ItemAdd("当前B相无功功率", this.OperaRec(Value.Substring(num, 6), "A9"));
					num += 6;
					this.ItemAdd("当前C相无功功率", this.OperaRec(Value.Substring(num, 6), "A9"));
					num += 6;
					this.ItemAdd("当前总功率因数", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("当前A相功率因数", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("当前B相功率因数", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("当前C相功率因数", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("当前A相电压", this.OperaRec(Value.Substring(num, 4), "A7"));
					num += 4;
					this.ItemAdd("当前B相电压", this.OperaRec(Value.Substring(num, 4), "A7"));
					num += 4;
					this.ItemAdd("当前C相电压", this.OperaRec(Value.Substring(num, 4), "A7"));
					num += 4;
					this.ItemAdd("当前A相电流", this.OperaRec(Value.Substring(num, 6), "A25"));
					num += 6;
					this.ItemAdd("当前B相电流", this.OperaRec(Value.Substring(num, 6), "A25"));
					num += 6;
					this.ItemAdd("当前C相电流", this.OperaRec(Value.Substring(num, 6), "A25"));
					num += 6;
					this.ItemAdd("当前零序电流", this.OperaRec(Value.Substring(num, 6), "A25"));
					num += 6;
					this.ItemAdd("当前总视在功率", this.OperaRec(Value.Substring(num, 6), "A9"));
					num += 6;
					this.ItemAdd("当前A相视在功率", this.OperaRec(Value.Substring(num, 6), "A9"));
					num += 6;
					this.ItemAdd("当前B相视在功率", this.OperaRec(Value.Substring(num, 6), "A9"));
					num += 6;
					this.ItemAdd("当前C相视在功率", this.OperaRec(Value.Substring(num, 6), "A9"));
					num += 6;
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F26(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					this.ItemAdd("总断相次数", this.OperaRec(Value.Substring(num, 4), "A8"));
					num += 4;
					this.ItemAdd("A相断相次数", this.OperaRec(Value.Substring(num, 4), "A8"));
					num += 4;
					this.ItemAdd("B相断相次数", this.OperaRec(Value.Substring(num, 4), "A8"));
					num += 4;
					this.ItemAdd("C相断相次数", this.OperaRec(Value.Substring(num, 4), "A8"));
					num += 4;
					this.ItemAdd("断相时间累计值", this.OperaRec(Value.Substring(num, 6), "A10"));
					num += 6;
					this.ItemAdd("A相断相时间累计值", this.OperaRec(Value.Substring(num, 6), "A10"));
					num += 6;
					this.ItemAdd("B相断相时间累计值", this.OperaRec(Value.Substring(num, 6), "A10"));
					num += 6;
					this.ItemAdd("C相断相时间累计值", this.OperaRec(Value.Substring(num, 6), "A10"));
					num += 6;
					this.ItemAdd("最近一次断相起始时刻", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					this.ItemAdd("A相最近断相起始时刻", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					this.ItemAdd("B相最近断相起始时刻", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					this.ItemAdd("C相最近断相起始时刻", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					this.ItemAdd("最近一次断相结束时刻", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					this.ItemAdd("A相最近断相结束时刻", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					this.ItemAdd("B相最近断相结束时刻", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					this.ItemAdd("C相最近断相结束时刻", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F27(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					this.ItemAdd("电能表日历时钟", this.OperaRec(Value.Substring(num, 12), "A1"));
					num += 12;
					this.ItemAdd("电池工作时间", this.OperaRec(Value.Substring(num, 8), "A27"));
					num += 8;
					this.ItemAdd("编程总次数", this.OperaRec(Value.Substring(num, 6), "A10"));
					num += 6;
					this.ItemAdd("最近一次编程发生时刻", this.OperaRec(Value.Substring(num, 12), "A1"));
					num += 12;
					this.ItemAdd("电表清零总次数", this.OperaRec(Value.Substring(num, 6), "A10"));
					num += 6;
					this.ItemAdd("最近一次清零发生时刻", this.OperaRec(Value.Substring(num, 12), "A1"));
					num += 12;
					this.ItemAdd("需量清零总次数", this.OperaRec(Value.Substring(num, 6), "A10"));
					num += 6;
					this.ItemAdd("最近一次清零发生时刻", this.OperaRec(Value.Substring(num, 12), "A1"));
					num += 12;
					this.ItemAdd("事件清零总次数", this.OperaRec(Value.Substring(num, 6), "A10"));
					num += 6;
					this.ItemAdd("最近一次清零发生时刻", this.OperaRec(Value.Substring(num, 12), "A1"));
					num += 12;
					this.ItemAdd("校时总次数", this.OperaRec(Value.Substring(num, 6), "A10"));
					num += 6;
					this.ItemAdd("最近一次校时发生时刻", this.OperaRec(Value.Substring(num, 12), "A1"));
					num += 12;
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F28(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					this.ItemAdd("电表运行状态字变位标志1", this.OperaRec(Value.Substring(num, 4), "BCD"));
					num += 4;
					this.ItemAdd("电表运行状态字变位标志2", this.OperaRec(Value.Substring(num, 4), "BCD"));
					num += 4;
					this.ItemAdd("电表运行状态字变位标志3", this.OperaRec(Value.Substring(num, 4), "BCD"));
					num += 4;
					this.ItemAdd("电表运行状态字变位标志4", this.OperaRec(Value.Substring(num, 4), "BCD"));
					num += 4;
					this.ItemAdd("电表运行状态字变位标志5", this.OperaRec(Value.Substring(num, 4), "BCD"));
					num += 4;
					this.ItemAdd("电表运行状态字变位标志6", this.OperaRec(Value.Substring(num, 4), "BCD"));
					num += 4;
					this.ItemAdd("电表运行状态字变位标志7", this.OperaRec(Value.Substring(num, 4), "BCD"));
					num += 4;
					this.ItemAdd("电表运行状态字1", this.ZhuangTaiZi(this.OperaRec(Value.Substring(num, 4), "BCD"), 1));
					num += 4;
					this.ItemAdd("电表运行状态字2", this.ZhuangTaiZi(this.OperaRec(Value.Substring(num, 4), "BCD"), 2));
					num += 4;
					this.ItemAdd("电表运行状态字3", this.ZhuangTaiZi(this.OperaRec(Value.Substring(num, 4), "BCD"), 3));
					num += 4;
					this.ItemAdd("电表运行状态字4", this.ZhuangTaiZi(this.OperaRec(Value.Substring(num, 4), "BCD"), 4));
					num += 4;
					this.ItemAdd("电表运行状态字5", this.ZhuangTaiZi(this.OperaRec(Value.Substring(num, 4), "BCD"), 5));
					num += 4;
					this.ItemAdd("电表运行状态字6", this.ZhuangTaiZi(this.OperaRec(Value.Substring(num, 4), "BCD"), 6));
					num += 4;
					this.ItemAdd("电表运行状态字7", this.ZhuangTaiZi(this.OperaRec(Value.Substring(num, 4), "BCD"), 7));
					num += 4;
					result = num;
				}
				return result;
			}
		}
		private string ZhuangTaiZi(string RecUserData, int ZTZIndex)
		{
			string text = string.Empty;
			string result;
			if (string.IsNullOrEmpty(RecUserData) || RecUserData.IndexOf("Error") >= 0)
			{
				result = "";
			}
			else
			{
				text = PubFuncHelper.HexToBin(RecUserData);
				string text2 = string.Empty;
				text = DataConvert.ReverseStr(text, 1);
				switch (ZTZIndex)
				{
				case 1:
					text2 = text2 + "\r\n需量计算方式:" + ((text.Substring(1, 1) == "0") ? "滑差" : "区间") + ",";
					text2 = text2 + "\r\n时钟电池:" + ((text.Substring(2, 1) == "0") ? "正常" : "欠压") + ",";
					text2 = text2 + "\r\n停电抄表电池:" + ((text.Substring(3, 1) == "0") ? "正常" : "欠压") + ",";
					text2 = text2 + "\r\n有功功率方向:" + ((text.Substring(4, 1) == "0") ? "正向" : "反向") + ",";
					text2 = text2 + "\r\n无功功率方向:" + ((text.Substring(5, 1) == "0") ? "正向" : "反向");
					break;

				case 2:
					text2 = text2 + "\r\nA相有功功率:" + ((text.Substring(0, 1) == "0") ? "正向" : "反向") + ",";
					text2 = text2 + "\r\nB相有功功率:" + ((text.Substring(1, 1) == "0") ? "正向" : "反向") + ",";
					text2 = text2 + "\r\nC相有功功率:" + ((text.Substring(2, 1) == "0") ? "正向" : "反向") + ",";
					text2 = text2 + "\r\nA相无功功率:" + ((text.Substring(4, 1) == "0") ? "正向" : "反向") + ",";
					text2 = text2 + "\r\nB相无功功率:" + ((text.Substring(5, 1) == "0") ? "正向" : "反向") + ",";
					text2 = text2 + "\r\nC相无功功率:" + ((text.Substring(6, 1) == "0") ? "正向" : "反向") + ",";
					break;

				case 3:
					{
						text2 = text2 + "\r\n运行时段:" + ((text.Substring(0, 1) == "0") ? "第一套" : "第二套") + ",";
						string str = string.Empty;
						if (text.Substring(1, 2) == "00")
						{
							str = "主电源";
						}
						else
						{
							if (text.Substring(1, 2) == "01")
							{
								str = "辅助电源";
							}
							else
							{
								if (text.Substring(1, 2) == "02")
								{
									str = "电池供电";
								}
								else
								{
									str = "未设置";
								}
							}
						}
						text2 = text2 + "\r\n供电:" + str + ",";
						text2 = text2 + "\r\n编程允许:" + ((text.Substring(3, 1) == "0") ? "禁止" : "许可") + ",";
						text2 = text2 + "\r\n继电器状态:" + ((text.Substring(4, 1) == "0") ? "通" : "断") + ",";
						text2 = text2 + "\r\n运行时区:" + ((text.Substring(5, 1) == "0") ? "第一套" : "第二套") + ",";
						text2 = text2 + "\r\n断电器命令状态:" + ((text.Substring(6, 1) == "0") ? "通" : "断") + ",";
						text2 = text2 + "\r\n预跳闸报警状态:" + ((text.Substring(7, 1) == "0") ? "无" : "有") + ",";
						string str2 = string.Empty;
						if (text.Substring(8, 2) == "00")
						{
							str2 = "非预付费表";
						}
						else
						{
							if (text.Substring(8, 2) == "01")
							{
								str2 = "电量型预付费表";
							}
							else
							{
								if (text.Substring(8, 2) == "02")
								{
									str2 = "电费型预付费表";
								}
								else
								{
									str2 = "未设置";
								}
							}
						}
						text2 = text2 + "\r\n电能表类型:" + str2 + ",";
						text2 = text2 + "\r\n运行分时费率:" + ((text.Substring(10, 1) == "0") ? "第一套" : "第二套") + ",";
						text2 = text2 + "\r\n当前阶梯:" + ((text.Substring(11, 1) == "0") ? "第一套" : "第二套") + ",";
						break;
					}

				case 4:
					text2 = text2 + "\r\n失压:" + ((text.Substring(0, 1) == "0") ? "无故障" : "故障") + ",";
					text2 = text2 + "\r\n欠压:" + ((text.Substring(1, 1) == "0") ? "无故障" : "故障") + ",";
					text2 = text2 + "\r\n过压:" + ((text.Substring(2, 1) == "0") ? "无故障" : "故障") + ",";
					text2 = text2 + "\r\n失流:" + ((text.Substring(3, 1) == "0") ? "无故障" : "故障") + ",";
					text2 = text2 + "\r\n过流:" + ((text.Substring(4, 1) == "0") ? "无故障" : "故障") + ",";
					text2 = text2 + "\r\n过载:" + ((text.Substring(5, 1) == "0") ? "无故障" : "故障") + ",";
					text2 = text2 + "\r\n潮流反向:" + ((text.Substring(6, 1) == "0") ? "无故障" : "故障") + ",";
					text2 = text2 + "\r\n断相:" + ((text.Substring(7, 1) == "0") ? "无故障" : "故障") + ",";
					text2 = text2 + "\r\n断流:" + ((text.Substring(8, 1) == "0") ? "无故障" : "故障");
					break;

				case 5:
					text2 = text2 + "\r\n失压:" + ((text.Substring(0, 1) == "0") ? "无故障" : "故障") + ",";
					text2 = text2 + "\r\n欠压:" + ((text.Substring(1, 1) == "0") ? "无故障" : "故障") + ",";
					text2 = text2 + "\r\n过压:" + ((text.Substring(2, 1) == "0") ? "无故障" : "故障") + ",";
					text2 = text2 + "\r\n失流:" + ((text.Substring(3, 1) == "0") ? "无故障" : "故障") + ",";
					text2 = text2 + "\r\n过流:" + ((text.Substring(4, 1) == "0") ? "无故障" : "故障") + ",";
					text2 = text2 + "\r\n过载:" + ((text.Substring(5, 1) == "0") ? "无故障" : "故障") + ",";
					text2 = text2 + "\r\n潮流反向:" + ((text.Substring(6, 1) == "0") ? "无故障" : "故障") + ",";
					text2 = text2 + "\r\n断相:" + ((text.Substring(7, 1) == "0") ? "无故障" : "故障") + ",";
					text2 = text2 + "\r\n断流:" + ((text.Substring(8, 1) == "0") ? "无故障" : "故障");
					break;

				case 6:
					text2 = text2 + "\r\n失压:" + ((text.Substring(0, 1) == "0") ? "无故障" : "故障") + ",";
					text2 = text2 + "\r\n欠压:" + ((text.Substring(1, 1) == "0") ? "无故障" : "故障") + ",";
					text2 = text2 + "\r\n过压:" + ((text.Substring(2, 1) == "0") ? "无故障" : "故障") + ",";
					text2 = text2 + "\r\n失流:" + ((text.Substring(3, 1) == "0") ? "无故障" : "故障") + ",";
					text2 = text2 + "\r\n过流:" + ((text.Substring(4, 1) == "0") ? "无故障" : "故障") + ",";
					text2 = text2 + "\r\n过载:" + ((text.Substring(5, 1) == "0") ? "无故障" : "故障") + ",";
					text2 = text2 + "\r\n潮流反向:" + ((text.Substring(6, 1) == "0") ? "无故障" : "故障") + ",";
					text2 = text2 + "\r\n断相:" + ((text.Substring(7, 1) == "0") ? "无故障" : "故障") + ",";
					text2 = text2 + "\r\n断流:" + ((text.Substring(8, 1) == "0") ? "无故障" : "故障");
					break;

				case 7:
					text2 = text2 + "\r\n电压逆相序:" + ((text.Substring(0, 1) == "0") ? "无故障" : "故障") + ",";
					text2 = text2 + "\r\n电流逆相序:" + ((text.Substring(1, 1) == "0") ? "无故障" : "故障") + ",";
					text2 = text2 + "\r\n电压不平衡:" + ((text.Substring(2, 1) == "0") ? "无故障" : "故障") + ",";
					text2 = text2 + "\r\n电流不平衡:" + ((text.Substring(3, 1) == "0") ? "无故障" : "故障") + ",";
					text2 = text2 + "\r\n辅助电源失电:" + ((text.Substring(4, 1) == "0") ? "无故障" : "故障") + ",";
					text2 = text2 + "\r\n掉电:" + ((text.Substring(5, 1) == "0") ? "无故障" : "故障") + ",";
					text2 = text2 + "\r\n需量超限:" + ((text.Substring(6, 1) == "0") ? "无故障" : "故障");
					text2 = text2 + "\r\n总功率因数超下限:" + ((text.Substring(7, 1) == "0") ? "无故障" : "故障");
					text2 = text2 + "\r\n电流严重不平衡:" + ((text.Substring(8, 1) == "0") ? "无故障" : "故障");
					break;
				}
				result = text2;
			}
			return result;
		}
		private int AF0C_F29(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					this.ItemAdd("当前铜损有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					this.ItemAdd("当前铁损有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F30(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					this.ItemAdd("上一结算日铜损有功总电能补偿量", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					this.ItemAdd("上一结算日铁损有功总电能补偿量", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F31(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					this.ItemAdd("当前A相正向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					this.ItemAdd("当前A相反向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					this.ItemAdd("当前A相组合无功1电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					this.ItemAdd("当前A相组合无功2电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					this.ItemAdd("当前B相正向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					this.ItemAdd("当前B相反向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					this.ItemAdd("当前B相组合无功1电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					this.ItemAdd("当前B相组合无功2电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					this.ItemAdd("当前C相正向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					this.ItemAdd("当前C相反向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					this.ItemAdd("当前C相组合无功1电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					this.ItemAdd("当前C相组合无功2电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F32(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					this.ItemAdd("上一结算日A相正向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					this.ItemAdd("上一结算日A相反向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					this.ItemAdd("上一结算日A相组合无功1电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					this.ItemAdd("上一结算日A相组合无功2电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					this.ItemAdd("上一结算日B相正向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					this.ItemAdd("上一结算日B相反向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					this.ItemAdd("上一结算日B相组合无功1电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					this.ItemAdd("上一结算日B相组合无功2电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					this.ItemAdd("上一结算日C相正向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					this.ItemAdd("上一结算日C相反向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					this.ItemAdd("上一结算日C相组合无功1电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					this.ItemAdd("上一结算日C相组合无功2电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F33(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("当前正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("当前费率" + (i + 1).ToString() + "正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					this.ItemAdd("当前正向无功(组合无功1)总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("当前费率" + (i + 1).ToString() + "正向无功(组合无功1)总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					this.ItemAdd("当前一象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("当前一象限费率" + (i + 1).ToString() + "无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					this.ItemAdd("当前四象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("当前四象限费率" + (i + 1).ToString() + "无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F34(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("当前反向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("当前费率" + (i + 1).ToString() + "反向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					this.ItemAdd("当前反向无功(组合无功2)总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("当前费率" + (i + 1).ToString() + "反向无功(组合无功2)总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					this.ItemAdd("当前二象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("当前二象限费率" + (i + 1).ToString() + "无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					this.ItemAdd("当前三象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("当前三象限费率" + (i + 1).ToString() + "无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F35(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("当月正向有功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("当月正向有功费率" + (i + 1).ToString() + "最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
					}
					this.ItemAdd("当月正向有功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("当月正向有功费率" + (i + 1).ToString() + "最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					this.ItemAdd("当月正向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("当月正向无功费率" + (i + 1).ToString() + "最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
					}
					this.ItemAdd("当月正向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("当月正向无功费率" + (i + 1).ToString() + "最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F36(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("当月反向有功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("当月反向有功费率" + (i + 1).ToString() + "最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
					}
					this.ItemAdd("当月反向有功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("当月反向有功费率" + (i + 1).ToString() + "最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					this.ItemAdd("当月反向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("当月反向无功费率" + (i + 1).ToString() + "最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
					}
					this.ItemAdd("当月反向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("当月反向无功费率" + (i + 1).ToString() + "最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F37(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("上月(上一结算日)正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("上月(上一结算日)费率" + (i + 1).ToString() + "正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					this.ItemAdd("上月(上一结算日)正向无功(组合无功1)总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("上月(上一结算日)费率" + (i + 1).ToString() + "正向无功(组合无功1)总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					this.ItemAdd("上月(上一结算日)一象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("上月(上一结算日)一象限费率" + (i + 1).ToString() + "无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					this.ItemAdd("上月(上一结算日)四象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("上月(上一结算日)四象限费率" + (i + 1).ToString() + "无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F38(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("上月(上一结算日)反向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("上月(上一结算日)费率" + (i + 1).ToString() + "反向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					this.ItemAdd("上月(上一结算日)反向无功(组合无功2)总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("上月(上一结算日)费率" + (i + 1).ToString() + "反向无功(组合无功2)总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					this.ItemAdd("上月(上一结算日)二象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("上月(上一结算日)二象限费率" + (i + 1).ToString() + "无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					this.ItemAdd("上月(上一结算日)三象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("上月(上一结算日)三象限费率" + (i + 1).ToString() + "无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F39(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("上月(上一结算日)正向有功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("上月(上一结算日)正向有功费率" + (i + 1).ToString() + "最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
					}
					this.ItemAdd("上月(上一结算日)正向有功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("上月(上一结算日)正向有功费率" + (i + 1).ToString() + "最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					this.ItemAdd("上月(上一结算日)正向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("上月(上一结算日)正向无功费率" + (i + 1).ToString() + "最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
					}
					this.ItemAdd("上月(上一结算日)正向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("上月(上一结算日)正向无功费率" + (i + 1).ToString() + "最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F40(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("上月(上一结算日)反向有功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("上月(上一结算日)反向有功费率" + (i + 1).ToString() + "最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
					}
					this.ItemAdd("上月(上一结算日)反向有功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("上月(上一结算日)反向有功费率" + (i + 1).ToString() + "最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					this.ItemAdd("上月(上一结算日)反向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("上月(上一结算日)反向无功费率" + (i + 1).ToString() + "最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
					}
					this.ItemAdd("上月(上一结算日)反向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("上月(上一结算日)反向无功费率" + (i + 1).ToString() + "最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F41(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = DataConvert.HexToInt(Value.Substring(0, 2));
					this.ItemAdd("费率数", num.ToString());
					this.ItemAdd("当日正向有功总电能量", this.OperaRec(Value.Substring(2, 8), "A13"));
					int num2 = 10;
					for (int i = 0; i < num; i++)
					{
						this.ItemAdd("当日费率" + (i + 1).ToString() + "正向有功电能量", this.OperaRec(Value.Substring(num2, 8), "A13"));
						num2 += 8;
					}
					result = num2;
				}
				return result;
			}
		}
		private int AF0C_F42(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = DataConvert.HexToInt(Value.Substring(0, 2));
					this.ItemAdd("费率数", num.ToString());
					this.ItemAdd("当日正向无功总电能量", this.OperaRec(Value.Substring(2, 8), "A13"));
					int num2 = 10;
					for (int i = 0; i < num; i++)
					{
						this.ItemAdd("当日费率" + (i + 1).ToString() + "正向无功电能量", this.OperaRec(Value.Substring(num2, 8), "A13"));
						num2 += 8;
					}
					result = num2;
				}
				return result;
			}
		}
		private int AF0C_F43(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = DataConvert.HexToInt(Value.Substring(0, 2));
					this.ItemAdd("费率数", num.ToString());
					this.ItemAdd("当日反向有功总电能量", this.OperaRec(Value.Substring(2, 8), "A13"));
					int num2 = 10;
					for (int i = 0; i < num; i++)
					{
						this.ItemAdd("当日费率" + (i + 1).ToString() + "反向有功电能量", this.OperaRec(Value.Substring(num2, 8), "A13"));
						num2 += 8;
					}
					result = num2;
				}
				return result;
			}
		}
		private int AF0C_F44(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = DataConvert.HexToInt(Value.Substring(0, 2));
					this.ItemAdd("费率数", num.ToString());
					this.ItemAdd("当日反向无功总电能量", this.OperaRec(Value.Substring(2, 8), "A13"));
					int num2 = 10;
					for (int i = 0; i < num; i++)
					{
						this.ItemAdd("当日费率" + (i + 1).ToString() + "反向无功电能量", this.OperaRec(Value.Substring(num2, 8), "A13"));
						num2 += 8;
					}
					result = num2;
				}
				return result;
			}
		}
		private int AF0C_F45(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = DataConvert.HexToInt(Value.Substring(0, 2));
					this.ItemAdd("费率数", num.ToString());
					this.ItemAdd("当月正向有功总电能量", this.OperaRec(Value.Substring(2, 8), "A13"));
					int num2 = 10;
					for (int i = 0; i < num; i++)
					{
						this.ItemAdd("当日费率" + (i + 1).ToString() + "正向有功电能量", this.OperaRec(Value.Substring(num2, 8), "A13"));
						num2 += 8;
					}
					result = num2;
				}
				return result;
			}
		}
		private int AF0C_F46(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = DataConvert.HexToInt(Value.Substring(0, 2));
					this.ItemAdd("费率数", num.ToString());
					this.ItemAdd("当月正向无功总电能量", this.OperaRec(Value.Substring(2, 8), "A13"));
					int num2 = 10;
					for (int i = 0; i < num; i++)
					{
						this.ItemAdd("当日费率" + (i + 1).ToString() + "正向无功电能量", this.OperaRec(Value.Substring(num2, 8), "A13"));
						num2 += 8;
					}
					result = num2;
				}
				return result;
			}
		}
		private int AF0C_F47(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = DataConvert.HexToInt(Value.Substring(0, 2));
					this.ItemAdd("费率数", num.ToString());
					this.ItemAdd("当月反向有功总电能量", this.OperaRec(Value.Substring(2, 8), "A13"));
					int num2 = 10;
					for (int i = 0; i < num; i++)
					{
						this.ItemAdd("当日费率" + (i + 1).ToString() + "反向有功电能量", this.OperaRec(Value.Substring(num2, 8), "A13"));
						num2 += 8;
					}
					result = num2;
				}
				return result;
			}
		}
		private int AF0C_F48(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = DataConvert.HexToInt(Value.Substring(0, 2));
					this.ItemAdd("费率数", num.ToString());
					this.ItemAdd("当月反向无功总电能量", this.OperaRec(Value.Substring(2, 8), "A13"));
					int num2 = 10;
					for (int i = 0; i < num; i++)
					{
						this.ItemAdd("当日费率" + (i + 1).ToString() + "反向无功电能量", this.OperaRec(Value.Substring(num2, 8), "A13"));
						num2 += 8;
					}
					result = num2;
				}
				return result;
			}
		}
		private int AF0C_F49(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("Uab/Ua相位角", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("Ub相位角", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("Ucb/Uc相位角", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("Ia相位角", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("Ib相位角", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("Ic相位角", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F57(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = DataConvert.HexToInt(Value.Substring(0, 2));
					this.ItemAdd("谐波次数", num.ToString());
					int num2 = 2;
					for (int i = 2; i < num; i++)
					{
						this.ItemAdd("A相" + i.ToString() + "次谐波电压", this.OperaRec(Value.Substring(num2, 4), "A7"));
						num2 += 4;
					}
					for (int i = 2; i < num; i++)
					{
						this.ItemAdd("B相" + i.ToString() + "次谐波电压", this.OperaRec(Value.Substring(num2, 4), "A7"));
						num2 += 4;
					}
					for (int i = 2; i < num; i++)
					{
						this.ItemAdd("C相" + i.ToString() + "次谐波电压", this.OperaRec(Value.Substring(num2, 4), "A7"));
						num2 += 4;
					}
					for (int i = 2; i < num; i++)
					{
						this.ItemAdd("A相" + i.ToString() + "次谐波电流", this.OperaRec(Value.Substring(num2, 4), "A6"));
						num2 += 4;
					}
					for (int i = 2; i < num; i++)
					{
						this.ItemAdd("B相" + i.ToString() + "次谐波电流", this.OperaRec(Value.Substring(num2, 4), "A6"));
						num2 += 4;
					}
					for (int i = 2; i < num; i++)
					{
						this.ItemAdd("C相" + i.ToString() + "次谐波电流", this.OperaRec(Value.Substring(num2, 4), "A6"));
						num2 += 4;
					}
					result = num2;
				}
				return result;
			}
		}
		private int AF0C_F58(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("谐波次数", num2.ToString());
					num += 2;
					this.ItemAdd("A相总谐波电压含有率", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					for (int i = 2; i < num2; i++)
					{
						this.ItemAdd("A相" + i.ToString() + "次谐波电压含有率", this.OperaRec(Value.Substring(num, 4), "A5"));
						num += 4;
					}
					this.ItemAdd("B相总谐波电压含有率", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					for (int i = 2; i < num2; i++)
					{
						this.ItemAdd("B相" + i.ToString() + "次谐波电压含有率", this.OperaRec(Value.Substring(num, 4), "A5"));
						num += 4;
					}
					this.ItemAdd("C相总谐波电压含有率", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					for (int i = 2; i < num2; i++)
					{
						this.ItemAdd("C相" + i.ToString() + "次谐波电压含有率", this.OperaRec(Value.Substring(num, 4), "A5"));
						num += 4;
					}
					for (int i = 2; i < num2; i++)
					{
						this.ItemAdd("A相" + i.ToString() + "次谐波电流含有率", this.OperaRec(Value.Substring(num, 4), "A5"));
						num += 4;
					}
					for (int i = 2; i < num2; i++)
					{
						this.ItemAdd("B相" + i.ToString() + "次谐波电流含有率", this.OperaRec(Value.Substring(num, 4), "A5"));
						num += 4;
					}
					for (int i = 2; i < num2; i++)
					{
						this.ItemAdd("C相" + i.ToString() + "次谐波电流含有率", this.OperaRec(Value.Substring(num, 4), "A5"));
						num += 4;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F65(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					string text = string.Empty;
					text += (((num2 & 1) == 0) ? "" : "当地控制,");
					text += (((num2 >> 1 & 1) == 0) ? "" : "远方控制,");
					text += (((num2 >> 2 & 1) == 0) ? "" : "硬件闭锁,");
					text += (((num2 >> 3 & 1) == 0) ? "" : "软件闭锁,");
					text += (((num2 >> 4 & 1) == 0) ? "" : "过压闭锁,");
					text += (((num2 >> 5 & 1) == 0) ? "" : "设备故障闭锁,");
					text += (((num2 >> 6 & 1) == 0) ? "" : "执行回路故障闭锁,");
					text += (((num2 >> 7 & 1) == 0) ? "" : "备用,");
					this.ItemAdd("运行方式", text.ToString());
					long num3 = DataConvert.HexToLong(DataConvert.ReverseStr(Value.Substring(num, 4)));
					num += 4;
					string empty = string.Empty;
					for (int i = 0; i < 9; i++)
					{
						this.ItemAdd("电容器" + (i + 1).ToString() + "组投切状态", ((num3 >> i & 1L) == 1L) ? "投入" : "切除");
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F66(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					for (int i = 0; i < 9; i++)
					{
						this.ItemAdd("当前第" + (i + 1).ToString() + "组电容器累计投入时间", this.OperaRec(Value.Substring(num, 8), "BIN"));
						num += 8;
					}
					for (int i = 0; i < 9; i++)
					{
						this.ItemAdd("当前第" + (i + 1).ToString() + "组电容器累计投入次数", this.OperaRec(Value.Substring(num, 8), "BIN"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F67(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("当前日补偿的无功电能量", this.OperaRec(Value.Substring(num, 8), "A13"));
					num += 8;
					this.ItemAdd("当前月补偿的无功电能量", this.OperaRec(Value.Substring(num, 8), "A13"));
					num += 8;
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F73(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("直流模拟量当前数据", this.OperaRec(Value.Substring(num), "A2"));
					num += Value.Length;
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F81(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("小时冻结类数据时标", this.Td_h(Value.Substring(num, 4), ref num2));
					num += 4;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("小时冻结总加有功功率" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 4), "A2"));
						num += 4;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F82(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("小时冻结类数据时标", this.Td_h(Value.Substring(num, 4), ref num2));
					num += 4;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("小时冻结总加无功功率" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 4), "A2"));
						num += 4;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F83(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("小时冻结类数据时标", this.Td_h(Value.Substring(num, 4), ref num2));
					num += 4;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("小时冻结总加有功总电能量" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 8), "A3", "kWh"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F84(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("小时冻结类数据时标", this.Td_h(Value.Substring(num, 4), ref num2));
					num += 4;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("小时冻结总加无功总电能量" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 8), "A3", "kvarh"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F89(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("小时冻结类数据时标", this.Td_h(Value.Substring(num, 4), ref num2));
					num += 4;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("小时冻结有功功率" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 6), "A9"));
						num += 6;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F93(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("小时冻结类数据时标", this.Td_h(Value.Substring(num, 4), ref num2));
					num += 4;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("小时冻结无功功率" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 6), "A9"));
						num += 6;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F97(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("小时冻结类数据时标", this.Td_h(Value.Substring(num, 4), ref num2));
					num += 4;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("小时冻结电压" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 4), "A7"));
						num += 4;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F100(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("小时冻结类数据时标", this.Td_h(Value.Substring(num, 4), ref num2));
					num += 4;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("小时冻结电流" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 6), "A25"));
						num += 6;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F105(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("小时冻结类数据时标", this.Td_h(Value.Substring(num, 4), ref num2));
					num += 4;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("小时冻结正向有功总电能量" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 8), "A13"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F106(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("小时冻结类数据时标", this.Td_h(Value.Substring(num, 4), ref num2));
					num += 4;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("小时冻结正向无功总电能量" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 8), "A13"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F107(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("小时冻结类数据时标", this.Td_h(Value.Substring(num, 4), ref num2));
					num += 4;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("小时冻结反向有功总电能量" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 8), "A13"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F108(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("小时冻结类数据时标", this.Td_h(Value.Substring(num, 4), ref num2));
					num += 4;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("小时冻结反向无功总电能量" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 8), "A13"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F109(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("小时冻结类数据时标", this.Td_h(Value.Substring(num, 4), ref num2));
					num += 4;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("小时冻结正向有功总电能示值" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F110(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("小时冻结类数据时标", this.Td_h(Value.Substring(num, 4), ref num2));
					num += 4;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("小时冻结正向无功总电能示值" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F111(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("小时冻结类数据时标", this.Td_h(Value.Substring(num, 4), ref num2));
					num += 4;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("小时冻结反向有功总电能示值" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F112(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("小时冻结类数据时标", this.Td_h(Value.Substring(num, 4), ref num2));
					num += 4;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("小时冻结反向无功总电能示值" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F113(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("小时冻结类数据时标", this.Td_h(Value.Substring(num, 4), ref num2));
					num += 4;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("小时冻结总功率因数" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 4), "A5"));
						num += 4;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F121(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("小时冻结类数据时标", this.Td_h(Value.Substring(num, 4), ref num2));
					num += 4;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("小时冻结直流模拟量" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 4), "A2"));
						num += 4;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F129(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F130(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向无功(组合无功1)总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向无功(组合无功1)总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F131(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("反向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F132(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("反向无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F133(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("一象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("一象限费率" + (i + 1).ToString() + "无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F134(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("二象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("二象限费率" + (i + 1).ToString() + "无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F135(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("三象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("三象限费率" + (i + 1).ToString() + "无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F136(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("四象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("四象限费率" + (i + 1).ToString() + "无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F137(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("上月(上一结算日)正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("上月(上一结算日)费率" + (i + 1).ToString() + "正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F138(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("上月(上一结算日)正向无功(组合无功1)总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("上月(上一结算日)费率" + (i + 1).ToString() + "正向无功(组合无功1)总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F139(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("上月(上一结算日)反向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("上月(上一结算日)费率" + (i + 1).ToString() + "反向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F140(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("上月(上一结算日)反向无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("上月(上一结算日)费率" + (i + 1).ToString() + "反向无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F141(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("上月(上一结算日)一象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("上月(上一结算日)一象限费率" + (i + 1).ToString() + "无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F142(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("上月(上一结算日)二象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("上月(上一结算日)二象限费率" + (i + 1).ToString() + "无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F143(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("上月(上一结算日)三象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("上月(上一结算日)三象限费率" + (i + 1).ToString() + "无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F144(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("上月(上一结算日)四象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("上月(上一结算日)四象限费率" + (i + 1).ToString() + "无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F145(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向有功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("正向有功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("正向有功费率" + (i + 1).ToString() + "最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
						this.ItemAdd("正向有功费率" + (i + 1).ToString() + "最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F146(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("正向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("正向无功费率" + (i + 1).ToString() + "最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
						this.ItemAdd("正向无功费率" + (i + 1).ToString() + "最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F147(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("反向有功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("反向有功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("反向有功费率" + (i + 1).ToString() + "最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
						this.ItemAdd("反向有功费率" + (i + 1).ToString() + "最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F148(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("反向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("反向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("反向无功费率" + (i + 1).ToString() + "最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
						this.ItemAdd("反向无功费率" + (i + 1).ToString() + "最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F149(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("上月(上一结算日)正向有功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("上月(上一结算日)正向有功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("上月(上一结算日)正向有功费率" + (i + 1).ToString() + "最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
						this.ItemAdd("上月(上一结算日)正向有功费率" + (i + 1).ToString() + "最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F150(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("上月(上一结算日)正向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("上月(上一结算日)正向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("上月(上一结算日)正向无功费率" + (i + 1).ToString() + "最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
						this.ItemAdd("上月(上一结算日)正向无功费率" + (i + 1).ToString() + "最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F151(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("上月(上一结算日)反向有功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("上月(上一结算日)反向有功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("上月(上一结算日)反向有功费率" + (i + 1).ToString() + "最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
						this.ItemAdd("上月(上一结算日)反向有功费率" + (i + 1).ToString() + "最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F152(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("上月(上一结算日)反向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("上月(上一结算日)反向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("上月(上一结算日)反向无功费率" + (i + 1).ToString() + "最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
						this.ItemAdd("上月(上一结算日)反向无功费率" + (i + 1).ToString() + "最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F153(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F154(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F155(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F156(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F157(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F158(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F159(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F160(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F161(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("电能表通断电状态", (num2 == 1) ? "通电" : "断电");
					num += 2;
					this.ItemAdd("最近一次电能表远程控制通电时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					this.ItemAdd("最近一次电能表远程控制断电时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F165(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					this.ItemAdd("编程开关操作次数", this.OperaRec(Value.Substring(num, 4), "A8"));
					num += 4;
					this.ItemAdd("最近一次编程开关操作时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					this.ItemAdd("电能表尾盖打开次数", this.OperaRec(Value.Substring(num, 4), "A8"));
					num += 4;
					this.ItemAdd("最近一次尾盖打开时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F166(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					this.ItemAdd("电能表时钟修改次数", this.OperaRec(Value.Substring(num, 4), "A8"));
					num += 4;
					this.ItemAdd("电能表最近一次时钟修改时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					this.ItemAdd("电能表时段参数修改次数", this.OperaRec(Value.Substring(num, 4), "A8"));
					num += 4;
					this.ItemAdd("最近一次电能表时段参数修改时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F167(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					this.ItemAdd("购电次数", this.OperaRec(Value.Substring(num, 4), "A8"));
					num += 4;
					this.ItemAdd("剩余金额", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					this.ItemAdd("累计购电金额", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					this.ItemAdd("剩余电量", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					this.ItemAdd("透支电量", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					this.ItemAdd("累计购电量", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					this.ItemAdd("赊欠门限电量", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					this.ItemAdd("报警电量", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					this.ItemAdd("故障电量", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F168(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("已结有功总电能", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("已结费率" + (i + 1).ToString() + "正向有功总电能", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					this.ItemAdd("未结有功总电能", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("未结费率" + (i + 1).ToString() + "正向有功总电能", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F169(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("所属终端通信端口号", DataConvert.HexToInt(Value.Substring(num, 2)).ToString());
					num += 2;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("中继路由个数n", num2.ToString());
					num += 2;
					for (int i = 0; i < num2; i++)
					{
						int num3 = DataConvert.HexToInt(Value.Substring(num, 2));
						this.ItemAdd("第" + (i + 1).ToString() + "中继路由.级数", num3.ToString());
						num += 2;
						for (int j = 0; j < num3; j++)
						{
							this.ItemAdd(string.Concat(new string[]
							{
								"第",
								(i + 1).ToString(),
								"中继路由.第",
								(j + 1).ToString(),
								"级中继地址"
							}), this.OperaRec(Value.Substring(num, 12), "A12"));
							num += 12;
						}
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0C_F170(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("所属终端通信端口号", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					this.ItemAdd("中继路由级数", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					num += 2;
					this.ItemAdd("载波抄读通信相位.实际相位A相", ((num2 & 1) == 0) ? "无效" : "有效");
					this.ItemAdd("载波抄读通信相位.实际相位B相", ((num2 >> 1 & 1) == 0) ? "无效" : "有效");
					this.ItemAdd("载波抄读通信相位.实际相位C相", ((num2 >> 2 & 1) == 0) ? "无效" : "有效");
					this.ItemAdd("载波抄读通信相位.抄表相位A相", ((num2 >> 4 & 1) == 0) ? "无效" : "有效");
					this.ItemAdd("载波抄读通信相位.抄表相位B相", ((num2 >> 5 & 1) == 0) ? "无效" : "有效");
					this.ItemAdd("载波抄读通信相位.抄表相位C相", ((num2 >> 6 & 1) == 0) ? "无效" : "有效");
					num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					num += 2;
					this.ItemAdd("发送载波信号品质", (num2 >> 4 & 15).ToString());
					this.ItemAdd("接收载波信号品质", (num2 & 15).ToString());
					this.ItemAdd("最近一次抄表成功/失败标志", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					this.ItemAdd("最近一次抄表成功时间", this.OperaRec(Value.Substring(num, 12), "A1"));
					num += 12;
					this.ItemAdd("最近一次抄表失败时间", this.OperaRec(Value.Substring(num, 12), "A1"));
					num += 12;
					this.ItemAdd("最近连续失败累计次数", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F1(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					this.ItemAdd("正向无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					this.ItemAdd("一象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "一象限无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					this.ItemAdd("四象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "四象限无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F2(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("反向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					this.ItemAdd("反向无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					this.ItemAdd("二象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "二象限无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					this.ItemAdd("三象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "三象限无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F3(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向有功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
					}
					this.ItemAdd("正向有功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					this.ItemAdd("正向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
					}
					this.ItemAdd("正向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F4(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("反向有功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向有功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
					}
					this.ItemAdd("反向有功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向有功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					this.ItemAdd("反向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
					}
					this.ItemAdd("反向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F5(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("日正向有功总电能量", this.OperaRec(Value.Substring(num, 8), "A13"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "日正向有功总电能量", this.OperaRec(Value.Substring(num, 8), "A13"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F6(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("日正向无功总电能量", this.OperaRec(Value.Substring(num, 8), "A13"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向无功电能量", this.OperaRec(Value.Substring(num, 8), "A13"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F7(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("日反向有功总电能量", this.OperaRec(Value.Substring(num, 8), "A13"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向有功电能量", this.OperaRec(Value.Substring(num, 8), "A13"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F8(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("日反向无功总电能量", this.OperaRec(Value.Substring(num, 8), "A13"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "日反向无功总电能量", this.OperaRec(Value.Substring(num, 8), "A13"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F9(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("抄表日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					this.ItemAdd("正向无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					this.ItemAdd("一象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "一象限无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					this.ItemAdd("四象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "四象限无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F10(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("抄表日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("反向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					this.ItemAdd("反向无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					this.ItemAdd("二象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "二象限无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					this.ItemAdd("三象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "三象限无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F11(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("抄表日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向有功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
					}
					this.ItemAdd("正向有功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					this.ItemAdd("正向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
					}
					this.ItemAdd("正向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F12(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("抄表日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("反向有功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向有功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
					}
					this.ItemAdd("反向有功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向有功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					this.ItemAdd("反向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
					}
					this.ItemAdd("反向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F17(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					this.ItemAdd("正向无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					this.ItemAdd("一象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "一象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					this.ItemAdd("四象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "四象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F18(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("反向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					this.ItemAdd("反向无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					this.ItemAdd("二象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "二象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					this.ItemAdd("三象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "三象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F19(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向有功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
					}
					this.ItemAdd("正向有功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					this.ItemAdd("正向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
					}
					this.ItemAdd("正向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F20(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("反向有功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向有功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
					}
					this.ItemAdd("反向有功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向有功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					this.ItemAdd("反向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
					}
					this.ItemAdd("反向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F21(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("月正向有功总电能量", this.OperaRec(Value.Substring(num, 8), "A13"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("月费率" + (i + 1).ToString() + "正向有功电能量", this.OperaRec(Value.Substring(num, 8), "A13"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F22(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("月正向有功总电能量", this.OperaRec(Value.Substring(num, 8), "A13"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("月费率" + (i + 1).ToString() + "正向无功电能量", this.OperaRec(Value.Substring(num, 8), "A13"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F23(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("月反向有功总电能量", this.OperaRec(Value.Substring(num, 8), "A13"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("月费率" + (i + 1).ToString() + "反向有功电能量", this.OperaRec(Value.Substring(num, 8), "A13"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F24(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("月反向无功总电能量", this.OperaRec(Value.Substring(num, 8), "A13"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("月费率" + (i + 1).ToString() + "反向无功电能量", this.OperaRec(Value.Substring(num, 8), "A13"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F25(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("三相总最大有功功率", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("三相总最大有功功率发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("A相最大有功功率", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("A相最大有功功率发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("B相最大有功功率", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("B相最大有功功率发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("C相最大有功功率", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("C相最大有功功率发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("三相总有功功率为零时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("A相有功功率为零时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("B相有功功率为零时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("C相有功功率为零时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F26(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("三相总有功最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("三相总有功最大需量发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("A相有功最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("A相有功最大需量发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("B相有功最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("B相有功最大需量发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("C相有功最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("C相有功最大需量发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F27(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("A相电压越上上限日累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("A相电压越下下限日累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("A相电压越上限日累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("A相电压越下限日累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("A相电压合格日累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("B相电压越上上限日累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("B相电压越下下限日累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("B相电压越上限日累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("B相电压越下限日累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("B相电压合格日累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("C相电压越上上限日累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("C相电压越下下限日累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("C相电压越上限日累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("C相电压越下限日累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("C相电压合格日累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("A相电压最大值", this.OperaRec(Value.Substring(num, 4), "A7"));
					num += 4;
					this.ItemAdd("A相电压最大值发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("A相电压最小值", this.OperaRec(Value.Substring(num, 4), "A7"));
					num += 4;
					this.ItemAdd("A相电压最小值发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("B相电压最大值", this.OperaRec(Value.Substring(num, 4), "A7"));
					num += 4;
					this.ItemAdd("B相电压最大值发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("B相电压最小值", this.OperaRec(Value.Substring(num, 4), "A7"));
					num += 4;
					this.ItemAdd("B相电压最小值发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("C相电压最大值", this.OperaRec(Value.Substring(num, 4), "A7"));
					num += 4;
					this.ItemAdd("C相电压最大值发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("C相电压最小值", this.OperaRec(Value.Substring(num, 4), "A7"));
					num += 4;
					this.ItemAdd("C相电压最小值发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("A相平均电压", this.OperaRec(Value.Substring(num, 4), "A7"));
					num += 4;
					this.ItemAdd("B相平均电压", this.OperaRec(Value.Substring(num, 4), "A7"));
					num += 4;
					this.ItemAdd("C相平均电压", this.OperaRec(Value.Substring(num, 4), "A7"));
					num += 4;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F28(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("电流不平衡度越限日累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("电压不平衡度越限日累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("电流不平衡最大值", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("电流不平衡最大值发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("电压不平衡最大值", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("电压不平衡最大值发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F29(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("A相电流越上上限累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("A相电流越上限累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("B相电流越上上限累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("B相电流越上限累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("C相电流越上上限累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("C相电流越上限累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("零序电流越上限累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("A相电流最大值", this.OperaRec(Value.Substring(num, 6), "A25"));
					num += 6;
					this.ItemAdd("A相电流最大值发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("B相电流最大值", this.OperaRec(Value.Substring(num, 6), "A25"));
					num += 6;
					this.ItemAdd("B相电流最大值发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("C相电流最大值", this.OperaRec(Value.Substring(num, 6), "A25"));
					num += 6;
					this.ItemAdd("C相电流最大值发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("零序电流最大值", this.OperaRec(Value.Substring(num, 6), "A25"));
					num += 6;
					this.ItemAdd("零序电流最大值发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F30(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("视在功率越上上限累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("视在功率越上限累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F31(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("负载率最大值", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("负载率最大值发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("负载率最小值", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("负载率最小值发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F32(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					this.ItemAdd("总断相次数", this.OperaRec(Value.Substring(num, 4), "A8"));
					num += 4;
					this.ItemAdd("A相断相次数", this.OperaRec(Value.Substring(num, 4), "A8"));
					num += 4;
					this.ItemAdd("B相断相次数", this.OperaRec(Value.Substring(num, 4), "A8"));
					num += 4;
					this.ItemAdd("C相断相次数", this.OperaRec(Value.Substring(num, 4), "A8"));
					num += 4;
					this.ItemAdd("断相累计时间", this.OperaRec(Value.Substring(num, 6), "A10"));
					num += 6;
					this.ItemAdd("A断相累计时间", this.OperaRec(Value.Substring(num, 6), "A10"));
					num += 6;
					this.ItemAdd("B断相累计时间", this.OperaRec(Value.Substring(num, 6), "A10"));
					num += 6;
					this.ItemAdd("C断相累计时间", this.OperaRec(Value.Substring(num, 6), "A10"));
					num += 6;
					this.ItemAdd("最近一次断相起始时刻", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					this.ItemAdd("A相最近断相起始时刻", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					this.ItemAdd("B相最近断相起始时刻", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					this.ItemAdd("C相最近断相起始时刻", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					this.ItemAdd("最近一次断相结束时刻", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					this.ItemAdd("A相最近断相结束时刻", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					this.ItemAdd("B相最近断相结束时刻", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					this.ItemAdd("C相最近断相结束时刻", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F33(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("三相总最大有功功率", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("三相总最大有功功率发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("A相最大有功功率", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("A相最大有功功率发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("B相最大有功功率", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("B相最大有功功率发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("C相最大有功功率", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("C相最大有功功率发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("三相总有功功率为零时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("A相有功功率为零时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("B相有功功率为零时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("C相有功功率为零时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F34(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("总有功最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("总有功最大需量发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("A相有功最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("A相有功最大需量发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("B相有功最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("B相有功最大需量发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("C相有功最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("C相有功最大需量发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F35(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("A相电压越上上限月累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("A相电压越下下限月累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("A相电压越上限月累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("A相电压越下限月累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("A相电压合格月累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("B相电压越上上限月累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("B相电压越下下限月累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("B相电压越上限月累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("B相电压越下限月累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("B相电压合格月累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("C相电压越上上限月累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("C相电压越下下限月累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("C相电压越上限月累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("C相电压越下限月累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("C相电压合格月累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("A相电压最大值", this.OperaRec(Value.Substring(num, 4), "A7"));
					num += 4;
					this.ItemAdd("A相电压最大值发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("A相电压最小值", this.OperaRec(Value.Substring(num, 4), "A7"));
					num += 4;
					this.ItemAdd("A相电压最小值发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("B相电压最大值", this.OperaRec(Value.Substring(num, 4), "A7"));
					num += 4;
					this.ItemAdd("B相电压最大值发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("B相电压最小值", this.OperaRec(Value.Substring(num, 4), "A7"));
					num += 4;
					this.ItemAdd("B相电压最小值发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("C相电压最大值", this.OperaRec(Value.Substring(num, 4), "A7"));
					num += 4;
					this.ItemAdd("C相电压最大值发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("C相电压最小值", this.OperaRec(Value.Substring(num, 4), "A7"));
					num += 4;
					this.ItemAdd("C相电压最小值发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("A相平均电压", this.OperaRec(Value.Substring(num, 4), "A7"));
					num += 4;
					this.ItemAdd("B相平均电压", this.OperaRec(Value.Substring(num, 4), "A7"));
					num += 4;
					this.ItemAdd("C相平均电压", this.OperaRec(Value.Substring(num, 4), "A7"));
					num += 4;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F36(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("电流不平衡度越限月累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("电压不平衡度越限月累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("电流不平衡最大值", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("电流不平衡最大值发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					this.ItemAdd("电压不平衡最大值", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("电压不平衡最大值发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F37(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("A相电流越上上限月累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("A相电流越上限月累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("B相电流越上上限月累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("B相电流越上限月累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("C相电流越上上限月累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("C相电流越上限月累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("零序电流越上限月累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("A相电流最大值", this.OperaRec(Value.Substring(num, 6), "A25"));
					num += 6;
					this.ItemAdd("A相电流最大值发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("B相电流最大值", this.OperaRec(Value.Substring(num, 6), "A25"));
					num += 6;
					this.ItemAdd("B相电流最大值发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("C相电流最大值", this.OperaRec(Value.Substring(num, 6), "A25"));
					num += 6;
					this.ItemAdd("C相电流最大值发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("零序电流最大值", this.OperaRec(Value.Substring(num, 6), "A25"));
					num += 6;
					this.ItemAdd("零序电流最大值发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F38(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("视在功率越上上限月累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("视在功率越上限月累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F39(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("负载率最大值", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("负载率最大值发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					this.ItemAdd("负载率最小值", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("负载率最小值发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F41(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					for (int i = 0; i < 9; i++)
					{
						this.ItemAdd("第" + (i + 1).ToString() + "组电容器累计投入时间", this.OperaRec(Value.Substring(num, 8), "BIN"));
						num += 8;
					}
					for (int i = 0; i < 9; i++)
					{
						this.ItemAdd("第" + (i + 1).ToString() + "组电容器累计投入次数", this.OperaRec(Value.Substring(num, 8), "BIN"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F42(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("日补偿的无功电能量", this.OperaRec(Value.Substring(num, 8), "A13"));
					num += 8;
					this.ItemAdd("月补偿的无功电能量", this.OperaRec(Value.Substring(num, 8), "A13"));
					num += 8;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F43(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("区段1累计时间(功率因数<定值1)", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("区段2累计时间(定值1≤功率因数<定值2)", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("区段3累计时间(功率因数≥定值2)", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F44(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("区段1累计时间(功率因数<定值1)", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("区段2累计时间(定值1≤功率因数<定值2)", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("区段3累计时间(功率因数≥定值2)", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F45(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("铜损有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					this.ItemAdd("铁损有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F46(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("铜损有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					this.ItemAdd("铁损有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F49(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端日供电时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("终端日复位累计次数", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F50(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("月电控跳闸日累计次数", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					this.ItemAdd("购电控跳闸日累计次数", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					this.ItemAdd("功控跳闸日累计次数", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					this.ItemAdd("遥控跳闸日累计次数", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F51(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端月供电时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("终端月复位累计次数", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F52(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("月电控跳闸月累计次数", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					this.ItemAdd("购电控跳闸日累计次数", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					this.ItemAdd("功控跳闸日累计次数", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					this.ItemAdd("遥控跳闸日累计次数", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F53(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端与主站日通信流量", this.OperaRec(Value.Substring(num, 8), "BIN"));
					num += 8;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F54(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端与主站日通信流量", this.OperaRec(Value.Substring(num, 8), "BIN"));
					num += 8;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F57(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("日最大有功功率", this.OperaRec(Value.Substring(num, 4), "A2"));
					num += 4;
					this.ItemAdd("日最大有功功率发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("日最有功小功率", this.OperaRec(Value.Substring(num, 4), "A2"));
					num += 4;
					this.ItemAdd("日最小有功功率发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("有功功率为零日累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F58(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("日累计总有功电能量", this.OperaRec(Value.Substring(num, 8), "A3"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "日累计有功电能量", this.OperaRec(Value.Substring(num, 8), "A3", "kWh/MWh"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F59(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("日累计总无功电能量", this.OperaRec(Value.Substring(num, 8), "A3", "kvarh/Mvarh"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "日累计无功电能量", this.OperaRec(Value.Substring(num, 8), "A3", "kvarh/Mvarh"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F60(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("月最大有功功率", this.OperaRec(Value.Substring(num, 4), "A2"));
					num += 4;
					this.ItemAdd("月最大有功功率发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("月最有功小功率", this.OperaRec(Value.Substring(num, 4), "A2"));
					num += 4;
					this.ItemAdd("月最小有功功率发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("月有功功率为零累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F61(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("月总有功电能量", this.OperaRec(Value.Substring(num, 8), "A3", "kWh/MWh"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "月有功电能量", this.OperaRec(Value.Substring(num, 8), "A3", "kWh/MWh"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F62(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("月总无功电能量", this.OperaRec(Value.Substring(num, 8), "A3", "kvarh/Mvarh"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "月无功电能量", this.OperaRec(Value.Substring(num, 8), "A3", "kvarh/Mvarh"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F65(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("超功率定值月累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("超功率定值的月累计电能量", this.OperaRec(Value.Substring(num, 8), "A3", "kWh/MWh"));
					num += 8;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F66(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("超月电能量定值月累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("超月冻结电能量定值的月累计电能量", this.OperaRec(Value.Substring(num, 8), "A3", "kWh/MWh"));
					num += 8;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F73(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("有功功率" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 4), "A2"));
						num += 4;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F74(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("无功功率" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 4), "A2"));
						num += 4;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F75(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("有功电能量" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 8), "A3", "kWh/MWh"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F76(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("无功电能" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 8), "A3", "kvarh/Mvarh"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F81(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("有功功率" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 6), "A9"));
						num += 6;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F82(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("有功功率" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 6), "A9"));
						num += 6;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F83(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("有功功率" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 6), "A9"));
						num += 6;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F84(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("有功功率" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 6), "A9"));
						num += 6;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F85(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("无功功率" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 6), "A9"));
						num += 6;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F86(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("无功功率" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 6), "A9"));
						num += 6;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F87(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("无功功率" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 6), "A9"));
						num += 6;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F88(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("无功功率" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 6), "A9"));
						num += 6;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F89(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("电压数据" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 4), "A7"));
						num += 4;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F90(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("电压数据" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 4), "A7"));
						num += 4;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F91(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("电压数据" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 4), "A7"));
						num += 4;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F92(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("电流数据" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 6), "A25"));
						num += 6;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F93(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("电流数据" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 6), "A25"));
						num += 6;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F94(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("电流数据" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 6), "A25"));
						num += 6;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F95(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("电流数据" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 6), "A25"));
						num += 6;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F97(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("有功电能量" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 8), "A13"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F98(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("无功电能量" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 8), "A13"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F99(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("有功电能量" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 8), "A13"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F100(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("无功电能量" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 8), "A13"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F101(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("电能示值" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F102(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("电能示值" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F103(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("电能示值" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F104(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("电能示值" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F105(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("功率因数" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 4), "A5"));
						num += 4;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F106(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("功率因数" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 4), "A5"));
						num += 4;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F107(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("功率因数" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 4), "A5"));
						num += 4;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F108(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("功率因数" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 4), "A5"));
						num += 4;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F109(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("Uab/Ua相位角" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 4), "A5"));
						num += 4;
						this.ItemAdd("Ub相位角" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 4), "A5"));
						num += 4;
						this.ItemAdd("Ucb/Uc相位角" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 4), "A5"));
						num += 4;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F110(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("Ia相位角" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 4), "A5"));
						num += 4;
						this.ItemAdd("Ib相位角" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 4), "A5"));
						num += 4;
						this.ItemAdd("Ic相位角" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 4), "A5"));
						num += 4;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F113(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					for (int i = 2; i < 19; i++)
					{
						this.ItemAdd("A相" + i.ToString() + "次谐波电流日最大值", this.OperaRec(Value.Substring(num, 4), "A6"));
						num += 4;
						this.ItemAdd("A相" + i.ToString() + "次谐波电流日最大值发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					this.ItemAdd("A相总畸变电流日最大值", this.OperaRec(Value.Substring(num, 4), "A6"));
					num += 4;
					this.ItemAdd("A相总畸变电流日最大值发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F114(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					for (int i = 2; i < 19; i++)
					{
						this.ItemAdd("B相" + i.ToString() + "次谐波电流日最大值", this.OperaRec(Value.Substring(num, 4), "A6"));
						num += 4;
						this.ItemAdd("B相" + i.ToString() + "次谐波电流日最大值发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					this.ItemAdd("B相总畸变电流日最大值", this.OperaRec(Value.Substring(num, 4), "A6"));
					num += 4;
					this.ItemAdd("B相总畸变电流日最大值发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F115(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					for (int i = 2; i < 19; i++)
					{
						this.ItemAdd("C相" + i.ToString() + "次谐波电流日最大值", this.OperaRec(Value.Substring(num, 4), "A6"));
						num += 4;
						this.ItemAdd("C相" + i.ToString() + "次谐波电流日最大值发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					this.ItemAdd("C相总畸变电流日最大值", this.OperaRec(Value.Substring(num, 4), "A6"));
					num += 4;
					this.ItemAdd("C相总畸变电流日最大值发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F116(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					for (int i = 2; i < 19; i++)
					{
						this.ItemAdd("A相" + i.ToString() + "次谐波电压含有率日最大值", this.OperaRec(Value.Substring(num, 4), "A5"));
						num += 4;
						this.ItemAdd("A相" + i.ToString() + "次谐波电压含有率日最大值发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					this.ItemAdd("A相总谐波电压含有率日最大值", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("A相总畸变电压含有率日最大值发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F117(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					for (int i = 2; i < 19; i++)
					{
						this.ItemAdd("B相" + i.ToString() + "次谐波电压含有率日最大值", this.OperaRec(Value.Substring(num, 4), "A5"));
						num += 4;
						this.ItemAdd("B相" + i.ToString() + "次谐波电压含有率日最大值发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					this.ItemAdd("B相总谐波电压含有率日最大值", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("B相总畸变电压含有率日最大值发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F118(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					for (int i = 2; i < 19; i++)
					{
						this.ItemAdd("C相" + i.ToString() + "次谐波电压含有率日最大值", this.OperaRec(Value.Substring(num, 4), "A5"));
						num += 4;
						this.ItemAdd("C相" + i.ToString() + "次谐波电压含有率日最大值发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					this.ItemAdd("C相总谐波电压含有率日最大值", this.OperaRec(Value.Substring(num, 4), "A5"));
					num += 4;
					this.ItemAdd("C相总畸变电压含有率日最大值发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F121(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("谐波次数", num2.ToString());
					num += 2;
					this.ItemAdd("A相总畸变电压含有率越限日累计时间", this.OperaRec(Value.Substring(num, 4), "BCD"));
					num += 4;
					for (int i = 2; i < 19; i++)
					{
						this.ItemAdd("A相" + (i + 1).ToString() + "次谐波电压含有率越限日累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
						num += 4;
					}
					this.ItemAdd("A相总畸变电流越限日累计时间", this.OperaRec(Value.Substring(num, 4), "BCD"));
					num += 4;
					for (int i = 2; i < num2; i++)
					{
						this.ItemAdd("A相" + (i + 1).ToString() + "次谐波电流越限日累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
						num += 4;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F122(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("谐波次数", num2.ToString());
					num += 2;
					this.ItemAdd("B相总畸变电压含有率越限日累计时间", this.OperaRec(Value.Substring(num, 4), "BCD"));
					num += 4;
					for (int i = 2; i < 19; i++)
					{
						this.ItemAdd("B相" + (i + 1).ToString() + "次谐波电压含有率越限日累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
						num += 4;
					}
					this.ItemAdd("B相总畸变电流越限日累计时间", this.OperaRec(Value.Substring(num, 4), "BCD"));
					num += 4;
					for (int i = 2; i < num2; i++)
					{
						this.ItemAdd("B相" + (i + 1).ToString() + "次谐波电流越限日累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
						num += 4;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F123(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("谐波次数", num2.ToString());
					num += 2;
					this.ItemAdd("C相总畸变电压含有率越限日累计时间", this.OperaRec(Value.Substring(num, 4), "BCD"));
					num += 4;
					for (int i = 2; i < 19; i++)
					{
						this.ItemAdd("C相" + (i + 1).ToString() + "次谐波电压含有率越限日累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
						num += 4;
					}
					this.ItemAdd("C相总畸变电流越限日累计时间", this.OperaRec(Value.Substring(num, 4), "BCD"));
					num += 4;
					for (int i = 2; i < num2; i++)
					{
						this.ItemAdd("C相" + (i + 1).ToString() + "次谐波电流越限日累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
						num += 4;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F129(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("直流模拟量越上限日累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("直流模拟量越下限日累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("直流模拟量日最大值", this.OperaRec(Value.Substring(num, 4), "A2"));
					num += 4;
					this.ItemAdd("直流模拟量日最大值发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("直流模拟量日最小值", this.OperaRec(Value.Substring(num, 4), "A2"));
					num += 4;
					this.ItemAdd("直流模拟量日最小值发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F130(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("直流模拟量越上限月累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("直流模拟量越下限月累计时间", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					this.ItemAdd("直流模拟量月最大值", this.OperaRec(Value.Substring(num, 4), "A2"));
					num += 4;
					this.ItemAdd("直流模拟量月最大值发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					this.ItemAdd("直流模拟量月最小值", this.OperaRec(Value.Substring(num, 4), "A2"));
					num += 4;
					this.ItemAdd("直流模拟量月最小值发生时间", this.OperaRec(Value.Substring(num, 6), "A18"));
					num += 6;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F138(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("直流模拟量冻结数据" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 4), "A2"));
						num += 4;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F145(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("电能示值" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F146(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("电能示值" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F147(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("电能示值" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F148(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("电能示值" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F152(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					int num3 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num3.ToString());
					num += 2;
					this.ItemAdd("正向有功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 1; i <= num3; i++)
					{
						this.ItemAdd("费率" + i.ToString() + "正向有功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					this.ItemAdd("抄表是否成功标志", (this.OperaRec(Value.Substring(num, 2), "BIN") == "1") ? "不成功" : "成功");
					num += 2;
					this.ItemAdd("抄表轮数", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F153(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					this.ItemAdd("A相正向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					this.ItemAdd("B相正向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					this.ItemAdd("C相正向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F154(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					this.ItemAdd("A相正向无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					this.ItemAdd("B相正向无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					this.ItemAdd("C相正向无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F155(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					this.ItemAdd("A相反向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					this.ItemAdd("B相反向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					this.ItemAdd("C相反向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F156(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					this.ItemAdd("A相反向无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					this.ItemAdd("B相反向无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					this.ItemAdd("C相反向无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F157(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					this.ItemAdd("A相正向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					this.ItemAdd("B相正向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					this.ItemAdd("C相正向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F158(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					this.ItemAdd("A相正向无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					this.ItemAdd("B相正向无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					this.ItemAdd("C相正向无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F159(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					this.ItemAdd("A相反向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					this.ItemAdd("B相反向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					this.ItemAdd("C相反向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F160(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					this.ItemAdd("A相反向无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					this.ItemAdd("B相反向无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					this.ItemAdd("C相反向无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F161(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F162(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向无功(组合无功1)总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向无功(组合无功1)电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F163(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("反向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F164(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("反向无功(组合无功1)总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向无功(组合无功1)电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F165(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("一象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "一象限无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F166(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("二象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "二象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F167(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("三象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "三象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F168(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("四象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "四象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F169(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					this.ItemAdd("A相正向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					this.ItemAdd("B相正向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					this.ItemAdd("C相正向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F170(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("抄表日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向无功(组合无功1)总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向无功(组合无功1)电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F171(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("抄表日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("反向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F172(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("抄表日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("反向无功(组合无功1)总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向无功(组合无功1)电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F173(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("抄表日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("一象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "一象限无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F174(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("抄表日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("二象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "二象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F175(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("抄表日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("三象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "三象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F176(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("抄表日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("四象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "四象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F177(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F178(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向无功(组合无功1)总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向无功(组合无功1)电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F179(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("反向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F180(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("反向无功(组合无功1)总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向无功(组合无功1)电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F181(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("一象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "一象限无功电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F182(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("二象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "二象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F183(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("三象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "三象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F184(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("四象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "四象限无功总电能示值", this.OperaRec(Value.Substring(num, 8), "A11"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F185(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向有功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("正向有功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F186(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("正向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
						this.ItemAdd("费率" + (i + 1).ToString() + "正向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F187(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("反向有功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("反向有功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向有功最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
						this.ItemAdd("费率" + (i + 1).ToString() + "反向有功最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F188(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("反向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("反向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
						this.ItemAdd("费率" + (i + 1).ToString() + "反向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F189(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("抄表日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向有功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("正向有功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F190(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("抄表日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("正向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
						this.ItemAdd("费率" + (i + 1).ToString() + "正向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F191(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("抄表日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("反向有功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("反向有功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向有功最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
						this.ItemAdd("费率" + (i + 1).ToString() + "反向有功最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F192(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("抄表日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("反向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("反向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
						this.ItemAdd("费率" + (i + 1).ToString() + "反向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F193(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向有功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("正向有功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F194(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("正向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
						this.ItemAdd("费率" + (i + 1).ToString() + "正向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F195(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("反向有功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("反向有功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向有功最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
						this.ItemAdd("费率" + (i + 1).ToString() + "反向有功最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F196(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("反向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
					num += 6;
					this.ItemAdd("反向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
					num += 8;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "反向无功总最大需量", this.OperaRec(Value.Substring(num, 6), "A23"));
						num += 6;
						this.ItemAdd("费率" + (i + 1).ToString() + "反向无功总最大需量发生时间", this.OperaRec(Value.Substring(num, 8), "A17"));
						num += 8;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F201(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F202(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F203(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F204(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F205(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F206(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F207(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F208(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("正向有功总电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("费率" + (i + 1).ToString() + "正向有功电能示值", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F209(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("日冻结类数据时标", this.OperaRec(Value.Substring(num, 6), "Td_d"));
					num += 6;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("电能表通断电状态", (num2 == 0) ? "断电" : "通电");
					num += 2;
					this.ItemAdd("最近一次电能表远程控制通电时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					this.ItemAdd("最近一次电能表远程控制断电时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F213(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					this.ItemAdd("编程开关操作次数", this.OperaRec(Value.Substring(num, 4), "A8"));
					num += 4;
					this.ItemAdd("最近一次编程开关操作时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					this.ItemAdd("电能表尾盖打开次数", this.OperaRec(Value.Substring(num, 4), "A8"));
					num += 4;
					this.ItemAdd("最近一次尾盖打开时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F214(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					this.ItemAdd("电能表时钟修改次数", this.OperaRec(Value.Substring(num, 4), "A8"));
					num += 4;
					this.ItemAdd("电能表最近一次时钟修改时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					this.ItemAdd("电能表时段参数修改次数", this.OperaRec(Value.Substring(num, 4), "A8"));
					num += 4;
					this.ItemAdd("最近一次电能表时段参数修改时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F215(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					this.ItemAdd("购电次数", this.OperaRec(Value.Substring(num, 4), "A8"));
					num += 4;
					this.ItemAdd("剩余金额", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					this.ItemAdd("累计购电金额", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					this.ItemAdd("剩余电量", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					this.ItemAdd("透支电量", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					this.ItemAdd("累计购电量", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					this.ItemAdd("赊欠门限电量", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					this.ItemAdd("报警电量", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					this.ItemAdd("故障电量", this.OperaRec(Value.Substring(num, 8), "A11"));
					num += 8;
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F216(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("月冻结类数据时标", this.OperaRec(Value.Substring(num, 4), "Td_m"));
					num += 4;
					this.ItemAdd("终端抄表时间", this.OperaRec(Value.Substring(num, 10), "A15"));
					num += 10;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("费率数", num2.ToString());
					num += 2;
					this.ItemAdd("已结有功总电能", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("已结费率" + (i + 1).ToString() + "正向有功总电能", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					this.ItemAdd("未结有功总电能", this.OperaRec(Value.Substring(num, 10), "A14"));
					num += 10;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("未结费率" + (i + 1).ToString() + "正向有功总电能", this.OperaRec(Value.Substring(num, 10), "A14"));
						num += 10;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F217(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("噪声比值" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 2), "BIN"));
						num += 2;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0D_F218(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					int num2 = 0;
					this.ItemAdd("曲线类数据时标", this.Td_c(Value.Substring(num, 14), ref num2));
					num += 14;
					for (int i = 0; i < num2; i++)
					{
						this.ItemAdd("噪声比值" + (i + 1).ToString(), this.OperaRec(Value.Substring(num, 2), "BIN"));
						num += 2;
						this.ItemAdd("对应噪声比值" + (i + 1).ToString() + "的主节点地址", this.OperaRec(Value.Substring(num, 12), "A12"));
						num += 12;
					}
					result = num;
				}
				return result;
			}
		}
		private int AF0E_F1(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("当前重要事件计数器EC1", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					this.ItemAdd("当前一般事件计数器EC2", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("本帧报文传送的事件记录起始指针Pm", num2.ToString());
					num += 2;
					int num3 = DataConvert.HexToInt(Value.Substring(num, 2));
					this.ItemAdd("本帧报文传送的事件记录结束指针Pn", num3.ToString());
					num += 2;
					int num4;
					if (num2 <= num3)
					{
						num4 = num3 - num2;
					}
					else
					{
						num4 = 256 + num2 - num3;
					}
					for (int i = 0; i <= num4; i++)
					{
						int num5 = 0;
						string empty = string.Empty;
						string values = this.DoERC(Value.Substring(num), ref num5, ref empty);
						this.ItemAdd("事件记录:[" + empty + "]", values);
						num += 2 * (num5 + 2);
						if (num >= Value.Length - 1)
						{
							break;
						}
					}
					result = num;
				}
				return result;
			}
		}
		private int AF10_F1(string Value, string format)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端通信端口号", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					this.ItemAdd("透明转发内容字节数", this.OperaRec(Value.Substring(num, 4), "BIN"));
					num += 4;
					string text = this.DataClass(Value.Substring(num));
					num += Value.Length - num;
					this.ItemAdd("透明转发内容", text);
					this.DataFormat(text, format);
					result = num;
				}
				return result;
			}
		}
		private int AF10_F9(string Value, string format)
		{
			this.AF10_F9_Val = string.Empty;
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端通信端口号", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					this.ItemAdd("转发目标地址", this.OperaRec(Value.Substring(num, 12), "A12"));
					num += 12;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					num += 2;
					switch (num2)
					{
					case 0:
						this.ItemAdd("转发结果标志", "不能执行转发");
						break;

					case 1:
						this.ItemAdd("转发结果标志", "转发接收超时");
						break;

					case 2:
						this.ItemAdd("转发结果标志", "转发接收错误");
						break;

					case 3:
						this.ItemAdd("转发结果标志", "转发接收确认");
						break;

					case 4:
						this.ItemAdd("转发结果标志", "转发接收否认");
						break;

					case 5:
						this.ItemAdd("转发结果标志", "转发接收数据");
						break;

					default:
						this.ItemAdd("转发结果标志", "无效");
						break;
					}
					num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					num += 2;
					this.ItemAdd("转发直接抄读的数据内容字节数", (num2 - 2).ToString());
					this.ItemAdd("转发直接抄读的数据标识", this.OperaRec(Value.Substring(num, 8), "BCD"));
					num += 8;
					string neirong = Value.Substring(num);
					num += Value.Length - num;
					this.ItemAdd("转发直接抄读的数据内容", Value.Substring(num));
					this.DataFormat(neirong, format);
					result = num;
				}
				return result;
			}
		}
		private int AF10_F10(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端通信端口号", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					this.ItemAdd("转发目标地址", this.OperaRec(Value.Substring(num, 12), "A12"));
					num += 12;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					num += 2;
					switch (num2)
					{
					case 0:
						this.ItemAdd("转发结果标志", "不能执行转发");
						break;

					case 1:
						this.ItemAdd("转发结果标志", "转发接收超时");
						break;

					case 2:
						this.ItemAdd("转发结果标志", "转发接收错误");
						break;

					case 3:
						this.ItemAdd("转发结果标志", "转发接收确认");
						break;

					case 4:
						this.ItemAdd("转发结果标志", "转发接收否认");
						break;

					case 5:
						this.ItemAdd("转发结果标志", "转发接收数据");
						break;

					default:
						this.ItemAdd("转发结果标志", "无效");
						break;
					}
					string a = this.OperaRec(Value.Substring(num, 2), "BIN");
					num += 2;
					this.ItemAdd("遥控跳闸/允许合闸标志", (a == "55") ? "允许合闸" : "跳闸");
					result = num;
				}
				return result;
			}
		}
		private int AF10_F11(string Value)
		{
			checked
			{
				int result;
				if (string.IsNullOrEmpty(Value))
				{
					result = 0;
				}
				else
				{
					int num = 0;
					this.ItemAdd("终端通信端口号", this.OperaRec(Value.Substring(num, 2), "BIN"));
					num += 2;
					this.ItemAdd("转发目标地址", this.OperaRec(Value.Substring(num, 12), "A12"));
					num += 12;
					int num2 = DataConvert.HexToInt(Value.Substring(num, 2));
					num += 2;
					switch (num2)
					{
					case 0:
						this.ItemAdd("转发结果标志", "不能执行转发");
						break;

					case 1:
						this.ItemAdd("转发结果标志", "转发接收超时");
						break;

					case 2:
						this.ItemAdd("转发结果标志", "转发接收错误");
						break;

					case 3:
						this.ItemAdd("转发结果标志", "转发接收确认");
						break;

					case 4:
						this.ItemAdd("转发结果标志", "转发接收否认");
						break;

					case 5:
						this.ItemAdd("转发结果标志", "转发接收数据");
						break;

					default:
						this.ItemAdd("转发结果标志", "无效");
						break;
					}
					string a = this.OperaRec(Value.Substring(num, 2), "BIN");
					this.ItemAdd("遥控送电标志", (a == "FF") ? "遥控送电" : "无效");
					result = num;
				}
				return result;
			}
		}
		private string DataClass(string strRecvData)
		{
			byte[] array = new byte[strRecvData.Length / 2];
			checked
			{
				for (int i = 0; i < array.Length; i++)
				{
					array[i] = byte.Parse(strRecvData.Substring(i * 2, 2), NumberStyles.HexNumber);
				}
				int j;
				for (j = 0; j < array.Length; j++)
				{
					if (array[j] == 104)
					{
						break;
					}
				}
				int num = (int)array[j + 9];
				return strRecvData.Substring((10 + j) * 2, num * 2);
			}
		}
		private string DataReversal(string strValue)
		{
			string hexChar = string.Empty;
			string text = string.Empty;
			checked
			{
				for (int i = 0; i < strValue.Length / 2; i++)
				{
					hexChar = strValue.Substring(i * 2, 2);
					text = this.Minus33H((byte)DataConvert.HexToInt(hexChar)).ToString("X2") + text;
				}
				return text;
			}
		}
		private byte Plus33H(byte mbyte)
		{
            return (byte)checked((mbyte + 51 > 255) ? (mbyte + 51 & 255) : (mbyte + 51));
		}
		private byte Minus33H(byte mbyte)
		{
            return (byte)checked((mbyte >= 51) ? (mbyte - 51) : (mbyte + 255 + 1 - 51));
		}
		private void DataFormat(string neirong, string format)
		{
			string text = this.FormatUserData(neirong, format);
			string empty = string.Empty;
			char c;
			if (format.Split(new char[]
			{
				'^'
			}).Length > 1)
			{
				string[] array = format.Split(new char[]
				{
					'^'
				});
				c = '^';
			}
			else
			{
				if (format.Split(new char[]
				{
					'~'
				}).Length > 1)
				{
					string[] array = format.Split(new char[]
					{
						'^'
					});
					c = '~';
				}
				else
				{
					string[] array = format.Split(new char[]
					{
						'\\'
					});
					c = '\\';
				}
			}
			string[] array2 = text.Split(new char[]
			{
				c
			});
			checked
			{
				for (int i = 0; i < array2.Length; i++)
				{
					if (!string.IsNullOrEmpty(array2[i]))
					{
						this.ItemAdd("数据内容" + (i + 1).ToString(), array2[i]);
					}
				}
				this.AF10_F9_Val = text;
			}
		}
		private string FormatUserData(string userdata, string MeterDataFormat)
		{
			string result = string.Empty;
			string text = string.Empty;
			checked
			{
				if (userdata.IndexOf("Error") < 0)
				{
					if (!this.AssertBlockData(MeterDataFormat))
					{
						string text2 = DataConvert.ReverseStr(userdata);
						int specialStrNum = PubFuncHelper.GetSpecialStrNum(MeterDataFormat);
						if (specialStrNum == 0)
						{
							text = text2;
						}
						else
						{
							if (specialStrNum > 0 && text2.Length == MeterDataFormat.Length - specialStrNum)
							{
								text = "";
								int num = 0;
								for (int i = 0; i < MeterDataFormat.Length; i++)
								{
									string text3 = MeterDataFormat.Substring(i, 1);
									if (PubFuncHelper.IsNumOrStr(text3))
									{
										text += text2.Substring(num, 1);
										num++;
									}
									else
									{
										text += text3;
									}
								}
							}
							else
							{
								if (specialStrNum > 0 && text2.Length % (MeterDataFormat.Length - specialStrNum) == 0)
								{
									int num2 = text2.Length / (MeterDataFormat.Length - specialStrNum);
									string text4 = "";
									for (int i = 0; i < num2; i++)
									{
										text4 = text4 + MeterDataFormat + " ";
									}
									MeterDataFormat = text4;
									text = "";
									int num = 0;
									for (int i = 0; i < MeterDataFormat.Length; i++)
									{
										string text3 = MeterDataFormat.Substring(i, 1);
										if (PubFuncHelper.IsNumOrStr(text3))
										{
											text += text2.Substring(num, 1);
											num++;
										}
										else
										{
											text += text3;
										}
									}
								}
								else
								{
									text = text2;
								}
							}
						}
					}
					else
					{
						text = this.OperBlockData(userdata, MeterDataFormat);
					}
					result = text;
				}
				else
				{
					result = userdata;
				}
				return result;
			}
		}
		private bool AssertBlockData(string datamformat)
		{
			return datamformat.Split(new char[]
			{
				'^'
			}).Length > 1 | datamformat.Split(new char[]
			{
				'~'
			}).Length > 1 | datamformat.Split(new char[]
			{
				'\\'
			}).Length > 1;
		}
		public string OperBlockData(string data, string dataformat)
		{
			string text = string.Empty;
			string text2 = string.Empty;
			string[] array;
			if (dataformat.Split(new char[]
			{
				'^'
			}).Length > 1)
			{
				array = dataformat.Split(new char[]
				{
					'^'
				});
				text2 = "^";
			}
			else
			{
				if (dataformat.Split(new char[]
				{
					'~'
				}).Length > 1)
				{
					array = dataformat.Split(new char[]
					{
						'^'
					});
					text2 = "~";
				}
				else
				{
					array = dataformat.Split(new char[]
					{
						'\\'
					});
					text2 = "\\";
				}
			}
			int num = array.Length;
			int num2 = 0;
			checked
			{
				for (int i = num - 1; i >= 0; i--)
				{
					int specialStrNum = PubFuncHelper.GetSpecialStrNum(array[i]);
					int length = array[i].ToString().Length;
					int num3 = length - specialStrNum;
					string text3 = string.Empty;
					try
					{
						text3 = DataConvert.ReverseStr(data.Substring(num2, num3));
					}
					catch
					{
					}
					num2 += num3;
					string str = string.Empty;
					if (!string.IsNullOrEmpty(text3))
					{
						if (!this.AssertBlockData(array[i]))
						{
							str = PubFuncHelper.StringFormat_NextFrame(text3, array[i]);
						}
						else
						{
							str = this.OperBlockData(text3, array[i]);
						}
						text = str + text;
						if (i != 0)
						{
							text = text2 + text;
						}
					}
					else
					{
						if (text2 == "^" | text2 == "~")
						{
							str = "无数据项";
						}
						else
						{
							str = "";
						}
						text = str + text;
						if (i != 0)
						{
							if (text2 == "^" | text2 == "~")
							{
								text = text2 + text;
							}
							else
							{
								text = (text ?? "");
							}
						}
					}
				}
				return text;
			}
		}
		public int CustomizeAnalysis(string Items, string Value)
		{
			string[] array = Items.Split(new char[]
			{
				'|'
			});
			int num = 0;
			checked
			{
				for (int i = 0; i < array.Length; i++)
				{
					string[] array2 = array[i].Split(new char[]
					{
						','
					});
					if (array2.Length > 1)
					{
						string type = array2[1].Trim().ToUpper();
						int num2 = int.Parse(array2[2]);
						string value = Value.Substring(num, num2 * 2);
						num += num2 * 2;
						this.ItemAdd(array2[0], this.OperaRec(value, type));
					}
				}
				return num;
			}
		}
	}
}
