using ExcelLibrary.BinaryDrawingFormat;
using ExcelLibrary.SpreadSheet;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
namespace ExcelLibrary.BinaryFileFormat
{
	public class WorkbookEncoder
	{
		public static void Encode(Workbook workbook, Stream stream)
		{
			List<Record> list = WorkbookEncoder.EncodeWorkbook(workbook);
			BinaryWriter binaryWriter = new BinaryWriter(stream);
			foreach (Record current in list)
			{
				current.Write(binaryWriter);
			}
			binaryWriter.Close();
		}
		private static List<Record> EncodeWorkbook(Workbook workbook)
		{
			SharedResource sharedResource = new SharedResource(true);
			List<Record> list = new List<Record>();
			list.Add(new BOF
			{
				BIFFversion = 1536,
				StreamType = 5,
				BuildID = 3515,
				BuildYear = 1996,
				RequiredExcelVersion = 6u
			});
			checked
			{
				list.Add(new CODEPAGE
				{
					CodePageIdentifier = (ushort)Encoding.Unicode.CodePage
				});
				list.Add(new WINDOW1
				{
					WindowWidth = 16384,
					WindowHeight = 8192,
					SelecteWorksheets = 1,
					TabBarWidth = 600,
					OptionFlags = 56
				});
				DATEMODE dATEMODE = new DATEMODE();
				dATEMODE.Mode = 1;
				sharedResource.BaseDate = DateTime.Parse("1904-01-01");
				list.Add(dATEMODE);
				List<List<Record>> list2 = new List<List<Record>>();
				foreach (Worksheet current in workbook.Worksheets)
				{
					List<Record> list3 = WorkSheetEncoder.Encode(current, sharedResource);
					Record.EncodeRecords(list3);
					list2.Add(list3);
				}
				list.AddRange(sharedResource.FormatRecords.ToArray());
				list.AddRange(sharedResource.ExtendedFormats.ToArray());
				List<BOUNDSHEET> list4 = new List<BOUNDSHEET>();
				foreach (Worksheet current in workbook.Worksheets)
				{
					BOUNDSHEET bOUNDSHEET = new BOUNDSHEET();
					bOUNDSHEET.Visibility = 0;
					bOUNDSHEET.SheetType = 0;
					bOUNDSHEET.SheetName = current.Name;
					bOUNDSHEET.StreamPosition = 0u;
					list4.Add(bOUNDSHEET);
					list.Add(bOUNDSHEET);
				}
				if (sharedResource.Images.Count > 0)
				{
					list.Add(WorkbookEncoder.EncodeImages(sharedResource.Images));
				}
				Record.EncodeRecords(list);
				int sstOffset = Record.CountDataLength(list);
				list.Add(sharedResource.SharedStringTable);
				list.Add(WorkbookEncoder.CreateEXTSST(sharedResource.SharedStringTable, sstOffset));
				EOF item = new EOF();
				list.Add(item);
				Record.EncodeRecords(list);
				int num = Record.CountDataLength(list);
				for (int i = 0; i < workbook.Worksheets.Count; i++)
				{
					list4[i].StreamPosition = (uint)num;
					list4[i].Encode();
					int num2 = Record.CountDataLength(list2[i]);
					num += num2;
				}
				List<Record> list5 = new List<Record>();
				list5.AddRange(list);
				foreach (List<Record> list3 in list2)
				{
					
					list5.AddRange(list3);
				}
				return list5;
			}
		}
		private static EXTSST CreateEXTSST(SST sst, int sstOffset)
		{
			EXTSST eXTSST = new EXTSST();
			eXTSST.NumStrings = 8;
			int num = 0;
			checked
			{
				int num2 = sstOffset + 12;
				int num3 = 12;
				foreach (string text in sst.StringList)
				{
					int stringDataLength = Record.GetStringDataLength(text);
					if (num3 + stringDataLength > 8228)
					{
						num2 += 4;
						num3 = 4;
					}
					if (num == 0)
					{
						StringOffset stringOffset = new StringOffset();
						stringOffset.AbsolutePosition = (uint)num2;
						stringOffset.RelativePosition = (ushort)num3;
						eXTSST.Offsets.Add(stringOffset);
					}
					num++;
					if (num == (int)eXTSST.NumStrings)
					{
						num = 0;
					}
					num2 += stringDataLength;
					num3 += stringDataLength;
				}
				return eXTSST;
			}
		}
		private static Record EncodeImages(IList<Image> images)
		{
			MSODRAWINGGROUP mSODRAWINGGROUP = new MSODRAWINGGROUP();
			MsofbtDggContainer msofbtDggContainer = new MsofbtDggContainer();
			mSODRAWINGGROUP.EscherRecords.Add(msofbtDggContainer);
			MsofbtDgg msofbtDgg = new MsofbtDgg();
			msofbtDgg.NumSavedDrawings = images.Count;
			checked
			{
				msofbtDgg.NumSavedShapes = images.Count + 1;
				msofbtDgg.MaxShapeID = 1024 + msofbtDgg.NumSavedShapes;
				msofbtDgg.GroupIdClusters.Add(1, msofbtDgg.NumSavedShapes);
				msofbtDggContainer.EscherRecords.Add(msofbtDgg);
				MsofbtBstoreContainer msofbtBstoreContainer = new MsofbtBstoreContainer();
				msofbtBstoreContainer.Instance = (ushort)images.Count;
				foreach (Image current in images)
				{
					MsofbtBSE msofbtBSE = new MsofbtBSE();
					msofbtBSE.UID = Guid.NewGuid();
					msofbtBSE.Ref = 1;
					msofbtBSE.Version = 2;
					msofbtBSE.BlipRecord = WorkbookEncoder.CreateBlipRecord(current);
					msofbtBSE.BlipRecord.Type = current.Format;
					msofbtBSE.BlipRecord.ImageData = current.Data;
					msofbtBSE.BlipRecord.UID = msofbtBSE.UID;
					msofbtBSE.BlipRecord.Marker = 255;
					msofbtBSE.SetBlipType(current.Format);
					msofbtBstoreContainer.EscherRecords.Add(msofbtBSE);
				}
				msofbtDggContainer.EscherRecords.Add(msofbtBstoreContainer);
				MsofbtOPT msofbtOPT = new MsofbtOPT();
				msofbtOPT.Add(PropertyIDs.FitTextToShape, 524296u);
				msofbtOPT.Add(PropertyIDs.FillColor, 134217793u);
				msofbtOPT.Add(PropertyIDs.LineColor, 134217792u);
				msofbtDggContainer.EscherRecords.Add(msofbtOPT);
				MsofbtSplitMenuColors msofbtSplitMenuColors = new MsofbtSplitMenuColors();
				msofbtSplitMenuColors.Instance = 4;
				msofbtSplitMenuColors.Color1 = 134217741;
				msofbtSplitMenuColors.Color2 = 134217740;
				msofbtSplitMenuColors.Color3 = 134217751;
				msofbtSplitMenuColors.Color4 = 268435703;
				msofbtDggContainer.EscherRecords.Add(msofbtSplitMenuColors);
				return mSODRAWINGGROUP;
			}
		}
		private static MsofbtBlip CreateBlipRecord(Image image)
		{
			MsofbtBlip result;
			switch (image.Format)
			{
			case 61466:
				result = new MsofbtBlipMetafileEMF();
				break;

			case 61467:
				result = new MsofbtBlipMetafileWMF();
				break;

			case 61468:
				result = new MsofbtBlipMetafilePICT();
				break;

			case 61469:
				result = new MsofbtBlipBitmapJPEG();
				break;

			case 61470:
				result = new MsofbtBlipBitmapPNG();
				break;

			case 61471:
				result = new MsofbtBlipBitmapDIB();
				break;

			default:
				throw new Exception("Image format not supported.");
			}
			return result;
		}
	}
}
