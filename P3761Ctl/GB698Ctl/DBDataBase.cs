using System;
using System.Data;
using System.Data.OleDb;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;
namespace GB698Ctl
{
	public class DBDataBase
	{
		private OleDbConnection myConn = new OleDbConnection();
		private string file = Program.SysPath + "\\Data.mdb";
		public string dbconnectstring;
		public DBDataBase()
		{
			this.dbconnectstring = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + this.file + ";User Id=admin;Password=;";
			this.CreateDB(this.file);
		}
		public void InitSys()
		{
			this.myConn = new OleDbConnection(this.dbconnectstring);
			this.myConn.Open();
		}
		private void CreateDB(string iflie)
		{
			if (!File.Exists(iflie))
			{
				object obj = Activator.CreateInstance(Type.GetTypeFromProgID("ADOX.Catalog"));
				object[] args = new object[]
				{
					this.dbconnectstring
				};
				obj.GetType().InvokeMember("Create", BindingFlags.InvokeMethod, null, obj, args);
				Marshal.ReleaseComObject(obj);
				this.InitSys();
				this.CreateTB();
			}
			else
			{
				this.InitSys();
			}
		}
		private void CreateTB()
		{
			string cmdText = "Create table Data([ID] int identity primary key,[A1] nvarchar(10),[A2] nvarchar(10), [Categories] nvarchar(50),[Name] nvarchar(50),[AFN] nvarchar(10),[FN] nvarchar(10),[PN] nvarchar(10),[Send] memo,[Data] memo,[Time] datetime)";
			OleDbCommand oleDbCommand = new OleDbCommand(cmdText, this.myConn);
			oleDbCommand.ExecuteNonQuery();
			cmdText = "Create table AF10F9([ID] int identity primary key,[A1] nvarchar(10),[A2] nvarchar(10),[Addr] nvarchar(20), [Categories] nvarchar(50),[Name] nvarchar(50),[AFN] nvarchar(10),[FN] nvarchar(10),[PN] nvarchar(10),[Val] memo,[Data] memo,[Time] datetime)";
			oleDbCommand = new OleDbCommand(cmdText, this.myConn);
			oleDbCommand.ExecuteNonQuery();
		}
		public string[] GetALLBars()
		{
			string text = string.Empty;
			string cmdText = "Select [A1],[A2] from Data GROUP BY [A1],[A2] ";
			OleDbCommand oleDbCommand = new OleDbCommand(cmdText, this.myConn);
			OleDbDataReader oleDbDataReader = oleDbCommand.ExecuteReader();
			while (oleDbDataReader.Read())
			{
				text = text + Convert.ToString(oleDbDataReader["A1"]) + ",";
				text += Convert.ToString(oleDbDataReader["A2"]);
				text += "|";
			}
			oleDbDataReader.Close();
			return text.Split(new char[]
			{
				'|'
			});
		}
		public string[] GetALLItems(string a1, string a2)
		{
			string text = string.Empty;
			string cmdText = string.Concat(new string[]
			{
				"Select * from Data where [A1]='",
				a1,
				"' and [A2]='",
				a2,
				"'  "
			});
			OleDbCommand oleDbCommand = new OleDbCommand(cmdText, this.myConn);
			OleDbDataReader oleDbDataReader = oleDbCommand.ExecuteReader();
			while (oleDbDataReader.Read())
			{
				text = text + Convert.ToString(oleDbDataReader["Categories"]) + ",";
				text = text + Convert.ToString(oleDbDataReader["Name"]) + ",";
				text = text + Convert.ToString(oleDbDataReader["AFN"]) + ",";
				text = text + Convert.ToString(oleDbDataReader["FN"]) + ",";
				text = text + Convert.ToString(oleDbDataReader["PN"]) + ",";
				text += Convert.ToString(oleDbDataReader["Send"] + ",");
				text += Convert.ToString(oleDbDataReader["Data"] + ",");
				text += Convert.ToString(oleDbDataReader["Time"]);
				text += "|";
			}
			oleDbDataReader.Close();
			return text.Split(new char[]
			{
				'|'
			});
		}
		public string[] GetALLItems()
		{
			string text = string.Empty;
			string cmdText = "Select * from Data";
			OleDbCommand oleDbCommand = new OleDbCommand(cmdText, this.myConn);
			OleDbDataReader oleDbDataReader = oleDbCommand.ExecuteReader();
			while (oleDbDataReader.Read())
			{
				text = text + Convert.ToString(oleDbDataReader["A1"]) + ",";
				text = text + Convert.ToString(oleDbDataReader["A2"]) + ",";
				text = text + Convert.ToString(oleDbDataReader["Categories"]) + ",";
				text = text + Convert.ToString(oleDbDataReader["Name"]) + ",";
				text = text + Convert.ToString(oleDbDataReader["AFN"]) + ",";
				text = text + Convert.ToString(oleDbDataReader["FN"]) + ",";
				text = text + Convert.ToString(oleDbDataReader["PN"]) + ",";
				text += Convert.ToString(oleDbDataReader["Send"] + ",");
				text += Convert.ToString(oleDbDataReader["Data"] + ",");
				text += Convert.ToString(oleDbDataReader["Time"]);
				text += "|";
			}
			oleDbDataReader.Close();
			return text.Split(new char[]
			{
				'|'
			});
		}
		public void DeleteData(string a1, string a2)
		{
			string cmdText = string.Concat(new string[]
			{
				"Delete from Data where [A1]='",
				a1,
				"' and [A2]='",
				a2,
				"'  "
			});
			OleDbCommand oleDbCommand = new OleDbCommand(cmdText, this.myConn);
			oleDbCommand.ExecuteNonQuery();
		}
		public void DeleteData()
		{
			string cmdText = "Delete from Data";
			OleDbCommand oleDbCommand = new OleDbCommand(cmdText, this.myConn);
			oleDbCommand.ExecuteNonQuery();
		}
		public void InsertData(string a1, string a2, string Categories, string Name, string AFN, string FN, string PN, string Data, string Send)
		{
			string text = "Insert into Data([A1],[A2],[Categories],[Name],[AFN],[FN],[PN],[Data],[time],[Send]) values(";
			text = string.Concat(new string[]
			{
				text,
				"'",
				a1,
				"','",
				a2,
				"',"
			});
			text = string.Concat(new string[]
			{
				text,
				"'",
				Categories,
				"','",
				Name,
				"','",
				AFN,
				"',"
			});
			text = string.Concat(new string[]
			{
				text,
				"'",
				FN,
				"','",
				PN,
				"','",
				Data,
				"','",
				DateTime.Now.ToString(),
				"','",
				Send,
				"')"
			});
			OleDbCommand oleDbCommand = new OleDbCommand(text, this.myConn);
			oleDbCommand.ExecuteNonQuery();
		}
		public void InsertDataAF10F9(string a1, string a2, string addr, string Categories, string Name, string AFN, string FN, string PN, string Data, string Val)
		{
			string text = "Insert into AF10F9([A1],[A2],[Addr],[Categories],[Name],[AFN],[FN],[PN],[Data],[time],[Val]) values(";
			text = string.Concat(new string[]
			{
				text,
				"'",
				a1,
				"','",
				a2,
				"','",
				addr,
				"',"
			});
			text = string.Concat(new string[]
			{
				text,
				"'",
				Categories,
				"','",
				Name,
				"','",
				AFN,
				"',"
			});
			text = string.Concat(new string[]
			{
				text,
				"'",
				FN,
				"','",
				PN,
				"','",
				Data,
				"','",
				DateTime.Now.ToString(),
				"','",
				Val,
				"')"
			});
			OleDbCommand oleDbCommand = new OleDbCommand(text, this.myConn);
			oleDbCommand.ExecuteNonQuery();
		}
		public DataTable GetTableAF10F9()
		{
			string selectCommandText = "select * from AF10F9";
			OleDbDataAdapter oleDbDataAdapter = new OleDbDataAdapter(selectCommandText, this.myConn.ConnectionString);
			DataTable dataTable = new DataTable();
			oleDbDataAdapter.Fill(dataTable);
			return dataTable;
		}
	}
}
