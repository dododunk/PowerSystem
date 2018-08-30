using System;
namespace ExcelLibrary.CompoundDocumentFormat
{
	public static class EntryType
	{
		public const byte Empty = 0;
		public const byte Storage = 1;
		public const byte Stream = 2;
		public const byte LockBytes = 3;
		public const byte Property = 4;
		public const byte Root = 5;
	}
}
