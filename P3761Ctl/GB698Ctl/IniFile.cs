using System;
using System.Runtime.InteropServices;
using System.Text;
namespace GB698Ctl
{
	public class IniFile
	{
		private string IniFileName;
	
		[DllImport("kernel32.dll")]
		private static extern int GetPrivateProfileStringA(string segName, string keyName, string sDefault, StringBuilder buffer, int nSize, string fileName);
		[DllImport("kernel32.dll")]
		private static extern int GetPrivateProfileSectionA(string segName, StringBuilder buffer, int nSize, string fileName);
		[DllImport("kernel32.dll")]
		private static extern int WritePrivateProfileSectionA(string segName, string sValue, string fileName);
		[DllImport("kernel32.dll")]
		private static extern int WritePrivateProfileStringA(string segName, string keyName, string sValue, string fileName);
		[DllImport("kernel32.dll")]
		private static extern int GetPrivateProfileSectionNamesA(byte[] buffer, int iLen, string fileName);
		public IniFile(string Filename)
		{
			this.IniFileName = Filename;
		}
		public string ReadIni(string Section, string Key, string Default)
		{
			StringBuilder stringBuilder = new StringBuilder(65535);
			IniFile.GetPrivateProfileStringA(Section, Key, Default, stringBuilder, stringBuilder.Capacity, this.IniFileName);
			return stringBuilder.ToString();
		}
		public void WriteIni(string Section, string Key, string strValue)
		{
			if (strValue != null)
			{
				IniFile.WritePrivateProfileStringA(Section, Key, strValue.ToString(), this.IniFileName);
			}
			else
			{
				IniFile.WritePrivateProfileStringA(Section, Key, null, this.IniFileName);
			}
		}
	}
}
