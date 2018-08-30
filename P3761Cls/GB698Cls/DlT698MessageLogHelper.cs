using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Helper;
using System.Globalization;

namespace GB698Cls.GB698Cls
{
   public class DlT698MessageLogHelper
    {
        public static string Print_FnPnData(DLT698Message.FrameInfo gFrame)
        {
            string text = string.Empty;
            if (gFrame.AFN == "00")
            {
                if (gFrame.PN == "0000")
                {
                    if (gFrame.FN == "0001")
                    {
                        text += "全部确认";
                    }
                    if (gFrame.FN == "0002")
                    {
                        text += "全部否认";
                    }
                    if (gFrame.FN == "0003")
                    {
                        text = text + "部分确认:" + gFrame.Data;
                    }
                    if (gFrame.FN == "0008")
                    {
                        text += "否认:终端不存在";
                    }
                    if (gFrame.FN == "0009")
                    {
                        text += gFrame.Data;
                    }
                }
            }
            return text;
        }










        public  static string Print_GetControlField(string strValue)
        {
            string str = string.Empty;
            byte b = checked((byte)DataConvert.HexToInt(strValue));
            str = string.Concat(new string[]
			{
				"控制域C [",
				strValue,
				"]-->\r\nDIR=",
				(b >> 7 & 1).ToString("0"),
				"\r\n"
			});
            str = str + "PRM=" + (b >> 6 & 1).ToString("0") + "\r\n";
            str = str + "FCB=" + (b >> 5 & 1).ToString("0") + "\r\n";
            str = str + "FCV=" + (b >> 4 & 1).ToString("0") + "\r\n";
            return str + "CID=" + ((int)(b & 15)).ToString() + "\r\n";
        }
        public static string Print_GetAddressField(string strValue)
        {
            string text = string.Empty;
            byte b = checked((byte)DataConvert.HexToInt(strValue.Substring(8, 2)));
            text = string.Concat(new string[]
			{
				"行政区划码A1 [",
				strValue.Substring(0, 4),
				"]-->",
				strValue.Substring(2, 2),
				strValue.Substring(0, 2),
				"\r\n"
			});
            string text2 = text;
            text = string.Concat(new string[]
			{
				text2,
				"终端地址A2 [",
				strValue.Substring(4, 4),
				"]-->",
				ushort.Parse(strValue.Substring(6, 2) + strValue.Substring(4, 2), NumberStyles.HexNumber).ToString(),
				"\r\n"
			});
            text2 = text;
            return string.Concat(new string[]
			{
				text2,
				"主站地址和标志A3 [",
				strValue.Substring(8, 2),
				"]-->\r\n主站地址:",
				(b >> 1 & 127).ToString(),
				"\r\n组标志:",
				((int)(b & 1)).ToString(),
				"\r\n"
			});
        }
        public static string Print_GetAppCode(string strValue)
        {
            return string.Concat(new string[]
			{
				"应用层功能码 [",
				strValue,
				"]-->",
				DataConvert.HexToInt(strValue).ToString(),
				"\r\n"
			});
        }
        public static string Print_GetSEQ(string strValue)
        {
            string str = string.Empty;
            byte b = checked((byte)DataConvert.HexToInt(strValue));
            str = "帧序列域 [" + strValue + "]-->\r\n";
            str = str + "TpV=" + (b >> 7 & 1).ToString() + "\r\n";
            str = str + "FIR=" + (b >> 6 & 1).ToString() + "\r\n";
            str = str + "FIN=" + (b >> 5 & 1).ToString() + "\r\n";
            str = str + "CON=" + (b >> 4 & 1).ToString() + "\r\n";
            return str + "PSEQ∕RSEQ=" + ((int)(b & 15)).ToString() + "\r\n";
        }










