using ExcelLibrary.SpreadSheet;
using System;
using System.Collections.Generic;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class WorksheetDecoder
	{
		public static Worksheet Decode(Workbook book, Stream stream, SharedResource sharedResource)
		{
			Worksheet worksheet = new Worksheet();
			worksheet.Book = book;
			List<Record> list = WorksheetDecoder.ReadRecords(stream, out worksheet.Drawing);
			worksheet.Cells = WorksheetDecoder.PopulateCells(list, sharedResource);
			worksheet.Book.Records.AddRange(list);
			return worksheet;
		}
		private static List<Record> ReadRecords(Stream stream, out MSODRAWING drawingRecord)
		{
			List<Record> list = new List<Record>();
			drawingRecord = null;
			Record record = Record.Read(stream);
			Record record2 = record;
			Record record3 = null;
			record2.Decode();
			if (record is BOF && ((BOF)record).StreamType == 16)
			{
				while (record.Type != 10)
				{
					if (record.Type == 60)
					{
						record2.ContinuedRecords.Add(record);
					}
					else
					{
						ushort type = record.Type;
						if (type != 236)
						{
							if (type != 519)
							{
								list.Add(record);
							}
							else
							{
								if (record3 is FORMULA)
								{
									record.Decode();
									(record3 as FORMULA).StringRecord = (record as STRING);
								}
							}
						}
						else
						{
							if (drawingRecord == null)
							{
								drawingRecord = (record as MSODRAWING);
								list.Add(record);
							}
							else
							{
								drawingRecord.ContinuedRecords.Add(record);
							}
						}
						if (record.Type == 6)
						{
							record3 = record;
						}
						else
						{
							if (record.Type != 1212 && record.Type != 545)
							{
								record3 = null;
							}
						}
						record2 = record;
					}
					record = Record.Read(stream);
				}
				list.Add(record);
			}
			return list;
		}
		private static CellCollection PopulateCells(List<Record> records, SharedResource sharedResource)
		{
			CellCollection cellCollection = new CellCollection();
			cellCollection.SharedResource = sharedResource;
			checked
			{
				foreach (Record current in records)
				{
					current.Decode();
					ushort type = current.Type;
					if (type <= 189)
					{
						if (type != 6)
						{
							if (type == 189)
							{
								MULRK mULRK = current as MULRK;
								int rowIndex = (int)mULRK.RowIndex;
								for (int i = (int)mULRK.FirstColIndex; i <= (int)mULRK.LastColIndex; i++)
								{
									int index = i - (int)mULRK.FirstColIndex;
									object value = Record.DecodeRK(mULRK.RKList[index]);
									int xFindex = (int)mULRK.XFList[index];
									cellCollection.CreateCell(rowIndex, i, value, xFindex);
								}
							}
						}
						else
						{
							FORMULA fORMULA = current as FORMULA;
							cellCollection.CreateCell((int)fORMULA.RowIndex, (int)fORMULA.ColIndex, fORMULA.DecodeResult(), (int)fORMULA.XFIndex);
						}
					}
					else
					{
						if (type != 253)
						{
							switch (type)
							{
							case 515:
								{
									NUMBER nUMBER = current as NUMBER;
									cellCollection.CreateCell((int)nUMBER.RowIndex, (int)nUMBER.ColIndex, nUMBER.Value, (int)nUMBER.XFIndex);
									break;
								}

							case 516:
								break;

							case 517:
								{
									BOOLERR bOOLERR = current as BOOLERR;
									cellCollection.CreateCell((int)bOOLERR.RowIndex, (int)bOOLERR.ColIndex, bOOLERR.GetValue(), (int)bOOLERR.XFIndex);
									break;
								}

							default:
								if (type == 638)
								{
									RK rK = current as RK;
									cellCollection.CreateCell((int)rK.RowIndex, (int)rK.ColIndex, Record.DecodeRK(rK.Value), (int)rK.XFIndex);
								}
								break;
							}
						}
						else
						{
							LABELSST lABELSST = current as LABELSST;
							Cell cell = cellCollection.CreateCell((int)lABELSST.RowIndex, (int)lABELSST.ColIndex, sharedResource.GetStringFromSST(lABELSST.SSTIndex), (int)lABELSST.XFIndex);
							cell.Style.RichTextFormat = sharedResource.SharedStringTable.RichTextFormatting[lABELSST.SSTIndex];
						}
					}
				}
				return cellCollection;
			}
		}
		private static FONT getFontRecord(SharedResource sharedResource, ushort index)
		{
			FONT result;
			if (index >= 0 && index <= 3)
			{
				result = sharedResource.Fonts[(int)index];
			}
			else
			{
				if (index >= 5)
				{
					result = sharedResource.Fonts[(int)checked(index - 1)];
				}
				else
				{
					result = null;
				}
			}
			return result;
		}
		public static FONT getFontForCharacter(Cell cell, ushort charIndex)
		{
			FONT result = null;
			int num = cell.Style.RichTextFormat.CharIndexes.BinarySearch(charIndex);
			List<ushort> fontIndexes = cell.Style.RichTextFormat.FontIndexes;
			if (num >= 0)
			{
				result = WorksheetDecoder.getFontRecord(cell.SharedResource, fontIndexes[num]);
			}
			else
			{
				if (~num != 0)
				{
					result = WorksheetDecoder.getFontRecord(cell.SharedResource, fontIndexes[checked(~num - 1)]);
				}
			}
			return result;
		}
	}
}
