using ExcelLibrary.SpreadSheet;
using QiHe.CodeLib;
using System;
using System.Collections.Generic;
namespace ExcelLibrary.BinaryFileFormat
{
	public class SharedResource
	{
		public SST SharedStringTable;
		public DateTime BaseDate;
		public ColorPalette ColorPalette = new ColorPalette();
		public List<FORMAT> FormatRecords = new List<FORMAT>();
		public List<XF> ExtendedFormats = new List<XF>();
		public CellFormatCollection CellFormats = new CellFormatCollection();
		public UniqueList<Image> Images = new UniqueList<Image>();
		public List<FONT> Fonts = new List<FONT>();
		private Dictionary<string, int> NumberFormatXFIndice = new Dictionary<string, int>();
		private ushort MaxNumberFormatIndex;
		public SharedResource()
		{
		}
		public SharedResource(bool newbook)
		{
			FONT fONT = new FONT();
			fONT.Height = 200;
			fONT.OptionFlags = 0;
			fONT.ColorIndex = 32767;
			fONT.Weight = 400;
			fONT.Escapement = 0;
			fONT.Underline = 0;
			fONT.CharacterSet = 1;
			fONT.Name = "Arial";
			checked
			{
				for (ushort num = 0; num < 21; num += 1)
				{
					XF xF = new XF();
					xF.Attributes = 252;
					xF.CellProtection = 65524;
					xF.PatternColorIndex = 64;
					xF.PatternBackgroundColorIndex = 130;
					xF.FontIndex = 0;
					xF.FormatIndex = num;
					this.ExtendedFormats.Add(xF);
				}
				this.MaxNumberFormatIndex = 163;
				this.GetXFIndex(CellFormat.General);
				this.SharedStringTable = new SST();
			}
		}
		public string GetStringFromSST(int index)
		{
			string result;
			if (this.SharedStringTable != null)
			{
				result = this.SharedStringTable.StringList[index];
			}
			else
			{
				result = null;
			}
			return result;
		}
		public int GetSSTIndex(string text)
		{
			checked
			{
				this.SharedStringTable.TotalOccurance++;
				int num = this.SharedStringTable.StringList.IndexOf(text);
				int result;
				if (num == -1)
				{
					this.SharedStringTable.StringList.Add(text);
					result = this.SharedStringTable.StringList.Count - 1;
				}
				else
				{
					result = num;
				}
				return result;
			}
		}
		public double EncodeDateTime(DateTime value)
		{
			double num = (double)(value - this.BaseDate).Days;
			if (num > 365.0)
			{
				num += 1.0;
			}
			return num;
		}
		internal int GetXFIndex(CellFormat cellFormat)
		{
			string formatString = cellFormat.FormatString;
			checked
			{
				int result;
				if (this.NumberFormatXFIndice.ContainsKey(formatString))
				{
					result = this.NumberFormatXFIndice[formatString];
				}
				else
				{
					ushort num = this.CellFormats.GetFormatIndex(formatString);
					if (num == 65535)
					{
						ushort maxNumberFormatIndex;
						this.MaxNumberFormatIndex =(ushort)( (maxNumberFormatIndex = this.MaxNumberFormatIndex) + 1);
						num = maxNumberFormatIndex;
					}
					FORMAT fORMAT = new FORMAT();
					fORMAT.FormatIndex = num;
					fORMAT.FormatString = formatString;
					this.FormatRecords.Add(fORMAT);
					XF xF = new XF();
					xF.Attributes = 252;
					xF.CellProtection = 0;
					xF.PatternColorIndex = 64;
					xF.PatternBackgroundColorIndex = 130;
					xF.FontIndex = 0;
					xF.FormatIndex = num;
					this.ExtendedFormats.Add(xF);
					int num2 = this.ExtendedFormats.Count - 1;
					this.NumberFormatXFIndice.Add(formatString, num2);
					result = num2;
				}
				return result;
			}
		}
	}
}
