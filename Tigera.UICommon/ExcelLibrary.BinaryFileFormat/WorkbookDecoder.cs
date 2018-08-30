using ExcelLibrary.SpreadSheet;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class WorkbookDecoder
	{
		public static Workbook Decode(Stream stream)
		{
			Workbook workbook = new Workbook();
			List<Record> records = WorkbookDecoder.ReadRecords(stream, out workbook.DrawingGroup);
			workbook.Records = records;
			SharedResource sharedResource;
			List<BOUNDSHEET> list = WorkbookDecoder.DecodeRecords(records, out sharedResource);
			foreach (BOUNDSHEET current in list)
			{
				stream.Position = (long)((ulong)current.StreamPosition);
				Worksheet worksheet = WorksheetDecoder.Decode(workbook, stream, sharedResource);
				worksheet.Book = workbook;
				worksheet.Name = current.SheetName;
				worksheet.SheetType = (SheetType)current.SheetType;
				workbook.Worksheets.Add(worksheet);
			}
			return workbook;
		}
		private static List<Record> ReadRecords(Stream stream, out MSODRAWINGGROUP drawingGroup)
		{
			List<Record> list = new List<Record>();
			drawingGroup = null;
			Record record = Record.Read(stream);
			record.Decode();
			Record record2 = record;
			if (record is BOF && ((BOF)record).StreamType == 5)
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
						if (type != 235)
						{
							list.Add(record);
						}
						else
						{
							if (drawingGroup == null)
							{
								drawingGroup = (record as MSODRAWINGGROUP);
								list.Add(record);
							}
							else
							{
								drawingGroup.ContinuedRecords.Add(record);
							}
						}
						record2 = record;
					}
					record = Record.Read(stream);
				}
				list.Add(record);
				return list;
			}
			throw new Exception("Invalid Workbook.");
		}
		private static List<BOUNDSHEET> DecodeRecords(List<Record> records, out SharedResource sharedResource)
		{
			sharedResource = new SharedResource();
			List<BOUNDSHEET> list = new List<BOUNDSHEET>();
			checked
			{
				foreach (Record current in records)
				{
					current.Decode();
					ushort type = current.Type;
					if (type <= 133)
					{
						if (type != 34)
						{
							if (type != 49)
							{
								if (type == 133)
								{
									list.Add(current as BOUNDSHEET);
								}
							}
							else
							{
								FONT item = current as FONT;
								sharedResource.Fonts.Add(item);
							}
						}
						else
						{
							DATEMODE dATEMODE = current as DATEMODE;
							switch (dATEMODE.Mode)
							{
							case 0:
								sharedResource.BaseDate = DateTime.Parse("1899-12-31");
								break;

							case 1:
								sharedResource.BaseDate = DateTime.Parse("1904-01-01");
								break;
							}
						}
					}
					else
					{
						if (type <= 224)
						{
							if (type != 146)
							{
								if (type == 224)
								{
									sharedResource.ExtendedFormats.Add(current as XF);
								}
							}
							else
							{
								PALETTE pALETTE = current as PALETTE;
								int num = 8;
								foreach (int current2 in pALETTE.Colors)
								{
									sharedResource.ColorPalette[num] = Color.FromArgb(current2);
									num++;
								}
							}
						}
						else
						{
							if (type != 252)
							{
								if (type == 1054)
								{
									sharedResource.CellFormats.Add(current as FORMAT);
								}
							}
							else
							{
								sharedResource.SharedStringTable = (current as SST);
							}
						}
					}
				}
				return list;
			}
		}
	}
}
