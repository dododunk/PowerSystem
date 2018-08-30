using System;
using System.Runtime.InteropServices;
namespace GB698Cls
{
    /// <summary>
    /// COMM串口通讯
    /// </summary>
	public class SerialPort
	{
		private struct DCB
		{
			public int DCBlength;
			public int BaudRate;
			public int fBinary;
			public int fParity;
			public int fOutxCtsFlow;
			public int fOutxDsrFlow;
			public int fDtrControl;
			public int fDsrSensitivity;
			public int fTXContinueOnXoff;
			public int fOutX;
			public int fInX;
			public int fErrorChar;
			public int fNull;
			public int fRtsControl;
			public int fAbortOnError;
			public int fDummy2;
			public ushort wReserved;
			public ushort XonLim;
			public ushort XoffLim;
			public byte ByteSize;
			public byte Parity;
			public byte StopBits;
			public char XonChar;
			public char XoffChar;
			public char ErrorChar;
			public char EofChar;
			public char EvtChar;
			public ushort wReserved1;
		}
		private struct COMMTIMEOUTS
		{
			public int ReadIntervalTimeout;
			public int ReadTotalTimeoutMultiplier;
			public int ReadTotalTimeoutConstant;
			public int WriteTotalTimeoutMultiplier;
			public int WriteTotalTimeoutConstant;
		}
		private struct OVERLAPPED
		{
			public int Internal;
			public int InternalHigh;
			public int Offset;
			public int OffsetHigh;
			public int hEvent;
		}
		private const uint GENERIC_READ = 2147483648u;
		private const uint GENERIC_WRITE = 1073741824u;
		private const int OPEN_EXISTING = 3;
		private const int INVALID_HANDLE_VALUE = -1;
		private int hComm = -1;
		private int retval = -1;
		public bool Opened = false;
		public int PortNum;
		public string ComSettings;
		public int ReadTimeout = 1000;
		public int WriteTimeout = 250;
		[DllImport("kernel32.dll")]
		private static extern int CreateFile(string lpFileName, uint dwDesiredAccess, int dwShareMode, int lpSecurityAttributes, int dwCreationDisposition, int dwFlagsAndAttributes, int hTemplateFile);
		[DllImport("kernel32.dll")]
		private static extern int GetCommState(int hFile, ref SerialPort.DCB lpDCB);
		[DllImport("kernel32.dll")]
		private static extern int BuildCommDCB(string lpDef, ref SerialPort.DCB lpDCB);
		[DllImport("kernel32.dll")]
		private static extern int SetCommState(int hFile, ref SerialPort.DCB lpDCB);
		[DllImport("kernel32.dll")]
		private static extern int GetCommTimeouts(int hFile, ref SerialPort.COMMTIMEOUTS lpCommTimeouts);
		[DllImport("kernel32.dll")]
		private static extern int SetCommTimeouts(int hFile, ref SerialPort.COMMTIMEOUTS lpCommTimeouts);
		[DllImport("kernel32.dll")]
		private static extern int ReadFile(int hFile, byte[] lpBuffer, int nNumberOfBytesToRead, ref int lpNumberOfBytesRead, ref SerialPort.OVERLAPPED lpOverlapped);
		[DllImport("kernel32.dll")]
		private static extern int WriteFile(int hFile, byte[] lpBuffer, int nNumberOfBytesToWrite, ref int lpNumberOfBytesWritten, ref SerialPort.OVERLAPPED lpOverlapped);
		[DllImport("kernel32.dll")]
		private static extern int CloseHandle(int hObject);
		[DllImport("kernel32.dll")]
		private static extern int FlushFileBuffers(int hFile);
		public bool Open()
		{
			if (this.Opened)
			{
				this.Close();
			}
			if (!string.IsNullOrEmpty(this.ComSettings))
			{
                this.Open(this.ComSettings, this.PortNum);
			}
			return this.Opened;
		}
        public bool Open(string comsettings, int portnum)
		{
			SerialPort.DCB dCB = default(SerialPort.DCB);
			SerialPort.COMMTIMEOUTS cOMMTIMEOUTS = default(SerialPort.COMMTIMEOUTS);
			this.Opened = true;
			this.hComm = SerialPort.CreateFile("\\\\.\\COM" + portnum.ToString(), 3221225472u, 0, 0, 3, 0, 0);
			bool result;
			if (this.hComm == -1)
			{
				SerialPort.CloseHandle(this.hComm);
				this.Opened = false;
				result = false;
			}
			else
			{
				this.retval = SerialPort.GetCommTimeouts(this.hComm, ref cOMMTIMEOUTS);
				if (this.retval == -1)
				{
					SerialPort.CloseHandle(this.hComm);
					this.Opened = false;
					result = false;
				}
				else
				{
					cOMMTIMEOUTS.ReadTotalTimeoutConstant = this.ReadTimeout;
					cOMMTIMEOUTS.ReadTotalTimeoutMultiplier = 0;
					cOMMTIMEOUTS.WriteTotalTimeoutMultiplier = 0;
					cOMMTIMEOUTS.WriteTotalTimeoutConstant = 0;
					this.retval = SerialPort.SetCommTimeouts(this.hComm, ref cOMMTIMEOUTS);
					if (this.retval == -1)
					{
						SerialPort.CloseHandle(this.hComm);
						this.Opened = false;
						result = false;
					}
					else
					{
						this.retval = SerialPort.GetCommState(this.hComm, ref dCB);
						if (this.retval == -1)
						{
							SerialPort.CloseHandle(this.hComm);
							this.Opened = false;
							result = false;
						}
						else
						{
							this.retval = SerialPort.BuildCommDCB(comsettings, ref dCB);
							if (this.retval == -1)
							{
								SerialPort.CloseHandle(this.hComm);
								this.Opened = false;
								result = false;
							}
							else
							{
								this.retval = SerialPort.SetCommState(this.hComm, ref dCB);
								if (this.retval == -1)
								{
									SerialPort.CloseHandle(this.hComm);
									this.Opened = false;
									result = false;
								}
								else
								{
									this.PortNum = portnum;
									this.ComSettings = comsettings;
									result = this.Opened;
								}
							}
						}
					}
				}
			}
			return result;
		}
		public void FlushComm()
		{
			if (this.hComm != -1)
			{
				SerialPort.FlushFileBuffers(this.hComm);
			}
		}
		public void Close()
		{
			try
			{
				if (this.hComm != -1)
				{
					SerialPort.FlushFileBuffers(this.hComm);
					SerialPort.CloseHandle(this.hComm);
					this.Opened = false;
				}
			}
			catch
			{
				this.Opened = false;
				LogMSG.AddInfo("串口关闭错误！", 2);
			}
		}
		public byte[] Read(int NumBytes)
		{
			byte[] array = new byte[NumBytes];
			byte[] array2 = new byte[0];
			if (this.hComm != -1)
			{
				try
				{
					SerialPort.OVERLAPPED oVERLAPPED = default(SerialPort.OVERLAPPED);
					int num = 0;
					SerialPort.ReadFile(this.hComm, array, NumBytes, ref num, ref oVERLAPPED);
					array2 = new byte[num];
					Array.Copy(array, array2, num);
				}
				catch
				{
					LogMSG.AddInfo("串口读数据错误！", 2);
				}
			}
			return array2;
		}
		public byte[] Read()
		{
			return this.Read(512);
		}
		public int Write(byte[] WriteBytes)
		{
			int result = 0;
			if (this.hComm != -1)
			{
				try
				{
					SerialPort.OVERLAPPED oVERLAPPED = default(SerialPort.OVERLAPPED);
					SerialPort.WriteFile(this.hComm, WriteBytes, WriteBytes.Length, ref result, ref oVERLAPPED);
				}
				catch
				{
					LogMSG.AddInfo("串口写入错误!", 2);
				}
			}
			return result;
		}
		public string[] GetPortNames()
		{
			string text = string.Empty;
			DeviceManagement.WMI wMI = new DeviceManagement.WMI(DeviceManagement.WMIPath.Win32_SerialPort);
			checked
			{
				for (int i = 0; i < wMI.Count; i++)
				{
					string text2 = wMI[i, "DeviceID"].ToString();
					if (text2.Length == 4)
					{
						text2 = "COM0" + text2.Substring(3, 1);
					}
					text2 = text2.ToUpper();
					text = text + text2 + "^";
				}
				return text.Split(new char[]
				{
					'^'
				});
			}
		}
	}
}
