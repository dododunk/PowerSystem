using System;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class ShapeFlag
	{
		public const int Group = 1;
		public const int Child = 2;
		public const int Patriarch = 4;
		public const int Deleted = 8;
		public const int Oleshape = 16;
		public const int Havemaster = 32;
		public const int Fliphoriz = 64;
		public const int Flipvert = 128;
		public const int Connector = 256;
		public const int Haveanchor = 512;
		public const int Background = 1024;
		public const int Hasshapetype = 2048;
	}
}
