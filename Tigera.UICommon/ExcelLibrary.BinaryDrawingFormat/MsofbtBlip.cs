using System;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtBlip : EscherRecord
	{
		public Guid UID;
		public byte Marker;
		public byte[] ImageData;
		public MsofbtBlip()
		{
		}
		public MsofbtBlip(EscherRecord record) : base(record)
		{
		}
	}
}
