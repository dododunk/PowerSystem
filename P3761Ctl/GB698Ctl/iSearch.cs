using System;
using System.Data.OleDb;
using System.Windows.Forms;
namespace GB698Ctl
{
	internal class iSearch
	{
		public ListView iListView;
		public OleDbConnection myConn;
		public string Path;
		public iSearch(string path)
		{
			this.Path = path;
		}
		public void InitListView()
		{
			this.iListView.View = View.Details;
			this.iListView.FullRowSelect = true;
			this.iListView.MultiSelect = false;
			this.iListView.GridLines = true;
			this.iListView.Columns.Add("类别", 100);
			this.iListView.Columns.Add("字段名称", 250);
			this.iListView.Columns.Add("规约标识", 70);
			this.iListView.Columns.Add("规约格式", 150);
			this.iListView.Columns.Add("字节数", 60);
			this.iListView.Columns.Add("数据编码", 80);
			this.iListView.Columns.Add("块内容", 200);
		}
		public void SearhData(string dalei, string subdalei)
		{
			this.iListView.Items.Clear();
			string text = string.Empty;
			if (!string.IsNullOrEmpty(dalei))
			{
				text = "select * from 规约 where 大类='" + dalei + "'";
			}
			if (!string.IsNullOrEmpty(subdalei))
			{
				text = text + " and 中类='" + subdalei + "'";
			}
			text += " order by 字段名称";
			OleDbCommand oleDbCommand = new OleDbCommand(text, this.myConn);
			OleDbDataReader oleDbDataReader = oleDbCommand.ExecuteReader();
			while (oleDbDataReader.Read())
			{
				string lb = oleDbDataReader["中类"].ToString();
				string zdmc = oleDbDataReader["字段名称"].ToString();
				string gybz = oleDbDataReader["规约标识"].ToString();
				string gygs = oleDbDataReader["规约格式"].ToString();
				string zjs = oleDbDataReader["项字节数"].ToString();
				string bmlx = oleDbDataReader["数据编码"].ToString();
				string knr = oleDbDataReader["块内容"].ToString();
				this.InfoToList(this.iListView, lb, zdmc, gybz, gygs, zjs, bmlx, knr);
			}
			oleDbDataReader.Close();
		}
		public void SearhData(string dalei, bool isbiaozhi, string val)
		{
			this.iListView.Items.Clear();
			string text = string.Empty;
			checked
			{
				if (isbiaozhi)
				{
					text = "select * from 规约 where 规约标识='" + val + "'";
				}
				else
				{
					string[] array = val.Trim().Split(new char[]
					{
						' '
					});
					text = "select * from 规约 where ";
					for (int i = 0; i < array.Length; i++)
					{
						if (!string.IsNullOrEmpty(array[i]))
						{
							text = text + "字段名称 like '%" + array[i] + "%' and 字段名称<>''";
						}
					}
					text += " and 1=1";
				}
				if (!string.IsNullOrEmpty(dalei))
				{
					text = text + " and 大类='" + dalei + "'";
				}
				text += " order by 字段名称";
				OleDbCommand oleDbCommand = new OleDbCommand(text, this.myConn);
				OleDbDataReader oleDbDataReader = oleDbCommand.ExecuteReader();
				while (oleDbDataReader.Read())
				{
					string lb = oleDbDataReader["中类"].ToString();
					string zdmc = oleDbDataReader["字段名称"].ToString();
					string gybz = oleDbDataReader["规约标识"].ToString();
					string gygs = oleDbDataReader["规约格式"].ToString();
					string zjs = oleDbDataReader["项字节数"].ToString();
					string bmlx = oleDbDataReader["数据编码"].ToString();
					string knr = oleDbDataReader["块内容"].ToString();
					this.InfoToList(this.iListView, lb, zdmc, gybz, gygs, zjs, bmlx, knr);
				}
				oleDbDataReader.Close();
			}
		}
		private void InfoToList(ListView lv, string lb, string zdmc, string gybz, string gygs, string zjs, string bmlx, string knr)
		{
			ListViewItem listViewItem = new ListViewItem();
			listViewItem.SubItems.Clear();
			listViewItem.SubItems[0].Text = lb;
			listViewItem.SubItems.Add(zdmc);
			listViewItem.SubItems.Add(gybz);
			listViewItem.SubItems.Add(gygs);
			listViewItem.SubItems.Add(zjs);
			listViewItem.SubItems.Add(bmlx);
			listViewItem.SubItems.Add(knr);
			lv.Items.Add(listViewItem);
		}
	}
}
