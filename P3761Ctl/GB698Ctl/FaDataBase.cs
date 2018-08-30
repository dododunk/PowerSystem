using System;
using System.Data.OleDb;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;
namespace GB698Ctl
{
	public class FaDataBase
	{
		private OleDbConnection myConn = new OleDbConnection();
		private string file = Program.SysPath + "\\Scheme.mdb";
		private string dbconnectstring;
		public FaDataBase()
		{
			this.dbconnectstring = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + this.file + ";User Id=admin;Password=;";
			this.CreateDB(this.file);
		}
		private void InitSys()
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
			string cmdText = "Create table Scheme([ID] int identity primary key,[Scheme] nvarchar(50),[Categories] nvarchar(50),[Name] nvarchar(50),[AFN] nvarchar(10),[FN] nvarchar(10),[PN] nvarchar(10),[Data] memo)";
			OleDbCommand oleDbCommand = new OleDbCommand(cmdText, this.myConn);
			oleDbCommand.ExecuteNonQuery();
			cmdText = "Create table Customize([ID] int identity primary key,[Name] nvarchar(50),[AFN] nvarchar(10),[FN] nvarchar(10),[Items] memo)";
			oleDbCommand = new OleDbCommand(cmdText, this.myConn);
			oleDbCommand.ExecuteNonQuery();
		}
		public string[] GetFaNames()
		{
			string text = string.Empty;
			string cmdText = "Select DISTINCT([Scheme]) from Scheme where [Scheme]<>''";
			OleDbCommand oleDbCommand = new OleDbCommand(cmdText, this.myConn);
			OleDbDataReader oleDbDataReader = oleDbCommand.ExecuteReader();
			while (oleDbDataReader.Read())
			{
				text = text + oleDbDataReader["Scheme"].ToString() + "|";
			}
			oleDbDataReader.Close();
			return text.Split(new char[]
			{
				'|'
			});
		}
		public string[] GetALLItems(string faname)
		{
			string text = string.Empty;
			string cmdText = "Select * from Scheme where [Scheme]<>'' and [Scheme]='" + faname + "'";
			OleDbCommand oleDbCommand = new OleDbCommand(cmdText, this.myConn);
			OleDbDataReader oleDbDataReader = oleDbCommand.ExecuteReader();
			while (oleDbDataReader.Read())
			{
				text = text + Convert.ToString(oleDbDataReader["Categories"]) + ",";
				text = text + Convert.ToString(oleDbDataReader["Name"]) + ",";
				text = text + Convert.ToString(oleDbDataReader["AFN"]) + ",";
				text = text + Convert.ToString(oleDbDataReader["FN"]) + ",";
				text = text + Convert.ToString(oleDbDataReader["PN"]) + ",";
				text += Convert.ToString(oleDbDataReader["Data"]);
				text += "|";
			}
			oleDbDataReader.Close();
			return text.Split(new char[]
			{
				'|'
			});
		}
		public string GetCustomizeItems(string AFN, string FN)
		{
			string result = string.Empty;
			string cmdText = string.Concat(new string[]
			{
				"Select * from Customize where [AFN]='",
				AFN,
				"' and [FN]='",
				FN,
				"'"
			});
			OleDbCommand oleDbCommand = new OleDbCommand(cmdText, this.myConn);
			OleDbDataReader oleDbDataReader = oleDbCommand.ExecuteReader();
			if (oleDbDataReader.Read())
			{
				result = Convert.ToString(oleDbDataReader["Items"]);
			}
			oleDbDataReader.Close();
			return result;
		}
		public string[] GetALLCustomizeItems()
		{
			string text = string.Empty;
			string cmdText = "Select * from Customize where [Name]<>''";
			OleDbCommand oleDbCommand = new OleDbCommand(cmdText, this.myConn);
			OleDbDataReader oleDbDataReader = oleDbCommand.ExecuteReader();
			while (oleDbDataReader.Read())
			{
				text = text + Convert.ToString(oleDbDataReader["Name"]) + ",";
				text = text + Convert.ToString(oleDbDataReader["AFN"]) + ",";
				text += Convert.ToString(oleDbDataReader["FN"]);
				text += "|";
			}
			oleDbDataReader.Close();
			return text.Split(new char[]
			{
				'|'
			});
		}
		public void DeleteFa(string faname)
		{
			string cmdText = "Delete from Scheme where [Scheme]<>'' and [Scheme]='" + faname + "'";
			OleDbCommand oleDbCommand = new OleDbCommand(cmdText, this.myConn);
			oleDbCommand.ExecuteNonQuery();
		}
		public void DeleteCustomize(string AFN, string FN)
		{
			string cmdText = string.Concat(new string[]
			{
				"Delete from Customize where  [AFN]='",
				AFN,
				"' and [FN]='",
				FN,
				"'"
			});
			OleDbCommand oleDbCommand = new OleDbCommand(cmdText, this.myConn);
			oleDbCommand.ExecuteNonQuery();
		}
		public void InsertFa(string Scheme, string Categories, string Name, string AFN, string FN, string PN, string Data)
		{
			string text = "Insert into Scheme([Scheme],[Categories],[Name],[AFN],[FN],[PN],[Data]) values('" + Scheme + "',";
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
				"')"
			});
			OleDbCommand oleDbCommand = new OleDbCommand(text, this.myConn);
			oleDbCommand.ExecuteNonQuery();
		}
		public void InsertCustomize(string Name, string AFN, string FN, string Items)
		{
			if (!string.IsNullOrEmpty(Name))
			{
				string text = "Insert into Customize([Name],[AFN],[FN],[Items]) values('" + Name + "',";
				text = string.Concat(new string[]
				{
					text,
					"'",
					AFN,
					"','",
					FN,
					"','",
					Items,
					"')"
				});
				OleDbCommand oleDbCommand = new OleDbCommand(text, this.myConn);
				oleDbCommand.ExecuteNonQuery();
			}
		}
	}
}
