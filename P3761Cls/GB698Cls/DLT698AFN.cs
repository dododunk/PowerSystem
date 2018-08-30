using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GB698Cls
{

    /* 00H	确认∕否认
01H	复位
02H	链路接口检测
03H	中继站命令
04H	设置参数
05H	控制命令
06H	身份认证及密钥协商
07H	备用
08H	请求被级联终端主动上报
09H	请求终端配置
    表5（续）
0AH	查询参数
0BH	请求任务数据
0CH	请求1类数据（实时数据）
0DH	请求2类数据（历史数据）
0EH	请求3类数据（事件数据）
0FH	文件传输
10H	数据转发
11H～FFH	备用*/
    /// <summary>
    /// 应用功能码
    /// </summary>
    public class AFN
    {
        static public readonly string 确认_否认 = "00";
        static public readonly string 复位 = "01";
        static public readonly string 链路接口检测 = "02";
        static public readonly string 中继站命令 = "03";
        static public readonly string 设置参数 = "04";
        static public readonly string 控制命令 = "05";
        static public readonly string 身份认证及密钥协商 = "06";
        static public readonly string 备用 = "07";
        static public readonly string 请求被级联终端主动上报 = "08";
        static public readonly string 请求终端配置 = "09";
        static public readonly string 查询参数 = "0A";
        static public readonly string 请求任务数据 = "0B";
        static public readonly string 请求1类数据_实时数据 = "0C";
        static public readonly string 请求2类数据_历史数据 = "0D";
        static public readonly string 请求3类数据_事件数据 = "0E";
        static public readonly string 文件传输 = "0F";
        static public readonly string 数据转发 = "10";
    }
}
