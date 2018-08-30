using System;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public static class BlipType
	{
		public const byte ERROR = 0;
		public const byte UNKNOWN = 1;
		public const byte EMF = 2;
		public const byte WMF = 3;
		public const byte PICT = 4;
		public const byte JPEG = 5;
		public const byte PNG = 6;
		public const byte DIB = 7;
		public static byte FromImageFormat(ushort imageForamt)
		{
			byte result;
			switch (imageForamt)
			{
			case 61466:
				result = 2;
				break;

			case 61467:
				result = 3;
				break;

			case 61468:
				result = 4;
				break;

			case 61469:
				result = 5;
				break;

			case 61470:
				result = 6;
				break;

			case 61471:
				result = 7;
				break;

			default:
				result = 1;
				break;
			}
			return result;
		}
	}
}
