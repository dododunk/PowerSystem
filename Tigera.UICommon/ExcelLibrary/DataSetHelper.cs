using ExcelLibrary.SpreadSheet;
using System;
using System.Data;
namespace ExcelLibrary
{
	public sealed class DataSetHelper
	{
		public static DataSet CreateDataSet(string filePath)
		{
			DataSet dataSet = new DataSet();
			Workbook workbook = Workbook.Open(filePath);
			foreach (Worksheet current in workbook.Worksheets)
			{
				DataTable table = DataSetHelper.PopulateDataTable(current);
				dataSet.Tables.Add(table);
			}
			return dataSet;
		}
		public static DataTable CreateDataTable(string filePath, string sheetName)
		{
			Workbook workbook = Workbook.Open(filePath);
			DataTable result;
			foreach (Worksheet current in workbook.Worksheets)
			{
				if (current.Name.Equals(sheetName))
				{
					result = DataSetHelper.PopulateDataTable(current);
					return result;
				}
			}
			result = null;
			return result;
		}
		private static DataTable PopulateDataTable(Worksheet ws)
		{
			CellCollection cells = ws.Cells;
			DataTable dataTable = new DataTable(ws.Name);
			checked
			{
				for (int i = 0; i <= cells.LastColIndex; i++)
				{
					dataTable.Columns.Add(cells[0, i].StringValue, typeof(string));
				}
				for (int j = 1; j <= cells.LastRowIndex; j++)
				{
					DataRow dataRow = dataTable.NewRow();
					for (int k = 0; k <= cells.LastColIndex; k++)
					{
						dataRow[k] = cells[j, k].StringValue;
					}
					dataTable.Rows.Add(dataRow);
				}
				return dataTable;
			}
		}
		public static void CreateWorkbook(string filePath, DataSet dataset)
		{
			if (dataset.Tables.Count == 0)
			{
				throw new ArgumentException("DataSet needs to have at least one DataTable", "dataset");
			}
			Workbook workbook = new Workbook();
			checked
			{
				foreach (DataTable dataTable in dataset.Tables)
				{
					Worksheet worksheet = new Worksheet(dataTable.TableName);
					for (int i = 0; i < dataTable.Columns.Count; i++)
					{
						worksheet.Cells[0, i] = new Cell(dataTable.Columns[i].ColumnName);
						for (int j = 0; j < dataTable.Rows.Count; j++)
						{
							worksheet.Cells[j + 1, i] = new Cell(dataTable.Rows[j][i].ToString());
						}
					}
					workbook.Worksheets.Add(worksheet);
				}
				workbook.Save(filePath);
			}
		}
	}
}
