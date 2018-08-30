namespace GB698Cls
{
    using System;
    using System.Collections.Generic;
    using System.Drawing;
    using System.Runtime.InteropServices;

    public class LogMSG
    {
        public static List<MSGInfo> gMSGInfo = new List<MSGInfo>();

        public static void AddInfo(string info, int color)
        {
            MSGInfo item = new MSGInfo();
            item.Msg = info;
            switch (color)
            {
                case 1:
                    item.cor = Color.Blue;
                    break;

                case 2:
                    item.cor = Color.Red;
                    break;

                case 3:
                    item.cor = Color.DarkGreen;
                    break;

                case 4:
                    item.cor = Color.DarkOrange;
                    break;

                case 5:
                    item.cor = Color.DarkViolet;
                    break;

                case 6:
                    item.cor = Color.MediumSlateBlue;
                    break;

                case 7:
                    item.cor = Color.CornflowerBlue;
                    break;

                default:
                    item.cor = Color.FromArgb(0x17, 0x17, 0x17);
                    break;
            }
            gMSGInfo.Add(item);
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct MSGInfo
        {
            public string Msg;
            public Color cor;
        }
    }
}

