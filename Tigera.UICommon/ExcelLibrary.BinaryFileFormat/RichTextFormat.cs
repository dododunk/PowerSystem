using System;
using System.Collections.Generic;
namespace ExcelLibrary.BinaryFileFormat
{
	public class RichTextFormat
	{
		public List<ushort> CharIndexes;
		public List<ushort> FontIndexes;
		public RichTextFormat()
		{
			this.CharIndexes = new List<ushort>();
			this.FontIndexes = new List<ushort>();
		}
		public RichTextFormat(int numberOfFormattingRuns)
		{
			this.CharIndexes = new List<ushort>(numberOfFormattingRuns);
			this.FontIndexes = new List<ushort>(numberOfFormattingRuns);
		}
	}
}
