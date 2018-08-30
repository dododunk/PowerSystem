using System;
namespace ExcelLibrary.CompoundDocumentFormat
{
	public class ByteOrderMarks
	{
		public static readonly byte[] LittleEndian = new byte[]
		{
			254,
			255
		};
		public static readonly byte[] BigEndian = new byte[]
		{
			255,
			254
		};
	}
}