        public static string Print_GetDataCellMark(string strValue)
        {
            string text = string.Empty;
            text = string.Concat(new string[]
			{
				"数据单元标识:[",
				strValue.Substring(0, 2),
				" ",
				strValue.Substring(2, 2),
				" ",
				strValue.Substring(4, 2),
				" ",
				strValue.Substring(6, 2),
				"]-->\r\n"
			});
            string text2 = text;
            text = string.Concat(new string[]
			{
				text2,
				"[",
				strValue.Substring(6, 2),
				" ",
				strValue.Substring(4, 2),
				"]-->FN:",
				DLT698Message.FNToDec(strValue.Substring(4, 4)),
				"\r\n"
			});
            text2 = text;
            return string.Concat(new string[]
			{
				text2,
				"[",
				strValue.Substring(2, 2),
				" ",
				strValue.Substring(0, 2),
				"]-->PN:",
				DLT698Message.PNToDec(strValue.Substring(0, 4)),
				"\r\n"
			});
        }
        public static string Print_ShowFrameInfo(DLT698Message.FrameInfo gFrame,DLT698Message msg)
        {
            string text = "起始字符:[68]\r\n";
            string text2 = text;
            text = string.Concat(new string[]
			{
				text2,
				"长度L:[",
				DLT698Message.GetDataLenSpace(gFrame.L1),
				"]-->",
				gFrame.L1,
				"\r\n"
			});
            text += "起始字符:[68]\r\n";
            string controlField = DLT698Message.GetControlField(byte.Parse(gFrame.DIR), byte.Parse(gFrame.PRM), byte.Parse(gFrame.FCB), byte.Parse(gFrame.FCV), byte.Parse(gFrame.CID));
            text += DlT698MessageLogHelper.Print_GetControlField(controlField);
            string addressField = DLT698Message.GetAddressField(gFrame.A1, gFrame.A2, gFrame.MSA, byte.Parse(gFrame.ArrFlag));
            text += DlT698MessageLogHelper.Print_GetAddressField(addressField);
            string appCode = DlT698MessageLogHelper.Print_GetAppCode(gFrame.AFN);
            text += appCode;
            string sEQ = DLT698Message.GetSEQ(byte.Parse(gFrame.TpV), byte.Parse(gFrame.FIR), byte.Parse(gFrame.FIN), byte.Parse(gFrame.CON), byte.Parse(gFrame.PSEQ));
            text += DlT698MessageLogHelper.Print_GetSEQ(sEQ);
            if (!string.IsNullOrEmpty(gFrame.FN) | !string.IsNullOrEmpty(gFrame.PN))
            {
                string dataCellMark = DLT698Message.GetDataCellMark(ushort.Parse(gFrame.FN), ushort.Parse(gFrame.PN));
                text += Print_GetDataCellMark(dataCellMark);
            }
            text += "数据部分:\r\n";
            if (!string.IsNullOrEmpty(gFrame.PW))
            {
                text2 = text;
                text = string.Concat(new string[]
				{
					text2,
					"密码PW:[",
					gFrame.PW,
					"]-->",
					gFrame.PW,
					"\r\n"
				});
            }
            if (!string.IsNullOrEmpty(gFrame.EC1))
            {
                text2 = text;
                text = string.Concat(new string[]
				{
					text2,
					"重要事件计数器EC1:[",
					gFrame.EC1,
					"]-->",
					DataConvert.HexToInt(gFrame.EC1).ToString(),
					"\r\n"
				});
            }
            if (!string.IsNullOrEmpty(gFrame.EC2))
            {
                text2 = text;
                text = string.Concat(new string[]
				{
					text2,
					"重要事件计数器EC2:[",
					gFrame.EC2,
					"]-->",
					DataConvert.HexToInt(gFrame.EC2).ToString(),
					"\r\n"
				});
            }
            if (gFrame.TpV == "1")
            {
                text2 = text;
                text = string.Concat(new string[]
				{
					text2,
					"启动帧帧序号计数器PFC:[",
					int.Parse(gFrame.PFC).ToString("X2"),
					"]-->",
					gFrame.PFC,
					"\r\n"
				});
                text2 = text;
                text = string.Concat(new string[]
				{
					text2,
					"启动帧发送时标:[",
					DataConvert.AddSpace(DataConvert.ReverseStr(gFrame.Time)),
					"]-->",
					gFrame.Time.Substring(0, 2),
					"日",
					gFrame.Time.Substring(2, 2),
					"时",
					gFrame.Time.Substring(4, 2),
					"分",
					gFrame.Time.Substring(6, 2),
					"秒\r\n"
				});
                text2 = text;
                text = string.Concat(new string[]
				{
					text2,
					"允许发送传输延时时间:[",
					int.Parse(gFrame.Delay).ToString("X2"),
					"]-->",
					gFrame.Delay,
					"\r\n"
				});
            }
            if (!string.IsNullOrEmpty(gFrame.Data))
            {
                text = text + "数据:[" + gFrame.Data + "]\r\n";
            }
            text = text + "校验:[" + gFrame.CS + "]\r\n";
            return text + "结束符:[16]\r\n";
        }
    }
}
