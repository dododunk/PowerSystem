using ExcelLibrary.SpreadSheet;
using System;
using System.Data;
using System.Diagnostics;
using System.IO;
namespace GB698Ctl
{
	internal class MyExcel
	{
		private Workbook workbook;
		private Worksheet worksheet;
		private string path = Program.SysPath;
		public void Create()
		{
			this.workbook = new Workbook();
		}
		public void DataTableOutPut(DataTable tb)
		{
			this.worksheet = new Worksheet("AF10F9");
			checked
			{
				for (int i = 0; i < tb.Columns.Count; i++)
				{
					this.worksheet.Cells[0, i] = new Cell(tb.Columns[i].Caption);
					for (int j = 0; j < tb.Rows.Count; j++)
					{
						this.worksheet.Cells[j + 1, i] = new Cell(tb.Rows[j][i].ToString());
					}
				}
				this.workbook.Worksheets.Add(this.worksheet);
			}
		}
		public void Save(string Filename)
		{
			string text = Program.SysPath + Filename + ".xls";
			this.workbook.Save(text);
			if (File.Exists(text))
			{
				Process.Start(text);
			}
		}
	}
}
