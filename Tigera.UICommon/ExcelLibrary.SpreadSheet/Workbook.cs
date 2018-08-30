using ExcelLibrary.BinaryDrawingFormat;
using ExcelLibrary.BinaryFileFormat;
using ExcelLibrary.CompoundDocumentFormat;
using System;
using System.Collections.Generic;
using System.IO;
namespace ExcelLibrary.SpreadSheet
{
	public class Workbook
	{
		public List<Worksheet> Worksheets = new List<Worksheet>();
		public MSODRAWINGGROUP DrawingGroup;
		public List<Record> Records;
		public static Workbook Open(string file)
		{
			CompoundDocument compoundDocument = CompoundDocument.Read(file);
			if (compoundDocument == null)
			{
				throw new Exception("Invalid Excel file");
			}
			byte[] streamData = compoundDocument.GetStreamData("Workbook");
			return WorkbookDecoder.Decode(new MemoryStream(streamData));
		}
		public void Save(string file)
		{
			CompoundDocument compoundDocument = CompoundDocument.Create(file);
			MemoryStream memoryStream = new MemoryStream();
			WorkbookEncoder.Encode(this, memoryStream);
			compoundDocument.WriteStreamData(new string[]
			{
				"Workbook"
			}, memoryStream.ToArray());
			compoundDocument.Save();
			compoundDocument.Close();
		}
		public List<byte[]> ExtractImages()
		{
			List<byte[]> list = new List<byte[]>();
			if (this.DrawingGroup != null)
			{
				MsofbtDggContainer msofbtDggContainer = this.DrawingGroup.EscherRecords[0] as MsofbtDggContainer;
				using (List<EscherRecord>.Enumerator enumerator = msofbtDggContainer.BstoreContainer.EscherRecords.GetEnumerator())
				{
					while (enumerator.MoveNext())
					{
						MsofbtBSE msofbtBSE = (MsofbtBSE)enumerator.Current;
						if (msofbtBSE.BlipRecord != null)
						{
							list.Add(msofbtBSE.ImageData);
						}
					}
				}
			}
			return list;
		}
		public Image ExtractImage(int index)
		{
			Image result;
			if (this.DrawingGroup != null)
			{
				MsofbtDggContainer msofbtDggContainer = this.DrawingGroup.EscherRecords[0] as MsofbtDggContainer;
				MsofbtBSE msofbtBSE = msofbtDggContainer.BstoreContainer.EscherRecords[index] as MsofbtBSE;
				if (msofbtBSE.BlipRecord != null)
				{
					result = new Image(msofbtBSE.ImageData, msofbtBSE.BlipRecord.Type);
					return result;
				}
			}
			result = null;
			return result;
		}
		internal void RemoveRecord(int index)
		{
			Record record = this.Records[index];
			checked
			{
				foreach (Record current in this.Records)
				{
					if (current.Type == 133)
					{
						((BOUNDSHEET)current).StreamPosition -= (uint)record.FullSize;
						current.Encode();
					}
					if (current.Type == 255)
					{
						foreach (StringOffset current2 in ((EXTSST)current).Offsets)
						{
							current2.AbsolutePosition -= (uint)record.FullSize;
						}
						current.Encode();
					}
					if (record.Type == 224 && current is CellValue)
					{
						(current as CellValue).XFIndex = 0;
						current.Encode();
					}
				}
				this.Records.RemoveAt(index);
			}
		}
	}
}
