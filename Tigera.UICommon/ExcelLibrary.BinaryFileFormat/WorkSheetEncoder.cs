using ExcelLibrary.BinaryDrawingFormat;
using ExcelLibrary.SpreadSheet;
using QiHe.CodeLib;
using System;
using System.Collections.Generic;
namespace ExcelLibrary.BinaryFileFormat
{
	public class WorkSheetEncoder
	{
		public static List<Record> Encode(Worksheet worksheet, SharedResource sharedResource)
		{
			List<Record> list = new List<Record>();
			list.Add(new BOF
			{
				BIFFversion = 1536,
				StreamType = 16,
				BuildID = 3515,
				BuildYear = 1996,
				RequiredExcelVersion = 6u
			});
			foreach (KeyValuePair<Pair<ushort, ushort>, ushort> current in worksheet.Cells.ColumnWidth)
			{
				list.Add(new COLINFO
				{
					FirstColIndex = current.Key.Left,
					LastColIndex = current.Key.Right,
					Width = current.Value
				});
			}
			DIMENSIONS dIMENSIONS = new DIMENSIONS();
			checked
			{
				if (worksheet.Cells.Rows.Count > 0)
				{
					dIMENSIONS.FirstRow = worksheet.Cells.FirstRowIndex;
					dIMENSIONS.FirstColumn = (short)worksheet.Cells.FirstColIndex;
					dIMENSIONS.LastRow = worksheet.Cells.LastRowIndex + 1;
					dIMENSIONS.LastColumn = (short)(worksheet.Cells.LastColIndex + 1);
				}
				list.Add(dIMENSIONS);
				List<Record> list2 = new List<Record>(32);
				List<Record> list3 = new List<Record>();
				for (int i = dIMENSIONS.FirstRow; i < dIMENSIONS.LastRow; i++)
				{
					if (worksheet.Cells.Rows.ContainsKey(i))
					{
						Row row = worksheet.Cells.Rows[i];
						list2.Add(new ROW
						{
							RowIndex = (ushort)i,
							FirstColIndex = (ushort)row.FirstColIndex,
							LastColIndex = (ushort)(row.LastColIndex + 1),
							RowHeight = row.Height,
							Flags = 983296u
						});
						for (int j = row.FirstColIndex; j <= row.LastColIndex; j++)
						{
							Cell cell = row.GetCell(j);
							if (cell != Cell.EmptyCell && cell.Value != null)
							{
								CellValue cellValue = WorkSheetEncoder.EncodeCell(cell, sharedResource);
								cellValue.RowIndex = (ushort)i;
								cellValue.ColIndex = (ushort)j;
								cellValue.XFIndex = (ushort)sharedResource.GetXFIndex(cell.Format);
								list3.Add(cellValue);
							}
						}
						if (list2.Count == 32)
						{
							list.AddRange(list2);
							list.AddRange(list3);
							list2.Clear();
							list3.Clear();
						}
					}
				}
				if (list2.Count > 0)
				{
					list.AddRange(list2);
					list.AddRange(list3);
				}
				if (worksheet.Pictures.Count > 0)
				{
					list.Add(WorkSheetEncoder.EncodePictures(worksheet.Pictures, sharedResource, worksheet));
					ushort num = 1;
					while ((int)num <= worksheet.Pictures.Count)
					{
						OBJ oBJ = new OBJ();
						CommonObjectData commonObjectData = new CommonObjectData();
						commonObjectData.ObjectID = num;
						commonObjectData.ObjectType = 8;
						commonObjectData.OptionFlags = 24593;
						oBJ.SubRecords.Add(commonObjectData);
						oBJ.SubRecords.Add(new End());
						list.Add(oBJ);
						num += 1;
					}
				}
				EOF item = new EOF();
				list.Add(item);
				return list;
			}
		}
		private static CellValue EncodeCell(Cell cell, SharedResource sharedResource)
		{
			object value = cell.Value;
			CellValue result;
			if (value is int)
			{
				result = new RK
				{
					Value = checked((uint)((int)value << 2 | 2))
				};
			}
			else
			{
				if (value is decimal)
				{
					result = new RK
					{
						Value = (uint)((decimal)value * 100m) << 2 | 3u
					};
				}
				else
				{
					if (value is double)
					{
						result = new NUMBER
						{
							Value = (double)value
						};
					}
					else
					{
						if (value is string)
						{
							result = new LABELSST
							{
								SSTIndex = sharedResource.GetSSTIndex((string)value)
							};
						}
						else
						{
							if (value is DateTime)
							{
								result = new NUMBER
								{
									Value = sharedResource.EncodeDateTime((DateTime)value)
								};
							}
							else
							{
								if (value is bool)
								{
									result = new BOOLERR
									{
										ValueType = 0,
										Value = Convert.ToByte((bool)value)
									};
								}
								else
								{
									if (!(value is ErrorCode))
									{
										throw new Exception("Invalid cell value.");
									}
									result = new BOOLERR
									{
										ValueType = 1,
										Value = ((ErrorCode)value).Code
									};
								}
							}
						}
					}
				}
			}
			return result;
		}
		private static Record EncodePictures(Dictionary<Pair<int, int>, Picture> pictures, SharedResource sharedResource, Worksheet worksheet)
		{
			MSODRAWING mSODRAWING = new MSODRAWING();
			MsofbtDgContainer msofbtDgContainer = new MsofbtDgContainer();
			mSODRAWING.EscherRecords.Add(msofbtDgContainer);
			MsofbtDg msofbtDg = new MsofbtDg();
			msofbtDg.Instance = 1;
			checked
			{
				msofbtDg.NumShapes = pictures.Count + 1;
				msofbtDg.LastShapeID = 1024 + pictures.Count;
				msofbtDgContainer.EscherRecords.Add(msofbtDg);
				MsofbtSpgrContainer msofbtSpgrContainer = new MsofbtSpgrContainer();
				msofbtDgContainer.EscherRecords.Add(msofbtSpgrContainer);
				MsofbtSpContainer msofbtSpContainer = new MsofbtSpContainer();
				msofbtSpContainer.EscherRecords.Add(new MsofbtSpgr());
				MsofbtSp msofbtSp = new MsofbtSp();
				msofbtSp.ShapeId = 1024;
				msofbtSp.Flags = 5;
				msofbtSp.Version = 2;
				msofbtSpContainer.EscherRecords.Add(msofbtSp);
				msofbtSpgrContainer.EscherRecords.Add(msofbtSpContainer);
				foreach (Picture current in pictures.Values)
				{
					if (!sharedResource.Images.Contains(current.Image))
					{
						sharedResource.Images.Add(current.Image);
					}
					MsofbtSpContainer msofbtSpContainer2 = new MsofbtSpContainer();
					MsofbtSp msofbtSp2 = new MsofbtSp();
					msofbtSp2.Version = 2;
					msofbtSp2.ShapeType = ShapeType.PictureFrame;
					msofbtSp2.ShapeId = 1024 + msofbtSpgrContainer.EscherRecords.Count;
					msofbtSp2.Flags = 2560;
					msofbtSpContainer2.EscherRecords.Add(msofbtSp2);
					MsofbtOPT msofbtOPT = new MsofbtOPT();
					msofbtOPT.Add(PropertyIDs.LockAgainstGrouping, 33226880u);
					msofbtOPT.Add(PropertyIDs.FitTextToShape, 262148u);
					msofbtOPT.Add(PropertyIDs.BlipId, (uint)sharedResource.Images.IndexOf(current.Image) + 1u);
					msofbtSpContainer2.EscherRecords.Add(msofbtOPT);
					MsofbtClientAnchor msofbtClientAnchor = new MsofbtClientAnchor();
					msofbtClientAnchor.Row1 = current.TopLeftCorner.RowIndex;
					msofbtClientAnchor.Col1 = current.TopLeftCorner.ColIndex;
					msofbtClientAnchor.DX1 = current.TopLeftCorner.DX;
					msofbtClientAnchor.DY1 = current.TopLeftCorner.DY;
					msofbtClientAnchor.Row2 = current.BottomRightCorner.RowIndex;
					msofbtClientAnchor.Col2 = current.BottomRightCorner.ColIndex;
					msofbtClientAnchor.DX2 = current.BottomRightCorner.DX;
					msofbtClientAnchor.DY2 = current.BottomRightCorner.DY;
					msofbtClientAnchor.ExtraData = new byte[0];
					msofbtSpContainer2.EscherRecords.Add(msofbtClientAnchor);
					msofbtSpContainer2.EscherRecords.Add(new MsofbtClientData());
					msofbtSpgrContainer.EscherRecords.Add(msofbtSpContainer2);
				}
				return mSODRAWING;
			}
		}
	}
}
