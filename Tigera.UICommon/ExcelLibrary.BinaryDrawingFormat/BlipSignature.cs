using System;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public static class BlipSignature
	{
		public const ushort UNKNOWN = 0;
		public const ushort EMF = 980;
		public const ushort WMF = 534;
		public const ushort PICT = 1346;
		public const ushort JPEG = 1130;
		public const ushort PNG = 1760;
		public const ushort JFIF = 1130;
		public const ushort DIB = 1960;
		public const ushort CMYKJPEG = 1762;
		public const ushort TIFF = 1764;
		public const ushort Client = 2048;
		public static ushort FromBlipType(byte bliptype)
		{
			ushort result;
			switch (bliptype)
			{
			case 2:
				result = 980;
				break;

			case 3:
				result = 534;
				break;

			case 4:
				result = 1346;
				break;

			case 5:
				result = 1130;
				break;

			case 6:
				result = 1760;
				break;

			case 7:
				result = 1960;
				break;

			default:
				result = 0;
				break;
			}
			return result;
		}
	}
}
