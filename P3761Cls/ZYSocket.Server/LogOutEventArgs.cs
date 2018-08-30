using System;
namespace ZYSocket.Server
{
	public class LogOutEventArgs : EventArgs
	{
		private LogType messClass;
		private string mess;
		public LogType MessClass
		{
			get
			{
				return this.messClass;
			}
		}
		public string Mess
		{
			get
			{
				return this.mess;
			}
		}
		public LogOutEventArgs(LogType messclass, string str)
		{
			this.messClass = messclass;
			this.mess = str;
		}
	}
}
