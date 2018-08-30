using System;
namespace ExcelLibrary.BinaryFileFormat
{
	public class StreamType
	{
		public const ushort WorkbookGlobals = 5;
		public const ushort VisualBasicModule = 6;
		public const ushort Worksheet = 16;
		public const ushort Chart = 32;
		public const ushort Macrosheet = 64;
		public const ushort WorkspaceFile = 256;
	}
}
